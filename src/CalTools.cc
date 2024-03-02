// ----------------------------------------------------------------------------
// 'CalTools.cc'
// Derek Anderson
// 02.23.2024
//
// Collection of frequent calo. cluster-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#define CALTOOLS_CC

// c++ utilities
#include <limits>
#include <string>
#include <vector>
#include <optional>
#include <cassert>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// CaloBase libraries
#include <calobase/RawCluster.h>
#include <calobase/RawClusterUtility.h>
#include <calobase/RawClusterContainer.h>
// calo utility definition
#include "CalTools.h"

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {

  // cluster methods --------------------------------------------------------

  RawClusterContainer* SCorrelatorUtilities::GetClusterStore(PHCompositeNode* topNode, const string node) {

    // grab clusters
    RawClusterContainer* clustStore = getClass<RawClusterContainer>(topNode, node.data());
    if (!clustStore) {
      cout << PHWHERE
           << "PANIC: " << node << " node is missing!"
           << endl;
      assert(clustStore);
    }
    return clustStore;

  }  // end 'GetClusterStore(PHCompositeNode*, string)'



  RawClusterContainer::ConstRange SCorrelatorUtilities::GetClusters(PHCompositeNode* topNode, const string store) {

    // get store and return range of clusters
    RawClusterContainer* clustStore = GetClusterStore(topNode, store);
    return clustStore -> getClusters();

  }  // end 'GetClusters(PHCompositeNode*, string)'

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
