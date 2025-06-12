// from TChain Events/
//////////////////////////////////////////////////////////

#ifndef EventsBaseMC_hh
#define EventsBaseMC_hh

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string>
#include "EventsBaseMC.h"


class EventsMC : public EventsBaseMC {
public:
    EventsMC(TTree *tree=0);
    void LoopMC(std::string outname, std::string outdir);
    void OutputMC(std::string outname, std::string outdir);
    void initVarsMC();

   int          run_MC;
   int          luminosityBlock_MC;
   long long int       event_MC;
   int          bunchCrossing_MC;
   int          nBToKEE_MC;
   int          nElectron_MC;
   int          nGenPart_MC;
   float        genWeight_MC;
   int          nPSWeight_MC;
   float        PSWeight_MC; 
   int          nProbeTracks_MC;
   bool         HLT_DoubleEle10_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle9p5_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle9_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle8p5_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle8_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle7p5_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle7_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle6p5_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle6_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle5p5_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle5_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle4p5_eta1p22_mMax6_MC;
   bool         HLT_DoubleEle4_eta1p22_mMax6_MC;
   bool         L1_DoubleEG11_er1p2_dR_Max0p6_MC;
   bool         L1_DoubleEG10p5_er1p2_dR_Max0p6_MC;
   bool         L1_DoubleEG10_er1p2_dR_Max0p6_MC;
   bool         L1_DoubleEG9p5_er1p2_dR_Max0p6_MC;
   bool         L1_DoubleEG9_er1p2_dR_Max0p7_MC;
   bool         L1_DoubleEG8p5_er1p2_dR_Max0p7_MC;
   bool         L1_DoubleEG8_er1p2_dR_Max0p7_MC;
   bool         L1_DoubleEG7p5_er1p2_dR_Max0p7_MC;
   bool         L1_DoubleEG7_er1p2_dR_Max0p8_MC;
   bool         L1_DoubleEG6p5_er1p2_dR_Max0p8_MC;
   bool         L1_DoubleEG6_er1p2_dR_Max0p8_MC;
   bool         L1_DoubleEG5p5_er1p2_dR_Max0p8_MC;
   bool         L1_DoubleEG5_er1p2_dR_Max0p9_MC;
   bool         L1_DoubleEG4p5_er1p2_dR_Max0p9_MC;
   bool         L1_DoubleEG4_er1p2_dR_Max0p9_MC;

   bool         L1_4p5_HLT_4p0_ ;
   bool         L1_5p0_HLT_4p0_ ;
   bool         L1_5p5_HLT_4p0_ ;
   bool         L1_5p5_HLT_6p0_ ;
   bool         L1_6p0_HLT_4p0_ ;
   bool         L1_6p5_HLT_4p5_ ;
   bool         L1_7p0_HLT_5p0_ ;
   bool         L1_7p5_HLT_5p0_ ;
   bool         L1_8p0_HLT_5p0_ ;
   bool         L1_8p5_HLT_5p0_ ;
   bool         L1_8p5_HLT_5p5_ ;
   bool         L1_9p0_HLT_6p0_ ;
   bool         L1_10p5_HLT_5p0_;
   bool         L1_10p5_HLT_6p5_;
   bool         L1_11p0_HLT_6p5_;
   bool         trigger_OR_;


   int          nTrigObj_MC;
   int          nOtherPV_MC;
   float        PV_ndof_MC;
   float        PV_x_MC;
   float        PV_y_MC;
   float        PV_z_MC;
   float        PV_chi2_MC;
   float        PV_score_MC;
   int          PV_npvs_MC;
   int          PV_npvsGood_MC;
   int          nSV_MC;
   float        genB_pdgId_MC;
   float        genE1_pdgId_MC;
   float        genE2_pdgId_MC;
   float        genK_pdgId_MC;
   float        genB_pt_MC;
   float        genE1_pt_MC;
   float        genE2_pt_MC;
   float        genK_pt_MC;
   float        genB_eta_MC;
   float        genE1_eta_MC;
   float        genE2_eta_MC;
   float        genK_eta_MC;
   float        genB_phi_MC;
   float        genE1_phi_MC;
   float        genE2_phi_MC;
   float        genK_phi_MC;
   float        genB_mass_MC;
   float        genE1_mass_MC;
   float        genE2_mass_MC;
   float        genK_mass_MC;
   float        genB_charge_MC;
   float        genE1_charge_MC;
   float        genE2_charge_MC;
   float        genK_charge_MC;
   double        genB_mll_MC;
   float        recoE1_DR_MC;
   float        recoE1_Idx_MC;
   float        recoE1_pt_MC;
   float        recoE1_eta_MC;
   float        recoE1_phi_MC;
   float        recoE1_vx_MC;
   float        recoE1_vy_MC;
   float        recoE1_vz_MC;
   float        recoE1_isPF_MC;
   float        recoE1_isPFoverlap_MC;
   float        recoE1_charge_MC;
   float        recoE1_PFEleMvaID_Fall17NoIsoV2RawValue_MC;
   float        recoE1_PFEleMvaID_RetrainedRawValue_MC;
   float        recoE1_PFEleMvaID_Fall17NoIsoV2wpLoose_MC;
   float        recoE1_PFEleMvaID_Fall17NoIsoV2wp90_MC;
   float        recoE1_PFEleMvaID_Fall17NoIsoV2wp80_MC;
   float        recoE1_convVeto_MC;
   float        recoE2_DR_MC;
   float        recoE2_Idx_MC;
   float        recoE2_pt_MC;
   float        recoE2_eta_MC;
   float        recoE2_phi_MC;
   float        recoE2_vx_MC;
   float        recoE2_vy_MC;
   float        recoE2_vz_MC;
   float        recoE2_isPF_MC;
   float        recoE2_isPFoverlap_MC;
   float        recoE2_charge_MC;
   float        recoE2_PFEleMvaID_Fall17NoIsoV2RawValue_MC;
   float        recoE2_PFEleMvaID_RetrainedRawValue_MC;
   float        recoE2_PFEleMvaID_Fall17NoIsoV2wpLoose_MC;
   float        recoE2_PFEleMvaID_Fall17NoIsoV2wp90_MC;
   float        recoE2_PFEleMvaID_Fall17NoIsoV2wp80_MC;
   float        recoE2_convVeto_MC;
   float        recoK_DR_MC;
   float        recoK_Idx_MC;
   float        recoK_pt_MC;
   float        recoK_eta_MC;
   float        recoK_phi_MC;
   float        recoK_vx_MC;
   float        recoK_vy_MC;
   float        recoK_vz_MC;
   float        recoK_DCASig_MC;
   float        recoK_dzTrg_MC;
   float        recoK_isMatchedToMuon_MC;
   float        recoK_charge_MC;
   int          npreSkimBToKEE_MC;
   float        recoB_fit_pt_MC;
   float        recoB_fit_eta_MC;
   float        recoB_fit_phi_MC;
   float        recoB_D0_mass_LepToK_KToPi_MC;
   float        recoB_D0_mass_LepToPi_KToK_MC;
   float        recoB_fit_mass_MC;
   float        recoB_l_xy_MC;
   float        recoB_l_xy_unc_MC;
   float        recoB_fit_cos2D_MC;
   float        recoB_svprob_MC;
   float        recoB_fit_massErr_MC;
   float        recoB_b_iso04_MC;
   float        recoB_mll_fullfit_MC;
   float        recoB_vtx_x_MC;
   float        recoB_vtx_y_MC;
   float        recoB_vtx_z_MC;
   float        recoB_l1Idx_MC;
   float        recoB_l2Idx_MC;
   float        recoB_kIdx_MC;
   float        recoB_fit_k_pt_MC;
   float        recoB_fit_k_eta_MC;
   float        recoB_fit_k_phi_MC;
   float        recoB_fit_l1_pt_MC;
   float        recoB_fit_l1_eta_MC;
   float        recoB_fit_l1_phi_MC;
   float        recoB_fit_l2_pt_MC;
   float        recoB_fit_l2_eta_MC;
   float        recoB_fit_l2_phi_MC;
   float        recoB_l1_iso04_MC;
   float        recoB_l2_iso04_MC;
   float        recoB_l1_isPF_MC;
   float        recoB_l2_isPF_MC;
   float        recoB_k_iso04_MC;
   float        recoB_l1_isPFoverlap_MC;
   float        recoB_l2_isPFoverlap_MC;
   float        recoB_l1_LooseId_MC;
   float        recoB_l2_LooseId_MC;
   float        recoB_l1_MediumId_MC;
   float        recoB_l2_MediumId_MC;
   float        recoB_l1_TightId_MC;
   float        recoB_l2_TightId_MC;
   float        recoB_l1_ConvVeto_MC;
   float        recoB_l2_ConvVeto_MC;
   float        recoB_l1_PFMvaID_Fall17_MC;
   float        recoB_l2_PFMvaID_Fall17_MC;
   float        recoB_l1_PFMvaID_retrained_MC;
   float        recoB_l2_PFMvaID_retrained_MC;
   float        recoB_l1_iso04_dca_MC;
   float        recoB_l2_iso04_dca_MC;
   float        recoB_b_iso04_dca_MC;
   float        recoB_k_iso04_dca_MC;
   float        recoB_k_svip3d_MC;
   float        recoB_k_svip3d_err_MC;
   float        recoB_l1_n_isotrk_dca_MC;
   float        recoB_l2_n_isotrk_dca_MC;
   float        recoB_k_n_isotrk_dca_MC;
   float        recoB_Idx_MC;
   float        recoB_l_xy_sig_MC;
   float        recoB_l1l2Dz_MC;
   float        recoB_lKDz_MC;
   float        recoB_l1l2Dr_MC;
   float        recoB_lKDr_MC;
   float        recoB_k_opp_l_mass_MC;
   float        recoB_p_assymetry_MC;

   float        trig_wgt_MC; 
   float        BDTSCORE_1_MC;
   float        BDTSCORE_2_MC; 

   TFile* outFileMC_=nullptr;
   TTree* outTreeMC_=nullptr;


};

#endif