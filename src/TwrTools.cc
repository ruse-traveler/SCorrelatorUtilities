/// ---------------------------------------------------------------------------
/*! \file   TwrTools.cc
 *  \author Derek Anderson
 *  \date   08.04.2024
 *
 *  Collection of frequent tower-related methods utilized in
 *  the sPHENIX Cold QCD Energy-Energy Correlator analysis.
 */
/// ---------------------------------------------------------------------------

#define SCORRELATORUTILITIES_TWRTOOLS_CC

// namespace definition
#include "TwrTools.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // --------------------------------------------------------------------------
  //! Get tower status
  // --------------------------------------------------------------------------
  /*! NOTE: only applies to TowerInfo objects.
   */
  int Tools::GetTowerStatus(TowerInfo* tower) {

    int status = Const::TowerStatus::Unknown;
    if (tower -> get_isHot()) {
      status = Const::TowerStatus::Hot;
    } else if (tower -> get_isBadTime()) {
      status = Const::TowerStatus::BadTime;
    } else if (tower -> get_isBadChi2()) {
      status = Const::TowerStatus::BadChi;
    } else if (tower -> get_isNotInstr()) {
      status = Const::TowerStatus::NotInstr;
    } else if (tower -> get_isNoCalib()) {
      status = Const::TowerStatus::NoCalib;
    } else {
      status = Const::TowerStatus::Good;
    }
    return status;

  }  // end 'GetTowerStatus(TowerInfo*)' 



  // --------------------------------------------------------------------------
  //! Get key and eta-phi indices for a TowerInfo object
  // --------------------------------------------------------------------------
  tuple<int, int, int> Tools::GetTowerIndices(
    const int channel,
    const int subsys,
    PHCompositeNode* topNode
  ) {

    // grab container & key
    TowerInfoContainer* towers = Interfaces::GetTowerInfoStore(
      topNode,
      Const::MapIndexOntoTowerInfo()[ subsys ]
    );
    const uint32_t key = towers -> encode_key(channel);

    // grab indices
    const int iEta = towers -> getTowerEtaBin(key);
    const int iPhi = towers -> getTowerPhiBin(key);
    return make_tuple((int) key, iEta, iPhi);

  }  // end 'GetTowerIndices(int, int, PHCompositeNode*)'



  // --------------------------------------------------------------------------
  //! Get tower coordinates in (x, y, z)
  // --------------------------------------------------------------------------
  ROOT::Math::XYZVector Tools::GetTowerPositionXYZ() {

    return ROOT::Math::XYZVector(0., 0., 0.);  // TODO fill in

  }  // end 'GetTowerPositionXYZ()'



  // --------------------------------------------------------------------------
  //! Get tower coordinates in (r, eta, phi)
  // --------------------------------------------------------------------------
  ROOT::Math::RhoEtaPhiVector Tools::GetTowerPositionRhoEtaPhi() {

    return ROOT::Math::RhoEtaPhiVector(0., 0., 0.);  // TODO fill in

  }  // end 'GetTowerPositionRhoEtaPhi()'



  // --------------------------------------------------------------------------
  //! Get 4-momentum for a tower
  // --------------------------------------------------------------------------
  ROOT::Math::PxPyPzEVector Tools::GetTowerMomentum(const double energy, const ROOT::Math::XYZVector pos, const ROOT::Math::XYZVector vtx) {

    // get displacement
    ROOT::Math::XYZVector displace = GetDisplacement(pos, vtx);

    // get magnitdue of 3-momentum
    const double magnitude = sqrt((energy * energy) - (Const::MassPion() * Const::MassPion()));

    // now get components and return
    ROOT::Math::XYZVector momentum = displace.Unit() * magnitude;
    return ROOT::Math::PxPyPzEVector(momentum.X(), momentum.Y(), momentum.Z(), energy);

  }  // end 'GetTowerMomentum(double, ROOT::Math::XYZVector, ROOT::Math::XYZVector)'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
