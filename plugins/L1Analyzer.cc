// -*- C++ -*-
//
// Package:    L1Trigger/L1Analyzer
// Class:      L1Analyzer
// 
/**\class L1Analyzer L1Analyzer.cc L1Trigger/L1Analyzer/plugins/L1Analyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Bhawna Gomber
//         Created:  Fri, 29 Apr 2016 13:11:46 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "L1Trigger/L1Analyzer/interface/L1Analyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <iostream>
#include <fstream>
//

using namespace edm;

class PtSortCriterium{
public:
  bool operator() (l1extra::L1EmParticle p1,l1extra::L1EmParticle p2 ){
    return p1.pt() > p2.pt();
  }
};


L1Analyzer::L1Analyzer(const edm::ParameterSet& cfg):
  ecalSrc_(consumes<EcalTrigPrimDigiCollection>(cfg.getParameter<edm::InputTag>("ecalDigis"))),
  hcalSrc_(consumes<HcalTrigPrimDigiCollection>(cfg.getParameter<edm::InputTag>("hcalDigis"))),
  l1Stage2METSource_(consumes<l1t::EtSumBxCollection>(cfg.getUntrackedParameter<edm::InputTag>("l1Stage2METSource"))),
  l1ExtraMETSource_(consumes<vector <l1extra::L1EtMissParticle> >(cfg.getParameter<edm::InputTag>("l1ExtraMETSource"))),
  l1ExtraMHTSource_(consumes<vector <l1extra::L1EtMissParticle> >(cfg.getParameter<edm::InputTag>("l1ExtraMHTSource"))),
  l1ExtraIsoEMSource_(consumes<vector <l1extra::L1EmParticle> >(cfg.getParameter<edm::InputTag>("l1ExtraIsoEMSource"))),
  l1ExtraEMSource_(consumes<vector <l1extra::L1EmParticle> >(cfg.getParameter<edm::InputTag>("l1ExtraEMSource"))),
  pfMetToken_(consumes<reco::PFMETCollection>(cfg.getUntrackedParameter<edm::InputTag>("pfMetToken"))),
  caloMetToken_(consumes<reco::CaloMETCollection>(cfg.getUntrackedParameter<edm::InputTag>("caloMetToken"))),
  caloMetTokenBE_(consumes<reco::CaloMETCollection>(cfg.getUntrackedParameter<edm::InputTag>("caloMetTokenBE"))),
  ElectronToken_(consumes<reco::GsfElectronCollection>(cfg.getUntrackedParameter<edm::InputTag>("ElectronToken"))),
  ElectronVetoIdMapToken_(consumes<edm::ValueMap<bool> >(cfg.getUntrackedParameter<edm::InputTag>("eleVetoIdMapToken"))),
  ElectronLooseIdMapToken_(consumes<edm::ValueMap<bool> >(cfg.getUntrackedParameter<edm::InputTag>("eleLooseIdMapToken"))),
  ElectronMediumIdMapToken_(consumes<edm::ValueMap<bool> >(cfg.getUntrackedParameter<edm::InputTag>("eleMediumIdMapToken"))),
  ElectronTightIdMapToken_(consumes<edm::ValueMap<bool> >(cfg.getUntrackedParameter<edm::InputTag>("eleTightIdMapToken")))
  
  //  vtxLabel_(consumes<reco::VertexCollection>(cfg.getParameter<edm::InputTag>("vertice")))
{
  tree_    = file_->make<TTree>("EventTree", "Event data");
  tree_->Branch("l1EtTot",         &l1ettot_);
  tree_->Branch("l1MET",         &l1met_);
  tree_->Branch("l1MHT",         &l1mht_);
  tree_->Branch("l1METPhi",         &l1metphi_);
  tree_->Branch("l1METEta",         &l1meteta_);
  tree_->Branch("l1METPx",         &l1metpx_);
  tree_->Branch("l1METPy",         &l1metpy_);
  tree_->Branch("l1EtHad",         &l1ethad_);

  tree_->Branch("l1EtTotStage2",         &l1ettotstage2_);
  tree_->Branch("l1METStage2",         &l1metstage2_);
  tree_->Branch("l1METStage2px",         &l1metstage2px_);
  tree_->Branch("l1METStage2py",         &l1metstage2py_);
  tree_->Branch("l1METStage2eta",         &l1metstage2eta_);
  tree_->Branch("l1METStage2phi",         &l1metstage2phi_);
  tree_->Branch("l1EtHadStage2",         &l1ethadstage2_);
  tree_->Branch("l1MHTStage2",         &l1mhtstage2_);

  tree_->Branch("l1IsoEmEt",         &l1isoEmEt_);
  tree_->Branch("l1IsoEmEta",         &l1isoEmEta_);
  tree_->Branch("l1IsoEmPhi",         &l1isoEmPhi_);
  tree_->Branch("l1IsoEmBx",         &l1isoEmBx_);
  tree_->Branch("l1nonIsoEmEt",         &l1nonIsoEmEt_);
  tree_->Branch("l1nonIsoEmEta",         &l1nonIsoEmEta_);
  tree_->Branch("l1nonIsoEmPhi",         &l1nonIsoEmPhi_);
  tree_->Branch("l1nonIsoEmBx",         &l1nonIsoEmBx_);
  tree_->Branch("nl1IsoEm",         &nl1isoEm_);
  tree_->Branch("nl1nonIsoEm",         &nl1nonIsoEm_);

  tree_->Branch("PFSumet",         &PFSumet_);
  tree_->Branch("PFmet",         &PFmet_);
  tree_->Branch("PFmetphi",         &PFmetphi_);
  tree_->Branch("PFmetpx",         &PFmetpx_);
  tree_->Branch("PFmetpy",         &PFmetpy_);
  tree_->Branch("PFmeteta",         &PFmeteta_);



  tree_->Branch("Calomet",         &Calomet_);
  tree_->Branch("Calometphi",         &Calometphi_);
  tree_->Branch("Calometeta",         &Calometeta_);
  tree_->Branch("Calometpx",         &Calometpx_);
  tree_->Branch("Calometpy",         &Calometpy_);
  tree_->Branch("CaloSumet",         &CaloSumet_);


  tree_->Branch("CalometBE",         &CalometBE_);
  tree_->Branch("CalometBEphi",         &CalometBEphi_);
  tree_->Branch("CalometBEeta",         &CalometBEeta_);
  tree_->Branch("CalometBEpx",         &CalometBEpx_);
  tree_->Branch("CalometBEpy",         &CalometBEpy_);
  tree_->Branch("CaloSumetBE",         &CaloSumetBE_);

  tree_->Branch("nrecoele",         &nrecoele_);
  tree_->Branch("Elee",         &Elee_);
  tree_->Branch("Elept",         &Elept_);
  tree_->Branch("Eleet",         &Eleet_);
  tree_->Branch("Eleeta",         &Eleeta_);
  tree_->Branch("Elephi",         &Elephi_);
  tree_->Branch("Eleeta_SC",         &Eleeta_SC_);
  tree_->Branch("Elephi_SC",         &Elephi_SC_);
  tree_->Branch("EleECALen",         &EleECALen_);
  tree_->Branch("EleSCen",         &EleSCen_);
  tree_->Branch("Elecharge",         &Elecharge_);
  tree_->Branch("Eleiso",         &Eleiso_);
  tree_->Branch("EleisVetoElectron",         &EleisVetoElectron_);
  tree_->Branch("EleisLooseElectron",         &EleisLooseElectron_);
  tree_->Branch("EleisMediumElectron",         &EleisMediumElectron_);
  tree_->Branch("EleisTightElectron",         &EleisTightElectron_);


  
  



}


L1Analyzer::~L1Analyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
L1Analyzer::analyze(const edm::Event& evt, const edm::EventSetup& es)
{

//  edm::Handle<reco::VertexCollection> vertices;
//  if(evt.getByToken(vtxLabel_, vertices)){
//    nvtx = vertices->size();
//  }
//  std::cout<<"nvtx: "<<std::endl;
//


  edm::Handle < vector<l1extra::L1EtMissParticle> > l1ExtraMET;
  evt.getByToken(l1ExtraMETSource_, l1ExtraMET);


  edm::Handle < vector<l1extra::L1EtMissParticle> > l1ExtraMHT;
  evt.getByToken(l1ExtraMHTSource_, l1ExtraMHT);  

  edm::Handle < vector<l1extra::L1EmParticle> > l1ExtraIsoEM;
  evt.getByToken(l1ExtraIsoEMSource_, l1ExtraIsoEM);

  edm::Handle < vector<l1extra::L1EmParticle> > l1ExtraEM;
  evt.getByToken(l1ExtraEMSource_, l1ExtraEM);

  std::vector<l1extra::L1EmParticle> myl1IsoEMcont;  
  myl1IsoEMcont.clear();


  std::vector<l1extra::L1EmParticle> myl1EMcont;  
  myl1EMcont.clear();




  edm::Handle <l1t::EtSumBxCollection> l1ExtraMETStage2;
  evt.getByToken(l1Stage2METSource_, l1ExtraMETStage2);

  edm::Handle<EcalTrigPrimDigiCollection> ecalTPs;
  evt.getByToken(ecalSrc_, ecalTPs);
  edm::Handle<HcalTrigPrimDigiCollection> hcalTPs;
  evt.getByToken(hcalSrc_, hcalTPs);

  edm::Handle<reco::PFMETCollection> pfMet;
  evt.getByToken(pfMetToken_, pfMet);


  edm::Handle<reco::CaloMETCollection> caloMet;
  evt.getByToken(caloMetToken_, caloMet);

  edm::Handle<reco::CaloMETCollection> caloMetBE;
  evt.getByToken(caloMetTokenBE_, caloMetBE);

  edm::Handle<reco::GsfElectronCollection> recoElectrons;
  evt.getByToken(ElectronToken_, recoElectrons);


  std::vector<edm::Handle<edm::ValueMap<bool> > > eleVIDDecisionHandles(4) ;

  evt.getByToken  (ElectronVetoIdMapToken_ , eleVIDDecisionHandles[0]) ;
  evt.getByToken  (ElectronLooseIdMapToken_ , eleVIDDecisionHandles[1]) ;
  evt.getByToken  (ElectronMediumIdMapToken_ , eleVIDDecisionHandles[2]) ;
  evt.getByToken  (ElectronTightIdMapToken_ , eleVIDDecisionHandles[3]) ;
  

  
  l1met_= -999.;
  l1meteta_= -999.;
  l1metphi_= -999.;
  l1metpx_= -999.;
  l1metpy_= -999.;
  l1ettot_ = -999.;
  l1mht_ = -999.;
  l1ethad_ = -999.;
  l1metstage2_ =-999.;
  l1metstage2px_ =-999.;
  l1metstage2py_ =-999.;
  l1metstage2phi_ =-999.;
  l1metstage2eta_ =-999.;
  l1ettotstage2_=-999.;
  l1mhtstage2_ =-999.;
  l1ethadstage2_=-999.;
  PFmet_ = -999.;
  PFmetphi_ = -999.;
  PFmetpx_ = -999.;
  PFmetpy_ = -999.;
  PFmeteta_ = -999.;
  PFSumet_ =-999.;

  nl1isoEm_= 0;
  nl1nonIsoEm_= 0;
  nrecoele_=0;
  l1isoEmEt_.clear();
  l1isoEmEta_.clear();
  l1isoEmPhi_.clear();
  l1isoEmBx_.clear();
  l1nonIsoEmEt_.clear();
  l1nonIsoEmEta_.clear();
  l1nonIsoEmPhi_.clear();
  l1nonIsoEmBx_.clear();

  Elee_.clear();
  Elept_.clear();
  Eleet_.clear();
  Eleeta_.clear();
  Elephi_.clear();
  Eleeta_SC_.clear();
  Elephi_SC_.clear();
  EleECALen_.clear();
  EleSCen_.clear();
  Elecharge_.clear();
  Eleiso_.clear();

  EleisVetoElectron_.clear();
  EleisLooseElectron_.clear();
  EleisMediumElectron_.clear();
  EleisTightElectron_.clear();
  
  
  int expectedTotalET_woHF = 0;
  int expectedTotalET_wHF = 0;
  

  if (pfMet.isValid()) {
    for(reco::PFMETCollection::const_iterator it = pfMet->begin(); it!= pfMet->end(); it++ ){
      PFmet_ = it->et();
      PFmetphi_ = it->phi();
      PFmetpx_ = it->px();
      PFmetpy_ = it->py();
      PFmeteta_ = it->eta();
      PFSumet_ = it->sumEt();
      //      std::cout<<"PFMET: "<<PFmet_<<" PFSumet_:"<<PFSumet_<<std::endl;
      
    }
  }




  if (caloMet.isValid()) {
    for(reco::CaloMETCollection::const_iterator it = caloMet->begin(); it!= caloMet->end(); it++ ){
      Calomet_ = it->et();
      Calometphi_ = it->phi();
      Calometpx_ = it->px();
      Calometpy_ = it->py();
      Calometeta_ = it->eta();
      CaloSumet_ = it->sumEt();
      std::cout<<"CaloMET: "<<Calomet_<<" CaloSumet_:"<<CaloSumet_<<std::endl;
      
    }
  }


  if (caloMetBE.isValid()) {
    for(reco::CaloMETCollection::const_iterator it = caloMetBE->begin(); it!= caloMetBE->end(); it++ ){
      CalometBE_ = it->et();
      CalometBEphi_ = it->phi();
      CalometBEpx_ = it->px();
      CalometBEpy_ = it->py();
      CalometBEeta_ = it->eta();
      CaloSumetBE_ = it->sumEt();
      std::cout<<"CaloMET without HF: "<<CalometBE_<<" CaloSumet_:"<<CaloSumetBE_<<std::endl;
      
    }
  }


  if(recoElectrons.isValid())
    {
      for(reco::GsfElectronCollection::const_iterator el=recoElectrons->begin(); el!=recoElectrons->end(); el++) {
	Elee_.push_back(el->energy());    
	Elept_.push_back(el->pt());    
	Eleet_.push_back(el->et());    
	Eleeta_.push_back(el->eta());
	Elephi_.push_back(el->phi());
	Eleeta_SC_.push_back((el->superClusterPosition()).eta());
	Elephi_SC_.push_back((el->superClusterPosition()).phi());
	EleECALen_.push_back(el->ecalEnergy());
	EleSCen_.push_back(el->superCluster()->energy());
	Elecharge_.push_back(el->charge());

	edm::Ref<reco::GsfElectronCollection> electronEdmRef(recoElectrons,nrecoele_);
	

	EleisVetoElectron_.push_back( (*(eleVIDDecisionHandles[0]))[electronEdmRef] );
	EleisLooseElectron_.push_back( (*(eleVIDDecisionHandles[1]))[electronEdmRef] );
        EleisMediumElectron_.push_back( (*(eleVIDDecisionHandles[2]))[electronEdmRef] );
	EleisTightElectron_.push_back( (*(eleVIDDecisionHandles[3]))[electronEdmRef] );

	
	double iso = (el->pfIsolationVariables().sumChargedHadronPt + max(
									  el->pfIsolationVariables().sumNeutralHadronEt +
									  el->pfIsolationVariables().sumPhotonEt - 
									  0.5 * el->pfIsolationVariables().sumPUPt, 0.0)) / el->pt();
	
	Eleiso_.push_back(iso);
	
	nrecoele_++;
	
	std::cout<<"nrecoele_ "<<nrecoele_<<" Elept_ "<<el->pt()<<" Eleeta_ "<<el->eta()<<" Eleiso_ "<<iso<<"EleisLooseElectron_:"<< (*(eleVIDDecisionHandles[1]))[electronEdmRef]<<" EleisMediumElectron_ "<<(*(eleVIDDecisionHandles[2]))[electronEdmRef]<<std::endl;

      }


    }



  for ( const auto& ecalTp : *ecalTPs ) {
    int et = ecalTp.compressedEt();
    expectedTotalET_woHF += et;
    expectedTotalET_wHF += et;
  }

  for ( const auto& hcalTp : *hcalTPs ) {
    int caloEta = hcalTp.id().ieta();
    uint32_t absCaloEta = abs(caloEta);
    if(absCaloEta == 29) {
      continue;
    }
    else if(hcalTp.id().version() == 0 && absCaloEta > 29) {
      continue;
    }
    else if(absCaloEta <= 28){
      int et = hcalTp.SOI_compressedEt();
      expectedTotalET_woHF += et;
      expectedTotalET_wHF += et;
    }
    else if(absCaloEta <= 41) {
      int et = hcalTp.SOI_compressedEt();
      expectedTotalET_wHF += et;
    }
  }

  //  std::cout<<"ECAL+HCAL et woHF: "<<expectedTotalET_woHF<<" and with HF: "<<expectedTotalET_wHF<<std::endl;

  


  if(l1ExtraMETStage2.isValid())
    {
      for(int ibx = l1ExtraMETStage2->getFirstBX(); ibx <= l1ExtraMETStage2->getLastBX(); ++ibx)
	{
	  for(l1t::EtSumBxCollection::const_iterator it =l1ExtraMETStage2->begin(ibx); it!=l1ExtraMETStage2->end(ibx); it++)
	    {
	      int type = static_cast<int>( it->getType() ); // type =0 totalet; type=1 totalht; type =2 misset; type=3 missht; 
	      if(type==0) l1ettotstage2_=it->et();
	      if(type==1) l1ethadstage2_=it->et();
	      if(type==2) 
		{
		  l1metstage2_=it->et();
		  l1metstage2px_=it->px();
		  l1metstage2py_=it->py();
		  l1metstage2eta_=it->eta();
		  l1metstage2phi_=it->phi();
		}

	      //std::cout<<"Stage 2 total et :"<<l1ettotstage2_<<" and total MET: "<<l1metstage2_<<std::endl;
	      if(type==3) l1mhtstage2_=it->et();
	      //    std::cout<<"type: "<< type<<" Stage2 ET: "<<it->et()<<std::endl;
	      //std::cout<<"Stage2 Total ET: "<<l1ettotstage2_<<" "<<std::endl;
	      //		       <<"l1ethadstage2_: "<<l1ethadstage2_<<" "
	      //		       <<"l1metstage2_: "<<l1metstage2_<<" "
	      //		       <<"l1mhtstage2_: "<<l1mhtstage2_<<" "
	      //		       <<std::endl;
	    }
	}
      
    }





    

  if(l1ExtraMET.isValid()){
    for( vector<l1extra::L1EtMissParticle>::const_iterator l1met = l1ExtraMET->begin(); l1met!= l1ExtraMET->end(); l1met++ ){
      //      l1met_ = l1met->etMiss();
      l1met_ = l1met->et();
      l1ettot_ = l1met->etTotal();
      l1metphi_ = l1met->phi();
      l1meteta_ = l1met->eta();
      l1metpx_ = l1met->px();
      l1metpy_ = l1met->py();
      //std::cout<<"Stage3 phi: "<<l1metphi_<<std::endl;
      //      std::cout<<"Stage3 Total ET: "<<l1ettot_<<" and Met: "<<l1met_<<std::endl;
    }
    
  }

  if(l1ExtraMHT.isValid()){
    for( vector<l1extra::L1EtMissParticle>::const_iterator l1mht = l1ExtraMHT->begin(); l1mht!= l1ExtraMHT->end(); l1mht++ ){
      l1mht_ = l1mht->etMiss();
      l1ethad_ = l1mht->etTotal();
      //std::cout<<"mht: "<<l1mht_<<"total energy: "<<l1ethad_<<std::endl;
      
    }
    
  }

  if(l1ExtraIsoEM.isValid()){
    for( vector<l1extra::L1EmParticle>::const_iterator l1isoem = l1ExtraIsoEM->begin(); l1isoem!= l1ExtraIsoEM->end(); l1isoem++ ){
      myl1IsoEMcont.push_back(*l1isoem);
      //      std::cout<<"l1 Iso EM Stage 3 wo pt ordered:"<<l1isoem->et()<<std::endl;
    }

  }

  if(myl1IsoEMcont.size()>1) std::sort(myl1IsoEMcont.begin(),myl1IsoEMcont.end(),PtSortCriterium());
  
  for(unsigned int x=0;x < myl1IsoEMcont.size(); x++){
    l1isoEmEt_.push_back(myl1IsoEMcont[x].et());
    l1isoEmEta_.push_back(myl1IsoEMcont[x].eta());
    l1isoEmPhi_.push_back(myl1IsoEMcont[x].phi());
    l1isoEmBx_.push_back(myl1IsoEMcont[x].bx());
    nl1isoEm_++;
    //std::cout<<"l1 Iso EM Stage 3:"<<myl1IsoEMcont[x].et()<<std::endl;
  }
  



  if(l1ExtraEM.isValid()){
    for( vector<l1extra::L1EmParticle>::const_iterator l1em = l1ExtraEM->begin(); l1em!= l1ExtraEM->end(); l1em++ ){
      myl1EMcont.push_back(*l1em);
      //std::cout<<"l1 Non Iso EM Stage 3 wo pt ordered:"<<l1em->et()<<std::endl;
    }

  }

  if(myl1EMcont.size()>1) std::sort(myl1EMcont.begin(),myl1EMcont.end(),PtSortCriterium());

  for(unsigned int x=0;x < myl1EMcont.size(); x++){
      l1nonIsoEmEt_.push_back(myl1EMcont[x].et());
      l1nonIsoEmEta_.push_back(myl1EMcont[x].eta());
      l1nonIsoEmPhi_.push_back(myl1EMcont[x].phi());
      l1nonIsoEmBx_.push_back(myl1EMcont[x].bx());
      nl1nonIsoEm_++;
      //      std::cout<<"l1 Non-Iso EM Stage 3:"<<myl1EMcont[x].et()<<std::endl;
  }
    
  





  tree_->Fill();


  



}


// ------------ method called once each job just before starting event loop  ------------
void 
L1Analyzer::beginJob(const edm::EventSetup &es)
{

}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1Analyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------


//define this as a plug-in
DEFINE_FWK_MODULE(L1Analyzer);
