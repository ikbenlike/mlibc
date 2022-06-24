
#include <errno.h>
#include <sys/wait.h>
#include <bits/ensure.h>

#include <mlibc/posix-sysdeps.hpp>
#include <mlibc/debug.hpp>

int waitid(idtype_t, id_t, siginfo_t *, int) {
	__ensure(!"Not implemented");
	__builtin_unreachable();
}

pid_t waitpid(pid_t pid, int *status, int flags) {
	pid_t ret;
	MLIBC_CHECK_OR_ENOSYS(mlibc::sys_waitpid, -1);
	if(int e = mlibc::sys_waitpid(pid, status, flags, &ret); e) {
		errno = e;
		return -1;
	}
	return ret;
}

pid_t wait(int *status) {
	return waitpid(-1, status, 0);
}

pid_t wait3(int *status, int options, struct rusage *rusage) {
	(void) rusage;
	mlibc::infoLogger() << "\e[31mmlibc: wait3() is not implemented correctly\e[39m"
		<< frg::endlog;
	return waitpid(-1, status, options);
}

pid_t wait4(pid_t pid, int *status, int options, struct rusage *ru) {
	pid_t ret;
	MLIBC_CHECK_OR_ENOSYS(mlibc::sys_wait4, -1);
	if(int e = mlibc::sys_wait4(pid, status, options, ru, &ret); e) {
		errno = e;
		return -1;
	}
	return ret;
}
