// ----------------------------------------------------------------------------
// 'Interfaces.h'
// Derek Anderson
// 12.29.2023
//
// Various interfaces between sPHENIX Cold QCD Correlator
// Analysis objects and data structures (e.g. TTree's) are
// collected here.
// ----------------------------------------------------------------------------

#ifndef INTERFACES_H
#define INTERFACES_H

// c++ utilities
#include <string>
#include <vector>
#include <optional>
// root libraries
#include <TTree.h>
// phool libraries
#include <phool/PHCompositeNode.h>

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // correlator object-data structure interfaces ----------------------------

    /* TODO will go here */



    // f4a interfaces ---------------------------------------------------------

    void CleanseNodeName(string& nameToClean);
    template <typename T> void CreateNode(PHCompositeNode* topNode, string newNodeName, T& objectInNode);



    // TTree interfaces -------------------------------------------------------

    template <typename T> int64_t GetEntry(T* tree, const uint64_t entry);
    template <typename T> int64_t LoadTree(T* tree, const uint64_t entry, int& current);



    // data member-to-string methods ------------------------------------------

    // append a tag to a vector of leaf names
    void AddTagToLeaves(const string tag, vector<string>& leaves);
    string FlattenLeafList(const vector<string>& leaves);
    template <typename T> vector<string> MakeLeafVector(optional<string> tag = nullopt);
    template <typename T> void AddLeavesToVector(vector<string>& vecToAddTo, optional<string> tag = nullopt);

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
