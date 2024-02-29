// ----------------------------------------------------------------------------
// 'TrkTools.cc'
// Derek Anderson
// 02.29.2024
//
// Definition of TrkInfo class and collection of frequent track-
// related methods utilized in the sPHENIX Cold QCD Energy-Energy
// Correlator analysis.
// ----------------------------------------------------------------------------

#define TRKTOOLS_CC

// c++ utilities
#include <array>
#include <limits>
#include <string>
#include <vector>
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
// phenix Geant4 utilities
#include <g4main/PHG4Particle.h>
// analysis utilities
#include "TrkTools.h"
#include "VtxTools.h"
#include "Constants.h"

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {

  // track methods ----------------------------------------------------------

  SvtxTrackMap* SCorrelatorUtilities::GetTrackMap(PHCompositeNode* topNode) {

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



  bool SCorrelatorUtilities::IsInAcceptance(const TrkInfo& trk, const TrkInfo& minimum, const TrkInfo& maximum) {

    return ((trk >= minimum) && (trk <= maximum));

  }  // end 'IsInAcceptance(TrkInfo&, TrkInfo&, TrkInfo&)'



  bool SCorrelatorUtilities::IsInSigmaDcaCut(const TrkInfo& trk, const pair<float, float> nSigCut, const pair<float, float> ptFitMax, const pair<TF1*, TF1*> fSigmaDca) {

    // if above max pt used to fit dca width, use value of fit at max pt
    const double ptEvalXY = (trk.pt > ptFitMax.first)  ? ptFitMax.first  : trk.pt;
    const double ptEvalZ  = (trk.pt > ptFitMax.second) ? ptFitMax.second : trk.pt;

    // check if dca is in cut
    const bool isInDcaRangeXY  = (abs(trk.dcaXY) < (nSigCut.first  * (fSigmaDca.first  -> Eval(ptEvalXY))));
    const bool isInDcaRangeZ   = (abs(trk.dcaZ)  < (nSigCut.second * (fSigmaDca.second -> Eval(ptEvalZ))));
    const bool isInSigmaDcaCut = (isInDcaRangeXY && isInDcaRangeZ);
    return isInSigmaDcaCut;

  }  // end 'IsInSigmaDcaCut(TrkInfo&, pair<float, float>, pair<float, float>, pair<TF1*, TF1*>)'



  bool SCorrelatorUtilities::IsGoodTrackSeed(SvtxTrack* track, const bool requireSiSeeds) {

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



  bool SCorrelatorUtilities::IsFromPrimaryVtx(SvtxTrack* track, PHCompositeNode* topNode) {

    // get id of vertex associated with track
    const int vtxID = (int) track -> get_vertex_id();

    // get id of primary vertex
    GlobalVertex* primVtx   = GetGlobalVertex(topNode);
    const int     primVtxID = primVtx -> get_id();

    // check if from vertex and return
    const bool isFromPrimVtx = (vtxID == primVtxID);
    return isFromPrimVtx;

  }  // end 'IsFromPrimaryVtx(SvtTrack*, PHCompsiteNode*)'



  pair<double, double> SCorrelatorUtilities::GetTrackDcaPair(SvtxTrack* track, PHCompositeNode* topNode) {

    // get global vertex and convert to acts vector
    GlobalVertex* sphxVtx = GetGlobalVertex(topNode);
    Acts::Vector3 actsVtx = Acts::Vector3(sphxVtx -> get_x(), sphxVtx -> get_y(), sphxVtx -> get_z());

    // return dca
    const auto dcaAndErr = TrackAnalysisUtils::get_dca(track, actsVtx);
    return make_pair(dcaAndErr.first.first, dcaAndErr.second.first);

  }  // end 'GetTrackDcaPair(SvtxTrack*, PHCompositeNode*)'



  ROOT::Math::XYZVector SCorrelatorUtilities::GetTrackVertex(SvtxTrack* track, PHCompositeNode* topNode) {

    // get vertex associated with track
    const int     vtxID = (int) track -> get_vertex_id();
    GlobalVertex* vtx   = GetGlobalVertex(topNode, vtxID);

    // return vertex 3-vector
    ROOT::Math::XYZVector xyzVtx = ROOT::Math::XYZVector(vtx -> get_x(), vtx -> get_y(), vtx -> get_z());
    return xyzVtx;

  }  // end 'GetTrackVertex(SvtxTrack*, PHCompositeNode*)'



  double SCorrelatorUtilities::GetTrackDeltaPt(SvtxTrack* track) {

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



  TrackSeed* SCorrelatorUtilities::GetTrackSeed(SvtxTrack* track, const uint8_t sys) {

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



  int SCorrelatorUtilities::GetNumLayer(SvtxTrack* track, const uint8_t sys) {

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



  int SCorrelatorUtilities::GetNumClust(SvtxTrack* track, const uint8_t sys) {

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



  int SCorrelatorUtilities::GetMatchID(SvtxTrack* track, SvtxTrackEval* trackEval) {

    // get best match from truth particles
    PHG4Particle* bestMatch = trackEval -> max_truth_particle_by_nclusters(track);

    // grab barcode of best match
    int matchID;
    if (bestMatch) {
      matchID = bestMatch -> get_barcode();
    } else {
      matchID = numeric_limits<int>::max();
    }
    return matchID;

  }  // end 'GetMatchID(SvtxTrack*)'

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
