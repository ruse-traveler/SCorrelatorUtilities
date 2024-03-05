// ----------------------------------------------------------------------------
// 'ParInfo.h'
// Derek Anderson
// 03.04.2024
//
// Utility class to hold information from
// generated particles.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_PARINFO_H
#define SCORRELATORUTILITIES_PARINFO_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// c++ utilities
#include <limits>
#include <string>
#include <vector>
#include <utility>
// root libraries
#include <Rtypes.h>
#include <Math/Vector4D.h>
// PHG4 libraries
#include <g4main/PHG4Particle.h>
// hepmc libraries
#include <HepMC/GenParticle.h>
// analysis utilities
#include "Constants.h"

#pragma GCC diagnostic pop

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // ParInfo definition -----------------------------------------------------

  struct ParInfo {

    private:

      // data members
      int    pid     = numeric_limits<int>::max();
      int    status  = numeric_limits<int>::max();
      int    barcode = numeric_limits<int>::max();
      int    embedID = numeric_limits<int>::max();
      float  charge  = numeric_limits<float>::max();
      double mass    = numeric_limits<double>::max();
      double eta     = numeric_limits<double>::max();
      double phi     = numeric_limits<double>::max();
      double ene     = numeric_limits<double>::max();
      double px      = numeric_limits<double>::max();
      double py      = numeric_limits<double>::max();
      double pz      = numeric_limits<double>::max();
      double pt      = numeric_limits<double>::max();
      double vx      = numeric_limits<double>::max();
      double vy      = numeric_limits<double>::max();
      double vz      = numeric_limits<double>::max();
      double vr      = numeric_limits<double>::max();

      //internal methods
      void Minimize();
      void Maximize();

    public:

      // public methods
      void Reset();
      void SetInfo(const HepMC::GenParticle* particle, const int event);
      void SetInfo(const PHG4Particle* particle, const int event);
      bool IsInAcceptance(const ParInfo& minimum, const ParInfo& maximum);
      bool IsInAcceptance(const pair<ParInfo, ParInfo>& range);
      bool IsFinalState();
      bool IsHardScatterProduct();
      bool IsParton();
      bool IsOutgoingParton();

      // static methods
      static vector<string> GetListOfMembers();

      // overloaded operators
      friend bool operator<(const ParInfo& lhs, const ParInfo& rhs);
      friend bool operator>(const ParInfo& lhs, const ParInfo& rhs);
      friend bool operator<=(const ParInfo& lhs, const ParInfo& rhs);
      friend bool operator>=(const ParInfo& lhs, const ParInfo& rhs);

      // default ctor/dtor
      ParInfo();
      ~ParInfo();

      // ctors accepting arguments
      ParInfo(const Const::Init init);
      ParInfo(HepMC::GenParticle* particle, const int event);
      ParInfo(PHG4Particle* particle, const int event);

    // identify this class to ROOT
    ClassDefNV(ParInfo, 1)

  };  // end ParInfo definition

}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
