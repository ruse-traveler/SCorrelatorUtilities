// ----------------------------------------------------------------------------
// 'CstInfo.h'
// Derek Anderson
// 03.03.2024
//
// Utility class to hold information from
// jet constituents.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_CSTINFO_H
#define SCORRELATORUTILITIES_CSTINFO_H

// c++ utilities
#include <limits>
#include <string>
#include <vector>
#include <utility>
#include <optional>
// root libraries
#include <Rtypes.h>
// fastjet libraries
#include <fastjet/PseudoJet.hh>
// analysis utilities
#include "Constants.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // CstInfo definition -------------------------------------------------------

  class CstInfo {

    private:

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

      // internal methods
      void Minimize();
      void Maximize();

    public:

      // getters
      int    GetType()    {return type;}
      int    GetCstID()   {return cstID;}
      int    GetJetID()   {return jetID;}
      int    GetEmbedID() {return embedID;}
      int    GetPID()     {return pid;}
      double GetZ()       {return z;}
      double GetDR()      {return dr;}
      double GetEne()     {return ene;}
      double GetPx()      {return px;}
      double GetPy()      {return py;}
      double GetPz()      {return pz;}
      double GetPt()      {return pt;}
      double GetEta()     {return eta;}
      double GetPhi()     {return phi;}

      // setters
      void SetType(int arg_type)       {type    = arg_type;}
      void SetCstID(int arg_cstID)     {cstID   = arg_cstID;}
      void SetJetID(int arg_jetID)     {jetID   = arg_jetID;}
      void SetEmbedID(int arg_embedID) {embedID = arg_embedID;}
      void SetPID(int arg_pid)         {pid     = arg_pid;}
      void SetZ(double arg_z)          {z       = arg_z;}
      void SetDR(double arg_dr)        {dr      = arg_dr;}
      void SetEne(double arg_ene)      {ene     = arg_ene;}
      void SetPx(double arg_px)        {px      = arg_px;}
      void SetPy(double arg_py)        {py      = arg_py;}
      void SetPz(double arg_pz)        {pz      = arg_pz;}
      void SetPt(double arg_pt)        {pt      = arg_pt;}
      void SetEta(double arg_eta)      {eta     = arg_eta;}
      void SetPhi(double arg_phi)      {phi     = arg_phi;}

      // public methods
      void Reset();
      void SetInfo(fastjet::PseudoJet& pseudojet);
      bool IsInAcceptance(const CstInfo& minimum, const CstInfo& maximum);
      bool IsInAcceptance(const pair<CstInfo, CstInfo>& range);

      // static methods
      static vector<string> GetListOfMembers();

      // overloaded operators
      friend bool operator<(const CstInfo& lhs, const CstInfo& rhs);
      friend bool operator>(const CstInfo& lhs, const CstInfo& rhs);
      friend bool operator<=(const CstInfo& lhs, const CstInfo& rhs);
      friend bool operator>=(const CstInfo& lhs, const CstInfo& rhs);

      // default ctor/dtor
      CstInfo();
      ~CstInfo();

      // ctors accepting arguments
      CstInfo(const Const::Init init);
      CstInfo(fastjet::PseudoJet& pseudojet);

    // identify this class to ROOT
    ClassDefNV(CstInfo, 1)

  };  // end CstInfo def

}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
