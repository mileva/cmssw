/** \file
 *
 *  $Date: 2013/04/24 17:16:35 $
 *  $Revision: 1.1 $
 *  \author M. Maggi -- INFN Bari
*/

#include "GEMRecHitProducerPreReco.h"


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/GEMDigi/interface/GEMDigiCollection.h"
#include "DataFormats/GEMDigi/interface/GEMDigiPreRecoCollection.h"

#include "Geometry/GEMGeometry/interface/GEMEtaPartition.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHit.h"

#include "RecoLocalMuon/GEMRecHit/interface/GEMRecHitBaseAlgoPreReco.h"
#include "RecoLocalMuon/GEMRecHit/interface/GEMRecHitAlgoFactoryPreReco.h"
#include "RecoLocalMuon/GEMRecHit/interface/GEMRecHitBaseAlgo.h"
#include "RecoLocalMuon/GEMRecHit/interface/GEMRecHitAlgoFactory.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"

// #include "CondFormats/GEMObjects/interface/GEMMaskedStrips.h"
// #include "CondFormats/DataRecord/interface/GEMMaskedStripsRcd.h"
// #include "CondFormats/GEMObjects/interface/GEMDeadStrips.h"
// #include "CondFormats/DataRecord/interface/GEMDeadStripsRcd.h"

#include <string>


using namespace edm;
using namespace std;


GEMRecHitProducerPreReco::GEMRecHitProducerPreReco(const ParameterSet& config){

  // Set verbose output

  produces<GEMRecHitCollection>();

  thePreGEMDigiLabel = config.getParameter<InputTag>("gemPreDigiLabel");
  theGEMDigiLabel = config.getParameter<InputTag>("gemDigiLabel");

  // Get the concrete reconstruction algo from the factory

  string thePreAlgoName = config.getParameter<string>("prerecAlgo");
  thePreAlgo = GEMRecHitAlgoFactoryPreReco::get()->create(thePreAlgoName,
						config.getParameter<ParameterSet>("recAlgoConfig"));

  string theAlgoName = config.getParameter<string>("recAlgo");
  theAlgo = GEMRecHitAlgoFactory::get()->create(theAlgoName,
						config.getParameter<ParameterSet>("recAlgoConfig"));

}


GEMRecHitProducerPreReco::~GEMRecHitProducerPreReco(){

  delete thePreAlgo;
  delete theAlgo;
  // delete GEMMaskedStripsObj;
  // delete GEMDeadStripsObj;

}



void GEMRecHitProducerPreReco::beginRun(const edm::Run& r, const edm::EventSetup& setup){

}



void GEMRecHitProducerPreReco::produce(Event& event, const EventSetup& setup) {

//  std::cout << " event loop started  " << std::endl;
  // Get the GEM Geometry

  ESHandle<GEMGeometry> gemGeom;
  setup.get<MuonGeometryRecord>().get(gemGeom);

  // Get the digis from the event

  Handle<GEMDigiPreRecoCollection> predigis;
  event.getByLabel(thePreGEMDigiLabel,predigis);

  Handle<GEMDigiCollection> digis; 
  event.getByLabel(theGEMDigiLabel,digis);

// Create the pointer to the collection which will store the rechits
   auto_ptr<GEMRecHitCollection> recHitCollection(new GEMRecHitCollection());
   

  // Pass the EventSetup to the algo

  thePreAlgo->setES(setup);

  // Iterate through all digi collections ordered by LayerId   

  GEMDigiPreRecoCollection::DigiRangeIterator gempredgIt;
  for (gempredgIt = predigis->begin(); gempredgIt != predigis->end();
       ++gempredgIt){

     std::cout << " in the pseudo digi loop " << std::endl;       
    // The layerId
    const GEMDetId& gemId = (*gempredgIt).first;

   // Get the iterators over the digis associated with this LayerId
    const GEMDigiPreRecoCollection::Range& range = (*gempredgIt).second;


    // Call the reconstruction algorithm    

//    if(gemId.station() == 2 || gemId.station() == 3){
    if(gemId.station() == 3){              ////masking the hits from short station
     std::cout << "station for pseudo digis = " << gemId.station() << std::endl;

    OwnVector<GEMRecHit> recHits =
      thePreAlgo->reconstruct(gemId, range);
    
    if(recHits.size() > 0) //FIXME: is it really needed?
      recHitCollection->put(gemId, recHits.begin(), recHits.end());
   }
  }


   // Pass the EventSetup to the algo
    theAlgo->setES(setup);

   GEMDigiCollection::DigiRangeIterator gemdgIt;
 
   for (gemdgIt = digis->begin(); gemdgIt != digis->end();
       ++gemdgIt){

  ///   std::cout << " in the real digi loop " << std::endl;
     // The layerId
     const GEMDetId& gemId = (*gemdgIt).first;

    // Get the GeomDet from the setup
     const GEMEtaPartition* roll = gemGeom->etaPartition(gemId);

    // Get the iterators over the digis associated with this LayerId
     const GEMDigiCollection::Range& range = (*gemdgIt).second;

     // Getting the roll mask, that includes dead strips, for the given GEMDet
      EtaPartitionMask mask;
  
     if(gemId.station() == 1){
   ///  std::cout << "station for real digis = " << gemId.station() << "layer for real digis " << gemId.layer() << std::endl;

     OwnVector<GEMRecHit> recHits =
     theAlgo->reconstruct(*roll, gemId, range, mask);
    
     if(recHits.size() > 0) //FIXME: is it really needed?
     recHitCollection->put(gemId, recHits.begin(), recHits.end());
   }
  }

    event.put(recHitCollection);

}

