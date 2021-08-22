#ifndef __IOS_SOCKETS_H__
#define __IOS_SOCKETS_H__
# if defined(IOS) && !defined(IOS_EMUL)
#  ifdef __cplusplus
extern "C" {
#  endif
int ios_bg_attach_socket(int sock);
int ios_bg_detach_socket(int sock);
typedef void (*ios_watch_callback_t)(int conns, int bytes, int sslbytes);
void ios_set_watch_callback(ios_watch_callback_t cb);
void ios_run_watch_callback(int conns, int bytes, int sslbytes);
#  ifdef __cplusplus
}
#  endif
# else /* IOS && !IOSEMUL */
#define ios_bg_attach_socket(x) 0
#define ios_bg_detach_socket(x) 0
#define ios_set_watch_callback(cb)
#define ios_run_watch_callback(a,b,c) 
# endif /* IOS && !IOS_EMUL */
#endif
