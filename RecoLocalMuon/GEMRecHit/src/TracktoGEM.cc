//#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/GEMGeometry/interface/GEMGeometry.h>
#include <Geometry/DTGeometry/interface/DTGeometry.h>
#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonTopologies/interface/RectangularStripTopology.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include "FWCore/Framework/interface/ESHandle.h"
//#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
//#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include <DataFormats/GEMRecHit/interface/GEMRecHit.h>
//#include <DataFormats/RPCRecHit/interface/RPCRecHitCollection.h>
#include <DataFormats/GEMRecHit/interface/GEMRecHitCollection.h>

//#include "RecoLocalMuon/RPCRecHit/interface/DTSegtoRPC.h"
//#include "RecoLocalMuon/RPCRecHit/interface/CSCSegtoRPC.h"

#include <DataFormats/DetId/interface/DetId.h>
//#include <RecoLocalMuon/RPCRecHit/interface/TracktoRPC.h>
#include <RecoLocalMuon/GEMRecHit/interface/TracktoGEM.h>
#include <ctime>
#include <TMath.h>

/*
ObjectMap2* ObjectMap2::mapInstance = NULL;

ObjectMap2* ObjectMap2::GetInstance(const edm::EventSetup& iSetup){
  if (mapInstance == NULL){
    mapInstance = new ObjectMap2(iSetup);
  }
  return mapInstance;
}
*/
/*
ObjectMap2::ObjectMap2(const edm::EventSetup& iSetup){
  edm::ESHandle<RPCGeometry> rpcGeo;
  edm::ESHandle<DTGeometry> dtGeo;
  
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  iSetup.get<MuonGeometryRecord>().get(dtGeo);
  
  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
    if(dynamic_cast< RPCChamber* >( *it ) != 0 ){
      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it ); 
      std::vector< const RPCRoll*> roles = (ch->rolls());
      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
	RPCDetId rpcId = (*r)->id();
	int region=rpcId.region();
	if(region==0){
	  int wheel=rpcId.ring();
	  int sector=rpcId.sector();
	  int station=rpcId.station();
	  DTStationIndex2 ind(region,wheel,sector,station);
	  std::set<RPCDetId> myrolls;
	  if (rollstoreDT.find(ind)!=rollstoreDT.end()) myrolls=rollstoreDT[ind];
	  myrolls.insert(rpcId);
	  rollstoreDT[ind]=myrolls;
	}
      }
    }
  }
}
*/

/*
int distsector2(int sector1,int sector2){
  if(sector1==13) sector1=4;
  if(sector1==14) sector1=10;
  
  if(sector2==13) sector2=4;
  if(sector2==14) sector2=10;
  
  int distance = std::abs(sector1 - sector2);
  if(distance>6) distance = 12-distance;
  return distance;
}
*/
/*
int distwheel2(int wheel1,int wheel2){
  int distance = std::abs(wheel1 - wheel2);
  return distance;
}
*/
ObjectMap2CSC* ObjectMap2CSC::mapInstance = NULL;

ObjectMap2CSC* ObjectMap2CSC::GetInstance(const edm::EventSetup& iSetup){
  if (mapInstance == NULL){
    mapInstance = new ObjectMap2CSC(iSetup);
  }
  return mapInstance;
}

ObjectMap2CSC::ObjectMap2CSC(const edm::EventSetup& iSetup){
//  edm::ESHandle<RPCGeometry> rpcGeo;
  edm::ESHandle<GEMGeometry> gemGeo;
  edm::ESHandle<CSCGeometry> cscGeo;
  
//  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  iSetup.get<MuonGeometryRecord>().get(gemGeo);
  iSetup.get<MuonGeometryRecord>().get(cscGeo);
  
//  for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++){
  for (TrackingGeometry::DetContainer::const_iterator it=gemGeo->dets().begin();it<gemGeo->dets().end();it++){
//    if(dynamic_cast< RPCChamber* >( *it ) != 0 ){
    if(dynamic_cast< GEMChamber* >( *it ) != 0 ){
//      RPCChamber* ch = dynamic_cast< RPCChamber* >( *it ); 
      GEMChamber* ch = dynamic_cast< GEMChamber* >( *it ); 
//      std::vector< const RPCRoll*> roles = (ch->rolls());
      std::vector< const GEMEtaPartition*> roles = (ch->etaPartitions());
//      for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r){
      for(std::vector<const GEMEtaPartition*>::const_iterator r = roles.begin();r != roles.end(); ++r){
//	RPCDetId rpcId = (*r)->id();
	GEMDetId gemId = (*r)->id();
//	int region=rpcId.region();
	int region=gemId.region();
	if(region!=0){
//	  int station=rpcId.station();
	  int station=gemId.station();
//          int ring=rpcId.ring();
          int ring=gemId.ring();
          int cscring=ring;
          int cscstation=station;
//	  RPCGeomServ rpcsrv(rpcId);
//	  int rpcsegment = rpcsrv.segment();
	  int gemsegment = gemId.chamber();
//	  int cscchamber = rpcsegment; //FIX THIS ACCORDING TO RPCGeomServ::segment()Definition
	  int cscchamber = gemsegment;
          if((station==2||station==3||station==4)&&ring==3){//Adding Ring 3 of RPC to the CSC Ring 2
            cscring = 2;
            std::cout << "I found a GEM chamber on the station out of range, station number = " << station << std::endl;
          }
	  CSCStationIndex2 ind(region,cscstation,cscring,cscchamber);
//          std::set<RPCDetId> myrolls;
          std::set<GEMDetId> myrolls;
	  if (rollstoreCSC.find(ind)!=rollstoreCSC.end()) myrolls=rollstoreCSC[ind];
//	  myrolls.insert(rpcId);
	  myrolls.insert(gemId);
          rollstoreCSC[ind]=myrolls;
	}
      }
    }
  }
}

//bool TracktoRPC::ValidRPCSurface(RPCDetId rpcid, LocalPoint LocalP, const edm::EventSetup& iSetup)
bool TracktoGEM::ValidGEMSurface(GEMDetId gemid, LocalPoint LocalP, const edm::EventSetup& iSetup)
{
//  edm::ESHandle<RPCGeometry> rpcGeo;
//  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  edm::ESHandle<GEMGeometry> gemGeo;
  iSetup.get<MuonGeometryRecord>().get(gemGeo);

//  const GeomDet *whichdet3 = rpcGeo->idToDet(rpcid.rawId());
// ne mi triabva  const GeomDet *whichdet3 = gemGeo->idToDet(gemid.rawId());
//  const RPCRoll *aroll = dynamic_cast<const RPCRoll *>(whichdet3);
// ne mi triabva    const GEMEtaPartition *aroll = dynamic_cast<const GEMEtaPartition *>(whichdet3);
  float locx=LocalP.x(), locy=LocalP.y();//, locz=LocalP.z();
/*
  if(aroll->isBarrel())
  {
     const Bounds &rollbound = rpcGeo->idToDet((rpcid))->surface().bounds();
     float boundlength = rollbound.length();
     float boundwidth = rollbound.width();

     if(fabs(locx) < boundwidth/2 && fabs(locy) < boundlength/2 && locy > -boundlength/2) return true;
     else return false;

   }
*/
//   else if(aroll->isForward())
//   {
//     const Bounds &rollbound = rpcGeo->idToDet((rpcid))->surface().bounds();
     const Bounds &rollbound = gemGeo->idToDet((gemid))->surface().bounds();
     float boundlength = rollbound.length();
     float boundwidth = rollbound.width();

//rumi:: da se proveri kakvo tochno presmiata tova? Zashto e 18
     float nminx = TMath::Pi()*(18*boundwidth/ TMath::Pi() - boundlength)/18;	//rumi: ?
     float ylimit = ((boundlength)/(boundwidth/2 - nminx/2))*fabs(locx) + boundlength/2 - ((boundlength)/(boundwidth/2 - nminx/2))*(boundwidth/2);
     if(ylimit < -boundlength/2 ) ylimit = -boundlength/2;

     if(fabs(locx) < boundwidth/2 && fabs(locy) < boundlength/2 && locy > ylimit) return true;
     else return false;
//   } else return false;
}

//TracktoRPC::TracktoRPC(edm::Handle<reco::TrackCollection> alltracks, const edm::EventSetup& iSetup,const edm::Event& iEvent,bool debug,const edm::ParameterSet& iConfig,edm::InputTag& tracklabel){ 
TracktoGEM::TracktoGEM(edm::Handle<reco::TrackCollection> alltracks, const edm::EventSetup& iSetup,const edm::Event& iEvent,bool debug,const edm::ParameterSet& iConfig,edm::InputTag& tracklabel){ 

// _ThePoints = new RPCRecHitCollection();
 _ThePoints = new GEMRecHitCollection();
// if(alltracks->empty()) return;

 if(tracklabel.label().find("cosmic")==0) theTrackTransformer = new TrackTransformerForCosmicMuons(iConfig);
 else if(tracklabel.label().find("globalCosmic")==0) theTrackTransformer = new TrackTransformerForCosmicMuons(iConfig);
 else theTrackTransformer = new TrackTransformer(iConfig);
 theTrackTransformer->setServices(iSetup);  

// edm::ESHandle<RPCGeometry> rpcGeo;
 edm::ESHandle<GEMGeometry> gemGeo;
// edm::ESHandle<DTGeometry> dtGeo;
 edm::ESHandle<CSCGeometry> cscGeo;
 
 iSetup.get<TrackingComponentsRecord>().get("SteppingHelixPropagatorAny",thePropagator); 
// iSetup.get<MuonGeometryRecord>().get(rpcGeo);
 iSetup.get<MuonGeometryRecord>().get(gemGeo);
// iSetup.get<MuonGeometryRecord>().get(dtGeo);
 iSetup.get<MuonGeometryRecord>().get(cscGeo);

//std::vector<uint32_t> rpcput;
std::vector<uint32_t> gemput;
double MaxD=999.;

for (TrackCollection::const_iterator track = alltracks->begin(); track !=alltracks->end(); track++)
{
 Trajectories trajectories = theTrackTransformer->transform(*track);
 if(debug) std::cout << "Building Trajectory from Track. " << std::endl;

// std::vector<uint32_t> rpcrolls;
// std::vector<uint32_t> rpcrolls2; 
// std::map<uint32_t, int> rpcNdtcsc;
// std::map<uint32_t, int> rpcrollCounter;

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

//if(debug) std::cout << "1. Search expeted RPC roll detid !!" << std::endl;
if(debug) std::cout << "1. Search expeted GEM roll detid !!" << std::endl;
for(trackingRecHit_iterator hit=track->recHitsBegin(); hit != track->recHitsEnd(); hit++)
 {
    if((*hit)->isValid())
    {
      DetId id = (*hit)->geographicalId();
/*
       if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::DT)
       {
          const GeomDet *geomDet =  dtGeo->idToDet((*hit)->geographicalId());
          const DTLayer *dtlayer = dynamic_cast<const DTLayer *>(geomDet);
         if(dtlayer) for(Trajectories::const_iterator trajectory = trajectories.begin(); trajectory != trajectories.end(); ++trajectory)
          {
             const BoundPlane & DTSurface = dtlayer->surface();
             const GlobalPoint dcPoint = DTSurface.toGlobal(LocalPoint(0.,0.,0.));

             TrajectoryMeasurement tMt = trajectory->closestMeasurement(dcPoint);
             TrajectoryStateOnSurface upd2 = (tMt).updatedState();
             if(upd2.isValid())
             {
                LocalPoint trajLP = upd2.localPosition();
                LocalPoint trackLP = (*hit)->localPosition();
                float dx = trajLP.x()-trackLP.x(), dy=trajLP.y()-trackLP.y();//, dz=trajLP.z()-trackLP.z();
                if( dx>10. && dy>10.) continue;

                DTChamberId dtid(geomDet->geographicalId().rawId());
                int dtW=dtid.wheel(), dtS=dtid.sector(), dtT=dtid.station();
                if(dtS==13) dtS=4; if(dtS==14) dtS=10;
                ObjectMap2* TheObject = ObjectMap2::GetInstance(iSetup);
                DTStationIndex2 theindex(0,dtW,dtS,dtT);
                std::set<RPCDetId> rollsForThisDT = TheObject->GetInstance(iSetup)->GetRolls(theindex);
                for(std::set<RPCDetId>::iterator iteraRoll = rollsForThisDT.begin();iteraRoll != rollsForThisDT.end(); iteraRoll++)
                {                                 
	            const RPCRoll* rollasociated = rpcGeo->roll(*iteraRoll);

                    TrajectoryStateOnSurface ptss =  thePropagator->propagate(upd2, rpcGeo->idToDet(rollasociated->id())->surface());
                    if(ptss.isValid()) if(ValidRPCSurface(rollasociated->id().rawId(), ptss.localPosition(), iSetup))
                    {
                      rpcrollCounter[rollasociated->id().rawId()]++;
                      bool check = true;
                      std::vector<uint32_t>::iterator rpcroll;
                      for( rpcroll=rpcrolls.begin() ; rpcroll < rpcrolls.end(); rpcroll++ )
                      if(rollasociated->id().rawId()== *rpcroll) check=false; 
                      if(check==true)
                      {
                        rpcrolls.push_back(rollasociated->id().rawId());
                        RPCGeomServ servId(rollasociated->id().rawId());
                        if(debug) std::cout << "1\t Barrel RPC roll" << rollasociated->id().rawId() << " "<< servId.name().c_str() <<std::endl;
                      }
                    }
	      	}                                 
	     }
	  }
       }
*/
//       else if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::CSC) 
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

//             if(upd2.isValid() && cscid.station()!=4 && cscid.ring()!=1 )
             if(upd2.isValid() && (cscid.station()==1 || cscid.station()==2) && cscid.ring()==1 )	//change this to select GE21 and GE11
             {
                LocalPoint trajLP = upd2.localPosition();
                LocalPoint trackLP = (*hit)->localPosition();
                float dx = trajLP.x()-trackLP.x(), dy=trajLP.y()-trackLP.y();//, dz=trajLP.z()-trackLP.z();
//rumi:
std::cout << "dx = " << dx << "dy = " << dy << std::endl;
                if( dx>10. && dy>10.) continue;	//rumi: why?

                ObjectMap2CSC* TheObjectCSC = ObjectMap2CSC::GetInstance(iSetup);
	        int En = cscid.endcap(), St = cscid.station(), Ri = cscid.ring();
//	        int rpcSegment = cscid.chamber();
	        int cscSegment = cscid.chamber();
                if(En==2) En= -1; if(Ri==4) Ri =1; 

//                CSCStationIndex2 theindex(En,St,Ri,rpcSegment);
                CSCStationIndex2 theindex(En,St,Ri,cscSegment);
//                std::set<RPCDetId> rollsForThisCSC = TheObjectCSC->GetInstance(iSetup)->GetRolls(theindex);
                std::set<GEMDetId> rollsForThisCSC = TheObjectCSC->GetInstance(iSetup)->GetRolls(theindex);
//                for (std::set<RPCDetId>::iterator iteraRoll = rollsForThisCSC.begin();iteraRoll != rollsForThisCSC.end(); iteraRoll++)
                for (std::set<GEMDetId>::iterator iteraRoll = rollsForThisCSC.begin();iteraRoll != rollsForThisCSC.end(); iteraRoll++)
                {
//	            const RPCRoll* rollasociated = rpcGeo->roll(*iteraRoll);
	            const GEMEtaPartition* rollasociated = gemGeo->etaPartition(*iteraRoll);	//GEMEtaPartition

//                    TrajectoryStateOnSurface ptss =  thePropagator->propagate(upd2, rpcGeo->idToDet(rollasociated->id())->surface());
                    TrajectoryStateOnSurface ptss =  thePropagator->propagate(upd2, gemGeo->idToDet(rollasociated->id())->surface());
//                    if(ptss.isValid()) if(ValidRPCSurface(rollasociated->id().rawId(), ptss.localPosition(), iSetup))
                    if(ptss.isValid()) if(ValidGEMSurface(rollasociated->id().rawId(), ptss.localPosition(), iSetup))
                    {
//                      rpcrollCounter[rollasociated->id().rawId()]++;
                      gemrollCounter[rollasociated->id().rawId()]++;
                      bool check = true;
//                      std::vector<uint32_t>::iterator rpcroll;
                      std::vector<uint32_t>::iterator gemroll;
//                      for( rpcroll=rpcrolls.begin() ; rpcroll < rpcrolls.end(); rpcroll++ )
                      for( gemroll=gemrolls.begin() ; gemroll < gemrolls.end(); gemroll++ )
//                      if(rollasociated->id().rawId()==*rpcroll) check=false; 
                      if(rollasociated->id().rawId()==*gemroll) check=false; 
                      if(check==true)
                      {
//                        rpcrolls.push_back(rollasociated->id().rawId());
                        gemrolls.push_back(rollasociated->id().rawId());
//                        RPCGeomServ servId(rollasociated->id().rawId());
//                        if(debug) std::cout << "1\t Forward RPC roll" << rollasociated->id().rawId() << " "<< servId.name().c_str() <<std::endl;
                        if(debug) std::cout << "1\t Forward GEM roll" << rollasociated->id().rawId() << std::endl;
                      }
                    }
	      	}
             }
          }
//       } else { if(debug) std::cout << "1\t The hit is not DT/CSC's.   " << std::endl;} 
       } else { if(debug) std::cout << "1\t The hit is not CSC's.   " << std::endl;} 
    }
 }
// if(debug) std::cout << "First step OK!!\n2. Search nearest DT/CSC sufrace!!" << std::endl;
 if(debug) std::cout << "First step OK!!\n2. Search nearest CSC sufrace!!" << std::endl;
// std::vector<uint32_t>::iterator rpcroll;
 std::vector<uint32_t>::iterator gemroll;
// for( rpcroll=rpcrolls.begin() ; rpcroll < rpcrolls.end(); rpcroll++ )
 for( gemroll=gemrolls.begin() ; gemroll < gemrolls.end(); gemroll++ )
 {
//    RPCDetId rpcid(*rpcroll);
    GEMDetId gemid(*gemroll);
//    const GlobalPoint &rGP = rpcGeo->idToDet(*rpcroll)->surface().toGlobal(LocalPoint(0,0,0));
    const GlobalPoint &rGP = gemGeo->idToDet(*gemroll)->surface().toGlobal(LocalPoint(0,0,0));
//    RPCGeomServ servId(rpcid);
//    int rEn=rpcid.region(), rSe=rpcid.sector(), rWr=rpcid.ring(), rSt=rpcid.station(), rCh=servId.segment();
    int rEn=gemid.region(), rWr=gemid.ring(), rSt=gemid.station(), rCh=gemid.chamber();

//    if(rpcrollCounter[*rpcroll]<3) continue ;	//rumi: check what is this: is this the number of rolls per chamber
    if(gemrollCounter[*gemroll]<3) continue ;	//if yes - fix it to be 8 according to last gem geometry
    
    uint32_t dtcscid=0; double distance= MaxD;

   // if(rSt ==2 && rEn==0) MaxD=100;
   // else if(rSt ==3 && rEn==0) MaxD=100;
   // else if(rSt ==4 && rEn==0) MaxD =150;
    for(trackingRecHit_iterator hit=track->recHitsBegin(); hit != track->recHitsEnd(); hit++)
    {
        if((*hit)->isValid())
        {
            DetId id = (*hit)->geographicalId(); 
/*
            if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::DT)
            {
               const GeomDet *geomDet =  dtGeo->idToDet((*hit)->geographicalId());
               //const DTLayer *dtlayer = dynamic_cast<const DTLayer *>(geomDet);
               const GlobalPoint &dtGP = dtGeo->idToDet((*hit)->geographicalId())->surface().toGlobal(LocalPoint(0,0,0));
               double dx = rGP.x()-dtGP.x(), dy = rGP.y()-dtGP.y(), dz = rGP.z()-dtGP.z();
               double distanceN = sqrt(dx*dx+dy*dy+dz*dz);

               DTChamberId dtid(geomDet->geographicalId().rawId());
               int Se = dtid.sector(), Wh = dtid.wheel(), St = dtid.station();
               if(Se == 13) Se=4; if(Se ==14) Se=10;  

               if( rEn==0&& (rSe-Se)==0 && (rWr-Wh) ==0 && (rSt-St)==0 && distanceN < distance)
               {
                   dtcscid=geomDet->geographicalId().rawId();
                   distance = distanceN;
                   if(debug) std::cout << "2\t DT "<< dtcscid << " Wheel : " << Wh << " station : " << St << " sector : " << Se << std::endl; 
               }
            }
*/
//            else if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::CSC)
            if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::CSC)
            {
               const GeomDet *geomDet =  cscGeo->idToDet((*hit)->geographicalId());
               //const CSCLayer *csclayer = dynamic_cast<const CSCLayer *>(geomDet);
               const GlobalPoint &cscGP = cscGeo->idToDet((*hit)->geographicalId())->surface().toGlobal(LocalPoint(0,0,0));
               double dx = rGP.x()-cscGP.x(), dy = rGP.y()-cscGP.y(), dz = rGP.z()-cscGP.z();
               double distanceN = sqrt(dx*dx+dy*dy+dz*dz);

               CSCDetId cscid(geomDet->geographicalId().rawId());
               int En =cscid.endcap(), Ri=cscid.ring(), St=cscid.station(), Ch=cscid.chamber();
               if(En==2) En=-1; if(Ri==4) Ri=1;

//               if((rEn-En)==0 && (rSt-St)==0 && (Ch-rCh) ==0 && rWr!=1 && rSt!=4 && distanceN < distance)
               if((rEn-En)==0 && (rSt-St)==0 && (Ch-rCh) ==0 && rWr==1 && (rSt==1 || rSt==2) && distanceN < distance)	//set this to GE11 and GE21
               {
                   dtcscid=geomDet->geographicalId().rawId();
                   distance = distanceN;
                   if(debug) std::cout << "2\t CSC " <<dtcscid <<" region : " << En << " station : " << St << " Ring : " << Ri << " chamber : " << Ch <<std::endl;
               }
            } 
         }
    }
    if(dtcscid != 0 && distance < MaxD)	//rumi: check MaxD for GEM case
    {
//       rpcrolls2.push_back(*rpcroll);
       gemrolls2.push_back(*gemroll);
//       rpcNdtcsc[*rpcroll] = dtcscid;
       gemNdtcsc[*gemroll] = dtcscid;
    }
 } 
// if(debug) std::cout << "Second step OK!! \n3. Propagate to RPC from DT/CSC!!" << std::endl;  
 if(debug) std::cout << "Second step OK!! \n3. Propagate to GEM from CSC!!" << std::endl;  
 //std::map<uint32_t, int> rpcput;	//rumi: not commented by me
// std::vector<uint32_t>::iterator rpcroll2;
 std::vector<uint32_t>::iterator gemroll2;
// for( rpcroll2=rpcrolls2.begin() ; rpcroll2 < rpcrolls2.end(); rpcroll2++ )
 for( gemroll2=gemrolls2.begin() ; gemroll2 < gemrolls2.end(); gemroll2++ )
 {
    bool check = true;
//    std::vector<uint32_t>::iterator rpcput_;
    std::vector<uint32_t>::iterator gemput_;
//    for( rpcput_=rpcput.begin() ; rpcput_ < rpcput.end(); rpcput_++ )
    for( gemput_=gemput.begin() ; gemput_ < gemput.end(); gemput_++ )
//    if(*rpcroll2==*rpcput_) check = false;
    if(*gemroll2==*gemput_) check = false;

    if(check == true)
    {
//        uint32_t dtcscid = rpcNdtcsc[*rpcroll2];
        uint32_t dtcscid = gemNdtcsc[*gemroll2];
        DetId id(dtcscid);
/*
        if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::DT)
        {
           const GeomDet *geomDet =  dtGeo->idToDet(dtcscid);
           const DTLayer *dtlayer = dynamic_cast<const DTLayer *>(geomDet);
        
           if(dtlayer) for(Trajectories::const_iterator trajectory = trajectories.begin(); trajectory != trajectories.end(); ++trajectory)
           {
              const BoundPlane & DTSurface = dtlayer->surface();
              const GlobalPoint dcPoint = DTSurface.toGlobal(LocalPoint(0.,0.,0.));

              TrajectoryMeasurement tMt = trajectory->closestMeasurement(dcPoint);
              TrajectoryStateOnSurface upd2 = (tMt).updatedState();
              if(upd2.isValid())
              {
                 TrajectoryStateOnSurface ptss =  thePropagator->propagate(upd2, rpcGeo->idToDet(*rpcroll2)->surface());
                 if(ptss.isValid())  if(ValidRPCSurface(*rpcroll2, ptss.localPosition(), iSetup))
                 {
                   float rpcGPX = ptss.globalPosition().x();
                   float rpcGPY = ptss.globalPosition().y();
                   float rpcGPZ = ptss.globalPosition().z();

                   if(tInX > rpcGPX || tOuX < rpcGPX ) continue;
                   if(tInY > rpcGPY || tOuY < rpcGPY ) continue;
                   if(tInZ > rpcGPZ || tOuZ < rpcGPZ ) continue;
                 
                   const GeomDet *geomDet2 = rpcGeo->idToDet(*rpcroll2);
                   const RPCRoll *aroll = dynamic_cast<const RPCRoll *>(geomDet2);
                   const RectangularStripTopology* top_= dynamic_cast<const RectangularStripTopology*> (&(aroll->topology()));
                   LocalPoint xmin = top_->localPosition(0.);
                   LocalPoint xmax = top_->localPosition((float)aroll->nstrips());
                   float rsize = fabs( xmax.x()-xmin.x() );
                   float stripl = top_->stripLength();
                   //float stripw = top_->pitch();
                   float eyr=1;

                   float locx = ptss.localPosition().x(), locy = ptss.localPosition().y(), locz= ptss.localPosition().z();
                   if( locx < rsize*eyr && locy < stripl*eyr && locz < 1. )
                   {
                      RPCRecHit RPCPoint(*rpcroll2,0,LocalPoint(locx,locy,locz));

                      RPCGeomServ servId(*rpcroll2);
                      if(debug) std::cout << "3\t Barrel Expected RPC " << servId.name().c_str() <<
                        " \tLocalposition X: " << locx << ", Y: "<< locy << " GlobalPosition(x,y,z) (" << rpcGPX <<", "<< rpcGPY <<", " << rpcGPZ << ")"<< std::endl;        
                      RPCPointVector.clear();
                      RPCPointVector.push_back(RPCPoint);
                      _ThePoints->put(*rpcroll2,RPCPointVector.begin(),RPCPointVector.end());
                      rpcput.push_back(*rpcroll2);
                   }
                 }
              }
           }
        }
*/
//        else if (id.det() == DetId::Muon  &&  id.subdetId() == MuonSubdetId::CSC)
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
//                 TrajectoryStateOnSurface ptss =  thePropagator->propagate(upd2, rpcGeo->idToDet(*rpcroll2)->surface());
                 TrajectoryStateOnSurface ptss =  thePropagator->propagate(upd2, gemGeo->idToDet(*gemroll2)->surface());
//                 if(ptss.isValid()) if( ValidRPCSurface(*rpcroll2, ptss.localPosition(), iSetup))
                 if(ptss.isValid()) if( ValidGEMSurface(*gemroll2, ptss.localPosition(), iSetup))
                 {
//                   float rpcGPX = ptss.globalPosition().x();
//                   float rpcGPY = ptss.globalPosition().y();
//                   float rpcGPZ = ptss.globalPosition().z();
                   float gemGPX = ptss.globalPosition().x();
                   float gemGPY = ptss.globalPosition().y();
                   float gemGPZ = ptss.globalPosition().z();

//                   if(tInX > rpcGPX || tOuX < rpcGPX ) continue;
//                   if(tInY > rpcGPY || tOuY < rpcGPY ) continue;
//                   if(tInZ > rpcGPZ || tOuZ < rpcGPZ ) continue;
                   if(tInX > gemGPX || tOuX < gemGPX ) continue;
                   if(tInY > gemGPY || tOuY < gemGPY ) continue;
                   if(tInZ > gemGPZ || tOuZ < gemGPZ ) continue;

//                   RPCDetId rpcid(*rpcroll2); 
                   GEMDetId gemid(*gemroll2); 
//                   const GeomDet *geomDet3 = rpcGeo->idToDet(*rpcroll2);
                   const GeomDet *geomDet3 = gemGeo->idToDet(*gemroll2);
//                   const RPCRoll *aroll = dynamic_cast<const RPCRoll *>(geomDet3);
                   const GEMEtaPartition *aroll = dynamic_cast<const GEMEtaPartition *>(geomDet3);
                   const TrapezoidalStripTopology* top_=dynamic_cast<const TrapezoidalStripTopology*>(&(aroll->topology()));
                   LocalPoint xmin = top_->localPosition(0.);
                   LocalPoint xmax = top_->localPosition((float)aroll->nstrips());
                   float rsize = fabs( xmax.x()-xmin.x() );
                   float stripl = top_->stripLength();
                   //float stripw = top_->pitch();
                  
                   float eyr=1;
////////////////////////////
                   float locx = ptss.localPosition().x(), locy = ptss.localPosition().y(), locz= ptss.localPosition().z();
                   if( locx < rsize*eyr && locy < stripl*eyr && locz < 1. )
                   {
//                      RPCRecHit RPCPoint(*rpcroll2,0,LocalPoint(locx,locy,locz));
                      GEMRecHit GEMPoint(*gemroll2,0,LocalPoint(locx,locy,locz));
//                      RPCGeomServ servId(*rpcroll2); //id().rawId()
//                      if(debug) std::cout << "3\t Forward Expected RPC " << servId.name().c_str() <<
//                        " \tLocalposition X: " << locx << ", Y: "<< locy << " GlobalPosition(x,y,z) (" << rpcGPX <<", "<< rpcGPY <<", " << rpcGPZ << ")"<< std::endl;
                      if(debug) std::cout << "3\t Forward Expected GEM " << aroll->id().rawId() <<
                        " \tLocalposition X: " << locx << ", Y: "<< locy << " GlobalPosition(x,y,z) (" << gemGPX <<", "<< gemGPY <<", " << gemGPZ << ")"<< std::endl;
//                      RPCPointVector.clear();
                      GEMPointVector.clear();
//                      RPCPointVector.push_back(RPCPoint);
                      GEMPointVector.push_back(GEMPoint);
//                      _ThePoints->put(*rpcroll2,RPCPointVector.begin(),RPCPointVector.end());
                      _ThePoints->put(*gemroll2,GEMPointVector.begin(),GEMPointVector.end());
//                      rpcput.push_back(*rpcroll2);
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

//TracktoRPC::~TracktoRPC(){
TracktoGEM::~TracktoGEM(){
}
