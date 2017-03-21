#ifndef RecoLocalMuon_ME0TrivRecHit_ME0TrivRecHitProducer_h
#define RecoLocalMuon_ME0TrivRecHit_ME0TrivRecHitProducer_h

/** \class ME0TrivRecHitProducer
 *  Module for ME0TrivRecHit production. 
 *  
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

class ME0TrivRecHitBaseAlgo;

class ME0TrivRecHitProducer : public edm::stream::EDProducer<> {

public:
  /// Constructor
  ME0TrivRecHitProducer(const edm::ParameterSet& config);

  /// Destructor
  virtual ~ME0TrivRecHitProducer();

  // Method that access the EventSetup for each run
  virtual void beginRun(const edm::Run&, const edm::EventSetup& ) override;

  /// The method which produces the rechits
  virtual void produce(edm::Event& event, const edm::EventSetup& setup) override;

private:

  // The token to be used to retrieve ME0 realistic digis from the event
  edm::EDGetTokenT<ME0DigiCollection> theME0TrivDigiToken;

  // The reconstruction algorithm
  ME0TrivRecHitBaseAlgo *theAlgo;
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

