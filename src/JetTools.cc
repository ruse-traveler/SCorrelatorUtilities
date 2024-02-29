// ----------------------------------------------------------------------------
// 'JetTools.cc'
// Derek Anderson
// 02.29.2024
//
// Collection of frequent jet-related methods and types
// utilized in the sPHENIX cold QCD Energy-Energy
// Correlator analysis.
// ----------------------------------------------------------------------------

#define JETTOOLS_CC

// analysis utilities
#include "JetTools.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // jet methods ------------------------------------------------------------

  bool SCorrelatorUtilities::IsInAcceptance(const JetInfo& jet, const JetInfo& minimum, const JetInfo& maximum) {

    return ((jet >= minimum) && (jet <= maximum));

  }  // end 'IsInAcceptance(JetInfo&, JetInfo&, JetInfo&)'

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
