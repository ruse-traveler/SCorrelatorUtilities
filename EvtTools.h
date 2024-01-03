// ----------------------------------------------------------------------------
// 'EvtTools.h'
// Derek Anderson
// 10.30.2023
//
// Collection of frequent event-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once

// c++ utilities
#include <vector>
#include <cassert>
#include <utility>
#include <optional>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// tracking includes
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
// calo includes
#include <calobase/RawCluster.h>
#include <calobase/RawClusterUtility.h>
#include <calobase/RawClusterContainer.h>
// hepmc includes
#include <HepMC/GenEvent.h>
#include <HepMC/GenVertex.h>
#include <HepMC/GenParticle.h>
#include <phhepmc/PHHepMCGenEvent.h>
#include <phhepmc/PHHepMCGenEventMap.h>
// vertex libraries
#include <globalvertex/GlobalVertex.h>
#include <globalvertex/GlobalVertexMap.h>
// analysis utilities
#include "Constants.h"
#include "Interfaces.h"
#include "CalTools.h"
#include "TrkTools.h"
#include "VtxTools.h"
#include "GenTools.h"

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // RecoInfo definition ----------------------------------------------------

    struct RecoInfo {

      // data members
      int    nTrks     = -1;
      double pSumTrks  = -999.;
      double eSumEMCal = -999.;
      double eSumIHCal = -999.;
      double eSumOHCal = -999.;
      double vtxX      = -999.;
      double vtxY      = -999.;
      double vtxZ      = -999.;

      void SetInfo(PHCompositeNode* topNode) {
        nTrks     = GetNumTrks(topNode);
        pSumTrks  = GetSumTrkMomentum(topNode);
        eSumEMCal = GetSumCaloEne(topNode, "CLUSTER_CEMC");
        eSumIHCal = GetSumCaloEne(topNode, "CLUSTER_HCALIN");
        eSumOHCal = GetSumCaloEne(topNode, "CLUSTER_HCALOUT");
        return;
      }  // end 'SetInfo(PHCompositeNode*)'

      void Reset() {
        nTrks     = -1;
        pSumTrks  = -999.;
        eSumEMCal = -999.;
        eSumIHCal = -999.;
        eSumOHCal = -999.;
        vtxX      = -999.;
        vtxY      = -999.;
        vtxZ      = -999.;
        return;
      }  // end 'Reset()'

      static vector<string> GetListOfMembers() {
        vector<string> members = {
          "nTrks",
          "pSumTrks",
          "eSumEMCal",
          "eSumIHCal",
          "eSumOHCal",
          "vtxX",
          "vtxY",
          "vtxZ"
        };
        return members;
      }  // end 'GetListOfMembers()'

      // default ctor/dtor
      RecoInfo()  {};
      ~RecoInfo() {};

      // ctor accepting PHCompositeNode*
      RecoInfo(PHCompositeNode* topNode) {
        SetInfo(topNode);
      };

    };  // end RecoInfo definition



    // GenInfo definition ------------------------------------------------------

    struct GenInfo {

      // atomic data members
      int    nChrgPar = -1;
      int    nNeuPar  = -1;
      double eSumChrg = -999.;
      double eSumNeu  = -999.;
      double vtxX     = -999.;
      double vtxY     = -999.;
      double vtxZ     = -999.;

      // hard scatter products
      pair<ParInfo, ParInfo> partons;

      void SetInfo(PHCompositeNode* topNode, vector<int> evtsToGrab) {
        nChrgPar = GetNumFinalStatePars(topNode, evtsToGrab, 1., true);
        nNeuPar  = GetNumFinalStatePars(topNode, evtsToGrab, 0.);
        eSumChrg = GetSumFinalStateParEne(topNode, evtsToGrab, 1., true);
        eSumNeu  = GetSumFinalStateParEne(topNode, evtsToGrab, 0.);
      }  // end 'SetInfo(PHCompositeNode*, vector<int>)'

      // default ctor/dtor
      GenInfo()  {};
      ~GenInfo() {};

      // ctor accepting PHCompositeNode* and list of subevents
      GenInfo(PHCompositeNode* topNode, vector<int> evtsToGrab) {
        SetInfo(topNode, evtsToGrab);
      };
    };  // end GenInfo definition



    // EvtInfo definition -----------------------------------------------------

    struct EvtInfo {

      // data members
      RecoInfo reco;
      GenInfo  gen;
      bool     isSimEvt = false;

      void SetInfo(PHCompositeNode* topNode, const bool sim, optional<vector<int>> evtsToGrab) {
        isSimEvt = sim;
        if (isSimEvt) {
          gen.SetInfo(topNode, evtsToGrab.value());
        }
        reco.SetInfo(topNode);
        return;
      }  // end 'SetInfo(PHCompositeNode*)'

      void Reset() {
        reco.Reset();
        gen.Reset();
        isSimEvt = false;
        return;
      }  // end 'Reset()'

      static vector<string> GetListOfMembers() {
        vector<string> members = reco.GetListOfMembers();
        if (isSimEvt) {
          AddLeavesToVector<GenInfo>(members);
        }
        return members;
      }  // end 'GetListOfMembers()'

      // default ctor/dtor
      EvtInfo()  {};
      ~EvtInfo() {};

      // ctor accepting PHCompositeNode* & bool
      EvtInfo(PHCompositeNode* topNode, optional<bool> sim, optional<vector<int>> evtsToGrab) {
        if (sim.has_value() {
          SetInfo(topNode, sim.value(), evtsToGrab.value());
        } else {
          SetInfo(topNode, false);
        }
      };

    };  // end EvtInfo def



    // event methods ----------------------------------------------------------

    long GetNumTrks(PHCompositeNode* topNode) {

      // grab size of track map
      SvtxTrackMap* mapTrks = GetTrackMap(topNode);
      return mapTrks.size();

    }  // end 'GetNumTrks(PHCompositeNode*)'



    long GetNumFinalStatePars(PHCompositeNode* topNode, vector<int> evtsToGrab, optional<float> charge, optional<bool> doAllCharge) {

      // loop over subevents
      long nPar = 0;
      for (const int evtToGrab : evtsToGrab) {

        // loop over particles
        HepMC::GenEvent* genEvt = GetGenEvent(topNode, evtToGrab);
        for (
          HepMC::GenEvent::particle_const_iterator particle = genEvt -> particles_begin();
          particle != genEvt -> particles_end();
          ++particle
        ) {

          // check if particle is final state
          if (!IsFinalState(*particle -> status())) continue;

          // if doAllCharge flag is set and true, count all charged particles
          //   else if charge provided, count only particles with matching charge
          //   otherwise count all final state particles
          if (doAllCharge.has_value() && doAllCharge.value()) {
            if (GetParticleCharge(*particle -> pid()) != 0.) {
              ++nPar;
            }
          } else if (charge.has_value()) {
            if (GetParticleCharge(*particle -> pid()) == charge.value()) {
              ++nPar;
            }
          } else {
            ++nPar;
          }
        }  // end particle loop
      }  // end subevent loop
      return nPar;

    }  // end 'GetNumFinalStatePars(PHCompositeNode*, vector<int>, optional<float>, optional<float> bool)'



    double GetSumTrkMomentum(PHCompositeNode* topNode) {

      // grab track map
      SvtxTrackMap* mapTrks = GetTrackMap(topNode);

      // loop over tracks
      double pSum = 0.;
      for (
        SvtxTrackMap::Iter itTrk = mapTrks -> begin();
        itTrk != mapTrks -> end();
        ++itTrk
      ) {

        // grab track
        SvtxTrack* track = itTrk -> second;
        if (!track) continue;

        // momentum to sum
        const double pTrk = std::hypot(track -> get_px(), track -> get_py(), track -> get_pz());
        pSum += pTrk;
      }
      return pSum;

    }  // end 'GetSumTrkMomentum(PHCompositeNode*)'



    double GetSumCaloEne(PHCompositeNode* topNode, const string store) {

      // grab clusters
      RawClusterContainer::ConstRange clusters = GetClusters(topNode, store);

      // loop over emcal clusters
      double eSum = 0.;
      for (
        RawClusterContainer::ConstIterator itClust = clusters.first;
        itClust != clusters.second;
        itClust++
      ) {

        // grab cluster and increment sum
        const RawCluster* cluster = itClust -> second;
        if (!cluster) {
          continue;
        } else {
          eSum += cluster -> get_energy();
        }
      }  // end cluster loop
      return eSum;

    }  // end 'GetSumCaloEne(PHCompositeNode*, string)'



    double GetSumFinalStateParEne(PHCompositeNode* topNode, vector<int> evtsToGrab, optional<float> charge, optional<bool> doAllCharge) {

      // loop over subevents
      double eSum = 0.;
      for (const int evtToGrab : evtsToGrab) {

        HepMC::GenEvent* genEvt = GetMcEvent(topNode, evtToGrab);
        for (
          HepMC::GenEvent::particle_const_iterator particle = genEvt -> particles_begin();
          particle != genEvt -> particles_end();
          ++particle
        ) {

          // check if particle is final state
          if (!IsFinalState(*particle -> status()) continue;

          // if doAllCharge flag is set and true, count all charged particles
          //   else if charge provided, count only particles with matching charge
          //   otherwise count all final state particles
          if (doAllCharge.has_value() && doAllCharge.value()) {
            if (GetParticleCharge(*particle -> pid()) != 0.) {
              eSum += *particle -> momentum().e();
            }
          } else if (charge.has_value()) {
            if (GetParticleCharge(*particle -> pid()) == charge.value()) {
              eSum += *particle -> momentum().e();
            }
          } else {
            eSum += *particle -> momentum().e();
          }

        }  // end particle loop
      }  // end subevent loop
      return eSum;

    }  // end 'GetSumFinalStateParEne(PHCompositeNode*, vector<int>, optional<float>, optional<bool>)'



    ParInfo GetPartonInfo(PHCompositeNode* topNode, const int event const int status) {

      // pick out relevant sub-sevent to grab
      HepMC::GenEvent* genEvt = GetMcEvent(topNode, event);

      // loop over particles
      ParInfo parton;
      for (
        HepMC::GenEvent::particle_const_iterator particle = genEvt -> particles_begin();
        particle != mcEvt -> particles_end();
        ++particle
      ) {

        // ignore all non-partons
        if (!IsParton(*particle -> pid())) continue;

        // set info if parton is desired status
        if ((*particle -> status()) == status) {
          parton.SetInfo(*particle);
        }
      }  // end particle loop
      return parton;

    }  // end 'GetPartonInfo(PHCompositeNode*, int, int)'

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
