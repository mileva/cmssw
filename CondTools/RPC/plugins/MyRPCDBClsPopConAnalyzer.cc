#include "CondCore/PopCon/interface/PopConAnalyzer.h"
#include "CondTools/RPC/interface/RPCDBClsPerformanceHandler.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef popcon::PopConAnalyzer<RPCDBClsPerformanceHandler> MyRPCDBClsPopConAnalyzer;
//define this as a plug-in
DEFINE_FWK_MODULE(MyRPCDBClsPopConAnalyzer);
