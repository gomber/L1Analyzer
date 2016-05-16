import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process("L1TCaloSummaryTest",eras.Run2_2016)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryExtended2016Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

# To get L1 CaloParams
process.load('L1Trigger.L1TCalorimeter.caloStage2Params_2016_v2_1_cfi')
# To get CaloTPGTranscoder
process.load('SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff')

process.HcalTPGCoderULUT.LUTGenerationMode = cms.bool(False)

process.load("Configuration.Geometry.GeometryExtended2016Reco_cff")


from L1Trigger.Configuration.customiseReEmul import L1TEventSetupForHF1x1TPs,L1TReEmulFromRAW 
process = L1TEventSetupForHF1x1TPs(process)

process.load('L1Trigger.Configuration.SimL1Emulator_cff')
process.load('L1Trigger.Configuration.CaloTriggerPrimitives_cff')
process.simEcalTriggerPrimitiveDigis.Label = 'ecalDigis'
process.simHcalTriggerPrimitiveDigis.inputLabel = cms.VInputTag(
    cms.InputTag('hcalDigis'),
    cms.InputTag('hcalDigis')
    )
process.L1TReEmul = cms.Sequence(process.simHcalTriggerPrimitiveDigis * process.SimL1Emulator)

process.load('L1Trigger.L1TCaloSummary.uct2016EmulatorDigis_cfi')

process.uct2016EmulatorDigis.useECALLUT = cms.bool(True)
process.uct2016EmulatorDigis.useHCALLUT = cms.bool(True)
process.uct2016EmulatorDigis.useHFLUT = cms.bool(True)
process.uct2016EmulatorDigis.useLSB = cms.bool(True)
process.uct2016EmulatorDigis.verbose = cms.bool(False)
process.uct2016EmulatorDigis.ecalToken = cms.InputTag("ecalDigis","EcalTriggerPrimitives")
process.uct2016EmulatorDigis.hcalToken = cms.InputTag("hcalDigis")

process.load('EventFilter.L1TXRawToDigi.caloLayer1Stage2Digis_cfi')

process.load('L1Trigger.L1Analyzer.L1Analyzer_cfi')
process.L1Analyzer.ecalDigis = cms.InputTag("ecalDigis","EcalTriggerPrimitives")
process.L1Analyzer.hcalDigis = cms.InputTag("simHcalTriggerPrimitiveDigis")


#process.load('L1Trigger.L1TCaloLayer1.simCaloStage2Layer1Digis_cfi')
process.simCaloStage2Layer1Digis.useECALLUT = cms.bool(True)
process.simCaloStage2Layer1Digis.useHCALLUT = cms.bool(True)
process.simCaloStage2Layer1Digis.useHFLUT = cms.bool(True)
process.simCaloStage2Layer1Digis.useLSB = cms.bool(True)
process.simCaloStage2Layer1Digis.verbose = cms.bool(False)
process.simCaloStage2Layer1Digis.ecalToken = cms.InputTag("ecalDigis","EcalTriggerPrimitives")
process.simCaloStage2Layer1Digis.hcalToken = cms.InputTag("hcalDigis")

process.load('L1Trigger.L1TCalorimeter.simCaloStage2Digis_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.AOD

switchOnVIDElectronIdProducer(process, dataFormat)


my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff']

#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

# Input source                                                                                                                                                                                                                                                
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/mc/RunIIFall15DR76/ttHTobb_M125_13TeV_powheg_pythia8/AODSIM/25nsPUfixed30NzshcalRaw_76X_mcRun2_asymptotic_v12-v1/10000/04F64DC2-1DC3-E511-8C46-B083FED138B3.root'),
    secondaryFileNames = cms.untracked.vstring('/store/mc/RunIIFall15DR76/ttHTobb_M125_13TeV_powheg_pythia8/GEN-SIM-RAW/25nsPUfixed30NzshcalRaw_76X_mcRun2_asymptotic_v12-v1/10000/0002DED1-DFC2-E511-BC7C-20CF3027A61A.root')
)


#process.source = cms.Source("PoolSource",
 #   fileNames = cms.untracked.vstring('/store/mc/RunIIFall15DR76/DYToLL_M_1_TuneCUETP8M1_13TeV_pythia8/AODSIM/25nsFlat10to50ZsecalNzshcalRaw_76X_mcRun2_asymptotic_2016EcalTune_30fb_v1_ext1-v1/00000/0803AE13-20D1-E511-829B-00238BCE44F0.root')
#    secondaryFileNames = cms.untracked.vstring('/store/mc/RunIIFall15DR76/DYToLL_M_1_TuneCUETP8M1_13TeV_pythia8/GEN-SIM-RAW/25nsFlat10to50ZsecalNzshcalRaw_76X_mcRun2_asymptotic_2016EcalTune_30fb_v1_ext1-v1/00000/B025B7DA-FDD0-E511-9EC1-002590E3A0FC.root','/store/mc/RunIIFall15DR76/DYToLL_M_1_TuneCUETP8M1_13TeV_pythia8/GEN-SIM-RAW/25nsFlat10to50ZsecalNzshcalRaw_76X_mcRun2_asymptotic_2016EcalTune_30fb_v1_ext1-v1/00000/567842A2-FDD0-E511-A59F-90B11C2AAEEC.root','/store/mc/RunIIFall15DR76/DYToLL_M_1_TuneCUETP8M1_13TeV_pythia8/GEN-SIM-RAW/25nsFlat10to50ZsecalNzshcalRaw_76X_mcRun2_asymptotic_2016EcalTune_30fb_v1_ext1-v1/00000/627441E6-FDD0-E511-B4CF-0025901D0C68.root','/store/mc/RunIIFall15DR76/DYToLL_M_1_TuneCUETP8M1_13TeV_pythia8/GEN-SIM-RAW/25nsFlat10to50ZsecalNzshcalRaw_76X_mcRun2_asymptotic_2016EcalTune_30fb_v1_ext1-v1/00000/6E0CEEFC-04D1-E511-B410-003048357A8C.root','/store/mc/RunIIFall15DR76/DYToLL_M_1_TuneCUETP8M1_13TeV_pythia8/GEN-SIM-RAW/25nsFlat10to50ZsecalNzshcalRaw_76X_mcRun2_asymptotic_2016EcalTune_30fb_v1_ext1-v1/00000/76C14308-05D1-E511-BAED-003048344A90.root','/store/mc/RunIIFall15DR76/DYToLL_M_1_TuneCUETP8M1_13TeV_pythia8/GEN-SIM-RAW/25nsFlat10to50ZsecalNzshcalRaw_76X_mcRun2_asymptotic_2016EcalTune_30fb_v1_ext1-v1/00000/C0124EDD-FDD0-E511-8A59-0025904AC2CC.root')
#)


process.TFileService = cms.Service("TFileService", fileName = cms.string('Ntuple_Stage3_mc.root'))

process.load('L1Trigger.L1TCaloLayer1.layer1Validator_cfi')
process.layer1Validator.testRegionToken = cms.InputTag("uct2016EmulatorDigis")
process.layer1Validator.emulRegionToken= cms.InputTag("simCaloStage2Layer1Digis")
process.layer1Validator.emulTowerToken = cms.InputTag("simCaloStage2Layer1Digis")
process.layer1Validator.validateTowers= cms.bool(False)
process.layer1Validator.validateRegions = cms.bool(True)
process.layer1Validator.verbose = cms.bool(False)

#process.out = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string('L1Ntuple.root'),
#   outputCommands = cms.untracked.vstring('drop *', 'keep *_*_*_L1TCaloSummaryTest')
#)

#process.p = cms.Path(process.RawToDigi*process.L1TReEmul*process.uct2016EmulatorDigis*process.simCaloStage2Layer1Digis*process.simCaloStage2Digis*process.L1Analyzer)
process.p = cms.Path(process.RawToDigi*process.L1TReEmul*process.uct2016EmulatorDigis*process.simCaloStage2Layer1Digis*process.simCaloStage2Digis*process.egmGsfElectronIDSequence*process.L1Analyzer)
#process.p = cms.Path(process.L1Analyzer)

#process.e = cms.EndPath(process.out)

dump_file = open("dump_file.py", "w")
dump_file.write(process.dumpPython())
