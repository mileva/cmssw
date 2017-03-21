#ifndef RecoLocalMuon_ME0RecHitProducer_h
#define RecoLocalMuon_ME0RecHitProducer_h

/** \class ME0RecHitProducer
 *  Module for ME0RecHit production. 
 *  
 *  $Date: 2014/02/04 10:53:23 $
 *  $Revision: 1.1 $
 *  \author M. Maggim -- INFN Bari
 */


#include <memory>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include <bitset>
#include <map>

#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/MuonDetId/interface/ME0DetId.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/GEMDigi/interface/ME0DigiPreRecoCollection.h"

#include "Geometry/GEMGeometry/interface/ME0EtaPartition.h"
#include "Geometry/GEMGeometry/interface/ME0Geometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "DataFormats/MuonDetId/interface/ME0DetId.h"
#include "DataFormats/GEMRecHit/interface/ME0RecHit.h"

#include "RecoLocalMuon/GEMRecHit/interface/ME0RecHitBaseAlgo.h"
#include "RecoLocalMuon/GEMRecHit/interface/ME0RecHitAlgoFactory.h"
#include "DataFormats/GEMRecHit/interface/ME0RecHitCollection.h"

#include <string>

//rumi
#include "DataFormats/GEMDigi/interface/ME0DigiCollection.h"
// #include "CondFormats/GEMObjects/interface/ME0MaskedStrips.h"
// #include "CondFormats/DataRecord/interface/ME0MaskedStripsRcd.h"
// #include "CondFormats/GEMObjects/interface/ME0DeadStrips.h"
// #include "CondFormats/DataRecord/interface/ME0DeadStripsRcd.h"
#include "ME0EtaPartitionMask.h"


namespace edm {
  class ParameterSet;
  class Event;
  class EventSetup;
}
//rumi end

class ME0RecHitBaseAlgo;

class ME0RecHitProducer : public edm::stream::EDProducer<> {

public:
  /// Constructor
  ME0RecHitProducer(const edm::ParameterSet& config);

  /// Destructor
  virtual ~ME0RecHitProducer();

  // Method that access the EventSetup for each run
  virtual void beginRun(const edm::Run&, const edm::EventSetup& ) override;

  /// The method which produces the rechits
  virtual void produce(edm::Event& event, const edm::EventSetup& setup) override;

private:

  // The label to be used to retrieve ME0 digis from the event
  edm::EDGetTokenT<ME0DigiPreRecoCollection> m_token;

//rumi
  // The token to be used to retrieve ME0 realistic digis from the event
  edm::EDGetTokenT<ME0DigiCollection> theME0TrivDigiToken;
//rumi end

  // The reconstruction algorithm
  ME0RecHitBaseAlgo *theAlgo;

//rumi
  //   static std::string theAlgoName;
  // ME0MaskedStrips* ME0MaskedStripsObj;
  // Object with mask-strips-vector for all the ME0 Detectors

  // ME0DeadStrips* ME0DeadStripsObj;
  // Object with dead-strips-vector for all the ME0 Detectors

  // std::string maskSource;
  // std::string deadSource;

  // std::vector<ME0MaskedStrips::MaskItem> MaskVec;
  // std::vector<ME0DeadStrips::DeadItem> DeadVec;

};

#endif

