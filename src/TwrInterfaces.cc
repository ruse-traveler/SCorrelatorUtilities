/// ---------------------------------------------------------------------------
/*! \file   TwrInterfaces.cc
 *  \author Derek Anderson
 *  \date   08.04.2024
 *
 *  Calorimeter tower-related interfaces.
 */
/// ---------------------------------------------------------------------------

#define SCORRELATORUTILITIES_TWRINTERFACES_CC

// namespace definition 
#include "TwrInterfaces.h"

// make common namespaces implicit
using namespace std;
using namespace findNode;



// tower interfaces ===========================================================

namespace SColdQcdCorrelatorAnalysis {

  // --------------------------------------------------------------------------
  //! Get raw tower container from node tree
  // --------------------------------------------------------------------------
  RawTowerContainer* Interfaces::GetTowerStore(PHCompositeNode* topNode, const string node) {

    // grab clusters
    RawTowerContainer* towerStore = getClass<RawTowerContainer>(topNode, node.data());
    if (!towerStore) {
      cout << PHWHERE
           << "PANIC: " << node << " node is missing!"
           << endl;
      assert(towerStore);
    }
    return towerStore;

  }  // end 'GetTowerStore(PHCompositeNode*, string)'



  // --------------------------------------------------------------------------
  //! Get raw towers from container
  // --------------------------------------------------------------------------
  RawTowerContainer::ConstRange Interfaces::GetRawTowers(PHCompositeNode* topNode, const string store) {

    // get store and return range of clusters
    RawTowerContainer* towerStore = GetTowerStore(topNode, store);
    return towerStore -> getTowers();

  }  // end 'GetRawTowers(PHCompositeNode*, string)'

  /* TODO
   *   - Add geometry getter (EMCal, IHCal, OHCal)' 
   *   - Add tower info store getter
   *   - Add tower info range getter
   */

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
