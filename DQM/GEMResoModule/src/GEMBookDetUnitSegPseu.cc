#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>

#include <DataFormats/MuonDetId/interface/GEMDetId.h>
#include <DQM/GEMResoModule/interface/GEMMuonSegmentPseudo.h>
#include <DQM/GEMResoModule/interface/GEMBookFolderStructure.h>
#include "DQMServices/Core/interface/MonitorElement.h"

//add pseudo rechit case
  std::map<std::string, MonitorElement*> GEMMuonSegmentPseudo::bookDetUnitSegPseu(GEMDetId & detId,float rollw,float height) {
  std::map<std::string, MonitorElement*> meMapPseu;

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
    sprintf(meId,"GEMDataOccupancy_pseudo_%s",detUnitLabel);
    sprintf(meTitle,"GEMDataOccupancy_pseudo_for_%s",layerLabel);
    meMapPseu[meId] = dbe->book1D(meId, meTitle, 10*(std::ceil(rollw)),0,std::ceil(rollw));

    sprintf(meId,"ExpectedOccupancy2D_pseudo_%s",detUnitLabel);
    sprintf(meTitle,"ExpectedOccupancy2D_pseudo_for_%s",layerLabel);
    meMapPseu[meId] = dbe->book2D(meId, meTitle, 2*(int)(scale2D*rollw),-scale2D*rollw,scale2D*rollw, 2*(int)(scale2D*height),-scale2D*height,scale2D*height);
    
    sprintf(meId,"GEMDataOccupancy2D_pseudo_%s",detUnitLabel);
    sprintf(meTitle,"GEMDataOccupancy2D_pseudo_for_%s",layerLabel);
    meMapPseu[meId] = dbe->book2D(meId, meTitle,
			      2*(int)(scale2D*rollw),-scale2D*rollw,scale2D*rollw,
			      2*(int)(scale2D*height),-scale2D*height,scale2D*height);
    
    sprintf(meId,"GEMResiduals_pseudo_%s",detUnitLabel);
    sprintf(meTitle,"GEMResiduals_pseudo_%s",layerLabel);
    meMapPseu[meId] = dbe->book1D(meId, meTitle,100, -1., 1.);
  }
  return meMapPseu;
}

