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
#include <trackbase_historic/SvtxVertex.h>
#include <trackbase_historic/SvtxTrackMap.h>
#include <trackbase_historic/SvtxVertexMap.h>
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

    // types --------------------------------------------------------------------
    // FIXME some of these should be classes rather than just structs

    struct EvtInfo {

      // data members
      // TODO add energy sums, etc
      int    m_numJets;
      int    m_numTrks;
      double m_vtxX;
      double m_vtxY;
      double m_vtxZ;

      // setter
      void SetInfo(int nJet, int nTrk, double vX, double vY, double vZ) {
        m_numJets = nJet;
        m_numTrks = nTrk;
        m_vtxX    = vX;
        m_vtxY    = vY;
        m_vtxZ    = vZ;
      }  // end 'SetInfo(int, int, double, double, double)'

    };  // end EvtInfo def



    struct JetInfo {

      // data members
      uint32_t m_jetID;
      uint64_t m_numCsts;
      double   m_ene;
      double   m_pt;
      double   m_eta;
      double   m_phi;
      double   m_area;

      // setter
      void SetInfo(uint32_t id, uint64_t nCst, double ene, double pt, double h, double f, double a) {
        m_jetID   = id;
        m_numCsts = nCst;
        m_ene     = ene;
        m_pt      = pt;
        m_eta     = h;
        m_phi     = f;
        m_area    = a;
      } // end 'SetInfo(uint32_t, uint64_t, double, double, double, double, double)'

    };  // end JetInfo def



    struct CstInfo {

      // data members
      int    m_cstID;
      double m_z;
      double m_dr;
      double m_ene;
      double m_jt;
      double m_eta;
      double m_phi;

      // setter
      void SetInfo(int id, int z, double dr, double ene, double jt, double eta, double phi) {
        m_cstID = id;
        m_z     = z;
        m_dr    = dr;
        m_ene   = ene;
        m_jt    = jt;
        m_eta   = eta;
        m_phi   = phi;
      }  // end 'SetInfo(int, int, double, double, double, double, double)'

    };  // end CstInfo def



    // methods ----------------------------------------------------------------

    /* FIXME these probaly should be split off into another file for ease of browsing */

/* TODO uncomment once ready to remove these from SCorrelatorJetTree
    int GetEmbedID(PHCompositeNode* topNode, const int iEvtToGrab) {

      // grab mc event map
      PHHepMCGenEventMap* mapMcEvts = findNode::getClass<PHHepMCGenEventMap>(topNode, "PHHepMCGenEventMap");
      if (!mapMcEvts) {
        cerr << PHWHERE
             << "PANIC: HEPMC event map node is missing!"
             << endl;
        assert(mapMcEvts);
      }

      // grab mc event & return embedding id
      PHHepMCGenEvent* mcEvtStart = mapMcEvts -> get(iEvtToGrab);
      if (!mcEvtStart) {
        cerr << PHWHERE
             << "PANIC: Couldn't grab start of mc events!"
             << endl;
        assert(mcEvtStart);
      }
      return mcEvtStart -> get_embedding_id();

    }  // end 'GetEmbedID(PHCompositeNode*, int)'



    SvtxTrackMap* GetTrackMap(PHCompositeNode* topNode) {

      // grab track map
      SvtxTrackMap* mapTrks = findNode::getClass<SvtxTrackMap>(topNode, "SvtxTrackMap");
      if (!mapTrks) {
        cerr << PHWHERE
             << "PANIC: SvtxTrackMap node is missing!"
             << endl;
        assert(mapTrks);
      }
      return mapTrks;

    }  // end 'GetTrackMap(PHCompositeNode*)'



    GlobalVertexMap* GetVertexMap(PHCompositeNode* topNode) {

      // get vertex map
      GlobalVertexMap* mapVtx = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");

      // check if good
      const bool isVtxMapGood = (mapVtx && !(mapVtx -> empty()));
      if (!isVtxMapGood) {
        cerr << PHWHERE
             << "PANIC: GlobalVertexMap node is missing or empty!\n"
             << "       Please turn on the do_global flag in the main macro in order to reconstruct the global vertex!"
             << endl;
        assert(isVtxMapGood);
      }
      return mapVtx;

    }  // end 'GetVertexMap(PHCompositeNode*)'



    GlobalVertex* GetGlobalVertex(PHCompositeNode* topNode, const int iVtxToGrab) {

      // get vertex map
      GlobalVertexMap* mapVtx = GetVertexMap(topNode);

      // get specified vertex
      GlobalVertex* vtx = NULL;
      if (iVtxToGrab < 0) {
        vtx = mapVtx -> begin() -> second;
      } else {
        vtx = mapVtx -> get(iVtxToGrab);
      }

      // check if good
      if (!vtx) {
        cerr << PHWHERE
             << "PANIC: no vertex!"
             << endl;
        assert(vtx);
      }
      return vtx;

    }  // end 'GetGlobalVertex(PHCompositeNode*, int)'
  


    HepMC::GenEvent* GetMcEvent(PHCompositeNode* topNode, const int iEvtToGrab) {

      // grab mc event map
      PHHepMCGenEventMap* mapMcEvts = findNode::getClass<PHHepMCGenEventMap>(topNode, "PHHepMCGenEventMap");
      if (!mapMcEvts) {
        cerr << PHWHERE
             << "PANIC: HEPMC event map node is missing!"
             << endl;
        assert(mapMcEvts);
      }

      // grab mc event & check if good
      PHHepMCGenEvent* mcEvtStart = mapMcEvts -> get(iEvtToGrab);
      if (!mcEvtStart) {
        cerr << PHWHERE
             << "PANIC: Couldn't grab start of mc events!"
             << endl;
        assert(mcEvtStart);
      }

      HepMC::GenEvent* mcEvt = mcEvtStart -> getEvent();
      if (!mcEvt) {
        cerr << PHWHERE
             << "PANIC: Couldn't grab HepMC event!"
             << endl;
        assert(mcEvt);
      }
      return mcEvt;

    }  // end 'GetMcEvent(PHCompositeNode*, int)'



    RawClusterContainer* GetClusterStore(PHCompositeNode* topNode, const TString sNodeName) {

      // grab clusters
      RawClusterContainer *clustStore = findNode::getClass<RawClusterContainer>(topNode, sNodeName.Data());
      if (!clustStore) {
        cout << PHWHERE
             << "PANIC: " << sNodeName.Data() << " node is missing!"
             << endl;
        assert(clustStore);
      }
      return clustStore;

    }  // end 'GetClusterStore(PHCompositeNode*, TString)'



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
*/

  }  // end SCorrelatorUtilities namespace

}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
