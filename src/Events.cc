#define Events_cxx
#include "../include/json.hpp"
#include "../include/Events.hh"
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
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <stdlib.h>
using json = nlohmann::json;

Events::Events(TTree* tree) :
  EventsBase((TTree*)tree){
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

void Events::Loop(std::string outname, std::string outdir)
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
   std::ifstream f("./jsons/2022/merged2022.json");
   std::ifstream f2("/eos/user/j/jodedra/AnalysisWork_2024/BDTScoreadder_FINAL/CMSSW_14_0_1/src/BDTscoreAdder/jsons/2023new/merged.json");

   json data2 = json::parse(f2);
   json data = json::parse(f);

   std::vector<std::string> triggers{"L1_10p5_HLT_5p0_Excl_Final", "L1_10p5_HLT_6p5_Excl_Final", "L1_11p0_HLT_6p5_Excl_Final", "L1_4p5_HLT_4p0_Excl_Final", "L1_5p0_HLT_4p0_Excl_Final", "L1_5p5_HLT_4p0_Excl_Final", "L1_5p5_HLT_6p0_Excl_Final", "L1_6p0_HLT_4p0_Excl_Final", "L1_6p5_HLT_4p5_Excl_Final", "L1_7p0_HLT_5p0_Excl_Final", "L1_7p5_HLT_5p0_Excl_Final", "L1_8p0_HLT_5p0_Excl_Final", "L1_8p5_HLT_5p0_Excl_Final", "L1_8p5_HLT_5p5_Excl_Final", "L1_9p0_HLT_6p0_Excl_Final"};
   std::vector<std::string> triggers2{"L1_10p5_HLT_6p5_Excl_final", "L1_11p0_HLT_6p5_Excl_final", "L1_5p0_HLT_4p0_Excl_final", "L1_5p5_HLT_4p0_Excl_final", "L1_6p0_HLT_4p0_Excl_final", "L1_6p5_HLT_4p5_Excl_final", "L1_7p0_HLT_5p0_Excl_final", "L1_7p5_HLT_5p0_Excl_final", "L1_8p0_HLT_5p0_Excl_final", "L1_8p5_HLT_5p5_Excl_final", "L1_9p0_HLT_6p0_Excl_final"};
   
   

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   Output(outname,outdir);
   //initialize bdt
   fastforest::FastForest bdt1;

   std::string modellocation1 = "./models/preselbdt15_10_23.txt";

   std::vector<std::string> features1{"BToKEE_l1_PFMvaID_retrained", "BToKEE_l2_PFMvaID_retrained", "BToKEE_fit_pt", "BToKEE_fit_l2_pt"};

   
   LoadBDT(bdt1,modellocation1,features1); 

   int interval = 100000;
   auto start = std::chrono::system_clock::now();

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (jentry%interval==0) { timing(nentries,jentry,start); }
        run_ = run ;
        luminosityBlock_ = luminosityBlock ;
        event_ =        event ;
        bunchCrossing_ = bunchCrossing ;
        nBToKEE_ = nBToKEE ;
        nElectron_ = nElectron ;
        nProbeTracks_ = nProbeTracks ;
        HLT_DoubleEle10_eta1p22_mMax6_ = HLT_DoubleEle10_eta1p22_mMax6 ;
        HLT_DoubleEle9p5_eta1p22_mMax6_ = HLT_DoubleEle9p5_eta1p22_mMax6 ;
        HLT_DoubleEle9_eta1p22_mMax6_ = HLT_DoubleEle9_eta1p22_mMax6 ;
        HLT_DoubleEle8p5_eta1p22_mMax6_ = HLT_DoubleEle8p5_eta1p22_mMax6 ;
        HLT_DoubleEle8_eta1p22_mMax6_ = HLT_DoubleEle8_eta1p22_mMax6 ;
        HLT_DoubleEle7p5_eta1p22_mMax6_ = HLT_DoubleEle7p5_eta1p22_mMax6 ;
        HLT_DoubleEle7_eta1p22_mMax6_ = HLT_DoubleEle7_eta1p22_mMax6 ;
        HLT_DoubleEle6p5_eta1p22_mMax6_ = HLT_DoubleEle6p5_eta1p22_mMax6 ;
        HLT_DoubleEle6_eta1p22_mMax6_ = HLT_DoubleEle6_eta1p22_mMax6 ;
        HLT_DoubleEle5p5_eta1p22_mMax6_ = HLT_DoubleEle5p5_eta1p22_mMax6 ;
        HLT_DoubleEle5_eta1p22_mMax6_ = HLT_DoubleEle5_eta1p22_mMax6 ;
        HLT_DoubleEle4p5_eta1p22_mMax6_ = HLT_DoubleEle4p5_eta1p22_mMax6 ;
        HLT_DoubleEle4_eta1p22_mMax6_ = HLT_DoubleEle4_eta1p22_mMax6 ;
        L1_DoubleEG11_er1p2_dR_Max0p6_ = L1_DoubleEG11_er1p2_dR_Max0p6 ;
        L1_DoubleEG10p5_er1p2_dR_Max0p6 = L1_DoubleEG10p5_er1p2_dR_Max0p6 ;
        L1_DoubleEG10_er1p2_dR_Max0p6_ = L1_DoubleEG10_er1p2_dR_Max0p6 ;
        L1_DoubleEG9p5_er1p2_dR_Max0p6_ = L1_DoubleEG9p5_er1p2_dR_Max0p6 ;
        L1_DoubleEG9_er1p2_dR_Max0p7_ = L1_DoubleEG9_er1p2_dR_Max0p7 ;
        L1_DoubleEG8p5_er1p2_dR_Max0p7_ = L1_DoubleEG8p5_er1p2_dR_Max0p7 ;
        L1_DoubleEG8_er1p2_dR_Max0p7_ = L1_DoubleEG8_er1p2_dR_Max0p7 ;
        L1_DoubleEG7p5_er1p2_dR_Max0p7_ = L1_DoubleEG7p5_er1p2_dR_Max0p7 ;
        L1_DoubleEG7_er1p2_dR_Max0p8_ = L1_DoubleEG7_er1p2_dR_Max0p8 ;
        L1_DoubleEG6p5_er1p2_dR_Max0p8_ = L1_DoubleEG6p5_er1p2_dR_Max0p8 ;
        L1_DoubleEG6_er1p2_dR_Max0p8_ = L1_DoubleEG6_er1p2_dR_Max0p8 ;
        L1_DoubleEG5p5_er1p2_dR_Max0p8_ = L1_DoubleEG5p5_er1p2_dR_Max0p8 ;
        L1_DoubleEG5_er1p2_dR_Max0p9_ = L1_DoubleEG5_er1p2_dR_Max0p9 ;
        L1_DoubleEG4p5_er1p2_dR_Max0p9_ = L1_DoubleEG4p5_er1p2_dR_Max0p9 ;
        L1_DoubleEG4_er1p2_dR_Max0p9_ = L1_DoubleEG4_er1p2_dR_Max0p9 ;
        nTrigObj_ = nTrigObj ;
        nOtherPV_ = nOtherPV ;
        PV_ndof_ =   PV_ndof ;
        PV_x_ =   PV_x ;
        PV_y_ =   PV_y ;
        PV_z_ =   PV_z ;
        PV_chi2_ =   PV_chi2 ;
        PV_score_ =   PV_score ;
        PV_npvs_ =  PV_npvs ;
        PV_npvsGood_ =  PV_npvsGood ;
        nSV_ = nSV ;
        nSkimBToKEE_ = nSkimBToKEE ;
        if(nSkimBToKEE_>9999){
            continue;
        }
        std::array<int,15> number = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        for(int i=0;i<triggers.size();i++){
            for (json::iterator it = data[std::string(triggers[i])].begin(); it != data[std::string(triggers[i])].end(); ++it) {
                std::string runt = it.key();
                if(runt==std::to_string(run_)){
                  for (json::iterator it2 = data[std::string(triggers[i])][runt].begin(); it2 != data[std::string(triggers[i])][runt].end(); ++it2) {
                    if(luminosityBlock_>=it2.value()[0]&&luminosityBlock_<=it2.value()[1]){
                        //std::cout<<"reeeeeeooga"<<std::endl;
                        number[i] = 1;
                    }
                  }
                }
            }
        }
        L1_4p5_HLT_4p0_ =  L1_DoubleEG4p5_er1p2_dR_Max0p9*HLT_DoubleEle4_eta1p22_mMax6*number[3]    ; 
        L1_5p0_HLT_4p0_ =  L1_DoubleEG5_er1p2_dR_Max0p9*HLT_DoubleEle4_eta1p22_mMax6*number[4]    ; 
        L1_5p5_HLT_4p0_ =  L1_DoubleEG5p5_er1p2_dR_Max0p8*HLT_DoubleEle4_eta1p22_mMax6*number[5]    ; 
        L1_5p5_HLT_6p0_ =  L1_DoubleEG5p5_er1p2_dR_Max0p8*HLT_DoubleEle6_eta1p22_mMax6*number[6]    ; 
        L1_6p0_HLT_4p0_ =  L1_DoubleEG6_er1p2_dR_Max0p8*HLT_DoubleEle4_eta1p22_mMax6*number[7]    ; 
        L1_6p5_HLT_4p5_ =  L1_DoubleEG6p5_er1p2_dR_Max0p8*HLT_DoubleEle4p5_eta1p22_mMax6*number[8]    ; 
        L1_7p0_HLT_5p0_ =  L1_DoubleEG7_er1p2_dR_Max0p8*HLT_DoubleEle5_eta1p22_mMax6*number[9]    ; 
        L1_7p5_HLT_5p0_ =  L1_DoubleEG7p5_er1p2_dR_Max0p7*HLT_DoubleEle5_eta1p22_mMax6*number[10]    ; 
        L1_8p0_HLT_5p0_ =  L1_DoubleEG8_er1p2_dR_Max0p7*HLT_DoubleEle5_eta1p22_mMax6*number[11]    ; 
        L1_8p5_HLT_5p0_ =  L1_DoubleEG8p5_er1p2_dR_Max0p7*HLT_DoubleEle5_eta1p22_mMax6*number[12]    ; 
        L1_8p5_HLT_5p5_ =  L1_DoubleEG8p5_er1p2_dR_Max0p7*HLT_DoubleEle5p5_eta1p22_mMax6*number[13]    ; 
        L1_9p0_HLT_6p0_ =  L1_DoubleEG9_er1p2_dR_Max0p7*HLT_DoubleEle6_eta1p22_mMax6*number[14]    ; 
        L1_10p5_HLT_5p0_ = L1_DoubleEG10p5_er1p2_dR_Max0p6*HLT_DoubleEle5_eta1p22_mMax6*number[0]     ;
        L1_10p5_HLT_6p5_ = L1_DoubleEG10p5_er1p2_dR_Max0p6*HLT_DoubleEle6p5_eta1p22_mMax6*number[1]     ;
        L1_11p0_HLT_6p5_ = L1_DoubleEG11_er1p2_dR_Max0p6*HLT_DoubleEle6p5_eta1p22_mMax6*number[2]     ;
        
        trigger_OR_ = false;
        if(L1_4p5_HLT_4p0_ || L1_5p0_HLT_4p0_ ||L1_5p5_HLT_4p0_ ||L1_5p5_HLT_6p0_ ||L1_6p0_HLT_4p0_ ||L1_6p5_HLT_4p5_ ||L1_7p0_HLT_5p0_ ||L1_7p5_HLT_5p0_ ||L1_8p0_HLT_5p0_ ||L1_8p5_HLT_5p0_ ||L1_8p5_HLT_5p5_ ||L1_9p0_HLT_6p0_ ||L1_10p5_HLT_5p0_||L1_10p5_HLT_6p5_||L1_11p0_HLT_6p5_){
            trigger_OR_ = true;
        }
        

//        // 2023 trigger 
//        std::array<int,11> number = {0,0,0,0,0,0,0,0,0,0,0};
//        for(int i=0;i<triggers2.size();i++){
//            for (json::iterator it = data2[std::string(triggers2[i])].begin(); it != data2[std::string(triggers2[i])].end(); ++it) {
//                std::string runt = it.key();
//                if(runt==std::to_string(run_)){
//                  for (json::iterator it2 = data2[std::string(triggers2[i])][runt].begin(); it2 != data2[std::string(triggers2[i])][runt].end(); ++it2) {
//                    if(luminosityBlock_>=it2.value()[0]&&luminosityBlock_<=it2.value()[1]){
//                        //std::cout<<"reeeeeeooga"<<std::endl;
//                        number[i] = 1;
//                    }
//                  }
//                }
//            }
//        }
//
//        L1_4p5_HLT_4p0_ =  L1_DoubleEG4p5_er1p2_dR_Max0p9*HLT_DoubleEle4_eta1p22_mMax6*0    ; 
//        L1_5p0_HLT_4p0_ =  L1_DoubleEG5_er1p2_dR_Max0p9*HLT_DoubleEle4_eta1p22_mMax6*number[2]    ; 
//        L1_5p5_HLT_4p0_ =  L1_DoubleEG5p5_er1p2_dR_Max0p8*HLT_DoubleEle4_eta1p22_mMax6*number[3]    ; 
//        L1_5p5_HLT_6p0_ =  L1_DoubleEG5p5_er1p2_dR_Max0p8*HLT_DoubleEle6_eta1p22_mMax6*0    ; 
//        L1_6p0_HLT_4p0_ =  L1_DoubleEG6_er1p2_dR_Max0p8*HLT_DoubleEle4_eta1p22_mMax6*number[4]    ; 
//        L1_6p5_HLT_4p5_ =  L1_DoubleEG6p5_er1p2_dR_Max0p8*HLT_DoubleEle4p5_eta1p22_mMax6*number[5]    ; 
//        L1_7p0_HLT_5p0_ =  L1_DoubleEG7_er1p2_dR_Max0p8*HLT_DoubleEle5_eta1p22_mMax6*number[6]    ; 
//        L1_7p5_HLT_5p0_ =  L1_DoubleEG7p5_er1p2_dR_Max0p7*HLT_DoubleEle5_eta1p22_mMax6*number[7]    ; 
//        L1_8p0_HLT_5p0_ =  L1_DoubleEG8_er1p2_dR_Max0p7*HLT_DoubleEle5_eta1p22_mMax6*number[8]    ; 
//        L1_8p5_HLT_5p0_ =  L1_DoubleEG8p5_er1p2_dR_Max0p7*HLT_DoubleEle5_eta1p22_mMax6*0    ; 
//        L1_8p5_HLT_5p5_ =  L1_DoubleEG8p5_er1p2_dR_Max0p7*HLT_DoubleEle5p5_eta1p22_mMax6*number[9]    ; 
//        L1_9p0_HLT_6p0_ =  L1_DoubleEG9_er1p2_dR_Max0p7*HLT_DoubleEle6_eta1p22_mMax6*number[10]    ; 
//        L1_10p5_HLT_5p0_ = L1_DoubleEG10p5_er1p2_dR_Max0p6*HLT_DoubleEle5_eta1p22_mMax6*0     ;
//        L1_10p5_HLT_6p5_ = L1_DoubleEG10p5_er1p2_dR_Max0p6*HLT_DoubleEle6p5_eta1p22_mMax6*number[0]     ;
//        L1_11p0_HLT_6p5_ = L1_DoubleEG11_er1p2_dR_Max0p6*HLT_DoubleEle6p5_eta1p22_mMax6*number[1]     ;




//        L1_4p5_HLT_4p0_ =  L1_DoubleEG4p5_er1p2_dR_Max0p9*HLT_DoubleEle4_eta1p22_mMax6;
//        L1_5p0_HLT_4p0_ =  L1_DoubleEG5_er1p2_dR_Max0p9*HLT_DoubleEle4_eta1p22_mMax6;
//        L1_5p5_HLT_4p0_ =  L1_DoubleEG5p5_er1p2_dR_Max0p8*HLT_DoubleEle4_eta1p22_mMax6;
//        L1_5p5_HLT_6p0_ =  L1_DoubleEG5p5_er1p2_dR_Max0p8*HLT_DoubleEle6_eta1p22_mMax6;
//        L1_6p0_HLT_4p0_ =  L1_DoubleEG6_er1p2_dR_Max0p8*HLT_DoubleEle4_eta1p22_mMax6;
//        L1_6p5_HLT_4p5_ =  L1_DoubleEG6p5_er1p2_dR_Max0p8*HLT_DoubleEle4p5_eta1p22_mMax6;
//        L1_7p0_HLT_5p0_ =  L1_DoubleEG7_er1p2_dR_Max0p8*HLT_DoubleEle5_eta1p22_mMax6;
//        L1_7p5_HLT_5p0_ =  L1_DoubleEG7p5_er1p2_dR_Max0p7*HLT_DoubleEle5_eta1p22_mMax6;
//        L1_8p0_HLT_5p0_ =  L1_DoubleEG8_er1p2_dR_Max0p7*HLT_DoubleEle5_eta1p22_mMax6;
//        L1_8p5_HLT_5p0_ =  L1_DoubleEG8p5_er1p2_dR_Max0p7*HLT_DoubleEle5_eta1p22_mMax6;
//        L1_8p5_HLT_5p5_ =  L1_DoubleEG8p5_er1p2_dR_Max0p7*HLT_DoubleEle5p5_eta1p22_mMax6;
//        L1_9p0_HLT_6p0_ =  L1_DoubleEG9_er1p2_dR_Max0p7*HLT_DoubleEle6_eta1p22_mMax6;
//        L1_10p5_HLT_5p0_ = L1_DoubleEG10p5_er1p2_dR_Max0p6*HLT_DoubleEle5_eta1p22_mMax6;
//        L1_10p5_HLT_6p5_ = L1_DoubleEG10p5_er1p2_dR_Max0p6*HLT_DoubleEle6p5_eta1p22_mMax6;
//        L1_11p0_HLT_6p5_ = L1_DoubleEG11_er1p2_dR_Max0p6*HLT_DoubleEle6p5_eta1p22_mMax6;

        //trigger_OR_ = false;
        //if( L1_5p0_HLT_4p0_ ||L1_5p5_HLT_4p0_||L1_6p0_HLT_4p0_ ||L1_6p5_HLT_4p5_ ||L1_7p0_HLT_5p0_ ||L1_7p5_HLT_5p0_ ||L1_8p0_HLT_5p0_||L1_8p5_HLT_5p5_ ||L1_9p0_HLT_6p0_||L1_10p5_HLT_6p5_||L1_11p0_HLT_6p5_){
        //    trigger_OR_ = true;
       //}

      //std::cout<<run<<std::endl;
      for(int i=0;i<nSkimBToKEE_;i++){
         BToKEE_fit_pt_ = SkimBToKEE_fit_pt[i];
         BToKEE_fit_eta_ = SkimBToKEE_fit_eta[i];
         BToKEE_fit_phi_ = SkimBToKEE_fit_phi[i];
         BToKEE_D0_mass_LepToK_KToPi_ = SkimBToKEE_D0_mass_LepToK_KToPi[i];
         BToKEE_D0_mass_LepToPi_KToK_ = SkimBToKEE_D0_mass_LepToPi_KToK[i];
         BToKEE_fit_mass_ = SkimBToKEE_fit_mass[i];
         BToKEE_l_xy_ = SkimBToKEE_l_xy[i];
         BToKEE_l_xy_unc_ = SkimBToKEE_l_xy_unc[i];
         BToKEE_fit_cos2D_ = SkimBToKEE_fit_cos2D[i];
         BToKEE_svprob_ = SkimBToKEE_svprob[i];
         BToKEE_fit_massErr_ = SkimBToKEE_fit_massErr[i];
         BToKEE_b_iso04_ = SkimBToKEE_b_iso04[i];
         BToKEE_mll_fullfit_ = SkimBToKEE_mll_fullfit[i];
         BToKEE_vtx_x_ = SkimBToKEE_vtx_x[i];
         BToKEE_vtx_y_ = SkimBToKEE_vtx_y[i];
         BToKEE_vtx_z_ = SkimBToKEE_vtx_z[i];
         BToKEE_l1Idx_ = SkimBToKEE_l1Idx[i];
         BToKEE_l2Idx_ = SkimBToKEE_l2Idx[i];
         BToKEE_kIdx_ = SkimBToKEE_kIdx[i];
         BToKEE_fit_k_pt_ = SkimBToKEE_fit_k_pt[i];
         BToKEE_fit_k_eta_ = SkimBToKEE_fit_k_eta[i];
         BToKEE_fit_k_phi_ = SkimBToKEE_fit_k_phi[i];
         BToKEE_fit_l1_pt_ = SkimBToKEE_fit_l1_pt[i];
         BToKEE_fit_l1_eta_ = SkimBToKEE_fit_l1_eta[i];
         BToKEE_fit_l1_phi_ = SkimBToKEE_fit_l1_phi[i];
         BToKEE_fit_l2_pt_ = SkimBToKEE_fit_l2_pt[i];
         BToKEE_fit_l2_eta_ = SkimBToKEE_fit_l2_eta[i];
         BToKEE_fit_l2_phi_ = SkimBToKEE_fit_l2_phi[i];
         BToKEE_l1_iso04_ = SkimBToKEE_l1_iso04[i];
         BToKEE_l2_iso04_ = SkimBToKEE_l2_iso04[i];
         BToKEE_l1_isPF_ = SkimBToKEE_l1_isPF[i];
         BToKEE_l2_isPF_ = SkimBToKEE_l2_isPF[i];
         BToKEE_k_iso04_ = SkimBToKEE_k_iso04[i];
         BToKEE_l1_isPFoverlap_ = SkimBToKEE_l1_isPFoverlap[i];
         BToKEE_l2_isPFoverlap_ = SkimBToKEE_l2_isPFoverlap[i];
         BToKEE_l1_LooseId_ = SkimBToKEE_l1_LooseId[i];
         BToKEE_l2_LooseId_ = SkimBToKEE_l2_LooseId[i];
         BToKEE_l1_MediumId_ = SkimBToKEE_l1_MediumId[i];
         BToKEE_l2_MediumId_ = SkimBToKEE_l2_MediumId[i];
         BToKEE_l1_TightId_ = SkimBToKEE_l1_TightId[i];
         BToKEE_l2_TightId_ = SkimBToKEE_l2_TightId[i];
         BToKEE_l1_ConvVeto_ = SkimBToKEE_l1_ConvVeto[i];
         BToKEE_l2_ConvVeto_ = SkimBToKEE_l2_ConvVeto[i];
         BToKEE_l1_PFMvaID_Fall17_ = SkimBToKEE_l1_PFMvaID_Fall17[i];
         BToKEE_l2_PFMvaID_Fall17_ = SkimBToKEE_l2_PFMvaID_Fall17[i];
         BToKEE_l1_PFMvaID_retrained_ = SkimBToKEE_l1_PFMvaID_retrained[i];
         BToKEE_l2_PFMvaID_retrained_ = SkimBToKEE_l2_PFMvaID_retrained[i];
         BToKEE_l1_iso04_dca_ = SkimBToKEE_l1_iso04_dca[i];
         BToKEE_l2_iso04_dca_ = SkimBToKEE_l2_iso04_dca[i];
         BToKEE_b_iso04_dca_ = SkimBToKEE_b_iso04_dca[i];
         BToKEE_k_iso04_dca_ = SkimBToKEE_k_iso04_dca[i];
         BToKEE_k_svip3d_ = SkimBToKEE_k_svip3d[i];
         BToKEE_k_svip3d_err_ = SkimBToKEE_k_svip3d_err[i];
         BToKEE_l1_n_isotrk_dca_ = SkimBToKEE_l1_n_isotrk_dca[i];
         BToKEE_l2_n_isotrk_dca_ = SkimBToKEE_l2_n_isotrk_dca[i];
         BToKEE_k_n_isotrk_dca_ = SkimBToKEE_k_n_isotrk_dca[i];
         BToKEE_l1_vx_ = SkimBToKEE_l1_vx[i];
         BToKEE_l1_vy_ = SkimBToKEE_l1_vy[i];
         BToKEE_l1_vz_ = SkimBToKEE_l1_vz[i];
         BToKEE_l1_charge_ = SkimBToKEE_l1_charge[i];
         BToKEE_l2_vx_ = SkimBToKEE_l2_vx[i];
         BToKEE_l2_vy_ = SkimBToKEE_l2_vy[i];
         BToKEE_l2_vz_ = SkimBToKEE_l2_vz[i];
         BToKEE_l2_charge_ = SkimBToKEE_l2_charge[i];
         BToKEE_k_vx_ = SkimBToKEE_k_vx[i];
         BToKEE_k_vy_ = SkimBToKEE_k_vy[i];
         BToKEE_k_vz_ = SkimBToKEE_k_vz[i];
         BToKEE_k_dca_sig_ = SkimBToKEE_k_dca_sig[i];
         BToKEE_k_dz_ = SkimBToKEE_k_dz[i];
         BToKEE_kMu_matched_ = SkimBToKEE_kMu_matched[i];
         BToKEE_k_charge_ = SkimBToKEE_k_charge[i];
         BToKEE_l_xy_sig_ = SkimBToKEE_l_xy_sig[i];
         BToKEE_l1l2Dz_ = SkimBToKEE_l1l2Dz[i];
         BToKEE_lKDz_ = SkimBToKEE_lKDz[i];
         BToKEE_l1l2Dr_ = SkimBToKEE_l1l2Dr[i];
         BToKEE_lKDr_ = SkimBToKEE_lKDr[i];
         BToKEE_kl_massKPi_ = SkimBToKEE_kl_massKPi[i];
         BToKEE_p_assymetry_ = SkimBToKEE_p_assymetry[i];
         float BToKEE_k_svip3d_sig_ = BToKEE_k_svip3d_/BToKEE_k_svip3d_err_;
         float BToKEE_fit_pt_over_mass_= BToKEE_fit_pt_/BToKEE_fit_mass_;
         float BToKEE_fit_l1_pt_over_mass_ = BToKEE_fit_l1_pt_/BToKEE_fit_mass_;
         float BToKEE_fit_l2_pt_over_mass_ = BToKEE_fit_l2_pt_/BToKEE_fit_mass_;
         float BToKEE_fit_k_pt_over_mass_ = BToKEE_fit_k_pt_/BToKEE_fit_mass_;
         


         std::vector<float> input1{BToKEE_l1_PFMvaID_retrained_,BToKEE_l2_PFMvaID_retrained_,BToKEE_fit_pt_,BToKEE_fit_l2_pt_};



         //BDTSCORE_1 = bdt1(input1.data());
         BDTSCORE_1 = bdt1(input1.data());
//         if (BDTSCORE_1<-3.4003663){
//            initVars();
//            goto end;
//         }
         outTree_->Fill();
//         end:;
  
         //initVars();
   
      }
      initVars();


      
      //std::cout<<HLT_DoubleEle10_eta1p22_mMax6_<<std::endl;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
//      if(jentry>20000){
//        break;
//      }
   }
   outFile_->Write();
   outFile_->Close();
}
void Events::Output(std::string outname, std::string outdir) {
   TString outputfilename(std::string(outdir)+"/"+std::string(outname)+"_.root");
   outFile_ = new TFile(outputfilename,"RECREATE");
   outTree_ = new TTree("Events","Events");
   outTree_->Branch("run", &run_);
   outTree_->Branch("luminosityBlock", &luminosityBlock_);;
   outTree_->Branch("event", &event_);;
   outTree_->Branch("bunchCrossing", &bunchCrossing_);;
   outTree_->Branch("nBToKEE", &nBToKEE_);;
   outTree_->Branch("nElectron", &nElectron_);;
   outTree_->Branch("nProbeTracks", &nProbeTracks_);;
   outTree_->Branch("HLT_DoubleEle10_eta1p22_mMax6", &HLT_DoubleEle10_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle9p5_eta1p22_mMax6", &HLT_DoubleEle9p5_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle9_eta1p22_mMax6", &HLT_DoubleEle9_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle8p5_eta1p22_mMax6", &HLT_DoubleEle8p5_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle8_eta1p22_mMax6", &HLT_DoubleEle8_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle7p5_eta1p22_mMax6", &HLT_DoubleEle7p5_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle7_eta1p22_mMax6", &HLT_DoubleEle7_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle6p5_eta1p22_mMax6", &HLT_DoubleEle6p5_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle6_eta1p22_mMax6", &HLT_DoubleEle6_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle5p5_eta1p22_mMax6", &HLT_DoubleEle5p5_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle5_eta1p22_mMax6", &HLT_DoubleEle5_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle4p5_eta1p22_mMax6", &HLT_DoubleEle4p5_eta1p22_mMax6_);
   outTree_->Branch("HLT_DoubleEle4_eta1p22_mMax6", &HLT_DoubleEle4_eta1p22_mMax6_);
   outTree_->Branch("L1_DoubleEG11_er1p2_dR_Max0p6", &L1_DoubleEG11_er1p2_dR_Max0p6_);
   outTree_->Branch("L1_DoubleEG10p5_er1p2_dR_Max0p6", &L1_DoubleEG10p5_er1p2_dR_Max0p6);
   outTree_->Branch("L1_DoubleEG10_er1p2_dR_Max0p6", &L1_DoubleEG10_er1p2_dR_Max0p6_);
   outTree_->Branch("L1_DoubleEG9p5_er1p2_dR_Max0p6", &L1_DoubleEG9p5_er1p2_dR_Max0p6_);
   outTree_->Branch("L1_DoubleEG9_er1p2_dR_Max0p7", &L1_DoubleEG9_er1p2_dR_Max0p7_);
   outTree_->Branch("L1_DoubleEG8p5_er1p2_dR_Max0p7", &L1_DoubleEG8p5_er1p2_dR_Max0p7_);
   outTree_->Branch("L1_DoubleEG8_er1p2_dR_Max0p7", &L1_DoubleEG8_er1p2_dR_Max0p7_);
   outTree_->Branch("L1_DoubleEG7p5_er1p2_dR_Max0p7", &L1_DoubleEG7p5_er1p2_dR_Max0p7_);
   outTree_->Branch("L1_DoubleEG7_er1p2_dR_Max0p8", &L1_DoubleEG7_er1p2_dR_Max0p8_);
   outTree_->Branch("L1_DoubleEG6p5_er1p2_dR_Max0p8", &L1_DoubleEG6p5_er1p2_dR_Max0p8_);
   outTree_->Branch("L1_DoubleEG6_er1p2_dR_Max0p8", &L1_DoubleEG6_er1p2_dR_Max0p8_);
   outTree_->Branch("L1_DoubleEG5p5_er1p2_dR_Max0p8", &L1_DoubleEG5p5_er1p2_dR_Max0p8_);
   outTree_->Branch("L1_DoubleEG5_er1p2_dR_Max0p9", &L1_DoubleEG5_er1p2_dR_Max0p9_);
   outTree_->Branch("L1_DoubleEG4p5_er1p2_dR_Max0p9", &L1_DoubleEG4p5_er1p2_dR_Max0p9_);
   outTree_->Branch("L1_DoubleEG4_er1p2_dR_Max0p9", &L1_DoubleEG4_er1p2_dR_Max0p9_);

   outTree_->Branch("L1_4p5_HLT_4p0",&L1_4p5_HLT_4p0_);
   outTree_->Branch("L1_5p0_HLT_4p0",&L1_5p0_HLT_4p0_);
   outTree_->Branch("L1_5p5_HLT_4p0",&L1_5p5_HLT_4p0_);
   outTree_->Branch("L1_5p5_HLT_6p0",&L1_5p5_HLT_6p0_);
   outTree_->Branch("L1_6p0_HLT_4p0",&L1_6p0_HLT_4p0_);
   outTree_->Branch("L1_6p5_HLT_4p5",&L1_6p5_HLT_4p5_);
   outTree_->Branch("L1_7p0_HLT_5p0",&L1_7p0_HLT_5p0_);
   outTree_->Branch("L1_7p5_HLT_5p0",&L1_7p5_HLT_5p0_);
   outTree_->Branch("L1_8p0_HLT_5p0",&L1_8p0_HLT_5p0_);
   outTree_->Branch("L1_8p5_HLT_5p0",&L1_8p5_HLT_5p0_);
   outTree_->Branch("L1_8p5_HLT_5p5",&L1_8p5_HLT_5p5_);
   outTree_->Branch("L1_9p0_HLT_6p0",&L1_9p0_HLT_6p0_);
   outTree_->Branch("L1_10p5_HLT_5p0",&L1_10p5_HLT_5p0_);
   outTree_->Branch("L1_10p5_HLT_6p5",&L1_10p5_HLT_6p5_);
   outTree_->Branch("L1_11p0_HLT_6p5",&L1_11p0_HLT_6p5_);
   outTree_->Branch("trigger_OR",&trigger_OR_);

   outTree_->Branch("nTrigObj", &nTrigObj_);
   outTree_->Branch("nOtherPV", &nOtherPV_);
   outTree_->Branch("PV_ndof", &PV_ndof_);
   outTree_->Branch("PV_x", &PV_x_);
   outTree_->Branch("PV_y", &PV_y_);
   outTree_->Branch("PV_z", &PV_z_);
   outTree_->Branch("PV_chi2", &PV_chi2_);
   outTree_->Branch("PV_score", &PV_score_);
   outTree_->Branch("PV_npvs", &PV_npvs_);
   outTree_->Branch("PV_npvsGood", &PV_npvsGood_);
   outTree_->Branch("nSV", &nSV_);
   outTree_->Branch("nSkimBToKEE", &nSkimBToKEE_);



   outTree_->Branch("BToKEE_fit_pt", &BToKEE_fit_pt_);
   outTree_->Branch("BToKEE_fit_eta", &BToKEE_fit_eta_);
   outTree_->Branch("BToKEE_fit_phi", &BToKEE_fit_phi_);
   outTree_->Branch("BToKEE_D0_mass_LepToK_KToPi", &BToKEE_D0_mass_LepToK_KToPi_);
   outTree_->Branch("BToKEE_D0_mass_LepToPi_KToK", &BToKEE_D0_mass_LepToPi_KToK_);
   outTree_->Branch("BToKEE_fit_mass", &BToKEE_fit_mass_);
   outTree_->Branch("BToKEE_l_xy", &BToKEE_l_xy_);
   outTree_->Branch("BToKEE_l_xy_unc", &BToKEE_l_xy_unc_);
   outTree_->Branch("BToKEE_fit_cos2D", &BToKEE_fit_cos2D_);
   outTree_->Branch("BToKEE_svprob", &BToKEE_svprob_);
   outTree_->Branch("BToKEE_fit_massErr", &BToKEE_fit_massErr_);
   outTree_->Branch("BToKEE_b_iso04", &BToKEE_b_iso04_);
   outTree_->Branch("BToKEE_mll_fullfit", &BToKEE_mll_fullfit_);
   outTree_->Branch("BToKEE_vtx_x", &BToKEE_vtx_x_);
   outTree_->Branch("BToKEE_vtx_y", &BToKEE_vtx_y_);
   outTree_->Branch("BToKEE_vtx_z", &BToKEE_vtx_z_);
   outTree_->Branch("BToKEE_l1Idx", &BToKEE_l1Idx_);
   outTree_->Branch("BToKEE_l2Idx", &BToKEE_l2Idx_);
   outTree_->Branch("BToKEE_kIdx", &BToKEE_kIdx_);
   outTree_->Branch("BToKEE_fit_k_pt", &BToKEE_fit_k_pt_);
   outTree_->Branch("BToKEE_fit_k_eta", &BToKEE_fit_k_eta_);
   outTree_->Branch("BToKEE_fit_k_phi", &BToKEE_fit_k_phi_);
   outTree_->Branch("BToKEE_fit_l1_pt", &BToKEE_fit_l1_pt_);
   outTree_->Branch("BToKEE_fit_l1_eta", &BToKEE_fit_l1_eta_);
   outTree_->Branch("BToKEE_fit_l1_phi", &BToKEE_fit_l1_phi_);
   outTree_->Branch("BToKEE_fit_l2_pt", &BToKEE_fit_l2_pt_);
   outTree_->Branch("BToKEE_fit_l2_eta", &BToKEE_fit_l2_eta_);
   outTree_->Branch("BToKEE_fit_l2_phi", &BToKEE_fit_l2_phi_);
   outTree_->Branch("BToKEE_l1_iso04", &BToKEE_l1_iso04_);
   outTree_->Branch("BToKEE_l2_iso04", &BToKEE_l2_iso04_);
   outTree_->Branch("BToKEE_l1_isPF", &BToKEE_l1_isPF_);
   outTree_->Branch("BToKEE_l2_isPF", &BToKEE_l2_isPF_);
   outTree_->Branch("BToKEE_k_iso04", &BToKEE_k_iso04_);
   outTree_->Branch("BToKEE_l1_isPFoverlap", &BToKEE_l1_isPFoverlap_);
   outTree_->Branch("BToKEE_l2_isPFoverlap", &BToKEE_l2_isPFoverlap_);
   outTree_->Branch("BToKEE_l1_LooseId", &BToKEE_l1_LooseId_);
   outTree_->Branch("BToKEE_l2_LooseId", &BToKEE_l2_LooseId_);
   outTree_->Branch("BToKEE_l1_MediumId", &BToKEE_l1_MediumId_);
   outTree_->Branch("BToKEE_l2_MediumId", &BToKEE_l2_MediumId_);
   outTree_->Branch("BToKEE_l1_TightId", &BToKEE_l1_TightId_);
   outTree_->Branch("BToKEE_l2_TightId", &BToKEE_l2_TightId_);
   outTree_->Branch("BToKEE_l1_ConvVeto", &BToKEE_l1_ConvVeto_);
   outTree_->Branch("BToKEE_l2_ConvVeto", &BToKEE_l2_ConvVeto_);
   outTree_->Branch("BToKEE_l1_PFMvaID_Fall17", &BToKEE_l1_PFMvaID_Fall17_);
   outTree_->Branch("BToKEE_l2_PFMvaID_Fall17", &BToKEE_l2_PFMvaID_Fall17_);
   outTree_->Branch("BToKEE_l1_PFMvaID_retrained", &BToKEE_l1_PFMvaID_retrained_);
   outTree_->Branch("BToKEE_l2_PFMvaID_retrained", &BToKEE_l2_PFMvaID_retrained_);
   outTree_->Branch("BToKEE_l1_iso04_dca", &BToKEE_l1_iso04_dca_);
   outTree_->Branch("BToKEE_l2_iso04_dca", &BToKEE_l2_iso04_dca_);
   outTree_->Branch("BToKEE_b_iso04_dca", &BToKEE_b_iso04_dca_);
   outTree_->Branch("BToKEE_k_iso04_dca", &BToKEE_k_iso04_dca_);
   outTree_->Branch("BToKEE_k_svip3d", &BToKEE_k_svip3d_);
   outTree_->Branch("BToKEE_k_svip3d_err", &BToKEE_k_svip3d_err_);
   outTree_->Branch("BToKEE_l1_n_isotrk_dca", &BToKEE_l1_n_isotrk_dca_);
   outTree_->Branch("BToKEE_l2_n_isotrk_dca", &BToKEE_l2_n_isotrk_dca_);
   outTree_->Branch("BToKEE_k_n_isotrk_dca", &BToKEE_k_n_isotrk_dca_);
   outTree_->Branch("BToKEE_l1_vx", &BToKEE_l1_vx_);
   outTree_->Branch("BToKEE_l1_vy", &BToKEE_l1_vy_);
   outTree_->Branch("BToKEE_l1_vz", &BToKEE_l1_vz_);
   outTree_->Branch("BToKEE_l1_charge", &BToKEE_l1_charge_);
   outTree_->Branch("BToKEE_l2_vx", &BToKEE_l2_vx_);
   outTree_->Branch("BToKEE_l2_vy", &BToKEE_l2_vy_);
   outTree_->Branch("BToKEE_l2_vz", &BToKEE_l2_vz_);
   outTree_->Branch("BToKEE_l2_charge", &BToKEE_l2_charge_);
   outTree_->Branch("BToKEE_k_vx", &BToKEE_k_vx_);
   outTree_->Branch("BToKEE_k_vy", &BToKEE_k_vy_);
   outTree_->Branch("BToKEE_k_vz", &BToKEE_k_vz_);
   outTree_->Branch("BToKEE_k_dca_sig", &BToKEE_k_dca_sig_);
   outTree_->Branch("BToKEE_k_dz", &BToKEE_k_dz_);
   outTree_->Branch("BToKEE_kMu_matched", &BToKEE_kMu_matched_);
   outTree_->Branch("BToKEE_k_charge", &BToKEE_k_charge_);
   outTree_->Branch("BToKEE_l_xy_sig", &BToKEE_l_xy_sig_);
   outTree_->Branch("BToKEE_l1l2Dz", &BToKEE_l1l2Dz_);
   outTree_->Branch("BToKEE_lKDz", &BToKEE_lKDz_);
   outTree_->Branch("BToKEE_l1l2Dr", &BToKEE_l1l2Dr_);
   outTree_->Branch("BToKEE_lKDr", &BToKEE_lKDr_);
   outTree_->Branch("BToKEE_kl_massKPi", &BToKEE_kl_massKPi_);
   outTree_->Branch("BToKEE_p_assymetry", &BToKEE_p_assymetry_);
   outTree_->Branch("Presel_BDT", &BDTSCORE_1);


}
void Events::initVars() {

    run_ = -1000;
    luminosityBlock_ = -1000;
    event_ = -1000;
    bunchCrossing_ = -1000;
    nBToKEE_ = -1000;
    nElectron_ = -1000;
    nProbeTracks_ = -1000;
    HLT_DoubleEle10_eta1p22_mMax6_ = false;
    HLT_DoubleEle9p5_eta1p22_mMax6_ = false;
    HLT_DoubleEle9_eta1p22_mMax6_ = false;
    HLT_DoubleEle8p5_eta1p22_mMax6_ = false;
    HLT_DoubleEle8_eta1p22_mMax6_ = false;
    HLT_DoubleEle7p5_eta1p22_mMax6_ = false;
    HLT_DoubleEle7_eta1p22_mMax6_ = false;
    HLT_DoubleEle6p5_eta1p22_mMax6_ = false;
    HLT_DoubleEle6_eta1p22_mMax6_ = false;
    HLT_DoubleEle5p5_eta1p22_mMax6_ = false;
    HLT_DoubleEle5_eta1p22_mMax6_ = false;
    HLT_DoubleEle4p5_eta1p22_mMax6_ = false;
    HLT_DoubleEle4_eta1p22_mMax6_ = false;
    L1_DoubleEG11_er1p2_dR_Max0p6_ = false;
    L1_DoubleEG10p5_er1p2_dR_Max0p6_ = false;
    L1_DoubleEG10_er1p2_dR_Max0p6_ = false;
    L1_DoubleEG9p5_er1p2_dR_Max0p6_ = false;
    L1_DoubleEG9_er1p2_dR_Max0p7_ = false;
    L1_DoubleEG8p5_er1p2_dR_Max0p7_ = false;
    L1_DoubleEG8_er1p2_dR_Max0p7_ = false;
    L1_DoubleEG7p5_er1p2_dR_Max0p7_ = false;
    L1_DoubleEG7_er1p2_dR_Max0p8_ = false;
    L1_DoubleEG6p5_er1p2_dR_Max0p8_ = false;
    L1_DoubleEG6_er1p2_dR_Max0p8_ = false;
    L1_DoubleEG5p5_er1p2_dR_Max0p8_ = false;
    L1_DoubleEG5_er1p2_dR_Max0p9_ = false;
    L1_DoubleEG4p5_er1p2_dR_Max0p9_ = false;
    L1_DoubleEG4_er1p2_dR_Max0p9_ = false;



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
    L1_10p5_HLT_5p0_ = false;
    L1_10p5_HLT_6p5_ = false;
    L1_11p0_HLT_6p5_ = false;
    trigger_OR_ = false;

    nTrigObj_ = -1000;
    nOtherPV_ = -1000;
    PV_ndof_ = -1000;
    PV_x_ = -1000;
    PV_y_ = -1000;
    PV_z_ = -1000;
    PV_chi2_ = -1000;
    PV_score_ = -1000;
    PV_npvs_ = -1000;
    PV_npvsGood_ = -1000;
    nSV_ = -1000;
    nSkimBToKEE_ = -1000;
    BToKEE_fit_pt_ = -1000.;
    BToKEE_fit_eta_ = -1000.;
    BToKEE_fit_phi_ = -1000.;
    BToKEE_D0_mass_LepToK_KToPi_ = -1000.;
    BToKEE_D0_mass_LepToPi_KToK_ = -1000.;
    BToKEE_fit_mass_ = -1000.;
    BToKEE_l_xy_ = -1000.;
    BToKEE_l_xy_unc_ = -1000.;
    BToKEE_fit_cos2D_ = -1000.;
    BToKEE_svprob_ = -1000.;
    BToKEE_fit_massErr_ = -1000.;
    BToKEE_b_iso04_ = -1000.;
    BToKEE_mll_fullfit_ = -1000.;
    BToKEE_vtx_x_ = -1000.;
    BToKEE_vtx_y_ = -1000.;
    BToKEE_vtx_z_ = -1000.;
    BToKEE_l1Idx_ = -1000.;
    BToKEE_l2Idx_ = -1000.;
    BToKEE_kIdx_ = -1000.;
    BToKEE_fit_k_pt_ = -1000.;
    BToKEE_fit_k_eta_ = -1000.;
    BToKEE_fit_k_phi_ = -1000.;
    BToKEE_fit_l1_pt_ = -1000.;
    BToKEE_fit_l1_eta_ = -1000.;
    BToKEE_fit_l1_phi_ = -1000.;
    BToKEE_fit_l2_pt_ = -1000.;
    BToKEE_fit_l2_eta_ = -1000.;
    BToKEE_fit_l2_phi_ = -1000.;
    BToKEE_l1_iso04_ = -1000.;
    BToKEE_l2_iso04_ = -1000.;
    BToKEE_l1_isPF_ = -1000.;
    BToKEE_l2_isPF_ = -1000.;
    BToKEE_k_iso04_ = -1000.;
    BToKEE_l1_isPFoverlap_ = -1000.;
    BToKEE_l2_isPFoverlap_ = -1000.;
    BToKEE_l1_LooseId_ = -1000.;
    BToKEE_l2_LooseId_ = -1000.;
    BToKEE_l1_MediumId_ = -1000.;
    BToKEE_l2_MediumId_ = -1000.;
    BToKEE_l1_TightId_ = -1000.;
    BToKEE_l2_TightId_ = -1000.;
    BToKEE_l1_ConvVeto_ = -1000.;
    BToKEE_l2_ConvVeto_ = -1000.;
    BToKEE_l1_PFMvaID_Fall17_ = -1000.;
    BToKEE_l2_PFMvaID_Fall17_ = -1000.;
    BToKEE_l1_PFMvaID_retrained_ = -1000.;
    BToKEE_l2_PFMvaID_retrained_ = -1000.;
    BToKEE_l1_iso04_dca_ = -1000.;
    BToKEE_l2_iso04_dca_ = -1000.;
    BToKEE_b_iso04_dca_ = -1000.;
    BToKEE_k_iso04_dca_ = -1000.;
    BToKEE_k_svip3d_ = -1000.;
    BToKEE_k_svip3d_err_ = -1000.;
    BToKEE_l1_n_isotrk_dca_ = -1000.;
    BToKEE_l2_n_isotrk_dca_ = -1000.;
    BToKEE_k_n_isotrk_dca_ = -1000.;
    BToKEE_l1_vx_ = -1000.;
    BToKEE_l1_vy_ = -1000.;
    BToKEE_l1_vz_ = -1000.;
    BToKEE_l1_charge_ = -1000.;
    BToKEE_l2_vx_ = -1000.;
    BToKEE_l2_vy_ = -1000.;
    BToKEE_l2_vz_ = -1000.;
    BToKEE_l2_charge_ = -1000.;
    BToKEE_k_vx_ = -1000.;
    BToKEE_k_vy_ = -1000.;
    BToKEE_k_vz_ = -1000.;
    BToKEE_k_dca_sig_ = -1000.;
    BToKEE_k_dz_ = -1000.;
    BToKEE_kMu_matched_ = -1000.;
    BToKEE_k_charge_ = -1000.;
    BToKEE_l_xy_sig_ = -1000.;
    BToKEE_l1l2Dz_ = -1000.;
    BToKEE_lKDz_ = -1000.;
    BToKEE_l1l2Dr_ = -1000.;
    BToKEE_lKDr_ = -1000.;
    BToKEE_kl_massKPi_ = -1000.;
    BToKEE_p_assymetry_ = -1000.;             
    BDTSCORE_1 = -1000.; 
    BDTSCORE_2 = -1000.; 

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
    Events t(chain);
    t.Loop(outputFile,outputDir);
    std::cout<<"ended"<<std::endl;
    return 0;
}
