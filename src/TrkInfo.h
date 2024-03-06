// ----------------------------------------------------------------------------
// 'TrkInfo.h'
// Derek Anderson
// 03.05.2024
//
// Utility class to hold information from tracks.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_TRKINFO_H
#define SCORRELATORUTILITIES_TRKINFO_H

// c++ utilities
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <utility>
// root libraries
#include <TF1.h>
#include <Rtypes.h>
#include <Math/Vector3D.h>
// phool libraries
#include <phool/PHCompositeNode.h>
// tracking libraries
#include <trackbase_historic/SvtxTrack.h>
// analysis utilities
#include "Tools.h"
#include "Constants.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // TrkInfo definition -------------------------------------------------------

  class TrkInfo {

    private:

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

      // internal methods
      void Minimize();
      void Maximize();

    public:

      // public methods
      void Reset();
      void SetInfo(SvtxTrack* track, PHCompositeNode* topNode);
      bool IsInAcceptance(const TrkInfo& minimum, const TrkInfo& maximum);
      bool IsInAcceptance(const pair<TrkInfo, TrkInfo>& range);
      bool IsInSigmaDcaCut(const pair<float, float> nSigCut, const pair<float, float> ptFitMax, const pair<TF1*, TF1*> fSigmaDca);

      // static methods
      static vector<string> GetListOfMembers();

      // overloaded operators
      friend bool operator<(const TrkInfo& lhs, const TrkInfo& rhs);
      friend bool operator>(const TrkInfo& lhs, const TrkInfo& rhs);
      friend bool operator<=(const TrkInfo& lhs, const TrkInfo& rhs);
      friend bool operator>=(const TrkInfo& lhs, const TrkInfo& rhs);

      // default ctor/dtor
      TrkInfo();
      ~TrkInfo();

      // ctors accepting arguments
      TrkInfo(const Const::Init init);
      TrkInfo(SvtxTrack* track, PHCompositeNode* topNode);

    // identify this class to ROOT
    ClassDefNV(TrkInfo, 1);

  };  // end TrkInfo def

}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
