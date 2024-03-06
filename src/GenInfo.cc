// ----------------------------------------------------------------------------
// 'GenInfo.cc'
// Derek Anderson
// 03.06.2024
//
// Utility class to hold event-level generator
// information.
// ----------------------------------------------------------------------------

#define SCORRELATORUTILITIES_GENINFO_CC

// class definition
#include "GenInfo.h"

// make comon namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {


  // internal methods ---------------------------------------------------------

  void GenInfo::Minimize() {

    // minimize atomic members
    nChrgPar = numeric_limits<int>::min();
    nNeuPar  = numeric_limits<int>::min();
    isEmbed  = false;
    eSumChrg = numeric_limits<double>::min();
    eSumNeu  = numeric_limits<double>::min();

    // minimize parton info
    partons.first.Minimize();
    partons.second.Minimize();
    return;

  }  // end 'Minimize()'



  void GenInfo::Maximize() {

    // maximize atomic members
    nChrgPar = numeric_limits<int>::max();
    nNeuPar  = numeric_limits<int>::max();
    isEmbed  = false;
    eSumChrg = numeric_limits<double>::max();
    eSumNeu  = numeric_limits<double>::max();

    // maximize parton info
    partons.first.Maximize();
    partons.second.Maximize();
    return;

  }  // end 'Maximize()'



  // public methods -----------------------------------------------------------

  void GenInfo::Reset() {

    Maximize();
    return;

  }  // end 'Reset()'



  void GenInfo::SetInfo(
    PHCompositeNode* topNode,
    const bool embed,
    const vector<int> evtsToGrab
  ) {

    // set embed flag
    isEmbed = embed;

    // set parton info
    isEmbed  = embed;
    if (isEmbed) {
      partons.first  = Tools::GetPartonInfo(topNode, SubEvt::EmbedSignal, HardScatterStatus::First);
      partons.second = Tools::GetPartonInfo(topNode, SubEvt::EmbedSignal, HardScatterStatus::Second);

    } else {
      partons.first  = Tools::GetPartonInfo(topNode, SubEvt::NotEmbedSignal, HardScatterStatus::First);
      partons.second = Tools::GetPartonInfo(topNode, SubEvt::NotEmbedSignal, HardScatterStatus::Second);
    }

    // get sums
    nChrgPar = Tools::GetNumFinalStatePars(topNode, evtsToGrab, Subset::Charged);
    nNeuPar  = Tools::GetNumFinalStatePars(topNode, evtsToGrab, Subset::Neutral);
    eSumChrg = Tools::GetSumFinalStateParEne(topNode, evtsToGrab, Subset::Charged);
    eSumNeu  = Tools::GetSumFinalStateParEne(topNode, evtsToGrab, Subset::Neutral);
    return;

  }  // end 'SetInfo(PHCompositeNode*, vector<int>)'



  // static methods -----------------------------------------------------------

  vector<string> GenInfo::GetListOfMembers() {

    vector<string> members = {
      "nChrgPar",
      "nNeuPar",
      "isEmbed",
      "eSumChrg",
      "eSumNeu"
    };
    AddLeavesToVector<ParInfo>(members, "PartonA");
    AddLeavesToVector<ParInfo>(members, "PartonB");
    return members;

  }  // end 'GetListOfMembers()'



  // ctor/dtor ----------------------------------------------------------------

  GenInfo::GenInfo() {

    /* nothing to do */

  }  // end ctor()



  GenInfo::~GenInfo() {

    /* nothing to do */

  }  // end dtor()



  GenInfo::GenInfo(const Const::Init init) {

    switch (init) {
      case Const::Init::Minimize:
        Minimize();
        break;
      case Const::Init::Maximize:
        Maximize();
        break;
      default:
        Maximize();
        break;
    }

  }  // end ctor(Const::init)



  GenInfo::GenInfo(PHCompositeNode* topNode, const bool embed, vector<int> evtsToGrab) {

    SetInfo(topNode, embed, evtsToGrab);

  }  // end ctor(PHCompositeNode*, int, vector<int>)'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------

