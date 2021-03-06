#include <common/getThreadId.h>

#if OS_LINUX
    #include <unistd.h>
    #include <syscall.h>
#elif OS_FREEBSD
    #include <pthread_np.h>
#else
    #include <pthread.h>
    #include <stdexcept>
#endif


static thread_local uint64_t current_tid = 0;
uint64_t getThreadId()
{
    if (!current_tid)
    {
#if OS_LINUX
        current_tid = syscall(SYS_gettid); /// This call is always successful. - man gettid
#elif OS_FREEBSD
        current_tid = pthread_getthreadid_np();
#else
        if (0 != pthread_threadid_np(nullptr, &current_tid))
            throw std::logic_error("pthread_threadid_np returned error");
#endif
    }

    return current_tid;
}
