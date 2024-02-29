// ----------------------------------------------------------------------------
// 'VtxTools.h'
// Derek Anderson
// 12.30.2023
//
// Collection of frequent vertex-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#ifndef VTXTOOLS_H
#define VTXTOOLS_H

// c++ utilities
#include <optional>
// root libraries
#include <Math/Vector3D.h>
// phool libraries
#include <phool/PHCompositeNode.h>
// vertex libraries
#include <globalvertex/GlobalVertex.h>
#include <globalvertex/GlobalVertexMap.h>

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // event methods ----------------------------------------------------------

    GlobalVertexMap* GetVertexMap(PHCompositeNode* topNode);
    GlobalVertex* GetGlobalVertex(PHCompositeNode* topNode, optional<int> iVtxToGrab = nullopt);
    ROOT::Math::XYZVector GetRecoVtx(PHCompositeNode* topNode);

  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

#endif

// end ------------------------------------------------------------------------

