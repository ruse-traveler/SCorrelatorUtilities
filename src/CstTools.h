// ----------------------------------------------------------------------------
// 'CstTools.h'
// Derek Anderson
// 10.22.2023
//
// Collection of frequent constituent-related methods and
// types utilized in the sPHENIX cold QCD Energy-Energy
// Correlator analysis.
// ----------------------------------------------------------------------------

#ifndef CSTTOOLS_H
#define CSTTOOLS_H

// c++ utilities
#include <limits>
#include <string>
#include <vector>
#include <optional>
// fastjet libraries
#include <fastjet/PseudoJet.hh>
// analysis utilities
#include "Constants.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    struct CstInfo {

      // data members
      int    type    = numeric_limits<int>::max();
      int    cstID   = numeric_limits<int>::max();
      int    jetID   = numeric_limits<int>::max();
      int    embedID = numeric_limits<int>::max();
      int    pid     = numeric_limits<int>::max();
      double z       = numeric_limits<double>::max();
      double dr      = numeric_limits<double>::max();
      double ene     = numeric_limits<double>::max();
      double px      = numeric_limits<double>::max();
      double py      = numeric_limits<double>::max();
      double pz      = numeric_limits<double>::max();
      double pt      = numeric_limits<double>::max();
      double eta     = numeric_limits<double>::max();
      double phi     = numeric_limits<double>::max();

      void SetInfo(fastjet::PseudoJet& pseudojet) {
        cstID = pseudojet.user_index();
        ene   = pseudojet.E();
        px    = pseudojet.px();
        py    = pseudojet.py();
        pz    = pseudojet.pz();
        pt    = pseudojet.perp();
        eta   = pseudojet.pseudorapidity();
        phi   = pseudojet.phi_std();
        return;
      }  // end 'SetInfo(fastjet::PseudoJet)'

      void Rest() {
        type    = numeric_limits<int>::max();
        cstID   = numeric_limits<int>::max();
        jetID   = numeric_limits<int>::max();
        embedID = numeric_limits<int>::max();
        pid     = numeric_limits<int>::max();
        z       = numeric_limits<double>::max();
        dr      = numeric_limits<double>::max();
        ene     = numeric_limits<double>::max();
        px      = numeric_limits<double>::max();
        py      = numeric_limits<double>::max();
        pz      = numeric_limits<double>::max();
        pt      = numeric_limits<double>::max();
        eta     = numeric_limits<double>::max();
        phi     = numeric_limits<double>::max();
        return;
      }  // end 'Reset()'

      static vector<string> GetListOfMembers() {
        vector<string> members = {
          "type",
          "cstID",
          "jetID",
          "embedID",
          "pid",
          "z",
          "dr",
          "ene",
          "px",
          "py",
          "pz",
          "pt",
          "eta",
          "phi"
        };
        return members;
      }  // end 'GetListOfMembers()'

      // overloaded < operator
      friend bool operator<(const CstInfo& lhs, const CstInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isLessThan = (
          (lhs.z   < rhs.z)   &&
          (lhs.dr  < rhs.dr)  &&
          (lhs.ene < rhs.ene) &&
          (lhs.px  < rhs.px)  &&
          (lhs.py  < rhs.py)  &&
          (lhs.pz  < rhs.pz)  &&
          (lhs.pt  < rhs.pt)  &&
          (lhs.eta < rhs.eta) &&
          (lhs.phi < rhs.phi)
        );
        return isLessThan;
      
      }  // end 'operator<(CstInfo&, CstInfo&)'

      // overloaded > operator
      friend bool operator>(const CstInfo& lhs, const CstInfo& rhs) {

        // note that some quantities aren't relevant for this comparison
        const bool isGreaterThan = (
          (lhs.z   > rhs.z)   &&
          (lhs.dr  > rhs.dr)  &&
          (lhs.ene > rhs.ene) &&
          (lhs.px  > rhs.px)  &&
          (lhs.py  > rhs.py)  &&
          (lhs.pz  > rhs.pz)  &&
          (lhs.pt  > rhs.pt)  &&
          (lhs.eta > rhs.eta) &&
          (lhs.phi > rhs.phi)
        );
        return isGreaterThan;
      
      }  // end 'operator<(CstInfo&, CstInfo&)'

      // overloaded <=, >= operators
      inline friend bool operator<=(const CstInfo& lhs, const CstInfo& rhs) {return !(lhs > rhs);}
      inline friend bool operator>=(const CstInfo& lhs, const CstInfo& rhs) {return !(lhs < rhs);}

      // default ctor/dtor
      CstInfo()  {};
      ~CstInfo() {};

      // ctor accepting fastjet pseudojets
      CstInfo(fastjet::PseudoJet& pseudojet) {
        SetInfo(pseudojet);
      }

    };  // end CstInfo def



    // constituent methods ----------------------------------------------------

    bool IsInAcceptance(const CstInfo& cst, const CstInfo& minimum, const CstInfo& maximum);

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
