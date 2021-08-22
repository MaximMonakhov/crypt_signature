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

#define GMUTEX_SNAME 0 /* ubi_mutex_open() конструирует имя файла из названия мютеха */
#define GMUTEX_FPATH 1 /* ubi_mutex_open() использует название мютеха как имя файла */

typedef struct ubi_named_mutex_t_ {
    pthread_mutex_t mutex;
    int sem_fd;
    char name[PATH_MAX];
    struct ubi_named_mutex_t_* next;
    struct ubi_named_mutex_t_* prev;
    int count;
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
