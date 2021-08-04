#ifdef __CLING__
#include <iostream>
#include <list>
#include "Plotstyle.h"
#endif

TH1F* GetCF(const char *PathAnalysisFile) {
  TFile *_file0 = TFile::Open(PathAnalysisFile, "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TH1F *h = (TH1F*) (_file0->FindObjectAny("hCk_ReweightedpdVar0_1"));

  if (!h) {
    std::cout << "no histo from" << TString::Format("%s", PathAnalysisFile)
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  return hCk;
}

TH1F* GetCFSignal(const char *PathAnalysisFile, int Addon) {

  TString FileName = "AODlowPTVar_";
  TFile *_file0 = TFile::Open(
      TString::Format("%s%s%d.root", PathAnalysisFile, FileName.Data(), Addon),
      "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TH1F *h = (TH1F*) (_file0->FindObjectAny("hCk_ReweightedMeV_3"));

  if (!h) {
    std::cout << "no histo from"
        << TString::Format("%s%s%d.root", PathAnalysisFile, FileName.Data(),
                           Addon) << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  return hCk;
}
TH1F* GetCFSignalpd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "Signal40MeVFullpTNormFull0.root";
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

TH1F* GetCFSignalApAd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "Signal40MeVFullpTNormFull0.root";
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

TH1F* GetCFLSBApAd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "Sideband40MeVFullpTNormFull1";
  TFile *_file0 = TFile::Open(
      TString::Format("%s%s.root", PathAnalysisFile, FileName.Data()), "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TList *DirPair = (TList*) (_file0->FindObjectAny("AntiPairDist"));
  TList *SubDirPair = (TList*) (DirPair->FindObject("PairReweighted"));
  TH1F *h =
      (TH1F*) (SubDirPair->FindObject(
          "CFDist_Particle1_Particle3_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from LSB ApAd"
        << TString::Format("%s%s%d.root", PathAnalysisFile, FileName.Data())
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  hCk->Draw("");
  return hCk;
}

TH1F* GetCFRSBApAd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "Sideband40MeVFullpTNormFull10";
  TFile *_file0 = TFile::Open(
      TString::Format("%s%s.root", PathAnalysisFile, FileName.Data()), "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TList *DirPair = (TList*) (_file0->FindObjectAny("AntiPairDist"));
  TList *SubDirPair = (TList*) (DirPair->FindObject("PairReweighted"));
  TH1F *h =
      (TH1F*) (SubDirPair->FindObject(
          "CFDist_Particle1_Particle3_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from RSB ApAd"
        << TString::Format("%s%s%d.root", PathAnalysisFile, FileName.Data())
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  hCk->Draw("");
  return hCk;
}

TH1F* GetCFLSBpd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "Sideband40MeVFullpTNormFull1";
  TFile *_file0 = TFile::Open(
      TString::Format("%s%s.root", PathAnalysisFile, FileName.Data()), "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TList *DirPair = (TList*) (_file0->FindObjectAny("PairDist"));
  TList *SubDirPair = (TList*) (DirPair->FindObject("PairReweighted"));
  TH1F *h =
      (TH1F*) (SubDirPair->FindObject(
          "CFDist_Particle0_Particle2_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from LSB pd"
        << TString::Format("%s%s.root", PathAnalysisFile, FileName.Data())
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  hCk->Draw("");
  return hCk;
}

TH1F* GetCFRSBpd(const char *PathAnalysisFile, int Addon) {

  TString FileName = "Sideband40MeVFullpTNormFull10";
  TFile *_file0 = TFile::Open(
      TString::Format("%s%s.root", PathAnalysisFile, FileName.Data()), "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TList *DirPair = (TList*) (_file0->FindObjectAny("PairDist"));
  TList *SubDirPair = (TList*) (DirPair->FindObject("PairReweighted"));
  TH1F *h =
      (TH1F*) (SubDirPair->FindObject(
          "CFDist_Particle0_Particle2_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from RSB pd"
        << TString::Format("%s%s.root", PathAnalysisFile, FileName.Data())
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  hCk->Draw("");
  return hCk;
}

void Rescale(TH1F *h0, float rescale, TString OutputdirName,
             TString Outputfilename, int pTBin, bool pair) {
  TH1F *h01 = nullptr;
  TH1F *h11 = nullptr;
  TH1F *hrescaled = (TH1F*) h0->Clone();
  hrescaled->Sumw2();
  hrescaled->Scale(rescale);
  h01 = h0;
  h11 = hrescaled;
  TFile *out = TFile::Open(Form("%s%s.root",OutputdirName.Data(), Outputfilename.Data()),
                           "recreate");
  TCanvas *c4 = new TCanvas("c8", "c8", 1200, 800);
  c4->cd();
  TLegend *leg1 = new TLegend(0.45, 0.18, 0.62, 0.42);
  leg1->SetFillStyle(0);
  leg1->SetTextFont(43);
  leg1->SetTextSizePixels(40);

  h01->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h01->SetTitle("; #it{p}_{T}  (GeV/#it{c}); Purity/100");
  h01->GetXaxis()->SetLabelOffset(.02);
  h01->GetYaxis()->SetLabelOffset(.02);

  h01->SetMarkerColor(kYellow + 2);
  h01->SetLineColor(kYellow + 2);
  h01->SetMarkerStyle(20);
  h01->SetLineWidth(1.1);
  h01->SetMarkerStyle(20);
  h01->SetMarkerSize(1.3);
  h01->SetMarkerStyle(20);
  h01->SetTitle(0);
  h01->SetStats(0);

  h01->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h11->SetLineColor(kGreen + 2);
  h11->SetMarkerColor(kGreen + 2);

  h11->SetLineWidth(1.1);
  h11->SetMarkerStyle(20);
  h11->SetMarkerSize(1.3);
  h11->SetMarkerStyle(20);
  h11->SetTitle(0);
  h11->SetTitle(0);
  h11->SetLineWidth(1);

  h01->GetYaxis()->SetRangeUser(0, 1.5);
  h01->GetXaxis()->SetRangeUser(0.0, 0.4);
  h11->GetYaxis()->SetRangeUser(0, 1.5);
  h11->GetXaxis()->SetRangeUser(0.0, 0.4);

  h01->Draw("");
  h11->Draw("same");

  if (pair) {
    leg1->AddEntry(h01, "p#minus#kern[0.4]{d}: [Corrected original]");
    leg1->AddEntry(h11, "p#minus#kern[0.4]{d}: [corrected rescaled]");
  } else {
    leg1->AddEntry(h01, "#bar{p}#minus#kern[0.4]{#bard}: [Corrected original]");
    leg1->AddEntry(h11, "#bar{p}#minus#kern[0.4]{#bard}: [corrected rescaled]");
  }

  leg1->Draw("same");
  c4->Print(Form("%s%s.pdf",  OutputdirName.Data(),Outputfilename.Data()));
  std::cout << "Rescaled drawn" << std::endl;
  delete c4;
  h11->Write();
  out->Close();
}

void GetWeightedSBPlots(TH1F *Signal, TH1F *LSB, TH1F *RSB,
                        TString OutputdirName, TString Outputfilename,
                        int pTBin) {
  TH1F *AddedSB = new TH1F(*LSB);
  AddedSB->Add(LSB, RSB, 0.514, 0.486);
  float pTRanges[6] = { 0.0, 1.5, 2.5, 4.05 };
  TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 500, 400);
  cMassplot->SetLeftMargin(0.1605);
  cMassplot->SetRightMargin(0.035);
  cMassplot->SetTopMargin(0.105);
  cMassplot->SetBottomMargin(0.18);
  gStyle->SetOptStat(0);
  TLegend *leg = new TLegend(0.5, 0.6, 0.9, 0.8);
  leg->SetTextSize(0.035);
  leg->AddEntry(Signal, "pd #oplus #bar{p}-#bar{d}");
  leg->AddEntry(LSB, "Left Sideband");
  leg->AddEntry(RSB, "Right SideBand");
  leg->AddEntry(AddedSB, "51.35%LeftSB + 48.65% RightSB");
  leg->SetLineColor(0);

  Signal->SetTitleSize(0.05);
  LSB->SetTitleSize(0.05);
  RSB->SetTitleSize(0.05);
  if (pTBin == 0) {
    Signal->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
    LSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
    RSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
  } else {
    Signal->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
    LSB->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
    RSB->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
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
  cMassplot->Print(
      Form("%s%s%FromTOFMassAddedWeightedSB.pdf", OutputdirName.Data(),
           Outputfilename.Data(), pTBin));
  delete cMassplot;
}

void GetCkCorrectedSB(TH1F *Signal, TH1F *LSB, TH1F *RSB, TString OutputdirName,
                      TString Outputfilename, int pTBin) {
  TH1F *AddedSB = new TH1F(*LSB);
  TH1F *CorrectCk = new TH1F(*Signal);
  AddedSB->Add(LSB, RSB, 0.514, 0.486);
  CorrectCk->Add(CorrectCk, AddedSB, 1.0 / (0.615), -(1.0 - 0.615) / (0.615));

  float pTRanges[6] = { 0.0, 1.5, 2.5, 4.05 };
  TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 600, 400);
  cMassplot->SetLeftMargin(0.1605);
  cMassplot->SetRightMargin(0.035);
  cMassplot->SetTopMargin(0.105);
  cMassplot->SetBottomMargin(0.18);
  gStyle->SetOptStat(0);
  TLegend *leg = new TLegend(0.45, 0.7, 0.9, 0.85);
  leg->SetTextSize(0.045);
  leg->AddEntry(Signal, "pd #oplus #bar{p}-#bar{d} [uncorrected]");
  leg->AddEntry(CorrectCk, "pd #oplus #bar{p}-#bar{d} [SB corrected]");
  leg->AddEntry(AddedSB, "51.35%LeftSB + 48.65% RightSB");
  leg->SetLineColor(0);

  Signal->SetTitleSize(0.05);
  LSB->SetTitleSize(0.05);
  RSB->SetTitleSize(0.05);
  if (pTBin == 0) {
    Signal->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
    LSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
    RSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
  } else {
    Signal->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
    LSB->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
    RSB->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
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
  cMassplot->Print(
      Form("%s%s%d_CkSBcorrected.pdf", OutputdirName.Data(),
           Outputfilename.Data(), pTBin));
  delete cMassplot;
}

void GetCkCorrectedSBPairs(TH1F *Signal, TH1F *LSB, TH1F *RSB,
                           TString OutputdirName, TString Outputfilename,
                           int pTBin) {
  bool fullnorm = true;
  TH1F *AddedSB = new TH1F(*LSB);
  TH1F *CorrectCk = new TH1F(*Signal);
  //AddedSB->Add(LSB, RSB, 0.830568, 0.169432);
  AddedSB->Sumw2();
  RSB->Sumw2();
  CorrectCk->Sumw2();
  //AddedSB->Add(LSB, RSB, 0.514, 0.486);
  //AddedSB->Add(LSB, RSB, 0.964333, 0.0356669);
  AddedSB->Add(LSB, RSB, 0.654333, 0.346669);
  CorrectCk->Add(CorrectCk, AddedSB, 1.0 / (0.790), -(1.0 - 0.790) / (0.790));

  float pTRanges[6] = { 0.0, 1.5, 2.5, 4.05 };

  Signal->SetTitleSize(0.05);
  LSB->SetTitleSize(0.05);
  RSB->SetTitleSize(0.05);
  if (pTBin == 0) {
    Signal->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
    LSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
    RSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
  } else {
    Signal->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
    LSB->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
    RSB->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
  }

  TH1F *h0 = nullptr;
  TH1F *h1 = nullptr;
  TH1F *h2 = nullptr;
  h0 = Signal;
  h1 = CorrectCk;
  h2 = AddedSB;
  float rescale = 0.0;
  if(fullnorm){
    rescale = 0.986/0.8916;
  }else{
    rescale = 1.10604;
  }
  SetStyle(true);

  Rescale(CorrectCk, rescale, OutputdirName, "RescaledPairs", pTBin, true);

  TFile *out = TFile::Open(
      Form("%s FromTOFMasCorrectedSidebandPlots.root", OutputdirName.Data()),
      "recreate");
  TCanvas *c4 = new TCanvas("c8", "c8", 1200, 800);
  c4->cd();
  TLegend *leg = new TLegend(0.45, 0.18, 0.62, 0.42);
  leg->SetFillStyle(0);
  leg->SetTextFont(43);
  leg->SetTextSizePixels(40);

  std::cout << "reached-4" << std::endl;
  h0->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
//h0->SetTitle("; #it{p}_{T}  (GeV/#it{c}); Purity/100");

  h0->GetXaxis()->SetTitleSize(40);
  h0->GetYaxis()->SetTitleSize(40);
  h0->GetXaxis()->SetTitleOffset(1.35);
  h0->GetYaxis()->SetTitleOffset(1.4);
  h0->GetXaxis()->SetLabelSize(40);
  h0->GetYaxis()->SetLabelSize(40);
  h0->GetXaxis()->SetLabelOffset(.02);
  h0->GetYaxis()->SetLabelOffset(.02);

  h0->SetMarkerColor(kYellow + 2);
  h0->SetLineColor(kYellow + 2);
  h0->SetMarkerStyle(20);
  h0->SetLineWidth(1.1);
  h0->SetMarkerStyle(20);
  h0->SetMarkerSize(1.3);
  h0->SetMarkerStyle(20);
  h0->SetTitle(0);
  h1->SetStats(0);
  h2->SetTitle(0);
  h1->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h1->GetXaxis()->SetTitleOffset(1.35);
  h1->GetYaxis()->SetTitleOffset(1.4);

  h1->GetXaxis()->SetLabelOffset(.02);
  h1->GetYaxis()->SetLabelOffset(.02);
  h1->SetMarkerColor(kGreen + 2);
  h1->SetLineColor(kGreen + 2);
  h1->SetLineWidth(1.1);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(1.3);
  h1->SetMarkerStyle(20);
  h1->SetTitle(0);
  h1->SetTitle(0);
  h1->SetLineWidth(1);

  h2->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h2->GetXaxis()->SetTitleSize(40);
  h2->GetYaxis()->SetTitleSize(40);
  h2->GetXaxis()->SetTitleOffset(1.35);
  h2->GetYaxis()->SetTitleOffset(1.4);
  h2->GetXaxis()->SetLabelSize(40);
  h2->GetYaxis()->SetLabelSize(40);
  h2->GetXaxis()->SetLabelOffset(.02);
  h2->GetYaxis()->SetLabelOffset(.02);
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(1.3);
  h2->SetMarkerColor(12);
  h2->SetLineColor(12);

  h0->GetYaxis()->SetRangeUser(0, 2.2);
  h0->GetXaxis()->SetRangeUser(0.0, 0.4);
  h1->GetYaxis()->SetRangeUser(0, 2.2);
  h1->GetXaxis()->SetRangeUser(0.0, 0.4);
  h2->GetYaxis()->SetRangeUser(0, 2.2);
  h2->GetXaxis()->SetRangeUser(0.0, 0.4);

  h1->Draw("");
  h2->Draw("same");
  h0->Draw("same");

  leg->AddEntry(h0, "p#minus#kern[0.4]{d}: [uncorrected]", "pef");
  leg->AddEntry(h1, "p#minus#kern[0.4]{d}: [corrected]", "pef");
  leg->AddEntry(h2, "51.35%Lower + 48.65% Upper", "pef");
  leg->Draw("same");
  std::cout << "reached-9" << std::endl;

  c4->SaveAs(
      Form("%s/FromTOFMassCorrectedDeuteronSideBand.pdf",
           OutputdirName.Data()));
  std::cout << "reached-10" << std::endl;
  delete c4;
}

void GetCkCorrectedSBAntiPairs(TH1F *Signal, TH1F *LSB, TH1F *RSB,
                               TString OutputdirName, TString Outputfilename,
                               int pTBin) {
  bool fullnorm = true;
  TH1F *AddedSB = new TH1F(*LSB);
  TH1F *CorrectCk = new TH1F(*Signal);
  //AddedSB->Add(LSB, RSB, 0.52, 0.48);
  //AddedSB->Add(LSB, RSB, 0.830568, 0.169432);
  AddedSB->Sumw2();
  RSB->Sumw2();
  CorrectCk->Sumw2();
  AddedSB->Add(LSB, RSB, 0.650568, 0.349432);
  CorrectCk->Add(CorrectCk, AddedSB, 1.0 / (0.7190),
                 -(1.0 - 0.7190) / (0.7190));

  float pTRanges[6] = { 0.0, 1.5, 2.5, 4.05 };
  TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 600, 400);
  cMassplot->SetLeftMargin(0.1605);
  cMassplot->SetRightMargin(0.035);
  cMassplot->SetTopMargin(0.105);
  cMassplot->SetBottomMargin(0.18);
  gStyle->SetOptStat(0);

  SetStyle(true);
  float rescale = 0.0;
  if(fullnorm){
    rescale = 1.0286/0.923;
  }else{
    rescale = 1.07495;
  }
  Rescale(CorrectCk, rescale, OutputdirName, "RescaledAntiPair", pTBin, false);

  Signal->SetTitleSize(0.05);
  LSB->SetTitleSize(0.05);
  RSB->SetTitleSize(0.05);
  if (pTBin == 0) {
    Signal->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
    LSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
    RSB->SetTitle(Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", 1.5, 4.05));
  } else {
    Signal->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
    LSB->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
    RSB->SetTitle(
        Form("%0.2f GeV/c #leq p_{T} #leq %0.2f GeV/c", pTRanges[pTBin],
             pTRanges[pTBin + 1]));
  }

  TH1F *h0 = nullptr;
  TH1F *h1 = nullptr;
  TH1F *h2 = nullptr;
  h0 = Signal;
  h1 = CorrectCk;
  h2 = AddedSB;

  TFile *out = TFile::Open(
      Form("%s FromTOFMassApAdCorrectedSidebandPlots.root",
           OutputdirName.Data()),
      "recreate");
  TCanvas *c4 = new TCanvas("c8", "c8", 1200, 800);
  c4->cd();
  TLegend *leg = new TLegend(0.45, 0.65, 0.6, 0.9);
  leg->SetFillStyle(0);
  leg->SetTextFont(43);
  leg->SetTextSizePixels(40);
  h0->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h0->SetTitle(0);
  h1->SetStats(0);
  h2->SetTitle(0);
  h0->GetXaxis()->SetTitleSize(40);
  h0->GetYaxis()->SetTitleSize(40);
  h0->GetXaxis()->SetTitleOffset(1.35);
  h0->GetYaxis()->SetTitleOffset(1.4);
  h0->GetXaxis()->SetLabelSize(40);
  h0->GetYaxis()->SetLabelSize(40);
  h0->GetXaxis()->SetLabelOffset(.02);
  h0->GetYaxis()->SetLabelOffset(.02);

  h0->SetMarkerColor(kYellow + 2);
  h0->SetLineColor(kYellow + 2);
  h0->SetMarkerStyle(20);
  h0->SetLineWidth(1.1);
  h0->SetMarkerStyle(20);
  h0->SetMarkerSize(1.3);
  h0->SetMarkerStyle(20);
  h0->SetTitle(0);
  h0->SetStats(0);

  h1->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h1->GetXaxis()->SetTitleOffset(1.35);
  h1->GetYaxis()->SetTitleOffset(1.4);
  h1->GetXaxis()->SetLabelOffset(.02);
  h1->GetYaxis()->SetLabelOffset(.02);
  h1->SetMarkerColor(kGreen + 2);
  h1->SetLineColor(kGreen + 2);
  h1->SetLineWidth(1.1);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(1.3);
  h1->SetMarkerStyle(20);
  h1->SetTitle(0);
  h1->SetTitle(0);
  h1->SetLineWidth(1);

  h2->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h2->GetXaxis()->SetTitleSize(40);
  h2->GetYaxis()->SetTitleSize(40);
  h2->GetXaxis()->SetTitleOffset(1.35);
  h2->GetYaxis()->SetTitleOffset(1.4);
  h2->GetXaxis()->SetLabelSize(40);
  h2->GetYaxis()->SetLabelSize(40);
  h2->GetXaxis()->SetLabelOffset(.02);
  h2->GetYaxis()->SetLabelOffset(.02);
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(1.3);
  h2->SetMarkerColor(12);
  h2->SetLineColor(12);

  h0->GetYaxis()->SetRangeUser(0, 3.0);
  h0->GetXaxis()->SetRangeUser(0.0, 0.4);
  h1->GetYaxis()->SetRangeUser(0, 3.0);
  h1->GetXaxis()->SetRangeUser(0.0, 0.4);
  h2->GetYaxis()->SetRangeUser(0, 3.0);
  h2->GetXaxis()->SetRangeUser(0.0, 0.4);
  h1->Draw("");
  h2->Draw("same");
  h0->Draw("same");
  leg->AddEntry(h0, "#bar{p}#minus#kern[0.4]{#bard}: [uncorrected]", "pef");
  leg->AddEntry(h1, "#bar{p}#minus#kern[0.4]{#bard}: [corrected]", "pef");
  leg->AddEntry(h2, "51.35%Lower + 48.65% Upper", "pef");
  leg->Draw("same");
  c4->SaveAs(
      Form("%s/FromTOFMassAntiDeuteronSideBandCorrected.pdf",
           OutputdirName.Data()));
  std::cout << "reached-10" << std::endl;
  c4->Print(
      Form("%s%s%d_FromTOFMassNewCkSBcorrectedAntiPairs.pdf",
           OutputdirName.Data(), Outputfilename.Data(), pTBin));
  delete c4;
}

void GetCkAdded(TH1F *Signalpure, TH1F *Signalpd, TH1F *LSBpd, TH1F *RSBpd,
                TH1F *Signalapad, TH1F *LSBapad, TH1F *RSBapad,
                TString OutputdirName, TString Outputfilename) {

  TH1F *AddedSBpd = new TH1F(*LSBpd);
  TH1F *CorrectCkpd = new TH1F(*Signalpd);
  TH1F *AddedSBApAd = new TH1F(*LSBapad);
  TH1F *CorrectCkApAd = new TH1F(*Signalapad);
  TH1F *CorrectedCk = new TH1F(*CorrectCkpd);

  AddedSBpd->Add(LSBpd, RSBpd, 0.52, 0.48);
  CorrectCkpd->Add(CorrectCkpd, AddedSBpd, 1.0 / (0.63),
                   -(1.0 - 0.79) / (0.79));
  AddedSBApAd->Add(LSBapad, RSBapad, 0.52, 0.48);
  CorrectCkApAd->Add(CorrectCkApAd, AddedSBApAd, 1.0 / (0.7190),
                     -(1.0 - 0.7190) / (0.7190));
  CorrectedCk->Add(CorrectCkpd, CorrectCkApAd, 0.5, 0.5);
  SetStyle(true);

  TH1F *h0 = nullptr;
  TH1F *h1 = nullptr;
  TH1F *h2 = nullptr;

  h0 = Signalpure;
  h1 = CorrectedCk;
  h2 = AddedSBpd;

  TFile *out = TFile::Open(
      Form("%sFromTOFMassComparedCorrectedandPureSample.root",
           OutputdirName.Data()),
      "recreate");
  TCanvas *c4 = new TCanvas("c8", "c8", 1200, 800);
  c4->cd();
  TLegend *leg = new TLegend(0.45, 0.2, 0.6, 0.4);
  leg->SetFillStyle(0);
  leg->SetTextFont(43);
  leg->SetTextSizePixels(40);

  std::cout << "reached-4" << std::endl;
  h0->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");

  h0->GetXaxis()->SetTitleOffset(1.35);
  h0->GetYaxis()->SetTitleOffset(1.4);
// h0->GetXaxis()->SetLabelSize(40);
// h0->GetYaxis()->SetLabelSize(40);
  h0->GetXaxis()->SetLabelOffset(.02);
  h0->GetYaxis()->SetLabelOffset(.02);

  h0->SetMarkerColor(kYellow + 2);
  h0->SetLineColor(kYellow + 2);
  h0->SetMarkerStyle(20);
  h0->SetLineWidth(1.1);
  h0->SetMarkerStyle(20);
  h0->SetMarkerSize(1.3);
  h0->SetMarkerStyle(20);
  h0->SetTitle(0);
  h0->SetStats(0);

  h1->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
//h1->GetXaxis()->SetTitleSize(40);
//h1->GetYaxis()->SetTitleSize(40);
  h1->GetXaxis()->SetTitleOffset(1.35);
  h1->GetYaxis()->SetTitleOffset(1.4);
//h1->GetXaxis()->SetLabelSize(40);
//h1->GetYaxis()->SetLabelSize(40);
  h1->GetXaxis()->SetLabelOffset(.02);
  h1->GetYaxis()->SetLabelOffset(.02);
  h1->SetMarkerColor(kGreen + 2);
  h1->SetLineColor(kGreen + 2);
  h1->SetLineWidth(1.1);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(1.3);
  h1->SetMarkerStyle(20);
  h1->SetTitle(0);
  h1->SetTitle(0);
  h1->SetLineWidth(1);

  h2->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
  h2->GetXaxis()->SetTitleSize(40);
  h2->GetYaxis()->SetTitleSize(40);
  h2->GetXaxis()->SetTitleOffset(1.35);
  h2->GetYaxis()->SetTitleOffset(1.4);
  h2->GetXaxis()->SetLabelSize(40);
  h2->GetYaxis()->SetLabelSize(40);
  h2->GetXaxis()->SetLabelOffset(.02);
  h2->GetYaxis()->SetLabelOffset(.02);
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(1.3);
  h2->SetMarkerColor(12);
  h2->SetLineColor(12);

  h0->GetYaxis()->SetRangeUser(0, 1.5);
  h0->GetXaxis()->SetRangeUser(0.0, 0.4);
  h1->GetYaxis()->SetRangeUser(0, 1.5);
  h1->GetXaxis()->SetRangeUser(0.0, 0.4);
  h2->GetYaxis()->SetRangeUser(0, 1.5);
  h2->GetXaxis()->SetRangeUser(0.0, 0.4);
//h2->GetXaxis()->SetRangeUser(0, 0.4);
//h2->GetYaxis()->SetRangeUser(0.0, 2.5);

  h1->Draw("");
// h2->Draw("same");
  h0->Draw("same");
  leg->AddEntry(
      h0,
      "p#minus#kern[0.4]{d} #oplus #bar{p}#minus#kern[0.4]{#bard}: [#it{p}_{T}#leq 1.4 GeV/#it{c}]",
      "pef");
  leg->AddEntry(
      h1,
      "p#minus#kern[0.4]{d} #oplus #bar{p}#minus#kern[0.4]{#bard}: [Corrected]",
      "pef");
//leg->AddEntry(h2,"51.35%Lower + 48.65% Upper","pef");
  std::cout << "reached-6" << std::endl;
// leg->AddEntry(hpTAd,"p#minus#kern[0.4]{d} #oplus #bar{p}#minus#kern[0.4]{#bard}","pef");
  std::cout << "reached-7" << std::endl;
//  TLatex BeamText;
// BeamText.SetTextFont(43);
// BeamText.SetTextSize(40);
// BeamText.SetNDC(kTRUE);
//  BeamText.DrawLatex(0.48, 0.86,Form("ALICE %s #sqrt{#it{s}} = %i TeV", "pp", (int) 13));
//  BeamText.DrawLatex( 0.48,0.79,"High-mult. (0#kern[-0.65]{ }#minus#kern[-0.65]{ } 0.17#kern[-0.9]{ }% INEL#kern[-0.5]{ }>#kern[-0.5]{ }0)");
// BeamText.DrawLatex(0.48, 0.79, "High Mult");
//BeamText.DrawLatex(0.48, 0.72, TString::Format("%s", sourceName).Data());
//BeamText.DrawLatex(0.48, 0.65, "Avg Ref. Mult_{#eta < 0.8} ~23");
  std::cout << "reached-8" << std::endl;
  leg->Draw("same");
  std::cout << "reached-9" << std::endl;
  c4->SaveAs(
      Form("%s/FromTOFMassAntiDeuteronSideBandCorrected.pdf",
           OutputdirName.Data()));
  std::cout << "reached-10" << std::endl;
  c4->Print(
      Form("%sFromTOFMassComparedCorrectedandPure.pdf", OutputdirName.Data()));
  delete c4;
}

void DrawSideBandCorrectedCF() {
  TString PathtoFolder =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version7.0/";
  TString OutputdirName =
      "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version7.0/Pairs_AntiPairsCorrected/";
  TString Outputfilename = "CorrectedAndPureCompared";
  TString OutputfilenamePairs = "SideBandCorrected_Pairs";
  TString OutputfilenameAntiPairs = "SideBandCorrected_AntiPairs";
  TH1F *Signalpure = 0;
  TH1F *Signal = 0;
  TH1F *Signalpd = 0;
  TH1F *SignalApAd = 0;

  TH1F *CFLSBpd = 0;
  TH1F *CFRSBpd = 0;
  TH1F *CFLSBApAd = 0;
  TH1F *CFRSBApAd = 0;

  TH1F *LSB = 0;
  TH1F *RSB = 0;
  float rescale1 = 1.4844;
  float rescale2 = 0.9732 / 0.7932;
  float pTRanges[6] = { 0.0, 1.5, 2.5, 4.05 };
  int MaxpTBin = 5;

  for (int pTBin = 4; pTBin < MaxpTBin; ++pTBin) {
    if (pTBin == 0) {
      //Signal = GetCF(PathtoFolder,0);
      // LSB = GetCF(PathtoFolder,7);
      // RSB = GetCF(PathtoFolder,8);
    } else if (pTBin == 1) {
      //Signal =GetCF(PathtoFolder,1);
      // LSB = GetCF(PathtoFolder,3);
      // RSB = GetCF(PathtoFolder,5);
    } else if (pTBin == 2) {
      // Signal =GetCF(PathtoFolder,2);
      //  LSB = GetCF(PathtoFolder,4);
      //  RSB = GetCF(PathtoFolder,6);
    } else {

      // Signalpd = GetCFSignalpd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/Systematics/systematicslow",0);
      Signalpd =
          GetCFSignalpd(
              "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version7.0/",
              0);
      SignalApAd =
          GetCFSignalApAd(
              "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version7.0/",
              0);
      CFLSBpd =
          GetCFLSBpd(
              "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version7.0/",
              0);
      CFRSBpd =
          GetCFRSBpd(
              "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version7.0/",
              0);

      CFLSBApAd =
          GetCFLSBApAd(
              "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version7.0/",
              0);
      CFRSBApAd =
          GetCFRSBApAd(
              "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version7.0/",
              0);
      // RSB = GetCF(PathtoFolder,8);
    }
    Signalpure =
        GetCF(
            "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/Systematics/systematicslow/CF_pd_Var0.root");
    //Signalpure->Draw("");
    if (!Signalpure) {
      cout << "No pureSignal\n";
      return;
    }
    //GetCkCorrectedSB(Signal,LSB,RSB,OutputdirName,Outputfilename,pTBin);
    GetCkCorrectedSBPairs(Signalpd, CFLSBpd, CFRSBpd, OutputdirName,
                          OutputfilenamePairs, pTBin);
    GetCkCorrectedSBAntiPairs(SignalApAd, CFLSBApAd, CFRSBApAd, OutputdirName,
                              OutputfilenameAntiPairs, pTBin);
    //GetCkAdded(Signalpure,Signalpd,CFLSBpd,CFRSBpd,SignalApAd,CFLSBApAd,CFRSBApAd, OutputdirName,Outputfilename);
    return;

  }
}
