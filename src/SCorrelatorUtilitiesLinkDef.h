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
#include "JetInfo.h"

#ifdef __CINT__

// base utility classes
#pragma link C++ class ClustInfo+;
#pragma link C++ class CstInfo+;
#pragma link C++ class JetInfo+;

// stl collections of utility classes
#pragma link C++ class vector<CstInfo>+;
#pragma link C++ class vector<JetInfo>+;
#pragma link c++ class vector<vector<CstInfo>>+;

#endif

// end ------------------------------------------------------------------------

