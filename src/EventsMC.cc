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


float FONLLweightRun3(float ptB){
  if (ptB<1) return 1.15515;
  else if(ptB<2) return 1.18534;
  else if(ptB<3) return 1.16911;
  else if(ptB<4) return 1.14175;
  else if(ptB<5) return 1.11175;
  else if(ptB<6) return 1.01419;
  else if(ptB<7) return 0.907751;
  else if(ptB<8) return 0.817504;
  else if(ptB<9) return 0.78137;
  else if(ptB<10) return 0.738612;
  else if(ptB<11) return 0.732303;
  else if(ptB<12) return 0.73074;
  else if(ptB<13) return 0.740836;
  else if(ptB<14) return 0.750178;
  else if(ptB<15) return 0.758338;
  else if(ptB<16) return 0.763555;
  else if(ptB<17) return 0.816048;
  else if(ptB<18) return 0.80948;
  else if(ptB<19) return 0.820215;
  else if(ptB<20) return 0.83501;
  else if(ptB<21) return 0.853838;
  else if(ptB<22) return 0.865113;
  else if(ptB<23) return 0.87358;
  else if(ptB<24) return 0.893233;
  else if(ptB<25) return 0.909597;
  else if(ptB<26) return 0.919336;
  else if(ptB<27) return 0.926104;
  else if(ptB<28) return 0.940649;
  else if(ptB<29) return 0.963733;
  else if(ptB<30) return 0.97171;
  else if(ptB<31) return 0.967569;
  else if(ptB<32) return 0.948828;
  else if(ptB<33) return 1.05547;
  else if(ptB<34) return 1.00769;
  else if(ptB<35) return 0.988522;
  else if(ptB<36) return 0.995099;
  else if(ptB<37) return 1.04206;
  else if(ptB<38) return 1.02003;
  else if(ptB<39) return 1.0461;
  else if(ptB<40) return 1.04391;
  else if(ptB<41) return 1.02988;
  else if(ptB<42) return 1.09458;
  else if(ptB<43) return 1.02195;
  else if(ptB<44) return 1.00227;
  else if(ptB<45) return 1.042;
  else if(ptB<46) return 1.00599;
  else if(ptB<47) return 1.08266;
  else if(ptB<48) return 1.0664;
  else if(ptB<49) return 0.999711;
  else if(ptB<50) return 1.10879;
  else if(ptB<51) return 1.09674;
  else if(ptB<52) return 1.09955;
  else if(ptB<53) return 1.09597;
  else if(ptB<54) return 1.13401;
  else if(ptB<55) return 1.04907;
  else if(ptB<56) return 1.11719;
  else if(ptB<57) return 1.02235;
  else if(ptB<58) return 1.11178;
  else if(ptB<59) return 1.04314;
  else if(ptB<60) return 0.940032;
  else if(ptB<61) return 1.1208;
  else if(ptB<62) return 1.09524;
  else if(ptB<63) return 1.09587;
  else if(ptB<64) return 1.06172;
  else if(ptB<65) return 1.32325;
  else if(ptB<66) return 1.23206;
  else if(ptB<67) return 0.975764;
  else if(ptB<68) return 1.09389;
  else if(ptB<69) return 1.22962;
  else if(ptB<70) return 1.23585;
  else if(ptB<71) return 1.10778;
  else if(ptB<72) return 0.978404;
  else if(ptB<73) return 0.976452;
  else if(ptB<74) return 0.926465;
  else if(ptB<75) return 1.36474;
  else if(ptB<76) return 1.0219;
  else if(ptB<77) return 1.06599;
  else if(ptB<78) return 1.1451;
  else if(ptB<79) return 0.944286;
  else if(ptB<80) return 1.01788;
  else if(ptB<81) return 1.08498;
  else if(ptB<82) return 0.893767;
  else if(ptB<83) return 1.08491;
  else if(ptB<84) return 0.824411;
  else if(ptB<85) return 1.10867;
  else if(ptB<86) return 1.11823;
  else if(ptB<87) return 1.26815;
  else if(ptB<88) return 1.04035;
  else if(ptB<89) return 1.12364;
  else if(ptB<90) return 0.999843;
  else if(ptB<91) return 1.09449;
  else if(ptB<92) return 0.800113;
  else if(ptB<93) return 0.839017;
  else if(ptB<94) return 1.24008;
  else if(ptB<95) return 1.07787;
  else if(ptB<96) return 1.1578;
  else if(ptB<97) return 0.926529;
  else if(ptB<98) return 1.34082;
  else if(ptB<99) return 1.54135;
  else if(ptB<110) return 0.973232;
  else return 1;
}



float FONLLweightRun3_Up(float ptB){
  if (ptB<1) return	0.538034;
  else if(ptB<2) return	0.583865;
  else if(ptB<3) return	0.615693;
  else if(ptB<4) return	0.640369;
  else if(ptB<5) return	0.659844;
  else if(ptB<6) return	0.63329;
  else if(ptB<7) return	0.592136;
  else if(ptB<8) return	0.552837;
  else if(ptB<9) return	0.551522;
  else if(ptB<10) return 0.534102;
  else if(ptB<11) return 0.542191;
  else if(ptB<12) return 0.549186;
  else if(ptB<13) return 0.561285;
  else if(ptB<14) return 0.572809;
  else if(ptB<15) return 0.583388;
  else if(ptB<16) return 0.591578;
  else if(ptB<17) return 0.636491;
  else if(ptB<18) return 0.635424;
  else if(ptB<19) return 0.647729;
  else if(ptB<20) return 0.663214;
  else if(ptB<21) return 0.681837;
  else if(ptB<22) return 0.694459;
  else if(ptB<23) return 0.704716;
  else if(ptB<24) return 0.723846;
  else if(ptB<25) return 0.740308;
  else if(ptB<26) return 0.75133;
  else if(ptB<27) return 0.759839;
  else if(ptB<28) return 0.774648;
  else if(ptB<29) return 0.796468;
  else if(ptB<30) return 0.805716;
  else if(ptB<31) return 0.804868;
  else if(ptB<32) return 0.791613;
  else if(ptB<33) return 0.882969;
  else if(ptB<34) return 0.845299;
  else if(ptB<35) return 0.831279;
  else if(ptB<36) return 0.838875;
  else if(ptB<37) return 0.88038;
  else if(ptB<38) return 0.863614;
  else if(ptB<39) return 0.887429;
  else if(ptB<40) return 0.887236;
  else if(ptB<41) return 0.876873;
  else if(ptB<42) return 0.933361;
  else if(ptB<43) return 0.872915;
  else if(ptB<44) return 0.857389;
  else if(ptB<45) return 0.892452;
  else if(ptB<46) return 0.862755;
  else if(ptB<47) return 0.929317;
  else if(ptB<48) return 0.916311;
  else if(ptB<49) return 0.860041;
  else if(ptB<50) return 0.954062;
  else if(ptB<51) return 0.94443;               
  else if(ptB<52) return 0.947303;
  else if(ptB<53) return 0.944689;
  else if(ptB<54) return 0.977496;
  else if(ptB<55) return 0.90517;
  else if(ptB<56) return 0.963472;
  else if(ptB<57) return 0.882623;
  else if(ptB<58) return 0.958668;
  else if(ptB<59) return 0.900069;
  else if(ptB<60) return 0.812043;
  else if(ptB<61) return 0.965189;
  else if(ptB<62) return 0.942925;
  else if(ptB<63) return 0.942721;
  else if(ptB<64) return 0.913128;
  else if(ptB<65) return 1.1308;
  else if(ptB<66) return 1.05339;
  else if(ptB<67) return 0.838155;
  else if(ptB<68) return 0.935597;
  else if(ptB<69) return 1.04612;
  else if(ptB<70) return 1.04915;
  else if(ptB<71) return 0.94217;
  else if(ptB<72) return 0.834057;
  else if(ptB<73) return 0.830866;
  else if(ptB<74) return 0.788221;
  else if(ptB<75) return 1.13863;
  else if(ptB<76) return 0.862078;
  else if(ptB<77) return 0.895112;
  else if(ptB<78) return 0.955165;
  else if(ptB<79) return 0.793115;
  else if(ptB<80) return 0.848999;
  else if(ptB<81) return 0.89861;
  else if(ptB<82) return 0.746077;
  else if(ptB<83) return 0.891876;
  else if(ptB<84) return 0.686867;
  else if(ptB<85) return 0.902467;
  else if(ptB<86) return 0.905568;
  else if(ptB<87) return 1.01106;
  else if(ptB<88) return 0.839588;
  else if(ptB<89) return 0.896304;
  else if(ptB<90) return 0.801849;
  else if(ptB<91) return 0.865943;
  else if(ptB<92) return 0.647708;
  else if(ptB<93) return 0.673347;
  else if(ptB<94) return 0.950225;
  else if(ptB<95) return 0.834233;
  else if(ptB<96) return 0.882643;
  else if(ptB<97) return 0.72054;
  else if(ptB<98) return 0.986762;
  else if(ptB<99) return 1.09923;
  else if(ptB<100) return 0.738026;
  else return 1;	
}	


float FONLLweightRun3_Down(float ptB){
  if (ptB<1) return 1.83234;
  else if(ptB<2) return	1.81862;
  else if(ptB<3) return	1.74421;
  else if(ptB<4) return	1.68144;
  else if(ptB<5) return	1.62834;
  else if(ptB<6) return	1.47856;
  else if(ptB<7) return	1.31521;
  else if(ptB<8) return	1.17523;
  else if(ptB<9) return	1.11322;
  else if(ptB<10) return 1.04231;
  else if(ptB<11) return 1.02327;
  else if(ptB<12) return 1.01092;
  else if(ptB<13) return 1.01485;
  else if(ptB<14) return 1.01785;
  else if(ptB<15) return 1.01952;
  else if(ptB<16) return 1.01755;
  else if(ptB<17) return 1.07828;
  else if(ptB<18) return 1.06088;
  else if(ptB<19) return 1.06657;
  else if(ptB<20) return 1.07787;
  else if(ptB<21) return 1.0944;
  else if(ptB<22) return 1.10156;
  else if(ptB<23) return 1.10535;
  else if(ptB<24) return 1.12345;
  else if(ptB<25) return 1.13753;
  else if(ptB<26) return 1.14353;
  else if(ptB<27) return 1.14609;
  else if(ptB<28) return 1.15846;
  else if(ptB<29) return 1.18142;
  else if(ptB<30) return 1.18593;
  else if(ptB<31) return 1.17597;
  else if(ptB<32) return 1.14856;
  else if(ptB<33) return 1.27285;
  else if(ptB<34) return 1.21088;
  else if(ptB<35) return 1.18375;
  else if(ptB<36) return 1.18786;
  else if(ptB<37) return 1.2401;
  else if(ptB<38) return 1.21026;
  else if(ptB<39) return 1.23781;
  else if(ptB<40) return 1.23201;
  else if(ptB<41) return 1.21248;
  else if(ptB<42) return 1.2858;
  else if(ptB<43) return 1.19772;
  else if(ptB<44) return 1.17213;
  else if(ptB<45) return 1.21628;
  else if(ptB<46) return 1.17191;
  else if(ptB<47) return 1.25926;
  else if(ptB<48) return 1.23828;
  else if(ptB<49) return 1.1588;
  else if(ptB<50) return 1.28394;
  else if(ptB<51) return 1.26844;
  else if(ptB<52) return 1.27017;
  else if(ptB<53) return 1.26475;
  else if(ptB<54) return 1.30766;
  else if(ptB<55) return 1.20811;
  else if(ptB<56) return 1.28616;
  else if(ptB<57) return 1.17544;
  else if(ptB<58) return 1.27842;
  else if(ptB<59) return 1.1983;
  else if(ptB<60) return 1.0784;
  else if(ptB<61) return 1.288;
  else if(ptB<62) return 1.25825;
  else if(ptB<63) return 1.25911;
  else if(ptB<64) return 1.21956;
  else if(ptB<65) return 1.52622;
  else if(ptB<66) return 1.42001;
  else if(ptB<67) return 1.12053;
  else if(ptB<68) return 1.25962;
  else if(ptB<69) return 1.42077;
  else if(ptB<70) return 1.42973;
  else if(ptB<71) return 1.27954;
  else if(ptB<72) return 1.12792;
  else if(ptB<73) return 1.12687;
  else if(ptB<74) return 1.06902;
  else if(ptB<75) return 1.5963;
  else if(ptB<76) return 1.18579;
  else if(ptB<77) return 1.24077;
  else if(ptB<78) return 1.33889;
  else if(ptB<79) return 1.09856;
  else if(ptB<80) return 1.18972;
  else if(ptB<81) return 1.27425;
  else if(ptB<82) return 1.0438;
  else if(ptB<83) return 1.28047;
  else if(ptB<84) return 0.963848;
  else if(ptB<85) return 1.31702;
  else if(ptB<86) return 1.33288;
  else if(ptB<87) return 1.52721;
  else if(ptB<88) return 1.24271;
  else if(ptB<89) return 1.35246;
  else if(ptB<90) return 1.19906;
  else if(ptB<91) return 1.32426;
  else if(ptB<92) return 0.95335;
  else if(ptB<93) return 1.0054;
  else if(ptB<94) return 1.53069;
  else if(ptB<95) return 1.32206;
  else if(ptB<96) return 1.43344;
  else if(ptB<97) return 1.13283;
  else if(ptB<98) return 1.69517;
  else if(ptB<99) return 1.98366;
  else if(ptB<100) return 1.20852;
  else return 1;	
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
      FONLLweight_Down_MC = FONLLweightRun3_Down(genB_pt);
      FONLLweight_Up_MC = FONLLweightRun3_Up(genB_pt);
      FONLLweight_MC = FONLLweightRun3(genB_pt);


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
   outTreeMC_->Branch("genK_pdgId", &genK_pdgId_MC );
   outTreeMC_->Branch("genB_pt", &genB_pt_MC );
   outTreeMC_->Branch("genE1_pt", &genE1_pt_MC);
   outTreeMC_->Branch("genE2_pt", &genE2_pt_MC   );
   outTreeMC_->Branch("genK_pt", &genK_pt_MC);
   outTreeMC_->Branch("genB_eta", &genB_eta_MC );
   outTreeMC_->Branch("genE1_eta", &genE1_eta_MC);
   outTreeMC_->Branch("genE2_eta", &genE2_eta_MC);
   outTreeMC_->Branch("genK_eta", &genK_eta_MC );
   outTreeMC_->Branch("genB_phi", &genB_phi_MC );
   outTreeMC_->Branch("genE1_phi", &genE1_phi_MC);
   outTreeMC_->Branch("genE2_phi", &genE2_phi_MC);
   outTreeMC_->Branch("genK_phi", &genK_phi_MC );
   outTreeMC_->Branch("genB_mass", &genB_mass_MC);
   outTreeMC_->Branch("genE1_mass", &genE1_mass_MC);
   outTreeMC_->Branch("genE2_mass", &genE2_mass_MC);
   outTreeMC_->Branch("genK_mass", &genK_mass_MC );
   outTreeMC_->Branch("genB_charge", &genB_charge_MC );
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
   outTreeMC_->Branch("FONLLweight_Down", &FONLLweight_Down_MC);
   outTreeMC_->Branch("FONLLweight_Up", &FONLLweight_Up_MC);
   outTreeMC_->Branch("FONLLweight", &FONLLweight_MC);
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
    FONLLweight_Down_MC = -1000.;
    FONLLweight_Up_MC = -1000.;
    FONLLweight_MC = -1000.;
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
