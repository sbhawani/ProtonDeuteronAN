#ifdef __CLING__
#include <iostream>
#include <list>
#endif

//histograms
void CountDeuteronFromPt() {

  TString FileNameData1, FileNameData2;

  int Var = 0;  // Peak of Mass

  FileNameData1 =
      "/home/sbhawani/Desktop/NanoBhawani/NanoTrains_result/Data/Systematics/AnalysisResultsPTCutVariation.root";

  TFile *FileData1 = TFile::Open(FileNameData1.Data(), "READ");

  TDirectoryFile *MyTaskDirectorySBL = (TDirectoryFile*) (FileData1
      ->FindObjectAny(Form("HMDeuteron%i", Var)));
  TList *MyTaskSBL = (TList*) (MyTaskDirectorySBL->FindObjectAny(
      Form("HMDeuteron%i", Var)));

  TH1F *hpT1;
  hpT1 = (TH1F*) MyTaskSBL->FindObject("pTDist_after");
  TH1F *hpT = (TH1F*) hpT1->Clone("hpT");
  hpT->Sumw2();
  hpT->Draw("");

  Double_t IntBinlow =hpT->GetXaxis()->FindBin(0.5);
  Double_t IntBinup = hpT->GetXaxis()->FindBin(4.05);
  std::cout << "BinLow " << IntBinlow <<" BinUp"<<IntBinup << std::endl;
  Double_t TotalCount = hpT->Integral(IntBinlow,IntBinup);


 Double_t IntBinlow1 =hpT->GetXaxis()->FindBin(0.5);
 Double_t IntBinup1 = hpT->GetXaxis()->FindBin(1.5);
 Double_t IntBinlow2 =hpT->GetXaxis()->FindBin(0.5);
 Double_t IntBinup2 = hpT->GetXaxis()->FindBin(2.0);

  double Countd1,Countd2, Countd3;
  Countd1 = hpT->Integral(IntBinlow1,IntBinup1);
  Countd2 = hpT->Integral(IntBinlow2,IntBinup2);


  cout<<"Total Count"<<TotalCount<< endl;
  cout<<" Count between pT[0.5, 1.5] "<<Countd1<<" Percentage "<<Countd1/TotalCount*100 <<"Throwing "<<100.0-Countd1/TotalCount*100<< endl;
  cout<<" Count between pT[0.5, 2.8] "<<Countd2<<" Percentage "<<Countd2/TotalCount*100 <<"Throwing "<<100.0-Countd2/TotalCount*100<< endl;
  return;

}
