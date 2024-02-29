// ----------------------------------------------------------------------------
// 'GenTools.cc'
// Derek Anderson
// 02.29.2024
//
// Collection of frequent generator/MC-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#define GENTOOLS_CC

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// c++ utilities
#include <cmath>
#include <limits>
#include <string>
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
// PHG4 libraries
#include <g4main/PHG4Particle.h>
#include <g4main/PHG4TruthInfoContainer.h>
// hepmc libraries
#include <HepMC/GenEvent.h>
#include <HepMC/GenVertex.h>
#include <HepMC/GenParticle.h>
#include <phhepmc/PHHepMCGenEvent.h>
#include <phhepmc/PHHepMCGenEventMap.h>
// analysis utilities
#include "GenTools.h"
#include "Constants.h"

#pragma GCC diagnostic pop

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {

  // generator/mc methods ---------------------------------------------------

  PHG4TruthInfoContainer* SCorrelatorUtilities::GetTruthContainer(PHCompositeNode* topNode) {

    PHG4TruthInfoContainer* container = getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");
    if (!container) {
      cerr << PHWHERE
           << "PANIC: G4 truth info container node is missing!"
           << endl;
      assert(container);
    }
    return container;

  }  // end 'GetTruthContainer(PHCompositeNode*)'



  PHHepMCGenEventMap* SCorrelatorUtilities::GetMcEventMap(PHCompositeNode* topNode) {

    PHHepMCGenEventMap* mapMcEvts = getClass<PHHepMCGenEventMap>(topNode, "PHHepMCGenEventMap");
    if (!mapMcEvts) {
      cerr << PHWHERE
           << "PANIC: HepMC event map node is missing!"
           << endl;
      assert(mapMcEvts);
    }
    return mapMcEvts;

  }  // end 'GetMcEventMap(PHCompositeNode*)'



  PHHepMCGenEvent* SCorrelatorUtilities::GetMcEvent(PHCompositeNode* topNode, const int iEvtToGrab) {

    PHHepMCGenEventMap* mcEvtMap = GetMcEventMap(topNode);
    PHHepMCGenEvent*    mcEvt    = mcEvtMap -> get(iEvtToGrab);
    if (!mcEvt) {
      cerr << PHWHERE
           << "PANIC: Couldn't grab mc event!"
           << endl;
      assert(mcEvt);
    }
    return mcEvt;

  }  // end 'GetMcEvent(PHCompositeNode*, int)'



  HepMC::GenEvent* SCorrelatorUtilities::GetGenEvent(PHCompositeNode* topNode, const int iEvtToGrab) {

    PHHepMCGenEvent* mcEvt  = GetMcEvent(topNode, iEvtToGrab);
    HepMC::GenEvent* genEvt = mcEvt -> getEvent();
    if (!genEvt) {
      cerr << PHWHERE
           << "PANIC: Couldn't grab HepMC event!"
           << endl;
      assert(mcEvt);
    }
    return genEvt;

  }  // end 'GetGenEvent(PHCompositeNode*, int)'



  int SCorrelatorUtilities::GetEmbedID(PHCompositeNode* topNode, const int iEvtToGrab) {

    // grab mc event & return embedding id
    PHHepMCGenEvent* mcEvt = GetMcEvent(topNode, iEvtToGrab);
    return mcEvt -> get_embedding_id();

  }  // end 'GetEmbedID(PHCompositeNode*, int)'



  bool SCorrelatorUtilities::IsInAcceptance(const ParInfo& particle, const ParInfo& minimum, const ParInfo& maximum) {

    return ((particle >= minimum) && (particle <= maximum));

  }  // end 'IsInAcceptance(ParInfo&, ParInfo&, ParInfo&)'



  bool SCorrelatorUtilities::IsFinalState(const int status) {

    return (status == 1);

  }  // end 'IsFinalState(int)'



  bool SCorrelatorUtilities::IsHardScatterProduct(const int status) {

    return ((status == HardScatterStatus::First) || (status == HardScatterStatus::Second));

  }  // end 'IsHardScatterProduct(int)'



  bool SCorrelatorUtilities::IsParton(const int pid) {

    const bool isLightQuark   = ((pid == Parton::Down)    || (pid == Parton::Up));
    const bool isStrangeQuark = ((pid == Parton::Strange) || (pid == Parton::Charm));
    const bool isHeavyQuark   = ((pid == Parton::Bottom)  || (pid == Parton::Top));
    const bool isGluon        = (pid == Parton::Gluon);
    return (isLightQuark || isStrangeQuark || isHeavyQuark || isGluon);

  }  // end 'IsParton(int)'



  bool SCorrelatorUtilities::IsOutgoingParton(const HepMC::GenParticle* par) {

    // grab particle info
    const int pid    = par -> pdg_id();
    const int status = par -> status();

    // check if is outgoing parton
    const bool isOutgoingParton = (IsHardScatterProduct(status) && IsParton(pid));
    return isOutgoingParton;

  }  // end 'IsOutgoingParton(HepMC::GenParticle*)'



  float SCorrelatorUtilities::GetParticleCharge(const int pid) {

    // particle charge
    float charge = MapPidOntoCharge[abs(pid)];

    // if antiparticle, flip charge and return
    if (pid < 0) {
      charge *= -1.;
    }
    return charge;

  }  // end 'GetParticleCharge(int)'



  bool SCorrelatorUtilities::IsSubEvtGood(const int embedID, const int option, const bool isEmbed) {

    // set ID of signal
    int signalID = SubEvt::NotEmbedSignal;
    if (isEmbed) {
      signalID = SubEvt::EmbedSignal;
    }

    bool isSubEvtGood = true;
    switch (option) {

      // consider everything
      case SubEvtOpt::Everything:
        isSubEvtGood = true;
        break;

      // only consider signal event
      case SubEvtOpt::OnlySignal:
        isSubEvtGood = (embedID == signalID);
        break;

      // only consider background events
      case SubEvtOpt::AllBkgd:
        isSubEvtGood = (embedID <= SubEvt::Background);
        break;

      // only consider primary background event
      case SubEvtOpt::PrimaryBkgd:
        isSubEvtGood = (embedID == SubEvt::Background);
        break;

      // only consider pileup events
      case SubEvtOpt::Pileup:
        isSubEvtGood = (embedID < SubEvt::Background);
        break;

      // by default do nothing
      default:
        isSubEvtGood = true;
        break;
    }
    return isSubEvtGood;

  }  // end 'IsSubEvtGood(int, int, bool)'



  bool SCorrelatorUtilities::IsSubEvtGood(const int embedID, vector<int> subEvtsToUse) {

    bool isSubEvtGood = false;
    for (const int evtToUse : subEvtsToUse) {
      if (embedID == evtToUse) {
        isSubEvtGood = true;
        break;
      }
    }
    return isSubEvtGood;

  }  // end 'IsSubEvtGood(int, vector<int>)'



/* TODO uncomment when used
  vector<int> SCorrelatorUtilities::GrabSubevents(PHCompositeNode* topNode, const SubEvtOpt option = SubEvtOpt::Everything, const bool isEmbed = false) {

    // instantiate vector to hold subevents
    vector<int> subevents;
  
    PHHepMCGenEventMap* mcEvtMap = GetMcEventMap(topNode);
    for (
      PHHepMCGenEventMap::ConstIter itEvt = mcEvtMap -> begin();
      itEvt != mcEvtMap -> end();
      ++itEvt
    ) {

      // grab event id
      const int embedID = itEvt -> second -> get_embedding_id();

      // if subevent satisfies option, add to list
      const bool isSubEvtGood = IsSubEvtGood(embedID, option, isEmbed);
      if (isSubEvtGood) subevents.push_back(embedID);
    }
    return subevents;

  }  // end 'GrabSubevents(PHCompositeNode*, optional<vector<int>>)'
*/



  vector<int> SCorrelatorUtilities::GrabSubevents(PHCompositeNode* topNode, vector<int> subEvtsToUse) {

    // instantiate vector to hold subevents
    vector<int> subevents;
  
    PHHepMCGenEventMap* mcEvtMap = GetMcEventMap(topNode);
    for (
      PHHepMCGenEventMap::ConstIter itEvt = mcEvtMap -> begin();
      itEvt != mcEvtMap -> end();
      ++itEvt
    ) {

      // grab event id
      const int embedID = itEvt -> second -> get_embedding_id();

      // check to see if event is in provided list
      bool addToList = false;
      for (const int idToCheck : subEvtsToUse) {
        if (embedID == idToCheck) {
          addToList = true;
          break;
        }
      }  // end evtsToGrab loop

      // if on list, add to list of good subevents
      if (addToList) subevents.push_back(embedID);

    }
    return subevents;

  }  // end 'GrabSubevents(PHCompositeNode*, vector<int>)'



  HepMC::GenParticle* SCorrelatorUtilities::GetHepMCGenParticleFromBarcode(const int barcode, PHCompositeNode* topNode) {

    // by default, return null pointer
    HepMC::GenParticle* parToGrab = NULL;

    // loop over all subevents to search
    PHHepMCGenEventMap* mcEvtMap = GetMcEventMap(topNode);
    for (
      PHHepMCGenEventMap::ConstIter genEvt = mcEvtMap -> begin();
      genEvt != mcEvtMap -> end();
      ++genEvt
    ) {
      for (
        HepMC::GenEvent::particle_const_iterator hepPar = genEvt -> second -> getEvent() -> particles_begin();
        hepPar != genEvt -> second -> getEvent() -> particles_end();
        ++hepPar
      ) {
        if ((*hepPar) -> barcode() == barcode) {
          parToGrab = *hepPar;
          break;
        }
      }  // end particle loop
    }  // end subevent loop
    return parToGrab;

  }  // end 'GetHepMCGenParticleFromBarcode(int, PHCompositeNode*)'



  PHG4Particle* SCorrelatorUtilities::GetPHG4ParticleFromBarcode(const int barcode, PHCompositeNode* topNode) {

    // by default, return null pointer
    PHG4Particle* parToGrab = NULL;

    // grab truth info container
    PHG4TruthInfoContainer* container = GetTruthContainer(topNode);

    // loop over all particles in container to search
    PHG4TruthInfoContainer::ConstRange particles = container -> GetParticleRange();
    for (
      PHG4TruthInfoContainer::ConstIterator itPar = particles.first;
      itPar != particles.second;
      ++itPar
    ) {
      if (itPar -> second -> get_barcode() == barcode) {
        parToGrab = itPar -> second;
        break;
      }
    }  // end particle loop
    return parToGrab;

  }  // end 'GetPHG4ParticleFromBarcode(int, PHCompositeNode*)'



  PHG4Particle* SCorrelatorUtilities::GetPHG4ParticleFromTrackID(const int id, PHCompositeNode* topNode) {

    // by default, return null pointer
    PHG4Particle* parToGrab = NULL;

    // grab truth info container
    PHG4TruthInfoContainer* container = GetTruthContainer(topNode);

    // loop over all particles in container to search
    PHG4TruthInfoContainer::ConstRange particles = container -> GetParticleRange();
    for (
      PHG4TruthInfoContainer::ConstIterator itPar = particles.first;
      itPar != particles.second;
      ++itPar
    ) {
      if (itPar -> second -> get_track_id() == id) {
        parToGrab = itPar -> second;
        break;
      }
    }  // end particle loop
    return parToGrab;

  }  // end 'GetPHG4ParticleFromTrackID(int, PHCompositeNode*)'

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
