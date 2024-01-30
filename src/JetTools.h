// ----------------------------------------------------------------------------
// 'JetTools.h'
// Derek Anderson
// 10.22.2023
//
// Collection of frequent jet-related methods and types
// utilized in the sPHENIX cold QCD Energy-Energy
// Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once

// c++ utilities
#include <limits>
#include <vector>
#include <optional>
// fastjet libraries
#include <fastjet/PseudoJet.hh>
// analysis utilities
#include "CstTools.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // JetInfo definition -----------------------------------------------------

    struct JetInfo {

      // data members
      uint32_t jetID = numeric_limits<uint32_t>::max();
      uint64_t nCsts = numeric_limits<uint64_t>::max();
      double   ene   = numeric_limits<double>::max();
      double   px    = numeric_limits<double>::max();
      double   py    = numeric_limits<double>::max();
      double   pz    = numeric_limits<double>::max();
      double   pt    = numeric_limits<double>::max();
      double   eta   = numeric_limits<double>::max();
      double   phi   = numeric_limits<double>::max();
      double   area  = numeric_limits<double>::max();

      void SetInfo(fastjet::PseudoJet& pseudojet) {
        nCsts = pseudojet.constituents().size();
        ene   = pseudojet.E();
        px    = pseudojet.px();
        py    = pseudojet.py();
        pz    = pseudojet.pz();
        pt    = pseudojet.perp();
        eta   = pseudojet.pseudorapidity();
        phi   = pseudojet.phi_std();
        return;
      }  // end 'SetInfo(fastjet::PseudoJet)'

      void Reset() {
        jetID = numeric_limits<uint32_t>::max();
        nCsts = numeric_limits<uint64_t>::max();
        ene   = numeric_limits<double>::max();
        px    = numeric_limits<double>::max();
        py    = numeric_limits<double>::max();
        pz    = numeric_limits<double>::max();
        pt    = numeric_limits<double>::max();
        eta   = numeric_limits<double>::max();
        phi   = numeric_limits<double>::max();
        area  = numeric_limits<double>::max();
        return;
      }  // end 'Reset()'

      static vector<string> GetListOfMembers() {
        vector<string> members = {
          "jetID",
          "nCsts",
          "ene",
          "px",
          "py",
          "pz",
          "pt",
          "eta",
          "phi",
          "area"
        };
        return members;
      }  // end 'GetListOfMembers()'

      // overloaded < operator
      friend bool operator<(const JetInfo& lhs, const JetInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isLessThan = (
          (lhs.nCsts < rhs.nCsts) &&
          (lhs.ene   < rhs.ene)   &&
          (lhs.px    < rhs.px)    &&
          (lhs.py    < rhs.py)    &&
          (lhs.pz    < rhs.pz)    &&
          (lhs.pt    < rhs.pt)    &&
          (lhs.eta   < rhs.eta)   &&
          (lhs.phi   < rhs.phi)   &&
          (lhs.area  < rhs.area)
        );
        return isLessThan;
      
      }  // end 'operator<(JetInfo&, JetInfo&)'

      // overloaded > operator
      friend bool operator>(const JetInfo& lhs, const JetInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isGreaterThan = (
          (lhs.nCsts > rhs.nCsts) &&
          (lhs.ene   > rhs.ene)   &&
          (lhs.px    > rhs.px)    &&
          (lhs.py    > rhs.py)    &&
          (lhs.pz    > rhs.pz)    &&
          (lhs.pt    > rhs.pt)    &&
          (lhs.eta   > rhs.eta)   &&
          (lhs.phi   > rhs.phi)   &&
          (lhs.area  > rhs.area)
        );
        return isGreaterThan;
      
      }  // end 'operator<(JetInfo&, JetInfo&)'

      // overloaded <=, >= operators
      inline friend bool operator<=(const JetInfo& lhs, const JetInfo& rhs) {return !(lhs > rhs);}
      inline friend bool operator>=(const JetInfo& lhs, const JetInfo& rhs) {return !(lhs < rhs);}

      // default ctor/dtor
      JetInfo()  {};
      ~JetInfo() {};

      // ctor accepting fastjet pseudojets
      JetInfo(fastjet::PseudoJet& pseudojet) {
        SetInfo(pseudojet);
      }

    };  // end JetInfo def



    // jet methods ------------------------------------------------------------

    bool IsInAcceptance(const JetInfo& jet, const JetInfo& minimum, const JetInfo& maximum) {

      return ((jet >= minimum) && (jet <= maximum));

    }  // end 'IsInAcceptance(JetInfo&, JetInfo&, JetInfo&)'

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
