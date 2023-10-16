// ----------------------------------------------------------------------------
// 'SCorrelatorUtilities.h'
// Derek Anderson
// 09.21.2023
//
// A namespace to collect various useful structs, methods, etc.
// for the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once

using namespace std;


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

  }  // end SCorrelatorUtilities namespace

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
