/// ---------------------------------------------------------------------------
/*! \file   TreeInterfaces.h
 *  \author Derek Anderson
 *  \date   03.05.2024
 *
 *  TTree-related interfaces.
 */
/// ---------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_TREEINTERFACES_H
#define SCORRELATORUTILITIES_TREEINTERFACES_H

// c++ utilities
#include <limits>
#include <string>
// root libraries
#include <TTree.h>
#include <TChain.h>
#include <TNtuple.h>

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace Interfaces {

    // tree interfaces --------------------------------------------------------

    // helper methods
    template <typename T> int64_t GetEntry(T* tree, const uint64_t entry);
    template <typename T> int64_t LoadTree(T* tree, const uint64_t entry, int& current);

    // ========================================================================
    //! Base tree I/O interface
    // ========================================================================
    /*! Base interface for I/O between TTree's and the
     *  various info objects used throughout the
     *  sPHENIX Cold QCD ENC analysis framework.
     *
     *  n.b. only a handful of types are defined for
     *  setting branches; others can always be added
     *  later.
     *
     *  TODO gist is that all of the tedious branch setting
     *  is done here, then:
     *    (1) Derived classes are made for each *Info type
     *        (e.g. JetInfo) which
     *        - Tell how to translate each type into a
     *          group of atomic types, one for each
     *          member
     *        - And tell how to add a scalar (0D), vector
     *          (1D), or tensor (2D) of each member
     *    (2) Then in the analysis modules, an interface is
     *        defined that
     *        - Defines the input/output of the module, and
     *        - Maps the input/output *Info types onto the
     *          necessary intermediate, atomic types
     *  The goal is to have an interface that looks
     *  something like this:
     *
     *        // the tree
     *        TTree* tree
     *
     *        // the output
     *        REvtInfo             evt;
     *        std::vector<JetInfo> jets;
     *
     *        // the interfaces
     *        REvtInfoIO evtIO( Dim::Zero );
     *        JetInfoIO  jetIO( Dim::One );
     *
     *        /... somewhere in the code... /
     *        evtIO.AddOutputBranch(evt,  "Tag", tree);
     *        jetIO.AddOutputBranch(jets, "Tag", tree);
     *
     *        /... further on in the code .../
     *        evtIO.SetValues( evt );
     *        jetIO.SetValues( jets );
     *        tree -> Fill();
     *
     *  So some additional thoughts:
     *    - This is going to be painful, but for this to work
     *      I might need to define scalar, 1d vector, and
     *      2d vector atomics as members of each dervied
     *      IO class..
     *    - The Set/GetValues functions might be easily
     *      handled with a parameter pack...
     *    - I might need to instead just pass the dimension
     *      as a parameter to the SetInput/OutputBranch
     *      and Set/GetValues functions...
     *    - Might want to template all the classes so that
     *      it works out-of-the-box for TTrees, TChains, and
     *      TNtuples
     */
    class BaseTreeIO {

      public:

        //! Type of branch
        enum class Typ {Double, Bool, UInt, Int};

        //! Dimensionality of branch
        enum class Dim {Zero, One, Two};

        // default ctor/dtor
        BaseTreeIO()  {};
        ~BaseTreeIO() {};

      protected:

        // make branch names/lists
        virtual std::string MakeBranchName() const;
        virtual std::string MakeLeafList(const Typ type) const;

      private:

        // set input branches
        void SetInputBranch0D(const std::string name, <TYPE>& address, TTree* tree);
        void SetInputBranch1D(const std::string name, <TYPE>& address, TTree* tree);
        void SetInputBranch2D(const std::string name, <TYPE>& address, TTree* tree);

        // set output branches
        void SetOutputBranch0D(const std::string name, <TYPE>& address, TTree* tree);
        void SetOutputBranch1D(const std::string name, <TYPE>& address, TTree* tree);
        void SetOutputBranch2D(const std::string name, <TYPE>& address, TTree* tree);

    };  // end BaseTreeID

  }  // end Interfaces namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
