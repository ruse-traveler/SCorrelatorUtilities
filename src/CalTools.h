// ----------------------------------------------------------------------------
// 'CalTools.h'
// Derek Anderson
// 10.30.2023
//
// Collection of frequent calo. cluster-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#ifndef CALTOOLS_H
#define CALTOOLS_H

// c++ utilities
#include <limits>
#include <string>
#include <vector>
#include <optional>
// phool libraries
#include <phool/PHCompositeNode.h>
// CaloBase libraries
#include <calobase/RawClusterContainer.h>

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // cluster methods --------------------------------------------------------

    RawClusterContainer*            GetClusterStore(PHCompositeNode* topNode, const string node);
    RawClusterContainer::ConstRange GetClusters(PHCompositeNode* topNode, const string store);

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------

