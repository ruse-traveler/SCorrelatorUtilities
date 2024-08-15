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
  //! Pull relevant information from a F4A SvtxTrack
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(SvtxTrack* track) {

    type  = Const::Object::Track;
    cstID = track -> get_id();
    pt    = track -> get_pt();
    px    = track -> get_px();
    py    = track -> get_py();
    pz    = track -> get_pz();
    ene   = hypot(track -> get_p(), Const::MassPion());
    eta   = track -> get_eta();
    phi   = track -> get_phi();
    return;

  }  // end 'SetInfo(SvtxTrack*)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A PFO
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(const ParticleFlowElement* flow) {

    type  = Const::Object::Flow;
    cstID = flow -> get_id();
    pt    = flow -> get_pt();
    px    = flow -> get_px();
    py    = flow -> get_py();
    pz    = flow -> get_pz();
    ene   = flow -> get_e();
    eta   = flow -> get_eta();
    phi   = flow -> get_phi();
    return;

  }  // end 'SetInfo(*)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A TowerInfo
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(TowerInfo* info) {

    /* TODO implement */
    return;

  }  // end 'SetInfo(TowerInfo*)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A RawTower
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(RawTower* tower, optional<ROOT::Math::XYZVector> vtx) {

    /* TODO implement */
    return;

  }  // end 'SetInfo(RawTower*, optional<ROOT::Math::XYZVector>)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A RawCluster
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(const RawCluster* clust, optional<ROOT::Math::XYZVector> vtx) {

    // if no vertex provided, use origin
    ROOT::Math::XYZVector vtxToUse(0., 0., 0.);
    if (vtx.has_value()) {
      vtxToUse = vtx.value();
    }

    // grab position
    ROOT::Math::XYZVector position(
      clust -> get_position().x(),
      clust -> get_position().y(),
      clust -> get_position().z()
    );

    // grab momentum
    ROOT::Math::PxPyPzEVector momentum = Tools::GetClustMomentum(clust -> get_energy(), position, vtxToUse);

    type  = Const::Object::Cluster;
    cstID = clust -> get_id();
    pt    = momentum.Pt();
    px    = momentum.Px();
    py    = momentum.Py();
    pz    = momentum.Pz();
    ene   = momentum.E();
    eta   = momentum.Eta();
    phi   = momentum.Phi();
    return;

  }  // end 'SetInfo(RawCluster*, optional<ROOT::Math::XYZVector>)'



  // --------------------------------------------------------------------------
  //! Pull relevant information from a F4A PHG4Particle
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetInfo(PHG4Particle* particle, const int event) {

    /* TODO implement */
    return;

  }  // end 'SetInfo(PHG4Particle*, int)'



  // --------------------------------------------------------------------------
  //! Calculate information relative to provided jet (e.g. momentum fraction)
  // --------------------------------------------------------------------------
  void Types::CstInfo::SetJetInfo(const int id, const Types::JetInfo& jet) {

    // grab 3-momenta
    ROOT::Math::XYZVector pJet(jet.GetPX(), jet.GetPY(), jet.GetPZ());
    ROOT::Math::XYZVector pCst(px, py, pz);
    ROOT::Math::XYZVector pCross = pCst.Cross(pJet);

    // get delta eta/phi
    const double dEta = eta - jet.GetEta();
    const double dPhi = phi - jet.GetPhi();

    // set values and exit
    jetID = id;
    z     = pCst.Dot(pJet) / pJet.Mag2();
    dr    = sqrt((dEta * dEta) + (dPhi * dPhi));
    jt    = sqrt( pCross.Mag2() ) / pJet.Mag2();
    return;

  }  // end 'SetJetInfo(int, Types::JetInfo&)'



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
  //! Constructor accepting a F4A SvtxTrack
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(SvtxTrack* track) {

    SetInfo(track);

  }  // end ctor(SvtxTrack*)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A PFO
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(const ParticleFlowElement* flow) {

    SetInfo(flow);

  }  // end ctor(ParticleFlowElement*)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A TowerInfo
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(TowerInfo* info) {

    SetInfo(info);

  }  // end ctor(TowerInfo*)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A RawTower
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(RawTower* tower, optional<ROOT::Math::XYZVector> vtx) {

    SetInfo(tower, vtx);

  }  // end ctor(RawTower*, optional<ROOT::Math::XYZVector>)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A RawCluster
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(const RawCluster* cluster, optional<ROOT::Math::XYZVector> vtx) {

    SetInfo(cluster, vtx);

  }  // end ctor(RawCluster*, optional<ROOT::Math::XYZVector>)



  // --------------------------------------------------------------------------
  //! Constructor accepting a F4A PHG4Particle
  // --------------------------------------------------------------------------
  Types::CstInfo::CstInfo(PHG4Particle* particle, const int event) {

    SetInfo(particle, event);

  }  // end ctor(PHG4Particle*, int)

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
