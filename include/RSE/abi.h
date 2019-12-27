#if defined(__cplusplus)
# define RSE_EXTERN extern "C"
#else
# define RSE_EXTERN
#endif

#if !(defined(RSE_STATIC)) && (defined(WIN32) || defined(_WIN32))
# if defined(RSE_DLL)
#  define RSE_DECLSPEC __declspec(dllexport)
# else
#  define RSE_DECLSPEC __declspec(dllimport)
# endif
#else
# define RSE_DECLSPEC
#endif

#define RSE_API RSE_EXTERN RSE_DECLSPEC
