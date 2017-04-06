#include "L1Trigger/ME0Trigger/src/ME0TriggerBuilder.h"
#include "L1Trigger/ME0Trigger/src/ME0Motherboard.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

const int ME0TriggerBuilder::min_endcap  = ME0DetId::minRegionId;
const int ME0TriggerBuilder::max_endcap  = ME0DetId::maxRegionId;
const int ME0TriggerBuilder::min_chamber = ME0DetId::minChamberId;
const int ME0TriggerBuilder::max_chamber = ME0DetId::maxChamberId;

ME0TriggerBuilder::ME0TriggerBuilder(const edm::ParameterSet& conf)
{
  for (int endc = min_endcap; endc <= max_endcap; endc++)
  {
    for (int cham = min_chamber; cham <= max_chamber; cham++)
    {
      if ((endc <= 0 || endc > MAX_ENDCAPS)    ||
	  (cham <= 0 || cham > MAX_CHAMBERS))
      {
	edm::LogError("L1ME0TPEmulatorSetupError")
	  << "+++ trying to instantiate TMB of illegal ME0 id ["
	  << " endcap = "  << endc 
	  << " chamber = " << cham 
	  << "]; skipping it... +++\n";
	continue;
      }
      tmb_[endc-1][cham-1].reset( new ME0Motherboard(endc, cham, conf) );
    }
  }
}

ME0TriggerBuilder::~ME0TriggerBuilder()
{
}

void ME0TriggerBuilder::build(const ME0PadDigiCollection* gemPads,
					ME0LCTDigiCollection& oc_lct)
{
  for (int endc = min_endcap; endc <= max_endcap; endc++)
  {
    for (int cham = min_chamber; cham <= max_chamber; cham++)
    {
      ME0Motherboard* tmb = tmb_[endc-1][cham-1].get();
      
      // 0th layer means whole chamber.
      ME0DetId detid(endc, 0, cham, 0);
      
      tmb->run(gemPads);
      
      std::vector<ME0LCTDigi> lctV = tmb->readoutLCTs();
      
      if (!lctV.empty()) {
	LogTrace("L1ME0Trigger")
	  << "ME0TriggerBuilder got results in " <<detid
	  << std::endl 
	  << "Put " << lctV.size() << " LCT digi"
	  << ((lctV.size() > 1) ? "s " : " ") << "in collection\n";
	oc_lct.put(std::make_pair(lctV.begin(),lctV.end()), detid);
      }
    } 
  }
}
