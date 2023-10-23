// ----------------------------------------------------------------------------
// 'SCorrelatorUtilities.EvtInfo.h'
// Derek Anderson
// 10.22.2023
//
// Definition of EvtInfo class utilized in the sPHENIX
// Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    struct EvtInfo {

      // data members
      // TODO add energy sums, etc
      int    m_numJets = -1;
      int    m_numTrks = -1;
      double m_vtxX    = -999.;
      double m_vtxY    = -999.;
      double m_vtxZ    = -999.;

      void SetInfo(int nJet, int nTrk, double vX, double vY, double vZ) {
        m_numJets = nJet;
        m_numTrks = nTrk;
        m_vtxX    = vX;
        m_vtxY    = vY;
        m_vtxZ    = vZ;
        return;
      }  // end 'SetInfo(int, int, double, double, double)'

      void Reset() {
        m_numJets = -1;
        m_numTrks = -1;
        m_vtxX    = -999.;
        m_vtxY    = -999.;
        m_vtxZ    = -999.;
        return;
      }  // end 'Reset()'

    };  // end EvtInfo def

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
