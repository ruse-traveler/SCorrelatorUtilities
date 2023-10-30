// ----------------------------------------------------------------------------
// 'SCorrelatorUtilities.TrkInfo.h'
// Derek Anderson
// 10.23.2023
//
// Definition of TrkInfo class utilized in the sPHENIX
// Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

// relevant headers
//

#pragma once

// make common namespaces implicit
using namespace std;

// set up aliases
using CLVec3  = CLHEP::Hep3Vector;  // FIXME replace CLHEP vectors with ROOT XYZVectors
using DcaPair = pair<double, double>;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // TrkInfo definition -----------------------------------------------------

    /* TODO
     *   - add overloaded <, > operators for applying cuts
     */
    struct TrkInfo {

      // data members
      int    m_nMvtxLayer = -1;
      int    m_nInttLayer = -1;
      int    m_nTpcLayer  = -1;
      int    m_nMvtxClust = -1;
      int    m_nInttClust = -1;
      int    m_nTpcClust  = -1;
      double m_pt         = -999.;
      double m_eta        = -999.;
      double m_phi        = -999.;
      double m_ene        = -999.;
      double m_dcaXY      = -999.;
      double m_dcaZ       = -999.;
      double m_ptErr      = -999.;
      double m_quality    = -999.;
      double m_vtxX       = -999.;
      double m_vtxY       = -999.;
      double m_vtxZ       = -999.;

      void SetInfo(SvtxTrack* track, PHCompositeNode* topNode) {

        // do relevant calculations
        const double  trkPx      = track -> get_px();
        const double  trkPy      = track -> get_py();
        const double  trkPz      = track -> get_pz();
        const CLVec3  trkVtx     = GetTrackVertex(track, topNode);
        const DcaPair trkDcaPair = GetTrackDcaPair(track, topNode);

        // set track info
        m_pt       = track -> get_pt();
        m_eta      = track -> get_eta();
        m_phi      = track -> get_phi();
        m_quality  = track -> get_quality();
        m_ene      = sqrt((trkPx * trkPx) + (trkPy * trkPy) + (trkPz * trkPz) + (MassPion * MassPion));
      
        m_vtxX     =   trkVtx.x();
        m_vtxY       = trkVtx.y();
        m_vtxZ       = trkVtx.z();
        m_dcaXY      = trkDcaPair.first;
        m_dcaZ       = trkDcaPair.second;
        m_nMvtxLayer = GetNumLayer(track, Subsys::Mvtx);
        m_nInttLayer = GetNumLayer(track, Subsys::Intt);
        m_nTpcLayer  = GetNumLayer(track, Subsys::Tpc);
        m_nMvtxClust = GetNumClust(track, Subsys::Mvtx);
        m_nInttClust = GetNumClust(track, Subsys::Intt);
        m_nTpcClust  = GetNumClust(track, Subsys::Tpc);
        m_ptErr      = GetTrackDeltaPt(track);
        return;
      }  // end 'SetInfo(SvtxTrack*)'

      void SetInfo(
        const int    nlmvtx,
        const int    nlintt,
        const int    nltpc,
        const int    ncmvtx,
        const int    ncintt,
        const int    nctpc,
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
        m_nMvtxLayer = nlmvtx;
        m_nInttLayer = nlintt;
        m_nTpcLayer  = nltpc;
        m_nMvtxClust = ncmvtx;
        m_nInttClust = ncintt;
        m_nTpcClust  = nctpc;
        m_pt         = pt;
        m_eta        = eta;
        m_phi        = phi;
        m_ene        = ene;
        m_dcaXY      = dcaxy;
        m_dcaZ       = dcaz;
        m_ptErr      = pterr;
        m_quality    = qual;
        m_vtxX       = vx;
        m_vtxY       = vy;
        m_vtxZ       = vz;
        return;
      }  // end 'SetInfo(int x 6, double x 11)'

      void Reset() {
        m_nMvtxLayer = -1;
        m_nInttLayer = -1;
        m_nTpcLayer  = -1;
        m_nMvtxClust = -1;
        m_nInttClust = -1;
        m_nTpcClust  = -1;
        m_pt         = -999.;
        m_eta        = -999.;
        m_phi        = -999.;
        m_ene        = -999.;
        m_dcaXY      = -999.;
        m_dcaZ       = -999.;
        m_ptErr      = -999.;
        m_quality    = -999.;
        m_vtxX       = -999.;
        m_vtxY       = -999.;
        m_vtxZ       = -999.;
        return;
      }  // end 'Reset()'

    };  // end TrkInfo def

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
