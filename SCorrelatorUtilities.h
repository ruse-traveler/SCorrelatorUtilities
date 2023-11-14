// ----------------------------------------------------------------------------
// 'SCorrelatorUtilities.h'
// Derek Anderson
// 09.21.2023
//
// A namespace to collect various useful structs, methods, etc.
// for the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_H
#define SCORRELATORUTILITIES_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// f4a include
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <fun4all/Fun4AllHistoManager.h>
// phool includes
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// main geant4 includes
#include <g4main/PHG4Hit.h>
#include <g4main/PHG4Particle.h>
#include <g4main/PHG4TruthInfoContainer.h>
// jet includes
#include <jetbase/Jet.h>
#include <jetbase/JetMap.h>
#include <jetbase/JetMapv1.h>
#include <jetbase/FastJetAlgo.h>
// track evaluator includes
#include <g4eval/SvtxTrackEval.h>
#include <g4eval/SvtxEvalStack.h>
// vtx includes
#include <globalvertex/GlobalVertex.h>
#include <globalvertex/GlobalVertexMap.h>
// tracking includes
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
#include <trackbase_historic/TrackAnalysisUtils.h>
// calo includes
#include <calobase/RawCluster.h>
#include <calobase/RawClusterUtility.h>
#include <calobase/RawClusterContainer.h>
#include <calobase/RawTower.h>
#include <calobase/RawTowerGeom.h>
#include <calobase/RawTowerContainer.h>
#include <calobase/RawTowerGeomContainer.h>
#include <calotrigger/CaloTriggerInfo.h>
// particle flow includes
#include <particleflowreco/ParticleFlowElement.h>
#include <particleflowreco/ParticleFlowElementContainer.h>
// hepmc includes
#include <HepMC/GenEvent.h>
#include <HepMC/GenVertex.h>
#include <HepMC/GenParticle.h>
#include <phhepmc/PHHepMCGenEvent.h>
#include <phhepmc/PHHepMCGenEventMap.h>

#pragma GCC diagnostic pop

#pragma once

using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // constants, enums, etc. -------------------------------------------------

    namespace {

      // subsystem indices
      enum class Subsys {Mvtx, Intt, Tpc, EMCal, IHCal, OHCal};

      // tracking-related constants
      const uint16_t NMvtxLayer = 3;
      const uint16_t NInttLayer = 8;
      const uint16_t NTpcLayer  = 48;
      const uint16_t NTpcSector = 12;

      // pion mass in GeV/c^2
      const double MassPion = 0.140;

    }  // end constants

    // methods ----------------------------------------------------------------

    /* FIXME these probaly should be split off into another file for ease of browsing */

    ParticleFlowElementContainer* GetFlowStore(PHCompositeNode* topNode) {

      // declare pf objects
      ParticleFlowElementContainer* flowStore = findNode::getClass<ParticleFlowElementContainer>(topNode, "ParticleFlowElements");
      if (!flowStore) {
        cerr << PHWHERE
             << "PANIC: Couldn't grab particle flow container!"
             << endl;
        assert(flowStore);
      }
      return flowStore;

    }  // end 'GetFlowStore(PHCompositeNode*)'

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
