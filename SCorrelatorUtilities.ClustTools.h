// ----------------------------------------------------------------------------
// 'SCorrelatorUtilities.ClustTools.h'
// Derek Anderson
// 10.30.2023
//
// Collection of frequent calo. cluster-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // cluster methods --------------------------------------------------------

    RawClusterContainer* GetClusterStore(PHCompositeNode* topNode, const TString sNodeName) {

      // grab clusters
      RawClusterContainer *clustStore = findNode::getClass<RawClusterContainer>(topNode, sNodeName.Data());
      if (!clustStore) {
        cout << PHWHERE
             << "PANIC: " << sNodeName.Data() << " node is missing!"
             << endl;
        assert(clustStore);
      }
      return clustStore;

    }  // end 'GetClusterStore(PHCompositeNode*, TString)'


  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------

