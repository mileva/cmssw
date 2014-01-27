//
// Original Author:  Roumyana Hadjiiska
//         Created:  Tue Jan  25 19:39:22 CEST 2014


#include "CondCore/PopCon/interface/PopCon.h"
#include <vector>


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CondTools/RPC/interface/RPCDBPerformanceHandler.h"


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"

#include "FWCore/Framework/interface/MakerMacros.h"


//namespace popcon{
  class MyPopConAnalyzer : public edm::EDAnalyzer {
  public:
    
    MyPopConAnalyzer(const edm::ParameterSet& pset) : 
      m_populator(pset),
      m_source(pset.getParameter<edm::ParameterSet>("Source")) {}
    
    
    virtual ~MyPopConAnalyzer(){}
   
  private:
    
    virtual void beginJob(){}
    virtual void endJob() {
      write();
   }
    
    virtual void analyze(const edm::Event& ev, const edm::EventSetup& eventSetup)
{
   edm::ESHandle<RPCGeometry> hGeom;
   eventSetup.get<MuonGeometryRecord>().get( hGeom );
   const RPCGeometry *pGeom = &*hGeom;
   m_source.setGeometry(pGeom);
} 
    
    
    void write() {
      m_populator.write(m_source);
      
   }
    
  private:
    popcon::PopCon m_populator;
//    SourceHandler m_source;    
    RPCDBPerformanceHandler m_source;
 };
//}

//define this as a plug-in
DEFINE_FWK_MODULE(MyPopConAnalyzer);
