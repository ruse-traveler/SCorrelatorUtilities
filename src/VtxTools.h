/// ---------------------------------------------------------------------------
/*! \file   VtxTools.h
 *  \author Derek Anderson
 *  \date   08.08.2024
 *
 *  Collection of frequent vertex-related methods
 *  utilized in the sPHENIX Cold QCD Energy-Energy
 *  Correlator analysis.
 */
/// ---------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_VTXTOOLS_H
#define SCORRELATORUTILITIES_VTXTOOLS_H

// c++ utilities
#include <cmath>
// root libraries
#include <Math/Vector3D.h>

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace Tools {

    // vertex methods ---------------------------------------------------------

    ROOT::Math::XYZVector GetDisplacement(const ROOT::Math::XYZVector pos, const ROOT::Math::XYZVector vtx);

  }  // end Tools namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
