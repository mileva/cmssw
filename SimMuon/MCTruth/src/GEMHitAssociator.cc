#include "SimMuon/MCTruth/interface/GEMHitAssociator.h"

using namespace std;

// Constructor
GEMHitAssociator::GEMHitAssociator(const edm::Event& e, const edm::EventSetup& eventSetup, const edm::ParameterSet& conf):

  GEMdigisimlinkTag(conf.getParameter<edm::InputTag>("GEMdigisimlinkTag")),
  // CrossingFrame used or not ?
  crossingframe(conf.getParameter<bool>("crossingframe")),
  GEMsimhitsTag(conf.getParameter<edm::InputTag>("GEMsimhitsTag")),
  GEMsimhitsXFTag(conf.getParameter<edm::InputTag>("GEMsimhitsXFTag"))

{
  if (crossingframe) {
    
    edm::Handle<CrossingFrame<PSimHit> > cf;
    LogTrace("GEMHitAssociator") <<"getting CrossingFrame<PSimHit> collection - "<<GEMsimhitsXFTag;
    e.getByLabel(GEMsimhitsXFTag, cf);
    
    std::auto_ptr<MixCollection<PSimHit> > 
      GEMsimhits( new MixCollection<PSimHit>(cf.product()) );
    LogTrace("GEMHitAssociator") <<"... size = "<<GEMsimhits->size();

    //   MixCollection<PSimHit> & simHits = *hits;
    
    for(MixCollection<PSimHit>::MixItr hitItr = GEMsimhits->begin();
	hitItr != GEMsimhits->end(); ++hitItr) 
      {
	_SimHitMap[hitItr->detUnitId()].push_back(*hitItr);
      }
    
  } else if (!(GEMsimhitsTag.label().empty())) {
    edm::Handle<edm::PSimHitContainer>   GEMsimhits;
    LogTrace("GEMHitAssociator") <<"getting PSimHit collection - "<<  GEMsimhitsTag;
    e.getByLabel(GEMsimhitsTag,  GEMsimhits);    
    LogTrace(" GEMHitAssociator") <<"... size = "<< GEMsimhits->size();
    
    // arrange the hits by detUnit
    for(edm::PSimHitContainer::const_iterator hitItr = GEMsimhits->begin();
	hitItr != GEMsimhits->end(); ++hitItr)
      {
	_SimHitMap[hitItr->detUnitId()].push_back(*hitItr);
      }
  }

  edm::Handle< edm::DetSetVector<GEMDigiSimLink> > thelinkDigis;
  LogTrace("GEMHitAssociator") <<"getting GEMDigiSimLink collection - "<<GEMdigisimlinkTag;
  e.getByLabel(GEMdigisimlinkTag, thelinkDigis);
  _thelinkDigis = thelinkDigis;
}
// end of constructor

std::vector<GEMHitAssociator::SimHitIdpr> GEMHitAssociator::associateRecHit(const TrackingRecHit & hit) {
  
  std::vector<SimHitIdpr> matched;

  const TrackingRecHit * hitp = &hit;
  const GEMRecHit * gemrechit = dynamic_cast<const  GEMRecHit *>(hitp);

  if (gemrechit) {
    
    GEMDetId gemDetId = gemrechit->gemId();
    int fstrip = gemrechit->firstClusterStrip();
    int cls = gemrechit->clusterSize();
    int bx = gemrechit->BunchX();
    
    for(int i = fstrip; i < fstrip+cls; ++i) {
      std::set<GEMDigiSimLink> links = findGEMDigiSimLink(gemDetId.rawId(),i,bx);
      
      if (links.empty()) edm::LogWarning("GEMHitAssociator")
	<<"*** WARNING in GEMHitAssociator::associateRecHit, GEMRecHit "<<*gemrechit<<", strip "<<i<<" has no associated GEMDigiSimLink !"<<endl;
      
      for(std::set<GEMDigiSimLink>::iterator itlink = links.begin(); itlink != links.end(); ++itlink) {
	SimHitIdpr currentId(itlink->getTrackId(),itlink->getEventId());
	if(find(matched.begin(),matched.end(),currentId ) == matched.end())
	  matched.push_back(currentId);
      }
    }
    
  } else edm::LogWarning("GEMHitAssociator")<<"*** WARNING in GEMHitAssociator::associateRecHit, null dynamic_cast !";
  
  return  matched;
}
  
std::set<GEMDigiSimLink>  GEMHitAssociator::findGEMDigiSimLink(uint32_t gemDetId, int strip, int bx){

  std::set<GEMDigiSimLink> links;

  for (edm::DetSetVector<GEMDigiSimLink>::const_iterator itlink = _thelinkDigis->begin(); itlink != _thelinkDigis->end(); itlink++){
    for(edm::DetSet<GEMDigiSimLink>::const_iterator digi_iter=itlink->data.begin();digi_iter != itlink->data.end();++digi_iter){

      uint32_t detid = digi_iter->getDetUnitId();
      int str = digi_iter->getStrip();
      int bunchx = digi_iter->getBx();

      if(detid == gemDetId && str == strip && bunchx == bx){
        links.insert(*digi_iter);
      }

    }
  }

  return links;
}


