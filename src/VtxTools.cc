/// ---------------------------------------------------------------------------
/*! \file   VtxTools.cc
 *  \author Derek Anderson
 *  \date   08.08.2024
 *
 *  Collection of frequent vertex-related methods
 *  utilized in the sPHENIX Cold QCD Energy-Energy
 *  Correlator analysis.
 */
/// ---------------------------------------------------------------------------

#define SCORRELATORUTILITIES_VTXTOOLS_CC

// namespace definition
#include "VtxTools.h"

// make common namespaces implicit
using namespace std;



// vertex methods =============================================================

namespace SColdQcdCorrelatorAnalysis {

  // --------------------------------------------------------------------------
  //! Get displacement relative to a vertex
  // --------------------------------------------------------------------------
  ROOT::Math::XYZVector Tools::GetDisplacement(const ROOT::Math::XYZVector pos, const ROOT::Math::XYZVector vtx) {

    return pos - vtx;

  }  // end 'GetDisplacement(ROOT::Math::XYZVector pos, ROOT::Math::XYZVector)'

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
