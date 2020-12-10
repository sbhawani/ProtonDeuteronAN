#ifdef __CLING__
#include <iostream>
#include <list>
#include "FitFunctions.C"
#endif

TH2F* MassHisto(const char *PathAnalysisFile, int Addon) {

  TString FileName = "FirstPtBinSideband.root";
  TFile *FileData = TFile::Open(TString::Format("%s%s", PathAnalysisFile,FileName.Data()), "READ");
  TDirectoryFile *MyTaskDirectory1 = (TDirectoryFile*) (FileData->FindObjectAny(Form("HMDeuteronMass%i", Addon)));
  TList *MyTaskList= (TList*) (MyTaskDirectory1->FindObjectAny(Form("HMDeuteronMass%i", Addon)));


  TH2F*hMass1 = (TH2F*) MyTaskList->FindObject("fDeuteronRestMassNoTOF");
  TH2F *hMass = (TH2F*) hMass1->Clone("hMass");
  hMass->Sumw2();


  if (!hMass) {
    std::cout << "no histo from"
        << TString::Format("%s%s%d", PathAnalysisFile, FileName.Data(), Addon)
        << std::endl;
    return 0;
  }
  return hMass;
}

void EstimateWeightsSB() {
  TString PathtoFolder =
      "/home/sbhawani/cernbox/ProtonDeuteron/AnalysisResultsRootfiles/AODs/ResultsFromAODTrain/Data/SidebandStudy/SideBandStudyInPTBins/";
  TString OutputdirName ="/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version1.0/EstimateWeightSBPlotVersion1.0/";
  TString Outputfilename = "FromSBCUT_";

  TH2F *Signal = 0;
  TH2F *LSB = 0;
  TH2F *RSB = 0;
  float pTRanges[6] = {0.0,1.5,2.0,2.5,3.2,4.05};
  int MaxpTBin = 1;

  for ( int pTBin = 0; pTBin < MaxpTBin; ++pTBin) {
        if(pTBin == 0) {
          Signal = MassHisto(PathtoFolder,0);
          LSB = MassHisto(PathtoFolder,13);
          RSB = MassHisto(PathtoFolder,14);
        } else if(pTBin == 1 ) {
          Signal =MassHisto(PathtoFolder,1);
          LSB = MassHisto(PathtoFolder,5);
          RSB = MassHisto(PathtoFolder,9);
        } else if(pTBin == 2 ) {
          Signal =MassHisto(PathtoFolder,2);
          LSB = MassHisto(PathtoFolder,6);
          RSB = MassHisto(PathtoFolder,10);
        } else if(pTBin == 3 ) {
          Signal =MassHisto(PathtoFolder,3);
          LSB = MassHisto(PathtoFolder,7);
          RSB = MassHisto(PathtoFolder,11);
        } else if(pTBin == 4 ) {
          Signal =MassHisto(PathtoFolder,4);
          LSB = MassHisto(PathtoFolder,8);
          RSB = MassHisto(PathtoFolder,12);
        }
        EstimateDeuteronBackground("DeuteronSB",OutputdirName,Outputfilename,Signal);
        EstimateDeuteronSBWeights("DeuteronSB",LSB,RSB);
      }

      return;
}
