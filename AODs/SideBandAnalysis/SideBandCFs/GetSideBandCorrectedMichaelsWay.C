#ifdef __CLING__
#include <iostream>
#include <list>
#include "CorrectionFunction.h"
#endif


TH1F* GetHist(const char *PathAnalysisFile, TString filename, TString histname) {
  TFile *_file0 = TFile::Open(TString::Format("%s%s", PathAnalysisFile, filename.Data()), "READ"); //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TH1F *h = (TH1F*) (_file0->FindObjectAny(histname));

  if (!h) {
    std::cout << "no histo from" << TString::Format("%s", PathAnalysisFile)
              << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  return hCk;
}
void GetSideBandCorrectedMichaelsWay() {
  TString InputdirName =
        "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/ComparewithMichael/Sidebandcomparision/Bhawani/Michaelsway/CFs/CFsForCorrections/";
  TString OutputdirName =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/ComparewithMichael/Sidebandcomparision/Bhawani/Michaelsway/CFs/Latest/InputFromBhawani/";

  TH1F *Signalpure = 0;
  TH1F *Signal = 0;
  TH1F *Signalpd = 0;
  TH1F *SignalApAd = 0;
  TH1F *Signalpd_apad = 0;

  TH1F *hCkLowerPD = 0;
  TH1F *hCkUpperPD = 0;
  TH1F *hCkLowerAPAD = 0;
  TH1F *hCkUpperAPAD = 0;
  float rescaledVal_pd =  1.133/0.916;
  float rescaledVal_apad =  1.349/1.116;
  TH1F *CorrectCkpd = new TH1F("CorrectCk","CorrectCk",75,0.0,3000);
  TH1F *CorrectCkApAd = new TH1F("CorrectCkApAd","CorrectCkApAd",75,0.0,3000);

  TH1F *rescalepd = new TH1F("rescalepd","rescalepd",75,0.0,3000);
  TH1F *rescaleapad = new TH1F("rescaleapad","rescaleapad",75,0.0,3000);

  TH1F *combinedpd_apad = new TH1F("combinedpd_apad","combinedpd_apad",75,0.0,3000);
  TH1F *Low_plusHihghPTcombinedpd_apad = new TH1F("Low_plusHihghPTcombinedpd_apad","Low_plusHihghPTcombinedpd_apad",75,0.0,3000);
  //LowPTsignal------------------------------------
  Signalpd_apad = GetHist(InputdirName,"LowPTcombinedpd_apad.root","combinedpd_apad");
  ////HighPT-------------------------------------
     Signalpd =GetCF(Form("%s%s",InputdirName.Data(),"FullSignal_pd.root"));
     SignalApAd =GetCF(Form("%s%s",InputdirName.Data(),"FullSignal_apad.root"));
     hCkLowerPD =GetCF(Form("%s%s",InputdirName.Data(),"LowerSB_pd.root"));
     hCkUpperPD =GetCF(Form("%s%s",InputdirName.Data(),"UpperSB_pd.root"));
     hCkLowerAPAD =GetCF(Form("%s%s",InputdirName.Data(),"LowerSB_apad.root"));
     hCkUpperAPAD =GetCF(Form("%s%s",InputdirName.Data(),"UpperSB_apad.root"));
     GetCkCorrected(Signalpd, hCkLowerPD, hCkUpperPD,CorrectCkpd, OutputdirName,"SBcorrected_Pd",0.633,false);
     GetCkCorrected(SignalApAd, hCkLowerAPAD, hCkUpperAPAD,CorrectCkApAd,OutputdirName,"SBcorrected_APAd",0.55,true);
     CombinedPlot(CorrectCkpd,CorrectCkApAd,combinedpd_apad, OutputdirName,"HighPTcombinedpd_apad");
     CombinedPlot(Signalpd_apad,combinedpd_apad,Low_plusHihghPTcombinedpd_apad, OutputdirName,"LowPlusHighPTcombinedpd_apad");
    return;
}
