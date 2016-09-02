

/** \class RPCEfficiency
 *
 * Class for RPC Monitoring using RPCDigi and DT and CSC Segments.
 *
 *  $Date: 2011/03/09 10:44:45 $
 *  $Revision: 1.7 $
 *
 * \Original author Camilo Carrillo (Uniandes)
 *
 * \Modified for GEM Roumyana Hadjiiska
 *
*/

#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include <FWCore/Framework/interface/Event.h>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

//#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include <DataFormats/MuonDetId/interface/GEMDetId.h>
#include "FWCore/Framework/interface/ESHandle.h"
//#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/GEMGeometry/interface/GEMGeometry.h>
//#include <Geometry/DTGeometry/interface/DTGeometry.h>
#include <Geometry/CSCGeometry/interface/CSCGeometry.h>

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
//#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
//#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>



#include<string>
#include<map>
#include<fstream>

//class RPCDetId;
class GEMDetId;
class TFile;
class TH1F;
class TFile;
class TCanvas;
class TH2F;
class TString;

class GEMMuonSegment : public edm::EDAnalyzer {
   public:
      explicit GEMMuonSegment(const edm::ParameterSet&);
      ~GEMMuonSegment();
      bool firstbook;
      virtual void beginJob() ;
      virtual void beginRun(const edm::Run&, const edm::EventSetup&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
//      std::map<std::string, MonitorElement*> bookDetUnitSeg(RPCDetId & detId,int nstrips,float stripw,float stripl);
      std::map<std::string, MonitorElement*> bookDetUnitSeg(GEMDetId & detId,int nstrips,float stripw,float stripl);
//rumi: create a GEM name:
      std::string GEMname(const GEMDetId&);

      virtual void endRun(const edm::Run& r, const edm::EventSetup& iSetup);
      std::map<int,float> alignmentinfo;
      
//      edm::ESHandle<RPCGeometry> rpcGeo;
      edm::ESHandle<GEMGeometry> gemGeo;
//      edm::ESHandle<DTGeometry> dtGeo;
      edm::ESHandle<CSCGeometry> cscGeo;

//      MonitorElement * rnNumber;
//      MonitorElement * unixeventtime;
      MonitorElement * statistics;
      MonitorElement * stationstatistics;

      //Ang Dependence
      MonitorElement * ScatterPlotAngCLSEndcaps;
      MonitorElement * AngClu1Endcaps;
      MonitorElement * AngClu2Endcaps;
      MonitorElement * AngClu3Endcaps;
      
      //Residuals Endcap
//Endcap GE11
      MonitorElement * hGlobalResClu1GE11_1;
      MonitorElement * hGlobalResClu1GE11_2;
      MonitorElement * hGlobalResClu1GE11_3;
      MonitorElement * hGlobalResClu1GE11_4;
      MonitorElement * hGlobalResClu1GE11_5;
      MonitorElement * hGlobalResClu1GE11_6;
      MonitorElement * hGlobalResClu1GE11_7;
      MonitorElement * hGlobalResClu1GE11_8;

      MonitorElement * hGlobalResClu2GE11_1;
      MonitorElement * hGlobalResClu2GE11_2;
      MonitorElement * hGlobalResClu2GE11_3;
      MonitorElement * hGlobalResClu2GE11_4;
      MonitorElement * hGlobalResClu2GE11_5;
      MonitorElement * hGlobalResClu2GE11_6;
      MonitorElement * hGlobalResClu2GE11_7;
      MonitorElement * hGlobalResClu2GE11_8;

      MonitorElement * hGlobalResClu3GE11_1;
      MonitorElement * hGlobalResClu3GE11_2;
      MonitorElement * hGlobalResClu3GE11_3;
      MonitorElement * hGlobalResClu3GE11_4;
      MonitorElement * hGlobalResClu3GE11_5;
      MonitorElement * hGlobalResClu3GE11_6;
      MonitorElement * hGlobalResClu3GE11_7;
      MonitorElement * hGlobalResClu3GE11_8;

//Endcap GE21
      MonitorElement * hGlobalResClu1GE21_1;
      MonitorElement * hGlobalResClu1GE21_2;
      MonitorElement * hGlobalResClu1GE21_3;
      MonitorElement * hGlobalResClu1GE21_4;
      MonitorElement * hGlobalResClu1GE21_5;
      MonitorElement * hGlobalResClu1GE21_6;
      MonitorElement * hGlobalResClu1GE21_7;
      MonitorElement * hGlobalResClu1GE21_8;

      MonitorElement * hGlobalResClu2GE21_1;
      MonitorElement * hGlobalResClu2GE21_2;
      MonitorElement * hGlobalResClu2GE21_3;
      MonitorElement * hGlobalResClu2GE21_4;
      MonitorElement * hGlobalResClu2GE21_5;
      MonitorElement * hGlobalResClu2GE21_6;
      MonitorElement * hGlobalResClu2GE21_7;
      MonitorElement * hGlobalResClu2GE21_8;

      MonitorElement * hGlobalResClu3GE21_1;
      MonitorElement * hGlobalResClu3GE21_2;
      MonitorElement * hGlobalResClu3GE21_3;
      MonitorElement * hGlobalResClu3GE21_4;
      MonitorElement * hGlobalResClu3GE21_5;
      MonitorElement * hGlobalResClu3GE21_6;
      MonitorElement * hGlobalResClu3GE21_7;
      MonitorElement * hGlobalResClu3GE21_8;

//XY_view plots
      MonitorElement * XY_globalGE1;
      MonitorElement * XY_globalGEm1;
      MonitorElement * XY_globalGE2;
      MonitorElement * XY_globalGEm2;

//xy_view extrapolated
      MonitorElement * XY_globalGE1_extra;
      MonitorElement * XY_globalGEm1_extra;
      MonitorElement * XY_globalGE2_extra;
      MonitorElement * XY_globalGEm2_extra;

 private:
//      std::vector<std::map<RPCDetId, int> > counter;
      std::vector<std::map<GEMDetId, int> > counter;
      std::vector<int> totalcounter;
      std::ofstream ofrej;
      bool debug;
      bool paper;
      bool inves;
      bool manualalignment;
      double rangestrips;
      int dupli;
      
      std::string rejected;
      std::string rollseff;

//      edm::EDGetTokenT<DTRecSegment4DCollection> dt4DSegments;
      edm::EDGetTokenT<CSCSegmentCollection> cscSegments;
//      edm::EDGetTokenT<RPCRecHitCollection> rpcRecHitsLabel;
      edm::EDGetTokenT<GEMRecHitCollection> gemRecHitsLabel;
//      edm::EDGetTokenT<RPCRecHitCollection> rpcDTPointsLabel;
//      edm::EDGetTokenT<RPCRecHitCollection> rpcCSCPointsLabel;
      edm::EDGetTokenT<GEMRecHitCollection> gemCSCPointsLabel;

      std::map<std::string, std::map<std::string, MonitorElement*> >  meCollection;
      
      bool EffSaveRootFile;
      std::string EffRootFileName;
      std::string AlignmentinfoFile;
      std::string nameInLog;

      DQMStore * dbe;
};
