//
// MATLAB Compiler: 4.16 (R2011b)
// Date: Fri Oct 19 19:08:05 2012
// Arguments: "-B" "macro_default" "-W" "cpplib:Training" "-T" "link:lib"
// "Training" "readspeech" "enframe" "sgn" "getmfcc" "Probabilitys"
// "GmmTraining" "Cluster_Probability" "Cluster_Covariance" 
//

#ifndef __Training_h
#define __Training_h 1

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

#ifdef EXPORTING_Training
#define PUBLIC_Training_C_API __global
#else
#define PUBLIC_Training_C_API /* No import statement needed. */
#endif

#define LIB_Training_C_API PUBLIC_Training_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_Training
#define PUBLIC_Training_C_API __declspec(dllexport)
#else
#define PUBLIC_Training_C_API __declspec(dllimport)
#endif

#define LIB_Training_C_API PUBLIC_Training_C_API


#else

#define LIB_Training_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_Training_C_API 
#define LIB_Training_C_API /* No special import/export declaration */
#endif

extern LIB_Training_C_API 
bool MW_CALL_CONV TrainingInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_Training_C_API 
bool MW_CALL_CONV TrainingInitialize(void);

extern LIB_Training_C_API 
void MW_CALL_CONV TrainingTerminate(void);



extern LIB_Training_C_API 
void MW_CALL_CONV TrainingPrintStackTrace(void);

extern LIB_Training_C_API 
bool MW_CALL_CONV mlxTraining(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Training_C_API 
bool MW_CALL_CONV mlxReadspeech(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Training_C_API 
bool MW_CALL_CONV mlxEnframe(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Training_C_API 
bool MW_CALL_CONV mlxSgn(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Training_C_API 
bool MW_CALL_CONV mlxGetmfcc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Training_C_API 
bool MW_CALL_CONV mlxProbabilitys(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Training_C_API 
bool MW_CALL_CONV mlxGmmTraining(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Training_C_API 
bool MW_CALL_CONV mlxCluster_Probability(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                         *prhs[]);

extern LIB_Training_C_API 
bool MW_CALL_CONV mlxCluster_Covariance(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                        *prhs[]);

extern LIB_Training_C_API 
long MW_CALL_CONV TrainingGetMcrID();


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_Training
#define PUBLIC_Training_CPP_API __declspec(dllexport)
#else
#define PUBLIC_Training_CPP_API __declspec(dllimport)
#endif

#define LIB_Training_CPP_API PUBLIC_Training_CPP_API

#else

#if !defined(LIB_Training_CPP_API)
#if defined(LIB_Training_C_API)
#define LIB_Training_CPP_API LIB_Training_C_API
#else
#define LIB_Training_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_Training_CPP_API void MW_CALL_CONV Training(const mwArray& SpkName, const mwArray& SphName, const mwArray& trainnum);

extern LIB_Training_CPP_API void MW_CALL_CONV readspeech(int nargout, mwArray& Wavx1, mwArray& fs, const mwArray& speechname, const mwArray& SpeakerName, const mwArray& addr);

extern LIB_Training_CPP_API void MW_CALL_CONV enframe(int nargout, mwArray& f, const mwArray& x, const mwArray& win, const mwArray& inc);

extern LIB_Training_CPP_API void MW_CALL_CONV sgn(int nargout, mwArray& output, const mwArray& input);

extern LIB_Training_CPP_API void MW_CALL_CONV getmfcc(int nargout, mwArray& mfccc, mwArray& FrameSize, mwArray& framelocation, mwArray& energy, const mwArray& speechname, const mwArray& SpeakerName, const mwArray& dimension);

extern LIB_Training_CPP_API void MW_CALL_CONV Probabilitys(int nargout, mwArray& pro, const mwArray& No_of_Cluster, const mwArray& No_of_Feature, const mwArray& X, const mwArray& alpha, const mwArray& Mu, const mwArray& Variances);

extern LIB_Training_CPP_API void MW_CALL_CONV GmmTraining(int nargout, mwArray& alpha, mwArray& Mu, mwArray& Variances, const mwArray& Input, const mwArray& No_of_Cluster, const mwArray& Iteration, const mwArray& maxtrain);

extern LIB_Training_CPP_API void MW_CALL_CONV Cluster_Probability(int nargout, mwArray& PC, mwArray& INDEX, const mwArray& Data, const mwArray& Mu);

extern LIB_Training_CPP_API void MW_CALL_CONV Cluster_Covariance(int nargout, mwArray& COVAR, const mwArray& Data, const mwArray& IDX, const mwArray& No_of_Cluster);

#endif
#endif
