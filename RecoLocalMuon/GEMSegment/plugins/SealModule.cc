#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include <RecoLocalMuon/GEMSegment/plugins/GEMSegmentProducer.h>
#include <RecoLocalMuon/GEMSegment/plugins/GEMPreSegmentProducer.h>
#include <RecoLocalMuon/GEMSegment/plugins/GEMSegmentBuilderPluginFactory.h>
#include <RecoLocalMuon/GEMSegment/plugins/GEMSegAlgoPV.h>

DEFINE_FWK_MODULE(GEMSegmentProducer);
DEFINE_FWK_MODULE(GEMPreSegmentProducer);
DEFINE_EDM_PLUGIN(GEMSegmentBuilderPluginFactory, GEMSegAlgoPV, "GEMSegAlgoPV");

