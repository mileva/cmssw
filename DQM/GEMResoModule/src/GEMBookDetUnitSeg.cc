#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>

#include <DataFormats/MuonDetId/interface/GEMDetId.h>
#include <DQM/GEMResoModule/interface/GEMMuonSegment.h>
#include <DQM/GEMResoModule/interface/GEMBookFolderStructure.h>
#include "DQMServices/Core/interface/MonitorElement.h"

std::map<std::string, MonitorElement*> GEMMuonSegment::bookDetUnitSeg(GEMDetId & detId,int nstrips,float stripw,float stripl) {
  
  std::map<std::string, MonitorElement*> meMap;
   
  GEMBookFolderStructure *  folderStr = new GEMBookFolderStructure();
  std::string folder = "Muons/MuonSegEff/" +  folderStr->folderStructure(detId);

  dbe->setCurrentFolder(folder);

  std::string nameRoll = GEMname(detId);

  char detUnitLabel[128];
  char layerLabel[128];

  sprintf(detUnitLabel ,"%s",nameRoll.c_str());
  sprintf(layerLabel ,"%s",nameRoll.c_str());

  char meId [128];
  char meTitle [128];

  float scale2D = 0.6;

  if(detId.region()==0) {
    std::cout << "I found GEM in barrel. Something is wrong. Please check!" << std::endl;

  }else{
    sprintf(meId,"ExpectedOccupancy_%s",detUnitLabel);
    sprintf(meTitle,"ExpectedOccupancy_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, nstrips,0,nstrips);
    
    sprintf(meId,"RealDetectedOccupancy_%s",detUnitLabel);
    sprintf(meTitle,"RealDetectedOccupancy_for_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle, nstrips,0, nstrips);
    
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
    meMap[meId] = dbe->book2D(meId, meTitle,9,-4.5,4.5,20,0,stripl);   
    
    //New 2D and more
    sprintf(meId,"ExpectedOccupancy2D_%s",detUnitLabel);
    sprintf(meTitle,"ExpectedOccupancy2D_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle, 
			      2*(int)(scale2D*nstrips*stripw),-scale2D*nstrips*stripw,scale2D*nstrips*stripw,
			      2*(int)(scale2D*stripl),-scale2D*stripl,scale2D*stripl);
    
    sprintf(meId,"GEMDataOccupancy2D_%s",detUnitLabel);
    sprintf(meTitle,"GEMDataOccupancy2D_for_%s",layerLabel);
    meMap[meId] = dbe->book2D(meId, meTitle,
			      2*(int)(scale2D*nstrips*stripw),-scale2D*nstrips*stripw,scale2D*nstrips*stripw,
			      2*(int)(scale2D*stripl),-scale2D*stripl,scale2D*stripl);
    
//    sprintf(meId,"Inefficiency2D_%s",detUnitLabel);
//    sprintf(meTitle,"Inefficiency2D_for_%s",layerLabel);
//    meMap[meId] = dbe->book2D(meId, meTitle, 2*(int)(scale2D*nstrips*stripw),-scale2D*nstrips*stripw,scale2D*nstrips*stripw, 2*(int)(scale2D*stripl),-scale2D*stripl,scale2D*stripl);
    
    sprintf(meId,"GEMResiduals_Clu1_%s",detUnitLabel);
    sprintf(meTitle,"GEMResiduals_Clu1_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,100, -1., 1.);

    sprintf(meId,"GEMResiduals_Clu2_%s",detUnitLabel);
    sprintf(meTitle,"GEMResiduals_Clu2_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,100, -1., 1.);
    
    sprintf(meId,"GEMResiduals_Clu3_%s",detUnitLabel);
    sprintf(meTitle,"GEMResiduals_Clu3_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,100, -1., 1.);
   
    sprintf(meId,"GEMResiduals_Other_%s",detUnitLabel);
    sprintf(meTitle,"GEMResiduals_Other_%s",layerLabel);
    meMap[meId] = dbe->book1D(meId, meTitle,100, -1., 1.);
   
  }
  return meMap;
}

