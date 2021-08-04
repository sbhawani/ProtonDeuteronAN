#ifdef __CLING__
#include <iostream>
#include <list>
#include "Plotstyle.h"
#endif

void GetCkCorrected(TH1F *hSignal, TH1F *hLSB, TH1F *hRSB,TH1F*CorrectCk,
                           TString OutputdirName, TString Outputfilename,float purity_pair,bool apair = false, bool Michael = false) {

  int nbins = 75;
  TH1F *AddedSB = new TH1F("AddedSB","AddedSB",nbins,0.0,3000);
  SetStyle(true);

  float vLSB =0.0;
  float vRSB =0.0;
  float vLSB_err =0.0;
  float vRSB_err =0.0;
  float weight1 =0.0 ;
  float weight2 =0.0;
  float vadd =0.0;
  float vadd_err =0.0;

  for(int j = 1; j < nbins; j++){

    vLSB = hLSB->GetBinContent(j);
    vLSB_err = hLSB->GetBinError(j);
    vRSB = hRSB->GetBinContent(j);
    vRSB_err = hRSB->GetBinError(j);
    weight1 = 1 / vLSB_err / vLSB_err;
    weight2 = 1 / vRSB_err / vRSB_err;
    vadd = (weight1*vLSB + weight2*vRSB)/(weight1+weight2);
    vadd_err = 1/pow(weight1+weight2,0.5);
    AddedSB->SetBinContent(j,vadd);
    AddedSB->SetBinError(j,vadd_err);

  }

  float signal =0.0;
  float sideband =0.0;
  float signal_err =0.0;
  float sideband_err =0.0;
  float wanted =0.0;
  float wanted_err =0.0;

  for(int j = 1; j <= nbins; j++){
    signal = hSignal->GetBinContent(j);
    signal_err = hSignal->GetBinError(j);
    sideband = AddedSB->GetBinContent(j);
    sideband_err = AddedSB->GetBinError(j);
    wanted = (signal - (sideband*(1-purity_pair)))/purity_pair;
    wanted_err = TMath::Sqrt(((signal_err*signal_err)/(purity_pair*purity_pair)) + ((sideband_err*sideband_err)*((1-purity_pair)*(1-purity_pair))/(purity_pair*purity_pair)));
      CorrectCk->SetBinContent(j,wanted);
      CorrectCk->SetBinError(j,wanted_err);

  }

  TH1F *h0 = nullptr;
  TH1F *h1 = nullptr;
  TH1F *h2 = nullptr;
  h0 = hSignal;
  h1 = CorrectCk;
  h2 = AddedSB;

  TCanvas *c4 = new TCanvas("c8", "c8", 1200, 800);
  c4->cd();
  TLegend *leg = new TLegend(0.5, 0.65, 0.8, 0.85);
  leg->SetFillStyle(0);
  leg->SetTextFont(43);
  leg->SetTextSizePixels(40);
  h0->SetTitle(0);
  h1->SetTitle(0);
  h2->SetTitle(0);
  h0->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
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
  h0->GetXaxis()->SetRangeUser(0.0, 400);
  h1->GetYaxis()->SetRangeUser(0, 3.0);
  h1->GetXaxis()->SetRangeUser(0.0, 400);
  h2->GetYaxis()->SetRangeUser(0,3.0);
  h2->GetXaxis()->SetRangeUser(0.0, 400);

  h1->Draw("");
  h2->Draw("same");
  h0->Draw("same");

  if (apair) {
    leg->AddEntry(h0, "#bar{p}#minus#kern[0.4]{#bard}: [uncorrected]");
    leg->AddEntry(h1, "#bar{p}#minus#kern[0.4]{#bard}: [corrected]");
  } else {
    leg->AddEntry(h0, "p#minus#kern[0.4]{d}: [uncorrected]");
    leg->AddEntry(h1, "p#minus#kern[0.4]{d}: [corrected]");
  }
  leg->AddEntry(h2, "CF of BothSidebands");
  leg->Draw("same");
  c4->SaveAs(
      Form("%s/%s.pdf",
           OutputdirName.Data(),Outputfilename.Data()));
  TFile *savefile3 = new TFile(Form("%s%s.root",OutputdirName.Data(),Outputfilename.Data()),"RECREATE");
  c4->Write();
  h0->Write();
  h1->Write();
  h2->Write();
  savefile3->Close();
  c4->SaveAs(Form("%s/%s.pdf",OutputdirName.Data(),Outputfilename.Data()));
  delete c4;
}

TH1F* GetCF(const char *PathAnalysisFile) {
  TFile *_file0 = TFile::Open(PathAnalysisFile, "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TH1F *h = (TH1F*) (_file0->FindObjectAny("hCk_ReweightedMeV_3"));

  if (!h) {
    std::cout << "no histo from" << TString::Format("%s", PathAnalysisFile)
        << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  return hCk;
}

void CombinedPlot(TH1F *histo1,TH1F *histo2,TH1F *histo8,TString OutputdirName, TString Outputfilename){

  TString name = "p#minus#kern[0.4]{d}";
  TCanvas *c4 = new TCanvas("c4","c4",800,600);
  c4->cd();
  c4->SetTicks();

  float err1=0.0;
  float err2=0.0;
  float weight1=0.0 ;
  float weight2=.0;
  float val2=0.0;
  float val1=0.0;
  float add=0.0;
  float add_err=0.0;
  int nbins = 74;
  for(int j = 1; j <= nbins; j++){

    val1 = histo1->GetBinContent(j);
    err1 = histo1->GetBinError(j);
    val2 = histo2->GetBinContent(j);
    err2 = histo2->GetBinError(j);
    weight1 = 1 / err1 / err1;
    weight2 = 1 / err2 / err2;
    add = (weight1*val1 + weight2*val2)/(weight1+weight2);
    add_err = 1/pow(weight1+weight2,0.5);
    histo8->SetBinContent(j,add);
    histo8->SetBinError(j,add_err);
  }
  gStyle->SetTitleX(0.1f);
  gStyle->SetTitleW(0.9f);
  histo8->GetYaxis()->SetRangeUser(0, 2.0);
  histo8->GetXaxis()->SetRangeUser(0.0, 400);
  histo8->Draw("");
  histo8->SetLineColor(kBlue);
  histo8->SetLineWidth(2);
  histo8->SetTitle(0);
  histo8->SetTitle("; #it{k}*  (MeV/#it{c}); #it{C}(#it{k}*)");
  histo8->SetTitle(Form("%s (%.1f < #it{p}_{T} < %.2f)",name.Data(),0.5,4.05));

  TFile *savefile3 = new TFile(Form("%s%s.root",OutputdirName.Data(),Outputfilename.Data()),"RECREATE");
  histo8->Write();
  savefile3->Close();
  c4->SaveAs(Form("%s/%s.pdf",OutputdirName.Data(),Outputfilename.Data()));
  c4->Destructor();
}

TH1F* Rescale(TH1F *h0, float rescale, TString OutputdirName,
             TString Outputfilename, bool pair) {
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
  h01->SetTitle(0);
  h11->SetTitle(0);
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
  h11->SetStats(0);

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

  h01->GetYaxis()->SetRangeUser(0, 2.0);
  h01->GetXaxis()->SetRangeUser(0.0, 400);
  h11->GetYaxis()->SetRangeUser(0, 2.0);
  h11->GetXaxis()->SetRangeUser(0.0, 400);

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
  h11->Write();
  c4->SaveAs(Form("%s/%s.pdf",OutputdirName.Data(),Outputfilename.Data()));
  c4->Destructor();
  delete c4;
  out->Close();
  return h11;
}

