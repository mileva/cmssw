#ifndef RPCDBPerformanceHandler_H
#define RPCDBPerformanceHandler_H

#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>

#include "CondCore/PopCon/interface/PopConSourceHandler.h"

#include "CondFormats/RPCObjects/interface/RPCStripNoises.h"
#include "CondFormats/DataRecord/interface/RPCStripNoisesRcd.h"

#include "FWCore/ParameterSet/interface/ParameterSetfwd.h"

#include "Geometry/RPCGeometry/interface/RPCGeometry.h"

class  RPCDBSimSetUp;


  class RPCDBPerformanceHandler: public popcon::PopConSourceHandler<RPCStripNoises>{
  public:
    void getNewObjects();
    ~RPCDBPerformanceHandler(); 
    RPCDBPerformanceHandler(const edm::ParameterSet& pset); 
    std::string id() const;
    void setGeometry(const RPCGeometry * geom) {theGeometry = geom;}

  private:
 
    unsigned long long m_since;
    std::string dataTag;
    RPCDBSimSetUp* theRPCSimSetUp;
    const RPCGeometry * theGeometry;
  };

#endif 
