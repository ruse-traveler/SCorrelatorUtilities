// ----------------------------------------------------------------------------
// 'Constants.h'
// Derek Anderson
// 11.16.2023
//
// Various constants used throughout the SColdQcdCorrelatorAnalysis
// namespace are collected here.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_CONSTANTS_H
#define SCORRELATORUTILITIES_CONSTANTS_H

// c++ utilities
#include <map>
#include <string>
#include <cstdint>

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace Const {

    // enums ------------------------------------------------------------------

    // info intialization options
    enum class Init {Minimize, Maximize};

    // object types
    enum Object {Track, Cluster, Flow, Particle, Unknown};

    // subsystem indices
    enum Subsys {Mvtx, Intt, Tpc, EMCal, IHCal, OHCal};

    // particle charge subsets
    enum Subset {All, Charged, Neutral};

    // subevent options
    enum SubEvtOpt {Everything, OnlySignal, AllBkgd, PrimaryBkgd, Pileup, Specific};

    // special subevent indices
    enum SubEvt {
      Background     = 0,
      NotEmbedSignal = 1,
      EmbedSignal    = 2
    };

    // hard scatter product statuses
    enum HardScatterStatus {
      First  = 23,
      Second = 24
    };

    // parton pdg codes
    enum Parton {
      Down    = 1,
      Up      = 2,
      Strange = 3,
      Charm   = 4,
      Bottom  = 5,
      Top     = 6,
      Gluon   = 21
    };



    // constants --------------------------------------------------------------

    // tracking-related constants
    inline uint16_t const &NMvtxLayer() {
      static uint16_t nMvtxLayer = 3;
      return nMvtxLayer;
    }

    inline uint16_t const &NInttLayer() {
      static uint16_t nInttLayer = 8;
      return nInttLayer;
    }

    inline uint16_t const &NTpcLayer() {
      static uint16_t nTpcLayer = 48;
      return nTpcLayer;
    }

    inline uint16_t const &NTpcSector() {
      static uint16_t nTpcSector = 12;
      return nTpcSector;
    }

    // charged pion mass in GeV/c^2
    inline double const &MassPion() {
      static double mPion = 0.140;
      return mPion;
    }



    // maps -------------------------------------------------------------------

    // map of PID onto charges
    inline map<int, float> &MapPidOntoCharge() {
      static map<int, float> mapPidOntoCharge = {
        {11, -1.},
        {12, 0.},
        {13, -1.},
        {14, 0.},
        {15, -1.},
        {16, 0.},
        {22, 0.},
        {23, 0.},
        {24, 1.},
        {111, 0.},
        {130, 0.},
        {211, 1.},
        {221, 0.},
        {310, 0.},
        {321, 1.},
        {421, 0.},
        {431, 1.},
        {441, 1.},
        {2112, 1.},
        {2212, 1.},
        {3112, -1.},
        {3122, 0.},
        {3212, 0.},
        {3222, 1.},
        {3322, 0.},
        {700201, 0.},
        {700202, 2.},
        {700301, 0.},
        {700302, 3.}
      };
      return mapPidOntoCharge;
    }

    // map of node name onto subsystem index
    inline map<string, int> MapNodeOntoIndex() {
      static map<string, int> mapNodeOntoIndex = {
        {"CLUSTER_CEMC", Subsys::EMCal},
        {"CLUSTER_HCALIN", Subsys::IHCal},
        {"CLUSTER_HCALOUT", Subsys::OHCal}
      };
      return mapNodeOntoIndex;
    }

    // map of forbidden strings onto good ones
    inline map<string, string> MapBadOntoGoodStrings() {
      static map<string, string> mapBadOntoGoodStrings = {
        {"/", "_"},
        {"(", "_"},
        {")", ""},
        {"+", "plus"},
        {"-", "minus"},
        {"*", "star"},
      };
      return mapBadOntoGoodStrings;
    }

  }  // end Const namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
