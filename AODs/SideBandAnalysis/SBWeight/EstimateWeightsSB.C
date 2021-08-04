#ifdef __CLING__
#include <iostream>
#include <list>
#include "FitFunctions.C"
#endif

TH2F* MassHisto(const char *PathAnalysisFile, int Addon) {

  TFile *FileData = TFile::Open(
      TString::Format("%s", PathAnalysisFile), "READ");
  TDirectoryFile *MyTaskDirectory1 = (TDirectoryFile*) (FileData->FindObjectAny(
      Form("HMAntiDeuteronDCA%i", Addon)));
  TList *MyTaskList = (TList*) (MyTaskDirectory1->FindObjectAny(
      Form("HMAntiDeuteronDCA%i", Addon)));

  TH2F *hMass1 = (TH2F*) MyTaskList->FindObject("fAntiDeuteronRestMass");
  TH2F *hMass = (TH2F*) hMass1->Clone("hMass");
  hMass->Sumw2();

  if (!hMass) {
    std::cout << "no histo from"
        << TString::Format("%s%d", PathAnalysisFile, Addon)
        << std::endl;
    return 0;
  }
  return hMass;
}

void EstimateWeightsSB() {
  TString PathtoFolder =
      "/home/sbhawani/cernbox/ProtonDeuteron/AnalysisResultsRootfiles/AODs/ResultsFromAODTrain/Data/SidebandStudy/SideBandStudyInPTBins/FourthptBinSideBand.root";
  TString OutputdirName =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/ComparewithMichael/Sidebandcomparision/Bhawani/FullNorm/";
  TString Outputfilename = "FromSBCUT_";

  TH2F *Signal = 0;
  TH2F *LSB = 0;
  TH2F *RSB = 0;
  float pTRanges[6] = { 0.0, 1.5, 2.0, 2.5, 3.2, 4.05 };
  int MaxpTBin = 7;

  for (int pTBin = 6; pTBin < MaxpTBin; ++pTBin) {
    if (pTBin == 0) {
      Signal = MassHisto(PathtoFolder, 0);
      LSB = MassHisto(PathtoFolder, 7);
      RSB = MassHisto(PathtoFolder, 8);
    } else if (pTBin == 1) {
      Signal = MassHisto(PathtoFolder, 1);
      LSB = MassHisto(PathtoFolder, 5);
      RSB = MassHisto(PathtoFolder, 9);
    } else if (pTBin == 2) {
      Signal = MassHisto(PathtoFolder, 2);
      LSB = MassHisto(PathtoFolder, 6);
      RSB = MassHisto(PathtoFolder, 10);
    } else if (pTBin == 3) {
      Signal = MassHisto(PathtoFolder, 3);
      LSB = MassHisto(PathtoFolder, 7);
      RSB = MassHisto(PathtoFolder, 11);
    } else if (pTBin == 4) {
      Signal = MassHisto(PathtoFolder, 4);
      LSB = MassHisto(PathtoFolder, 8);
      RSB = MassHisto(PathtoFolder, 12);
    } else {
      Signal = MassHisto(PathtoFolder, 0);
      LSB = MassHisto(PathtoFolder, 7);
      RSB = MassHisto(PathtoFolder, 8);
    }
    // EstimateDeuteronBackground("DeuteronSB",OutputdirName,Outputfilename,Signal);

  }
  LSB = MassHisto(PathtoFolder, 7);
  RSB = MassHisto(PathtoFolder, 8);
  EstimateDeuteronSBWeights("DeuteronSB", LSB, RSB);
  return;
}
