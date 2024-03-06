// ----------------------------------------------------------------------------
// 'TupleInterfaces.h'
// Derek Anderson
// 03.05.2024
//
// TNtuple-related interfaces.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_TUPLEINTERFACES_H
#define SCORRELATORUTILITIES_TUPLEINTERFACES_H

// c++ utilities
#include <string>
#include <vector>
#include <optional>

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace Interfaces {

    // tuple interfaces -------------------------------------------------------

    void   AddTagToLeaves(const string tag, vector<string>& leaves);
    string FlattenLeafList(const vector<string>& leaves);

    // generic methods
    template <typename T> vector<string> MakeLeafVector(optional<string> tag = nullopt);
    template <typename T> void           AddLeavesToVector(vector<string>& vecToAddTo, optional<string> tag = nullopt);

  }  // end Interfaces namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------