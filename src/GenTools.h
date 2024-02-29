// ----------------------------------------------------------------------------
// 'GenTools.h'
// Derek Anderson
// 10.30.2023
//
// Collection of frequent generator/MC-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#ifndef GENTOOLS_H
#define GENTOOLS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// c++ utilities
#include <limits>
#include <string>
#include <vector>
// phool libraries
#include <phool/PHCompositeNode.h>
// PHG4 libraries
#include <g4main/PHG4Particle.h>
#include <g4main/PHG4TruthInfoContainer.h>
// hepmc libraries
#include <HepMC/GenEvent.h>
#include <HepMC/GenParticle.h>
#include <phhepmc/PHHepMCGenEvent.h>
#include <phhepmc/PHHepMCGenEventMap.h>
// analysis utilities
#include "Constants.h"

#pragma GCC diagnostic pop

// make common namespaces implicit
using namespace std;



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

      }  // end 'operator<(ParInfo&, ParInfo&)'

      // overloaded <= operator
      friend bool operator<=(const ParInfo& lhs, const ParInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isLessThanOrEqualTo = (
          (lhs.eta  <= rhs.eta)  &&
          (lhs.phi  <= rhs.phi)  &&
          (lhs.ene  <= rhs.ene)  &&
          (lhs.px   <= rhs.px)   &&
          (lhs.py   <= rhs.py)   &&
          (lhs.pz   <= rhs.pz)   &&
          (lhs.pt   <= rhs.pt)
        );
        return isLessThanOrEqualTo;

      }  // end 'operator<=(ParInfo&, ParInfo&)'

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

      // overloaded >= operator
      friend bool operator>=(const ParInfo& lhs, const ParInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isGreaterThanOrEqualTo = (
          (lhs.eta  >= rhs.eta)  &&
          (lhs.phi  >= rhs.phi)  &&
          (lhs.ene  >= rhs.ene)  &&
          (lhs.px   >= rhs.px)   &&
          (lhs.py   >= rhs.py)   &&
          (lhs.pz   >= rhs.pz)   &&
          (lhs.pt   >= rhs.pt)
        );
        return isGreaterThanOrEqualTo;

      }  // end 'operator>=(ParInfo&, ParInfo&)'

      // default ctor/dtor
      ParInfo()  {};
      ~ParInfo() {};

      ParInfo(HepMC::GenParticle* particle, const int event) {
        SetInfo(particle, event);
      };

    };  // end ParInfo definition



    // generator/mc methods ---------------------------------------------------

    PHG4TruthInfoContainer* GetTruthContainer(PHCompositeNode* topNode);
    PHHepMCGenEventMap* GetMcEventMap(PHCompositeNode* topNode);
    PHHepMCGenEvent* GetMcEvent(PHCompositeNode* topNode, const int iEvtToGrab);
    HepMC::GenEvent* GetGenEvent(PHCompositeNode* topNode, const int iEvtToGrab);
    int GetEmbedID(PHCompositeNode* topNode, const int iEvtToGrab);
    bool IsInAcceptance(const ParInfo& particle, const ParInfo& minimum, const ParInfo& maximum);
    bool IsFinalState(const int status);
    bool IsHardScatterProduct(const int status);
    bool IsParton(const int pid);
    bool IsOutgoingParton(const HepMC::GenParticle* par);
    float GetParticleCharge(const int pid);
    bool IsSubEvtGood(const int embedID, const int option, const bool isEmbed);
    bool IsSubEvtGood(const int embedID, vector<int> subEvtsToUse);
    //vector<int> GrabSubevents(PHCompositeNode* topNode, const SubEvtOpt option = SubEvtOpt::Everything, const bool isEmbed = false);
    vector<int> GrabSubevents(PHCompositeNode* topNode, vector<int> subEvtsToUse);
    HepMC::GenParticle* GetHepMCGenParticleFromBarcode(const int barcode, PHCompositeNode* topNode);
    PHG4Particle* GetPHG4ParticleFromBarcode(const int barcode, PHCompositeNode* topNode);
    PHG4Particle* GetPHG4ParticleFromTrackID(const int id, PHCompositeNode* topNode);

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
