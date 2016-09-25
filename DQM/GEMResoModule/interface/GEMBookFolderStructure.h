 /** \class GEMBookFolderStructure
  *
  * \author Anna Cimmino (INFN Napoli)
  *
  * Create folder structure for DQM histo saving
  * \modified for GEM: Roumyana Mileva Hadjiiska
  */
 #ifndef GEMBookFolderStructure_H
 #define GEMBookFolderStructure_H
 
 #include <DataFormats/MuonDetId/interface/GEMDetId.h>
 #include<string>
 #include <sstream>
 class GEMBookFolderStructure {
    public:
       explicit GEMBookFolderStructure() {};
       ~GEMBookFolderStructure(){};
 
       std::string folderStructure(GEMDetId detId){ 
     
     std::stringstream myStream ;
     myStream.str("");
 
     if(detId.region() == -1) 
       myStream <<"Endcap-/Station_-"<<detId.station()<<"/ring_"<<detId.ring()<<"/chamber_"<<detId.chamber();
     else if(detId.region() ==  1) 
       myStream <<"Endcap+/Station_"<<detId.station()<<"/ring_"<<detId.ring()<<"/chamber_"<<detId.chamber();
     else  myStream <<"Error/Folder/Creation";
 
       return myStream.str();
       }
 };
 #endif

