// ----------------------------------------------------------------------------
// 'SCorrelatorUtilities.EvtTools.h'
// Derek Anderson
// 10.30.2023
//
// Collection of frequent event-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#pragma once

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {
  namespace SCorrelatorUtilities {

    // event methods ----------------------------------------------------------

    GlobalVertexMap* GetVertexMap(PHCompositeNode* topNode) {

      // get vertex map
      GlobalVertexMap* mapVtx = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");

      // check if good
      const bool isVtxMapGood = (mapVtx && !(mapVtx -> empty()));
      if (!isVtxMapGood) {
        cerr << PHWHERE
             << "PANIC: GlobalVertexMap node is missing or empty!\n"
             << "       Please turn on the do_global flag in the main macro in order to reconstruct the global vertex!"
             << endl;
        assert(isVtxMapGood);
      }
      return mapVtx;

    }  // end 'GetVertexMap(PHCompositeNode*)'



    GlobalVertex* GetGlobalVertex(PHCompositeNode* topNode, const int iVtxToGrab) {

      // get vertex map
      GlobalVertexMap* mapVtx = GetVertexMap(topNode);

      // get specified vertex
      GlobalVertex* vtx = NULL;
      if (iVtxToGrab < 0) {
        vtx = mapVtx -> begin() -> second;
      } else {
        vtx = mapVtx -> get(iVtxToGrab);
      }

      // check if good
      if (!vtx) {
        cerr << PHWHERE
             << "PANIC: no vertex!"
             << endl;
        assert(vtx);
      }
      return vtx;

    }  // end 'GetGlobalVertex(PHCompositeNode*, int)'


  }  // end SCorrelatorUtilities namespace
}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
