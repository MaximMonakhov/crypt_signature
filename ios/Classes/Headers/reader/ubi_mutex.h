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

#define GMUTEX_SNAME 0 /* ubi_mutex_open() ������������ ��� ����� �� �������� ������ */
#define GMUTEX_FPATH 1 /* ubi_mutex_open() ���������� �������� ������ ��� ��� ����� */
#define GMUTEX_RECURSIVE 2 /* ubi_mutex_open() ��������� ����������� */
#define GMUTEX_NO_FILE 4 /* ubi_mutex_open() ��������� ��� ������������� ����� */
#ifdef HAS_FLOCK
#define GMUTEX_USE_FLOCK 8 /* ubi_mutex_lock() � ubi_mutex_unlock() ����� ������������ flock ������ lockf */
#define GMUTEX_ALL_FLAGS (GMUTEX_FPATH|GMUTEX_RECURSIVE|GMUTEX_NO_FILE|GMUTEX_USE_FLOCK) /* ����� ��� ���� ��������� ������ */
#else // HAS_FLOCK
#define GMUTEX_ALL_FLAGS (GMUTEX_FPATH|GMUTEX_RECURSIVE|GMUTEX_NO_FILE) /* ����� ��� ���� ��������� ������ */
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
    // -- ������������ ��� ��������� ���������� ���������� �� ���� ����� ���,
    //    �� ��� ���������� ��������� ������������ ������� unlock
    // -- ����������� mutex "�����" ������� ��������, �� ��� ����������� ��� ������
    // -- ���������� �������������� ������� ������� ����������� ���������� �����
    //
    // �������� �����������, ��������, �
    // https://stackoverflow.com/questions/46425109/access-the-owners-counter-used-by-stdrecursive-mutex
    unsigned flock_level;
} ubi_named_mutex_t;

/* wrapper � pthread_mutex_init() � ���������� �������� RECURSIVE */
int support_mutex_init_recursive(pthread_mutex_t *mutex);

int ubi_mutex_open(ubi_named_mutex_t **ubi_mutex, const char *name, int flags);
int ubi_mutex_close(ubi_named_mutex_t *ubi_mutex);
int ubi_mutex_lock(ubi_named_mutex_t *ubi_mutex);
int ubi_mutex_unlock(ubi_named_mutex_t *ubi_mutex);

#if defined( __cplusplus )
}
#endif

#endif /* UBI_MUTEX_H */
