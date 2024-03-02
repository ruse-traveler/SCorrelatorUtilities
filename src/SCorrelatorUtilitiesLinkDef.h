// ----------------------------------------------------------------------------
// 'SCorrelatorUtiltiesLinkDef.h'
// Derek Anderson
// 11.16.2023
//
// LinkDef file for the utilities namespace of the
// sPHENIX Cold QCD Correlator Analysis.
// ----------------------------------------------------------------------------

#include "ClustInfo.h"
#include "EvtTools.h"
#include "FlowTools.h"
#include "GenTools.h"
#include "JetTools.h"
#include "TrkTools.h"

#ifdef __CINT__

// base utility structs
#pragma link C++ class ClustInfo+;
#pragma link C++ struct CstInfo-!;
#pragma link C++ struct FlowInfo-!;
#pragma link C++ struct GenInfo-!;
#pragma link C++ struct JetInfo-!;
#pragma link C++ struct ParInfo-!;
#pragma link C++ struct RecoInfo-!;
#pragma link C++ struct TrkInfo-!;

#endif

// end ------------------------------------------------------------------------

