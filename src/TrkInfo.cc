// ----------------------------------------------------------------------------
// 'TrkInfo.cc'
// Derek Anderson
// 03.05.2024
//
// Utility class to hold information from tracks.
// ----------------------------------------------------------------------------

#define SCORRELATORUTILITIES_TRKINFO_CC

// class definition
#include "TrkInfo.h"

// make comon namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // internal methods ---------------------------------------------------------

  void Types::TrkInfo::Minimize() {

    id         = numeric_limits<int>::min();
    nMvtxLayer = numeric_limits<int>::min();
    nInttLayer = numeric_limits<int>::min();
    nTpcLayer  = numeric_limits<int>::min();
    nMvtxClust = numeric_limits<int>::min();
    nInttClust = numeric_limits<int>::min();
    nTpcClust  = numeric_limits<int>::min();
    eta        = numeric_limits<double>::min();
    phi        = numeric_limits<double>::min();
    px         = numeric_limits<double>::min();
    py         = numeric_limits<double>::min();
    pz         = numeric_limits<double>::min();
    pt         = numeric_limits<double>::min();
    ene        = numeric_limits<double>::min();
    dcaXY      = numeric_limits<double>::min();
    dcaZ       = numeric_limits<double>::min();
    ptErr      = numeric_limits<double>::min();
    quality    = numeric_limits<double>::min();
    vx         = numeric_limits<double>::min();
    vy         = numeric_limits<double>::min();
    vz         = numeric_limits<double>::min();
    return;

  }  // end 'Minimize()'



  void Types::TrkInfo::Maximize() {

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
    vx         = numeric_limits<double>::max();
    vy         = numeric_limits<double>::max();
    vz         = numeric_limits<double>::max();
    return;

  }  // end 'Maximize()'


  // public methods -----------------------------------------------------------

  void Types::TrkInfo::Reset() {

    Maximize();
    return;

  }  // end 'Reset()'



  void Types::TrkInfo::SetInfo(SvtxTrack* track, PHCompositeNode* topNode) {

    // do relevant calculations
    const ROOT::Math::XYZVector trkVtx     = Tools::GetTrackVertex(track, topNode);
    const pair<double, double>  trkDcaPair = Tools::GetTrackDcaPair(track, topNode);

    // set track info
    id         = track -> get_id();
    quality    = track -> get_quality();
    eta        = track -> get_eta();
    phi        = track -> get_phi();
    px         = track -> get_px();
    py         = track -> get_py();
    pz         = track -> get_pz();
    pt         = track -> get_pt();
    ene        = sqrt((px * px) + (py * py) + (pz * pz) + (Const::MassPion() * Const::MassPion()));
    vx         = trkVtx.x();
    vy         = trkVtx.y();
    vz         = trkVtx.z();
    dcaXY      = trkDcaPair.first;
    dcaZ       = trkDcaPair.second;
    nMvtxLayer = Tools::GetNumLayer(track, Const::Subsys::Mvtx);
    nInttLayer = Tools::GetNumLayer(track, Const::Subsys::Intt);
    nTpcLayer  = Tools::GetNumLayer(track, Const::Subsys::Tpc);
    nMvtxClust = Tools::GetNumClust(track, Const::Subsys::Mvtx);
    nInttClust = Tools::GetNumClust(track, Const::Subsys::Intt);
    nTpcClust  = Tools::GetNumClust(track, Const::Subsys::Tpc);
    ptErr      = Tools::GetTrackDeltaPt(track);
    return;

  }  // end 'SetInfo(SvtxTrack*, PHCompositeNode*)'



  bool Types::TrkInfo::IsInAcceptance(const TrkInfo& minimum, const TrkInfo& maximum) {

    return ((*this >= minimum) && (*this <= maximum));

  }  // end 'IsInAcceptance(TrkInfo&, TrkInfo&)'



  bool Types::TrkInfo::IsInAcceptance(const pair<TrkInfo, TrkInfo>& range) {

    return ((*this >= range.first) && (*this <= range.second));

  }  // end 'IsInAcceptance(pair<TrkInfo, TrkInfo>&)'



  bool Types::TrkInfo::IsInSigmaDcaCut(
    const pair<float, float> nSigCut,
    const pair<float, float> ptFitMax,
    const pair<TF1*, TF1*> fSigmaDca
  ) {

    // if above max pt used to fit dca width, use value of fit at max pt
    const double ptEvalXY = (pt > ptFitMax.first)  ? ptFitMax.first  : pt;
    const double ptEvalZ  = (pt > ptFitMax.second) ? ptFitMax.second : pt;

    // check if dca is in cut
    const bool isInDcaRangeXY  = (abs(dcaXY) < (nSigCut.first  * (fSigmaDca.first  -> Eval(ptEvalXY))));
    const bool isInDcaRangeZ   = (abs(dcaZ)  < (nSigCut.second * (fSigmaDca.second -> Eval(ptEvalZ))));
    const bool isInSigmaDcaCut = (isInDcaRangeXY && isInDcaRangeZ);
    return isInSigmaDcaCut;

  }  // end 'IsInSigmaDcaCut(pair<float, float>, pair<float, float>, pair<TF1*, TF1*>)'



  // static methods -----------------------------------------------------------

  vector<string> Types::TrkInfo::GetListOfMembers() {

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
      "vx",
      "vy",
      "vz"
    };
    return members;

  }  // end 'GetListOfMembers()'



  // overloaded operators -----------------------------------------------------

  bool Types::operator <(const TrkInfo& lhs, const TrkInfo& rhs) {

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
      (lhs.vx         < rhs.vx)         &&
      (lhs.vy         < rhs.vy)         &&
      (lhs.vz         < rhs.vz)
    );
    return isLessThan;

  }  // end 'operator <(TrkInfo&, TrkInfo&)'



  bool Types::operator >(const TrkInfo& lhs, const TrkInfo& rhs) {

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
      (lhs.vx         > rhs.vx)         &&
      (lhs.vy         > rhs.vy)         &&
      (lhs.vz         > rhs.vz)
    );
    return isGreaterThan;

  }  // end 'operator >(TrkInfo&, TrkInfo&)'



  bool Types::operator <=(const TrkInfo& lhs, const TrkInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isLessThanOrEqualTo = (
      (lhs.nMvtxLayer <= rhs.nMvtxLayer) &&
      (lhs.nInttLayer <= rhs.nInttLayer) &&
      (lhs.nTpcLayer  <= rhs.nTpcLayer)  &&
      (lhs.nMvtxClust <= rhs.nMvtxClust) &&
      (lhs.nInttClust <= rhs.nInttClust) &&
      (lhs.nTpcClust  <= rhs.nTpcClust)  &&
      (lhs.eta        <= rhs.eta)        &&
      (lhs.phi        <= rhs.phi)        &&
      (lhs.px         <= rhs.px)         &&
      (lhs.py         <= rhs.py)         &&
      (lhs.pz         <= rhs.pz)         &&
      (lhs.pt         <= rhs.pt)         &&
      (lhs.ene        <= rhs.ene)        &&
      (lhs.dcaXY      <= rhs.dcaXY)      &&
      (lhs.dcaZ       <= rhs.dcaZ)       &&
      (lhs.ptErr      <= rhs.ptErr)      &&
      (lhs.quality    <= rhs.quality)    &&
      (lhs.vx         <= rhs.vx)         &&
      (lhs.vy         <= rhs.vy)         &&
      (lhs.vz         <= rhs.vz)
    );
    return isLessThanOrEqualTo;

  }  // end 'operator <(TrkInfo&, TrkInfo&)'



  bool Types::operator >=(const TrkInfo& lhs, const TrkInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isGreaterThanOrEqualTo = (
      (lhs.nMvtxLayer >= rhs.nMvtxLayer) &&
      (lhs.nInttLayer >= rhs.nInttLayer) &&
      (lhs.nTpcLayer  >= rhs.nTpcLayer)  &&
      (lhs.nMvtxClust >= rhs.nMvtxClust) &&
      (lhs.nInttClust >= rhs.nInttClust) &&
      (lhs.nTpcClust  >= rhs.nTpcClust)  &&
      (lhs.eta        >= rhs.eta)        &&
      (lhs.phi        >= rhs.phi)        &&
      (lhs.px         >= rhs.px)         &&
      (lhs.py         >= rhs.py)         &&
      (lhs.pz         >= rhs.pz)         &&
      (lhs.pt         >= rhs.pt)         &&
      (lhs.ene        >= rhs.ene)        &&
      (lhs.dcaXY      >= rhs.dcaXY)      &&
      (lhs.dcaZ       >= rhs.dcaZ)       &&
      (lhs.ptErr      >= rhs.ptErr)      &&
      (lhs.quality    >= rhs.quality)    &&
      (lhs.vx         >= rhs.vx)         &&
      (lhs.vy         >= rhs.vy)         &&
      (lhs.vz         >= rhs.vz)
    );
    return isGreaterThanOrEqualTo;

  }  // end 'operator >(TrkInfo&, TrkInfo&)'



  // ctor/dtor ----------------------------------------------------------------

  Types::TrkInfo::TrkInfo() {

    /* nothing to do */

  }  // end ctor()



  Types::TrkInfo::~TrkInfo() {

    /* nothing to do */

  }  // end dtor()



  Types::TrkInfo::TrkInfo(const Const::Init init) {

    switch (init) {
      case Const::Init::Minimize:
        Minimize();
        break;
      case Const::Init::Maximize:
        Maximize();
        break;
      default:
        Maximize();
        break;
    }

  }  // end ctor(Const::init)



  Types::TrkInfo::TrkInfo(SvtxTrack* track, PHCompositeNode* topNode) {

    SetInfo(track, topNode);

  }  // end ctor(SvtxTrack*, PHCompositeNode*)'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
