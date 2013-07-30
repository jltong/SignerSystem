//
// MATLAB Compiler: 4.16 (R2011b)
// Date: Wed Jun 06 11:29:47 2012
// Arguments: "-B" "macro_default" "-W" "cpplib:Initialize" "-T" "link:lib"
// "Initial" 
//

#ifndef __Initialize_h
#define __Initialize_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_Initialize
#define PUBLIC_Initialize_C_API __global
#else
#define PUBLIC_Initialize_C_API /* No import statement needed. */
#endif

#define LIB_Initialize_C_API PUBLIC_Initialize_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_Initialize
#define PUBLIC_Initialize_C_API __declspec(dllexport)
#else
#define PUBLIC_Initialize_C_API __declspec(dllimport)
#endif

#define LIB_Initialize_C_API PUBLIC_Initialize_C_API


#else

#define LIB_Initialize_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_Initialize_C_API 
#define LIB_Initialize_C_API /* No special import/export declaration */
#endif

extern LIB_Initialize_C_API 
bool MW_CALL_CONV InitializeInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_Initialize_C_API 
bool MW_CALL_CONV InitializeInitialize(void);

extern LIB_Initialize_C_API 
void MW_CALL_CONV InitializeTerminate(void);



extern LIB_Initialize_C_API 
void MW_CALL_CONV InitializePrintStackTrace(void);

extern LIB_Initialize_C_API 
bool MW_CALL_CONV mlxInitial(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Initialize_C_API 
long MW_CALL_CONV InitializeGetMcrID();


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_Initialize
#define PUBLIC_Initialize_CPP_API __declspec(dllexport)
#else
#define PUBLIC_Initialize_CPP_API __declspec(dllimport)
#endif

#define LIB_Initialize_CPP_API PUBLIC_Initialize_CPP_API

#else

#if !defined(LIB_Initialize_CPP_API)
#if defined(LIB_Initialize_C_API)
#define LIB_Initialize_CPP_API LIB_Initialize_C_API
#else
#define LIB_Initialize_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_Initialize_CPP_API void MW_CALL_CONV Initial();

#endif
#endif
