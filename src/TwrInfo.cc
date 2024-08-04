/// ---------------------------------------------------------------------------
/*! \file   TwrInfo.cc
 *  \author Derek Anderson
 *  \date   08.04.2024
 *
 *  Utility class to hold information from
 *  calorimeter clusters.
 */
/// ---------------------------------------------------------------------------

#define SCORRELATORUTILITIES_TWRINFO_CC

// class definition
#include "TwrInfo.h"

// make comon namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // private methods ==========================================================

  // --------------------------------------------------------------------------
  //! Set data members to absolute minima
  // --------------------------------------------------------------------------
  void Types::TwrInfo::Minimize() {

    system  = -1 * numeric_limits<int>::max();
    id      = -1 * numeric_limits<int>::max();
    ene     = -1. * numeric_limits<double>::max();
    rho     = -1. * numeric_limits<double>::max();
    eta     = -1. * numeric_limits<double>::max();
    phi     = -1. * numeric_limits<double>::max();
    px      = -1. * numeric_limits<double>::max();
    py      = -1. * numeric_limits<double>::max();
    pz      = -1. * numeric_limits<double>::max();
    rx      = -1. * numeric_limits<double>::max();
    ry      = -1. * numeric_limits<double>::max();
    rz      = -1. * numeric_limits<double>::max();
    return;

  }  // end 'Minimize()'



  // --------------------------------------------------------------------------
  //! Set data members to absolute maxima
  // --------------------------------------------------------------------------
  void Types::TwrInfo::Maximize() {

    system  = numeric_limits<int>::max();
    id      = numeric_limits<int>::max();
    ene     = numeric_limits<double>::max();
    rho     = numeric_limits<double>::max();
    eta     = numeric_limits<double>::max();
    phi     = numeric_limits<double>::max();
    px      = numeric_limits<double>::max();
    py      = numeric_limits<double>::max();
    pz      = numeric_limits<double>::max();
    rx      = numeric_limits<double>::max();
    ry      = numeric_limits<double>::max();
    rz      = numeric_limits<double>::max();
    return;

  }  // end 'Maximize()'



  // public methods ===========================================================

  // --------------------------------------------------------------------------
  //! Reset object by maximizing data members
  // --------------------------------------------------------------------------
  void Types::TwrInfo::Reset() {

    Maximize();
    return;

  }  // end 'Reset()'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A RawTower
  // --------------------------------------------------------------------------
  void Types::TwrInfo::SetInfo(const RawTower* tower, optional<ROOT::Math::XYZVector> vtx, optional<int> sys) {

    // if no vertex provided, use origin
    ROOT::Math::XYZVector vtxToUse(0., 0., 0.);
    if (vtx.has_value()) {
      vtxToUse = vtx.value();
    }

    // if subsystem ID provided, set data member
    if (sys.has_value()) {
      system = sys.value();
    }

    // grab position
    ROOT::Math::XYZVector position(
      tower -> get_position().x(),
      tower -> get_position().y(),
      tower -> get_position().z()
    );

    // grab momentum
    ROOT::Math::PxPyPzEVector momentum = Tools::GetTwrMomentum(tower -> get_energy(), position, vtxToUse);

    // set remaining members
    id   = tower -> get_id();
    ene  = tower -> get_energy();
    rho  = tower -> get_r();
    eta  = momentum.Eta();
    phi  = momentum.Phi();
    px   = momentum.Px();
    py   = momentum.Py();
    pz   = momentum.Pz();
    rx   = position.X();
    ry   = position.Y();
    rz   = position.Z();
    return;

  }  // end 'SetInfo(RawTower*, optional<ROOT::Math::XYZVector>, optional<int>)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A TowerInfo
  // --------------------------------------------------------------------------
  void Types::TwrInfo::SetInfo(const TowerInfo* tower, optional<ROOT::Math::XYZVector> vtx, optional<int> sys) {

    /* TODO fill in */
    return;

  }  // end 'SetInfo(TowerInfo*, optional<ROOT::Math::XYZVector>, optional<int>)'



  // --------------------------------------------------------------------------
  //! Check if object is within provided bounds (explicit minimum, maximum)
  // --------------------------------------------------------------------------
  bool Types::TwrInfo::IsInAcceptance(const TwrInfo& minimum, const TwrInfo& maximum) const {

    return ((*this >= minimum) && (*this <= maximum));

  }  // end 'IsInAcceptance(TwrInfo&, TwrInfo&)'



  // --------------------------------------------------------------------------
  //! Check if object is within provided bounds (set by pair)
  // --------------------------------------------------------------------------
  bool Types::TwrInfo::IsInAcceptance(const pair<TwrInfo, TwrInfo>& range) const {

    return ((*this >= range.first) && (*this <= range.second));

  }  // end 'IsInAcceptance(pair<TwrInfo, TwrInfo>&)'



  // static methods ===========================================================

  // --------------------------------------------------------------------------
  //! Get list of data fields
  // --------------------------------------------------------------------------
  vector<string> Types::TwrInfo::GetListOfMembers() {

    vector<string> members = {
      "sys",
      "id",
      "ene",
      "rho",
      "eta",
      "phi",
      "px",
      "py",
      "pz",
      "rx",
      "ry",
      "rz"
    };
    return members;

  }  // end 'GetListOfMembers()'



  // overloaded operators =====================================================

  // --------------------------------------------------------------------------
  //! Overloaded less-than comparison
  // --------------------------------------------------------------------------
  bool Types::operator <(const TwrInfo& lhs, const TwrInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isLessThan = (
      (lhs.nTwr < rhs.nTwr) &&
      (lhs.ene  < rhs.ene)  &&
      (lhs.rho  < rhs.rho)  &&
      (lhs.eta  < rhs.eta)  &&
      (lhs.phi  < rhs.phi)  &&
      (lhs.px   < rhs.px)   &&
      (lhs.py   < rhs.py)   &&
      (lhs.pz   < rhs.pz)   &&
      (lhs.rx   < rhs.rx)   &&
      (lhs.ry   < rhs.ry)   &&
      (lhs.rz   < rhs.rz)
    );
    return isLessThan;

  }  // end 'operator <(TwrInfo&, TwrInfo&) const'



  // --------------------------------------------------------------------------
  //! Overloaded greater-than comparison
  // --------------------------------------------------------------------------
  bool Types::operator >(const TwrInfo& lhs, const TwrInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isGreaterThan = (
      (lhs.nTwr > rhs.nTwr) &&
      (lhs.ene  > rhs.ene)  &&
      (lhs.rho  > rhs.rho)  &&
      (lhs.eta  > rhs.eta)  &&
      (lhs.phi  > rhs.phi)  &&
      (lhs.px   > rhs.px)   &&
      (lhs.py   > rhs.py)   &&
      (lhs.pz   > rhs.pz)   &&
      (lhs.rx   > rhs.rx)   &&
      (lhs.ry   > rhs.ry)   &&
      (lhs.rz   > rhs.rz)
    );
    return isGreaterThan;

  }  // end 'operator >(TwrInfo&, TwrInfo&)'



  // --------------------------------------------------------------------------
  //! Overloaded less-than-or-equal-to comparison
  // --------------------------------------------------------------------------
  bool Types::operator <=(const TwrInfo& lhs, const TwrInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isLessThanOrEqualTo = (
      (lhs.nTwr <= rhs.nTwr) &&
      (lhs.ene  <= rhs.ene)  &&
      (lhs.rho  <= rhs.rho)  &&
      (lhs.eta  <= rhs.eta)  &&
      (lhs.phi  <= rhs.phi)  &&
      (lhs.px   <= rhs.px)   &&
      (lhs.py   <= rhs.py)   &&
      (lhs.pz   <= rhs.pz)   &&
      (lhs.rx   <= rhs.rx)   &&
      (lhs.ry   <= rhs.ry)   &&
      (lhs.rz   <= rhs.rz)
    );
    return isLessThanOrEqualTo;

  }  // end 'operator <=(TwrInfo&, TwrInfo&) const'



  // --------------------------------------------------------------------------
  //! Overloaded greater-than-or-equal-to comparison
  // --------------------------------------------------------------------------
  bool Types::operator >=(const TwrInfo& lhs, const TwrInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isGreaterThanOrEqualTo = (
      (lhs.nTwr >= rhs.nTwr) &&
      (lhs.ene  >= rhs.ene)  &&
      (lhs.rho  >= rhs.rho)  &&
      (lhs.eta  >= rhs.eta)  &&
      (lhs.phi  >= rhs.phi)  &&
      (lhs.px   >= rhs.px)   &&
      (lhs.py   >= rhs.py)   &&
      (lhs.pz   >= rhs.pz)   &&
      (lhs.rx   >= rhs.rx)   &&
      (lhs.ry   >= rhs.ry)   &&
      (lhs.rz   >= rhs.rz)
    );
    return isGreaterThanOrEqualTo;

  }  // end 'operator >=(TwrInfo&, TwrInfo&)'



  // ctor/dtor ================================================================

  // --------------------------------------------------------------------------
  //! Default class constructor
  // --------------------------------------------------------------------------
  Types::TwrInfo::TwrInfo() {

     // nothing to do //

  }  // end ctor()



  // --------------------------------------------------------------------------
  //! Default class destructor
  // --------------------------------------------------------------------------
  Types::TwrInfo::~TwrInfo() {

    // nothing to do //

  }  // end dtor()



  // --------------------------------------------------------------------------
  //! Constructor accepting initialization option (minimize or maximize)
  // --------------------------------------------------------------------------
  Types::TwrInfo::TwrInfo(const Const::Init init) {

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

  }  // end ctor(Const::Init)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A RawTower and possibly a vertex
  // --------------------------------------------------------------------------
  Types::TwrInfo::TwrInfo(const RawTower* tower, optional<ROOT::Math::XYZVector> vtx, optional<int> sys) {

    SetInfo(tower, vtx, sys);

  }  // end ctor(RawTower*, optional<ROOT::Math::XYZVector>, optional<int>)'



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A TowerInfo and possibly a vertex
  // --------------------------------------------------------------------------
  Types::TwrInfo::TwrInfo(const TowerInfo* tower, optional<ROOT::Math::XYZVector> vtx, optional<int> sys) {

    SetInfo(tower, vtx, sys);

  }  // end ctor(TowerInfo*, optional<ROOT::Math::XYZVector>, optional<int>)'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
