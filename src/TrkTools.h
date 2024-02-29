// ----------------------------------------------------------------------------
// 'TrkTools.h'
// Derek Anderson
// 10.30.2023
//
// Definition of TrkInfo class and collection of frequent track-
// related methods utilized in the sPHENIX Cold QCD Energy-Energy
// Correlator analysis.
// ----------------------------------------------------------------------------

#ifndef TRKTOOLS_H
#define TRKTOOLS_H

// c++ utilities
#include <limits>
#include <string>
#include <vector>
#include <utility>
// root utilities
#include <TF1.h>
#include <Math/Vector3D.h>
// phool libraries
#include <phool/PHCompositeNode.h>
// tracking libraries
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
// track evaluator utilities
#include <g4eval/SvtxTrackEval.h>
// analysis utilities
#include "Constants.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // forward declarations used in TrkInfo
    pair<double, double>  GetTrackDcaPair(SvtxTrack* track, PHCompositeNode* topNode);
    ROOT::Math::XYZVector GetTrackVertex(SvtxTrack* track, PHCompositeNode* topNode);
    double                GetTrackDeltaPt(SvtxTrack* track);
    int                   GetNumLayer(SvtxTrack* track, const uint8_t sys);
    int                   GetNumClust(SvtxTrack* track, const uint8_t sys);

    // TrkInfo definition -----------------------------------------------------

    struct TrkInfo {

      // data members
      int    id         = numeric_limits<int>::max();
      int    nMvtxLayer = numeric_limits<int>::max();
      int    nInttLayer = numeric_limits<int>::max();
      int    nTpcLayer  = numeric_limits<int>::max();
      int    nMvtxClust = numeric_limits<int>::max();
      int    nInttClust = numeric_limits<int>::max();
      int    nTpcClust  = numeric_limits<int>::max();
      double phi        = numeric_limits<double>::max();
      double ene        = numeric_limits<double>::max();
      double px         = numeric_limits<double>::max();
      double py         = numeric_limits<double>::max();
      double pz         = numeric_limits<double>::max();
      double pt         = numeric_limits<double>::max();
      double eta        = numeric_limits<double>::max();
      double dcaXY      = numeric_limits<double>::max();
      double dcaZ       = numeric_limits<double>::max();
      double ptErr      = numeric_limits<double>::max();
      double quality    = numeric_limits<double>::max();
      double vtxX       = numeric_limits<double>::max();
      double vtxY       = numeric_limits<double>::max();
      double vtxZ       = numeric_limits<double>::max();

      void SetInfo(SvtxTrack* track, PHCompositeNode* topNode) {

        // do relevant calculations
        const ROOT::Math::XYZVector trkVtx     = GetTrackVertex(track, topNode);
        const pair<double, double>  trkDcaPair = GetTrackDcaPair(track, topNode);

        // set track info
        id         = track -> get_id();
        quality    = track -> get_quality();
        eta        = track -> get_eta();
        phi        = track -> get_phi();
        px         = track -> get_px();
        py         = track -> get_py();
        pz         = track -> get_pz();
        pt         = track -> get_pt();
        ene        = sqrt((px * px) + (py * py) + (pz * pz) + (MassPion * MassPion));
        vtxX       = trkVtx.x();
        vtxY       = trkVtx.y();
        vtxZ       = trkVtx.z();
        dcaXY      = trkDcaPair.first;
        dcaZ       = trkDcaPair.second;
        nMvtxLayer = GetNumLayer(track, Subsys::Mvtx);
        nInttLayer = GetNumLayer(track, Subsys::Intt);
        nTpcLayer  = GetNumLayer(track, Subsys::Tpc);
        nMvtxClust = GetNumClust(track, Subsys::Mvtx);
        nInttClust = GetNumClust(track, Subsys::Intt);
        nTpcClust  = GetNumClust(track, Subsys::Tpc);
        ptErr      = GetTrackDeltaPt(track);
        return;
      }  // end 'SetInfo(SvtxTrack*, PHCompositeNode*)'

      void Reset() {
        id         = numeric_limits<int>::max();
        nMvtxLayer = numeric_limits<int>::max();
        nInttLayer = numeric_limits<int>::max();
        nTpcLayer  = numeric_limits<int>::max();
        nMvtxClust = numeric_limits<int>::max();
        nInttClust = numeric_limits<int>::max();
        nTpcClust  = numeric_limits<int>::max();
        eta        = numeric_limits<double>::max();
        phi        = numeric_limits<double>::max();
        px         = numeric_limits<double>::max();
        py         = numeric_limits<double>::max();
        pz         = numeric_limits<double>::max();
        pt         = numeric_limits<double>::max();
        ene        = numeric_limits<double>::max();
        dcaXY      = numeric_limits<double>::max();
        dcaZ       = numeric_limits<double>::max();
        ptErr      = numeric_limits<double>::max();
        quality    = numeric_limits<double>::max();
        vtxX       = numeric_limits<double>::max();
        vtxY       = numeric_limits<double>::max();
        vtxZ       = numeric_limits<double>::max();
        return;
      }  // end 'Reset()'

      static vector<string> GetListOfMembers() {
        vector<string> members = {
          "id",
          "nMvtxLayer",
          "nInttLayer",
          "nTpcLayer",
          "nMvtxClust",
          "nInttClust",
          "nTpcClust",
          "eta",
          "phi",
          "px",
          "py",
          "pz",
          "pt",
          "ene",
          "dcaXY",
          "dcaZ",
          "ptErr",
          "quality",
          "vtxX",
          "vtxY",
          "vtxZ"
        };
        return members;
      }  // end 'GetListOfMembers()'

      // overloaded < operator
      friend bool operator<(const TrkInfo& lhs, const TrkInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isLessThan = (
          (lhs.nMvtxLayer < rhs.nMvtxLayer) &&
          (lhs.nInttLayer < rhs.nInttLayer) &&
          (lhs.nTpcLayer  < rhs.nTpcLayer)  &&
          (lhs.nMvtxClust < rhs.nMvtxClust) &&
          (lhs.nInttClust < rhs.nInttClust) &&
          (lhs.nTpcClust  < rhs.nTpcClust)  &&
          (lhs.eta        < rhs.eta)        &&
          (lhs.phi        < rhs.phi)        &&
          (lhs.px         < rhs.px)         &&
          (lhs.py         < rhs.py)         &&
          (lhs.pz         < rhs.pz)         &&
          (lhs.pt         < rhs.pt)         &&
          (lhs.ene        < rhs.ene)        &&
          (lhs.dcaXY      < rhs.dcaXY)      &&
          (lhs.dcaZ       < rhs.dcaZ)       &&
          (lhs.ptErr      < rhs.ptErr)      &&
          (lhs.quality    < rhs.quality)    &&
          (lhs.vtxX       < rhs.vtxX)       &&
          (lhs.vtxY       < rhs.vtxY)       &&
          (lhs.vtxZ       < rhs.vtxZ)
        );
        return isLessThan;

      }  // end 'operator<(TrkInfo&, TrkInfo&)'

      // overloaded > operator
      friend bool operator>(const TrkInfo& lhs, const TrkInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isGreaterThan = (
          (lhs.nMvtxLayer > rhs.nMvtxLayer) &&
          (lhs.nInttLayer > rhs.nInttLayer) &&
          (lhs.nTpcLayer  > rhs.nTpcLayer)  &&
          (lhs.nMvtxClust > rhs.nMvtxClust) &&
          (lhs.nInttClust > rhs.nInttClust) &&
          (lhs.nTpcClust  > rhs.nTpcClust)  &&
          (lhs.eta        > rhs.eta)        &&
          (lhs.phi        > rhs.phi)        &&
          (lhs.px         > rhs.px)         &&
          (lhs.py         > rhs.py)         &&
          (lhs.pz         > rhs.pz)         &&
          (lhs.pt         > rhs.pt)         &&
          (lhs.ene        > rhs.ene)        &&
          (lhs.dcaXY      > rhs.dcaXY)      &&
          (lhs.dcaZ       > rhs.dcaZ)       &&
          (lhs.ptErr      > rhs.ptErr)      &&
          (lhs.quality    > rhs.quality)    &&
          (lhs.vtxX       > rhs.vtxX)       &&
          (lhs.vtxY       > rhs.vtxY)       &&
          (lhs.vtxZ       > rhs.vtxZ)
        );
        return isGreaterThan;

      }  // end 'operator>(TrkInfo&, TrkInfo&)'

      // overloaded, <=, >= operators
      inline friend bool operator<=(const TrkInfo& lhs, const TrkInfo& rhs) {return !(lhs > rhs);}
      inline friend bool operator>=(const TrkInfo& lhs, const TrkInfo& rhs) {return !(lhs < rhs);}

      // default ctor/dtor
      TrkInfo()  {};
      ~TrkInfo() {};

      // ctor accepting SvtxTracks
      TrkInfo(SvtxTrack* track, PHCompositeNode* topNode) {
        SetInfo(track, topNode);
      }

    };  // end TrkInfo def



    // track methods ----------------------------------------------------------

    SvtxTrackMap* GetTrackMap(PHCompositeNode* topNode);
    bool IsInAcceptance(const TrkInfo& trk, const TrkInfo& minimum, const TrkInfo& maximum);
    bool IsInSigmaDcaCut(const TrkInfo& trk, const pair<float, float> nSigCut, const pair<float, float> ptFitMax, const pair<TF1*, TF1*> fSigmaDca);
    bool IsGoodTrackSeed(SvtxTrack* track, const bool requireSiSeeds = true);
    bool IsFromPrimaryVtx(SvtxTrack* track, PHCompositeNode* topNode);
    pair<double, double> GetTrackDcaPair(SvtxTrack* track, PHCompositeNode* topNode);
    ROOT::Math::XYZVector GetTrackVertex(SvtxTrack* track, PHCompositeNode* topNode);
    double GetTrackDeltaPt(SvtxTrack* track);
    TrackSeed* GetTrackSeed(SvtxTrack* track, const uint8_t sys);
    int GetNumLayer(SvtxTrack* track, const uint8_t sys = 0);
    int GetNumClust(SvtxTrack* track, const uint8_t sys = 0);
    int GetMatchID(SvtxTrack* track, SvtxTrackEval* trackEval);

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
