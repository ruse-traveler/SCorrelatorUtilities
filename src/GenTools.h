// ----------------------------------------------------------------------------
// 'GenTools.h'
// Derek Anderson
// 10.30.2023
//
// Collection of frequent generator/MC-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// c++ utilities
#include <cmath>
#include <limits>
#include <string>
#include <vector>
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
#include "Constants.h"

#pragma GCC diagnostic pop

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // ParInfo definition -----------------------------------------------------

    struct ParInfo {

      // data members
      int    pid     = numeric_limits<int>::max();
      int    status  = numeric_limits<int>::max();
      int    barcode = numeric_limits<int>::max();
      int    embedID = numeric_limits<int>::max();
      float  charge  = numeric_limits<float>::max();
      double mass    = numeric_limits<double>::max();
      double eta     = numeric_limits<double>::max();
      double phi     = numeric_limits<double>::max();
      double ene     = numeric_limits<double>::max();
      double px      = numeric_limits<double>::max();
      double py      = numeric_limits<double>::max();
      double pz      = numeric_limits<double>::max();
      double pt      = numeric_limits<double>::max();
      double vx      = numeric_limits<double>::max();
      double vy      = numeric_limits<double>::max();
      double vz      = numeric_limits<double>::max();
      double vr      = numeric_limits<double>::max();

      void SetInfo(const HepMC::GenParticle* particle, const int event) {
        pid     = particle -> pdg_id();
        status  = particle -> status();
        barcode = particle -> barcode();
        embedID = event;
        charge  = MapPidOntoCharge[pid];
        mass    = particle -> momentum().m();
        eta     = particle -> momentum().eta();
        phi     = particle -> momentum().phi();
        ene     = particle -> momentum().e();
        px      = particle -> momentum().px();
        py      = particle -> momentum().py();
        pz      = particle -> momentum().pz();
        pt      = particle -> momentum().perp();
        return;
      };  // end 'SetInfo(HepMC::GenParticle*, int)'

      void Reset() {
        pid     = numeric_limits<int>::max();
        status  = numeric_limits<int>::max();
        barcode = numeric_limits<int>::max();
        embedID = numeric_limits<int>::max();
        charge  = numeric_limits<float>::max();
        mass    = numeric_limits<double>::max();
        eta     = numeric_limits<double>::max();
        phi     = numeric_limits<double>::max();
        ene     = numeric_limits<double>::max();
        px      = numeric_limits<double>::max();
        py      = numeric_limits<double>::max();
        pz      = numeric_limits<double>::max();
        pt      = numeric_limits<double>::max();
        vx      = numeric_limits<double>::max();
        vy      = numeric_limits<double>::max();
        vz      = numeric_limits<double>::max();
        vr      = numeric_limits<double>::max();
        return;
      };  // end 'Reset()'

      static vector<string> GetListOfMembers() {
        vector<string> members = {
          "pid",
          "status",
          "barcode",
          "embedID",
          "charge",
          "mass",
          "eta",
          "phi",
          "ene",
          "px",
          "py",
          "pz",
          "pt",
          "vx",
          "vy",
          "vz",
          "vr"
        };
        return members;
      }  // end 'GetListOfMembers()'

      // overloaded < operator
      friend bool operator<(const ParInfo& lhs, const ParInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isLessThan = (
          (lhs.eta  < rhs.eta)  &&
          (lhs.phi  < rhs.phi)  &&
          (lhs.ene  < rhs.ene)  &&
          (lhs.px   < rhs.px)   &&
          (lhs.py   < rhs.py)   &&
          (lhs.pz   < rhs.pz)   &&
          (lhs.pt   < rhs.pt)
        );
        return isLessThan;

      }  // end 'operator>(ParInfo&, ParInfo&)'

      // overloaded > operator
      friend bool operator>(const ParInfo& lhs, const ParInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isGreaterThan = (
          (lhs.eta  > rhs.eta)  &&
          (lhs.phi  > rhs.phi)  &&
          (lhs.ene  > rhs.ene)  &&
          (lhs.px   > rhs.px)   &&
          (lhs.py   > rhs.py)   &&
          (lhs.pz   > rhs.pz)   &&
          (lhs.pt   > rhs.pt)
        );
        return isGreaterThan;

      }  // end 'operator>(ParInfo&, ParInfo&)'

      // overloaded, <=, >= operators
      inline friend bool operator<=(const ParInfo& lhs, const ParInfo& rhs) {return !(lhs > rhs);}
      inline friend bool operator>=(const ParInfo& lhs, const ParInfo& rhs) {return !(lhs < rhs);}

      // default ctor/dtor
      ParInfo()  {};
      ~ParInfo() {};

      ParInfo(HepMC::GenParticle* particle, const int event) {
        SetInfo(particle, event);
      };

    };  // end ParInfo definition



    // generator/mc methods ---------------------------------------------------

    PHG4TruthInfoContainer* GetTruthContainer(PHCompositeNode* topNode) {

      PHG4TruthInfoContainer* container = getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");
      if (!container) {
        cerr << PHWHERE
             << "PANIC: G4 truth info container node is missing!"
             << endl;
        assert(container);
      }
      return container;

    }  // end 'GetTruthContainer(PHCompositeNode*)'



    PHHepMCGenEventMap* GetMcEventMap(PHCompositeNode* topNode) {

      PHHepMCGenEventMap* mapMcEvts = getClass<PHHepMCGenEventMap>(topNode, "PHHepMCGenEventMap");
      if (!mapMcEvts) {
        cerr << PHWHERE
             << "PANIC: HepMC event map node is missing!"
             << endl;
        assert(mapMcEvts);
      }
      return mapMcEvts;

    }  // end 'GetMcEventMap(PHCompositeNode*)'



    PHHepMCGenEvent* GetMcEvent(PHCompositeNode* topNode, const int iEvtToGrab) {

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



    HepMC::GenEvent* GetGenEvent(PHCompositeNode* topNode, const int iEvtToGrab) {

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



    int GetEmbedID(PHCompositeNode* topNode, const int iEvtToGrab) {

      // grab mc event & return embedding id
      PHHepMCGenEvent* mcEvt = GetMcEvent(topNode, iEvtToGrab);
      return mcEvt -> get_embedding_id();

    }  // end 'GetEmbedID(PHCompositeNode*, int)'



    bool IsInAcceptance(const ParInfo& particle, const ParInfo& minimum, const ParInfo& maximum) {

      return ((particle >= minimum) && (particle <= maximum));

    }  // end 'IsInAcceptance(ParInfo&, ParInfo&, ParInfo&)'



    bool IsFinalState(const int status) {

      return (status == 1);

    }  // end 'IsFinalState(int)'



    bool IsHardScatterProduct(const int status) {

      return ((status == HardScatterStatus::First) || (status == HardScatterStatus::Second));

    }  // end 'IsHardScatterProduct(int)'



    bool IsParton(const int pid) {

      const bool isLightQuark   = ((pid == Parton::Down)    || (pid == Parton::Up));
      const bool isStrangeQuark = ((pid == Parton::Strange) || (pid == Parton::Charm));
      const bool isHeavyQuark   = ((pid == Parton::Bottom)  || (pid == Parton::Top));
      const bool isGluon        = (pid == Parton::Gluon);
      return (isLightQuark || isStrangeQuark || isHeavyQuark || isGluon);

    }  // end 'IsParton(int)'



    bool IsOutgoingParton(const HepMC::GenParticle* par) {

      // grab particle info
      const int pid    = par -> pdg_id();
      const int status = par -> status();

      // check if is outgoing parton
      const bool isOutgoingParton = (IsHardScatterProduct(status) && IsParton(pid));
      return isOutgoingParton;

    }  // end 'IsOutgoingParton(HepMC::GenParticle*)'



    float GetParticleCharge(const int pid) {

      // particle charge
      float charge = MapPidOntoCharge[abs(pid)];

      // if antiparticle, flip charge and return
      if (pid < 0) {
        charge *= -1.;
      }
      return charge;

    }  // end 'GetParticleCharge(int)'



    bool IsSubEvtGood(const int embedID, const int option, const bool isEmbed) {

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



    bool IsSubEvtGood(const int embedID, vector<int> subEvtsToUse) {

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
    vector<int> GrabSubevents(PHCompositeNode* topNode, const SubEvtOpt option = SubEvtOpt::Everything, const bool isEmbed = false) {

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



    vector<int> GrabSubevents(PHCompositeNode* topNode, vector<int> subEvtsToUse) {

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



    HepMC::GenParticle* GetHepMCGenParticleFromBarcode(const int barcode, PHCompositeNode* topNode) {

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



    PHG4Particle* GetPHG4ParticleFromBarcode(const int barcode, PHCompositeNode* topNode) {

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



    PHG4Particle* GetPHG4ParticleFromTrackID(const int id, PHCompositeNode* topNode) {

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

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
