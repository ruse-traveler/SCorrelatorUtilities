// ----------------------------------------------------------------------------
// 'GenTools.h'
// Derek Anderson
// 10.30.2023
//
// Collection of frequent generator/MC-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // generator/mc methods ---------------------------------------------------

    PHHepMCGenEventMap* GetMcEventMap(PHCompositeNode* topNode) {

      PHHepMCGenEventMap* mapMcEvts = getClass<PHHepMCGenEventMap>(topNode, "PHHepMCGenEventMap");
      if (!mapMcEvts) {
        cerr << PHWHERE
             << "PANIC: HEPMC event map node is missing!"
             << endl;
        assert(mapMcEvts);
      }
      return mapMcEvts;

    }  // end 'GetMcEventMap(PHCompositeNode*)'



    PHHepMCGenEvent* GetMcEvent(PHCompositeNode* topNode, const int iEvtToGrab) {

      PHHepMcGenEventMap* mcEvtMap = GetMcEventMap(topNode);
      PHHepMCGenEvent*    mcEvt    = mapMcEvts -> get(iEvtToGrab);
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
      HepMC::GenEvent* genEvt = mcEvtStart -> getEvent();
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
      PHHepMCGenEvent* mcEvt = GetMcEvent(topNode, iEvtTograb);
      return mcEvt -> get_embedding_id();

    }  // end 'GetEmbedID(PHCompositeNode*, int)'



    bool IsFinalState(const int status) {

      return (status == 1);

    }  // end 'IsFinalState(int)'



    bool IsHardScatterProduct(const int status) {

      return ((status == 23) || (status == 24));

    }  // end 'IsHardScatterProduct(int)'



    bool IsParton(const int pid) {

      const bool isLightQuark   = ((pid == 1) || (pid == 2));
      const bool isStrangeQuark = ((pid == 3) || (pid == 4));
      const bool isHeavyQuark   = ((pid == 5) || (pid == 6));
      const bool isGluon        = (pid == 21);
      return (isLightQuark || isStrangeQuark || isHeavyQuark || isGluon);

    }  // end 'IsParton(int)'



    bool IsOutgoingParton(HepMC::GenParticle* par) {

      // grab particle info
      const int pid    = par -> pdg_id();
      const int status = par -> status();

      // check if is outgoing parton
      const bool isOutgoingParton = (IsHardScatterProduct(status) && IsParton(pid));
      return isOutgoingParton;

    }  // end 'IsOutgoingParton(HepMC::GenParticle*)'



    float GetParticleCharge(const int pid) {

      // particle charge
      float charge = mapPidOntoCharge[abs(pid)];

      // if antiparticle, flip charge and return
      if (pid < 0) {
        charge *= -1.;
      }
      return charge;

    }  // end 'GetParticleCharge(int)'

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
