#define EventsMC_cxx
#include "../include/EventsMC.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <TFile.h>
#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
#include <TSystem.h>                // interface to OS
#include <TMath.h>
#include <TTree.h>
#include <TClonesArray.h>           // ROOT array class
#include <TBenchmark.h>             // class to track macro running statistics
#include <TVector2.h>               // 2D vector class
#include <TMath.h>                  // ROOT math library
#include <TLeaf.h>
#include <list>
#include <TCanvas.h>
#include <TH2F.h>
#include <TGraphAsymmErrors.h>
#include <typeinfo>
#include <TGraph.h>
#include <TBranch.h>
#include <TCanvas.h>
#include <TNtuple.h> 
#include <TH1.h>
#include <ROOT/RDataFrame.hxx>
#include "ROOT/RVec.hxx"
#include <TFile.h>
#include <TH1.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "../../FastForest/include/fastforest.h"
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

EventsMC::EventsMC(TTree* tree) :
  EventsBaseMC((TTree*)tree){
    std::cout<<"base"<<std::endl;
  }
void LoadBDT(fastforest::FastForest& bdt,std::string modellocation,std::vector<std::string> features){
    bdt = fastforest::load_txt(modellocation.c_str(), features);
}

float evaluatemodel(fastforest::FastForest& bdt,std::vector<float> input){
    float score = bdt(input.data());
    return score;
}
void timing( int nentries, int jentry, auto start ) {
  auto now = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = now-start;
  std::chrono::duration<double> predicted_duration = elapsed_seconds * (nentries*1.)/(jentry*1.);
  std::chrono::system_clock::time_point end = start + std::chrono::seconds((int)predicted_duration.count());
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::string tmp = std::ctime(&end_time); 
  tmp.resize(tmp.length()-1); // remove trailing \n
  std::cout << "Processed event " << jentry << " out of " << nentries << " (" << int(100.*jentry/nentries) << "%). "
	    << "Time elapsed: " << elapsed_seconds.count() << " s. "
	    << "Time remaining: " << (predicted_duration.count() - elapsed_seconds.count() ) << " s. "
	    << "Predicted finish time: " << tmp
	    << std::endl;
}

void EventsMC::LoopMC(std::string outname, std::string outdir)
{
//   In a ROOT session, you can do:
//      root> .L Events.C
//      root> Events t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   OutputMC(outname,outdir);
   //initialize bdt
   fastforest::FastForest bdt1;

   std::string modellocation1 = "./models/preselbdt15_10_23.txt";

   std::vector<std::string> features1{"BToKEE_l1_PFMvaID_retrained", "BToKEE_l2_PFMvaID_retrained", "BToKEE_fit_pt", "BToKEE_fit_l2_pt"};

   LoadBDT(bdt1,modellocation1,features1);
 
   int interval = 10000;
   auto start = std::chrono::system_clock::now();

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (jentry%interval==0) { timing(nentries,jentry,start); }
      run_MC = run;
      luminosityBlock_MC = luminosityBlock;
      event_MC = event;
      bunchCrossing_MC = bunchCrossing;
      nBToKEE_MC = nBToKEE;
      nElectron_MC = nElectron;
      nGenPart_MC = nGenPart;
      genWeight_MC = genWeight;
      nPSWeight_MC = nPSWeight;
      nProbeTracks_MC = nProbeTracks;
      HLT_DoubleEle10_eta1p22_mMax6_MC = HLT_DoubleEle10_eta1p22_mMax6;
      HLT_DoubleEle9p5_eta1p22_mMax6_MC = HLT_DoubleEle9p5_eta1p22_mMax6;
      HLT_DoubleEle9_eta1p22_mMax6_MC = HLT_DoubleEle9_eta1p22_mMax6;
      HLT_DoubleEle8p5_eta1p22_mMax6_MC = HLT_DoubleEle8p5_eta1p22_mMax6;
      HLT_DoubleEle8_eta1p22_mMax6_MC = HLT_DoubleEle8_eta1p22_mMax6;
      HLT_DoubleEle7p5_eta1p22_mMax6_MC = HLT_DoubleEle7p5_eta1p22_mMax6;
      HLT_DoubleEle7_eta1p22_mMax6_MC = HLT_DoubleEle7_eta1p22_mMax6;
      HLT_DoubleEle6p5_eta1p22_mMax6_MC = HLT_DoubleEle6p5_eta1p22_mMax6;
      HLT_DoubleEle6_eta1p22_mMax6_MC = HLT_DoubleEle6_eta1p22_mMax6;
      HLT_DoubleEle5p5_eta1p22_mMax6_MC = HLT_DoubleEle5p5_eta1p22_mMax6;
      HLT_DoubleEle5_eta1p22_mMax6_MC = HLT_DoubleEle5_eta1p22_mMax6;
      HLT_DoubleEle4p5_eta1p22_mMax6_MC = HLT_DoubleEle4p5_eta1p22_mMax6;
      HLT_DoubleEle4_eta1p22_mMax6_MC = HLT_DoubleEle4_eta1p22_mMax6;
      L1_DoubleEG11_er1p2_dR_Max0p6_MC = L1_DoubleEG11_er1p2_dR_Max0p6;
      L1_DoubleEG10p5_er1p2_dR_Max0p6_MC = L1_DoubleEG10p5_er1p2_dR_Max0p6;
      L1_DoubleEG10_er1p2_dR_Max0p6_MC = L1_DoubleEG10_er1p2_dR_Max0p6;
      L1_DoubleEG9p5_er1p2_dR_Max0p6_MC = L1_DoubleEG9p5_er1p2_dR_Max0p6;
      L1_DoubleEG9_er1p2_dR_Max0p7_MC = L1_DoubleEG9_er1p2_dR_Max0p7;
      L1_DoubleEG8p5_er1p2_dR_Max0p7_MC = L1_DoubleEG8p5_er1p2_dR_Max0p7;
      L1_DoubleEG8_er1p2_dR_Max0p7_MC = L1_DoubleEG8_er1p2_dR_Max0p7;
      L1_DoubleEG7p5_er1p2_dR_Max0p7_MC = L1_DoubleEG7p5_er1p2_dR_Max0p7;
      L1_DoubleEG7_er1p2_dR_Max0p8_MC = L1_DoubleEG7_er1p2_dR_Max0p8;
      L1_DoubleEG6p5_er1p2_dR_Max0p8_MC = L1_DoubleEG6p5_er1p2_dR_Max0p8;
      L1_DoubleEG6_er1p2_dR_Max0p8_MC = L1_DoubleEG6_er1p2_dR_Max0p8;
      L1_DoubleEG5p5_er1p2_dR_Max0p8_MC = L1_DoubleEG5p5_er1p2_dR_Max0p8;
      L1_DoubleEG5_er1p2_dR_Max0p9_MC = L1_DoubleEG5_er1p2_dR_Max0p9;
      L1_DoubleEG4p5_er1p2_dR_Max0p9_MC = L1_DoubleEG4p5_er1p2_dR_Max0p9;
      L1_DoubleEG4_er1p2_dR_Max0p9_MC = L1_DoubleEG4_er1p2_dR_Max0p9;

      L1_4p5_HLT_4p0_ =  L1_DoubleEG4p5_er1p2_dR_Max0p9_MC*HLT_DoubleEle4_eta1p22_mMax6_MC ; 
      L1_5p0_HLT_4p0_ =  L1_DoubleEG5_er1p2_dR_Max0p9_MC*HLT_DoubleEle4_eta1p22_mMax6_MC ; 
      L1_5p5_HLT_4p0_ =  L1_DoubleEG5p5_er1p2_dR_Max0p8_MC*HLT_DoubleEle4_eta1p22_mMax6_MC ; 
      L1_5p5_HLT_6p0_ =  L1_DoubleEG5p5_er1p2_dR_Max0p8_MC*HLT_DoubleEle6_eta1p22_mMax6_MC ; 
      L1_6p0_HLT_4p0_ =  L1_DoubleEG6_er1p2_dR_Max0p8_MC*HLT_DoubleEle4_eta1p22_mMax6_MC ; 
      L1_6p5_HLT_4p5_ =  L1_DoubleEG6p5_er1p2_dR_Max0p8_MC*HLT_DoubleEle4p5_eta1p22_mMax6_MC ; 
      L1_7p0_HLT_5p0_ =  L1_DoubleEG7_er1p2_dR_Max0p8_MC*HLT_DoubleEle5_eta1p22_mMax6_MC ; 
      L1_7p5_HLT_5p0_ =  L1_DoubleEG7p5_er1p2_dR_Max0p7_MC*HLT_DoubleEle5_eta1p22_mMax6_MC ; 
      L1_8p0_HLT_5p0_ =  L1_DoubleEG8_er1p2_dR_Max0p7_MC*HLT_DoubleEle5_eta1p22_mMax6_MC ; 
      L1_8p5_HLT_5p0_ =  L1_DoubleEG8p5_er1p2_dR_Max0p7_MC*HLT_DoubleEle5_eta1p22_mMax6_MC ; 
      L1_8p5_HLT_5p5_ =  L1_DoubleEG8p5_er1p2_dR_Max0p7_MC*HLT_DoubleEle5p5_eta1p22_mMax6_MC ; 
      L1_9p0_HLT_6p0_ =  L1_DoubleEG9_er1p2_dR_Max0p7_MC*HLT_DoubleEle6_eta1p22_mMax6_MC ; 
      L1_10p5_HLT_5p0_ = L1_DoubleEG10p5_er1p2_dR_Max0p6_MC*HLT_DoubleEle5_eta1p22_mMax6_MC  ;
      L1_10p5_HLT_6p5_ = L1_DoubleEG10p5_er1p2_dR_Max0p6_MC*HLT_DoubleEle6p5_eta1p22_mMax6_MC  ;
      L1_11p0_HLT_6p5_ = L1_DoubleEG11_er1p2_dR_Max0p6_MC*HLT_DoubleEle6p5_eta1p22_mMax6_MC  ;
      trigger_OR_ = false;
      if(L1_4p5_HLT_4p0_ || L1_5p0_HLT_4p0_ ||L1_5p5_HLT_4p0_ ||L1_5p5_HLT_6p0_ ||L1_6p0_HLT_4p0_ ||L1_6p5_HLT_4p5_ ||L1_7p0_HLT_5p0_ ||L1_7p5_HLT_5p0_ ||L1_8p0_HLT_5p0_ ||L1_8p5_HLT_5p0_ ||L1_8p5_HLT_5p5_ ||L1_9p0_HLT_6p0_ ||L1_10p5_HLT_5p0_||L1_10p5_HLT_6p5_||L1_11p0_HLT_6p5_){
        trigger_OR_ = true;
      }
      nTrigObj_MC = nTrigObj;
      nOtherPV_MC = nOtherPV;
      PV_ndof_MC = PV_ndof;
      PV_x_MC = PV_x;
      PV_y_MC = PV_y;
      PV_z_MC = PV_z;
      PV_chi2_MC = PV_chi2;
      PV_score_MC = PV_score;
      PV_npvs_MC = PV_npvs;
      PV_npvsGood_MC = PV_npvsGood;
      nSV_MC = nSV;
      genB_pdgId_MC = genB_pdgId;
      genE1_pdgId_MC = genE1_pdgId;
      genE2_pdgId_MC = genE2_pdgId;
      genK_pdgId_MC = genK_pdgId;
      genB_pt_MC = genB_pt;
      genE1_pt_MC = genE1_pt;
      genE2_pt_MC = genE2_pt;
      genK_pt_MC = genK_pt;
      genB_eta_MC = genB_eta;
      genE1_eta_MC = genE1_eta;
      genE2_eta_MC = genE2_eta;
      genK_eta_MC = genK_eta;
      genB_phi_MC = genB_phi;
      genE1_phi_MC = genE1_phi;
      genE2_phi_MC = genE2_phi;
      genK_phi_MC = genK_phi;
      genB_mass_MC = genB_mass;
      genE1_mass_MC = genE1_mass;
      genE2_mass_MC = genE2_mass;
      genK_mass_MC = genK_mass;
      genB_charge_MC = genB_charge;
      genE1_charge_MC = genE1_charge;
      genE2_charge_MC = genE2_charge;
      genK_charge_MC = genK_charge;
      TLorentzVector tloreznel1;
      TLorentzVector tloreznel2;
      tloreznel1.SetPtEtaPhiM(genE1_pt,genE1_eta,genE1_phi,genE1_mass);
      tloreznel2.SetPtEtaPhiM(genE2_pt,genE2_eta,genE2_phi,genE2_mass);      
      TLorentzVector tloreznesum = tloreznel1+tloreznel2;
      genB_mll_MC = tloreznesum.M();
      recoE1_DR_MC = recoE1_DR;
      recoE1_Idx_MC = recoE1_Idx;
      recoE1_pt_MC = recoE1_pt;
      recoE1_eta_MC = recoE1_eta;
      recoE1_phi_MC = recoE1_phi;
      recoE1_vx_MC = recoE1_vx;
      recoE1_vy_MC = recoE1_vy;
      recoE1_vz_MC = recoE1_vz;
      recoE1_isPF_MC = recoE1_isPF;
      recoE1_isPFoverlap_MC = recoE1_isPFoverlap;
      recoE1_charge_MC = recoE1_charge;
      recoE1_PFEleMvaID_Fall17NoIsoV2RawValue_MC = recoE1_PFEleMvaID_Fall17NoIsoV2RawValue;
      recoE1_PFEleMvaID_RetrainedRawValue_MC = recoE1_PFEleMvaID_RetrainedRawValue;
      recoE1_PFEleMvaID_Fall17NoIsoV2wpLoose_MC = recoE1_PFEleMvaID_Fall17NoIsoV2wpLoose;
      recoE1_PFEleMvaID_Fall17NoIsoV2wp90_MC = recoE1_PFEleMvaID_Fall17NoIsoV2wp90;
      recoE1_PFEleMvaID_Fall17NoIsoV2wp80_MC = recoE1_PFEleMvaID_Fall17NoIsoV2wp80;
      recoE1_convVeto_MC = recoE1_convVeto;
      recoE2_DR_MC = recoE2_DR;
      recoE2_Idx_MC = recoE2_Idx;
      recoE2_pt_MC = recoE2_pt;
      recoE2_eta_MC = recoE2_eta;
      recoE2_phi_MC = recoE2_phi;
      recoE2_vx_MC = recoE2_vx;
      recoE2_vy_MC = recoE2_vy;
      recoE2_vz_MC = recoE2_vz;
      recoE2_isPF_MC = recoE2_isPF;
      recoE2_isPFoverlap_MC = recoE2_isPFoverlap;
      recoE2_charge_MC = recoE2_charge;
      recoE2_PFEleMvaID_Fall17NoIsoV2RawValue_MC = recoE2_PFEleMvaID_Fall17NoIsoV2RawValue;
      recoE2_PFEleMvaID_RetrainedRawValue_MC = recoE2_PFEleMvaID_RetrainedRawValue;
      recoE2_PFEleMvaID_Fall17NoIsoV2wpLoose_MC = recoE2_PFEleMvaID_Fall17NoIsoV2wpLoose;
      recoE2_PFEleMvaID_Fall17NoIsoV2wp90_MC = recoE2_PFEleMvaID_Fall17NoIsoV2wp90;
      recoE2_PFEleMvaID_Fall17NoIsoV2wp80_MC = recoE2_PFEleMvaID_Fall17NoIsoV2wp80;
      recoE2_convVeto_MC = recoE2_convVeto;
      recoK_DR_MC = recoK_DR;
      recoK_Idx_MC = recoK_Idx;
      recoK_pt_MC = recoK_pt;
      recoK_eta_MC = recoK_eta;
      recoK_phi_MC = recoK_phi;
      recoK_vx_MC = recoK_vx;
      recoK_vy_MC = recoK_vy;
      recoK_vz_MC = recoK_vz;
      recoK_DCASig_MC = recoK_DCASig;
      recoK_dzTrg_MC = recoK_dzTrg;
      recoK_isMatchedToMuon_MC = recoK_isMatchedToMuon;
      recoK_charge_MC = recoK_charge;
      npreSkimBToKEE_MC = npreSkimBToKEE;



      recoB_fit_pt_MC = recoB_fit_pt;
      recoB_fit_eta_MC = recoB_fit_eta;
      recoB_fit_phi_MC = recoB_fit_phi;
      recoB_D0_mass_LepToK_KToPi_MC = recoB_D0_mass_LepToK_KToPi;
      recoB_D0_mass_LepToPi_KToK_MC = recoB_D0_mass_LepToPi_KToK;
      recoB_fit_mass_MC = recoB_fit_mass;
      recoB_l_xy_MC = recoB_l_xy;
      recoB_l_xy_unc_MC = recoB_l_xy_unc;
      recoB_fit_cos2D_MC = recoB_fit_cos2D;
      recoB_svprob_MC = recoB_svprob;
      recoB_fit_massErr_MC = recoB_fit_massErr;
      recoB_b_iso04_MC = recoB_b_iso04;
      recoB_mll_fullfit_MC = recoB_mll_fullfit;
      recoB_vtx_x_MC = recoB_vtx_x;
      recoB_vtx_y_MC = recoB_vtx_y;
      recoB_vtx_z_MC = recoB_vtx_z;
      recoB_l1Idx_MC = recoB_l1Idx;
      recoB_l2Idx_MC = recoB_l2Idx;
      recoB_kIdx_MC = recoB_kIdx;
      recoB_fit_k_pt_MC = recoB_fit_k_pt;
      recoB_fit_k_eta_MC = recoB_fit_k_eta;
      recoB_fit_k_phi_MC = recoB_fit_k_phi;
      recoB_fit_l1_pt_MC = recoB_fit_l1_pt;
      recoB_fit_l1_eta_MC = recoB_fit_l1_eta;
      recoB_fit_l1_phi_MC = recoB_fit_l1_phi;
      recoB_fit_l2_pt_MC = recoB_fit_l2_pt;
      recoB_fit_l2_eta_MC = recoB_fit_l2_eta;
      recoB_fit_l2_phi_MC = recoB_fit_l2_phi;
      recoB_l1_iso04_MC = recoB_l1_iso04;
      recoB_l2_iso04_MC = recoB_l2_iso04;
      recoB_l1_isPF_MC = recoB_l1_isPF;
      recoB_l2_isPF_MC = recoB_l2_isPF;
      recoB_k_iso04_MC = recoB_k_iso04;
      recoB_l1_isPFoverlap_MC = recoB_l1_isPFoverlap;
      recoB_l2_isPFoverlap_MC = recoB_l2_isPFoverlap;
      recoB_l1_LooseId_MC = recoB_l1_LooseId;
      recoB_l2_LooseId_MC = recoB_l2_LooseId;
      recoB_l1_MediumId_MC = recoB_l1_MediumId;
      recoB_l2_MediumId_MC = recoB_l2_MediumId;
      recoB_l1_TightId_MC = recoB_l1_TightId;
      recoB_l2_TightId_MC = recoB_l2_TightId;
      recoB_l1_ConvVeto_MC = recoB_l1_ConvVeto;
      recoB_l2_ConvVeto_MC = recoB_l2_ConvVeto;
      recoB_l1_PFMvaID_Fall17_MC = recoB_l1_PFMvaID_Fall17;
      recoB_l2_PFMvaID_Fall17_MC = recoB_l2_PFMvaID_Fall17;
      recoB_l1_PFMvaID_retrained_MC = recoB_l1_PFMvaID_retrained;
      recoB_l2_PFMvaID_retrained_MC = recoB_l2_PFMvaID_retrained;
      recoB_l1_iso04_dca_MC = recoB_l1_iso04_dca;
      recoB_l2_iso04_dca_MC = recoB_l2_iso04_dca;
      recoB_b_iso04_dca_MC = recoB_b_iso04_dca;
      recoB_k_iso04_dca_MC = recoB_k_iso04_dca;
      recoB_k_svip3d_MC = recoB_k_svip3d;
      recoB_k_svip3d_err_MC = recoB_k_svip3d_err;
      recoB_l1_n_isotrk_dca_MC = recoB_l1_n_isotrk_dca;
      recoB_l2_n_isotrk_dca_MC = recoB_l2_n_isotrk_dca;
      recoB_k_n_isotrk_dca_MC = recoB_k_n_isotrk_dca;
      recoB_Idx_MC = recoB_Idx;
      recoB_l_xy_sig_MC = recoB_l_xy_sig;
      recoB_l1l2Dz_MC = recoB_l1l2Dz;
      recoB_lKDz_MC = recoB_lKDz;
      recoB_l1l2Dr_MC = recoB_l1l2Dr;
      recoB_lKDr_MC = recoB_lKDr;
      recoB_k_opp_l_mass_MC = recoB_k_opp_l_mass;      
      recoB_p_assymetry_MC = recoB_p_assymetry; 
      trig_wgt_MC = trig_wgt;
      float k_svip3d_sig_MC = recoB_k_svip3d_MC/recoB_k_svip3d_err_MC;
      float fit_pt_over_mass_MC = recoB_fit_pt_MC/recoB_fit_mass_MC;
      float fit_pt_l1_over_mass_MC = recoB_fit_l1_pt_MC/recoB_fit_mass_MC;
      float fit_pt_l2_over_mass_MC = recoB_fit_l2_pt_MC/recoB_fit_mass_MC;
      float fit_pt_k_over_mass_MC = recoB_fit_k_pt_MC/recoB_fit_mass_MC;

      std::vector<float> input1{recoB_l1_PFMvaID_retrained_MC,recoB_l2_PFMvaID_retrained_MC,recoB_fit_pt_MC,recoB_fit_l2_pt_MC};


      BDTSCORE_1_MC = bdt1(input1.data());
//      if (BDTSCORE_1_MC<-3.4003663){
//            initVarsMC();
//            goto end;
//      }
      //std::cout<<HLT_DoubleEle10_eta1p22_mMax6_<<std::endl;
      outTreeMC_->Fill();  
//      end:;
   
      nb = fChain->GetEntry(jentry);   nbytes += nb;
   }
   initVarsMC();

   outFileMC_->Write();
   outFileMC_->Close();
}
void EventsMC::OutputMC(std::string outname, std::string outdir) {
   TString outputfilename(std::string(outdir)+"/"+std::string(outname)+"_MC_.root");
   outFileMC_ = new TFile(outputfilename,"RECREATE");
   outTreeMC_ = new TTree("Events","Events");
   outTreeMC_->Branch("run", &run_MC);
   outTreeMC_->Branch("luminosityBlock", &luminosityBlock_MC);
   outTreeMC_->Branch("event", &       event_MC);
   outTreeMC_->Branch("bunchCrossing", &bunchCrossing_MC);
   outTreeMC_->Branch("nBToKEE", &nBToKEE_MC);
   outTreeMC_->Branch("nElectron", &nElectron_MC);
   outTreeMC_->Branch("nGenPart", &nGenPart_MC);
   outTreeMC_->Branch("genWeight", &genWeight_MC);
   outTreeMC_->Branch("nPSWeight", &nPSWeight_MC);
   outTreeMC_->Branch("nProbeTracks", &nProbeTracks_MC);
   outTreeMC_->Branch("HLT_DoubleEle10_eta1p22_mMax6", &HLT_DoubleEle10_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle9p5_eta1p22_mMax6", &HLT_DoubleEle9p5_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle9_eta1p22_mMax6", &HLT_DoubleEle9_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle8p5_eta1p22_mMax6", &HLT_DoubleEle8p5_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle8_eta1p22_mMax6", &HLT_DoubleEle8_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle7p5_eta1p22_mMax6", &HLT_DoubleEle7p5_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle7_eta1p22_mMax6", &HLT_DoubleEle7_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle6p5_eta1p22_mMax6", &HLT_DoubleEle6p5_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle6_eta1p22_mMax6", &HLT_DoubleEle6_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle5p5_eta1p22_mMax6", &HLT_DoubleEle5p5_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle5_eta1p22_mMax6", &HLT_DoubleEle5_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle4p5_eta1p22_mMax6", &HLT_DoubleEle4p5_eta1p22_mMax6_MC);
   outTreeMC_->Branch("HLT_DoubleEle4_eta1p22_mMax6", &HLT_DoubleEle4_eta1p22_mMax6_MC);
   outTreeMC_->Branch("L1_DoubleEG11_er1p2_dR_Max0p6", &L1_DoubleEG11_er1p2_dR_Max0p6_MC);
   outTreeMC_->Branch("L1_DoubleEG10p5_er1p2_dR_Max0p6", &L1_DoubleEG10p5_er1p2_dR_Max0p6_MC);
   outTreeMC_->Branch("L1_DoubleEG10_er1p2_dR_Max0p6", &L1_DoubleEG10_er1p2_dR_Max0p6_MC);
   outTreeMC_->Branch("L1_DoubleEG9p5_er1p2_dR_Max0p6", &L1_DoubleEG9p5_er1p2_dR_Max0p6_MC);
   outTreeMC_->Branch("L1_DoubleEG9_er1p2_dR_Max0p7", &L1_DoubleEG9_er1p2_dR_Max0p7_MC);
   outTreeMC_->Branch("L1_DoubleEG8p5_er1p2_dR_Max0p7", &L1_DoubleEG8p5_er1p2_dR_Max0p7_MC);
   outTreeMC_->Branch("L1_DoubleEG8_er1p2_dR_Max0p7", &L1_DoubleEG8_er1p2_dR_Max0p7_MC);
   outTreeMC_->Branch("L1_DoubleEG7p5_er1p2_dR_Max0p7", &L1_DoubleEG7p5_er1p2_dR_Max0p7_MC);
   outTreeMC_->Branch("L1_DoubleEG7_er1p2_dR_Max0p8", &L1_DoubleEG7_er1p2_dR_Max0p8_MC);
   outTreeMC_->Branch("L1_DoubleEG6p5_er1p2_dR_Max0p8", &L1_DoubleEG6p5_er1p2_dR_Max0p8_MC);
   outTreeMC_->Branch("L1_DoubleEG6_er1p2_dR_Max0p8", &L1_DoubleEG6_er1p2_dR_Max0p8_MC);
   outTreeMC_->Branch("L1_DoubleEG5p5_er1p2_dR_Max0p8", &L1_DoubleEG5p5_er1p2_dR_Max0p8_MC);
   outTreeMC_->Branch("L1_DoubleEG5_er1p2_dR_Max0p9", &L1_DoubleEG5_er1p2_dR_Max0p9_MC);
   outTreeMC_->Branch("L1_DoubleEG4p5_er1p2_dR_Max0p9", &L1_DoubleEG4p5_er1p2_dR_Max0p9_MC);
   outTreeMC_->Branch("L1_DoubleEG4_er1p2_dR_Max0p9", &L1_DoubleEG4_er1p2_dR_Max0p9_MC);

   outTreeMC_->Branch("L1_4p5_HLT_4p0",&L1_4p5_HLT_4p0_);
   outTreeMC_->Branch("L1_5p0_HLT_4p0",&L1_5p0_HLT_4p0_);
   outTreeMC_->Branch("L1_5p5_HLT_4p0",&L1_5p5_HLT_4p0_);
   outTreeMC_->Branch("L1_5p5_HLT_6p0",&L1_5p5_HLT_6p0_);
   outTreeMC_->Branch("L1_6p0_HLT_4p0",&L1_6p0_HLT_4p0_);
   outTreeMC_->Branch("L1_6p5_HLT_4p5",&L1_6p5_HLT_4p5_);
   outTreeMC_->Branch("L1_7p0_HLT_5p0",&L1_7p0_HLT_5p0_);
   outTreeMC_->Branch("L1_7p5_HLT_5p0",&L1_7p5_HLT_5p0_);
   outTreeMC_->Branch("L1_8p0_HLT_5p0",&L1_8p0_HLT_5p0_);
   outTreeMC_->Branch("L1_8p5_HLT_5p0",&L1_8p5_HLT_5p0_);
   outTreeMC_->Branch("L1_8p5_HLT_5p5",&L1_8p5_HLT_5p5_);
   outTreeMC_->Branch("L1_9p0_HLT_6p0",&L1_9p0_HLT_6p0_);
   outTreeMC_->Branch("L1_10p5_HLT_5p0",&L1_10p5_HLT_5p0_);
   outTreeMC_->Branch("L1_10p5_HLT_6p5",&L1_10p5_HLT_6p5_);
   outTreeMC_->Branch("L1_11p0_HLT_6p5",&L1_11p0_HLT_6p5_);
   outTreeMC_->Branch("trigger_OR",&trigger_OR_);

   outTreeMC_->Branch("nTrigObj", &nTrigObj_MC);
   outTreeMC_->Branch("nOtherPV", &nOtherPV_MC);
   outTreeMC_->Branch("PV_ndof", &PV_ndof_MC);
   outTreeMC_->Branch("PV_x", &PV_x_MC);
   outTreeMC_->Branch("PV_y", &PV_y_MC);
   outTreeMC_->Branch("PV_z", &PV_z_MC);
   outTreeMC_->Branch("PV_chi2", &PV_chi2_MC);
   outTreeMC_->Branch("PV_score", &PV_score_MC);
   outTreeMC_->Branch("PV_npvs", &PV_npvs_MC);
   outTreeMC_->Branch("PV_npvsGood", &PV_npvsGood_MC);
   outTreeMC_->Branch("nSV", &nSV_MC);
   outTreeMC_->Branch("genB_pdgId", &genB_pdgId_MC );
   outTreeMC_->Branch("genE1_pdgId", &genE1_pdgId_MC);
   outTreeMC_->Branch("genE2_pdgId", &genE2_pdgId_MC);
   outTreeMC_->Branch("genK_pdgId ", &genK_pdgId_MC );
   outTreeMC_->Branch("genB_pt ", &genB_pt_MC );
   outTreeMC_->Branch("genE1_pt", &genE1_pt_MC);
   outTreeMC_->Branch("genE2_pt", &genE2_pt_MC   );
   outTreeMC_->Branch("genK_pt", &genK_pt_MC);
   outTreeMC_->Branch("genB_eta ", &genB_eta_MC );
   outTreeMC_->Branch("genE1_eta", &genE1_eta_MC);
   outTreeMC_->Branch("genE2_eta", &genE2_eta_MC);
   outTreeMC_->Branch("genK_eta ", &genK_eta_MC );
   outTreeMC_->Branch("genB_phi ", &genB_phi_MC );
   outTreeMC_->Branch("genE1_phi", &genE1_phi_MC);
   outTreeMC_->Branch("genE2_phi", &genE2_phi_MC);
   outTreeMC_->Branch("genK_phi ", &genK_phi_MC );
   outTreeMC_->Branch("genB_mass", &genB_mass_MC);
   outTreeMC_->Branch("genE1_mass", &genE1_mass_MC);
   outTreeMC_->Branch("genE2_mass", &genE2_mass_MC);
   outTreeMC_->Branch("genK_mass ", &genK_mass_MC );
   outTreeMC_->Branch("genB_charge ", &genB_charge_MC );
   outTreeMC_->Branch("genE1_charge", &genE1_charge_MC);
   outTreeMC_->Branch("genE2_charge", &genE2_charge_MC);
   outTreeMC_->Branch("genK_charge", &genK_charge_MC);
   outTreeMC_->Branch("genB_mll", &genB_mll_MC);

   outTreeMC_->Branch("nSkimBToKEE", &npreSkimBToKEE_MC);
   outTreeMC_->Branch("BToKEE_fit_pt", &recoB_fit_pt_MC);
   outTreeMC_->Branch("BToKEE_fit_eta", &recoB_fit_eta_MC);
   outTreeMC_->Branch("BToKEE_fit_phi", &recoB_fit_phi_MC);
   outTreeMC_->Branch("BToKEE_D0_mass_LepToK_KToPi", &recoB_D0_mass_LepToK_KToPi_MC);
   outTreeMC_->Branch("BToKEE_D0_mass_LepToPi_KToK", &recoB_D0_mass_LepToPi_KToK_MC);
   outTreeMC_->Branch("BToKEE_fit_mass", &recoB_fit_mass_MC);
   outTreeMC_->Branch("BToKEE_l_xy", &recoB_l_xy_MC);
   outTreeMC_->Branch("BToKEE_l_xy_unc", &recoB_l_xy_unc_MC);
   outTreeMC_->Branch("BToKEE_fit_cos2D", &recoB_fit_cos2D_MC);
   outTreeMC_->Branch("BToKEE_svprob", &recoB_svprob_MC);
   outTreeMC_->Branch("BToKEE_fit_massErr", &recoB_fit_massErr_MC);
   outTreeMC_->Branch("BToKEE_b_iso04", &recoB_b_iso04_MC);
   outTreeMC_->Branch("BToKEE_mll_fullfit", &recoB_mll_fullfit_MC);
   outTreeMC_->Branch("BToKEE_vtx_x", &recoB_vtx_x_MC);
   outTreeMC_->Branch("BToKEE_vtx_y", &recoB_vtx_y_MC);
   outTreeMC_->Branch("BToKEE_vtx_z", &recoB_vtx_z_MC);
   outTreeMC_->Branch("BToKEE_l1Idx", &recoB_l1Idx_MC);
   outTreeMC_->Branch("BToKEE_l2Idx", &recoB_l2Idx_MC);
   outTreeMC_->Branch("BToKEE_kIdx", &recoB_kIdx_MC);
   outTreeMC_->Branch("BToKEE_fit_k_pt", &recoB_fit_k_pt_MC);
   outTreeMC_->Branch("BToKEE_fit_k_eta", &recoB_fit_k_eta_MC);
   outTreeMC_->Branch("BToKEE_fit_k_phi", &recoB_fit_k_phi_MC);
   outTreeMC_->Branch("BToKEE_fit_l1_pt", &recoB_fit_l1_pt_MC);
   outTreeMC_->Branch("BToKEE_fit_l1_eta", &recoB_fit_l1_eta_MC);
   outTreeMC_->Branch("BToKEE_fit_l1_phi", &recoB_fit_l1_phi_MC);
   outTreeMC_->Branch("BToKEE_fit_l2_pt", &recoB_fit_l2_pt_MC);
   outTreeMC_->Branch("BToKEE_fit_l2_eta", &recoB_fit_l2_eta_MC);
   outTreeMC_->Branch("BToKEE_fit_l2_phi", &recoB_fit_l2_phi_MC);
   outTreeMC_->Branch("BToKEE_l1_iso04", &recoB_l1_iso04_MC);
   outTreeMC_->Branch("BToKEE_l2_iso04", &recoB_l2_iso04_MC);
   outTreeMC_->Branch("BToKEE_l1_isPF", &recoB_l1_isPF_MC);
   outTreeMC_->Branch("BToKEE_l2_isPF", &recoB_l2_isPF_MC);
   outTreeMC_->Branch("BToKEE_k_iso04", &recoB_k_iso04_MC);
   outTreeMC_->Branch("BToKEE_l1_isPFoverlap", &recoB_l1_isPFoverlap_MC);
   outTreeMC_->Branch("BToKEE_l2_isPFoverlap", &recoB_l2_isPFoverlap_MC);
   outTreeMC_->Branch("BToKEE_l1_LooseId", &recoB_l1_LooseId_MC);
   outTreeMC_->Branch("BToKEE_l2_LooseId", &recoB_l2_LooseId_MC);
   outTreeMC_->Branch("BToKEE_l1_MediumId", &recoB_l1_MediumId_MC);
   outTreeMC_->Branch("BToKEE_l2_MediumId", &recoB_l2_MediumId_MC);
   outTreeMC_->Branch("BToKEE_l1_TightId", &recoB_l1_TightId_MC);
   outTreeMC_->Branch("BToKEE_l2_TightId", &recoB_l2_TightId_MC);
   outTreeMC_->Branch("BToKEE_l1_ConvVeto", &recoB_l1_ConvVeto_MC);
   outTreeMC_->Branch("BToKEE_l2_ConvVeto", &recoB_l2_ConvVeto_MC);
   outTreeMC_->Branch("BToKEE_l1_PFMvaID_Fall17", &recoB_l1_PFMvaID_Fall17_MC);
   outTreeMC_->Branch("BToKEE_l2_PFMvaID_Fall17", &recoB_l2_PFMvaID_Fall17_MC);
   outTreeMC_->Branch("BToKEE_l1_PFMvaID_retrained", &recoB_l1_PFMvaID_retrained_MC);
   outTreeMC_->Branch("BToKEE_l2_PFMvaID_retrained", &recoB_l2_PFMvaID_retrained_MC);
   outTreeMC_->Branch("BToKEE_l1_iso04_dca", &recoB_l1_iso04_dca_MC);
   outTreeMC_->Branch("BToKEE_l2_iso04_dca", &recoB_l2_iso04_dca_MC);
   outTreeMC_->Branch("BToKEE_b_iso04_dca", &recoB_b_iso04_dca_MC);
   outTreeMC_->Branch("BToKEE_k_iso04_dca", &recoB_k_iso04_dca_MC);
   outTreeMC_->Branch("BToKEE_k_svip3d", &recoB_k_svip3d_MC);
   outTreeMC_->Branch("BToKEE_k_svip3d_err", &recoB_k_svip3d_err_MC);
   outTreeMC_->Branch("BToKEE_l1_n_isotrk_dca", &recoB_l1_n_isotrk_dca_MC);
   outTreeMC_->Branch("BToKEE_l2_n_isotrk_dca", &recoB_l2_n_isotrk_dca_MC);
   outTreeMC_->Branch("BToKEE_k_n_isotrk_dca", &recoB_k_n_isotrk_dca_MC);
   outTreeMC_->Branch("BToKEE_l1_vx", &recoE1_vx_MC);
   outTreeMC_->Branch("BToKEE_l1_vy", &recoE1_vy_MC);
   outTreeMC_->Branch("BToKEE_l1_vz", &recoE1_vz_MC);
   outTreeMC_->Branch("BToKEE_l1_charge", &recoE1_charge_MC);
   outTreeMC_->Branch("BToKEE_l2_vx", &recoE2_vx_MC);
   outTreeMC_->Branch("BToKEE_l2_vy", &recoE2_vy_MC);
   outTreeMC_->Branch("BToKEE_l2_vz", &recoE2_vz_MC);
   outTreeMC_->Branch("BToKEE_l2_charge", &recoE2_charge_MC);
   outTreeMC_->Branch("BToKEE_k_vx", &recoK_vx_MC);
   outTreeMC_->Branch("BToKEE_k_vy", &recoK_vy_MC);
   outTreeMC_->Branch("BToKEE_k_vz", &recoK_vz_MC);
   outTreeMC_->Branch("BToKEE_k_dca_sig", &recoK_DCASig_MC);
   outTreeMC_->Branch("BToKEE_k_dz", &recoK_dzTrg_MC);
   outTreeMC_->Branch("BToKEE_kMu_matched", &recoK_isMatchedToMuon_MC);
   outTreeMC_->Branch("BToKEE_l_xy_sig", &recoB_l_xy_sig_MC);
   outTreeMC_->Branch("BToKEE_l1l2Dz", &recoB_l1l2Dz_MC);
   outTreeMC_->Branch("BToKEE_lKDz", &recoB_lKDz_MC);
   outTreeMC_->Branch("BToKEE_l1l2Dr", &recoB_l1l2Dr_MC);
   outTreeMC_->Branch("BToKEE_lKDr", &recoB_lKDr_MC);
   outTreeMC_->Branch("BToKEE_kl_massKPi", &recoB_k_opp_l_mass_MC);
   outTreeMC_->Branch("BToKEE_p_assymetry", &recoB_p_assymetry_MC);
   outTreeMC_->Branch("trig_wgt", &trig_wgt_MC);
   //outTreeMC_->Branch("BDTSCORE_1", &BDTSCORE_1_MC);
   outTreeMC_->Branch("Presel_BDT", &BDTSCORE_1_MC);

}
void EventsMC::initVarsMC() {
    run_MC=-1000;
    luminosityBlock_MC=-1000;
    event_MC=-1000;
    bunchCrossing_MC=-1000;
    nBToKEE_MC=-1000;
    nElectron_MC=-1000;
    nGenPart_MC=-1000;
    genWeight_MC=-1000;
    nPSWeight_MC=-1000;
    PSWeight_MC=-1000;
    nProbeTracks_MC=-1000;
    HLT_DoubleEle10_eta1p22_mMax6_MC= false;
    HLT_DoubleEle9p5_eta1p22_mMax6_MC= false;
    HLT_DoubleEle9_eta1p22_mMax6_MC= false;
    HLT_DoubleEle8p5_eta1p22_mMax6_MC= false;
    HLT_DoubleEle8_eta1p22_mMax6_MC= false;
    HLT_DoubleEle7p5_eta1p22_mMax6_MC= false;
    HLT_DoubleEle7_eta1p22_mMax6_MC= false;
    HLT_DoubleEle6p5_eta1p22_mMax6_MC= false;
    HLT_DoubleEle6_eta1p22_mMax6_MC= false;
    HLT_DoubleEle5p5_eta1p22_mMax6_MC= false;
    HLT_DoubleEle5_eta1p22_mMax6_MC= false;
    HLT_DoubleEle4p5_eta1p22_mMax6_MC= false;
    HLT_DoubleEle4_eta1p22_mMax6_MC= false;
    L1_DoubleEG11_er1p2_dR_Max0p6_MC= false;
    L1_DoubleEG10p5_er1p2_dR_Max0p6_MC= false;
    L1_DoubleEG10_er1p2_dR_Max0p6_MC= false;
    L1_DoubleEG9p5_er1p2_dR_Max0p6_MC= false;
    L1_DoubleEG9_er1p2_dR_Max0p7_MC= false;
    L1_DoubleEG8p5_er1p2_dR_Max0p7_MC= false;
    L1_DoubleEG8_er1p2_dR_Max0p7_MC= false;
    L1_DoubleEG7p5_er1p2_dR_Max0p7_MC= false;
    L1_DoubleEG7_er1p2_dR_Max0p8_MC= false;
    L1_DoubleEG6p5_er1p2_dR_Max0p8_MC= false;
    L1_DoubleEG6_er1p2_dR_Max0p8_MC= false;
    L1_DoubleEG5p5_er1p2_dR_Max0p8_MC= false;
    L1_DoubleEG5_er1p2_dR_Max0p9_MC= false;
    L1_DoubleEG4p5_er1p2_dR_Max0p9_MC= false;
    L1_DoubleEG4_er1p2_dR_Max0p9_MC= false;




    L1_4p5_HLT_4p0_ = false;
    L1_5p0_HLT_4p0_ = false;
    L1_5p5_HLT_4p0_ = false;
    L1_5p5_HLT_6p0_ = false;
    L1_6p0_HLT_4p0_ = false;
    L1_6p5_HLT_4p5_ = false;
    L1_7p0_HLT_5p0_ = false;
    L1_7p5_HLT_5p0_ = false;
    L1_8p0_HLT_5p0_ = false;
    L1_8p5_HLT_5p0_ = false;
    L1_8p5_HLT_5p5_ = false;
    L1_9p0_HLT_6p0_ = false;
    L1_10p5_HLT_5p0_= false;
    L1_10p5_HLT_6p5_= false;
    L1_11p0_HLT_6p5_= false;
    trigger_OR_     = false;
    
    nTrigObj_MC=-1000;
    nOtherPV_MC=-1000;
    PV_ndof_MC=-1000.;
    PV_x_MC=-1000.;
    PV_y_MC=-1000.;
    PV_z_MC=-1000.;
    PV_chi2_MC= -1000.;
    PV_score_MC= -1000.;
    PV_npvs_MC=-1000;
    PV_npvsGood_MC=-1000;
    nSV_MC=-1000;
    genB_pdgId_MC=-1000.;
    genE1_pdgId_MC=-1000.;
    genE2_pdgId_MC=-1000.;
    genK_pdgId_MC=-1000.;
    genB_pt_MC=-1000.;
    genE1_pt_MC=-1000.;
    genE2_pt_MC=-1000.;
    genK_pt_MC=-1000.;
    genB_eta_MC=-1000.;
    genE1_eta_MC=-1000.;
    genE2_eta_MC=-1000.;
    genK_eta_MC=-1000.;
    genB_phi_MC=-1000.;
    genE1_phi_MC=-1000.;
    genE2_phi_MC=-1000.;
    genK_phi_MC=-1000.;
    genB_mass_MC=-1000.;
    genE1_mass_MC=-1000.;
    genE2_mass_MC=-1000.;
    genK_mass_MC=-1000.;
    genB_charge_MC=-1000.;
    genE1_charge_MC=-1000.;
    genE2_charge_MC=-1000.;
    genK_charge_MC=-1000.;
    genB_mll_MC=-1000.;
    recoE1_DR_MC=-1000.;
    recoE1_Idx_MC=-1000.;
    recoE1_pt_MC=-1000.;
    recoE1_eta_MC=-1000.;
    recoE1_phi_MC=-1000.;
    recoE1_vx_MC=-1000.;
    recoE1_vy_MC=-1000.;
    recoE1_vz_MC=-1000.;
    recoE1_isPF_MC=-1000.;
    recoE1_isPFoverlap_MC=-1000.;
    recoE1_charge_MC=-1000.;
    recoE1_PFEleMvaID_Fall17NoIsoV2wp90_MC=-1000.;
    recoE1_PFEleMvaID_RetrainedRawValue_MC=-1000.;
    recoE1_PFEleMvaID_Fall17NoIsoV2wpLoose_MC=-1000.;
    recoE1_PFEleMvaID_Fall17NoIsoV2wp90_MC=-1000.;
    recoE1_PFEleMvaID_Fall17NoIsoV2wp80_MC=-1000.;
    recoE1_convVeto_MC=-1000.;
    recoE2_DR_MC=-1000.;
    recoE2_Idx_MC=-1000.;
    recoE2_pt_MC=-1000.;
    recoE2_eta_MC=-1000.;
    recoE2_phi_MC=-1000.;
    recoE2_vx_MC=-1000.;
    recoE2_vy_MC=-1000.;
    recoE2_vz_MC=-1000.;
    recoE2_isPF_MC=-1000.;
    recoE2_isPFoverlap_MC=-1000.;
    recoE2_charge_MC=-1000.;
    recoE2_PFEleMvaID_Fall17NoIsoV2RawValue_MC=-1000.;
    recoE2_PFEleMvaID_RetrainedRawValue_MC=-1000.;
    recoE2_PFEleMvaID_Fall17NoIsoV2wpLoose_MC=-1000.;
    recoE2_PFEleMvaID_Fall17NoIsoV2wp90_MC=-1000.;
    recoE2_PFEleMvaID_Fall17NoIsoV2wp80_MC=-1000.;
    recoE2_convVeto_MC=-1000.;
    recoK_DR_MC=-1000.;
    recoK_Idx_MC=-1000.;
    recoK_pt_MC=-1000.;
    recoK_eta_MC=-1000.;
    recoK_phi_MC=-1000.;
    recoK_vx_MC=-1000.;
    recoK_vy_MC=-1000.;
    recoK_vz_MC=-1000.;
    recoK_DCASig_MC=-1000.;
    recoK_dzTrg_MC=-1000.;
    recoK_isMatchedToMuon_MC=-1000.;
    recoK_charge_MC=-1000.;
    npreSkimBToKEE_MC=-1000;
    recoB_fit_pt_MC=-1000.;
    recoB_fit_eta_MC=-1000.;
    recoB_fit_phi_MC=-1000.;
    recoB_D0_mass_LepToK_KToPi_MC=-1000.;
    recoB_D0_mass_LepToPi_KToK_MC=-1000.;
    recoB_fit_mass_MC=-1000.;
    recoB_l_xy_MC=-1000.;
    recoB_l_xy_unc_MC=-1000.;
    recoB_fit_cos2D_MC=-1000.;
    recoB_svprob_MC=-1000.;
    recoB_fit_massErr_MC=-1000.;
    recoB_b_iso04_MC=-1000.;
    recoB_mll_fullfit_MC=-1000.;
    recoB_vtx_x_MC=-1000.;
    recoB_vtx_y_MC=-1000.;
    recoB_vtx_z_MC=-1000.;
    recoB_l1Idx_MC=-1000.;
    recoB_l2Idx_MC=-1000.;
    recoB_kIdx_MC=-1000.;
    recoB_fit_k_pt_MC=-1000.;
    recoB_fit_k_eta_MC=-1000.;
    recoB_fit_k_phi_MC=-1000.;
    recoB_fit_l1_pt_MC=-1000.;
    recoB_fit_l1_eta_MC=-1000.;
    recoB_fit_l1_phi_MC=-1000.;
    recoB_fit_l2_pt_MC=-1000.;
    recoB_fit_l2_eta_MC=-1000.;
    recoB_fit_l2_phi_MC=-1000.;
    recoB_l1_iso04_MC=-1000.;
    recoB_l2_iso04_MC=-1000.;
    recoB_l1_isPF_MC=-1000.;
    recoB_l2_isPF_MC=-1000.;
    recoB_k_iso04_MC=-1000.;
    recoB_l1_isPFoverlap_MC=-1000.;
    recoB_l2_isPFoverlap_MC=-1000.;
    recoB_l1_LooseId_MC=-1000.;
    recoB_l2_LooseId_MC=-1000.;
    recoB_l1_MediumId_MC=-1000.;
    recoB_l2_MediumId_MC=-1000.;
    recoB_l1_TightId_MC=-1000.;
    recoB_l2_TightId_MC=-1000.;
    recoB_l1_ConvVeto_MC=-1000.;
    recoB_l2_ConvVeto_MC=-1000.;
    recoB_l1_PFMvaID_Fall17_MC=-1000.;
    recoB_l2_PFMvaID_Fall17_MC=-1000.;
    recoB_l1_PFMvaID_retrained_MC=-1000.;
    recoB_l2_PFMvaID_retrained_MC=-1000.;
    recoB_l1_iso04_dca_MC=-1000.;
    recoB_l2_iso04_dca_MC=-1000.;
    recoB_b_iso04_dca_MC=-1000.;
    recoB_k_iso04_dca_MC=-1000.;
    recoB_k_svip3d_MC=-1000.;
    recoB_k_svip3d_err_MC=-1000.;
    recoB_l1_n_isotrk_dca_MC=-1000.;
    recoB_l2_n_isotrk_dca_MC=-1000.;
    recoB_k_n_isotrk_dca_MC=-1000.;
    recoB_Idx_MC=-1000.;
    recoB_l_xy_sig_MC=-1000.;
    recoB_l1l2Dz_MC=-1000.;
    recoB_lKDz_MC=-1000.;
    recoB_l1l2Dr_MC;
    recoB_lKDr_MC=-1000.;
    recoB_k_opp_l_mass_MC=-1000.;
    recoB_p_assymetry_MC=-1000.;
    trig_wgt_MC=-1000.;
    BDTSCORE_1_MC=-1000.;

}

int main(int argc, char* argv[]){
    if (argc != 4) {
        std::cout << "Usage: program_name input_file_list output_file output_dir\n";
        return 1;
    }
    std::string inputFileList = argv[1];
    std::string outputFile = argv[2];
    std::string outputDir = argv[3];
    std::ifstream inputFile(inputFileList);
    std::cout<<outputFile<<std::endl;
    std::cout<<outputDir<<std::endl;
    if (!inputFile.is_open()) {
        std::cout << "Failed to open the input file list.\n";
        return 1;
    }

    TChain * chain = new TChain("Events","");
    std::vector<std::string> filenamesvector;
    std::string line;
    while (std::getline(inputFile, line)) {
        filenamesvector.push_back(line);
    }


    for(auto f: filenamesvector){
        std::cout<<f<<"reeeeeee"<<std::endl;
        TString iname(f+"/Events");
        chain->Add(iname);
    }
    //chain->Add("/eos/user/j/jodedra/fastforesttester/CMSSW_13_1_0/src/smallsample_Chunk0.root/Events");
    std::cout<<chain->GetEntries()<<std::endl;
    EventsMC t(chain);
    t.LoopMC(outputFile,outputDir);
    return 0;
}
