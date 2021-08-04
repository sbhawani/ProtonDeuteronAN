#include "TFile.h"

TH1F* GetCFSignalpd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "AODdataCorrelations40MeVFullpT";
  TFile *_file0 = TFile::Open(
      TString::Format("%s%s%d.root", PathAnalysisFile,FileName.Data(), Addon), "READ");
      TList *DirPair = (TList*)(_file0->FindObjectAny("PairDist"));

  cout<< "pointer0"<< DirPair << endl;
  TList *SubDirPair = (TList*)(DirPair->FindObject("PairReweighted"));
  cout<< "pointer1"<< SubDirPair << endl;
  TH1F  *h = (TH1F*) (SubDirPair->FindObject("CFDist_Particle0_Particle2_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from signal"
        << TString::Format("%s%s%d.root", PathAnalysisFile, FileName.Data(), Addon)
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  //hCk->Draw("");
  return hCk;
}

TH1F* GetCFSignalApAd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "AODdataCorrelations40MeVFullpT";
  TFile *_file0 = TFile::Open(
      TString::Format("%s%s%d.root", PathAnalysisFile,FileName.Data(), Addon), "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TList*DirPair = (TList*)(_file0->FindObjectAny("AntiPairDist"));
  TList*SubDirPair = (TList*)(DirPair->FindObject("PairReweighted"));
  TH1F *h = (TH1F*) (SubDirPair->FindObject("CFDist_Particle1_Particle3_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from Signal APAD"
        << TString::Format("%s%s%d.root", PathAnalysisFile, FileName.Data(), Addon)
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  return hCk;
}

TH2F* MassHistopd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "AnalysisResults.root";
  TFile *FileData = TFile::Open(TString::Format("%s%s", PathAnalysisFile,FileName.Data()), "READ");
  TDirectoryFile *MyTaskDirectory1 = (TDirectoryFile*) (FileData->FindObjectAny(Form("HMDeuteronDCA%i", Addon)));
  TList *MyTaskList= (TList*) (MyTaskDirectory1->FindObjectAny(Form("HMDeuteronDCA%i", Addon)));


  TH2F*hMass1 = (TH2F*) MyTaskList->FindObject("fDeuteronRestMass");
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

TH2F* MassHistoApAd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "AnalysisResults.root";
  TFile *FileData = TFile::Open(TString::Format("%s%s", PathAnalysisFile,FileName.Data()), "READ");
  TDirectoryFile *MyTaskDirectory1 = (TDirectoryFile*) (FileData->FindObjectAny(Form("HMDeuteronDCA%i", Addon)));
  TList *MyTaskList= (TList*) (MyTaskDirectory1->FindObjectAny(Form("HMDeuteronDCA%i", Addon)));


  TH2F*hMass1 = (TH2F*) MyTaskList->FindObject("fDeuteronRestMass");
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
