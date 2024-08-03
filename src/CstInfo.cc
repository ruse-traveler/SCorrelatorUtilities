/// ---------------------------------------------------------------------------
/*! \file   CstInfo.cc
 *  \author Derek Anderson
 *  \date   03.03.2024
 *
 *  Utility class to hold information from
 *  jet constituents.
 */
/// ---------------------------------------------------------------------------

#define SCORRELATORUTILITIES_CSTINFO_CC

// class definition
#include "CstInfo.h"

// make comon namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // private methods ==========================================================

  // --------------------------------------------------------------------------
  //! Set data members to absolute minima
  // --------------------------------------------------------------------------
  void Types::CstInfo::Minimize() {

    type    = -1 * numeric_limits<int>::max();
    cstID   = -1 * numeric_limits<int>::max();
    jetID   = -1 * numeric_limits<int>::max();
    embedID = -1 * numeric_limits<int>::max();
    pid     = -1 * numeric_limits<int>::max();
    z       = -1. * numeric_limits<double>::max();
    dr      = -1. * numeric_limits<double>::max();
    jt      = -1. * numeric_limits<double>::max();
    ene     = -1. * numeric_limits<double>::max();
    px      = -1. * numeric_limits<double>::max();
    py      = -1. * numeric_limits<double>::max();
    pz      = -1. * numeric_limits<double>::max();
    pt      = -1. * numeric_limits<double>::max();
    eta     = -1. * numeric_limits<double>::max();
    phi     = -1. * numeric_limits<double>::max();
    return;

  }  // end 'Minimize()'



  // --------------------------------------------------------------------------
  //! Set data members to absolute maxima
  // --------------------------------------------------------------------------
  void Types::CstInfo::Maximize() {

    type    = numeric_limits<int>::max();
    cstID   = numeric_limits<int>::max();
    jetID   = numeric_limits<int>::max();
    embedID = numeric_limits<int>::max();
    pid     = numeric_limits<int>::max();
    z       = numeric_limits<double>::max();
    dr      = numeric_limits<double>::max();
    jt      = numeric_limits<double>::max();
    ene     = numeric_limits<double>::max();
    px      = numeric_limits<double>::max();
    py      = numeric_limits<double>::max();
    pz      = numeric_limits<double>::max();
    pt      = numeric_limits<double>::max();
    eta     = numeric_limits<double>::max();
    phi     = numeric_limits<double>::max();
    return;

  }  // end 'Maximize()'



  // public methods ===========================================================

  // --------------------------------------------------------------------------
  //! Reset object by maximizing data members
  // --------------------------------------------------------------------------
  void Types::CstInfo::Reset() {

    Maximize();
    return;

  }  // end 'Reset()'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a FastJet PseudoJet
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(fastjet::PseudoJet& pseudojet) {

    cstID = pseudojet.user_index();
    ene   = pseudojet.E();
    px    = pseudojet.px();
    py    = pseudojet.py();
    pz    = pseudojet.pz();
    pt    = pseudojet.perp();
    eta   = pseudojet.pseudorapidity();
    phi   = pseudojet.phi_std();
    return;

  }  // end 'SetInfo(fastjet::PseudoJet)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A RawCluster
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(RawCluster& cluster) {

    /* TODO fill in*/
    return;

  }  // end 'SetInfo(RawCluster&)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A TowerInfo
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(TowerInfo& info) {

    /* TODO fill in*/
    return;

  }  // end 'SetInfo(TowerInfo&)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A RawTower
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(RawTower& tower) {

    /* TODO fill in*/
    return;

  }  // end 'SetInfo(RawTower&)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A SvtxTrack
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(SvtxTrack& track) {

    /* TODO fill in*/
    return;

  }  // end 'SetInfo(SvtxTrack&)'



  // --------------------------------------------------------------------------
  //! Calculate information relative to provided jet (e.g. momentum fraction)
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetJetInfo(const Types::JetInfo& jet) {

    // grab 3-momenta
    ROOT::Math::XYZVector pJet(jet.GetPX(), jet.GetPY(), jet.GetPZ());
    ROOT::Math::XYZVector pCst(px, py, pz);
    ROOT::Math::XYZVector pCross = pCst.Cross(pJet);

    // get delta eta/phi
    const double dEta = eta - jet.GetEta();
    const double dPhi = phi - jet.GetPhi();

    // set values and exit
    z  = pCst.Dot(pJet) / pJet.Mag2();
    dr = sqrt((dEta * dEta) + (dPhi * dPhi));
    jt = sqrt( pCross.Mag2() ) / pJet.Mag2();
    return;

  }  // end 'SetJetInfo(Types::JetInfo&)'



  // --------------------------------------------------------------------------
  //! Check if object is within provided bounds (explicit minimum, maximum)
  // --------------------------------------------------------------------------
  bool Types::CstInfo::IsInAcceptance(const CstInfo& minimum, const CstInfo& maximum) const {

    return ((*this >= minimum) && (*this <= maximum));

  }  // end 'IsInAcceptance(CstInfo&, CstInfo&)'



  // --------------------------------------------------------------------------
  //! Check if object is within provided bounds (set by pair)
  // --------------------------------------------------------------------------
  bool Types::CstInfo::IsInAcceptance(const pair<CstInfo, CstInfo>& range) const {

    return ((*this >= range.first) && (*this <= range.second));

  }  // end 'IsInAcceptance(pair<CstInfo, CstInfo>&)'



  // static methods ===========================================================

  // --------------------------------------------------------------------------
  //! Get list of data fields
  // --------------------------------------------------------------------------
  vector<string> Types::CstInfo::GetListOfMembers() {

    vector<string> members = {
      "type",
      "cstID",
      "jetID",
      "embedID",
      "pid",
      "z",
      "dr",
      "jt",
      "ene",
      "px",
      "py",
      "pz",
      "pt",
      "eta",
      "phi"
    };
    return members;

  }  // end 'GetListOfMembers()'



  // overloaded operators =====================================================

  // --------------------------------------------------------------------------
  //! Overloaded less-than comparison
  // --------------------------------------------------------------------------
  bool Types::operator <(const CstInfo& lhs, const CstInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isLessThan = (
      (lhs.z   < rhs.z)   &&
      (lhs.dr  < rhs.dr)  &&
      (lhs.jt  < rhs.jt)  &&
      (lhs.ene < rhs.ene) &&
      (lhs.px  < rhs.px)  &&
      (lhs.py  < rhs.py)  &&
      (lhs.pz  < rhs.pz)  &&
      (lhs.pt  < rhs.pt)  &&
      (lhs.eta < rhs.eta) &&
      (lhs.phi < rhs.phi)
    );
    return isLessThan;
  
  }  // end 'operator <(CstInfo&, CstInfo&)'



  // --------------------------------------------------------------------------
  //! Overloaded greater-than comparison
  // --------------------------------------------------------------------------
  bool Types::operator >(const CstInfo& lhs, const CstInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isGreaterThan = (
      (lhs.z   > rhs.z)   &&
      (lhs.dr  > rhs.dr)  &&
      (lhs.jt  > lhs.jt)  &&
      (lhs.ene > rhs.ene) &&
      (lhs.px  > rhs.px)  &&
      (lhs.py  > rhs.py)  &&
      (lhs.pz  > rhs.pz)  &&
      (lhs.pt  > rhs.pt)  &&
      (lhs.eta > rhs.eta) &&
      (lhs.phi > rhs.phi)
    );
    return isGreaterThan;
  
  }  // end 'operator >(CstInfo&, CstInfo&)'



  // --------------------------------------------------------------------------
  //! Overloaded less-than-or-equal-to comparison
  // --------------------------------------------------------------------------
  bool Types::operator <=(const CstInfo& lhs, const CstInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isLessThanOrEqualTo = (
      (lhs.z   <= rhs.z)   &&
      (lhs.dr  <= rhs.dr)  &&
      (lhs.jt  <= rhs.jt)  &&
      (lhs.ene <= rhs.ene) &&
      (lhs.px  <= rhs.px)  &&
      (lhs.py  <= rhs.py)  &&
      (lhs.pz  <= rhs.pz)  &&
      (lhs.pt  <= rhs.pt)  &&
      (lhs.eta <= rhs.eta) &&
      (lhs.phi <= rhs.phi)
    );
    return isLessThanOrEqualTo;
  
  }  // end 'operator <=(CstInfo&, CstInfo&)'



  // --------------------------------------------------------------------------
  //! Overloaded greater-than-or-equal-to comparison
  // --------------------------------------------------------------------------
  bool Types::operator >=(const CstInfo& lhs, const CstInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isGreaterThan = (
      (lhs.z   >= rhs.z)   &&
      (lhs.dr  >= rhs.dr)  &&
      (lhs.jt  >= rhs.jt)  &&
      (lhs.ene >= rhs.ene) &&
      (lhs.px  >= rhs.px)  &&
      (lhs.py  >= rhs.py)  &&
      (lhs.pz  >= rhs.pz)  &&
      (lhs.pt  >= rhs.pt)  &&
      (lhs.eta >= rhs.eta) &&
      (lhs.phi >= rhs.phi)
    );
    return isGreaterThan;
  
  }  // end 'operator >=(CstInfo&, CstInfo&)'



  // ctor/dtor ================================================================

  // --------------------------------------------------------------------------
  //! Default class constructor
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo() {

    /* nothing to do */

  }  // end ctor()



  // --------------------------------------------------------------------------
  //! Default class destructor
  // --------------------------------------------------------------------------
  Types::CstInfo::~CstInfo() {

    /* nothing to do */

  }  // end dtor()



  // --------------------------------------------------------------------------
  //! Constructor accepting initialization option (minimize or maximize)
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(const Const::Init init) {

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



  // --------------------------------------------------------------------------
  //! Constructor accepting a FastJet PseudoJet
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(fastjet::PseudoJet& pseudojet) {

    SetInfo(pseudojet);

  }  // end ctor(fastjet::PseudoJet&)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A RawCluster
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(RawCluster& cluster) {

    SetInfo(cluster);

  }  // end ctor(RawCluster&)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A TowerInfo
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(TowerInfo& info) {

    SetInfo(info);

  }  // end ctor(TowerInfo&)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A RawTower
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(RawTower& tower) {

    SetInfo(tower);

  }  // end ctor(RawTower&)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A SvtxTrack
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(SvtxTrack& track) {

    SetInfo(track);

  }  // end ctor(SvtxTrack&)

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
