#include "TROOT.h"
#include "TSystem.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TDatabasePDG.h"
#include "Plotstyle.h"

TH1F* GetCFSignalpd(const char *PathAnalysisFile) {


  TFile *_file0 = TFile::Open(
      TString::Format("%s", PathAnalysisFile), "READ");
      TList *DirPair = (TList*)(_file0->FindObjectAny("PairDist"));

  TList *SubDirPair = (TList*)(DirPair->FindObject("PairReweighted"));
  cout<< "pointer1"<< SubDirPair << endl;
  TH1F  *h = (TH1F*) (SubDirPair->FindObject("CFDist_Particle0_Particle2_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from signal" << TString::Format("%s", PathAnalysisFile)<< std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  //hCk->Draw("");
  return hCk;
}

TH1F* GetCFSignalApAd(const char *PathAnalysisFile) {


  TFile *_file0 = TFile::Open(
      TString::Format("%s", PathAnalysisFile), "READ");  //TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));
  TList*DirPair = (TList*)(_file0->FindObjectAny("AntiPairDist"));
  TList*SubDirPair = (TList*)(DirPair->FindObject("PairReweighted"));
  TH1F *h = (TH1F*) (SubDirPair->FindObject("CFDist_Particle1_Particle3_clone_Shifted_FixShifted_Rebinned_10_Reweighted"));
  if (!h) {
    std::cout << "no histo from Signal APAD"<< TString::Format("%s", PathAnalysisFile) << std::endl;
    return 0;
  }
  TH1F *hCk = (TH1F*) h->Clone("hCk");
  hCk->Sumw2();
  return hCk;
}


void MakeMCplots() {
  TString OutputdirName ="/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/MCStudies/Correlations/Antipairs/";
  TString Outputfilename = "MCAntiPairPlots.pdf";

  TH1F *Signal = 0;
  TH1F *Signalpd = 0;
  TH1F *SignalApAd = 0;

  TH1F *SignalpdMC = 0;
  TH1F *SignalApAdMC = 0;

  bool pair =false;
  SetStyle(true);
  if(pair){
    Signalpd = GetCFSignalpd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/MCStudies/Correlations/Antipairs/AODdataCorrelations40MeVFullpT0.root");
    SignalpdMC = GetCFSignalpd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/MCStudies/Correlations/Antipairs/MCCorrelations40MeVFullpT0.root");
    }else{
    SignalApAd = GetCFSignalApAd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/MCStudies/Correlations/Antipairs/AODdataCorrelations40MeVFullpT0.root");
    SignalApAdMC = GetCFSignalApAd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/MCStudies/Correlations/Antipairs/MCCorrelations40MeVFullpT0.root");

  }

  TH1F* h0 = nullptr;
  TH1F* h1 = nullptr;
  if(pair){
   h0 = Signalpd;
   h1 = SignalpdMC;
  }else{
    h0 = SignalApAd;
    h1 = SignalApAdMC;
  }
  TFile *out = TFile::Open(Form("%s AntipairMC.root",OutputdirName.Data() ), "recreate");
  TCanvas * c4 = new TCanvas("c8", "c8", 1200, 800);
  c4->cd();
  TLegend *leg= new TLegend(0.6, 0.45, 0.8, 0.65);
  leg->SetFillStyle(0);
  leg->SetTextFont(43);
  leg->SetTextSizePixels(40);

    std::cout << "reached-4" << std::endl;
    h0->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
    //h0->SetTitle("; #it{p}_{T}  (GeV/#it{c}); Purity/100");

    h0->GetXaxis()->SetTitleSize(60);
    h0->GetYaxis()->SetTitleSize(60);
    h0->GetXaxis()->SetTitleOffset(1.35);
    h0->GetYaxis()->SetTitleOffset(1.4);
    h0->GetXaxis()->SetLabelSize(40);
    h0->GetYaxis()->SetLabelSize(40);
    h0->GetXaxis()->SetLabelOffset(.02);
    h0->GetYaxis()->SetLabelOffset(.02);

    h0->SetMarkerColor(kBlack);
    h0->SetLineColor(kBlack);
    h0->SetMarkerStyle(20);
    h0->SetLineWidth(1.1);
    h0->SetMarkerStyle(20);
    h0->SetMarkerSize(1.3);
    h0->SetMarkerStyle(20);
    h0->SetTitle(0);
    h0->SetStats(0);

    h1->SetTitle("; #it{k}*  (GeV/#it{c}); #it{C}(#it{k}*)");
    h1->GetXaxis()->SetTitleSize(0.06);
    h1->GetYaxis()->SetTitleSize(0.06);
   h1->GetXaxis()->SetTitleOffset(0.95);
   h1->GetYaxis()->SetTitleOffset(0.95);
    h1->GetXaxis()->SetLabelSize(0.05);
    h1->GetYaxis()->SetLabelSize(0.05);
    h1->GetXaxis()->SetLabelOffset(.02);
    h1->GetYaxis()->SetLabelOffset(.02);
    h1->SetMarkerColor(kGreen + 1);
    h1->SetLineColor(kGreen + 1);
    h1->SetLineWidth(1.1);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1.3);
    h1->SetMarkerStyle(20);
    h1->SetTitle(0);
    h1->SetTitle(0);
    h1->SetLineWidth(1);




    h0->GetYaxis()->SetRangeUser(0, 4.5);
    h0->GetXaxis()->SetRangeUser(0.0, 0.4);
    h1->GetYaxis()->SetRangeUser(0, 4.5);
    h1->GetXaxis()->SetRangeUser(0.0, 0.4);
   // h2->GetYaxis()->SetRangeUser(0, 3.0);
   // h2->GetXaxis()->SetRangeUser(0.0, 0.4);
    //h2->GetXaxis()->SetRangeUser(0, 0.4);
    //h2->GetYaxis()->SetRangeUser(0.0, 2.5);





    h1->Draw("");
    h0->Draw("same");

    leg->AddEntry(h0,"#bar{p}#minus#kern[0.4]{#bard}: data","pef");
    leg->AddEntry(h1,"#bar{p}#minus#kern[0.4]{#bard}: MC ","pef");
   // leg->AddEntry(h2,"#bar{p}#minus#kern[0.4]{#bard}: Upper Sideband","pef");
    std::cout << "reached-6" << std::endl;
   // leg->AddEntry(hpTAd,"p#minus#kern[0.4]{d} #oplus #bar{p}#minus#kern[0.4]{#bard}","pef");
    std::cout << "reached-7" << std::endl;
    TLatex BeamText;
    BeamText.SetTextFont(43);
    BeamText.SetTextSize(40);
    BeamText.SetNDC(kTRUE);
    BeamText.DrawLatex(0.48, 0.86,Form("ALICE %s #sqrt{#it{s}} = %i TeV", "pp", (int) 13));
    BeamText.DrawLatex( 0.48,0.79,"High-mult. (0#kern[-0.65]{ }#minus#kern[-0.65]{ } 0.17#kern[-0.9]{ }% INEL#kern[-0.5]{ }>#kern[-0.5]{ }0)");
   // BeamText.DrawLatex(0.48, 0.79, "High Mult");
    //BeamText.DrawLatex(0.48, 0.72, TString::Format("%s", sourceName).Data());
   //BeamText.DrawLatex(0.48, 0.65, "Avg Ref. Mult_{#eta < 0.8} ~23");
    std::cout << "reached-8" << std::endl;
    leg->Draw("same");
    std::cout << "reached-9" << std::endl;
    c4->SaveAs(Form("%s/MCantipair.pdf",OutputdirName.Data()));
    std::cout << "reached-10" << std::endl;
    h0->Write();
    h1->Write();
  //  h2->Write();
    c4->Write();
    out->Write();
    out->Close();

 return;

}
