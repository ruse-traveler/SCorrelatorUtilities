// ----------------------------------------------------------------------------
// 'SCorrelatorUtilities.TrkInfo.h'
// Derek Anderson
// 10.23.2023
//
// Definition of TrkInfo class utilized in the sPHENIX
// Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    /* TODO
     *   - add overloaded <, > operators for applying cuts
     *   - add SetInfo(SvtxTrack*) method
     */
    struct TrkInfo {

      // data members
      int    m_nMvtxLyr = -1;
      int    m_nInttLyr = -1;
      int    m_nTpcLyr  = -1;
      double m_pt       = -999.;
      double m_eta      = -999.;
      double m_phi      = -999.;
      double m_ene      = -999.;
      double m_dcaXY    = -999.;
      double m_dcaZ     = -999.;
      double m_ptErr    = -999.;
      double m_quality  = -999.;
      double m_vtxX     = -999.;
      double m_vtxY     = -999.;
      double m_vtxZ     = -999.;

      void SetInfo(
        const int    mvtx,
        const int    intt,
        const int    tpc,
        const double pt,
        const double eta,
        const double phi,
        const double ene,
        const double dcaxy,
        const double dcaz,
        const double pterr,
        const double qual,
        const double vx,
        const double vy,
        const double vz
      ) {
        m_nMvtxLyr = mvtx;
        m_nInttLyr = intt;
        m_nTpcLyr  = tpc;
        m_pt       = pt;
        m_eta      = eta;
        m_phi      = phi;
        m_ene      = ene;
        m_dcaXY    = dcaxy;
        m_dcaZ     = dcaz;
        m_ptErr    = pterr;
        m_quality  = qual;
        m_vtxX     = vx;
        m_vtxY     = vy;
        m_vtxZ     = vz;
        return;
      }  // end 'SetInfo()'

      void Rest() {
        m_nMvtxLyr = -1;
        m_nInttLyr = -1;
        m_nTpcLyr  = -1;
        m_pt       = -999.;
        m_eta      = -999.;
        m_phi      = -999.;
        m_ene      = -999.;
        m_dcaXY    = -999.;
        m_dcaZ     = -999.;
        m_ptErr    = -999.;
        m_quality  = -999.;
        m_vtxX     = -999.;
        m_vtxY     = -999.;
        m_vtxZ     = -999.;
        return;
      }  // end 'Reset()'

    };  // end TrkInfo def

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
