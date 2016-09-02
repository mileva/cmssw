#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>


//#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include <DataFormats/MuonDetId/interface/GEMDetId.h>
//#include <DQM/RPCMonitorModule/interface/MuonSegmentEff.h>
#include <DQM/GEMResoModule/interface/GEMMuonSegment.h>

//#include <DQM/RPCMonitorDigi/interface/RPCBookFolderStructure.h>
#include <DQM/GEMResoModule/interface/GEMBookFolderStructure.h>
#include "DQMServices/Core/interface/MonitorElement.h"

//#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
//std::map<std::string, MonitorElement*> MuonSegmentEff::bookDetUnitSeg(RPCDetId & detId,int nstrips,float stripw,float stripl) {
std::map<std::string, MonitorElement*> GEMMuonSegment::bookDetUnitSeg(GEMDetId & detId,int nstrips,float stripw,float stripl) {
  
  std::map<std::string, MonitorElement*> meMap;
   
//  RPCBookFolderStructure *  folderStr = new RPCBookFolderStructure(); //Anna
  GEMBookFolderStructure *  folderStr = new GEMBookFolderStructure();
  std::string folder = "Muons/MuonSegEff/" +  folderStr->folderStructure(detId);

  dbe->setCurrentFolder(folder);

//  RPCGeomServ RPCname(detId);
//  std::string nameRoll = RPCname.name();
  std::string nameRoll = GEMname(detId);


  char detUnitLabel[128];
  char layerLabel[128];

  sprintf(detUnitLabel ,"%s",nameRoll.c_str());
  sprintf(layerLabel ,"%s",nameRoll.c_str());

  char meId [128];
  char meTitle [128];

  float scale2D = 0.6;

  //Begin booking DT
  if(detId.region()==0) {
std::cout << "I found GEM in barrel. Something is wrong. Please check!" << std::endl;
/*
    //std::cout<<"Booking for the Barrel"<<detUnitLabel<<std::endl;
    
    sprintf(meId,"ExpectedOccupancy_%s",detUnitLabel);
    sprintf(meTitle,"ExpectedOccupancy_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, nstrips, 0, nstrips);
    
    sprintf(meId,"RealDetectedOccupancy_%s",detUnitLabel);
    sprintf(meTitle,"RealDetectedOccupancy_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, nstrips, 0, nstrips);
    
    sprintf(meId,"RPCDataOccupancy_%s",detUnitLabel);
    sprintf(meTitle,"RPCDataOccupancy_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, nstrips,0,nstrips);
    
    sprintf(meId,"BXDistribution_%s",detUnitLabel);
    sprintf(meTitle,"BXDistribution_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, 11,-5.5, 5.5);

    sprintf(meId,"Signal_BXDistribution_%s",detUnitLabel);
    sprintf(meTitle,"Signal_BXDistribution_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, 11,-5.5, 5.5);

    sprintf(meId,"CLSDistribution_%s",detUnitLabel);
    sprintf(meTitle,"CLSDistribution_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, 10,0.5,10.5); //ESTO EN REALIDAD ES 10, no olvidar cambiar!

    sprintf(meId,"BXYDistribution_%s",detUnitLabel);
    sprintf(meTitle,"BXYDistribution_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle,7,-3.5,3.5,20,0,stripl);   

    //New 2D and more

    sprintf(meId,"ExpectedOccupancy2D_%s",detUnitLabel);
    sprintf(meTitle,"ExpectedOccupancy2D_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle, 
			      2*(int)(scale2D*nstrips*stripw),-scale2D*nstrips*stripw,scale2D*nstrips*stripw,
			      2*(int)(scale2D*stripl),-scale2D*stripl,scale2D*stripl);

    sprintf(meId,"RPCDataOccupancy2D_%s",detUnitLabel);
    sprintf(meTitle,"RPCDataOccupancy2D_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle, 
			      2*(int)(scale2D*nstrips*stripw),-scale2D*nstrips*stripw,scale2D*nstrips*stripw,
			      2*(int)(scale2D*stripl),-scale2D*stripl,scale2D*stripl);
    
    sprintf(meId,"Inefficiency2D_%s",detUnitLabel);
    sprintf(meTitle,"Inefficiency2D_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle, 
			      2*(int)(scale2D*nstrips*stripw),-scale2D*nstrips*stripw,scale2D*nstrips*stripw,
			      2*(int)(scale2D*stripl),-scale2D*stripl,scale2D*stripl);
    
    sprintf(meId,"RPCResiduals_Clu1_%s",detUnitLabel);
    sprintf(meTitle,"RPCResiduals_Clu1_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,101,-20,20);

    sprintf(meId,"RPCResiduals_Clu2_%s",detUnitLabel);
    sprintf(meTitle,"RPCResiduals_Clu2_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,101,-20,20);

    sprintf(meId,"RPCResiduals_Clu3_%s",detUnitLabel);
    sprintf(meTitle,"RPCResiduals_Clu3_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,101,-20,20);
    
    sprintf(meId,"RPCResiduals_Other_%s",detUnitLabel);
    sprintf(meTitle,"RPCResiduals_Other_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,101,-20,20);
*/

  }else{
    //std::cout<<"Booking for the EndCap"<<detUnitLabel<<std::endl;

    sprintf(meId,"ExpectedOccupancy_%s",detUnitLabel);
    sprintf(meTitle,"ExpectedOccupancy_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, nstrips,0,nstrips);
    
    sprintf(meId,"RealDetectedOccupancy_%s",detUnitLabel);
    sprintf(meTitle,"RealDetectedOccupancy_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, nstrips,0, nstrips);
    
//    sprintf(meId,"RPCDataOccupancy_%s",detUnitLabel);
//    sprintf(meTitle,"RPCDataOccupancy_for_%s",layerLabel);
    sprintf(meId,"GEMDataOccupancy_%s",detUnitLabel);
    sprintf(meTitle,"GEMDataOccupancy_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, nstrips, 0,nstrips);
    
    sprintf(meId,"BXDistribution_%s",detUnitLabel);
    sprintf(meTitle,"BXDistribution_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, 11,-5.5, 5.5);

    sprintf(meId,"Signal_BXDistribution_%s",detUnitLabel);
    sprintf(meTitle,"Signal_BXDistribution_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, 11,-5.5, 5.5);

    sprintf(meId,"CLSDistribution_%s",detUnitLabel);
    sprintf(meTitle,"CLSDistribution_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, 10,0.5,10.5);

    sprintf(meId,"BXYDistribution_%s",detUnitLabel);
    sprintf(meTitle,"BXYDistribution_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle,7,-3.5,3.5,20,0,stripl);   
    
    //New 2D and more
    sprintf(meId,"ExpectedOccupancy2D_%s",detUnitLabel);
    sprintf(meTitle,"ExpectedOccupancy2D_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle, 
			      2*(int)(scale2D*nstrips*stripw),-scale2D*nstrips*stripw,scale2D*nstrips*stripw,
			      2*(int)(scale2D*stripl),-scale2D*stripl,scale2D*stripl);
    
//    sprintf(meId,"RPCDataOccupancy2D_%s",detUnitLabel);
//    sprintf(meTitle,"RPCDataOccupancy2D_for_%s",layerLabel);
    sprintf(meId,"GEMDataOccupancy2D_%s",detUnitLabel);
    sprintf(meTitle,"GEMDataOccupancy2D_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle,
			      2*(int)(scale2D*nstrips*stripw),-scale2D*nstrips*stripw,scale2D*nstrips*stripw,
			      2*(int)(scale2D*stripl),-scale2D*stripl,scale2D*stripl);
    
    sprintf(meId,"Inefficiency2D_%s",detUnitLabel);
    sprintf(meTitle,"Inefficiency2D_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle, 
			      2*(int)(scale2D*nstrips*stripw),-scale2D*nstrips*stripw,scale2D*nstrips*stripw,
			      2*(int)(scale2D*stripl),-scale2D*stripl,scale2D*stripl);
    
    sprintf(meId,"GEMResiduals_Clu1_%s",detUnitLabel);
    sprintf(meTitle,"GEMResiduals_Clu1_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,101,-20.,20.);

    sprintf(meId,"GEMResiduals_Clu2_%s",detUnitLabel);
    sprintf(meTitle,"GEMResiduals_Clu2_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,101,-20.,20.);
    
    sprintf(meId,"GEMResiduals_Clu3_%s",detUnitLabel);
    sprintf(meTitle,"GEMResiduals_Clu3_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,101,-20.,20.);
   
    sprintf(meId,"GEMResiduals_Other_%s",detUnitLabel);
    sprintf(meTitle,"GEMResiduals_Other_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,101,-20.,20.);
   
  }
  return meMap;
}

/*
std::string GEMname(const GEMDetId& _id)
{
   int station = _id->station();
   int region = _id->region();
   int roll = _id->roll();
   int ring = _id->ring();
   int layer = _id->layer();
   int chamber = _id->chamber();
   std::stringstream os;
    if( region == 0 )
    {
      std::cout << "I found a GEM eta partition in the Barrel - should be wrong!" << std::endl;
      continue;
    }
    else
    {
      os << "GE";
      os << std::setw(2) << std::setfill('+') << station * region << std::setfill(' ') << "_";
      os << "R" << ring;
      os << "_CH" << std::setw(2) << std::setfill('0') << chamber();

      if( roll == 1 )
    os << "_A";
      else if( roll == 2 )
    os << "_B";
      else if( roll == 3 )
    os << "_C";
      else if( roll == 4 )
    os << "_D";
      else if( roll == 5 )
    os << "_E";
      else if( roll == 6 )
    os << "_F";
      else if( roll == 7 )
    os << "_G";
      else if( roll == 8 )
    os << "_H";
      else if( roll == 9 )
    os << "_I";
      else if( roll == 10 )
    os << "_J";
      else if( roll == 11 )
    os << "_K";
      else if( roll == 12 )
    os << "_L";
    }
    _n = os.str();
  return _n;
}
*/

