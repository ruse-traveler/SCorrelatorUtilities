// ----------------------------------------------------------------------------
// 'EvtTools.cc'
// Derek Anderson
// 02.25.2024
//
// Collection of frequent event-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#define EVTTOOLS_CC

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// c++ utilities
#include <cmath>
#include <limits>
#include <vector>
#include <cassert>
#include <utility>
#include <optional>
// root libraries
#include <Math/Vector3D.h>
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
#include "EvtTools.h"
#include "CalTools.h"
#include "TrkTools.h"
#include "VtxTools.h"
#include "GenTools.h"
#include "Constants.h"
#include "Interfaces.h"

#pragma GCC diagnostic pop



namespace SColdQcdCorrelatorAnalysis {

  // event methods ----------------------------------------------------------

  long SCorrelatorUtilities::GetNumTrks(PHCompositeNode* topNode) {

    // grab size of track map
    SvtxTrackMap* mapTrks = GetTrackMap(topNode);
    return mapTrks -> size();

  }  // end 'GetNumTrks(PHCompositeNode*)'



  long SCorrelatorUtilities::GetNumFinalStatePars(PHCompositeNode* topNode, const vector<int> evtsToGrab, const int subset, optional<float> chargeToGrab) {

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
        if (!IsFinalState((*particle) -> status())) continue;

        // if chargeToGrab is set, select only particle with charge
        const float charge = GetParticleCharge((*particle) -> pdg_id());
        if (chargeToGrab.has_value()) {
          if (charge == chargeToGrab.value()) {
            ++nPar;
          }
        } else {
          switch (subset) {

            // everything
            case Subset::All:
              ++nPar;
              break;

            // all charged
            case Subset::Charged:
              if (charge != 0.) {
                ++nPar;
              }
              break;

            // only neutral
            case Subset::Neutral:
              if (charge == 0.) {
                ++nPar;
              }
              break;

            default:
              ++nPar;
              break;
          }
        }  // end if-else chargeToGrab.has_value()
      }  // end particle loop
    }  // end subevent loop
    return nPar;

  }  // end 'GetNumFinalStatePars(PHCompositeNode*, vector<int>, optional<float>, optional<float> bool)'



  double SCorrelatorUtilities::GetSumTrkMomentum(PHCompositeNode* topNode) {

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



  double SCorrelatorUtilities::GetSumCaloEne(PHCompositeNode* topNode, const string store) {

    // grab clusters
    RawClusterContainer::ConstRange clusters = GetClusters(topNode, store);

    // loop over clusters
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



  double SCorrelatorUtilities::GetSumFinalStateParEne(PHCompositeNode* topNode, const vector<int> evtsToGrab, const int subset, optional<float> chargeToGrab) {

    // loop over subevents
    double eSum = 0.;
    for (const int evtToGrab : evtsToGrab) {

      HepMC::GenEvent* genEvt = GetGenEvent(topNode, evtToGrab);
      for (
        HepMC::GenEvent::particle_const_iterator particle = genEvt -> particles_begin();
        particle != genEvt -> particles_end();
        ++particle
      ) {

        // check if particle is final state
        if (!IsFinalState((*particle) -> status())) continue;

        // if chargeToGrab is set, select only particle with charge
        const float charge = GetParticleCharge((*particle) -> pdg_id());
        const float energy = (*particle) -> momentum().e();
        if (chargeToGrab.has_value()) {
          if (charge == chargeToGrab.value()) {
            eSum += energy;
          }
        } else {
          switch (subset) {

            // everything
            case Subset::All:
              eSum += energy;
              break;

            // all charged
            case Subset::Charged:
              if (charge != 0.) {
                eSum += energy;
              }
              break;

            // only neutral
            case Subset::Neutral:
              if (charge == 0.) {
                eSum += energy;
              }
              break;

            default:
              eSum += energy;
              break;
          }
        }  // end if-else chargeToGrab.has_value()
      }  // end particle loop
    }  // end subevent loop
    return eSum;

  }  // end 'GetSumFinalStateParEne(PHCompositeNode*, vector<int>, int, optional<float>)'



  SCorrelatorUtilities::ParInfo SCorrelatorUtilities::GetPartonInfo(PHCompositeNode* topNode, const int event, const int status) {

    // pick out relevant sub-sevent to grab
    HepMC::GenEvent* genEvt = GetGenEvent(topNode, event);

    // loop over particles
    ParInfo parton;
    for (
      HepMC::GenEvent::particle_const_iterator particle = genEvt -> particles_begin();
      particle != genEvt -> particles_end();
      ++particle
    ) {

      // ignore all non-partons
      if (!IsParton((*particle) -> pdg_id())) continue;

      // set info if parton is desired status
      if (((*particle) -> status()) == status) {
        parton.SetInfo(*particle, event);
      }
    }  // end particle loop
    return parton;

  }  // end 'GetPartonInfo(PHCompositeNode*, int, int)'

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------

