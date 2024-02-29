// ----------------------------------------------------------------------------
// 'EvtTools.h'
// Derek Anderson
// 10.30.2023
//
// Collection of frequent event-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#ifndef EVTTOOLS_H
#define EVTTOOLS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// c++ utilities
#include <limits>
#include <string>
#include <vector>
#include <optional>
// root libraries
#include <Math/Vector3D.h>
// phool libraries
#include <phool/PHCompositeNode.h>
// tracking includes
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
// analysis utilities
//#include "Constants.h"
#include "Interfaces.h"
#include "GenTools.h"

#pragma GCC diagnostic pop

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // forward declarations used in Reco/GenInfo
    long                  GetNumTrks(PHCompositeNode* topNode);
    long                  GetNumFinalStatePars(PHCompositeNode* topNode, const vector<int> evtsToGrab, const int subset = 0, optional<float> chargeToGrab = nullopt);
    double                GetSumTrkMomentum(PHCompositeNode* topNode);
    double                GetSumCaloEne(PHCompositeNode* topNode, const string store);
    double                GetSumFinalStateParEne(PHCompositeNode* topNode, const vector<int> evtsToGrab, const int subset, optional<float> chargeToGrab = nullopt);
    ParInfo               GetPartonInfo(PHCompositeNode* topNode, const int event, const int status);
    ROOT::Math::XYZVector GetRecoVtx(PHCompositeNode* topNode);

    // RecoInfo definition ----------------------------------------------------

    struct RecoInfo {

      // data members
      int    nTrks     = numeric_limits<int>::max();
      double pSumTrks  = numeric_limits<double>::max();
      double eSumEMCal = numeric_limits<double>::max();
      double eSumIHCal = numeric_limits<double>::max();
      double eSumOHCal = numeric_limits<double>::max();
      double vx        = numeric_limits<double>::max();
      double vy        = numeric_limits<double>::max();
      double vz        = numeric_limits<double>::max();
      double vr        = numeric_limits<double>::max();

      void SetInfo(PHCompositeNode* topNode) {

        // get sums
        nTrks     = GetNumTrks(topNode);
        pSumTrks  = GetSumTrkMomentum(topNode);
        eSumEMCal = GetSumCaloEne(topNode, "CLUSTER_CEMC");
        eSumIHCal = GetSumCaloEne(topNode, "CLUSTER_HCALIN");
        eSumOHCal = GetSumCaloEne(topNode, "CLUSTER_HCALOUT");

        // get vertex
        ROOT::Math::XYZVector vtx = GetRecoVtx(topNode);
        vx = vtx.x();
        vy = vtx.y();
        vz = vtx.z();
        vr = hypot(vx, vy);
        return;
      }  // end 'SetInfo(PHCompositeNode*)'

      void Reset() {
        nTrks     = numeric_limits<int>::max();
        pSumTrks  = numeric_limits<double>::max();
        eSumEMCal = numeric_limits<double>::max();
        eSumIHCal = numeric_limits<double>::max();
        eSumOHCal = numeric_limits<double>::max();
        vx        = numeric_limits<double>::max();
        vy        = numeric_limits<double>::max();
        vz        = numeric_limits<double>::max();
        vr        = numeric_limits<double>::max();
        return;
      }  // end 'Reset()'

      static vector<string> GetListOfMembers() {
        vector<string> members = {
          "nTrks",
          "pSumTrks",
          "eSumEMCal",
          "eSumIHCal",
          "eSumOHCal",
          "vx",
          "vy",
          "vz",
          "vr"
        };
        return members;
      }  // end 'GetListOfMembers()'

      // default ctor/dtor
      RecoInfo()  {};
      ~RecoInfo() {};

      // ctor accepting PHCompositeNode*
      RecoInfo(PHCompositeNode* topNode) {
        SetInfo(topNode);
      };

    };  // end RecoInfo definition



    // GenInfo definition ------------------------------------------------------

    struct GenInfo {

      // atomic data members
      int    nChrgPar = numeric_limits<int>::max();
      int    nNeuPar  = numeric_limits<int>::max();
      bool   isEmbed  = false;
      double eSumChrg = numeric_limits<double>::max();
      double eSumNeu  = numeric_limits<double>::max();

      // hard scatter products
      pair<ParInfo, ParInfo> partons;

      void SetInfo(PHCompositeNode* topNode, const bool embed, const vector<int> evtsToGrab) {

        // set embed flag
        isEmbed = embed;

        // set parton info
        isEmbed  = embed;
        if (isEmbed) {
          partons.first  = GetPartonInfo(topNode, SubEvt::EmbedSignal, HardScatterStatus::First);
          partons.second = GetPartonInfo(topNode, SubEvt::EmbedSignal, HardScatterStatus::Second);

        } else {
          partons.first  = GetPartonInfo(topNode, SubEvt::NotEmbedSignal, HardScatterStatus::First);
          partons.second = GetPartonInfo(topNode, SubEvt::NotEmbedSignal, HardScatterStatus::Second);
        }

        // get sums
        nChrgPar = GetNumFinalStatePars(topNode, evtsToGrab, Subset::Charged);
        nNeuPar  = GetNumFinalStatePars(topNode, evtsToGrab, Subset::Neutral);
        eSumChrg = GetSumFinalStateParEne(topNode, evtsToGrab, Subset::Charged);
        eSumNeu  = GetSumFinalStateParEne(topNode, evtsToGrab, Subset::Neutral);
        return;
      }  // end 'SetInfo(PHCompositeNode*, vector<int>)'

      void Reset() {
        nChrgPar = numeric_limits<int>::max();
        nNeuPar  = numeric_limits<int>::max();
        isEmbed  = false;
        eSumChrg = numeric_limits<double>::max();
        eSumNeu  = numeric_limits<double>::max();
        return;
      }  // end 'Reset()'

      static vector<string> GetListOfMembers() {
        vector<string> members = {
          "nChrgPar",
          "nNeuPar",
          "isEmbed",
          "eSumChrg",
          "eSumNeu"
        };
        AddLeavesToVector<ParInfo>(members, "PartonA");
        AddLeavesToVector<ParInfo>(members, "PartonB");
        return members;
      }  // end 'GetListOfMembers()'

      // default ctor/dtor
      GenInfo()  {};
      ~GenInfo() {};

      // ctor accepting PHCompositeNode* and list of subevents
      GenInfo(PHCompositeNode* topNode, const bool embed, vector<int> evtsToGrab) {
        SetInfo(topNode, embed, evtsToGrab);
      };
    };  // end GenInfo definition



    // event methods ----------------------------------------------------------

    long GetNumTrks(PHCompositeNode* topNode);
    long GetNumFinalStatePars(PHCompositeNode* topNode, const vector<int> evtsToGrab, const int subset, optional<float> chargeToGrab);
    double GetSumTrkMomentum(PHCompositeNode* topNode);
    double GetSumCaloEne(PHCompositeNode* topNode, const string store);
    double GetSumFinalStateParEne(PHCompositeNode* topNode, const vector<int> evtsToGrab, const int subset, optional<float> chargeToGrab);
    ParInfo GetPartonInfo(PHCompositeNode* topNode, const int event, const int status);

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
