#ifndef L1Trigger_ME0Trigger_ME0TriggerProducer_h
#define L1Trigger_ME0Trigger_ME0TriggerProducer_h

/** \class ME0TriggerProducer
 *
 * \author Sven Dildick (TAMU).
 *
 */

#include "DataFormats/GEMDigi/interface/ME0PadDigiCollection.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

class ME0TriggerBuilder;

class ME0TriggerProducer : public edm::one::EDProducer<edm::one::SharedResources>
{
 public:
  explicit ME0TriggerProducer(const edm::ParameterSet&);
  ~ME0TriggerProducer();

  //virtual void beginRun(const edm::EventSetup& setup);
  virtual void produce(edm::Event&, const edm::EventSetup&);

 private:
  edm::InputTag me0PadDigiProducer_;
  edm::EDGetTokenT<ME0PadDigiCollection> me0_pad_token_;
 
  std::unique_ptr<ME0TriggerBuilder> lctBuilder_;
};

#endif
