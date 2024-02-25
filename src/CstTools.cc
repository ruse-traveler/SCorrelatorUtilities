// ----------------------------------------------------------------------------
// 'CstTools.cc'
// Derek Anderson
// 02.24.2024
//
// Collection of frequent constituent-related methods and
// types utilized in the sPHENIX cold QCD Energy-Energy
// Correlator analysis.
// ----------------------------------------------------------------------------

#define CSTTOOLS_CC

// cst utility definition
#include "CstTools.h"



namespace SColdQcdCorrelatorAnalysis {

  // constituent methods ----------------------------------------------------

  bool SCorrelatorUtilities::IsInAcceptance(const CstInfo& cst, const CstInfo& minimum, const CstInfo& maximum) {

    return ((cst >= minimum) && (cst <= maximum));

  }  // end 'IsInAcceptance(CstInfo&, CstInfo&, CstInfo&)'

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
