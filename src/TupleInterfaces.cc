// ----------------------------------------------------------------------------
// 'TupleInterfaces.cc'
// Derek Anderson
// 03.05.2024
//
// TNtuple-related interfaces.
// ----------------------------------------------------------------------------

#define SCORRELATORUTILITIES_TUPLEINTERFACES_CC

// namespace definition
#include "TupleInterfaces.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  void Interfaces::AddTagToLeaves(const string tag, vector<string>& leaves) {

    for (string& leaf : leaves) {
      leaf.append(tag);
    }
    return;

  }  // end 'AddTagToLeaves(vector<string>)'



  string Interfaces::FlattenLeafList(const vector<string>& leaves) {

    string flattened("");
    for (size_t iLeaf = 0; iLeaf < leaves.size(); iLeaf++) {
      flattened.append(leaves[iLeaf]);
      if ((iLeaf + 1) != leaves.size()) {
        flattened.append(":");
      }
    }
    return flattened;

  }  // end 'FlattenLeafList(vector<string>&)'



  // generic methods ----------------------------------------------------------

  template <typename T> vector<string> Interfaces::MakeLeafVector(optional<string> tag) {

    vector<string> leaves = T::GetListOfMembers();
    if (tag.has_value()) {
      AddTagToLeaves(tag.value(), leaves);
    }
    return leaves;

  }  // end 'template <> MakeLeafVector(optional<string>)'



  template <typename T> void Interfaces::AddLeavesToVector(vector<string>& vecToAddTo, optional<string> tag) {

    vector<string> addends = MakeLeafVector<T>(tag);
    for (auto addend : addends) {
      vecToAddTo.push_back(addend);
    }
    return;

  }  // end 'template <> AddLeavesToVector(vector<string>&, optional<string>)'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
