// ----------------------------------------------------------------------------
// 'SCorrelatorUtilities.TrkTools.h'
// Derek Anderson
// 10.30.2023
//
// Definition of TrkInfo class and collection of frequent track-
// related methods utilized in the sPHENIX Cold QCD Energy-Energy
// Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once

// c++ utilities
#include <array>
#include <cassert>
#include <utility>
// root utilities
#include <TF1.h>
#include <Math/Vector3D.h>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// tracking libraries
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
#include <trackbase_historic/TrackAnalysisUtils.h>
// track evaluator utilities
#include <g4eval/SvtxTrackEval.h>
// vertex libraries
#include <globalvertex/GlobalVertex.h>
#include <globalvertex/GlobalVertexMap.h>
// phenix Geant4 utilities
#include <g4main/PHG4Particle.h>
// analysis utilities
#include "SCorrelatorUtilities.Constants.h"
#include "SCorrelatorUtilities.EvtTools.h"

// make common namespaces implicit
using namespace std;
using namespace findNode;



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
      int    id         = -1;
      int    nMvtxLayer = -1;
      int    nInttLayer = -1;
      int    nTpcLayer  = -1;
      int    nMvtxClust = -1;
      int    nInttClust = -1;
      int    nTpcClust  = -1;
      double phi        = -999.;
      double ene        = -999.;
      double px         = -999.;
      double py         = -999.;
      double pz         = -999.;
      double pt         = -999.;
      double eta        = -999.;
      double dcaXY      = -999.;
      double dcaZ       = -999.;
      double ptErr      = -999.;
      double quality    = -999.;
      double vtxX       = -999.;
      double vtxY       = -999.;
      double vtxZ       = -999.;

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
      }  // end 'SetInfo(SvtxTrack*)'

      void Reset() {
        id         = -1;
        nMvtxLayer = -1;
        nInttLayer = -1;
        nTpcLayer  = -1;
        nMvtxClust = -1;
        nInttClust = -1;
        nTpcClust  = -1;
        eta        = -999.;
        phi        = -999.;
        px         = -999.;
        py         = -999.;
        pz         = -999.;
        pt         = -999.;
        ene        = -999.;
        dcaXY      = -999.;
        dcaZ       = -999.;
        ptErr      = -999.;
        quality    = -999.;
        vtxX       = -999.;
        vtxY       = -999.;
        vtxZ       = -999.;
        return;
      }  // end 'Reset()'

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

    };  // end TrkInfo def



    // track methods ----------------------------------------------------------

    SvtxTrackMap* GetTrackMap(PHCompositeNode* topNode) {

      // grab track map
      SvtxTrackMap* mapTrks = findNode::getClass<SvtxTrackMap>(topNode, "SvtxTrackMap");
      if (!mapTrks) {
        cerr << PHWHERE
             << "PANIC: SvtxTrackMap node is missing!"
             << endl;
        assert(mapTrks);
      }
      return mapTrks;

    }  // end 'GetTrackMap(PHCompositeNode*)'



    bool IsInTrackAcceptance(const TrkInfo& trk, const TrkInfo& minimum, const TrkInfo& maximum) {

      // compare track against limits
      const bool isInAcceptance = ((trk >= minimum) && (trk <= maximum));
      return isInAcceptance;

    }  // end 'IsInTrackAcceptance(TrkInfo&, TrkInfo&, TrkInfo&)'



    bool IsInSigmaDcaCut(const TrkInfo& trk, const pair<float, float> nSigCut, const pair<float, float> ptFitMax, const pair<TF1*, TF1*> fSigmaDca) {

      // if above max pt used to fit dca width, use value of fit at max pt
      const double ptEvalXY = (trk.pt > ptFitMax.first)  ? ptFitMax.first  : trk.pt;
      const double ptEvalZ  = (trk.pt > ptFitMax.second) ? ptFitMax.second : trk.pt;

      // check if dca is in cut
      const bool isInDcaRangeXY  = (abs(trk.dcaXY) < (nSigCut.first  * (fSigmaDca.first  -> Eval(ptEvalXY))));
      const bool isInDcaRangeZ   = (abs(trk.dcaZ)  < (nSigCut.second * (fSigmaDca.second -> Eval(ptEvalZ))));
      const bool isInSigmaDcaCut = (isInDcaRangeXY && isInDcaRangeZ);
      return isInSigmaDcaCut;

    }  // end 'IsInSigmaDcaCut(TrkInfo&, pair<float, float>, pair<float, float>, pair<TF1*, TF1*>)'



    bool IsGoodTrackSeed(SvtxTrack* track, const bool requireSiSeeds = true) {

      // get track seeds
      TrackSeed* trkSiSeed  = track -> get_silicon_seed();
      TrackSeed* trkTpcSeed = track -> get_tpc_seed();

      // check if one or both seeds are present as needed
      bool isSeedGood = (trkSiSeed && trkTpcSeed);
      if (!requireSiSeeds) {
        isSeedGood = (trkSiSeed || trkTpcSeed);
      }
      return isSeedGood;

    }  // end 'IsGoodSeed(SvtxTrack*)'



    bool IsFromPrimaryVtx(SvtxTrack* track, PHCompositeNode* topNode) {

      // get id of vertex associated with track
      const int vtxID = (int) track -> get_vertex_id();

      // get id of primary vertex
      GlobalVertex* primVtx   = GetGlobalVertex(topNode);
      const int     primVtxID = primVtx -> get_id();

      // check if from vertex and return
      const bool isFromPrimVtx = (vtxID == primVtxID);
      return isFromPrimVtx;

    }  // end 'IsFromPrimaryVtx(SvtTrack*, PHCompsiteNode*)'



    pair<double, double> GetTrackDcaPair(SvtxTrack* track, PHCompositeNode* topNode) {

      // get global vertex and convert to acts vector
      GlobalVertex* sphxVtx = GetGlobalVertex(topNode);
      Acts::Vector3 actsVtx = Acts::Vector3(sphxVtx -> get_x(), sphxVtx -> get_y(), sphxVtx -> get_z());

      // return dca
      const auto dcaAndErr = TrackAnalysisUtils::get_dca(track, actsVtx);
      return make_pair(dcaAndErr.first.first, dcaAndErr.second.first);

    }  // end 'GetTrackDcaPair(SvtxTrack*, PHCompositeNode*)'



    ROOT::Math::XYZVector GetTrackVertex(SvtxTrack* track, PHCompositeNode* topNode) {

      // get vertex associated with track
      const int     vtxID = (int) track -> get_vertex_id();
      GlobalVertex* vtx   = GetGlobalVertex(topNode, vtxID);

      // return vertex 3-vector
      ROOT::Math::XYZVector xyzVtx = ROOT::Math::XYZVector(vtx -> get_x(), vtx -> get_y(), vtx -> get_z());
      return xyzVtx;

    }  // end 'GetTrackVertex(SvtxTrack*, PHCompositeNode*)'



    double GetTrackDeltaPt(SvtxTrack* track) {

      // grab covariances
      const float trkCovXX = track -> get_error(3, 3);
      const float trkCovXY = track -> get_error(3, 4);
      const float trkCovYY = track -> get_error(4, 4);

      // grab momentum
      const float trkPx = track -> get_px();
      const float trkPy = track -> get_py();
      const float trkPt = track -> get_pt();
 
      // calculate delta-pt
      const float numer    = (trkCovXX * trkPx * trkPx) + 2 * (trkCovXY * trkPx * trkPy) + (trkCovYY * trkPy * trkPy);
      const float denom    = (trkPx * trkPx) + (trkPy * trkPy); 
      const float ptDelta2 = numer / denom;
      const float ptDelta  = sqrt(ptDelta2) / trkPt;
      return ptDelta;

    }  // end 'GetTrackDeltaPt(SvtxTrack*)'



    TrackSeed* GetTrackSeed(SvtxTrack* track, const uint8_t sys) {

      // get both track seeds
      TrackSeed* trkSiSeed  = track -> get_silicon_seed();
      TrackSeed* trkTpcSeed = track -> get_tpc_seed();

      // select relevant seed
      const bool hasBothSeeds   = (trkSiSeed  && trkTpcSeed);
      const bool hasOnlyTpcSeed = (!trkSiSeed && trkTpcSeed);

      TrackSeed* seed = NULL;
      switch (sys) {
        case Subsys::Mvtx:
          if (hasBothSeeds)   seed = trkSiSeed;
          if (hasOnlyTpcSeed) seed = trkTpcSeed;
          break;
        case Subsys::Intt:
          if (hasBothSeeds)   seed = trkSiSeed;
          if (hasOnlyTpcSeed) seed = trkTpcSeed;
          break;
        case Subsys::Tpc:
          seed = trkTpcSeed;
          break;
        default:
          seed = NULL;
          break;
      }
      return seed;

    }  // end 'GetTrackSeed(SvtxTrack*, uint8_t)'



    int GetNumLayer(SvtxTrack* track, const uint8_t sys = 0) {

      // grab track seed
      TrackSeed* seed = GetTrackSeed(track, sys);

      // set min no. of layers
      const int minInttLayer = NMvtxLayer;
      const int minTpcLayer  = NMvtxLayer + NInttLayer;

      // initialize hit flags
      array<bool, NMvtxLayer> isMvtxLayerHit = {false};
      array<bool, NInttLayer> isInttLayerHit = {false};
      array<bool, NTpcLayer>  isTpcLayerHit  = {false};

      // determine which layers were hit
      unsigned int layer     = 0;
      unsigned int mvtxLayer = 0;
      unsigned int inttLayer = 0;
      unsigned int tpcLayer  = 0;
      for (auto itClustKey = (seed -> begin_cluster_keys()); itClustKey != (seed -> end_cluster_keys()); ++itClustKey) {

        // grab layer number
        layer = TrkrDefs::getLayer(*itClustKey);

        // increment accordingly
        switch (sys) {
          case Subsys::Mvtx:
            if (layer < NMvtxLayer) {
              mvtxLayer                 = layer;
              isMvtxLayerHit[mvtxLayer] = true;
            }
            break;
          case Subsys::Intt:
            if ((layer >= minInttLayer) && (layer < minTpcLayer)) {
              inttLayer                 = layer - minInttLayer;
              isInttLayerHit[inttLayer] = true;
            }
            break;
          case Subsys::Tpc:
            if (layer >= minTpcLayer) {
              tpcLayer                = layer - minTpcLayer;
              isTpcLayerHit[tpcLayer] = true;
            }
            break;
          default:
            break;
        }
      }  // end cluster loop

      // get the relevant no. of layers
      int nLayer = 0;
      switch (sys) {
        case Subsys::Mvtx:
          for (int iMvtxLayer = 0; iMvtxLayer < NMvtxLayer; iMvtxLayer++) {
            if (isMvtxLayerHit[iMvtxLayer]) ++nLayer;
          }
          break;
        case Subsys::Intt:
          for (int iInttLayer = 0; iInttLayer < NInttLayer; iInttLayer++) {
            if (isInttLayerHit[iInttLayer]) ++nLayer;
          }
          break;
        case Subsys::Tpc:
          for (int iTpcLayer = 0; iTpcLayer < NTpcLayer; iTpcLayer++) {
            if (isTpcLayerHit[iTpcLayer]) ++nLayer;
          }
          break;
        default:
          break;
      }
      return nLayer;

    }  // end 'GetNumLayer(SvtxTrack*, uint8_t)'



    int GetNumClust(SvtxTrack* track, const uint8_t sys = 0) {

      // grab track seed
      TrackSeed* seed = GetTrackSeed(track, sys);

      // set min no. of layers
      const int minInttLayer = NMvtxLayer;
      const int minTpcLayer  = NMvtxLayer + NInttLayer;

      // determine no. of clusters for a given layer
      unsigned int layer    = 0;
      unsigned int nCluster = 0;
      for (auto itClustKey = (seed -> begin_cluster_keys()); itClustKey != (seed -> end_cluster_keys()); ++itClustKey) {

        // grab layer number
        layer = TrkrDefs::getLayer(*itClustKey);

        // increment accordingly
        switch (sys) {
          case Subsys::Mvtx:
            if (layer < NMvtxLayer) {
              ++nCluster;
            }
            break;
          case Subsys::Intt:
            if ((layer >= minInttLayer) && (layer < minTpcLayer)) {
              ++nCluster;
            }
            break;
          case Subsys::Tpc:
            if (layer >= minTpcLayer) {
              ++nCluster;
            }
            break;
          default:
            break;
        }
      }  // end cluster loop
      return nCluster;

    }  // end 'GetNumClust(SvtxTrack*, uint8_t)'



    int GetMatchID(SvtxTrack* track, SvtxTrackEval* trackEval) {

      // get best match from truth particles
      PHG4Particle* bestMatch = trackEval -> max_truth_particle_by_nclusters(track);

      // grab barcode of best match
      int matchID;
      if (bestMatch) {
        matchID = bestMatch -> get_barcode();
      } else {
        matchID = -1;
      }
      return matchID;

    }  // end 'GetMatchID(SvtxTrack*)'

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
