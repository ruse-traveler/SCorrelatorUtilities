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
// vertex libraries
#include <globalvertex/GlobalVertex.h>
#include <globalvertex/GlobalVertexMap.h>
// analysis utilities
#include "Constants.h"
#include "CalTools.h"
#include "TrkTools.h"
#include "VtxTools.h"
#include "GenTools.h"

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // EvtInfo definition -----------------------------------------------------

    struct EvtInfo {

      // reco data members
      int    nTrks     = -1;
      int    nRecJets  = -1;
      bool   isSimEvt  = false;
      double eSumEMCal = -999.;
      double eSumIHCal = -999.;
      double eSumOHCal = -999.;

      void SetRecInfo(PHCompositeNode* topNode) {
        nTrks     = GetNumTrks(topNode);
        eSumEMCal = GetSumCaloEne(topNode, "CLUSTER_CEMC");
        eSumIHCal = GetSumCaloEne(topNode, "CLUSTER_HCALIN");
        eSumOHCal = GetSumCaloEne(topNode, "CLUSTER_HCALOUT");
        return;
      }  // end 'SetRecoInfo(PHCompositeNode*)'

      void SetGenInfo(PHCompositeNode* topNode) {
        /* will go here */
        return; 
      }  // end 'SetGenInfo(PHCompositeNode*)'

      void SetInfo(PHCompositeNode* topNode, const bool sim) {
        isSimEvt = sim;
        if (isSimEvt) {
          SetGenInfo(topNode);
        }
        SetRecInfo(topNode);
        return;
      }  // end 'SetInfo(PHCompositeNode*)'

      void Reset() {
        /* will go here */
        return;
      }  // end 'Reset()'

      // default ctor/dtor
      EvtInfo()  {};
      ~EvtInfo() {};

      // ctor accepting PHCompositeNode* &
      EvtInfo(PHCompositeNode* topNode, const bool sim) {
        SetInfo(topNode, sim);
      };

    };  // end EvtInfo def



    // event methods ----------------------------------------------------------

    long GetNumTrks(PHCompositeNode* topNode) {

      // loop over tracks
      SvtxTrackMap* mapTrks = GetTrackMap(topNode);
      return mapTrks.size();

    }  // end 'GetNumTrks(PHCompositeNode*)'



    long GetNumFinalStatePars(PHCompositeNode* topNode, vector<int> evtsToGrab, optional<float> charge) {

      // loop over subevents
      long nPar = 0;
      for (const int evtToGrab : evtsToGrab) {

        // loop over particles
        HepMC::GenEvent* mcEvt = GetGenEvent(topNode, evtToGrab);
        for (
          HepMC::GenEvent::particle_const_iterator particle = mcEvt -> particles_begin();
          particle != mcEvt -> particles_end();
          ++particle
        ) {

          // check if particle is final state
          if (!IsFinalState(*particle -> status())) continue;

          // if charge provided, count only particles with charge
          if (charge.has_value()) {
            if (GetParticleCharge(*particle -> pid()) == charge.value()) {
              ++nPar;
            }
          } else {
            ++nPar;
          }
        }  // end particle loop
      }  // end subevent loop
      return nPar;

    }  // end 'GetNumFinalStatePars(PHCompositeNode*, vector<int>, optional<float>)'




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

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
