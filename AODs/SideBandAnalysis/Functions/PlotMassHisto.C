#ifdef __CLING__
#include <iostream>
#include <list>
#endif

TH2F* MassHisto(const char *PathAnalysisFile, int Addon) {

  TString FileName = "FirstPtBinSideband.root";
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

void PlotMassHisto() {
  TString PathtoFolder =
      "/home/sbhawani/cernbox/ProtonDeuteron/AnalysisResultsRootfiles/AODs/ResultsFromAODTrain/Data/SidebandStudy/SideBandStudyInPTBins/";
  TString OutputdirName ="/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version1.0/MassPlotVersion1.0/";
  TString Outputfilename = "MassHistoinPTBin_";

  TH2F *Signal = 0;
  TH2F *LSB = 0;
  TH2F *RSB = 0;
  float pTRanges[6] = {0.0,1.5,2.0,2.5,3.2,4.05};
  int MaxpTBin = 5;

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

        TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 800, 600);
        cMassplot->SetLeftMargin(0.1605);
        cMassplot->SetRightMargin(0.0135);
        cMassplot->SetTopMargin(0.105);
        cMassplot->SetBottomMargin(0.18);
        gStyle->SetOptStat(0);
        TLegend *leg = new TLegend(0.6, 0.6, 0.9, 0.8);
        leg->AddEntry(Signal,"pd #oplus #bar{p}-#bar{d}");
        leg->AddEntry(LSB,"Left Sideband");
        leg->AddEntry(RSB,"Right SideBand");

        leg->SetLineColor(0);

        Signal->SetTitleSize(0.05);
        LSB->SetTitleSize(0.05);
        RSB->SetTitleSize(0.05);
        if(pTBin==0){
          Signal->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c",1.5,4.05));
          LSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c",1.5,4.05));
          RSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c",1.5,4.05));
        }else{
          Signal->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c",pTRanges[pTBin],pTRanges[pTBin+1]));
          LSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c",pTRanges[pTBin],pTRanges[pTBin+1]));
          RSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c",pTRanges[pTBin],pTRanges[pTBin+1]));
        }
        Signal->SetTitleOffset(0.55);
        LSB->SetTitleOffset(0.55);
        RSB->SetTitleOffset(0.55);
        Signal->GetXaxis()->SetLabelSize(0.05);
        Signal->GetXaxis()->SetTitleSize(0.06);
        Signal->GetXaxis()->SetTitleOffset(0.95);
        Signal->GetXaxis()->SetTitle("pT (GeV/c)");
        Signal->GetYaxis()->SetLabelSize(0.05);
        Signal->GetYaxis()->SetTitleSize(0.06);
        Signal->GetYaxis()->SetTitleOffset(1.0);
        Signal->GetYaxis()->SetTitle("#it{m}^{2}(GeV/c^{2})");
        Signal->GetXaxis()->SetRangeUser(1.4, 4.05);
        Signal->GetYaxis()->SetRangeUser(2.4, 4.5);

      //  Signal->SetLineColorAlpha(kBlue, 1);
     ///   LSB->SetLineColorAlpha(kRed, 1);
     //   RSB->SetLineColorAlpha(kGreen, 1);

       // Signal->SetMarkerStyle(8);
     //   LSB->SetMarkerStyle(8);
     //   RSB->SetMarkerStyle(8);

      //  Signal->SetMarkerSize(0.7);
      //  LSB->SetMarkerSize(0.7);
      //  RSB->SetMarkerSize(0.7);

       // Signal->SetMarkerColor(kBlue);
      //  LSB->SetMarkerColor(kRed);
       /// RSB->SetMarkerColor(kGreen);

        //Signal->SetLineWidth(1.1);
       // Signal->SetLineWidth(1.1);
       // Signal->SetLineWidth(1.1);
        Signal->Draw("colz histo");
        LSB->Draw("colz same");
        RSB->Draw("colz same");
        //leg->Draw("colz same");
        cMassplot->Print(Form("%s%s%d.png", OutputdirName.Data(), Outputfilename.Data(),pTBin));
        delete cMassplot;

      }

      return;

    }
