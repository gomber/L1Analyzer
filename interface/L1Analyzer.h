#ifndef L1Analyzer_h
#define L1Analyzer_h

#include "TTree.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Common/interface/ValueMap.h"

#include <memory>
#include <math.h>
#include <vector>
#include <list>

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/L1TCalorimeter/interface/CaloTower.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"


#include "DataFormats/L1Trigger/interface/L1EmParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EmParticle.h"

#include "DataFormats/L1Trigger/interface/EtSum.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"


using namespace std;


class L1Analyzer : public edm::EDAnalyzer {
 public:

  L1Analyzer(const edm::ParameterSet&);
  virtual ~L1Analyzer();

  //  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

 protected:
  // Analyze
  void analyze(const edm::Event& evt, const edm::EventSetup& es);
  
  // BeginJob
  void beginJob(const edm::EventSetup &es);
  
  // EndJob
  void endJob(void);


 private:

  bool verbose_;
  edm::EDGetTokenT<EcalTrigPrimDigiCollection> ecalSrc_; 
  edm::EDGetTokenT<HcalTrigPrimDigiCollection> hcalSrc_;
  edm::EDGetTokenT<l1t::EtSumBxCollection> l1Stage2METSource_;
  edm::EDGetTokenT<vector <l1extra::L1EtMissParticle> > l1ExtraMETSource_;
  edm::EDGetTokenT<vector <l1extra::L1EtMissParticle> > l1ExtraMHTSource_;
  edm::EDGetTokenT<vector <l1extra::L1EmParticle> > l1ExtraIsoEMSource_;
  edm::EDGetTokenT<vector <l1extra::L1EmParticle> > l1ExtraEMSource_;
  edm::EDGetTokenT<reco::PFMETCollection>     pfMetToken_;

  edm::EDGetTokenT<reco::GsfElectronCollection>       ElectronToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >              ElectronVetoIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >              ElectronLooseIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >              ElectronMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >              ElectronTightIdMapToken_;

  //  edm::EDGetTokenT<reco::VertexCollection> vtxLabel_;
  float l1met_, l1ettot_,l1metstage2_,l1ettotstage2_,l1metphi_;
  float l1mht_, l1ethad_,l1mhtstage2_,l1ethadstage2_;
  float PFmet_,PFmetphi_,PFSumet_,PFmeteta_,PFmetpx_,PFmetpy_;
  float l1metpx_,l1metpy_,l1meteta_;
  float l1metstage2px_,l1metstage2py_,l1metstage2eta_,l1metstage2phi_;
  std::vector<float> l1isoEmEt_;
  std::vector<float> l1isoEmEta_;
  std::vector<float> l1isoEmPhi_;
  std::vector<float> l1isoEmBx_;
  std::vector<float> l1nonIsoEmEt_;
  std::vector<float> l1nonIsoEmEta_;
  std::vector<float> l1nonIsoEmPhi_;
  std::vector<float> l1nonIsoEmBx_;
  std::vector<float> Elee_;
  std::vector<float> Elept_;
  std::vector<float> Eleet_;
  std::vector<float> Eleeta_;
  std::vector<float> Elephi_;
  std::vector<float> Eleeta_SC_;
  std::vector<float> Elephi_SC_;
  std::vector<float> EleECALen_;
  std::vector<float> EleSCen_;
  std::vector<float> Elecharge_;
  std::vector<float> Eleiso_;

  std::vector<float> EleisVetoElectron_;
  std::vector<float> EleisLooseElectron_;
  std::vector<float> EleisMediumElectron_;
  std::vector<float> EleisTightElectron_;

 

  Int_t   nl1isoEm_;
  Int_t   nl1nonIsoEm_;
  Int_t nrecoele_;
  
  edm::Service<TFileService> file_;
  TTree   *tree_;
  
};

#endif
