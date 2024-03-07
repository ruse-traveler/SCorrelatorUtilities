// ----------------------------------------------------------------------------
// 'ClustInfo.cc'
// Derek Anderson
// 03.01.2024
//
// Utility class to hold information from
// calorimeter clusters.
// ----------------------------------------------------------------------------

#define SCORRELATORUTILITIES_CLUSTINFO_CC

// class definition
#include "ClustInfo.h"

// make comon namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // internal methods ---------------------------------------------------------

  void Types::ClustInfo::Minimize() {

    system  = numeric_limits<int>::min();
    nTwr    = numeric_limits<int>::min();
    ene     = numeric_limits<double>::min();
    rho     = numeric_limits<double>::min();
    eta     = numeric_limits<double>::min();
    phi     = numeric_limits<double>::min();
    rx      = numeric_limits<double>::min();
    ry      = numeric_limits<double>::min();
    rz      = numeric_limits<double>::min();
    return;

  }  // end 'Minimize()'

  void Types::ClustInfo::Maximize() {

    system  = numeric_limits<int>::max();
    nTwr    = numeric_limits<int>::max();
    ene     = numeric_limits<double>::max();
    rho     = numeric_limits<double>::max();
    eta     = numeric_limits<double>::max();
    phi     = numeric_limits<double>::max();
    rx      = numeric_limits<double>::max();
    ry      = numeric_limits<double>::max();
    rz      = numeric_limits<double>::max();
    return;

  }  // end 'Maximize()'



  // public methods -----------------------------------------------------------

  void Types::ClustInfo::Reset() {

    Maximize();
    return;

  }  // end 'Reset()'



  void Types::ClustInfo::SetInfo(const RawCluster* clust, optional<int> sys = nullopt) {

    // if subsystem ID provided, set data member
    if (sys.has_value()) {
      system = sys.value();
    }

    // set remaining members
    nTwr = clust -> getNTowers();
    ene  = clust -> get_energy();
    rho  = clust -> get_r();
    eta  = numeric_limits<double>::max();  // FIXME add method to calculate eta
    phi  = clust -> get_phi();
    rx   = clust -> get_position().x();
    ry   = clust -> get_position().y();
    rz   = clust -> get_position().z();
    return;

  }  // end 'SetInfo(RawCluster*, optional<int>)'



  bool Types::ClustInfo::IsInAcceptance(const ClustInfo& minimum, const ClustInfo& maximum) {

    return ((*this >= minimum) && (*this <= maximum));

  }  // end 'IsInAcceptance(ClustInfo&, ClustInfo&)'



  bool Types::ClustInfo::IsInAcceptance(const pair<ClustInfo, ClustInfo>& range) {

    return ((*this >= range.first) && (*this <= range.second));

  }  // end 'IsInAcceptance(pair<ClustInfo, ClustInfo>&)'



  // static methods -----------------------------------------------------------

  vector<string> Types::ClustInfo::GetListOfMembers() {

    vector<string> members = {
      "sys",
      "nTwr",
      "ene",
      "rho",
      "eta",
      "phi",
      "rx",
      "ry",
      "rz"
    };
    return members;

  }  // end 'GetListOfMembers()'



  // overloaded operators -----------------------------------------------------

  bool Types::operator <(const ClustInfo& lhs, const ClustInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isLessThan = (
      (lhs.nTwr < rhs.nTwr) &&
      (lhs.ene  < rhs.ene)  &&
      (lhs.rho  < rhs.rho)  &&
      (lhs.eta  < rhs.eta)  &&
      (lhs.phi  < rhs.phi)  &&
      (lhs.rx   < rhs.rx)   &&
      (lhs.ry   < rhs.ry)   &&
      (lhs.rz   < rhs.rz)
    );
    return isLessThan;

  }  // end 'operator <(ClustInfo&, ClustInfo&) const'



  bool Types::operator >(const ClustInfo& lhs, const ClustInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isGreaterThan = (
      (lhs.nTwr > rhs.nTwr) &&
      (lhs.ene  > rhs.ene)  &&
      (lhs.rho  > rhs.rho)  &&
      (lhs.eta  > rhs.eta)  &&
      (lhs.phi  > rhs.phi)  &&
      (lhs.rx   > rhs.rx)   &&
      (lhs.ry   > rhs.ry)   &&
      (lhs.rz   > rhs.rz)
    );
    return isGreaterThan;

  }  // end 'operator >(ClustInfo&, ClustInfo&)'



  bool Types::operator <=(const ClustInfo& lhs, const ClustInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isLessThanOrEqualTo = (
      (lhs.nTwr <= rhs.nTwr) &&
      (lhs.ene  <= rhs.ene)  &&
      (lhs.rho  <= rhs.rho)  &&
      (lhs.eta  <= rhs.eta)  &&
      (lhs.phi  <= rhs.phi)  &&
      (lhs.rx   <= rhs.rx)   &&
      (lhs.ry   <= rhs.ry)   &&
      (lhs.rz   <= rhs.rz)
    );
    return isLessThanOrEqualTo;

  }  // end 'operator <=(ClustInfo&, ClustInfo&) const'



  bool Types::operator >=(const ClustInfo& lhs, const ClustInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isGreaterThanOrEqualTo = (
      (lhs.nTwr >= rhs.nTwr) &&
      (lhs.ene  >= rhs.ene)  &&
      (lhs.rho  >= rhs.rho)  &&
      (lhs.eta  >= rhs.eta)  &&
      (lhs.phi  >= rhs.phi)  &&
      (lhs.rx   >= rhs.rx)   &&
      (lhs.ry   >= rhs.ry)   &&
      (lhs.rz   >= rhs.rz)
    );
    return isGreaterThanOrEqualTo;

  }  // end 'operator >=(ClustInfo&, ClustInfo&)'



  // ctor/dtor ----------------------------------------------------------------

  Types::ClustInfo::ClustInfo() {

     // nothing to do //

  }  // end ctor()



  Types::ClustInfo::~ClustInfo() {

    // nothing to do //

  }  // end dtor()



  Types::ClustInfo::ClustInfo(const Const::Init init) {

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



  Types::ClustInfo::ClustInfo(const RawCluster* clust, optional<int> sys) {

    SetInfo(clust, sys);

  }  // end ctor(RawCluster*, optional<int>)'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
