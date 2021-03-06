import FWCore.ParameterSet.Config as cms

from HLTriggerOffline.Top.topDiLeptonHLTEventDQM_cfi import *
from HLTriggerOffline.Top.topSingleLeptonHLTEventDQM_cfi import *
from HLTriggerOffline.Top.singletopHLTEventDQM_cfi import *
from HLTriggerOffline.Top.topvalidation_cfi import *
from JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff import *



topHLTDQM = cms.Sequence(  
                           DiMuonDQM
			   *DiElectronDQM
			   *ElecMuonDQM
                           *topSingleMuonMediumTriggerDQM
                           *topSingleElectronMediumTriggerDQM
			   *SingleTopSingleMuonTriggerDQM
			   *SingleTopSingleElectronTriggerDQM	
                           )

