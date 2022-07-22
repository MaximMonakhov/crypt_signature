#ifndef UBI_MUTEX_H
#define UBI_MUTEX_H 1

#include <sys/param.h>

#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif /* HAVE_LIMITS_H */

#include <pthread.h>

#if defined( __cplusplus )
extern "C" {
#endif

#if defined UNIX && !defined SOLARIS && !defined AIX
#define HAS_FLOCK 1
#endif // UNIX && !SOLARIS && !AIX

#define GMUTEX_SNAME 0 /* ubi_mutex_open() конструирует имя файла из названия мютеха */
#define GMUTEX_FPATH 1 /* ubi_mutex_open() использует название мютеха как имя файла */
#define GMUTEX_RECURSIVE 2 /* ubi_mutex_open() создается рекурсивным */
#define GMUTEX_NO_FILE 4 /* ubi_mutex_open() создается без использования файла */
#ifdef HAS_FLOCK
#define GMUTEX_USE_FLOCK 8 /* ubi_mutex_lock() и ubi_mutex_unlock() будут использовать flock вместо lockf */
#define GMUTEX_ALL_FLAGS (GMUTEX_FPATH|GMUTEX_RECURSIVE|GMUTEX_NO_FILE|GMUTEX_USE_FLOCK) /* Маска для всех доступных флагов */
#else // HAS_FLOCK
#define GMUTEX_ALL_FLAGS (GMUTEX_FPATH|GMUTEX_RECURSIVE|GMUTEX_NO_FILE) /* Маска для всех доступных флагов */
#endif // HAS_FLOCK

typedef struct ubi_named_mutex_t_ {
    pthread_mutex_t mutex;
    int sem_fd;
    char name[PATH_MAX];
    int flags;
    struct ubi_named_mutex_t_* next;
    struct ubi_named_mutex_t_* prev;
    int count;
    // 2021-may-05 dim CPCSP-12087
    // -- существующий код позволяет установить блокировку на файл много раз,
    //    но все блокировки снимаются единственным вызовом unlock
    // -- рекурсивный mutex "знает" уровень рекурсии, но нет возможности его узнать
    // -- приходится самостоятельно считать уровень вложенности блокировок файла
    //
    // проблема описывается, например, в
    // https://stackoverflow.com/questions/46425109/access-the-owners-counter-used-by-stdrecursive-mutex
    unsigned flock_level;
} ubi_named_mutex_t;

/* wrapper к pthread_mutex_init() с установкой атрибута RECURSIVE */
int support_mutex_init_recursive(pthread_mutex_t *mutex);

int ubi_mutex_open(ubi_named_mutex_t **ubi_mutex, const char *name, int flags);
int ubi_mutex_close(ubi_named_mutex_t *ubi_mutex);
int ubi_mutex_lock(ubi_named_mutex_t *ubi_mutex);
int ubi_mutex_unlock(ubi_named_mutex_t *ubi_mutex);

#if defined( __cplusplus )
}
#endif

#endif /* UBI_MUTEX_H */
