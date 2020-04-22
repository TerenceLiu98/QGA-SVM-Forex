/*
 * MATLAB Compiler: 6.6 (R2018a)
 * Date: Wed Apr 22 22:11:18 2020
 * Arguments:
 * "-B""macro_default""-W""lib:GA""-T""link:lib""-d""/Users/terencelau/.nutstore
 * /.nutstore/Year_Four_File/[S2] Quantum
 * Finance/Project/GA/GA/for_testing""-v""/Users/terencelau/.nutstore/.nutstore/
 * Year_Four_File/[S2] Quantum
 * Finance/Project/GA/AcrChrom.m""/Users/terencelau/.nutstore/.nutstore/Year_Fou
 * r_File/[S2] Quantum
 * Finance/Project/GA/CalAveFitness.m""/Users/terencelau/.nutstore/.nutstore/Yea
 * r_Four_File/[S2] Quantum
 * Finance/Project/GA/CalFitness.m""/Users/terencelau/.nutstore/.nutstore/Year_F
 * our_File/[S2] Quantum
 * Finance/Project/GA/FindBest.m""/Users/terencelau/.nutstore/.nutstore/Year_Fou
 * r_File/[S2] Quantum
 * Finance/Project/GA/IfOut.m""/Users/terencelau/.nutstore/.nutstore/Year_Four_F
 * ile/[S2] Quantum
 * Finance/Project/GA/Initialize.m""/Users/terencelau/.nutstore/.nutstore/Year_F
 * our_File/[S2] Quantum
 * Finance/Project/GA/MutChrom.m""/Users/terencelau/.nutstore/.nutstore/Year_Fou
 * r_File/[S2] Quantum
 * Finance/Project/GA/PlotModel.m""/Users/terencelau/.nutstore/.nutstore/Year_Fo
 * ur_File/[S2] Quantum Finance/Project/GA/ReplaceWorse.m"
 */

#include <stdio.h>
#define EXPORTING_GA 1
#include "GA.h"

static HMCRINSTANCE _mcr_inst = NULL;

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
#ifndef LIB_GA_C_API
#define LIB_GA_C_API /* No special import/export declaration */
#endif

LIB_GA_C_API 
bool MW_CALL_CONV GAInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
    if (_mcr_inst != NULL)
        return true;
    if (!mclmcrInitialize())
        return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream((void *)(GAInitializeWithHandlers));
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(&_mcr_inst,
                                                             error_handler, 
                                                             print_handler,
                                                             ctfStream);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
    return true;
}

LIB_GA_C_API 
bool MW_CALL_CONV GAInitialize(void)
{
    return GAInitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_GA_C_API 
void MW_CALL_CONV GATerminate(void)
{
    if (_mcr_inst != NULL)
        mclTerminateInstance(&_mcr_inst);
}

LIB_GA_C_API 
void MW_CALL_CONV GAPrintStackTrace(void) 
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


LIB_GA_C_API 
bool MW_CALL_CONV mlxAcrChrom(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "AcrChrom", nlhs, plhs, nrhs, prhs);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlxCalAveFitness(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "CalAveFitness", nlhs, plhs, nrhs, prhs);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlxCalFitness(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "CalFitness", nlhs, plhs, nrhs, prhs);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlxFindBest(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "FindBest", nlhs, plhs, nrhs, prhs);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlxIfOut(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "IfOut", nlhs, plhs, nrhs, prhs);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlxInitialize(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "Initialize", nlhs, plhs, nrhs, prhs);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlxMutChrom(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "MutChrom", nlhs, plhs, nrhs, prhs);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlxPlotModel(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "PlotModel", nlhs, plhs, nrhs, prhs);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlxReplaceWorse(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "ReplaceWorse", nlhs, plhs, nrhs, prhs);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlfAcrChrom(int nargout, mxArray** chrom_new, mxArray* chrom, mxArray* 
                              acr, mxArray* N, mxArray* N_chrom)
{
    return mclMlfFeval(_mcr_inst, "AcrChrom", nargout, 1, 4, chrom_new, chrom, acr, N, N_chrom);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlfCalAveFitness(int nargout, mxArray** fitness_ave, mxArray* fitness)
{
    return mclMlfFeval(_mcr_inst, "CalAveFitness", nargout, 1, 1, fitness_ave, fitness);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlfCalFitness(int nargout, mxArray** fitness, mxArray* chrom, mxArray* 
                                N, mxArray* N_chrom)
{
    return mclMlfFeval(_mcr_inst, "CalFitness", nargout, 1, 3, fitness, chrom, N, N_chrom);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlfFindBest(int nargout, mxArray** chrom_best, mxArray* chrom, mxArray* 
                              fitness, mxArray* N_chrom)
{
    return mclMlfFeval(_mcr_inst, "FindBest", nargout, 1, 3, chrom_best, chrom, fitness, N_chrom);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlfIfOut(int nargout, mxArray** c_new, mxArray* c, mxArray* range)
{
    return mclMlfFeval(_mcr_inst, "IfOut", nargout, 1, 2, c_new, c, range);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlfInitialize(int nargout, mxArray** chrom_new, mxArray* N, mxArray* 
                                N_chrom, mxArray* chrom_range)
{
    return mclMlfFeval(_mcr_inst, "Initialize", nargout, 1, 3, chrom_new, N, N_chrom, chrom_range);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlfMutChrom(int nargout, mxArray** chrom_new, mxArray* chrom, mxArray* 
                              mut, mxArray* N, mxArray* N_chrom, mxArray* chrom_range, 
                              mxArray* t, mxArray* iter)
{
    return mclMlfFeval(_mcr_inst, "MutChrom", nargout, 1, 7, chrom_new, chrom, mut, N, N_chrom, chrom_range, t, iter);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlfPlotModel(int nargout, mxArray** y, mxArray* chrom)
{
    return mclMlfFeval(_mcr_inst, "PlotModel", nargout, 1, 1, y, chrom);
}

LIB_GA_C_API 
bool MW_CALL_CONV mlfReplaceWorse(int nargout, mxArray** chrom_new, mxArray** 
                                  fitness_new, mxArray* chrom, mxArray* chrom_best, 
                                  mxArray* fitness)
{
    return mclMlfFeval(_mcr_inst, "ReplaceWorse", nargout, 2, 3, chrom_new, fitness_new, chrom, chrom_best, fitness);
}
