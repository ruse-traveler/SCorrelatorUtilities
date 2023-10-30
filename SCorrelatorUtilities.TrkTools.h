// ----------------------------------------------------------------------------
// 'SCorrelatorUtilities.TrkTools.h'
// Derek Anderson
// 10.30.2023
//
// Collection of frequent track-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

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



    /* TODO
     *   - replace most of this with comparison b/n TrkInfo objects
     *   - remove/factorize out blocks specific to SCorrelatorJetTree
     */ 
    bool IsGoodTrack(SvtxTrack* track, PHCompositeNode* topNode) {

      // grab track info
      const double trkPt      = track -> get_pt();
      const double trkEta     = track -> get_eta();
      const double trkQual    = track -> get_quality();
      const double trkDeltaPt = GetTrackDeltaPt(track);
      const int    trkNMvtx   = GetNumLayer(track, Subsys::Mvtx);
      const int    trkNIntt   = GetNumLayer(track, Subsys::Intt);
      const int    trkNTpc    = GetNumLayer(track, Subsys::Tpc);

      // grab track dca
      const auto   trkDca   = GetTrackDcaPair(track, topNode);
      const double trkDcaXY = trkDca.first;
      const double trkDcaZ  = trkDca.second;


      // if above max pt used to fit dca width,
      // use value of fit at max pt
      double ptEvalXY = (trkPt > m_dcaPtFitMaxXY) ? m_dcaPtFitMaxXY : trkPt;
      double ptEvalZ  = (trkPt > m_dcaPtFitMaxZ)  ? m_dcaPtFitMaxZ  : trkPt;

      // check if dca is good
      bool isInDcaRangeXY = false;
      bool isInDcaRangeZ  = false;
      if (m_doDcaSigmaCut) {
        isInDcaRangeXY = (abs(trkDcaXY) < (m_nSigCutXY * (m_fSigDcaXY -> Eval(ptEvalXY))));
        isInDcaRangeZ  = (abs(trkDcaZ)  < (m_nSigCutZ  * (m_fSigDcaZ  -> Eval(ptEvalZ))));
      } else {
        isInDcaRangeXY = ((trkDcaXY > m_trkDcaRangeXY[0]) && (trkDcaXY < m_trkDcaRangeXY[1]));
        isInDcaRangeZ  = ((trkDcaZ  > m_trkDcaRangeZ[0])  && (trkDcaZ  < m_trkDcaRangeZ[1]));
      }  

      // if applying vertex cuts, grab track
      // vertex and check if good
      bool isInVtxRange = true;
      if (m_doVtxCut) {
        CLHEP::Hep3Vector trkVtx = GetTrackVertex(track, topNode);
        isInVtxRange = IsGoodVertex(trkVtx);
      }

      // if using only primary vertex,
      // ignore tracks from other vertices
      if (m_useOnlyPrimVtx) {
        const bool isFromPrimVtx = IsFromPrimaryVtx(track, topNode);
        if (!isFromPrimVtx) {
          isInVtxRange = false;
        }
      }

      // if masking tpc sector boundaries,
      // ignore tracks near boundaries
      bool isGoodPhi = true;
      if (m_maskTpcSectors) {
        isGoodPhi = IsGoodTrackPhi(track);
      }

      // apply cuts
      const bool isSeedGood       = IsGoodTrackSeed(track);
      const bool isInPtRange      = ((trkPt      > m_trkPtRange[0])      && (trkPt      <  m_trkPtRange[1]));
      const bool isInEtaRange     = ((trkEta     > m_trkEtaRange[0])     && (trkEta     <  m_trkEtaRange[1]));
      const bool isInQualRange    = ((trkQual    > m_trkQualRange[0])    && (trkQual    <  m_trkQualRange[1]));
      const bool isInNMvtxRange   = ((trkNMvtx   > m_trkNMvtxRange[0])   && (trkNMvtx   <= m_trkNMvtxRange[1]));
      const bool isInNInttRange   = ((trkNIntt   > m_trkNInttRange[0])   && (trkNIntt   <= m_trkNInttRange[1]));
      const bool isInNTpcRange    = ((trkNTpc    > m_trkNTpcRange[0])    && (trkNTpc    <= m_trkNTpcRange[1]));
      const bool isInDeltaPtRange = ((trkDeltaPt > m_trkDeltaPtRange[0]) && (trkDeltaPt <  m_trkDeltaPtRange[1]));
      const bool isInNumRange     = (isInNMvtxRange && isInNInttRange && isInNTpcRange);
      const bool isInDcaRange     = (isInDcaRangeXY && isInDcaRangeZ);
      const bool isGoodTrack      = (isSeedGood && isGoodPhi && isInPtRange && isInEtaRange && isInQualRange && isInNumRange && isInDcaRange && isInDeltaPtRange && isInVtxRange);
      return isGoodTrack;

    }  // end 'IsGoodTrack(SvtxTrack*)'



    /* TODO
     *   - remove/factorize out blocks specific to SCorrelatorJetTree
     */ 
    bool IsGoodTrackSeed(SvtxTrack* track) {

      // get track seeds
      TrackSeed* trkSiSeed  = track -> get_silicon_seed();
      TrackSeed* trkTpcSeed = track -> get_tpc_seed();

      // check if one or both seeds are present as needed
      bool isSeedGood = (trkSiSeed && trkTpcSeed);
      if (!m_requireSiSeeds) {
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
      PHG4Particle *bestMatch = m_trackEval -> max_truth_particle_by_nclusters(track);

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
