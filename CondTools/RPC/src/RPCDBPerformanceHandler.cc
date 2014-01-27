#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//
// class decleration
//
#include "CondTools/RPC/interface/RPCDBPerformanceHandler.h"
#include <iostream>
#include <fstream>

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

#include "CondTools/RPC/interface/RPCDBSimSetUp.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "CondFormats/RPCObjects/interface/RPCStripNoises.h"
#include "CondFormats/DataRecord/interface/RPCStripNoisesRcd.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCChamber.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"

#include <cmath>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include<cstring>
#include<string>
#include<vector>
#include<stdlib.h>
#include <utility>
#include <map>

using namespace edm;

RPCDBPerformanceHandler::RPCDBPerformanceHandler(const edm::ParameterSet& pset) :
  m_since(pset.getUntrackedParameter<int >("firstSince")),
  dataTag(   pset.getParameter<std::string>  (  "tag" ) ){
  theRPCSimSetUp  =  new RPCDBSimSetUp(pset);
}

RPCDBPerformanceHandler::~RPCDBPerformanceHandler(){}


void RPCDBPerformanceHandler::getNewObjects(){

  std::cout << " - > getNewObjects\n" << 
    //check whats already inside of database
    "got offlineInfo"<<
    tagInfo().name << ", size " << tagInfo().size 
	    << ", last object valid since " 
	    << tagInfo().lastInterval.first << std::endl;

  RPCStripNoises* obj = new RPCStripNoises();

  std::map< int, std::vector<double> >::iterator itc;
  for(itc = (theRPCSimSetUp->_clsMap).begin();itc != (theRPCSimSetUp->_clsMap).end();++itc)
  {
    for(unsigned int n = 0; n < (itc->second).size();++n)
    {
      (obj->v_cls).push_back((itc->second)[n]);
    }
  }

  RPCStripNoises::NoiseItem tipoprova;

  int i = 0;
  std::cout << "size of _mapDetIdNoise = " << (theRPCSimSetUp->_mapDetIdNoise).size() << std::endl;
  for(std::map<uint32_t, float>::iterator it = (theRPCSimSetUp->_mapDetIdNoise).begin(); 
      it != (theRPCSimSetUp->_mapDetIdNoise).end(); it++)
  {
    tipoprova.dpid = it->first;

//    std::cout << "dpid = " << tipoprova.dpid << std::endl;
    RPCDetId rpcid(tipoprova.dpid);
//    std::cout << "RPCDetId = " << rpcid << std::endl;

//    std::vector<RPCRoll*>  rpcRolls = theGeometry->rolls();

   const RPCRoll* roll = dynamic_cast<const RPCRoll* >(theGeometry->roll(rpcid));
   unsigned int numbStrips = roll->nstrips();
//   std::cout << "strip number = " << roll->nstrips() << std::endl;
//   std::cout << "------------------------" << std::endl;


    tipoprova.time =  theRPCSimSetUp->getTime(it->first);

    for(unsigned int k = 0; k < numbStrips; ++k)
    {
//      tipoprova.noise = 0.05;
//      tipoprova.eff = 0.95;
      tipoprova.noise = ((it->second));
      tipoprova.eff = (theRPCSimSetUp->getEff(it->first));
      (obj->v_noises).push_back(tipoprova);
    }
    
    edm::LogError("RPCStripNoisesBuilder")<<"[RPCStripNoisesBuilder::analyze] detid already exists"<<std::endl;
    
    i++;
  }

  // prepare for transfer:
  m_to_transfer.push_back( std::make_pair((RPCStripNoises*)obj,m_since) );
 
}

std::string RPCDBPerformanceHandler::id() const {
  return dataTag;
}
