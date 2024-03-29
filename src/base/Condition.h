/**********************************************************
 *   Author          : Apriluestc
 *   Email           : 13669186256@163.com
 *   Last modified   : 2019-07-28 13:27
 *   Filename        : Condition.h
 *   Description     : 
 * *******************************************************/

#ifndef INCLUDE_CONDITION_H
#define INCLUDE_CONDITION_H

#include <pthread.h>
#include <pthread.h>
#include <errno.h>
#include <cstdint>
#include <time.h>
#include <boost/noncopyable.hpp>

#include "MutexLock.h"
class Condition : boost::noncopyable {
public:
    explicit Condition(MutexLock &_mutex)
        :mutex(_mutex)
    {
        pthread_cond_init(&cond, NULL);
    }
    ~Condition() {
        pthread_cond_destroy(&cond);
    }
    void wait() {
        pthread_cond_wait(&cond, mutex.get());
    }
    void notify() {
        pthread_cond_signal(&cond);
    }
    void notifyAll() {
        pthread_cond_broadcast(&cond);
    }
    bool waitForSeconds(int seconds) {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);
    }
private:
    MutexLock &mutex;
    pthread_cond_t cond;
}; // Condition

#endif // INCLUDE_CONDITION_H
