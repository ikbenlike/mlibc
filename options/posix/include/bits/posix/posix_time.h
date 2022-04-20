#ifndef MLIBC_POSIX_TIME_H
#define MLIBC_POSIX_TIME_H

#include <bits/posix/timeval.h>
#include <bits/ansi/clockid_t.h>

#define TIMER_ABSTIME 1

#ifdef __cplusplus
extern "C" {
#endif

typedef long long timer_t;

int utimes(const char *, const struct timeval[2]);
int timer_create(clockid_t clockid, struct sigevent *__restrict sevp,
    timer_t *__restrict timerid);
int timer_delete(timer_t timerid);
int timer_getoverrun(timer_t timerid);
int timer_settime(timer_t timerid, int flags,
        const struct itimerspec *__restrict new_value,
        struct itimerspec *__restrict old_value);
int timer_gettime(timer_t timerid, struct itimerspec *curr_value);

#ifdef __cplusplus
}
#endif

#endif // MLIBC_POSIX_TIME_H
