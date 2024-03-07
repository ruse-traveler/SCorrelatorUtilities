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
  namespace Types {

    // ParInfo definition -----------------------------------------------------

    class ParInfo {

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

        // getters
        int    GetPID()     {return pid;}
        int    GetStatus()  {return status;}
        int    GetBarcode() {return barcode;}
        int    GetEmbedID() {return embedID;}
        float  GetCharge()  {return charge;}
        double GetMass()    {return mass;}
        double GetEta()     {return eta;}
        double GetPhi()     {return phi;}
        double GetEne()     {return ene;}
        double GetPX()      {return px;}
        double GetPY()      {return py;}
        double GetPZ()      {return pz;}
        double GetPT()      {return pt;}
        double GetVX()      {return vx;}
        double GetVY()      {return vy;}
        double GetVZ()      {return vz;}
        double GetVR()      {return vr;}

        // setters
        void SetPID(const int arg_pid)         {pid     = arg_pid;}
        void SetStatus(const int arg_status)   {status  = arg_status;}
        void SetBarcode(const int arg_barcode) {barcode = arg_barcode;}
        void SetEmbedID(const int arg_embedID) {embedID = arg_embedID;}
        void SetCharge(const float arg_charge) {charge  = arg_charge;}
        void SetMass(const double arg_mass)    {mass    = arg_mass;}
        void SetEta(const double arg_eta)      {eta     = arg_eta;}
        void SetPhi(const double arg_phi)      {phi     = arg_phi;}
        void SetEne(const double arg_ene)      {ene     = arg_ene;}
        void SetPX(const double arg_px)        {px      = arg_px;}
        void SetPY(const double arg_py)        {py      = arg_py;}
        void SetPZ(const double arg_pz)        {pz      = arg_pz;}
        void SetPT(const double arg_pt)        {pt      = arg_pt;}
        void SetVX(const double arg_vx)        {vx      = arg_vx;}
        void SetVY(const double arg_vy)        {vy      = arg_vy;}
        void SetVZ(const double arg_vz)        {vz      = arg_vz;}
        void SetVR(const double arg_vr)        {vr      = arg_vr;}

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
        friend bool operator <(const ParInfo& lhs, const ParInfo& rhs);
        friend bool operator >(const ParInfo& lhs, const ParInfo& rhs);
        friend bool operator <=(const ParInfo& lhs, const ParInfo& rhs);
        friend bool operator >=(const ParInfo& lhs, const ParInfo& rhs);

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



    // overloaded operator definitions ----------------------------------------

    bool operator <(const ParInfo& lhs, const ParInfo& rhs);
    bool operator >(const ParInfo& lhs, const ParInfo& rhs);
    bool operator <=(const ParInfo& lhs, const ParInfo& rhs);
    bool operator >=(const ParInfo& lhs, const ParInfo& rhs);

  }  // end Types namespace
}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
