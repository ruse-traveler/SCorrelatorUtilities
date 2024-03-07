// ----------------------------------------------------------------------------
// 'TypesLinkDef.h'
// Derek Anderson
// 11.16.2023
//
// LinkDef file for the utilities namespace of the
// sPHENIX Cold QCD Correlator Analysis.
// ----------------------------------------------------------------------------

#include "ClustInfo.h"
#include "CstInfo.h"
#include "JetInfo.h"

#ifdef __CINT__

// base utility classes
#pragma link C++ class ClustInfo+;
#pragma link C++ class CstInfo+;
#pragma link C++ class FlowInfo+;
#pragma link C++ class GenInfo+;
#pragma link C++ class JetInfo+;
#pragma link C++ class ParInfo+;
#pragma link C++ class RecoInfo+;
#pragma link C++ class TrkInfo+;

// stl collections of utility classes
#pragma link C++ class vector<CstInfo>+;
#pragma link C++ class vector<FlowInfo>+;
#pragma link C++ class vector<JetInfo>+;
#pragma link C++ class vector<ParInfo>+;
#pragma link C++ class vector<TrkInfo>+;
#pragma link C++ class vector<vector<CstInfo>>+;
#pragma link C++ class vector<vector<ParInfo>>+;
#pragma link C++ class pair<ParInfo, ParInfo>+;

#endif

// end ------------------------------------------------------------------------

