/*
* See header file for a description of this class.
*
* $Date: 2014/02/04 10:16:35 $
* $Revision: 1.1 $
* \author M. Maggi -- INFN Bari
*/



#include "RecoLocalMuon/GEMRecHit/interface/ME0RecHitBaseAlgo.h"
#include "Geometry/GEMGeometry/interface/ME0EtaPartition.h"
#include "DataFormats/GEMDigi/interface/ME0DigiPreRecoCollection.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//rumi
#include "RecoLocalMuon/GEMRecHit/src/ME0ClusterContainer.h"
#include "RecoLocalMuon/GEMRecHit/src/ME0Cluster.h"
#include "RecoLocalMuon/GEMRecHit/src/ME0Clusterizer.h"
#include "RecoLocalMuon/GEMRecHit/src/ME0MaskReClusterizer.h"
#include "DataFormats/GEMDigi/interface/ME0DigiCollection.h"
//rumi end

ME0RecHitBaseAlgo::ME0RecHitBaseAlgo(const edm::ParameterSet& config) {}

ME0RecHitBaseAlgo::~ME0RecHitBaseAlgo(){}


// Build all hits in the range associated to the layerId, at the 1st step.
edm::OwnVector<ME0RecHit> ME0RecHitBaseAlgo::reconstruct(const ME0DetId& me0Id,
const ME0DigiPreRecoCollection::Range& digiRange){
  edm::OwnVector<ME0RecHit> result;

  for (ME0DigiPreRecoCollection::const_iterator digi = digiRange.first;
       digi != digiRange.second;digi++) {
    
    LocalError tmpErr;
    LocalPoint point;
    // Call the compute method
    bool OK = this->compute(*digi, point, tmpErr);
    if (!OK) continue;
    ME0RecHit* recHit = new ME0RecHit(me0Id,digi->tof(),point,tmpErr);
    result.push_back(recHit);
  }
  return result;
}

//rumi

// Build all hits in the range associated to the layerId, at the 1st step.
edm::OwnVector<ME0RecHit> ME0RecHitBaseAlgo::reconstructReal(const ME0EtaPartition& roll,
							     const ME0DetId& me0Id,
							     const ME0DigiCollection::Range& digiRange,
                                                             const EtaPartitionMask& mask){
  edm::OwnVector<ME0RecHit> result; 


  ME0Clusterizer clizer;
  ME0ClusterContainer tcls = clizer.doAction(digiRange);
  ME0MaskReClusterizer mrclizer;
  ME0ClusterContainer cls = mrclizer.doAction(me0Id,tcls,mask);


  for (ME0ClusterContainer::const_iterator cl = cls.begin();
       cl != cls.end(); cl++){
    
    LocalError tmpErr;
    LocalPoint point;
    // Call the computeReal method
//    bool OK = this->compute(roll, *cl, point, tmpErr);
    bool OK = this->computeReal(roll, *cl, point, tmpErr);
    if (!OK) continue;

    // Build a new pair of 1D rechit 
    int firstClustStrip= cl->firstStrip();
    int clusterSize=cl->clusterSize(); 
    ME0RecHit*  recHit = new ME0RecHit(me0Id,cl->bx(),firstClustStrip,clusterSize,point,tmpErr);


    result.push_back(recHit);
  }
  return result;

}
