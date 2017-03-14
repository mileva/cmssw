/*
 *  See header file for a description of this class.
 *
 *  \author M. Maggi -- INFN Bari
 *  \modified for ME0  R. Hadjiiska -- INRNE Sofia
 */



#include "RecoLocalMuon/GEMRecHit/interface/ME0TrivRecHitBaseAlgo.h"
#include "RecoLocalMuon/GEMRecHit/src/ME0ClusterContainer.h"
#include "RecoLocalMuon/GEMRecHit/src/ME0Cluster.h"
#include "RecoLocalMuon/GEMRecHit/src/ME0Clusterizer.h"
#include "RecoLocalMuon/GEMRecHit/src/ME0MaskReClusterizer.h"

#include "Geometry/GEMGeometry/interface/ME0EtaPartition.h"
#include "DataFormats/GEMDigi/interface/ME0DigiCollection.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


ME0TrivRecHitBaseAlgo::ME0TrivRecHitBaseAlgo(const edm::ParameterSet& config) {
  //  theSync = ME0TrivTTrigSyncFactory::get()->create(config.getParameter<string>("tTrigMode"),
  //config.getParameter<ParameterSet>("tTrigModeConfig"));
}

ME0TrivRecHitBaseAlgo::~ME0TrivRecHitBaseAlgo(){}


// Build all hits in the range associated to the layerId, at the 1st step.
edm::OwnVector<ME0TrivRecHit> ME0TrivRecHitBaseAlgo::reconstruct(const ME0EtaPartition& roll,
							 const ME0DetId& me0Id,
							 const ME0DigiCollection::Range& digiRange,
                                                         const EtaPartitionMask& mask) {
  edm::OwnVector<ME0TrivRecHit> result; 


  ME0Clusterizer clizer;
  ME0ClusterContainer tcls = clizer.doAction(digiRange);
  ME0MaskReClusterizer mrclizer;
  ME0ClusterContainer cls = mrclizer.doAction(me0Id,tcls,mask);


  for (ME0ClusterContainer::const_iterator cl = cls.begin();
       cl != cls.end(); cl++){
    
    LocalError tmpErr;
    LocalPoint point;
    // Call the compute method
    bool OK = this->compute(roll, *cl, point, tmpErr);
    if (!OK) continue;

    // Build a new pair of 1D rechit 
    int firstClustStrip= cl->firstStrip();
    int clusterSize=cl->clusterSize(); 
    ME0TrivRecHit*  recHit = new ME0TrivRecHit(me0Id,cl->bx(),firstClustStrip,clusterSize,point,tmpErr);


    result.push_back(recHit);
  }
  return result;
}
