/// ---------------------------------------------------------------------------
/*! \file   CstInterfaces.cc
 *  \author Derek Anderson
 *  \date   08.15.2024
 *
 *  Jet constituent-related interfaces.
 */
/// ---------------------------------------------------------------------------

#define SCORRELATORUTILITIES_CSTINTERFACES_CC

// namespace definition 
#include "CstInterfaces.h"

// make common namespaces implicit
using namespace std;
using namespace findNode;



// cst interfaces =============================================================

namespace SColdQcdCorrelatorAnalysis {

  // --------------------------------------------------------------------------
  //! Find SvtxTrack based on provided ID
  // --------------------------------------------------------------------------
  SvtxTrack* Interfaces::FindTrack(const int idToFind, PHCompositeNode* topNode) {

    /* TODO implement */
    return nullptr;

  }  // end 'FindTrack(int, PHCompositeNode*)'



  // --------------------------------------------------------------------------
  //! Find PFO based on provided ID
  // --------------------------------------------------------------------------
  ParticleFlowElement* Interfaces::FindFlow(const int idToFind, PHCompositeNode* topNode) {

    /* TODO implement */
    return nullptr;

  }  // end 'FindFlow(int, PHCompositeNode*)'



  // --------------------------------------------------------------------------
  //! Find RawTower based on provided ID
  // --------------------------------------------------------------------------
  RawTower* Interfaces::FindRawTower(const int idToFind, PHCompositeNode* topNode) {

    /* TODO implement */
    return nullptr;

  }  // end 'FindRawTower(int, PHCompositeNode*)'



  // --------------------------------------------------------------------------
  //! Find TowerInfo based on provided ID
  // --------------------------------------------------------------------------
  TowerInfo* Interfaces::FindTowerInfo(const int idToFind, PHCompositeNode* topNode) {

    /* TODO implement */
    return nullptr;

  }  // end 'FindTowerInfo(int, PHCompositeNode*)'



  // --------------------------------------------------------------------------
  //! Find RawCluster based on provided ID
  // --------------------------------------------------------------------------
  RawCluster* Interfaces::FindCluster(const int idToFind, PHCompositeNode* topNode) {

    /* TODO implement */
    return nullptr;

  }  // end 'FindCluster(int, PHCompositeNode*)'



  // --------------------------------------------------------------------------
  //! Find PHG4Particle based on provided ID
  // --------------------------------------------------------------------------
  PHG4Particle* Interfaces::FindParticle(const int idToFind, PHCompositeNode* topNode) {

    /* TODO implement */
    return nullptr;

  }  // end 'FindParticle(int, PHCompositeNode*)'

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
