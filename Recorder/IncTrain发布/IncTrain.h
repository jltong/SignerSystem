//
// MATLAB Compiler: 4.16 (R2011b)
// Date: Fri Oct 19 19:10:53 2012
// Arguments: "-B" "macro_default" "-W" "cpplib:IncTrain" "-T" "link:lib"
// "IncrementGMM" "readspeech" "enframe" "sgn" "getmfcc" "Probabilitys"
// "Cluster_Probability" "Cluster_Covariance" "Exchange" 
//

#ifndef __IncTrain_h
#define __IncTrain_h 1

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

#ifdef EXPORTING_IncTrain
#define PUBLIC_IncTrain_C_API __global
#else
#define PUBLIC_IncTrain_C_API /* No import statement needed. */
#endif

#define LIB_IncTrain_C_API PUBLIC_IncTrain_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_IncTrain
#define PUBLIC_IncTrain_C_API __declspec(dllexport)
#else
#define PUBLIC_IncTrain_C_API __declspec(dllimport)
#endif

#define LIB_IncTrain_C_API PUBLIC_IncTrain_C_API


#else

#define LIB_IncTrain_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_IncTrain_C_API 
#define LIB_IncTrain_C_API /* No special import/export declaration */
#endif

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV IncTrainInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV IncTrainInitialize(void);

extern LIB_IncTrain_C_API 
void MW_CALL_CONV IncTrainTerminate(void);



extern LIB_IncTrain_C_API 
void MW_CALL_CONV IncTrainPrintStackTrace(void);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxIncrementGMM(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxReadspeech(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxEnframe(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxSgn(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxGetmfcc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxProbabilitys(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxCluster_Probability(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                         *prhs[]);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxCluster_Covariance(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                        *prhs[]);

extern LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxExchange(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_IncTrain_C_API 
long MW_CALL_CONV IncTrainGetMcrID();


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_IncTrain
#define PUBLIC_IncTrain_CPP_API __declspec(dllexport)
#else
#define PUBLIC_IncTrain_CPP_API __declspec(dllimport)
#endif

#define LIB_IncTrain_CPP_API PUBLIC_IncTrain_CPP_API

#else

#if !defined(LIB_IncTrain_CPP_API)
#if defined(LIB_IncTrain_C_API)
#define LIB_IncTrain_CPP_API LIB_IncTrain_C_API
#else
#define LIB_IncTrain_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_IncTrain_CPP_API void MW_CALL_CONV IncrementGMM(const mwArray& speaker, const mwArray& SphName, const mwArray& maxtrain);

extern LIB_IncTrain_CPP_API void MW_CALL_CONV readspeech(int nargout, mwArray& Wavx1, mwArray& fs, const mwArray& speechname, const mwArray& SpeakerName, const mwArray& addr);

extern LIB_IncTrain_CPP_API void MW_CALL_CONV enframe(int nargout, mwArray& f, const mwArray& x, const mwArray& win, const mwArray& inc);

extern LIB_IncTrain_CPP_API void MW_CALL_CONV sgn(int nargout, mwArray& output, const mwArray& input);

extern LIB_IncTrain_CPP_API void MW_CALL_CONV getmfcc(int nargout, mwArray& mfccc, mwArray& FrameSize, mwArray& framelocation, mwArray& energy, const mwArray& speechname, const mwArray& SpeakerName, const mwArray& dimension);

extern LIB_IncTrain_CPP_API void MW_CALL_CONV Probabilitys(int nargout, mwArray& pro, const mwArray& No_of_Cluster, const mwArray& No_of_Feature, const mwArray& X, const mwArray& alpha, const mwArray& Mu, const mwArray& Variances);

extern LIB_IncTrain_CPP_API void MW_CALL_CONV Cluster_Probability(int nargout, mwArray& PC, mwArray& INDEX, const mwArray& Data, const mwArray& Mu);

extern LIB_IncTrain_CPP_API void MW_CALL_CONV Cluster_Covariance(int nargout, mwArray& COVAR, const mwArray& Data, const mwArray& IDX, const mwArray& No_of_Cluster);

extern LIB_IncTrain_CPP_API void MW_CALL_CONV Exchange(int nargout, mwArray& b, mwArray& a, const mwArray& a_in1, const mwArray& b_in1);

#endif
#endif
