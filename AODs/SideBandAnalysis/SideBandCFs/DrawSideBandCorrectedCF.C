#ifdef __CLING__
#include <iostream>
#include <list>
#endif

TH1F* GetCF(const char *PathAnalysisFile, int Addon) {

  TString FileName = "AODCorrelationFullPTBin_";
  TFile *_file0 = TFile::Open(
      TString::Format("%s%s%d.root", PathAnalysisFile,FileName.Data(), Addon), "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TH1F *h = (TH1F*) (_file0->FindObjectAny("hCk_ReweightedMeV_1"));

  if (!h) {
    std::cout << "no histo from"
        << TString::Format("%s%s%d.root", PathAnalysisFile, FileName.Data(), Addon)
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  return hCk;
}


void GetWeightedSBPlots(TH1F *Signal,TH1F *LSB,TH1F *RSB,TString OutputdirName,TString Outputfilename,int pTBin){
   TH1F *AddedSB = new TH1F(*LSB);
   AddedSB->Add(LSB,RSB,0.514,0.486);
   float pTRanges[6] = {0.0,1.5,2.0,2.5,3.2,4.05};
   TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 500, 400);
   cMassplot->SetLeftMargin(0.1605);
   cMassplot->SetRightMargin(0.035);
   cMassplot->SetTopMargin(0.105);
   cMassplot->SetBottomMargin(0.18);
   gStyle->SetOptStat(0);
   TLegend *leg = new TLegend(0.5, 0.6, 0.9, 0.8);
   leg->SetTextSize(0.035);
   leg->AddEntry(Signal,"pd #oplus #bar{p}-#bar{d}");
   leg->AddEntry(LSB,"Left Sideband");
   leg->AddEntry(RSB,"Right SideBand");
   leg->AddEntry(AddedSB,"51.35%LeftSB + 48.65% RightSB");
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
   Signal->GetXaxis()->SetTitle("k* (MeV/c)");
   Signal->GetYaxis()->SetLabelSize(0.05);
   Signal->GetYaxis()->SetTitleSize(0.06);
   Signal->GetYaxis()->SetTitleOffset(1.0);
   Signal->GetYaxis()->SetTitle("#it{C}(k*)");
   Signal->GetXaxis()->SetRangeUser(0, 400);
   Signal->GetYaxis()->SetRangeUser(0.0, 2.5);

   Signal->SetLineColorAlpha(kBlue, 1);
   LSB->SetLineColorAlpha(kRed, 1);
   RSB->SetLineColorAlpha(kGreen, 1);
   AddedSB->SetLineColorAlpha(kBlack, 1);
   Signal->SetMarkerStyle(8);
   LSB->SetMarkerStyle(8);
   RSB->SetMarkerStyle(8);
   AddedSB->SetMarkerStyle(8);
   Signal->SetMarkerSize(0.7);
   LSB->SetMarkerSize(0.7);
   RSB->SetMarkerSize(0.7);
   AddedSB->SetMarkerSize(0.7);
   Signal->SetMarkerColor(kBlue);
   LSB->SetMarkerColor(kRed);
   RSB->SetMarkerColor(kGreen);
   AddedSB->SetMarkerColor(kBlack);
   Signal->SetLineWidth(1.1);
   LSB->SetLineWidth(1.1);
   RSB->SetLineWidth(1.1);
   AddedSB->SetLineWidth(1.1);
   Signal->Draw("ep");
   AddedSB->Draw("same");
   LSB->Draw("same");
   RSB->Draw("same");
   leg->Draw("same");
   cMassplot->Print(Form("%s%s%d_AddedWeightedSB.pdf", OutputdirName.Data(), Outputfilename.Data(),pTBin));
   delete cMassplot;
}

void GetCkCorrectedSB(TH1F *Signal,TH1F *LSB,TH1F *RSB,TString OutputdirName,TString Outputfilename,int pTBin){
  TH1F *AddedSB = new TH1F(*LSB);
  TH1F *CorrectCk = new TH1F(*Signal);
   AddedSB->Add(LSB,RSB,0.514,0.486);
   CorrectCk->Add(CorrectCk,AddedSB,1.0/(0.615), -(1.0-0.615)/(0.615));

   float pTRanges[6] = {0.0,1.5,2.0,2.5,3.2,4.05};
   TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 600, 400);
   cMassplot->SetLeftMargin(0.1605);
   cMassplot->SetRightMargin(0.035);
   cMassplot->SetTopMargin(0.105);
   cMassplot->SetBottomMargin(0.18);
   gStyle->SetOptStat(0);
   TLegend *leg = new TLegend(0.45, 0.7, 0.9, 0.85);
   leg->SetTextSize(0.045);
   leg->AddEntry(Signal,"pd #oplus #bar{p}-#bar{d} [uncorrected]");
   leg->AddEntry(CorrectCk,"pd #oplus #bar{p}-#bar{d} [SB corrected]");
   leg->AddEntry(AddedSB,"51.35%LeftSB + 48.65% RightSB");
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
   Signal->GetXaxis()->SetTitle("k* (MeV/c)");
   Signal->GetYaxis()->SetLabelSize(0.05);
   Signal->GetYaxis()->SetTitleSize(0.06);
   Signal->GetYaxis()->SetTitleOffset(1.0);
   Signal->GetYaxis()->SetTitle("#it{C}(k*)");
   Signal->GetXaxis()->SetRangeUser(0, 400);
   Signal->GetYaxis()->SetRangeUser(0.0, 2.5);

   Signal->SetLineColorAlpha(kBlue, 1);
   LSB->SetLineColorAlpha(kRed, 1);
   RSB->SetLineColorAlpha(kGreen, 1);
   AddedSB->SetLineColorAlpha(kBlack, 1);
   CorrectCk->SetLineColorAlpha(kMagenta, 1);
   Signal->SetMarkerStyle(8);
   LSB->SetMarkerStyle(8);
   RSB->SetMarkerStyle(8);
   AddedSB->SetMarkerStyle(8);
   CorrectCk->SetMarkerStyle(8);
   Signal->SetMarkerSize(0.7);
   LSB->SetMarkerSize(0.7);
   RSB->SetMarkerSize(0.7);
   AddedSB->SetMarkerSize(0.7);
   CorrectCk->SetMarkerSize(0.7);
   Signal->SetMarkerColor(kBlue);
   LSB->SetMarkerColor(kRed);
   RSB->SetMarkerColor(kGreen);
   AddedSB->SetMarkerColor(kBlack);
   CorrectCk->SetMarkerColor(kMagenta);
   Signal->SetLineWidth(1.1);
   LSB->SetLineWidth(1.1);
   RSB->SetLineWidth(1.1);
   AddedSB->SetLineWidth(1.1);
   CorrectCk->SetLineWidth(1.1);
   Signal->Draw("ep");
   AddedSB->Draw("same");
   CorrectCk->Draw("same");
 //  LSB->Draw("same");
 //  RSB->Draw("same");
   leg->Draw("same");
   cMassplot->Print(Form("%s%s%d_CkSBcorrected.pdf", OutputdirName.Data(), Outputfilename.Data(),pTBin));
   delete cMassplot;
}
void DrawSideBandCorrectedCF() {
  TString PathtoFolder =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version1.0/";
  TString OutputdirName ="/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version1.0/PlotsVersion1.0/";
  TString Outputfilename = "SideBandCFinPTBin_";

  TH1F *Signal = 0;
  TH1F *LSB = 0;
  TH1F *RSB = 0;

  float pTRanges[6] = {0.0,1.5,2.0,2.5,3.2,4.05};
  int MaxpTBin = 1;

  for ( int pTBin = 0; pTBin < MaxpTBin; ++pTBin) {
        if(pTBin == 0) {
          Signal = GetCF(PathtoFolder,0);
          LSB = GetCF(PathtoFolder,13);
          RSB = GetCF(PathtoFolder,14);
        } else if(pTBin == 1 ) {
          Signal =GetCF(PathtoFolder,1);
          LSB = GetCF(PathtoFolder,5);
          RSB = GetCF(PathtoFolder,9);
        } else if(pTBin == 2 ) {
          Signal =GetCF(PathtoFolder,2);
          LSB = GetCF(PathtoFolder,6);
          RSB = GetCF(PathtoFolder,10);
        } else if(pTBin == 3 ) {
          Signal =GetCF(PathtoFolder,3);
          LSB = GetCF(PathtoFolder,7);
          RSB = GetCF(PathtoFolder,11);
        } else if(pTBin == 4 ) {
          Signal =GetCF(PathtoFolder,4);
          LSB = GetCF(PathtoFolder,8);
          RSB = GetCF(PathtoFolder,12);
        }
        GetCkCorrectedSB(Signal,LSB,RSB,OutputdirName,Outputfilename,pTBin);

      }

      return;

    }
