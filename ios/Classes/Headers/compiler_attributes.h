/*
 * Copyright(C) 2000-2020 Проект ИОК
 *
 * Этот файл содержит информацию, являющуюся
 * собственностью компании Крипто Про.
 *
 * Любая часть этого файла не может быть скопирована,
 * исправлена, переведена на другие языки,
 * локализована или модифицирована любым способом,
 * откомпилирована, передана по сети с или на
 * любую компьютерную систему без предварительного
 * заключения соглашения с компанией Крипто Про.
 */

#if !defined _COMPILER_ATTRIBUTES_H_
#define _COMPILER_ATTRIBUTES_H_

#if !defined __GNUC__
#   define ATTR_NOASAN
#   define ATTR_NOTSAN
#   define ATTR_NORETURN
#   define ATTR_USERES
#if defined _WIN32
#   define CP_FORCE_INLINE __inline
#else
#   define CP_FORCE_INLINE inline
#endif	/* _WIN32 */
#   define DLL_LOCAL /* dim: для не-gcc отдельно посмотрю, если для gcc получится хорошо */
#   define DLL_PUBLIC
#else

/* CPCSP-11164 */
/* 2020-jun-11 dim: после отказа от gcc-3.2/CheckPoint убрать #if */
#if ((__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || __GNUC__ >= 4)
#   define DLL_LOCAL  __attribute__((visibility("hidden")))
#   define DLL_PUBLIC __attribute__((visibility("default")))
#else
#   define DLL_LOCAL
#   define DLL_PUBLIC
#endif

/* CPCSP-8892 dim: gcc-4.8 не меняется, чтобы не менялась сборка */
#if !((__GNUC__ == 4 && __GNUC_MINOR__ >= 8) || __GNUC__ >= 5)
#   define ATTR_NOASAN
#   define ATTR_NOTSAN
#   define ATTR_NORETURN
#   define ATTR_USERES
#   define CP_FORCE_INLINE inline
#else

/* наши реализации mem*() и str*() вызывают ошибки с -fsanitize=address */
#if defined __SANITIZE_ADDRESS__
# define ATTR_NOASAN __attribute__((no_sanitize_address))
#else
# define ATTR_NOASAN
#endif	/* __SANITIZE_ADDRESS__ */

/* распределитель хэндлов вызывает сообщения, про которые и так известно */
#if defined __SANITIZE_THREAD__
# define ATTR_NOTSAN __attribute__((no_sanitize_thread))
#else
# define ATTR_NOTSAN
#endif	/* __SANITIZE_THREAD__ */

#   define ATTR_NORETURN     __attribute__((noreturn))
#   define ATTR_USERES       __attribute__((warn_unused_result))
#   define CP_FORCE_INLINE   inline __attribute__ ((__always_inline__))
#endif	/* не новый gcc */
#endif	/* не gcc */
#endif	/* _COMPILER_ATTRIBUTES_H_ */
