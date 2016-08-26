//#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/GEMGeometry/interface/GEMGeometry.h>

#include <Geometry/CSCGeometry/interface/CSCGeometry.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include "FWCore/Framework/interface/ESHandle.h"

#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
//triabva da se zameni s niakakyv drug hedyr

//#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include <DataFormats/GEMRecHit/interface/GEMRecHit.h>

//#include <DataFormats/RPCRecHit/interface/RPCRecHitCollection.h>
#include <DataFormats/GEMRecHit/interface/GEMRecHitCollection.h>

//#include <RecoLocalMuon/RPCRecHit/interface/CSCSegtoRPC.h>
#include <RecoLocalMuon/GEMRecHit/interface/CSCSegtoGEM.h>

ObjectMapCSC* ObjectMapCSC::mapInstance = NULL;

ObjectMapCSC* ObjectMapCSC::GetInstance(const edm::EventSetup& iSetup){
  if (mapInstance == NULL){
    mapInstance = new ObjectMapCSC(iSetup);
  }
  return mapInstance;
}

ObjectMapCSC::ObjectMapCSC(const edm::EventSetup& iSetup){
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
//take the GEM chamber number directly from gemdetid:
          int gemsegment = gemId.chamber();
//	  int cscchamber = rpcsegment; //FIX THIS ACCORDING TO RPCGeomServ::segment()Definition
	  int cscchamber = gemsegment;

          if((station==2||station==3)&&ring==3){//Adding Ring 3 of RPC to the CSC Ring 2
            cscring = 2;
//            if(debug) 
              std::cout << "I found a GEM chamber on the station out of range, station number = " << station << std::endl;
          }

	  CSCStationIndex ind(region,cscstation,cscring,cscchamber);
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
  
//CSCSegtoRPC::CSCSegtoRPC(edm::Handle<CSCSegmentCollection> allCSCSegments, const edm::EventSetup& iSetup,const edm::Event& iEvent, bool debug, double eyr){
CSCSegtoGEM::CSCSegtoGEM(edm::Handle<CSCSegmentCollection> allCSCSegments, const edm::EventSetup& iSetup,const edm::Event& iEvent, bool debug, double eyr){
  
//  edm::ESHandle<RPCGeometry> rpcGeo;
  edm::ESHandle<GEMGeometry> gemGeo;
  edm::ESHandle<CSCGeometry> cscGeo;
  
//  iSetup.get<MuonGeometryRecord>().get(rpcGeo);
  iSetup.get<MuonGeometryRecord>().get(gemGeo);
  iSetup.get<MuonGeometryRecord>().get(cscGeo);
  
  MaxD=80.;		//rumi da se proveri tozi parametyr za GEM?

  if(debug) std::cout<<"CSC \t Number of CSC Segments in this event = "<<allCSCSegments->size()<<std::endl;

//  _ThePoints = new RPCRecHitCollection();
  _ThePoints = new GEMRecHitCollection();

  if(allCSCSegments->size()==0){
    if(debug) std::cout<<"CSC 0 segments skiping event"<<std::endl;
  }else {
    std::map<CSCDetId,int> CSCSegmentsCounter;
    CSCSegmentCollection::const_iterator segment;
      
    int segmentsInThisEventInTheEndcap=0;
      
    for (segment = allCSCSegments->begin();segment!=allCSCSegments->end(); ++segment){
      CSCSegmentsCounter[segment->cscDetId()]++;
      segmentsInThisEventInTheEndcap++;
    }    
      
    if(debug) std::cout<<"CSC \t loop over all the CSCSegments "<<std::endl;
    for (segment = allCSCSegments->begin();segment!=allCSCSegments->end(); ++segment){
      CSCDetId CSCId = segment->cscDetId();
	
      if(debug) std::cout<<"CSC \t \t This Segment is in Chamber id: "<<CSCId<<std::endl;
      if(debug) std::cout<<"CSC \t \t Number of segments in this CSC = "<<CSCSegmentsCounter[CSCId]<<std::endl;
      if(debug) std::cout<<"CSC \t \t Is the only one in this CSC? is not ind the ring 1 or station 4? Are there more than 2 segments in the event?"<<std::endl;

//      if(CSCSegmentsCounter[CSCId]==1 && CSCId.station()!=4 && CSCId.ring()!=1 && allCSCSegments->size()>=2){
      if(CSCSegmentsCounter[CSCId]==1 && CSCId.station()== 2 && CSCId.ring()==1 && allCSCSegments->size()>=2){
	if(debug) std::cout<<"CSC \t \t yes"<<std::endl;
	int cscEndCap = CSCId.endcap();
	int cscStation = CSCId.station();
	int cscRing = CSCId.ring();
//	int rpcRegion = 1; if(cscEndCap==2) rpcRegion= -1;//Relacion entre las endcaps
	int gemRegion = 1; if(cscEndCap==2) gemRegion= -1;//Relacion entre las endcaps
//	int rpcRing = cscRing;
	int gemRing = cscRing;
//	if(cscRing==4)rpcRing =1;	//rumi da proveria CSC geometry i Id?
	if(cscRing==4)gemRing =1;	//rumi da proveria CSC geometry i Id?
//	int rpcStation = cscStation;
	int gemStation = cscStation;
//	int rpcSegment = CSCId.chamber();
	int gemSegment = CSCId.chamber();
	
	LocalPoint segmentPosition= segment->localPosition();
	LocalVector segmentDirection=segment->localDirection();
	float dz=segmentDirection.z();

	if(debug) std::cout<<"CSC \t \t \t Information about the segment" 
			   <<"RecHits ="<<segment->nRecHits()
			   <<"Angle ="<<acos(dz)*180/3.1415926<<std::endl;
		      
	if(debug) std::cout<<"CSC \t \t Is it a good Segment? dim = 4, 4 <= nRecHits <= 10 Incident angle int range 45 < "<<acos(dz)*180/3.1415926<<" < 135? "<<std::endl;

	if((segment->dimension()==4) && (segment->nRecHits()<=10 && segment->nRecHits()>=4)){
	  //&& acos(dz)*180/3.1415926 > 45. && acos(dz)*180/3.1415926 < 135.){ 
	  //&& segment->chi2()< ??)Add 3 segmentes in the endcaps???


	  if(debug) std::cout<<"CSC \t \t yes"<<std::endl;
	  if(debug) std::cout<<"CSC \t \t CSC Segment Dimension "<<segment->dimension()<<std::endl; 
	    
	  float Xo=segmentPosition.x();
	  float Yo=segmentPosition.y();
	  float Zo=segmentPosition.z();
	  float dx=segmentDirection.x();
	  float dy=segmentDirection.y();
	  float dz=segmentDirection.z();

	  if(debug)  std::cout<<"Calling to Object Map class"<<std::endl;
	  ObjectMapCSC* TheObjectCSC = ObjectMapCSC::GetInstance(iSetup);
	  if(debug) std::cout<<"Creating the CSCIndex"<<std::endl;
//	  CSCStationIndex theindex(rpcRegion,rpcStation,rpcRing,rpcSegment);
	  CSCStationIndex theindex(gemRegion,gemStation,gemRing,gemSegment);
	  if(debug) std::cout<<"Getting the Rolls for the given index"<<std::endl;
	
//	  std::set<RPCDetId> rollsForThisCSC = TheObjectCSC->GetInstance(iSetup)->GetRolls(theindex);
	  std::set<GEMDetId> rollsForThisCSC = TheObjectCSC->GetInstance(iSetup)->GetRolls(theindex);
		
	   
	  if(debug) std::cout<<"CSC \t \t Getting chamber from Geometry"<<std::endl;
	  const CSCChamber* TheChamber=cscGeo->chamber(CSCId); 
	  if(debug) std::cout<<"CSC \t \t Getting ID from Chamber"<<std::endl;
	  const CSCDetId TheId=TheChamber->id();

	  if(debug) std::cout<<"CSC \t \t Number of rolls for this CSC = "<<rollsForThisCSC.size()<<std::endl;

	  if(debug) std::cout<<"CSC \t \t Printing The Id"<<TheId<<std::endl;

//	  if(rpcRing!=1&&rpcStation!=4){//They don't exist!
	  if(gemRing==1 && (gemStation==2 || gemStation==1)){//adjust the code for GE21 and probably GE11
	  
	    assert(rollsForThisCSC.size()>=1);

	    if(debug) std::cout<<"CSC \t \t Loop over all the rolls asociated to this CSC"<<std::endl;	    
//	    for (std::set<RPCDetId>::iterator iteraRoll = rollsForThisCSC.begin();iteraRoll != rollsForThisCSC.end(); iteraRoll++){
	    for (std::set<GEMDetId>::iterator iteraRoll = rollsForThisCSC.begin();iteraRoll != rollsForThisCSC.end(); iteraRoll++){

//	      const RPCRoll* rollasociated = rpcGeo->roll(*iteraRoll);
	      const GEMEtaPartition* rollasociated = gemGeo->etaPartition(*iteraRoll);
//	      RPCDetId rpcId = rollasociated->id();
	      GEMDetId gemId = rollasociated->id();
		
//	      if(debug) std::cout<<"CSC \t \t \t We are in the roll getting the surface"<<rpcId<<std::endl;
	      if(debug) std::cout<<"CSC \t \t \t We are in the roll getting the surface"<<gemId<<std::endl;
//	      const BoundPlane & RPCSurface = rollasociated->surface(); 
	      const BoundPlane & GEMSurface = rollasociated->surface(); 

//	      if(debug) std::cout<<"CSC \t \t \t RollID: "<<rpcId<<std::endl;
	      if(debug) std::cout<<"CSC \t \t \t RollID: "<<gemId<<std::endl;
		
	      if(debug) std::cout<<"CSC \t \t \t Doing the extrapolation to this roll"<<std::endl;
	      if(debug) std::cout<<"CSC \t \t \t CSC Segment Direction in CSCLocal "<<segmentDirection<<std::endl;
	      if(debug) std::cout<<"CSC \t \t \t CSC Segment Point in CSCLocal "<<segmentPosition<<std::endl;  
		
//	      GlobalPoint CenterPointRollGlobal = RPCSurface.toGlobal(LocalPoint(0,0,0));
	      GlobalPoint CenterPointRollGlobal = GEMSurface.toGlobal(LocalPoint(0,0,0));
	      if(debug) std::cout<<"CSC \t \t \t Center (0,0,0) of the Roll in Global"<<CenterPointRollGlobal<<std::endl;
	      GlobalPoint CenterPointCSCGlobal = TheChamber->toGlobal(LocalPoint(0,0,0));
	      if(debug) std::cout<<"CSC \t \t \t Center (0,0,0) of the CSC in Global"<<CenterPointCSCGlobal<<std::endl;
	      GlobalPoint segmentPositionInGlobal=TheChamber->toGlobal(segmentPosition); //new way to convert to global
	      if(debug) std::cout<<"CSC \t \t \t Segment Position in Global"<<segmentPositionInGlobal<<std::endl;
	      LocalPoint CenterRollinCSCFrame = TheChamber->toLocal(CenterPointRollGlobal);

//	      if(debug){//to check CSC RPC phi relation!
	      if(debug){//to check CSC GEM phi relation!
//		float rpcphi=0;
		float gemphi=0;
		float cscphi=0;
		  
		(CenterPointRollGlobal.barePhi()<0)? 
//		  rpcphi = 2*3.141592+CenterPointRollGlobal.barePhi():rpcphi=CenterPointRollGlobal.barePhi();
		  gemphi = 2*3.141592+CenterPointRollGlobal.barePhi():gemphi=CenterPointRollGlobal.barePhi();
		  
		(CenterPointCSCGlobal.barePhi()<0)? 	//rumi: da se prerazgleda, tyj kato gem kamerite sa 20 degree, a csc sa 10 degree, t.e. neshto triabva da e razlichno
		  cscphi = 2*3.1415926536+CenterPointCSCGlobal.barePhi():cscphi=CenterPointCSCGlobal.barePhi();

//		float df=fabs(cscphi-rpcphi); 
		float df=fabs(cscphi-gemphi); 	//razlika po phi mezhdu centrovete na csc kamerite i gem roll
		float dr=fabs(CenterPointRollGlobal.perp()-CenterPointCSCGlobal.perp());	//razlika w radiusvektorite do centrovete
		float diffz=CenterPointRollGlobal.z()-CenterPointCSCGlobal.z();	//razlika po z
		float dfg=df*180./3.14159265;	//ot rad v degree

//		if(debug) std::cout<<"CSC \t \t \t z of RPC="<<CenterPointRollGlobal.z()<<"z of CSC"<<CenterPointCSCGlobal.z()<<" dfg="<<dfg<<std::endl;
		if(debug) std::cout<<"CSC \t \t \t z of GEM="<<CenterPointRollGlobal.z()<<"z of CSC"<<CenterPointCSCGlobal.z()<<" dfg="<<dfg<<std::endl;
		  
//		RPCGeomServ rpcsrv(rpcId);
//Ne mi triabva za GEM. Direktno vzimam nomera na kamerata ot gemId
		  
		if(dr>200.||fabs(dz)>55.||dfg>1.){ 
		  //if(rpcRegion==1&&dfg>1.&&dr>100.){  
		  if (debug) std::cout
		    <<"\t \t \t CSC Station= "<<CSCId.station()
		    <<" Ring= "<<CSCId.ring()
		    <<" Chamber= "<<CSCId.chamber()
		    <<" cscphi="<<cscphi*180/3.14159265
//		    <<"\t RPC Station= "<<rpcId.station()
		    <<"\t GEM Station= "<<gemId.station()
//		    <<" ring= "<<rpcId.ring()
		    <<" ring= "<<gemId.ring()
//		    <<" segment =-> "<<rpcsrv.segment()
		    <<" segment =-> "<<gemId.chamber()
//		    <<" rollphi="<<rpcphi*180/3.14159265
		    <<" rollphi="<<gemphi*180/3.14159265
		    <<"\t dfg="<<dfg
		    <<" dz="<<diffz
		    <<" dr="<<dr
		    <<std::endl;
		    
		}
	      }
	      
	      float D=CenterRollinCSCFrame.z();
	  	  
	      float X=Xo+dx*D/dz;
	      float Y=Yo+dy*D/dz;
	      float Z=D;

	      const TrapezoidalStripTopology* top_=dynamic_cast<const TrapezoidalStripTopology*>(&(rollasociated->topology()));
	      LocalPoint xmin = top_->localPosition(0.);
	      if(debug) std::cout<<"CSC \t \t \t xmin of this  Roll "<<xmin<<"cm"<<std::endl;
	      LocalPoint xmax = top_->localPosition((float)rollasociated->nstrips());
	      if(debug) std::cout<<"CSC \t \t \t xmax of this  Roll "<<xmax<<"cm"<<std::endl;
	      float rsize = fabs( xmax.x()-xmin.x() );
	      if(debug) std::cout<<"CSC \t \t \t Roll Size "<<rsize<<"cm"<<std::endl;
	      float stripl = top_->stripLength();
	      float stripw = top_->pitch();

	      if(debug) std::cout<<"CSC \t \t \t Strip Lenght "<<stripl<<"cm"<<std::endl;
	      if(debug) std::cout<<"CSC \t \t \t Strip Width "<<stripw<<"cm"<<std::endl;

	      if(debug) std::cout<<"CSC \t \t \t X Predicted in CSCLocal= "<<X<<"cm"<<std::endl;
	      if(debug) std::cout<<"CSC \t \t \t Y Predicted in CSCLocal= "<<Y<<"cm"<<std::endl;
	      if(debug) std::cout<<"CSC \t \t \t Z Predicted in CSCLocal= "<<Z<<"cm"<<std::endl;
	  
	      float extrapolatedDistance = sqrt((X-Xo)*(X-Xo)+(Y-Yo)*(Y-Yo)+(Z-Zo)*(Z-Zo));

	      if(debug) std::cout<<"CSC \t \t \t Is the distance of extrapolation less than MaxD? ="<<extrapolatedDistance<<"cm"<<" MaxD="<<MaxD<<"cm"<<std::endl;
	  
	      if(extrapolatedDistance<=MaxD){ //rumi: da se proveri tazi distancia za gem

		if(debug) std::cout<<"CSC \t \t \t yes"<<std::endl;

		GlobalPoint GlobalPointExtrapolated=TheChamber->toGlobal(LocalPoint(X,Y,Z));
		if(debug) std::cout<<"CSC \t \t \t Point ExtraPolated in Global"<<GlobalPointExtrapolated<< std::endl;

	      
//		LocalPoint PointExtrapolatedRPCFrame = RPCSurface.toLocal(GlobalPointExtrapolated);
		LocalPoint PointExtrapolatedGEMFrame = GEMSurface.toLocal(GlobalPointExtrapolated);

//		if(debug) std::cout<<"CSC \t \t \t Point Extrapolated in RPCLocal"<<PointExtrapolatedRPCFrame<< std::endl;
		if(debug) std::cout<<"CSC \t \t \t Point Extrapolated in GEMLocal"<<PointExtrapolatedGEMFrame<< std::endl;
		if(debug) std::cout<<"CSC \t \t \t Corner of the Roll = ("<<rsize*eyr<<","<<stripl*eyr<<")"<<std::endl;
//		if(debug) std::cout<<"CSC \t \t \t Info About the Point Extrapolated in X Abs ("<<fabs(PointExtrapolatedRPCFrame.x())<<","
		if(debug) std::cout<<"CSC \t \t \t Info About the Point Extrapolated in X Abs ("<<fabs(PointExtrapolatedGEMFrame.x())<<","
//				   <<fabs(PointExtrapolatedRPCFrame.y())<<","<<fabs(PointExtrapolatedRPCFrame.z())<<")"<<std::endl;
				   <<fabs(PointExtrapolatedGEMFrame.y())<<","<<fabs(PointExtrapolatedGEMFrame.z())<<")"<<std::endl;
		if(debug) std::cout<<"CSC \t \t \t dz="
//				   <<fabs(PointExtrapolatedRPCFrame.z())<<" dx="
				   <<fabs(PointExtrapolatedGEMFrame.z())<<" dx="
//				   <<fabs(PointExtrapolatedRPCFrame.x())<<" dy="
				   <<fabs(PointExtrapolatedGEMFrame.x())<<" dy="
//				   <<fabs(PointExtrapolatedRPCFrame.y())<<std::endl;
				   <<fabs(PointExtrapolatedGEMFrame.y())<<std::endl;
		  
		if(debug) std::cout<<"CSC \t \t \t Does the extrapolation go inside this roll????"<<std::endl;

//		if(fabs(PointExtrapolatedRPCFrame.z()) < 1. && 
		if(fabs(PointExtrapolatedGEMFrame.z()) < 1. && 
//		   fabs(PointExtrapolatedRPCFrame.x()) < rsize*eyr && 
		   fabs(PointExtrapolatedGEMFrame.x()) < rsize*eyr && 
//		   fabs(PointExtrapolatedRPCFrame.y()) < stripl*eyr){ 
		   fabs(PointExtrapolatedGEMFrame.y()) < stripl*eyr){ 
		  if(debug) std::cout<<"CSC \t \t \t \t yes"<<std::endl;
		  if(debug) std::cout<<"CSC \t \t \t \t Creating the RecHit"<<std::endl;
//		  RPCRecHit RPCPoint(rpcId,0,PointExtrapolatedRPCFrame);
		  GEMRecHit GEMPoint(gemId,0,PointExtrapolatedGEMFrame);
		  if(debug) std::cout<<"CSC \t \t \t \t Clearing the vector"<<std::endl;	
//		  RPCPointVector.clear();
		  GEMPointVector.clear();
		  if(debug) std::cout<<"CSC \t \t \t \t Pushing back"<<std::endl;	
//		  RPCPointVector.push_back(RPCPoint); 
		  GEMPointVector.push_back(GEMPoint); 
		  if(debug) std::cout<<"CSC \t \t \t \t Putting the vector"<<std::endl;	
//		  _ThePoints->put(rpcId,RPCPointVector.begin(),RPCPointVector.end());
		  _ThePoints->put(gemId,GEMPointVector.begin(),GEMPointVector.end());
		}
	      }
	    }
	  }
	}
      }
    }
  }
}

//CSCSegtoRPC::~CSCSegtoRPC(){
CSCSegtoGEM::~CSCSegtoGEM(){

}
