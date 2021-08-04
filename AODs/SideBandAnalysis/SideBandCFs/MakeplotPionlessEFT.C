#include "TROOT.h"
#include "TSystem.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TDatabasePDG.h"
#include "Plotstyle.h"
#include "ReadCFFile.h"



void MakeplotPionlessEFT() {
  //TString FileName = "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/LowpT1p4/FITCATS/LatestCkFITPd_R_1p0Correct.root";


  TFile *_file0 = TFile::Open("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/Systematics/systematicslow/CF_pd_Var0.root", "READ");
  TFile *_file1 = TFile::Open("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/Systematics/systematicslow/CF_pd_Var0.root", "READ");
  TFile *_file2 = TFile::Open("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/Systematics/systematicslow/CF_pd_Var0.root", "READ");
  TFile *_file3 = TFile::Open("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/Systematics/systematicslow/CF_pd_Var0.root", "READ");
  TFile *_file4 = TFile::Open("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/Systematics/systematicslow/CF_pd_Var0.root", "READ");

  TString OutputdirName ="~/cernbox/ProtonDeuteron/Outputs/CATSOutput/PionlessEFTCFs/PdCFs2/plots/";
  TString Outputfilename = "FitResultCoulombOnly_";
  TH1F *data =(TH1F *) _file0->FindObjectAny("hCk_ReweightedpdVar0MeV_1");
  TF1 *Fit =(TF1  *) _file1->FindObjectAny("fit_pd");
  TF1 *SignalFit =(TF1*) _file0->FindObjectAny("Signal");
  TF1 *baselineFit =(TF1*) _file0->FindObjectAny("Bline");


  bool pair =false;
  SetStyle(true);

  /// here we style the histo
  TH1F* h0 = nullptr;
  TF1* h1 = nullptr;
  TF1* h2 = nullptr;
  TF1* h3 = nullptr;
  if(pair){
   h0 = data;
   h1 = Fit;
   h2 = SignalFit;
   h3 = baselineFit;
  }else{
    h0 = data;
    h1 = Fit;
    h2 = SignalFit;
    h3 = baselineFit;
  }
  TFile *out = TFile::Open(Form("%s ApAdSidebandPlots.root",OutputdirName.Data() ), "recreate");
  TCanvas * c4 = new TCanvas("c8", "c8", 1200, 800);
  c4->cd();
  TLegend *leg= new TLegend(0.5, 0.3, 0.7, 0.6);
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
    h1->SetMarkerColor(kRed + 2);
    h1->SetLineColor(kRed + 2);
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


    h3->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
    h3->GetXaxis()->SetTitleSize(40);
    h3->GetYaxis()->SetTitleSize(40);
    h3->GetXaxis()->SetTitleOffset(1.35);
    h3->GetYaxis()->SetTitleOffset(1.4);
    h3->GetXaxis()->SetLabelSize(40);
    h3->GetYaxis()->SetLabelSize(40);
    h3->GetXaxis()->SetLabelOffset(.02);
    h3->GetYaxis()->SetLabelOffset(.02);
    h3->SetMarkerStyle(80);
    h3->SetMarkerSize(1.3);
    h3->SetMarkerColor(12);
    h3->SetLineColor(8);

    h0->GetYaxis()->SetRangeUser(-0.1, 1.5);
    h0->GetXaxis()->SetRangeUser(0.1, 300);
    h1->GetYaxis()->SetRangeUser(-0.1, 1.5);
    h1->GetXaxis()->SetRangeUser(0.01, 300);
    h2->GetYaxis()->SetRangeUser(-0.1, 1.5);
    h2->GetXaxis()->SetRangeUser(0.1, 300);
    h3->GetXaxis()->SetRangeUser(0.0, 300);
    h3->GetYaxis()->SetRangeUser(-0.1, 1.5);




    h0->Draw("");
    h1->Draw("same");
    h2->Draw("same");
    h3->Draw("same");

    leg->AddEntry(h0,"p#minus#kern[0.4]{d} #oplus #bar{p}#minus#kern[0.4]{#bard}","pef");
    leg->AddEntry(h1,"Fit","pef");
    leg->AddEntry(h2,"Signal","pef");
    leg->AddEntry(h3,"Baseline","pef");
    std::cout << "reached-6" << std::endl;
   // leg->AddEntry(hpTAd,"p#minus#kern[0.4]{d} #oplus #bar{p}#minus#kern[0.4]{#bard}","pef");
    std::cout << "reached-7" << std::endl;
   TLatex BeamText;
    BeamText.SetTextFont(43);
    BeamText.SetTextSize(40);
    BeamText.SetNDC(kTRUE);
    BeamText.DrawLatex(0.48, 0.86,Form("ALICE %s #sqrt{#it{s}} = %i TeV", "pp", (int) 13));
    BeamText.DrawLatex( 0.48,0.79,"High-mult. (0#kern[-0.65]{ }#minus#kern[-0.65]{ } 0.17#kern[-0.9]{ }% INEL#kern[-0.5]{ }>#kern[-0.5]{ }0)");

    std::cout << "reached-8" << std::endl;
    leg->Draw("same");
    std::cout << "reached-9" << std::endl;
    c4->SaveAs(Form("%s/FitpdCoulomb.pdf",OutputdirName.Data()));
    std::cout << "reached-10" << std::endl;
    h0->Write();
    h1->Write();
    h2->Write();
    c4->Write();
    out->Write();
    out->Close();

 return;

}
