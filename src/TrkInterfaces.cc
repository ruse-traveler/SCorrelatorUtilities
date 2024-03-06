// ----------------------------------------------------------------------------
// 'TrkInterfaces.h'
// Derek Anderson
// 03.05.2024
//
// Track-related interfaces.
// ----------------------------------------------------------------------------

#define SCORRELATORUTILITIES_TRKINTERFACES_CC

// namespace definition
#include "TrkInterfaces.h"

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  SvtxTrackMap* Interfaces::GetTrackMap(PHCompositeNode* topNode) {

    // grab track map
    SvtxTrackMap* mapTrks = findNode::getClass<SvtxTrackMap>(topNode, "SvtxTrackMap");
    if (!mapTrks) {
      cerr << PHWHERE
           << "PANIC: SvtxTrackMap node is missing!"
           << endl;
      assert(mapTrks);
    }
    return mapTrks;

  }  // end 'GetTrackMap(PHCompositeNode*)'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
