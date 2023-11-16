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
#include <cassert>
#include <utilities>
// root utilities
#include <TF1.h>
// f4a libraries
#include <fun4all/SubsysReco.h>
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
// analysis utilities
#include "SCorrelatorUtilites.Constants.h"

// make common namespaces implicit
using namespace std;
using namespace findNode;

// set up aliases
using CLVec3  = CLHEP::Hep3Vector;  // FIXME replace CLHEP vectors with ROOT XYZVectors
using DcaPair = pair<double, double>;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

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
        const CLVec3  trkVtx     = GetTrackVertex(track, topNode);
        const DcaPair trkDcaPair = GetTrackDcaPair(track, topNode);

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
      inline bool operator<=(const TrkInfo& lhs, const TrkInfo& rhs) {return !(lhs > rhs);}
      inline bool operator>=(const TrkInfo& lhs, const TrkInfo& rhs) {return !(rhs < lhs);}

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
      const double ptEvalXY = (trk.pt > ptFitMax.first)  ? ptFitMax : trkPt;
      const double ptEvalZ  = (trk.pt > ptFitMax.second) ? ptFitMax : trkPt;

      // check if dca is in cut
      const bool isInDcaRangeXY  = (abs(trk.dcaXY) < (nSigCut.first  * (fSigmaDca.first  -> Eval(ptEvalXY))));
      const bool isInDcaRangeZ   = (abs(trk.dcaZ)  < (nSigcut.second * (fSigmaDca.second -> Eval(ptEvalZ))));
      const bool isInSigmaDcaCut = (isInDcaRangeXY && isInDcaRangeZ);
      return isInSigmaDcaCut;

    }  // end 'IsInSigmaDcaCut(TrkInfo&, pair<float, float>, pair<float, float>, pair<TF1*, TF1*>)'



    bool IsGoodTrackSeed(const SvtxTrack* track, const bool requireSiSeeds = true) {

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



    /* TODO
     *   - remove/factorize out blocks specific to SCorrelatorJetTree
     */ 
    bool IsGoodTrackPhi(SvtxTrack* track, const float phiMaskSize) {

      // Tpc sector boundaries:
      //   12 sectors --> ~0.523 rad/sector,
      //   assumed to be symmetric about phi = 0
      // FIXME move to constant in utilities namespace
      const array<float, NTpcSector> phiSectorBoundaries = {
        -2.877,
        -2.354,
        -1.831,
        -1.308,
        -0.785,
        -0.262,
        0.262,
        0.785,
        1.308,
        1.831,
        2.354,
        2.877
      };

      // flag phi as bad if within boundary +- (phiMaskSize / 2)
      const double halfMaskSize = phiMaskSize / 2.;
      const double trkPhi       = track -> get_phi();

      // loop over sector boundaries and check phi
      bool isGoodPhi = true;
      for (const float boundary : phiSectorBoundaries) {
        if ((trkPhi > (boundary - halfMaskSize)) && (trkPhi < (boundary + halfMaskSize))) {
          isGoodPhi = false;
          break;
        }
      }
      return isGoodPhi;

    }  // end 'IsGoodTrackPhi(SvtxTrack*, float)'



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



    // FIXME replace CLHEP vectors with ROOT GenVectors
    CLHEP::Hep3Vector GetTrackVertex(SvtxTrack* track, PHCompositeNode* topNode) {

      // get vertex associated with track
      const int     vtxID = (int) track -> get_vertex_id();
      GlobalVertex* vtx   = GetGlobalVertex(topNode, vtxID);

      // return vertex 3-vector
      CLHEP::Hep3Vector hepVecVtx = CLHEP::Hep3Vector(vtx -> get_x(), vtx -> get_y(), vtx -> get_z());
      return hepVecVtx;

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



    /* TODO
     *   - refactor/clean up
     *   - remove/factorize out blocks specific to SCorrelatorJetTree
     */
    int GetNumLayer(SvtxTrack* track, const Subsys sys) {

      // issue warning if sys is not set correctly
      const bool isSubsysWrong = (sys > 2);
      if (isSubsysWrong && m_doDebug && (Verbosity() > 3)) {
        cerr << "GetNumLayer(SvtxTrack*, uint8_t) PANIC: trying to determine no. of clusters for an unknown system (sys = " << sys << ")! Aborting!" << endl;
        assert(sys <= 2);
      }

      // check if seed is good
      const bool isSeedGood = IsGoodTrackSeed(track);
      if (!isSeedGood && m_doDebug && (Verbosity() > 3)) {
        cerr << "GetNumLayer(SvtxTrack*, uint8_t) PANIC: track seed(s) is (are) no good! Aborting!" << endl;
        assert(isSeedGood);
      }

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
      }
      if (!seed && m_doDebug && (Verbosity() > 3)) {
        cerr << "GetNumLayer(SvtxTrack*, uint8_t) PANIC: couldn't set seed! Aborting!" << endl;
        assert(seed);
      }

      // set min no. of layers
      const int minInttLayer = CONST::NMvtxLayer;
      const int minTpcLayer  = CONST::NMvtxLayer + CONST::NInttLayer;

      // reset hit flags
      switch (sys) {
        case Subsys::Mvtx:
          for (int iMvtxLayer = 0; iMvtxLayer < CONST::NMvtxLayer; iMvtxLayer++) {
            isMvtxLayerHit[iMvtxLayer] = false;
          }
          break;
        case Subsys::Intt:
          for (int iInttLayer = 0; iInttLayer < CONST::NInttLayer; iInttLayer++) {
            isInttLayerHit[iInttLayer] = false;
          }
          break;
        case Subsys::Tpc:
          for (int iTpcLayer = 0; iTpcLayer < CONST::NTpcLayer; iTpcLayer++) {
            isTpcLayerHit[iTpcLayer] = false;
          }
          break;
      }

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
            if (layer < CONST::NMvtxLayer) {
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
        }
      }  // end cluster loop

      // get the relevant no. of layers
      int nLayer = 0;
      switch (sys) {
        case Subsys::Mvtx:
          for (int iMvtxLayer = 0; iMvtxLayer < CONST::NMvtxLayer; iMvtxLayer++) {
            if (isMvtxLayerHit[iMvtxLayer]) ++nLayer;
          }
          break;
        case Subsys::Intt:
          for (int iInttLayer = 0; iInttLayer < CONST::NInttLayer; iInttLayer++) {
            if (isInttLayerHit[iInttLayer]) ++nLayer;
          }
          break;
        case Subsys::Tpc:
          for (int iTpcLayer = 0; iTpcLayer < CONST::NTpcLayer; iTpcLayer++) {
            if (isTpcLayerHit[iTpcLayer]) ++nLayer;
          }
          break;
      }
      return nLayer;

    }  // end 'GetNumLayer(SvtxTrack*, uint8_t)'



    /* TODO
     *   - refactor/clean up
     *   - remove/factorize out blocks specific to SCorrelatorJetTree
     */
    int GetNumClust(SvtxTrack* track, const uint8_t subsys = 0) {

      // issue warning if subsys is not set correctly
      const bool isSubsysWrong = (subsys > 2);
      if (isSubsysWrong && m_doDebug && (Verbosity() > 3)) {
        cerr << "GetNumLClust(SvtxTrack*, uint8_t) PANIC: trying to determine no. of clusters for an unknown subsystem (subsys = " << subsys << ")! Aborting!" << endl;
        assert(subsys <= 2);
      }

      // check if seed is good
      const bool isSeedGood = IsGoodTrackSeed(track);
      if (!isSeedGood && m_doDebug && (Verbosity() > 3)) {
        cerr << "GetNumLayer(SvtxTrack*, uint8_t) PANIC: track seed(s) is (are) no good! Aborting!" << endl;
        assert(isSeedGood);
      }

      // get both track seeds
      TrackSeed* trkSiSeed  = track -> get_silicon_seed();
      TrackSeed* trkTpcSeed = track -> get_tpc_seed();

      // select relevant seed
      const bool hasBothSeeds   = (trkSiSeed  && trkTpcSeed);
      const bool hasOnlyTpcSeed = (!trkSiSeed && trkTpcSeed);

      TrackSeed* seed = NULL;
      switch (subsys) {
        case SUBSYS::MVTX:
          if (hasBothSeeds)   seed = trkSiSeed;
          if (hasOnlyTpcSeed) seed = trkTpcSeed;
          break;
        case SUBSYS::INTT:
          if (hasBothSeeds)   seed = trkSiSeed;
          if (hasOnlyTpcSeed) seed = trkTpcSeed;
          break;
        case SUBSYS::TPC:
          seed = trkTpcSeed;
          break;
      }
      if (!seed && m_doDebug && (Verbosity() > 3)) {
        cerr << "GetNumClust(SvtxTrack*, uint8_t) PANIC: couldn't set seed! Aborting!" << endl;
        assert(seed);
      }

      // set min no. of layers
      const int minInttLayer = CONST::NMvtxLayer;
      const int minTpcLayer  = CONST::NMvtxLayer + CONST::NInttLayer;

      // determine no. of clusters for a given layer
      unsigned int layer    = 0;
      unsigned int nCluster = 0;
      for (auto itClustKey = (seed -> begin_cluster_keys()); itClustKey != (seed -> end_cluster_keys()); ++itClustKey) {

        // grab layer number
        layer = TrkrDefs::getLayer(*itClustKey);

        // increment accordingly
        switch (subsys) {
          case SUBSYS::MVTX:
            if (layer < CONST::NMvtxLayer) {
              ++nCluster;
            }
            break;
          case SUBSYS::INTT:
            if ((layer >= minInttLayer) && (layer < minTpcLayer)) {
              ++nCluster;
            }
            break;
          case SUBSYS::TPC:
            if (layer >= minTpcLayer) {
              ++nCluster;
            }
            break;
        }
      }  // end cluster loop
      return nCluster;

    }  // end 'GetNumClust(SvtxTrack*, uint8_t)'



    int GetMatchID(SvtxTrack* track) {

      // get best match from truth particles
      PHG4Particle* bestMatch = m_trackEval -> max_truth_particle_by_nclusters(track);

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
