// ----------------------------------------------------------------------------
// 'FlowTools.cc'
// Derek Anderson
// 02.29.2024
//
// Collection of frequent particle flow-related methods utilized
// in the sPHENIX Cold QCD Energy-Energy Correlator analysis.
// ----------------------------------------------------------------------------

#define FLOWTOOLS_CC

// c++ utilities
#include <cassert>
// f4a libraries
#include <fun4all/SubsysReco.h>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// particle flow libraries
#include <particleflowreco/ParticleFlowElement.h>
#include <particleflowreco/ParticleFlowElementContainer.h>
// analysis utilities
#include "FlowTools.h"

// make common namespaces implicit
using namespace std;
using namespace findNode;



namespace SColdQcdCorrelatorAnalysis {

  // particle flow methods --------------------------------------------------

  bool SCorrelatorUtilities::IsInAcceptance(const FlowInfo& flow, const FlowInfo& minimum, const FlowInfo& maximum) {

    return ((flow >= minimum) && (flow <= maximum));

  }  // end 'IsInAcceptance(FlowInfo&, FlowInfo&, FlowInfo&)'



  ParticleFlowElementContainer* SCorrelatorUtilities::GetFlowStore(PHCompositeNode* topNode) {

    ParticleFlowElementContainer* store = findNode::getClass<ParticleFlowElementContainer>(topNode, "ParticleFlowElements");
    if (!store) {
      cerr << PHWHERE
           << "PANIC: Couldn't grab particle flow container!"
           << endl;
      assert(store);
    }
    return store;

  }  // end 'GetFlowStore(PHCompositeNode*)'



  ParticleFlowElementContainer::ConstRange SCorrelatorUtilities::GetParticleFlowObjects(PHCompositeNode* topNode) {

    // get container
    ParticleFlowElementContainer* store = GetFlowStore(topNode);

    // get objects
    ParticleFlowElementContainer::ConstRange objects = store -> getParticleFlowElements();
    return objects;

  }  // end 'GetParticleFlowObjects(PHCompositeNode*)'

}  // end SColdQcdCorrealtorAnalysis namespace

// end ------------------------------------------------------------------------
