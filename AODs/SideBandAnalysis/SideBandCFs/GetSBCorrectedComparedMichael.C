#ifdef __CLING__
#include <iostream>
#include <list>
#include "CorrectionFunction.h"
#endif

void GetSBCorrectedComparedMichael() {
  TString InputdirName =
        "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/ComparewithMichael/Sidebandcomparision/Bhawani/ComparableWithMichael/version0/";
  TString OutputdirName =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/ComparewithMichael/Sidebandcomparision/Bhawani/ComparableWithMichael/OutputTocomparewithMichael/";
  TString Outputfilename = "CorrectedAndPureCompared";
  TString OutputfilenamePairs = "SideBandCorrected_Pairs";
  TString OutputfilenameAntiPairs = "SideBandCorrected_AntiPairs";
  TH1F *Signalpure = 0;
  TH1F *Signal = 0;
  TH1F *Signalpd = 0;
  TH1F *SignalApAd = 0;

  TH1F *hCkLowerPD = 0;
  TH1F *hCkUpperPD = 0;
  TH1F *hCkLowerAPAD = 0;
  TH1F *hCkUpperAPAD = 0;
  float rescaledVal_pd =  1.133/0.916;
  float rescaledVal_apad =  1.349/1.116;
  TH1F *CorrectCkpd = new TH1F("CorrectCk","CorrectCk",74,0.0,3004);
  TH1F *CorrectCkApAd = new TH1F("CorrectCkApAd","CorrectCkApAd",74,0.0,3004);

  TH1F *rescalepd = new TH1F("rescalepd","rescalepd",74,4.0,3004);
  TH1F *rescaleapad = new TH1F("rescaleapad","rescaleapad",74,0.0,3004);

  TH1F *combinedpd_apad = new TH1F("combinedpd_apad","combinedpd_apad",74,0.0,3004);
     Signalpd =GetCF(Form("%s%s",InputdirName.Data(),"FourthSignal_pd.root"));
     SignalApAd =GetCF(Form("%s%s",InputdirName.Data(),"FourthSignal_apad.root"));
     hCkLowerPD =GetCF(Form("%s%s",InputdirName.Data(),"LowerSB_pd.root"));
     hCkUpperPD =GetCF(Form("%s%s",InputdirName.Data(),"UpperSB_pd.root"));
     hCkLowerAPAD =GetCF(Form("%s%s",InputdirName.Data(),"LowerSB_apad.root"));
     hCkUpperAPAD =GetCF(Form("%s%s",InputdirName.Data(),"UpperSB_apad.root"));
     GetCkCorrected(Signalpd, hCkLowerPD, hCkUpperPD,CorrectCkpd, OutputdirName,"SBcorrected_Pd",0.79,false);
     GetCkCorrected(SignalApAd, hCkLowerAPAD, hCkUpperAPAD,CorrectCkApAd,OutputdirName,"SBcorrected_APAd",0.71,true);
     CombinedPlot(CorrectCkpd,CorrectCkApAd,combinedpd_apad, OutputdirName,"combinedpd_apad");
    return;
}
