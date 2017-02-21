#ifndef DataFormats_ME0Digi_ME0DigiCollection_h
#define DataFormats_ME0Digi_ME0DigiCollection_h

/** \class ME0DigiCollection
 *  
 *  \author Roumyana Hadjiiska
 */

#include <DataFormats/MuonDetId/interface/ME0DetId.h>
#include <DataFormats/ME0Digi/interface/ME0Digi.h>
#include <DataFormats/MuonData/interface/MuonDigiCollection.h>

typedef MuonDigiCollection<ME0DetId, ME0Digi> ME0DigiCollection;

#endif

