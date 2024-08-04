/// ---------------------------------------------------------------------------
/*! \file   TwrTools.h
 *  \author Derek Anderson
 *  \date   08.04.2024
 *
 *  Collection of frequent tower-related methods utilized in
 *  the sPHENIX Cold QCD Energy-Energy Correlator analysis.
 */
/// ---------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_TWRTOOLS_H
#define SCORRELATORUTILITIES_TWRTOOLS_H

// c++ utilities
#include <cmath>
// root libraries
#include <Math/Vector3D.h>
#include <Math/Vector4D.h>
// analysis utilities
#include "Constants.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace Tools {

    // tower methods ----------------------------------------------------------

    ROOT::Math::PxPyPzEVector GetTowerMomentum(const double energy, const ROOT::Math::XYZVector pos, const ROOT::Math::XYZVector vtx);

  }  // end Tools namespace
}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
