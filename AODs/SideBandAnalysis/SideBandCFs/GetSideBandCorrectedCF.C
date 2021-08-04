#ifdef __CLING__
#include <iostream>
#include <list>
#include "CorrectionFunction.h"
#endif

float GetScaleFactor(TH1F*h1,TH1F*h2){
  int fbin1 = h1->FindBin(200);
      int lbin1 = h1->FindBin(300);
      int fbin2 = h2->FindBin(200);
      int lbin2 = h2->FindBin(300);
      float histoIn1 = h1->Integral(fbin1, lbin1);
      float histoIn2 = h2->Integral(fbin2, lbin2);
      return histoIn1/histoIn2*1.08;
}


void GetSideBandCorrectedCF() {
  TString InputdirName =
        "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/ComparewithMichael/Sidebandcomparision/Bhawani/FullNorm/";
  TString InputdirName2 =
         "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/ComparewithMichael/Sidebandcomparision/Bhawani/Norm240_340/";
  TString OutputdirName =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/ComparewithMichael/Sidebandcomparision/Bhawani/FullNorm/Outputs/";
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
  float rescaledVal_pd =  0.0;///1.133/0.916;
  float rescaledVal_apad = 0.0;// 1.349/1.116;
  TH1F *CorrectCkpd = new TH1F("CorrectCk","CorrectCk",74,4.0,3004);
  TH1F *CorrectCkApAd = new TH1F("CorrectCkApAd","CorrectCkApAd",74,4.0,3004);

  TH1F *rescalepd = new TH1F("rescalepd","rescalepd",74,4.0,3004);
  TH1F *rescaleapad = new TH1F("rescaleapad","rescaleapad",74,4.0,3004);

  TH1F *combinedpd_apad = new TH1F("combinedpd_apad","combinedpd_apad",74,4.0,3004);


//just for renormalization purpose
  TH1F * SignalpdNorm240_340 =GetCF(Form("%s%s",InputdirName2.Data(),"Norm240_340Signal_pd.root"));
  TH1F * SignalApAdNorm240_340 =GetCF(Form("%s%s",InputdirName2.Data(),"Norm240_340Signal_apad.root"));
  //actual correlations
      Signalpd =GetCF(Form("%s%s",InputdirName.Data(),"FourthSignal_pd.root"));
      SignalApAd =GetCF(Form("%s%s",InputdirName.Data(),"FourthSignal_apad.root"));
      hCkLowerPD =GetCF(Form("%s%s",InputdirName.Data(),"LowerSB_pd.root"));
      hCkUpperPD =GetCF(Form("%s%s",InputdirName.Data(),"UpperSB_pd.root"));
      hCkLowerAPAD =GetCF(Form("%s%s",InputdirName.Data(),"LowerSB_apad.root"));
      hCkUpperAPAD =GetCF(Form("%s%s",InputdirName.Data(),"UpperSB_apad.root"));

      GetCkCorrected(Signalpd, hCkLowerPD, hCkUpperPD,CorrectCkpd, OutputdirName,"SBcorrected_Pd",0.79,false);
      GetCkCorrected(SignalApAd, hCkLowerAPAD, hCkUpperAPAD,CorrectCkApAd,OutputdirName,"SBcorrected_APAd",0.7190,true);

      rescaledVal_pd = GetScaleFactor(SignalpdNorm240_340,Signalpd);
      rescaledVal_apad = GetScaleFactor(SignalApAdNorm240_340,SignalApAd);

      rescalepd = Rescale(CorrectCkpd,rescaledVal_pd, OutputdirName,"Rescaled_pd",true);
      rescaleapad = Rescale(CorrectCkApAd,rescaledVal_apad, OutputdirName,"Rescaled_apad",false);
      CombinedPlot(rescalepd,rescaleapad,combinedpd_apad, OutputdirName,"Rescaled_combinedpd_apad");
    return;
}
