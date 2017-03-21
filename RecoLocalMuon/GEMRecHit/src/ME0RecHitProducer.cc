/** \file
 *
 *  $Date: 2013/04/24 17:16:35 $
 *  $Revision: 1.1 $
 *  \author M. Maggi -- INFN Bari
*/

#include "ME0RecHitProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/GEMDigi/interface/ME0DigiCollection.h"

#include "Geometry/GEMGeometry/interface/ME0EtaPartition.h"
#include "Geometry/GEMGeometry/interface/ME0Geometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "DataFormats/MuonDetId/interface/ME0DetId.h"
#include "DataFormats/GEMRecHit/interface/ME0TrivRecHit.h"

#include "RecoLocalMuon/GEMRecHit/interface/ME0TrivRecHitBaseAlgo.h"
#include "RecoLocalMuon/GEMRecHit/interface/ME0TrivRecHitAlgoFactory.h"
#include "DataFormats/GEMRecHit/interface/ME0TrivRecHitCollection.h"

// #include "CondFormats/GEMObjects/interface/ME0MaskedStrips.h"
// #include "CondFormats/DataRecord/interface/ME0MaskedStripsRcd.h"
// #include "CondFormats/GEMObjects/interface/ME0DeadStrips.h"
// #include "CondFormats/DataRecord/interface/ME0DeadStripsRcd.h"

using namespace edm;
using namespace std;


ME0RecHitProducer::ME0RecHitProducer(const edm::ParameterSet& config){

  produces<ME0RecHitCollection>();
 
  m_token = consumes<ME0DigiPreRecoCollection>( config.getParameter<edm::InputTag>("me0DigiLabel") ); 

 
  // Get the concrete reconstruction algo from the factory

  std::string theAlgoName = config.getParameter<std::string>("recAlgo");
  theAlgo = ME0RecHitAlgoFactory::get()->create(theAlgoName,
						config.getParameter<edm::ParameterSet>("recAlgoConfig"));
  // Get masked- and dead-strip information

  /* ME0MaskedStripsObj = new ME0MaskedStrips();

  ME0DeadStripsObj = new ME0DeadStrips();

  maskSource = config.getParameter<std::string>("maskSource");

  if (maskSource == "File") {
    edm::FileInPath fp = config.getParameter<edm::FileInPath>("maskvecfile");
    std::ifstream inputFile(fp.fullPath().c_str(), std::ios::in);
    if ( !inputFile ) {
      std::cerr << "Masked Strips File cannot not be opened" << std::endl;
      exit(1);
    }
    while ( inputFile.good() ) {
      ME0MaskedStrips::MaskItem Item;
      inputFile >> Item.rawId >> Item.strip;
      if ( inputFile.good() ) MaskVec.push_back(Item);
    }
    inputFile.close();
  }

  deadSource = config.getParameter<std::string>("deadSource");

  if (deadSource == "File") {
    edm::FileInPath fp = config.getParameter<edm::FileInPath>("deadvecfile");
    std::ifstream inputFile(fp.fullPath().c_str(), std::ios::in);
    if ( !inputFile ) {
      std::cerr << "Dead Strips File cannot not be opened" << std::endl;
      exit(1);
    }
    while ( inputFile.good() ) {
      ME0DeadStrips::DeadItem Item;
      inputFile >> Item.rawId >> Item.strip;
      if ( inputFile.good() ) DeadVec.push_back(Item);
    }
    inputFile.close();
  }
  */
}


ME0RecHitProducer::~ME0RecHitProducer(){
  delete theAlgo;
  // delete ME0MaskedStripsObj;
  // delete ME0DeadStripsObj;

}



void ME0RecHitProducer::beginRun(const edm::Run& r, const edm::EventSetup& setup){
  // Getting the masked-strip information
  /*
  if ( maskSource == "EventSetup" ) {
    edm::ESHandle<ME0MaskedStrips> readoutMaskedStrips;
    setup.get<ME0MaskedStripsRcd>().get(readoutMaskedStrips);
    const ME0MaskedStrips* tmp_obj = readoutMaskedStrips.product();
    ME0MaskedStripsObj->MaskVec = tmp_obj->MaskVec;
    delete tmp_obj;
  }
  else if ( maskSource == "File" ) {
    std::vector<ME0MaskedStrips::MaskItem>::iterator posVec;
    for ( posVec = MaskVec.begin(); posVec != MaskVec.end(); ++posVec ) {
      ME0MaskedStrips::MaskItem Item; 
      Item.rawId = (*posVec).rawId;
      Item.strip = (*posVec).strip;
      ME0MaskedStripsObj->MaskVec.push_back(Item);
    }
  }
  */
  // Getting the dead-strip information
  /*
  if ( deadSource == "EventSetup" ) {
    edm::ESHandle<ME0DeadStrips> readoutDeadStrips;
    setup.get<ME0DeadStripsRcd>().get(readoutDeadStrips);
    const ME0DeadStrips* tmp_obj = readoutDeadStrips.product();
    ME0DeadStripsObj->DeadVec = tmp_obj->DeadVec;
    delete tmp_obj;
  }
  else if ( deadSource == "File" ) {
    std::vector<ME0DeadStrips::DeadItem>::iterator posVec;
    for ( posVec = DeadVec.begin(); posVec != DeadVec.end(); ++posVec ) {
      ME0DeadStrips::DeadItem Item;
      Item.rawId = (*posVec).rawId;
      Item.strip = (*posVec).strip;
      ME0DeadStripsObj->DeadVec.push_back(Item);
    }
  }
  */
}



void ME0RecHitProducer::produce(edm::Event& event, const edm::EventSetup& setup) {

  // Get the ME0 Geometry
  edm::ESHandle<ME0Geometry> me0Geom;
  setup.get<MuonGeometryRecord>().get(me0Geom);

  // Get the digis from the event
  edm::Handle<ME0DigiPreRecoCollection> digis; 
  event.getByToken(m_token,digis);

  // Get the realistic digis from the event
  edm::Handle<ME0DigiCollection> digisReal; 
  event.getByToken(theME0TrivDigiToken,digisReal);

  // Pass the EventSetup to the algo

  theAlgo->setES(setup);

  // Create the pointer to the collection which will store the rechits

  auto recHitCollection = std::make_unique<ME0RecHitCollection>();

  // Iterate through all digi collections ordered by LayerId   

  ME0DigiPreRecoCollection::DigiRangeIterator me0dgIt;
  for (me0dgIt = digis->begin(); me0dgIt != digis->end();
       ++me0dgIt){
       
    // The layerId
    const ME0DetId& me0Id = (*me0dgIt).first;


    // Get the iterators over the digis associated with this LayerId
    const ME0DigiPreRecoCollection::Range& range = (*me0dgIt).second;

    // Call the reconstruction algorithm    

    edm::OwnVector<ME0RecHit> recHits =
      theAlgo->reconstruct(me0Id, range);
    
    if(recHits.size() > 0)
      recHitCollection->put(me0Id, recHits.begin(), recHits.end());
  }//rumi: end prereco input

//rumi
  // Iterate through all realisitc digi collections ordered by LayerId   
  ME0DigiCollection::DigiRangeIterator me0dgItR;
  for (me0dgItR = digisReal->begin(); me0dgItR != digisReal->end();
       ++me0dgItR){
       
    // The layerId
    const ME0DetId& me0Id = (*me0dgItR).first;

    // Get the GeomDet from the setup
    const ME0EtaPartition* roll = me0Geom->etaPartition(me0Id);

    // Get the iterators over the digisReal associated with this LayerId
    const ME0DigiCollection::Range& range = (*me0dgItR).second;

    // Getting the roll mask, that includes dead strips, for the given ME0Det
    EtaPartitionMask mask;
    /*
    int rawId = me0Id.rawId();
    int Size = ME0MaskedStripsObj->MaskVec.size();
    for (int i = 0; i < Size; i++ ) {
      if ( ME0MaskedStripsObj->MaskVec[i].rawId == rawId ) {
	int bit = ME0MaskedStripsObj->MaskVec[i].strip;
	mask.set(bit-1);
      }
    }

    Size = ME0DeadStripsObj->DeadVec.size();
    for (int i = 0; i < Size; i++ ) {
      if ( ME0DeadStripsObj->DeadVec[i].rawId == rawId ) {
	int bit = ME0DeadStripsObj->DeadVec[i].strip;
	mask.set(bit-1);
      }
    }
    */

    // Call the reconstruction algorithm    
    OwnVector<ME0RecHit> recHits =
      theAlgo->reconstructReal(*roll, me0Id, range, mask);
    
    if(recHits.size() > 0) //FIXME: is it really needed?
      recHitCollection->put(me0Id, recHits.begin(), recHits.end());
  }//end realistic digis input

  event.put(std::move(recHitCollection));

}

