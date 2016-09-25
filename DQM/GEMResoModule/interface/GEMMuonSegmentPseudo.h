/** \class RPCEfficiency
 *
 * Class for RPC Monitoring using RPCDigi and DT and CSC Segments.
 *
 *  $Date: 2011/03/09 10:44:45 $
 *  $Revision: 1.7 $
 *
 * \Original author Camilo Carrillo (Uniandes)
 *
 * \Modified for GEM pseudodigis and pseudorechits Roumyana Hadjiiska
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

class GEMMuonSegmentPseudo : public edm::EDAnalyzer {
   public:
      explicit GEMMuonSegmentPseudo(const edm::ParameterSet&);
      ~GEMMuonSegmentPseudo();
      bool firstbook;
      virtual void beginJob() ;
      virtual void beginRun(const edm::Run&, const edm::EventSetup&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
//add pseudo rechit case
      std::map<std::string, MonitorElement*> bookDetUnitSegPseu(GEMDetId & detId,float rollw,float stripl);
      std::string GEMname(const GEMDetId&);
      virtual void endRun(const edm::Run& r, const edm::EventSetup& iSetup);
      
      edm::ESHandle<GEMGeometry> gemGeo;
      edm::ESHandle<CSCGeometry> cscGeo;

      MonitorElement * statistics;
      MonitorElement * stationstatistics;

      //Ang Dependence
      MonitorElement * AngSigma1Endcaps;
      MonitorElement * AngSigma2Endcaps;
      MonitorElement * AngSigma3Endcaps;
      MonitorElement * AngSigmaAnyEndcaps;
      
      //Residuals
//Endcap GE11
      MonitorElement *hGlobalResAllClsGE11_1;
      MonitorElement *hGlobalResAllClsGE11_2;
      MonitorElement *hGlobalResAllClsGE11_3;
      MonitorElement *hGlobalResAllClsGE11_4;
      MonitorElement *hGlobalResAllClsGE11_5;
      MonitorElement *hGlobalResAllClsGE11_6;
      MonitorElement *hGlobalResAllClsGE11_7;
      MonitorElement *hGlobalResAllClsGE11_8;

//Endcap GE21
      MonitorElement *hGlobalResAllClsGE21_1;
      MonitorElement *hGlobalResAllClsGE21_2;
      MonitorElement *hGlobalResAllClsGE21_3;
      MonitorElement *hGlobalResAllClsGE21_4;
      MonitorElement *hGlobalResAllClsGE21_5;
      MonitorElement *hGlobalResAllClsGE21_6;
      MonitorElement *hGlobalResAllClsGE21_7;
      MonitorElement *hGlobalResAllClsGE21_8;

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

//Endcap GE22 delta phi
      MonitorElement *hGlobphiResAllGE22_1;
      MonitorElement *hGlobphiResAllGE22_2;
      MonitorElement *hGlobphiResAllGE22_3;
      MonitorElement *hGlobphiResAllGE22_4;
      MonitorElement *hGlobphiResAllGE22_5;
      MonitorElement *hGlobphiResAllGE22_6;
      MonitorElement *hGlobphiResAllGE22_7;
      MonitorElement *hGlobphiResAllGE22_8;
      MonitorElement *hGlobphiResAllGE22_9;
      MonitorElement *hGlobphiResAllGE22_10;
      MonitorElement *hGlobphiResAllGE22_11;
      MonitorElement *hGlobphiResAllGE22_12;

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
      int dupli;
      
      std::string rejected;
      std::string rollseff;

      edm::EDGetTokenT<CSCSegmentCollection> cscSegments;
      edm::EDGetTokenT<GEMRecHitCollection> gemRecHitsLabel;
      edm::EDGetTokenT<GEMRecHitCollection> gemCSCPointsLabel;

      std::map<std::string, std::map<std::string, MonitorElement*> >  meCollection;
      std::map<std::string, std::map<std::string, MonitorElement*> >  meCollectionPseu;
      
      bool EffSaveRootFile;
      std::string EffRootFileName;
      std::string nameInLog;
      DQMStore * dbe;
};
