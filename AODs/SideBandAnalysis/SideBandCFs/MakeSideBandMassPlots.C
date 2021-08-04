#include "TROOT.h"
#include "TSystem.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TDatabasePDG.h"
#include "Plotstyle.h"
#include "ReadCFFile.h"



void MakeSideBandMassPlots() {

  TString PathtoFolder =
      "/home/sbhawani/cernbox/ProtonDeuteron/AnalysisResultsRootfiles/AODs/ResultsFromAODTrain/Data/SidebandStudy/SideBandStudyInPTBins/SidebandSystematics/Version1/";
  TString OutputdirName ="/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version7.0/PlotsVersion7.0/";
  TString Outputfilename = "SideBandCFWholepTRange_";
  TString OutputfilenamePairs = "SideBandCorrected_Pairs";
  TString OutputfilenameAntiPairs = "SideBandCorrected_AntiPairs";

  TH2F *Signal = 0;
  TH2F *Signalpd = 0;
  TH2F *SignalApAd = 0;

  TH2F *CFLSBpd = 0;
  TH2F *CFRSBpd = 0;
  TH2F *CFLSBApAd = 0;
  TH2F *CFRSBApAd = 0;

  TH2F *LSB = 0;
  TH2F *RSB = 0;
  bool pair =true;
  SetStyle(true);
  if(pair){
  Signalpd = MassHistopd(PathtoFolder,0);
  CFLSBpd = MassHistopd(PathtoFolder,1);
  CFRSBpd = MassHistopd(PathtoFolder,10);
  }else{
    SignalApAd = MassHistoApAd(PathtoFolder,0);
    CFLSBApAd = MassHistoApAd(PathtoFolder,1);
    CFRSBApAd = MassHistoApAd(PathtoFolder,10);

  }
         // SignalApAd = GetCFSignalApAd("~/cernbox/ProtonDeuteron/Outputs/AODs/Correlations/",0);
         // CFLSBpd = GetCFLSBpd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version3.0/",0);
         // CFRSBpd = GetCFRSBpd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version3.0/",0);

         // CFLSBApAd = GetCFLSBApAd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version3.0/",0) ;
         // CFRSBApAd = GetCFRSBApAd("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/SideBandStudyInPtBins/Version3.0/",0) ;
 // SetStyleHistoCF(Signalpd,20,12,0.5);
  //SetStyleHistoCF(CFLSBpd,20,12,0.5);
  //SetStyleHistoCF(CFRSBpd,20,12,0.5);

  /// here we style the histo
  TH2F* h0 = nullptr;
  TH2F* h1 = nullptr;
  TH2F* h2 = nullptr;
  if(pair){
   h0 = Signalpd;
   h1 = CFLSBpd;
   h2 = CFRSBpd;
  }else{
    h0 = SignalApAd;
    h1 = CFLSBApAd;
    h2 = CFRSBApAd;
  }
  TFile *out = TFile::Open(Form("%s ApAdSidebandPlots.root",OutputdirName.Data() ), "recreate");
  TCanvas * c4 = new TCanvas("c8", "c8", 1200, 800);
  c4->SetLeftMargin(0.1405);
  c4->SetRightMargin(0.135);
  c4->SetTopMargin(0.105);
  c4->SetBottomMargin(0.18);
  c4->cd();
  TLegend *leg= new TLegend(0.5, 0.18, 0.7, 0.42);
  leg->SetFillStyle(0);
  leg->SetTextFont(43);
  leg->SetTextSizePixels(40);

    std::cout << "reached-4" << std::endl;
    h0->SetTitle("; #it{p}_{T} (GeV/#it{c}); #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2})");
    //h0->SetTitle("; #it{p}_{T}  (GeV/#it{c}); Purity/100");

   // h0->GetXaxis()->SetTitleSize(40);
    //h0->GetYaxis()->SetTitleSize(40);
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

    h1->SetTitle("; #it{p}_{T} (GeV/#it{c}); #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2})");
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

    h2->SetTitle("; #it{p}_{T} (GeV/#it{c}); #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2})");
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


    h0->GetYaxis()->SetRangeUser(0, 7.0);
    h0->GetXaxis()->SetRangeUser(0.0, 5.0);
    h1->GetYaxis()->SetRangeUser(0, 7.0);
    h1->GetXaxis()->SetRangeUser(0.0, 5.0);
    h2->GetYaxis()->SetRangeUser(0, 7.0);
    h2->GetXaxis()->SetRangeUser(0.0, 5.0);
    //h2->GetXaxis()->SetRangeUser(0, 0.4);
    //h2->GetYaxis()->SetRangeUser(0.0, 2.5);





    h0->Draw("colz");
    h2->Draw("col same");
    h1->Draw("col same");

    leg->AddEntry(h0,"#bar{p}#minus#kern[0.4]{#bard}: Signal","pef");
    leg->AddEntry(h1,"#bar{p}#minus#kern[0.4]{#bard}: Lower Sideband","pef");
    leg->AddEntry(h2,"#bar{p}#minus#kern[0.4]{#bard}: Upper Sideband","pef");
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
    //leg->Draw("same");
    std::cout << "reached-9" << std::endl;
    c4->SaveAs(Form("%s/AntiDeuteronMassPlot.pdf",OutputdirName.Data()));
    std::cout << "reached-10" << std::endl;
    h0->Write();
    h1->Write();
    h2->Write();
    c4->Write();
    out->Write();
    out->Close();

 return;

}
