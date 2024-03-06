// ----------------------------------------------------------------------------
// 'TrkInterfaces.h'
// Derek Anderson
// 03.05.2024
//
// Track-related interfaces.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORUTILITIES_TRKINTERFACES_H
#define SCORRELATORUTILITIES_TRKINTERFACES_H

// c++ utilities
#include <cassert>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// tracking libraries
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace Interfaces {

    // track interfaces -------------------------------------------------------

    SvtxTrackMap* GetTrackMap(PHCompositeNode* topNode);

  }  // end Interfaces namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
