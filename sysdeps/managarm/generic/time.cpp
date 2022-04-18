
#include <bits/ensure.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>

#include <hel.h>
#include <hel-syscalls.h>
#include <mlibc/debug.hpp>
#include <mlibc/allocator.hpp>
#include <mlibc/posix-pipe.hpp>
#include <mlibc/all-sysdeps.hpp>
#include <posix.frigg_bragi.hpp>

struct TrackerPage {
	uint64_t seqlock;
	int32_t state;
	int32_t padding;
	int64_t refClock;
	int64_t baseRealtime;
};

extern thread_local TrackerPage *__mlibc_clk_tracker_page;

namespace mlibc {

int sys_timer_create(clockid_t clockid, struct sigevent *__restrict sevp,
					 timer_t *__restrict timerid, bool sival_is_id){
	SignalGuard sguard;

	managarm::posix::TimerCreateRequest<MemoryAllocator> req(getSysdepsAllocator());
	req.set_clockid(clockid);
	req.set_notify(sevp->sigev_notify);

	//bad check, maybe instead introduce IS_SIGNAL(x) macro
	if(sevp->sigev_signo < 1 || sevp->sigev_signo > 34){
		return EINVAL;
	}

	req.set_signal(sevp->sigev_signo);
	req.set_sival(sevp->sigev_value.sival_int);
	req.set_sival_is_id(sival_is_id);
	req.set_notify_func((uint64_t)sevp->sigev_notify_function);

	auto [offer, send_head, send_tail, recv_resp] =
		exchangeMsgsSync(
			getPosixLane(),
			helix_ng::offer(
				helix_ng::sendBragiHeadTail(req, getSysdepsAllocator()),
				helix_ng::recvInline()
			)
		);

	HEL_CHECK(offer.error());
	HEL_CHECK(send_head.error());
	HEL_CHECK(send_tail.error());
	HEL_CHECK(recv_resp.error());

	managarm::posix::SvrResponse<MemoryAllocator> resp(getSysdepsAllocator());
	resp.ParseFromArray(recv_resp.data(), recv_resp.length());
	if(resp.error() == managarm::posix::Errors::ILLEGAL_ARGUMENTS){
		return EINVAL;
	}
	else if(resp.error() == managarm::posix::Errors::NOT_SUPPORTED){
		return ENOTSUP;
	}
	else if(resp.error() == managarm::posix::Errors::INSUFFICIENT_PERMISSION){
		return EPERM;
	}

	*timerid = resp.timerid();
	return 0;
}

int sys_clock_get(int clock, time_t *secs, long *nanos) {
	// This implementation is inherently signal-safe.
	if(clock == CLOCK_MONOTONIC) {
		uint64_t tick;
		HEL_CHECK(helGetClock(&tick));
		*secs = tick / 1000000000;
		*nanos = tick % 1000000000;
	}else if(clock == CLOCK_REALTIME) {
		cacheFileTable();

		// Start the seqlock read.
		auto seqlock = __atomic_load_n(&__mlibc_clk_tracker_page->seqlock, __ATOMIC_ACQUIRE);
		__ensure(!(seqlock & 1));

		// Perform the actual loads.
		auto ref = __atomic_load_n(&__mlibc_clk_tracker_page->refClock, __ATOMIC_RELAXED);
		auto base = __atomic_load_n(&__mlibc_clk_tracker_page->baseRealtime, __ATOMIC_RELAXED);

		// Finish the seqlock read.
		__atomic_thread_fence(__ATOMIC_ACQUIRE);
		__ensure(__atomic_load_n(&__mlibc_clk_tracker_page->seqlock, __ATOMIC_RELAXED) == seqlock);

		// Calculate the current time.
		uint64_t tick;
		HEL_CHECK(helGetClock(&tick));
		__ensure(tick >= (uint64_t)__mlibc_clk_tracker_page->refClock); // TODO: Respect the seqlock!
		tick -= ref;
		tick += base;
		*secs = tick / 1000000000;
		*nanos = tick % 1000000000;
	}else if(clock == CLOCK_PROCESS_CPUTIME_ID) {
		mlibc::infoLogger() << "\e[31mmlibc: clock_gettime does not support the CPU time clocks"
				"\e[39m" << frg::endlog;
		*secs = 0;
		*nanos = 0;
	}else if(clock == CLOCK_MONOTONIC_RAW) {
		mlibc::infoLogger() << "\e[31mmlibc: clock_gettime implements CLOCK_MONOTONIC_RAW as CLOCK_MONOTONIC"
				"\e[39m" << frg::endlog;
		uint64_t tick;
		HEL_CHECK(helGetClock(&tick));
		*secs = tick / 1000000000;
		*nanos = tick % 1000000000;
	}else{
		mlibc::panicLogger() << "mlibc: Unexpected clock " << clock << frg::endlog;
	}
	return 0;
}

int sys_clock_getres(int clock, time_t *secs, long *nanos) {
	(void)clock;
	(void)secs;
	(void)nanos;
	mlibc::infoLogger() << "mlibc: clock_getres is a stub" << frg::endlog;
	return 0;
}

} //namespace mlibc

