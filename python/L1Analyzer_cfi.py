import FWCore.ParameterSet.Config as cms

L1Analyzer = cms.EDAnalyzer('L1Analyzer',
                                  ecalDigis               = cms.InputTag( 'l1tCaloLayer1Digis'),
                                  hcalDigis               = cms.InputTag( 'l1tCaloLayer1Digis'),
                                  l1Stage2METSource       = cms.untracked.InputTag('simCaloStage2Digis'),
                                  l1ExtraMETSource        = cms.InputTag("uct2016EmulatorDigis","MET"),
                                  l1ExtraMHTSource        = cms.InputTag("uct2016EmulatorDigis","MHT"),
                                  l1ExtraIsoEMSource      = cms.InputTag("uct2016EmulatorDigis","Isolated"),
                                  l1ExtraEMSource         = cms.InputTag("uct2016EmulatorDigis","NonIsolated"),
                                  pfMetToken             = cms.untracked.InputTag('pfMet'),
                                  caloMetToken             = cms.untracked.InputTag('caloMet'),
                                  ElectronToken          = cms.untracked.InputTag('gedGsfElectrons'),
                                  eleVetoIdMapToken      = cms.untracked.InputTag('egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-veto'),
                                  eleLooseIdMapToken      = cms.untracked.InputTag('egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-loose'),
                                  eleMediumIdMapToken      = cms.untracked.InputTag('egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-medium'),
                                  eleTightIdMapToken      = cms.untracked.InputTag('egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight')
                                  #                      vertices                = cms.InputTag("offlinePrimaryVertices")
                                  


)
