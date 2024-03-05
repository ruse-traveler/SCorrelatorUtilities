// ----------------------------------------------------------------------------
// 'ParInfo.cc'
// Derek Anderson
// 03.04.2024
//
// Utility class to hold information from
// generated particles.
// ----------------------------------------------------------------------------

#define SCORRELATORUTILITIES_PARINFO_CC

// class definition
#include "ParInfo.h"

// make comon namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // internal methods ---------------------------------------------------------

  void ParInfo::Minimize() {

    pid     = numeric_limits<int>::min();
    status  = numeric_limits<int>::min();
    barcode = numeric_limits<int>::min();
    embedID = numeric_limits<int>::min();
    charge  = numeric_limits<float>::min();
    mass    = numeric_limits<double>::min();
    eta     = numeric_limits<double>::min();
    phi     = numeric_limits<double>::min();
    ene     = numeric_limits<double>::min();
    px      = numeric_limits<double>::min();
    py      = numeric_limits<double>::min();
    pz      = numeric_limits<double>::min();
    pt      = numeric_limits<double>::min();
    vx      = numeric_limits<double>::min();
    vy      = numeric_limits<double>::min();
    vz      = numeric_limits<double>::min();
    vr      = numeric_limits<double>::min();
    return;

  }  // end 'Minimize()'



  void ParInfo::Maximize() {

    pid     = numeric_limits<int>::max();
    status  = numeric_limits<int>::max();
    barcode = numeric_limits<int>::max();
    embedID = numeric_limits<int>::max();
    charge  = numeric_limits<float>::max();
    mass    = numeric_limits<double>::max();
    eta     = numeric_limits<double>::max();
    phi     = numeric_limits<double>::max();
    ene     = numeric_limits<double>::max();
    px      = numeric_limits<double>::max();
    py      = numeric_limits<double>::max();
    pz      = numeric_limits<double>::max();
    pt      = numeric_limits<double>::max();
    vx      = numeric_limits<double>::max();
    vy      = numeric_limits<double>::max();
    vz      = numeric_limits<double>::max();
    vr      = numeric_limits<double>::max();
    return;

  }  // end 'Maximize()'



  // public methods -----------------------------------------------------------

  void ParInfo::Reset() {

    Maximize();
    return;

  }  // end 'Reset()'



  void ParInfo::SetInfo(const HepMC::GenParticle* particle, const int event) {

    pid     = particle -> pdg_id();
    status  = particle -> status();
    barcode = particle -> barcode();
    embedID = event;
    charge  = Const::MapPidOntoCharge()[pid];
    mass    = particle -> momentum().m();
    eta     = particle -> momentum().eta();
    phi     = particle -> momentum().phi();
    ene     = particle -> momentum().e();
    px      = particle -> momentum().px();
    py      = particle -> momentum().py();
    pz      = particle -> momentum().pz();
    pt      = particle -> momentum().perp();
    return;

  }  // end 'SetInfo(HepMC::GenParticle*, int)'



  void ParInfo::SetInfo(const PHG4Particle* particle, const int event) {

    // set basic info
    pid     = particle -> get_pid();
    status  = numeric_limits<int>::max();  // FIXME there must be a way to get the status of these particles
    barcode = particle -> get_barcode();
    embedID = event;
    charge  = Const::MapPidOntoCharge()[pid];
    mass    = numeric_limits<double>::max();  // FIXME likewise for mass
    ene     = particle -> get_e();
    px      = particle -> get_px();
    py      = particle -> get_py();
    pz      = particle -> get_pz();

    // get remaining kinematic info
    ROOT::Math::PxPyPzEVector pPar(px, py, pz, ene);
    eta = pPar.Eta();
    phi = pPar.Phi();
    pt  = pPar.Pt();
    return;

  }  // end 'SetInfo(PHG4Particle*, int)'



  bool ParInfo::IsInAcceptance(const ParInfo& minimum, const ParInfo& maximum) {

    return ((*this >= minimum) && (*this <= maximum));

  }  // end 'IsInAcceptance(ParInfo&, ParInfo&)'



  bool ParInfo::IsInAcceptance(const pair<ParInfo, ParInfo>& range) {

    return ((*this >= range.first) && (*this <= range.second));

  }  // end 'IsInAcceptance(ParInfo&, ParInfo&)'



  bool ParInfo::IsFinalState() {

    return (status == 1);

  }  // end 'IsFinalState()'



  bool ParInfo::IsHardScatterProduct() {

    const bool isHardScatter = (
      (status == Const::HardScatterStatus::First) ||
      (status == Const::HardScatterStatus::Second)
    );
    return isHardScatter;

  }  // end 'IsHardScatterProduct()'



  bool ParInfo::IsParton() {

    const bool isLightQuark   = ((pid == Const::Parton::Down)    || (pid == Const::Parton::Up));
    const bool isStrangeQuark = ((pid == Const::Parton::Strange) || (pid == Const::Parton::Charm));
    const bool isHeavyQuark   = ((pid == Const::Parton::Bottom)  || (pid == Const::Parton::Top));
    const bool isGluon        = (pid == Const::Parton::Gluon);
    return (isLightQuark || isStrangeQuark || isHeavyQuark || isGluon);

  }  // end 'IsParton()'



  bool ParInfo::IsOutgoingParton() {

    return (IsHardScatterProduct() && IsParton());

  }  // end 'IsOutgoingParton()'



  // static methods -----------------------------------------------------------

  vector<string> ParInfo::GetListOfMembers() {

    vector<string> members = {
      "pid",
      "status",
      "barcode",
      "embedID",
      "charge",
      "mass",
      "eta",
      "phi",
      "ene",
      "px",
      "py",
      "pz",
      "pt",
      "vx",
      "vy",
      "vz",
      "vr"
    };
    return members;

  }  // end 'GetListOfMembers()'


  // overloaded operators -----------------------------------------------------

  bool operator<(const ParInfo& lhs, const ParInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isLessThan = (
      (lhs.eta  < rhs.eta)  &&
      (lhs.phi  < rhs.phi)  &&
      (lhs.ene  < rhs.ene)  &&
      (lhs.px   < rhs.px)   &&
      (lhs.py   < rhs.py)   &&
      (lhs.pz   < rhs.pz)   &&
      (lhs.pt   < rhs.pt)
    );
    return isLessThan;

  }  // end 'operator<(ParInfo&, ParInfo&)'



  bool operator>(const ParInfo& lhs, const ParInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isGreaterThan = (
      (lhs.eta  > rhs.eta)  &&
      (lhs.phi  > rhs.phi)  &&
      (lhs.ene  > rhs.ene)  &&
      (lhs.px   > rhs.px)   &&
      (lhs.py   > rhs.py)   &&
      (lhs.pz   > rhs.pz)   &&
      (lhs.pt   > rhs.pt)
    );
    return isGreaterThan;

  }  // end 'operator>(ParInfo&, ParInfo&)'



  bool operator<=(const ParInfo& lhs, const ParInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isLessThanOrEqualTo = (
      (lhs.eta  <= rhs.eta)  &&
      (lhs.phi  <= rhs.phi)  &&
      (lhs.ene  <= rhs.ene)  &&
      (lhs.px   <= rhs.px)   &&
      (lhs.py   <= rhs.py)   &&
      (lhs.pz   <= rhs.pz)   &&
      (lhs.pt   <= rhs.pt)
    );
    return isLessThanOrEqualTo;

  }  // end 'operator<=(ParInfo&, ParInfo&)'



  bool operator>=(const ParInfo& lhs, const ParInfo& rhs) {

    // note that some quantities aren't relevant for this comparison
    const bool isGreaterThanOrEqualTo = (
      (lhs.eta  >= rhs.eta)  &&
      (lhs.phi  >= rhs.phi)  &&
      (lhs.ene  >= rhs.ene)  &&
      (lhs.px   >= rhs.px)   &&
      (lhs.py   >= rhs.py)   &&
      (lhs.pz   >= rhs.pz)   &&
      (lhs.pt   >= rhs.pt)
    );
    return isGreaterThanOrEqualTo;

  }  // end 'operator>=(ParInfo&, ParInfo&)'



  // ctor/dtor ----------------------------------------------------------------

  ParInfo::ParInfo() {

    /* nothing to do */

  }  // end ctor()



  ParInfo::~ParInfo() {

    /* nothing to do */

  }  // end dtor()



  ParInfo::ParInfo(const Const::Init init) {

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



  ParInfo::ParInfo(HepMC::GenParticle* particle, const int event) {

    SetInfo(particle, event);

  }  // end ctor(HepMC::GenParticle*, int)'



  ParInfo::ParInfo(PHG4Particle* particle, const int event) {

    SetInfo(particle, event);

  }  // end ctor(PHG4Particle*, int)'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
