// ----------------------------------------------------------------------------
// 'Interfaces.h'
// Derek Anderson
// 12.29.2023
//
// Various interfaces between objects and data structures (e.g.
// TTree's) are collected here.
// ----------------------------------------------------------------------------

#pragma once

// c++ utilities
#include <string>
#include <vector>
#include <optional>
// analyis utilities
#include "TrkTools.h"
#include "CalTools.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // correlator object-data structure interfaces ----------------------------


    // data member-to-string methods ------------------------------------------

    // append a tag to a vector of leaf names
    void AddTagToLeaves(const string tag, vector<string>& leaves) {

      for (string& leaf : leaves) {
        leaf.append(tag);
      }
      return;

    }  // end 'AddTagToLeaves(vector<string>)'



    // flatten list of leaves into a colon-separated list
    string FlattenLeafList(const vector<string>& leaves) {

      string flattened("");
      for (size_t iLeaf = 0; iLeaf < leaves.size(); iLeaf++) {
        flattened.append(leaves[iLeaf]);
        if ((iLeaf + 1) != leaves.size()) {
          flattened.append(":");
        }
      }
      return flattened;

    }  // end 'FlattenLeafList(vector<string>&)'



    // generic function to create vector of leaf names
    template <typename T> vector<string> MakeLeafVector(optional<string> tag) {

      vector<string> leaves = T::GetListOfMembers();
      if (tag.has_value()) {
        AddTagToLeaves(tag.value(), leaves);
      }
      return leaves;

    }  // end 'template <> MakeLeafVector(optional<string>)'



    // generic function to append leaf names onto a vector
    template <typename T> void AddLeavesToVector(vector<string>& vecToAddTo, optional<string> tag) {

      vector<string> addends = MakeLeafVector<T>(tag);
      for (auto addend : addends) {
        vecToAddTo.push_back(addend);
      }
      return;

    }  // end 'template <> AddLeavesToVector(vector<string>&, optional<string>)'

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
