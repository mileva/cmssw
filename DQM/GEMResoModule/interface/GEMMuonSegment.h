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
#include <DataFormats/MuonDetId/interface/GEMDetId.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <Geometry/GEMGeometry/interface/GEMGeometry.h>
#include <Geometry/CSCGeometry/interface/CSCGeometry.h>
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>

#include<string>
#include<map>
#include<fstream>

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
      std::map<std::string, MonitorElement*> bookDetUnitSeg(GEMDetId & detId,int nstrips,float stripw,float stripl);
      std::string GEMname(const GEMDetId&);

      virtual void endRun(const edm::Run& r, const edm::EventSetup& iSetup);
      std::map<int,float> alignmentinfo;
      
      edm::ESHandle<GEMGeometry> gemGeo;
      edm::ESHandle<CSCGeometry> cscGeo;

      MonitorElement * statistics;
      MonitorElement * stationstatistics;

      //Ang Dependence
      MonitorElement * ScatterPlotAngCLSEndcaps;
      MonitorElement * AngClu1Endcaps;
      MonitorElement * AngClu2Endcaps;
      MonitorElement * AngClu3Endcaps;
      
      //Residuals Endcap
//Endcap GE11
      MonitorElement *hGlobalResAllClsGE11_1;
      MonitorElement *hGlobalResAllClsGE11_2;
      MonitorElement *hGlobalResAllClsGE11_3;
      MonitorElement *hGlobalResAllClsGE11_4;
      MonitorElement *hGlobalResAllClsGE11_5;
      MonitorElement *hGlobalResAllClsGE11_6;
      MonitorElement *hGlobalResAllClsGE11_7;
      MonitorElement *hGlobalResAllClsGE11_8;

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
      MonitorElement *hGlobalResAllClsGE21_1;
      MonitorElement *hGlobalResAllClsGE21_2;
      MonitorElement *hGlobalResAllClsGE21_3;
      MonitorElement *hGlobalResAllClsGE21_4;
      MonitorElement *hGlobalResAllClsGE21_5;
      MonitorElement *hGlobalResAllClsGE21_6;
      MonitorElement *hGlobalResAllClsGE21_7;
      MonitorElement *hGlobalResAllClsGE21_8;

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

//Endcap GE22
      MonitorElement *hGlobalResAllClsGE22_1;
      MonitorElement *hGlobalResAllClsGE22_2;
      MonitorElement *hGlobalResAllClsGE22_3;
      MonitorElement *hGlobalResAllClsGE22_4;
      MonitorElement *hGlobalResAllClsGE22_5;
      MonitorElement *hGlobalResAllClsGE22_6;
      MonitorElement *hGlobalResAllClsGE22_7;
      MonitorElement *hGlobalResAllClsGE22_8;
      MonitorElement *hGlobalResAllClsGE22_9;
      MonitorElement *hGlobalResAllClsGE22_10;
      MonitorElement *hGlobalResAllClsGE22_11;
      MonitorElement *hGlobalResAllClsGE22_12;

      MonitorElement * hGlobalResClu1GE22_1;
      MonitorElement * hGlobalResClu1GE22_2;
      MonitorElement * hGlobalResClu1GE22_3;
      MonitorElement * hGlobalResClu1GE22_4;
      MonitorElement * hGlobalResClu1GE22_5;
      MonitorElement * hGlobalResClu1GE22_6;
      MonitorElement * hGlobalResClu1GE22_7;
      MonitorElement * hGlobalResClu1GE22_8;
      MonitorElement * hGlobalResClu1GE22_9;
      MonitorElement * hGlobalResClu1GE22_10;
      MonitorElement * hGlobalResClu1GE22_11;
      MonitorElement * hGlobalResClu1GE22_12;

      MonitorElement * hGlobalResClu2GE22_1;
      MonitorElement * hGlobalResClu2GE22_2;
      MonitorElement * hGlobalResClu2GE22_3;
      MonitorElement * hGlobalResClu2GE22_4;
      MonitorElement * hGlobalResClu2GE22_5;
      MonitorElement * hGlobalResClu2GE22_6;
      MonitorElement * hGlobalResClu2GE22_7;
      MonitorElement * hGlobalResClu2GE22_8;
      MonitorElement * hGlobalResClu2GE22_9;
      MonitorElement * hGlobalResClu2GE22_10;
      MonitorElement * hGlobalResClu2GE22_11;
      MonitorElement * hGlobalResClu2GE22_12;

      MonitorElement * hGlobalResClu3GE22_1;
      MonitorElement * hGlobalResClu3GE22_2;
      MonitorElement * hGlobalResClu3GE22_3;
      MonitorElement * hGlobalResClu3GE22_4;
      MonitorElement * hGlobalResClu3GE22_5;
      MonitorElement * hGlobalResClu3GE22_6;
      MonitorElement * hGlobalResClu3GE22_7;
      MonitorElement * hGlobalResClu3GE22_8;
      MonitorElement * hGlobalResClu3GE22_9;
      MonitorElement * hGlobalResClu3GE22_10;
      MonitorElement * hGlobalResClu3GE22_11;
      MonitorElement * hGlobalResClu3GE22_12;

//XY_view plots
      MonitorElement * XY_globalGE11;
      MonitorElement * XY_globalGEm11;
      MonitorElement * XY_globalGE21;
      MonitorElement * XY_globalGEm21;
      MonitorElement * XY_globalGE22;
      MonitorElement * XY_globalGEm22;

//xy_view extrapolated
      MonitorElement * XY_globalGE11_extra;
      MonitorElement * XY_globalGEm11_extra;
      MonitorElement * XY_globalGE21_extra;
      MonitorElement * XY_globalGEm21_extra;
      MonitorElement * XY_globalGE22_extra;
      MonitorElement * XY_globalGEm22_extra;

 private:
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

      edm::EDGetTokenT<CSCSegmentCollection> cscSegments;
      edm::EDGetTokenT<GEMRecHitCollection> gemRecHitsLabel;
      edm::EDGetTokenT<GEMRecHitCollection> gemCSCPointsLabel;

      std::map<std::string, std::map<std::string, MonitorElement*> >  meCollection;
      
      bool EffSaveRootFile;
      std::string EffRootFileName;
      std::string AlignmentinfoFile;
      std::string nameInLog;

      DQMStore * dbe;
};
