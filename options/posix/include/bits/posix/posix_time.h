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

#ifdef __cplusplus
}
#endif

#endif // MLIBC_POSIX_TIME_H
