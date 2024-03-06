// ----------------------------------------------------------------------------
// 'FlowInfo.h'
// Derek Anderson
// 03.06.2024
//
// Utility class to hold information from
// particle flow elements.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_FLOWINFO_H
#define SCORRELATORUTILITIES_FLOWINFO_H

// c++ utilities
#include <limits>
#include <vector>
#include <string>
#include <utility>
// root libraries
#include <Rtypes.h>
// particle flow libraries
#include <particleflowreco/ParticleFlowElement.h>
#include <particleflowreco/ParticleFlowElementContainer.h>
// analysis utilites
#include "Constants.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // FlowInfo definition ------------------------------------------------------

  class FlowInfo {

    private:

      // data members
      int    id   = numeric_limits<int>::max();
      int    type = numeric_limits<int>::max();
      double mass = numeric_limits<double>::max();
      double eta  = numeric_limits<double>::max();
      double phi  = numeric_limits<double>::max();
      double ene  = numeric_limits<double>::max();
      double px   = numeric_limits<double>::max();
      double py   = numeric_limits<double>::max();
      double pz   = numeric_limits<double>::max();
      double pt   = numeric_limits<double>::max();

      // internal methods
      void Minimize();
      void Maximize();

    public:

      // public methods
      void Reset();
      void SetInfo(const ParticleFlowElement* flow);
      bool IsInAcceptance(const FlowInfo& minimum, const FlowInfo& maximum);
      bool IsInAcceptance(const pair<FlowInfo, FlowInfo>& range);

      // static methods
      static vector<string> GetListOfMembers();

      // overloaded operators
      friend bool operator<(const FlowInfo& lhs, const FlowInfo& rhs);
      friend bool operator>(const FlowInfo& lhs, const FlowInfo& rhs);
      friend bool operator<=(const FlowInfo& lhs, const FlowInfo& rhs);
      friend bool operator>=(const FlowInfo& lhs, const FlowInfo& rhs);

      // default ctor/dtor
      FlowInfo();
      ~FlowInfo();

      // ctors accepting arguments
      FlowInfo(const Const::Init init);
      FlowInfo(const ParticleFlowElement* flow);

    // identify this class to ROOT
    ClassDefNV(FlowInfo, 1);

  };  // end FlowInfo definition

}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
