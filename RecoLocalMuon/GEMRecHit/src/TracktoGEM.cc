#include <Geometry/GEMGeometry/interface/GEMGeometry.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonTopologies/interface/RectangularStripTopology.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <DataFormats/GEMRecHit/interface/GEMRecHit.h>
#include <DataFormats/GEMRecHit/interface/GEMRecHitCollection.h>

#include <DataFormats/DetId/interface/DetId.h>
#include <RecoLocalMuon/GEMRecHit/interface/TracktoGEM.h>
#include <ctime>
#include <TMath.h>

ObjectMap2CSC* ObjectMap2CSC::mapInstance = NULL;
ObjectMap2CSC* ObjectMap2CSC::GetInstance(const edm::EventSetup& iSetup){
  if (mapInstance == NULL){
    mapInstance = new ObjectMap2CSC(iSetup);
  }
  return mapInstance;
}

ObjectMap2CSC::ObjectMap2CSC(const edm::EventSetup& iSetup){
  edm::ESHandle<GEMGeometry> gemGeo;
  edm::ESHandle<CSCGeometry> cscGeo;
  
  iSetup.get<MuonGeometryRecord>().get(gemGeo);
  iSetup.get<MuonGeometryRecord>().get(cscGeo);
  
  for (TrackingGeometry::DetContainer::const_iterator it=gemGeo->dets().begin();it<gemGeo->dets().end();it++){
    if(dynamic_cast< GEMChamber* >( *it ) != 0 ){
      GEMChamber* ch = dynamic_cast< GEMChamber* >( *it ); 
      std::vector< const GEMEtaPartition*> roles = (ch->etaPartitions());
      for(std::vector<const GEMEtaPartition*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	GEMDetId gemId = (*r)->id();
	int region=gemId.region();
	if(region!=0){
	  int station=gemId.station();
          int ring=gemId.ring();
          int cscring=ring;
          int cscstation=999;
          if(station==1) cscstation=1;
          else if(station==2) cscstation=999;
          else if(station==3) cscstation=2; //GEMDetId.station() == 3 -> GE2/1 long; change this when the convetion is clear, station()==2 should is not relevant
          else {std::cout << "CSCSegtoGEM: I found station>3" << std::endl; continue;}
	  int gemsegment = gemId.chamber();
	  int cscchamber = gemsegment;

          if(! ((station==1||station==3) && ring ==1) ) {
//            std::cout << "I found a GEM chamber on the station out of range, station number = " << station << "\tring = " <<cscring << std::endl;
            continue;
          }

	  CSCStationIndex2 ind(region,cscstation,cscring,cscchamber);
          std::set<GEMDetId> myrolls;
	  if (rollstoreCSC.find(ind)!=rollstoreCSC.end()) myrolls=rollstoreCSC[ind];
	  myrolls.insert(gemId);
          rollstoreCSC[ind]=myrolls;
	}
      }
    }
  }
}

bool TracktoGEM::ValidGEMSurface(GEMDetId gemid, LocalPoint LocalP, const edm::EventSetup& iSetup)
{
  edm::ESHandle<GEMGeometry> gemGeo;
  iSetup.get<MuonGeometryRecord>().get(gemGeo);

  float locx=LocalP.x(), locy=LocalP.y();//, locz=LocalP.z();
     const Bounds &rollbound = gemGeo->idToDet((gemid))->surface().bounds();
     float boundlength = rollbound.length();
     float boundwidth = rollbound.width();

     float nminx = TMath::Pi()*(18*boundwidth/ TMath::Pi() - boundlength)/18;	//rumi: ?
     float ylimit = ((boundlength)/(boundwidth/2 - nminx/2))*fabs(locx) + boundlength/2 - ((boundlength)/(boundwidth/2 - nminx/2))*(boundwidth/2);
     if(ylimit < -boundlength/2 ) ylimit = -boundlength/2;

     if(fabs(locx) < boundwidth/2 && fabs(locy) < boundlength/2 && locy > ylimit) return true;
     else return false;
}

TracktoGEM::TracktoGEM(edm::Handle<reco::TrackCollection> alltracks, const edm::EventSetup& iSetup,const edm::Event& iEvent,bool debug,const edm::ParameterSet& iConfig,edm::InputTag& tracklabel){ 

 _ThePoints = new GEMRecHitCollection();

 if(tracklabel.label().find("cosmic")==0) theTrackTransformer = new TrackTransformerForCosmicMuons(iConfig);
 else if(tracklabel.label().find("globalCosmic")==0) theTrackTransformer = new TrackTransformerForCosmicMuons(iConfig);
 else theTrackTransformer = new TrackTransformer(iConfig);
 theTrackTransformer->setServices(iSetup);  

 edm::ESHandle<GEMGeometry> gemGeo;
 edm::ESHandle<CSCGeometry> cscGeo;
 
 iSetup.get<TrackingComponentsRecord>().get("SteppingHelixPropagatorAny",thePropagator); 
 iSetup.get<MuonGeometryRecord>().get(gemGeo);
 iSetup.get<MuonGeometryRecord>().get(cscGeo);

std::vector<uint32_t> gemput;
double MaxD=999.;

for (TrackCollection::const_iterator track = alltracks->begin(); track !=alltracks->end(); track++)
{
 Trajectories trajectories = theTrackTransformer->transform(*track);
 if(debug) std::cout << "Building Trajectory from Track. " << std::endl;

 std::vector<uint32_t> gemrolls;
 std::vector<uint32_t> gemrolls2; 
 std::map<uint32_t, int> gemNdtcsc;
 std::map<uint32_t, int> gemrollCounter;

 float tInX = track->innerPosition().X(), tInY = track->innerPosition().Y(), tInZ = track->innerPosition().Z();
 float tOuX = track->outerPosition().X(), tOuY = track->outerPosition().Y(), tOuZ = track->outerPosition().Z();
 if(tInX > tOuX) { float temp=tOuX; tOuX=tInX; tInX=temp; }
 if(tInY > tOuY) { float temp=tOuY; tOuY=tInY; tInY=temp; }
 if(tInZ > tOuZ) { float temp=tOuZ; tOuZ=tInZ; tInZ=temp; }

 if(debug) std::cout << "in (x,y,z): ("<< tInX <<", "<< tInY <<", "<< tInZ << ")" << std::endl;
 if(debug) std::cout << "out (x,y,z): ("<< tOuX <<", "<< tOuY <<", "<< tOuZ << ")" << std::endl;

if(debug) std::cout << "1. Search expeted GEM roll detid !!" << std::endl;
for(trackingRecHit_iterator hit=track->recHitsBegin(); hit != track->recHitsEnd(); hit++)
 {
    if((*hit)->isValid())
    {
      DetId id = (*hit)->geographicalId();
       if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::CSC) 
       {
          const GeomDet *geomDet =  cscGeo->idToDet((*hit)->geographicalId());
          const CSCLayer *csclayer = dynamic_cast<const CSCLayer *>(geomDet);

          CSCDetId cscid(geomDet->geographicalId().rawId());
          if(csclayer) for(Trajectories::const_iterator trajectory = trajectories.begin(); trajectory != trajectories.end(); ++trajectory)
          {
             const BoundPlane & CSCSurface = csclayer->surface();
             const GlobalPoint dcPoint = CSCSurface.toGlobal(LocalPoint(0.,0.,0.));

             TrajectoryMeasurement tMt = trajectory->closestMeasurement(dcPoint);
             TrajectoryStateOnSurface upd2 = (tMt).updatedState();

             if(upd2.isValid() && (cscid.station()==1 || cscid.station()==2) && cscid.ring()==1 )
             {
                LocalPoint trajLP = upd2.localPosition();
                LocalPoint trackLP = (*hit)->localPosition();
                float dx = trajLP.x()-trackLP.x(), dy=trajLP.y()-trackLP.y();//, dz=trajLP.z()-trackLP.z();
                if( dx>10. && dy>10.) continue;	//rumi: why?

                ObjectMap2CSC* TheObjectCSC = ObjectMap2CSC::GetInstance(iSetup);
	        int En = cscid.endcap(), St = cscid.station(), Ri = cscid.ring();
	        int cscSegment = cscid.chamber();
                if(En==2) En= -1; if(Ri==4) Ri =1; 

                CSCStationIndex2 theindex(En,St,Ri,cscSegment);
                std::set<GEMDetId> rollsForThisCSC = TheObjectCSC->GetInstance(iSetup)->GetRolls(theindex);
                for (std::set<GEMDetId>::iterator iteraRoll = rollsForThisCSC.begin();iteraRoll != rollsForThisCSC.end(); iteraRoll++)
                {
	            const GEMEtaPartition* rollasociated = gemGeo->etaPartition(*iteraRoll);
                    TrajectoryStateOnSurface ptss =  thePropagator->propagate(upd2, gemGeo->idToDet(rollasociated->id())->surface());
                    if(ptss.isValid()) if(ValidGEMSurface(rollasociated->id().rawId(), ptss.localPosition(), iSetup))
                    {
                      gemrollCounter[rollasociated->id().rawId()]++;
                      bool check = true;
                      std::vector<uint32_t>::iterator gemroll;
                      for( gemroll=gemrolls.begin() ; gemroll < gemrolls.end(); gemroll++ )
                      if(rollasociated->id().rawId()==*gemroll) check=false; 
                      if(check==true)
                      {
                        gemrolls.push_back(rollasociated->id().rawId());
                        if(debug) std::cout << "1\t Forward GEM roll" << rollasociated->id().rawId() << std::endl;
                      }
                    }
	      	}
             }
          }
       } else { if(debug) std::cout << "1\t The hit is not CSC's.   " << std::endl;} 
    }
 }
 if(debug) std::cout << "First step OK!!\n2. Search nearest CSC sufrace!!" << std::endl;
 std::vector<uint32_t>::iterator gemroll;
 for( gemroll=gemrolls.begin() ; gemroll < gemrolls.end(); gemroll++ )
 {
    GEMDetId gemid(*gemroll);
    const GlobalPoint &rGP = gemGeo->idToDet(*gemroll)->surface().toGlobal(LocalPoint(0,0,0));
    int rEn=gemid.region(), rWr=gemid.ring(), rSt=gemid.station(), rCh=gemid.chamber();

    if (rSt == 2) rSt = 999;
    if (rSt == 3) rSt = 2;  //GEMDetId.station() == 3 -> GE2/1 long; change this when the convetion is clear

    if(gemrollCounter[*gemroll]<3) continue ;	//rumi: check what is this: is this the number of rolls per chamber? If yes - fix it to be 8 according to last gem geometry
    
    uint32_t dtcscid=0; double distance= MaxD;

    for(trackingRecHit_iterator hit=track->recHitsBegin(); hit != track->recHitsEnd(); hit++)
    {
        if((*hit)->isValid())
        {
            DetId id = (*hit)->geographicalId(); 
            if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::CSC)
            {
               const GeomDet *geomDet =  cscGeo->idToDet((*hit)->geographicalId());
               const GlobalPoint &cscGP = cscGeo->idToDet((*hit)->geographicalId())->surface().toGlobal(LocalPoint(0,0,0));
               double dx = rGP.x()-cscGP.x(), dy = rGP.y()-cscGP.y(), dz = rGP.z()-cscGP.z();
               double distanceN = sqrt(dx*dx+dy*dy+dz*dz);

               CSCDetId cscid(geomDet->geographicalId().rawId());
               int En =cscid.endcap(), Ri=cscid.ring(), St=cscid.station(), Ch=cscid.chamber();
               if(En==2) En=-1; if(Ri==4) Ri=1;

               if((rEn-En)==0 && (rSt-St)==0 && (Ch-rCh) ==0 && rWr==1 && (rSt==1 || rSt==2 || rSt==3) && distanceN < distance)	
               {
                   dtcscid=geomDet->geographicalId().rawId();
                   distance = distanceN;
                   if(debug) std::cout << "2\t CSC " <<dtcscid <<" region : " << En << " station : " << St << " Ring : " << Ri << " chamber : " << Ch <<std::endl;
               }
            } 
         }
    }
    if(dtcscid != 0 && distance < MaxD)
    {
       gemrolls2.push_back(*gemroll);
       gemNdtcsc[*gemroll] = dtcscid;
    }
 } 
 if(debug) std::cout << "Second step OK!! \n3. Propagate to GEM from CSC!!" << std::endl;  
 std::vector<uint32_t>::iterator gemroll2;
 for( gemroll2=gemrolls2.begin() ; gemroll2 < gemrolls2.end(); gemroll2++ )
 {
    bool check = true;
    std::vector<uint32_t>::iterator gemput_;
    for( gemput_=gemput.begin() ; gemput_ < gemput.end(); gemput_++ )
    if(*gemroll2==*gemput_) check = false;

    if(check == true)
    {
        uint32_t dtcscid = gemNdtcsc[*gemroll2];
        DetId id(dtcscid);
        if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::CSC)
        {
           const GeomDet *geomDet4 =  cscGeo->idToDet(dtcscid);
           const CSCLayer *csclayer = dynamic_cast<const CSCLayer *>(geomDet4);
        
           if(csclayer) for(Trajectories::const_iterator trajectory = trajectories.begin(); trajectory != trajectories.end(); ++trajectory)
           {
              const BoundPlane & CSCSurface = csclayer->surface();
              const GlobalPoint dcPoint = CSCSurface.toGlobal(LocalPoint(0.,0.,0.));

              TrajectoryMeasurement tMt = trajectory->closestMeasurement(dcPoint);
              TrajectoryStateOnSurface upd2 = (tMt).updatedState();
              if(upd2.isValid())  
              {
                 TrajectoryStateOnSurface ptss =  thePropagator->propagate(upd2, gemGeo->idToDet(*gemroll2)->surface());
                 if(ptss.isValid()) if( ValidGEMSurface(*gemroll2, ptss.localPosition(), iSetup))
                 {
                   float gemGPX = ptss.globalPosition().x();
                   float gemGPY = ptss.globalPosition().y();
                   float gemGPZ = ptss.globalPosition().z();

                   if(tInX > gemGPX || tOuX < gemGPX ) continue;
                   if(tInY > gemGPY || tOuY < gemGPY ) continue;
                   if(tInZ > gemGPZ || tOuZ < gemGPZ ) continue;

                   GEMDetId gemid(*gemroll2); 
                   const GeomDet *geomDet3 = gemGeo->idToDet(*gemroll2);
                   const GEMEtaPartition *aroll = dynamic_cast<const GEMEtaPartition *>(geomDet3);
                   const TrapezoidalStripTopology* top_=dynamic_cast<const TrapezoidalStripTopology*>(&(aroll->topology()));
                   LocalPoint xmin = top_->localPosition(0.);
                   LocalPoint xmax = top_->localPosition((float)aroll->nstrips());
                   float rsize = fabs( xmax.x()-xmin.x() );
                   float stripl = top_->stripLength();
                   //float stripw = top_->pitch();
                  
                   float eyr=1;
                   float locx = ptss.localPosition().x(), locy = ptss.localPosition().y(), locz= ptss.localPosition().z();
                   if( locx < rsize*eyr && locy < stripl*eyr && locz < 1. )
                   {
                      GEMRecHit GEMPoint(*gemroll2,0,LocalPoint(locx,locy,locz));
                      if(debug) std::cout << "3\t Forward Expected GEM " << aroll->id().rawId() <<
                        " \tLocalposition X: " << locx << ", Y: "<< locy << " GlobalPosition(x,y,z) (" << gemGPX <<", "<< gemGPY <<", " << gemGPZ << ")"<< std::endl;
                      GEMPointVector.clear();
                      GEMPointVector.push_back(GEMPoint);
                      _ThePoints->put(*gemroll2,GEMPointVector.begin(),GEMPointVector.end());
                      gemput.push_back(*gemroll2);
                  
                   }
                 }
              }
           }       
        }
    }
 }
 if(debug) std::cout << "last steps OK!! " << std::endl; 
}
}

TracktoGEM::~TracktoGEM(){
}
