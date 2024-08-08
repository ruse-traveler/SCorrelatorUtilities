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
#include <utility>
// root libraries
#include <Math/Vector3D.h>
#include <Math/Vector4D.h>
// phool libraries
#include <phool/PHCompositeNode.h>
// calobase libraries
#include <calobase/TowerInfo.h>
#include <calobase/RawTowerDefs.h>
#include <calobase/TowerInfoContainer.h>
#include <calobase/RawTowerGeomContainer.h>
// analysis utilities
#include "VtxTools.h"
#include "Constants.h"
#include "Interfaces.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace Tools {

    // tower methods ----------------------------------------------------------

    int                         GetTowerStatus(TowerInfo* tower);
    tuple<int, int, int>        GetTowerIndices(const int channel, const int subsys, PHCompositeNode* topNode);
    ROOT::Math::XYZVector       GetTowerPositionXYZ();
    ROOT::Math::RhoEtaPhiVector GetTowerPositionRhoEtaPhi();
    ROOT::Math::PxPyPzEVector   GetTowerMomentum(const double energy, const ROOT::Math::XYZVector pos, const ROOT::Math::XYZVector vtx);

  }  // end Tools namespace
}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
