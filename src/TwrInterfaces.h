/// ---------------------------------------------------------------------------
/*! \file   TwrInterfaces.h
 *  \author Derek Anderson
 *  \date   08.04.2024
 *
 *  Calorimeter tower-related interfaces.
 */
/// ---------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_TWRINTERFACES_H
#define SCORRELATORUTILITIES_TWRINTERFACES_H

// c++ utilities
#include <limits>
#include <string>
#include <vector>
#include <cassert>
#include <optional>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// CaloBase libraries
#include <calobase/RawTower.h>
#include <calobase/TowerInfo.h>
#include <calobase/RawTowerContainer.h>
#include <calobase/TowerInfoContainer.h>

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace Interfaces {

    // tower interfaces -----------------------------------------------------

    RawTowerContainer*            GetRawTowerStore(PHCompositeNode* topNode, const string node);
    RawTowerContainer::ConstRange GetRawTowers(PHCompositeNode* topNode, const string store);

    /* TODO
     *   - Add geometry getter (EMCal, IHCal, OHCal)' 
     *   - Add tower info store getter
     *   - Add tower info range getter
     */

  }  // end Interfaces namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
