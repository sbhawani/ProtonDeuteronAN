TH1F* GetCFSignalpd(const char *PathAnalysisFile, TString FileName, int Addon) {

  TFile *_file0 = TFile::Open(
      TString::Format("%s%s", PathAnalysisFile, FileName.Data()), "READ");
  TList *DirPair = (TList*) (_file0->FindObjectAny("PairDist"));

  cout << "pointer0" << DirPair << endl;
  TList *SubDirPair = (TList*) (DirPair->FindObject("PairReweighted"));
  cout << "pointer1" << SubDirPair << endl;
  TH1F *h =
      (TH1F*) (SubDirPair->FindObject(
          "CFDist_Particle0_Particle2_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from signal"
        << TString::Format("%s%s", PathAnalysisFile, FileName.Data())
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  //hCk->Draw("");
  return hCk;
}

TH1F* GetCFSignalApAd(const char *PathAnalysisFile, TString FileName,
                      int Addon) {

  TFile *_file0 = TFile::Open(
      TString::Format("%s%s", PathAnalysisFile, FileName.Data()), "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TList *DirPair = (TList*) (_file0->FindObjectAny("AntiPairDist"));
  TList *SubDirPair = (TList*) (DirPair->FindObject("PairReweighted"));
  TH1F *h =
      (TH1F*) (SubDirPair->FindObject(
          "CFDist_Particle1_Particle3_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from Signal APAD"
        << TString::Format("%s%s", PathAnalysisFile, FileName.Data())
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  return hCk;
}

void ComputeRescaleFactor() {
  TString PathtoFolder =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version5.0/";
  TString OutputdirName =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version5.0/Pairs_AntiPairsCorrected/";
  TString Outputfilename = "CorrectedAndPureCompared";
  TString OutputfilenamePairs = "SideBandCorrected_Pairs";
  TString OutputfilenameAntiPairs = "SideBandCorrected_AntiPairs";

  TH1F *Signalpd0 = 0;
  TH1F *SignalApAd0 = 0;
  TH1F *Signalpd1 = 0;
  TH1F *SignalApAd1 = 0;

  float rescale1 = 0.9732 / 0.7932;
  float rescale2 = 0.9732 / 0.7932;
  int MaxpTBin = 5;

  // Signalpd = GetCFSignalpd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/Systematics/systematicslow",0);
  Signalpd0 =
  GetCFSignalpd(
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version6.0/PlotsVersion6.0/WithNoramlisationChnaged/Signal/","Signal40MeVFullpTNorm0p24_0p340.root",
      0);
 // Signalpd1 =GetCFSignalpd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version6.0/PlotsVersion5.0/WithNoramlisationChnaged/Signal/","Signal40MeVFullpTNorm0p0_300.root",0);
  Signalpd1 =GetCFSignalpd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version6.0/PlotsVersion6.0/WithNoramlisationChnaged/Signal/","Signal40MeVFullpTNormFull0.root",0);
  SignalApAd0 =GetCFSignalApAd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version6.0/PlotsVersion6.0/WithNoramlisationChnaged/Signal/","Signal40MeVFullpTNorm0p24_0p340.root",0);
  //SignalApAd1 =GetCFSignalApAd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version5.0/PlotsVersion5.0/WithNoramlisationChnaged/Signal/","Signal40MeVFullpTNorm0p0_300.root",0);
  SignalApAd1 =GetCFSignalApAd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version6.0/PlotsVersion6.0/WithNoramlisationChnaged/Signal/","Signal40MeVFullpTNormFull0.root",0);
  TH1F *hRescale1 = (TH1F*) Signalpd0->Clone("hRescale1");
  hRescale1->Divide(Signalpd0, Signalpd1);
  TH1F *hRescale2 = (TH1F*) SignalApAd0->Clone("hRescale2");
  hRescale2->Divide(SignalApAd0, SignalApAd1);
  cout << "hRescale1 =" << hRescale1->GetBinContent(6) << endl;
  cout << "hRescale2 =" << hRescale2->GetBinContent(6) << endl;
  hRescale1->Draw();
}

