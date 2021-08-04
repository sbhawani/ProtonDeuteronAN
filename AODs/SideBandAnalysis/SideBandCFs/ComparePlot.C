#ifdef __CLING__
#include <iostream>
#include <list>
#include "Plotstyle.h"
#endif

TH1F* GetCF(const char *PathAnalysisFile, TString FileName) {

  TFile *_file0 = TFile::Open(
      TString::Format("%s%s", PathAnalysisFile, FileName.Data()), "READ");

  TH1F *h = (TH1F*) (_file0->FindObjectAny("hCk"));
  if (!h) {
    std::cout << "no histo from signal"
        << TString::Format("%s%s", PathAnalysisFile, FileName.Data())
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  return hCk;
}
void PlotComaprision(TH1F *h1, TH1F *h2, TString path, TString Outputfilename,
                     bool pair = false) {
  SetStyle(true);
  TCanvas *c4 = new TCanvas("c8", "c8", 1200, 800);
  c4->cd();
  TLegend *leg1 = new TLegend(0.45, 0.5, 0.62, 0.62);
  leg1->SetFillStyle(0);
  leg1->SetTextFont(43);
  leg1->SetTextSizePixels(40);
  h1->SetTitle(0);
  h1->SetStats(0);
  h1->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h1->SetTitle("; #it{p}_{T}  (GeV/#it{c}); Purity/100");
  h1->GetXaxis()->SetLabelOffset(.02);
  h1->GetYaxis()->SetLabelOffset(.02);

  h1->SetMarkerColor(kYellow + 2);
  h1->SetLineColor(kYellow + 2);
  h1->SetMarkerStyle(20);
  h1->SetLineWidth(1.1);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(1.3);
  h1->SetMarkerStyle(20);
  h1->SetTitle(0);
  h1->SetStats(0);

  h1->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h2->SetLineColor(kGreen + 2);
  h2->SetMarkerColor(kGreen + 2);

  h2->SetLineWidth(1.1);
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(1.3);
  h2->SetMarkerStyle(20);
  h2->SetTitle(0);
  h2->SetTitle(0);
  h2->SetLineWidth(1);

  h1->GetYaxis()->SetRangeUser(0, 1.5);
  h1->GetXaxis()->SetRangeUser(0.0, 0.4);
  h2->GetYaxis()->SetRangeUser(0, 1.5);
  h2->GetXaxis()->SetRangeUser(0.0, 0.4);

  // h2->Draw("same");

  if (pair) {
    leg1->AddEntry(h1, "p#minus#kern[0.4]{d}: [Norm 0-3k]");
    leg1->AddEntry(h2, "p#minus#kern[0.4]{d}: [Norm 500-800]");
  } else {
    leg1->AddEntry(h1, "#bar{p}#minus#kern[0.4]{#bard}: [Norm 0-3k]");
    leg1->AddEntry(h2, "#bar{p}#minus#kern[0.4]{#bard}: [Norm 500-800]");
  }

  auto rp = new TRatioPlot(h1, h2);
  rp->SetH1DrawOpt("E");
  rp->Draw(" ");
  leg1->Draw("same");

  rp->GetLowerRefYaxis()->SetTitle("ratio");
  rp->GetUpperRefYaxis()->SetTitle("#it{C}(#it{k}*)");

  rp->GetLowerRefGraph()->SetMarkerColor(kRed + 2);
  rp->GetLowerRefGraph()->SetLineColor(kRed + 2);
  rp->GetLowerRefGraph()->SetMarkerStyle(20);
  rp->GetLowerRefGraph()->SetLineWidth(1.1);
  rp->GetLowerRefGraph()->SetMarkerStyle(20);
  rp->GetLowerRefGraph()->SetMarkerSize(1.3);
  rp->GetLowerRefGraph()->SetMarkerStyle(20);
  rp->SetSeparationMargin(0);
  c4->Print(Form("%s%s.pdf", path.Data(), Outputfilename.Data()));
  std::cout << "Comparison drawn" << std::endl;
  delete c4;

}
void ComparePlot() {
  TString PathtoFolder0 =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version5.0/Pairs_AntiPairsCorrected/";
  TString PathtoFolder1 =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version6.0/Pairs_AntiPairsCorrected/";

  TString OutputdirName =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version5.0/Pairs_AntiPairsCorrected/";

  TH1F *Signalpd0 = 0;
  TH1F *SignalApAd0 = 0;
  TH1F *Signalpd1 = 0;
  TH1F *SignalApAd1 = 0;

  Signalpd0 = GetCF(PathtoFolder0, "RescaledPairs.root");
  Signalpd1 = GetCF(PathtoFolder1, "RescaledPairs.root");
  ;
  SignalApAd0 = GetCF(PathtoFolder0, "RescaledAntiPair.root");
  ;
  SignalApAd1 = GetCF(PathtoFolder1, "RescaledAntiPair.root");
  ;

  TH1F *hRescale1 = (TH1F*) Signalpd0->Clone("hRescale1");
  hRescale1->Divide(Signalpd0, Signalpd1);
  TH1F *hRescale2 = (TH1F*) SignalApAd0->Clone("hRescale2");
  hRescale2->Divide(SignalApAd0, SignalApAd1);
  cout << "hRescale1 =" << hRescale1->GetBinContent(6) << endl;
  cout << "hRescale2 =" << hRescale2->GetBinContent(6) << endl;
  PlotComaprision(Signalpd0, Signalpd1, PathtoFolder0, "PairComparision", true);
  PlotComaprision(SignalApAd0, SignalApAd1, PathtoFolder0, "AntiPairComparision", false);
}
