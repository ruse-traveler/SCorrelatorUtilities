// ----------------------------------------------------------------------------
// 'SCorrelatorUtiltiesLinkDef.h'
// Derek Anderson
// 11.16.2023
//
// LinkDef file for the utilities namespace of the
// sPHENIX Cold QCD Correlator Analysis.
// ----------------------------------------------------------------------------

#include "ClustInfo.h"
#include "CstInfo.h"
#include "EvtTools.h"
#include "FlowTools.h"
#include "GenTools.h"
#include "JetTools.h"
#include "TrkTools.h"

#ifdef __CINT__

// base utility classes
#pragma link C++ class ClustInfo+;
#pragma link C++ class CstInfo+;
#pragma link C++ struct FlowInfo-!;
#pragma link C++ struct GenInfo-!;
#pragma link C++ struct JetInfo-!;
#pragma link C++ struct ParInfo-!;
#pragma link C++ struct RecoInfo-!;
#pragma link C++ struct TrkInfo-!;

// stl collections of utility classes
#pragma link C++ class vector<CstInfo>+;
#pragma link c++ class vector<vector<CstInfo>>+;


#endif

// end ------------------------------------------------------------------------

