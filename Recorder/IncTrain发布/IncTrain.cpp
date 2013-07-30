//
// MATLAB Compiler: 4.16 (R2011b)
// Date: Fri Oct 19 19:10:53 2012
// Arguments: "-B" "macro_default" "-W" "cpplib:IncTrain" "-T" "link:lib"
// "IncrementGMM" "readspeech" "enframe" "sgn" "getmfcc" "Probabilitys"
// "Cluster_Probability" "Cluster_Covariance" "Exchange" 
//

#include <stdio.h>
#define EXPORTING_IncTrain 1
#include "IncTrain.h"

static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#include <windows.h>

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_IncTrain_C_API
#define LIB_IncTrain_C_API /* No special import/export declaration */
#endif

LIB_IncTrain_C_API 
bool MW_CALL_CONV IncTrainInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
  if (!GetModuleFileName(GetModuleHandle("IncTrain"), path_to_dll, _MAX_PATH))
    return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream(path_to_dll, 
                                    331471);
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(   &_mcr_inst,
                                                                error_handler, 
                                                                print_handler,
                                                                ctfStream, 
                                                                331471);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
  return true;
}

LIB_IncTrain_C_API 
bool MW_CALL_CONV IncTrainInitialize(void)
{
  return IncTrainInitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_IncTrain_C_API 
void MW_CALL_CONV IncTrainTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_IncTrain_C_API 
long MW_CALL_CONV IncTrainGetMcrID() 
{
  return mclGetID(_mcr_inst);
}

LIB_IncTrain_C_API 
void MW_CALL_CONV IncTrainPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(&stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxIncrementGMM(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "IncrementGMM", nlhs, plhs, nrhs, prhs);
}

LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxReadspeech(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "readspeech", nlhs, plhs, nrhs, prhs);
}

LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxEnframe(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "enframe", nlhs, plhs, nrhs, prhs);
}

LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxSgn(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "sgn", nlhs, plhs, nrhs, prhs);
}

LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxGetmfcc(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "getmfcc", nlhs, plhs, nrhs, prhs);
}

LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxProbabilitys(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "Probabilitys", nlhs, plhs, nrhs, prhs);
}

LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxCluster_Probability(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                         *prhs[])
{
  return mclFeval(_mcr_inst, "Cluster_Probability", nlhs, plhs, nrhs, prhs);
}

LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxCluster_Covariance(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                        *prhs[])
{
  return mclFeval(_mcr_inst, "Cluster_Covariance", nlhs, plhs, nrhs, prhs);
}

LIB_IncTrain_C_API 
bool MW_CALL_CONV mlxExchange(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "Exchange", nlhs, plhs, nrhs, prhs);
}

LIB_IncTrain_CPP_API 
void MW_CALL_CONV IncrementGMM(const mwArray& speaker, const mwArray& SphName, const 
                               mwArray& maxtrain)
{
  mclcppMlfFeval(_mcr_inst, "IncrementGMM", 0, 0, 3, &speaker, &SphName, &maxtrain);
}

LIB_IncTrain_CPP_API 
void MW_CALL_CONV readspeech(int nargout, mwArray& Wavx1, mwArray& fs, const mwArray& 
                             speechname, const mwArray& SpeakerName, const mwArray& addr)
{
  mclcppMlfFeval(_mcr_inst, "readspeech", nargout, 2, 3, &Wavx1, &fs, &speechname, &SpeakerName, &addr);
}

LIB_IncTrain_CPP_API 
void MW_CALL_CONV enframe(int nargout, mwArray& f, const mwArray& x, const mwArray& win, 
                          const mwArray& inc)
{
  mclcppMlfFeval(_mcr_inst, "enframe", nargout, 1, 3, &f, &x, &win, &inc);
}

LIB_IncTrain_CPP_API 
void MW_CALL_CONV sgn(int nargout, mwArray& output, const mwArray& input)
{
  mclcppMlfFeval(_mcr_inst, "sgn", nargout, 1, 1, &output, &input);
}

LIB_IncTrain_CPP_API 
void MW_CALL_CONV getmfcc(int nargout, mwArray& mfccc, mwArray& FrameSize, mwArray& 
                          framelocation, mwArray& energy, const mwArray& speechname, 
                          const mwArray& SpeakerName, const mwArray& dimension)
{
  mclcppMlfFeval(_mcr_inst, "getmfcc", nargout, 4, 3, &mfccc, &FrameSize, &framelocation, &energy, &speechname, &SpeakerName, &dimension);
}

LIB_IncTrain_CPP_API 
void MW_CALL_CONV Probabilitys(int nargout, mwArray& pro, const mwArray& No_of_Cluster, 
                               const mwArray& No_of_Feature, const mwArray& X, const 
                               mwArray& alpha, const mwArray& Mu, const mwArray& 
                               Variances)
{
  mclcppMlfFeval(_mcr_inst, "Probabilitys", nargout, 1, 6, &pro, &No_of_Cluster, &No_of_Feature, &X, &alpha, &Mu, &Variances);
}

LIB_IncTrain_CPP_API 
void MW_CALL_CONV Cluster_Probability(int nargout, mwArray& PC, mwArray& INDEX, const 
                                      mwArray& Data, const mwArray& Mu)
{
  mclcppMlfFeval(_mcr_inst, "Cluster_Probability", nargout, 2, 2, &PC, &INDEX, &Data, &Mu);
}

LIB_IncTrain_CPP_API 
void MW_CALL_CONV Cluster_Covariance(int nargout, mwArray& COVAR, const mwArray& Data, 
                                     const mwArray& IDX, const mwArray& No_of_Cluster)
{
  mclcppMlfFeval(_mcr_inst, "Cluster_Covariance", nargout, 1, 3, &COVAR, &Data, &IDX, &No_of_Cluster);
}

LIB_IncTrain_CPP_API 
void MW_CALL_CONV Exchange(int nargout, mwArray& b, mwArray& a, const mwArray& a_in1, 
                           const mwArray& b_in1)
{
  mclcppMlfFeval(_mcr_inst, "Exchange", nargout, 2, 2, &b, &a, &a_in1, &b_in1);
}
