/**
 ******************************************************************************
 * @author: PND
 * @date:   04/09/2018
 * @brief: debug mt function
 ******************************************************************************
 **/
#ifndef __MT_DBG_H__
#define __MT_DBG_H__

#include <stdio.h>
#include <pthread.h>

#define MD_MUTEXAUTOLOCK_INIT(mutex) pthread_mutex_t AUTOLOCK_##mutex = PTHREAD_MUTEX_INITIALIZER;
#define MD_autoMutexLock(mutex, lock)                                             \
    __attribute__((cleanup(AutoUnLock))) pthread_mutex_t *lock = &AUTOLOCK_##mutex; \
    pthread_mutex_lock(lock);

__attribute__((always_inline)) inline void AutoUnLock(void *mutex)
{
    pthread_mutex_unlock(*(pthread_mutex_t **)mutex);
}

#ifndef MD_POINTER_CHECK_
#define MD_POINTER_CHECK_(p, errcode)          \
    do                                           \
    {                                            \
        if (!(p))                                \
        {                                        \
            printf("pointer[%s] is NULL\n", #p); \
            return errcode;                      \
        }                                        \
    } while (0)
#endif

#define DEBUG
#ifdef DEBUG
#define APP_PRINT(x...)       \
    do                        \
    {                         \
        printf("\033[1;32m"); \
        printf(x);            \
        printf("\033[0m\n");  \
    } while (0)
#define APP_DBG(x...)                                         \
    do                                                        \
    {                                                         \
        printf("\033[2;33m%s->%d: ", __FUNCTION__, __LINE__); \
        printf(x);                                            \
        printf("\033[0m\n");                                  \
    } while (0)
#define APP_INFO(x...)                                        \
    do                                                        \
    {                                                         \
        printf("\033[1;35m%s->%d: ", __FUNCTION__, __LINE__); \
        printf(x);                                            \
        printf("\033[0m\n");                                  \
    } while (0)

#define APP_ERR(x...)                                         \
    do                                                        \
    {                                                         \
        printf("\033[1;31m%s->%d: ", __FUNCTION__, __LINE__); \
        printf(x);                                            \
        printf("\033[0m\n");                                  \
    } while (0)

#else
#define APP_PRINT(args...) \
    do                     \
    {                      \
    } while (0)
#define APP_DBG(args...) \
    do                   \
    {                    \
    } while (0)
#define APP_INFO(args...) \
    do                    \
    {                     \
    } while (0)
#define APP_ERR(args...) \
    do                   \
    {                    \
    } while (0)
#endif

/******************************************************************************************************************************************
 * LOG
 * ****************************************************************************************************************************************/
#define MD_LOGD(tag, format, ...)                                           \
    do                                                                        \
    {                                                                         \
        printf("\033[1;34m [D][%s] " format "\033[0m\n", tag, ##__VA_ARGS__); \
    } while (0)

#define MD_LOGW(tag, format, ...)                                           \
    do                                                                        \
    {                                                                         \
        printf("\033[1;33m [W][%s] " format "\033[0m\n", tag, ##__VA_ARGS__); \
    } while (0)

#define MD_LOGI(tag, format, ...)                                           \
    do                                                                        \
    {                                                                         \
        printf("\033[1;35m [I][%s] " format "\033[0m\n", tag, ##__VA_ARGS__); \
    } while (0)

#define MD_LOGE(tag, format, ...)                                           \
    do                                                                        \
    {                                                                         \
        printf("\033[1;31m [E][%s] " format "\033[0m\n", tag, ##__VA_ARGS__); \
    } while (0)

#endif //__MT_DBG_H__
