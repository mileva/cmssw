// -*- C++ -*-
//
// Package:    rpcDigis/RPCDigiAna
// Class:      RPCDigiAna
//
/**\class RPCDigiAna RPCDigiAna.cc rpcDigis/RPCDigiAna/plugins/RPCDigiAna.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Roumyana Mileva Hadjiiska
//         Created:  Thu, 05 Jul 2018 18:47:21 GMT
//
//

// system include files
#include <memory>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/ESTransientHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/RPCDigi/interface/DataRecord.h"
#include "DataFormats/RPCDigi/interface/ReadoutError.h"
#include "DataFormats/RPCDigi/interface/RPCRawSynchro.h"
#include "DataFormats/RPCDigi/interface/RecordBX.h"
#include "DataFormats/RPCDigi/interface/RecordSLD.h"
#include "DataFormats/RPCDigi/interface/RecordCD.h"
#include "DataFormats/RPCDigi/interface/RPCDigi.h"
// user include files
#include "CondFormats/RPCObjects/interface/RPCReadOutMapping.h"
#include "CondFormats/RPCObjects/interface/LinkBoardSpec.h"
#include "CondFormats/RPCObjects/interface/RPCEMap.h"
#include "CondFormats/RPCObjects/interface/DccSpec.h"
#include "CondFormats/RPCObjects/interface/LinkBoardElectronicIndex.h"
#include "CondFormats/RPCObjects/interface/LinkBoardPackedStrip.h"
#include "CondFormats/RPCObjects/interface/TriggerBoardSpec.h"
#include "CondFormats/RPCObjects/interface/LinkBoardSpec.h"
#include "CondFormats/DataRecord/interface/RPCEMapRcd.h"
#include "EventFilter/RPCRawToDigi/interface/RPCRecordFormatter.h"
#include "EventFilter/RPCRawToDigi/interface/EventRecords.h"
#include "EventFilter/RPCRawToDigi/interface/DebugDigisPrintout.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"
#include "DataFormats/MuonDetId/interface/DTChamberId.h"
#include "DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigi.h"
#include "DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigiCollection.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCandFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1F.h"
#include "TH2F.h"

#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include "Geometry/CommonTopologies/interface/RectangularStripTopology.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"

//
// class declaration
//

class RPCDigiAna : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit RPCDigiAna(const edm::ParameterSet&);
      ~RPCDigiAna();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      int rollB(std::string shortname, std::map<int, std::string> rollNames);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<RPCDigiCollection> inputRPC_PACT;

  std::map<int, std::string> rollNamesInter;
  std::map<int, std::string> rollNamesExter;

//digis
  TH2F * Diskm4Digis_Roll_vs_Sector_Disk, *Diskm3Digis_Roll_vs_Sector_Disk, *Diskm2Digis_Roll_vs_Sector_Disk, *Diskm1Digis_Roll_vs_Sector_Disk, *Diskp1Digis_Roll_vs_Sector_Disk, *Diskp2Digis_Roll_vs_Sector_Disk, *Diskp3Digis_Roll_vs_Sector_Disk, *Diskp4Digis_Roll_vs_Sector_Disk;
  TH2F *Wheelm1Digis, *Wheel0Digis, *Wheel1Digis, *Wheelm2Digis, *Wheel2Digis;

//DigisToArea and time
  TH2F * Diskm4DigisToArea_Roll_vs_Sector_Disk, *Diskm3DigisToArea_Roll_vs_Sector_Disk, *Diskm2DigisToArea_Roll_vs_Sector_Disk, *Diskm1DigisToArea_Roll_vs_Sector_Disk, *Diskp1DigisToArea_Roll_vs_Sector_Disk, *Diskp2DigisToArea_Roll_vs_Sector_Disk, *Diskp3DigisToArea_Roll_vs_Sector_Disk, *Diskp4DigisToArea_Roll_vs_Sector_Disk;
  TH2F *Wheelm1DigisToArea, *Wheel0DigisToArea, *Wheel1DigisToArea, *Wheelm2DigisToArea, *Wheel2DigisToArea;

//DigisToTime
  TH2F * Diskm4DigisToTime_Roll_vs_Sector_Disk, *Diskm3DigisToTime_Roll_vs_Sector_Disk, *Diskm2DigisToTime_Roll_vs_Sector_Disk, *Diskm1DigisToTime_Roll_vs_Sector_Disk, *Diskp1DigisToTime_Roll_vs_Sector_Disk, *Diskp2DigisToTime_Roll_vs_Sector_Disk, *Diskp3DigisToTime_Roll_vs_Sector_Disk, *Diskp4DigisToTime_Roll_vs_Sector_Disk;
  TH2F *Wheelm1DigisToTime, *Wheel0DigisToTime, *Wheel1DigisToTime, *Wheelm2DigisToTime, *Wheel2DigisToTime;

  int numbEvents;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
RPCDigiAna::RPCDigiAna(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  inputRPC_PACT = consumes<RPCDigiCollection>(iConfig.getParameter<edm::InputTag>("srcRPC_PACT"));
  usesResource("TFileService");

  rollNamesInter[1] = "RB1in B";
  rollNamesInter[2] = "RB1in F";
  rollNamesInter[3] = "RB1out B";
  rollNamesInter[4] = "RB1out F";
  rollNamesInter[5] = "RB2in B";
  rollNamesInter[6] = "RB2in F";
  rollNamesInter[7] = "RB2in M";
  rollNamesInter[8] = "RB2out B";
  rollNamesInter[9] = "RB2out F";
  rollNamesInter[10] = "RB3,- B";
  rollNamesInter[11] = "RB3,- F";
  rollNamesInter[12] = "RB3+ B";
  rollNamesInter[13] = "RB3+ F";
  rollNamesInter[14] = "RB4,- B";
  rollNamesInter[15] = "RB4,- F";
  rollNamesInter[16] = "RB4+ B";
  rollNamesInter[17] = "RB4+ F";
  rollNamesInter[18] = "RB4++ B";
  rollNamesInter[19] = "RB4++ F";
  rollNamesInter[20] = "RB4-- B";
  rollNamesInter[21] = "RB4-- F";

  for (int i = 1; i <= 22; i++)
  {
    rollNamesExter[i] = rollNamesInter[i];
  }
  rollNamesExter[7] = "RB2out B";
  rollNamesExter[8] = "RB2out F";
  rollNamesExter[9] = "RB2out M";
}


RPCDigiAna::~RPCDigiAna()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

int RPCDigiAna::rollB(std::string shortname, std::map<int, std::string> rollNames)
{
  int myy = 0;
  for (int i = 1; i < 22; i++)
  {
    if (rollNames[i].compare(shortname) == 0)
    {
      myy = i;
      return myy;
    }
  }
  if (myy == 0)
  {
    std::cout << "Check your map or your DetId for " << shortname << std::endl;
  }
  return myy;
}

// ------------ method called for each event  ------------
void
RPCDigiAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  numbEvents++;
  using namespace edm;
  double area = 0.0;

  // Get the RPC Geometry
  edm::ESHandle < RPCGeometry > rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);

  edm::Handle< RPCDigiCollection > digiCollectionRPC_PACT;
  iEvent.getByToken(inputRPC_PACT,digiCollectionRPC_PACT);
  typedef  DigiContainerIterator<RPCDetId, RPCDigi> DigiRangeIterator;

  for (DigiRangeIterator it=digiCollectionRPC_PACT->begin(); it != digiCollectionRPC_PACT->end(); it++)
  {
    const RPCDetId rpcDetId = (*it).first;
    RPCDigiCollection::Range range = digiCollectionRPC_PACT->get(rpcDetId);
    const RPCRoll* roll = dynamic_cast<const RPCRoll*>(rpcGeom->roll(rpcDetId));

//take the global coordiantes of the center of the rpc roll (eta partition)
   const int nstrips = roll->nstrips();
   float middleStrip = nstrips/2.;
   const LocalPoint& middleOfRoll = roll->centreOfStrip(middleStrip);
   const GlobalPoint& globMiddleRol = roll->toGlobal(middleOfRoll);

   std::cout << "eta " << globMiddleRol.eta() << "\tphi " << globMiddleRol.phi() << std::endl;

//take the list of fired strips for a given roll"
  int digisInRoll = 0;
  RPCDigiCollection::const_iterator digiItr; 
   for (digiItr = ((*it ).second).first; digiItr!=((*it).second).second; ++digiItr)
   {
     digisInRoll++;
     int strip= (*digiItr).strip();
     int bx=(*digiItr).bx();
     std::cout << "strip " <<  strip << "\tbx " <<  bx << std::endl;     

//take the global coordinates of the center of a given strip
     const LocalPoint& middleOfStrip = roll->centreOfStrip(strip);
     const GlobalPoint& globMiddleStrip = roll->toGlobal(middleOfStrip);

     std::cout << "eta strip " << globMiddleStrip.eta() << "\tphi strip " << globMiddleStrip.phi() << std::endl;
   }
   std::cout << "digis in roll " << digisInRoll << std::endl;

    RPCGeomServ rpcsrv(rpcDetId);
    int rollY = rpcDetId.roll();
    if (rollY == 1)
      rollY = 3;
    else if (rollY == 3)
      rollY = 1;
    int Y = (rpcDetId.ring() - 1) * 3 + rollY;

    area = 0.0;

   if ( rpcDetId.region() == 0 )
     {
       const RectangularStripTopology* top_ = dynamic_cast<const
         RectangularStripTopology*>(&(roll->topology()));
       float xmin = (top_->localPosition(0.)).x();
       float xmax = (top_->localPosition((float)roll->nstrips())).x();
       float striplength = (top_->stripLength());
       area = striplength*(xmax-xmin);
//       stripArea = area / ((float)roll->nstrips());
     }
   else
     {
       const TrapezoidalStripTopology* top_=dynamic_cast<const TrapezoidalStripTopology*>(&(roll->topology()));
       float xmin = (top_->localPosition(0.)).x();
       float xmax = (top_->localPosition((float)roll->nstrips())).x();
       float striplength = (top_->stripLength());
       area = striplength*(xmax-xmin);
//       stripArea = area / ((float)roll->nstrips());
     }

      if (rpcDetId.region() == -1)
      {
//      std::cout << rpcsrv.name() << " " << rpcsrv.segment() << " " << Y << std::endl;
        if (rpcDetId.station() == 1) {Diskm1Digis_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll); Diskm1DigisToArea_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, (1.*digisInRoll)/area); Diskm1DigisToTime_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll);}
        if (rpcDetId.station() == 2) {Diskm2Digis_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll); Diskm2DigisToArea_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, (1.*digisInRoll)/area); Diskm2DigisToTime_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll);}
        if (rpcDetId.station() == 3) {Diskm3Digis_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll); Diskm3DigisToArea_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, (1.*digisInRoll)/area); Diskm3DigisToTime_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll);}
        if (rpcDetId.station() == 4) {Diskm4Digis_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll); Diskm4DigisToArea_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, (1.*digisInRoll)/area); Diskm4DigisToTime_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll);}
      }
      if (rpcDetId.region() == 1)
      {
//      std::cout << rpcsrv.name() << " " << rpcsrv.segment() << " " << Y << std::endl;
        if (rpcDetId.station() == 1) {Diskp1Digis_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll); Diskp1DigisToArea_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, (1.*digisInRoll)/area); Diskp1DigisToTime_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll);}
        if (rpcDetId.station() == 2) {Diskp2Digis_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll); Diskp1DigisToArea_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, (1.*digisInRoll)/area); Diskp2DigisToTime_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll);}
        if (rpcDetId.station() == 3) {Diskp3Digis_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll); Diskp1DigisToArea_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, (1.*digisInRoll)/area); Diskp3DigisToTime_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll);}
        if (rpcDetId.station() == 4) {Diskp4Digis_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll); Diskp1DigisToArea_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, (1.*digisInRoll)/area); Diskp4DigisToTime_Roll_vs_Sector_Disk->Fill(rpcsrv.segment(), Y, digisInRoll);}
      }
      if (rpcDetId.region() == 0)
      {
        if (abs(rpcDetId.ring()) == 2)
        {
          if (rpcDetId.ring() == 2)
          {
//          std::cout<< "Wheel " << rpcDetId.ring() <<rollB(rpcsrv.shortname(),rollNamesExter)<<"--"<<rpcsrv.shortname()<<std::endl;
            Wheel2Digis->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesExter), digisInRoll);
            Wheel2DigisToArea->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesExter), (1.*digisInRoll)/area);
            Wheel2DigisToTime->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesExter), digisInRoll);
          }
          else
          {
//          std::cout<< "Wheel " << rpcDetId.ring() <<rollB(rpcsrv.shortname(),rollNamesExter)<<"--"<<rpcsrv.shortname()<<std::endl;
            Wheelm2Digis->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesExter), digisInRoll);
            Wheelm2DigisToArea->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesExter), (1.*digisInRoll)/area);
            Wheelm2DigisToTime->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesExter), digisInRoll);
          }
        }
        else
        {
          if (rpcDetId.ring() == -1)
          {
//          std::cout<< "Wheel " << rpcDetId.ring() <<rollB(rpcsrv.shortname(),rollNamesExter)<<"--"<<rpcsrv.shortname()<<std::endl;
            Wheelm1Digis->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesInter), digisInRoll);
            Wheelm1DigisToArea->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesInter), (1.*digisInRoll)/area);
            Wheelm1DigisToTime->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesInter), digisInRoll);
          }
          else if (rpcDetId.ring() == 0)
          {
//          std::cout<< "Wheel " << rpcDetId.ring() <<rollB(rpcsrv.shortname(),rollNamesExter)<<"--"<<rpcsrv.shortname()<<std::endl;
            Wheel0Digis->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesInter), digisInRoll);
            Wheel0DigisToArea->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesInter), (1.*digisInRoll)/area);
            Wheel0DigisToTime->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesInter), digisInRoll);
          }
          else if (rpcDetId.ring() == 1)
          {
//          std::cout<< "Wheel " << rpcDetId.ring() <<rollB(rpcsrv.shortname(),rollNamesExter)<<"--"<<rpcsrv.shortname()<<std::endl;
            Wheel1Digis->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesInter), digisInRoll);
            Wheel1DigisToArea->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesInter), (1.*digisInRoll)/area);
            Wheel1DigisToTime->Fill(rpcDetId.sector(), rollB(rpcsrv.shortname(), rollNamesInter), digisInRoll);
          }
        }
      }//end wheels
  }
}


// ------------ method called once each job just before starting event loop  ------------
void
RPCDigiAna::beginJob()
{
  numbEvents=0;
  edm::Service <TFileService> fs;
  std::stringstream binLabel;

//legacy digis
  Diskm4Digis_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm4Digis_Roll_vs_Sector_Disk", "Disk-4 Number of Digis", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskm3Digis_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm3Digis_Roll_vs_Sector_Disk", "Disk-3 Number of Digis", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskm2Digis_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm2Digis_Roll_vs_Sector_Disk", "Disk-2 Number of Digis", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskm1Digis_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm1Digis_Roll_vs_Sector_Disk", "Disk-1 Number of Digis", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp1Digis_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp1Digis_Roll_vs_Sector_Disk", "Disk 1 Number of Digis", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp2Digis_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp2Digis_Roll_vs_Sector_Disk", "Disk 2 Number of Digis", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp3Digis_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp3Digis_Roll_vs_Sector_Disk", "Disk 3 Number of Digis", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp4Digis_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp4Digis_Roll_vs_Sector_Disk", "Disk 4 Number of Digis", 36, 0.5, 36.5, 9, 0.5, 9.5);
  for (int i = 1; i <= 36; i++)
  {
    binLabel.str("");
    binLabel << i;
    Diskm4Digis_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm3Digis_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm2Digis_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm1Digis_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp4Digis_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp3Digis_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp2Digis_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp1Digis_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
  }
  for (int ri = 1; ri <= 3; ri++)
  {
    for (int roll = 1; roll <= 3; roll++)
    {
      binLabel.str("");
      if (roll == 3) binLabel << "Ring " << ri << " A";
      else if (roll == 2) binLabel << "Ring " << ri << " B";
      else if (roll == 1) binLabel << "Ring " << ri << " C";
      //std::cout<<"Labeling EndCaps "<<binLabel.str()<<std::endl;
      Diskm4Digis_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskm3Digis_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskm2Digis_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskm1Digis_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp4Digis_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp3Digis_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp2Digis_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp1Digis_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
    }
  }

  Wheelm2Digis = fs->make < TH2F > ("Wheelm2Digis", "Wheel-2 Roll vs Sector, Number of Digis", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheelm1Digis = fs->make < TH2F > ("Wheelm1Digis", "Wheel-1 Roll vs Sector, Number of Digis", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheel0Digis = fs->make < TH2F > ("Wheel0Digis", "Wheel 0 Roll vs Sector, Number of Digis", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheel1Digis = fs->make < TH2F > ("Wheel1Digis", "Wheel 1 Roll vs Sector, Number of Digis", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheel2Digis = fs->make < TH2F > ("Wheel2Digis", "Wheel 2 Roll vs Sector, Number of Digis", 12, 0.5, 12.5, 22, 0.5, 22.5);

  for (int i = 1; i <= 12; i++)
  {
    binLabel.str("");
    binLabel << "Sec " << i;
    Wheelm2Digis->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheelm1Digis->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel0Digis->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel1Digis->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel2Digis->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
  }
  for (int i = 1; i < 22; i++)
  {
    Wheelm1Digis->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
    Wheel0Digis->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
    Wheel1Digis->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
  }

  for (int i = 1; i < 22; i++)
  {
    Wheelm2Digis->GetYaxis()->SetBinLabel(i, rollNamesExter[i].c_str());
    Wheel2Digis->GetYaxis()->SetBinLabel(i, rollNamesExter[i].c_str());
  }

//DigisToArea
  Diskm4DigisToArea_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm4DigisToArea_Roll_vs_Sector_Disk", "RE-4 - Rate [Hz/cm^{2}]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskm3DigisToArea_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm3DigisToArea_Roll_vs_Sector_Disk", "RE-3 - Rate [Hz/cm^{2}]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskm2DigisToArea_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm2DigisToArea_Roll_vs_Sector_Disk", "RE-2 - Rate [Hz/cm^{2}]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskm1DigisToArea_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm1DigisToArea_Roll_vs_Sector_Disk", "RE-1 - Rate [Hz/cm^{2}]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp1DigisToArea_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp1DigisToArea_Roll_vs_Sector_Disk", "RE+1 - Rate [Hz/cm^{2}]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp2DigisToArea_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp2DigisToArea_Roll_vs_Sector_Disk", "RE+2 - Rate [Hz/cm^{2}]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp3DigisToArea_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp3DigisToArea_Roll_vs_Sector_Disk", "RE+3 - Rate [Hz/cm^{2}]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp4DigisToArea_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp4DigisToArea_Roll_vs_Sector_Disk", "RE+4 - Rate [Hz/cm^{2}]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  for (int i = 1; i <= 36; i++)
  {
    binLabel.str("");
    binLabel << i;
    Diskm4DigisToArea_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm3DigisToArea_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm2DigisToArea_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm1DigisToArea_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp4DigisToArea_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp3DigisToArea_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp2DigisToArea_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp1DigisToArea_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
  }
  for (int ri = 1; ri <= 3; ri++)
  {
    for (int roll = 1; roll <= 3; roll++)
    {
      binLabel.str("");
      if (roll == 3) binLabel << "Ring " << ri << " A";
      else if (roll == 2) binLabel << "Ring " << ri << " B";
      else if (roll == 1) binLabel << "Ring " << ri << " C";
      //std::cout<<"Labeling EndCaps "<<binLabel.str()<<std::endl;
      Diskm4DigisToArea_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskm3DigisToArea_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskm2DigisToArea_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskm1DigisToArea_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp4DigisToArea_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp3DigisToArea_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp2DigisToArea_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp1DigisToArea_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
    }
  }

  Wheelm2DigisToArea = fs->make < TH2F > ("Wheelm2DigisToArea", "W-2 Rate [Hz/cm^{2}]", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheelm1DigisToArea = fs->make < TH2F > ("Wheelm1DigisToArea", "W-1 Rate [Hz/cm^{2}]", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheel0DigisToArea = fs->make < TH2F > ("Wheel0DigisToArea", "W 0 Rate [Hz/cm^{2}]", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheel1DigisToArea = fs->make < TH2F > ("Wheel1DigisToArea", "W+1 Rate [Hz/cm^{2}]", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheel2DigisToArea = fs->make < TH2F > ("Wheel2DigisToArea", "W+2 Rate [Hz/cm^{2}]", 12, 0.5, 12.5, 22, 0.5, 22.5);

  for (int i = 1; i <= 12; i++)
  {
    binLabel.str("");
    binLabel << "Sec " << i;
    Wheelm2DigisToArea->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheelm1DigisToArea->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel0DigisToArea->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel1DigisToArea->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel2DigisToArea->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
  }
  for (int i = 1; i < 22; i++)
  {
    Wheelm1DigisToArea->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
    Wheel0DigisToArea->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
    Wheel1DigisToArea->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
  }

  for (int i = 1; i < 22; i++)
  {
    Wheelm2DigisToArea->GetYaxis()->SetBinLabel(i, rollNamesExter[i].c_str());
    Wheel2DigisToArea->GetYaxis()->SetBinLabel(i, rollNamesExter[i].c_str());
  }

//DigisToTime
  Diskm4DigisToTime_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm4DigisToTime_Roll_vs_Sector_Disk", "RE-4 - Rate [Hz]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskm3DigisToTime_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm3DigisToTime_Roll_vs_Sector_Disk", "RE-3 - Rate [Hz]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskm2DigisToTime_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm2DigisToTime_Roll_vs_Sector_Disk", "RE-4 - Rate [Hz]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskm1DigisToTime_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskm1DigisToTime_Roll_vs_Sector_Disk", "RE-1 - Rate [Hz]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp1DigisToTime_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp1DigisToTime_Roll_vs_Sector_Disk", "RE+1 - Rate [Hz]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp2DigisToTime_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp2DigisToTime_Roll_vs_Sector_Disk", "RE+2 - Rate [Hz]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp3DigisToTime_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp3DigisToTime_Roll_vs_Sector_Disk", "RE+3 - Rate [Hz]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  Diskp4DigisToTime_Roll_vs_Sector_Disk = fs->make < TH2F > ("Diskp4DigisToTime_Roll_vs_Sector_Disk", "RE+4 - Rate [Hz]", 36, 0.5, 36.5, 9, 0.5, 9.5);
  for (int i = 1; i <= 36; i++)
  {
    binLabel.str("");
    binLabel << i;
    Diskm4DigisToTime_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm3DigisToTime_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm2DigisToTime_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm1DigisToTime_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp4DigisToTime_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp3DigisToTime_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp2DigisToTime_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp1DigisToTime_Roll_vs_Sector_Disk->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
  }
  for (int ri = 1; ri <= 3; ri++)
  {
    for (int roll = 1; roll <= 3; roll++)
    {
      binLabel.str("");
      if (roll == 3) binLabel << "Ring " << ri << " A";
      else if (roll == 2) binLabel << "Ring " << ri << " B";
      else if (roll == 1) binLabel << "Ring " << ri << " C";
      //std::cout<<"Labeling EndCaps "<<binLabel.str()<<std::endl;
      Diskm4DigisToTime_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskm3DigisToTime_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskm2DigisToTime_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskm1DigisToTime_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp4DigisToTime_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp3DigisToTime_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp2DigisToTime_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
      Diskp1DigisToTime_Roll_vs_Sector_Disk->GetYaxis()->SetBinLabel((ri - 1) * 3 + roll, binLabel.str().c_str());
    }
  }

  Wheelm2DigisToTime = fs->make < TH2F > ("Wheelm2DigisToTime", "W-2 Rate [Hz]", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheelm1DigisToTime = fs->make < TH2F > ("Wheelm1DigisToTime", "W-1 Rate [Hz]", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheel0DigisToTime = fs->make < TH2F > ("Wheel0DigisToTime", "W 0 Rate [Hz]", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheel1DigisToTime = fs->make < TH2F > ("Wheel1DigisToTime", "W+1 Rate [Hz]", 12, 0.5, 12.5, 22, 0.5, 22.5);
  Wheel2DigisToTime = fs->make < TH2F > ("Wheel2DigisToTime", "W+2 Rate [Hz]", 12, 0.5, 12.5, 22, 0.5, 22.5);

  for (int i = 1; i <= 12; i++)
  {
    binLabel.str("");
    binLabel << "Sec " << i;
    Wheelm2DigisToTime->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheelm1DigisToTime->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel0DigisToTime->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel1DigisToTime->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel2DigisToTime->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
  }
  for (int i = 1; i < 22; i++)
  {
    Wheelm1DigisToTime->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
    Wheel0DigisToTime->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
    Wheel1DigisToTime->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
  }

  for (int i = 1; i < 22; i++)
  {
    Wheelm2DigisToTime->GetYaxis()->SetBinLabel(i, rollNamesExter[i].c_str());
    Wheel2DigisToTime->GetYaxis()->SetBinLabel(i, rollNamesExter[i].c_str());
  }
}

// ------------ method called once each job just after ending the event loop  ------------
void
RPCDigiAna::endJob()
{
  std::cout << "numbEvents\t" << numbEvents << std::endl;  
  double myTime = numbEvents * 25. * 1.0e-9 * 6.;	//6 bx windows [-2, 3]

//FIXME configure the number of the lumi sections and the duration of one section
//  double myTime = 1*23.8;

//in Hz
  Diskm4DigisToTime_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskm3DigisToTime_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskm2DigisToTime_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskm1DigisToTime_Roll_vs_Sector_Disk->Scale(1./myTime);

  Diskp4DigisToTime_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskp3DigisToTime_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskp2DigisToTime_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskp1DigisToTime_Roll_vs_Sector_Disk->Scale(1./myTime);

  Wheelm2DigisToTime->Scale(1./myTime);
  Wheelm1DigisToTime->Scale(1./myTime);
  Wheel0DigisToTime->Scale(1./myTime);
  Wheel1DigisToTime->Scale(1./myTime);
  Wheel2DigisToTime->Scale(1./myTime);

//in Hz/cm2
  Diskm4DigisToArea_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskm3DigisToArea_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskm2DigisToArea_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskm1DigisToArea_Roll_vs_Sector_Disk->Scale(1./myTime);

  Diskp4DigisToArea_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskp3DigisToArea_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskp2DigisToArea_Roll_vs_Sector_Disk->Scale(1./myTime);
  Diskp1DigisToArea_Roll_vs_Sector_Disk->Scale(1./myTime);

  Wheelm2DigisToArea->Scale(1./myTime);
  Wheelm1DigisToArea->Scale(1./myTime);
  Wheel0DigisToArea->Scale(1./myTime);
  Wheel1DigisToArea->Scale(1./myTime);
  Wheel2DigisToArea->Scale(1./myTime);

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RPCDigiAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Update this part according to the rpc digi analysis
  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCDigiAna);
