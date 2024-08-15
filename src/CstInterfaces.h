/// ---------------------------------------------------------------------------
/*! \file   CstInterfaces.h
 *  \author Derek Anderson
 *  \date   08.15.2024
 *
 *  Jet constituent-related interfaces.
 */
/// ---------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_CSTINTERFACES_H
#define SCORRELATORUTILITIES_CSTINTERFACES_H

// c++ utilities
#include <cassert>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// PHG4 libraries
#include <g4main/PHG4Particle.h>
// calobase libraries
#include <calobase/RawTower.h>
#include <calobase/TowerInfo.h>
#include <calobase/RawCluster.h>
// trackbase libraries
#include <trackbase_historic/SvtxTrack.h>
// particle flow libraries
#include <particleflowreco/ParticleFlowElement.h>
// analysis utilities
#include "ParInterfaces.h"
#include "TrkInterfaces.h"
#include "TwrInterfaces.h"
#include "FlowInterfaces.h"
#include "ClustInterfaces.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace Interfaces {

    // cst interfaces -------------------------------------------------------

    SvtxTrack*           FindTrack(const int idToFind, PHCompositeNode* topNode);
    ParticleFlowElement* FindFlow(const int idToFind, PHCompositeNode* topNode);
    RawTower*            FindRawTower(const int idToFind, PHCompositeNode* topNode);
    TowerInfo*           FindTowerInfo(const int idToFind, PHCompositeNode* topNode);    
    RawCluster*          FindCluster(const int idToFind, PHCompositeNode* topNode);
    PHG4Particle*        FindParticle(const int idToFind, PHCompositeNode* topNode);

  }  // end Interfaces namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
