//
// MATLAB Compiler: 6.6 (R2018a)
// Date: Wed Apr 22 22:19:18 2020
// Arguments:
// "-B""macro_default""-W""cpplib:GA,all""-T""link:lib""-d""/Users/terencelau/.n
// utstore/.nutstore/Year_Four_File/[S2] Quantum
// Finance/Project/GA/GA/for_testing""-v""/Users/terencelau/.nutstore/.nutstore/
// Year_Four_File/[S2] Quantum
// Finance/Project/GA/AcrChrom.m""/Users/terencelau/.nutstore/.nutstore/Year_Fou
// r_File/[S2] Quantum
// Finance/Project/GA/CalAveFitness.m""/Users/terencelau/.nutstore/.nutstore/Yea
// r_Four_File/[S2] Quantum
// Finance/Project/GA/CalFitness.m""/Users/terencelau/.nutstore/.nutstore/Year_F
// our_File/[S2] Quantum
// Finance/Project/GA/FindBest.m""/Users/terencelau/.nutstore/.nutstore/Year_Fou
// r_File/[S2] Quantum
// Finance/Project/GA/IfOut.m""/Users/terencelau/.nutstore/.nutstore/Year_Four_F
// ile/[S2] Quantum
// Finance/Project/GA/Initialize.m""/Users/terencelau/.nutstore/.nutstore/Year_F
// our_File/[S2] Quantum
// Finance/Project/GA/MutChrom.m""/Users/terencelau/.nutstore/.nutstore/Year_Fou
// r_File/[S2] Quantum
// Finance/Project/GA/PlotModel.m""/Users/terencelau/.nutstore/.nutstore/Year_Fo
// ur_File/[S2] Quantum Finance/Project/GA/ReplaceWorse.m"
//

#ifndef __GA_h
#define __GA_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_GA_C_API 
#define LIB_GA_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_GA_C_API 
bool MW_CALL_CONV GAInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_GA_C_API 
bool MW_CALL_CONV GAInitialize(void);

extern LIB_GA_C_API 
void MW_CALL_CONV GATerminate(void);

extern LIB_GA_C_API 
void MW_CALL_CONV GAPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_GA_C_API 
bool MW_CALL_CONV mlxAcrChrom(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_GA_C_API 
bool MW_CALL_CONV mlxCalAveFitness(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_GA_C_API 
bool MW_CALL_CONV mlxCalFitness(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_GA_C_API 
bool MW_CALL_CONV mlxFindBest(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_GA_C_API 
bool MW_CALL_CONV mlxIfOut(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_GA_C_API 
bool MW_CALL_CONV mlxInitialize(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_GA_C_API 
bool MW_CALL_CONV mlxMutChrom(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_GA_C_API 
bool MW_CALL_CONV mlxPlotModel(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_GA_C_API 
bool MW_CALL_CONV mlxReplaceWorse(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_GA
#define PUBLIC_GA_CPP_API __declspec(dllexport)
#else
#define PUBLIC_GA_CPP_API __declspec(dllimport)
#endif

#define LIB_GA_CPP_API PUBLIC_GA_CPP_API

#else

#if !defined(LIB_GA_CPP_API)
#if defined(LIB_GA_C_API)
#define LIB_GA_CPP_API LIB_GA_C_API
#else
#define LIB_GA_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_GA_CPP_API void MW_CALL_CONV AcrChrom(int nargout, mwArray& chrom_new, const mwArray& chrom, const mwArray& acr, const mwArray& N, const mwArray& N_chrom);

extern LIB_GA_CPP_API void MW_CALL_CONV CalAveFitness(int nargout, mwArray& fitness_ave, const mwArray& fitness);

extern LIB_GA_CPP_API void MW_CALL_CONV CalFitness(int nargout, mwArray& fitness, const mwArray& chrom, const mwArray& N, const mwArray& N_chrom);

extern LIB_GA_CPP_API void MW_CALL_CONV FindBest(int nargout, mwArray& chrom_best, const mwArray& chrom, const mwArray& fitness, const mwArray& N_chrom);

extern LIB_GA_CPP_API void MW_CALL_CONV IfOut(int nargout, mwArray& c_new, const mwArray& c, const mwArray& range);

extern LIB_GA_CPP_API void MW_CALL_CONV Initialize(int nargout, mwArray& chrom_new, const mwArray& N, const mwArray& N_chrom, const mwArray& chrom_range);

extern LIB_GA_CPP_API void MW_CALL_CONV MutChrom(int nargout, mwArray& chrom_new, const mwArray& chrom, const mwArray& mut, const mwArray& N, const mwArray& N_chrom, const mwArray& chrom_range, const mwArray& t, const mwArray& iter);

extern LIB_GA_CPP_API void MW_CALL_CONV PlotModel(int nargout, mwArray& y, const mwArray& chrom);

extern LIB_GA_CPP_API void MW_CALL_CONV ReplaceWorse(int nargout, mwArray& chrom_new, mwArray& fitness_new, const mwArray& chrom, const mwArray& chrom_best, const mwArray& fitness);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
