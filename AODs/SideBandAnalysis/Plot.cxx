#include "TCanvas.h"
#include "TH1.h"
#include "TFile.h"
#include "TStyle.h"
#include "TPad.h"




void MakePretty(TH1& hist,TCanvas& c);
void DrawInfo();
void DrawDataType();

Color_t Color1 = kBlack;
Color_t Color2 = kBlue;
Color_t Color3 = kViolet+1;
Color_t Color4 = kGreen+2;
Color_t Color5 = kOrange+7;
Color_t ColorRatio = kViolet+1;


void plot(){

  double range_min = 0.0;
  double range_max = 0.4;
  int ndiv = 110;
  //double range_max = 3.0;
  //int ndiv = 506;
  double limit_min = 0;
  double limit_max = 3000;

  double z_min = 0.0;
  double z_max = 3.0;
  int nbins = 75;

  gROOT->SetBatch(kTRUE); // kTRUE: do not display canvas on screen

  gStyle->SetOptStat(0);
  gStyle->SetTitleX(0.5);

  char PlotName[40] = "Null";
  char SaveName[40] = "Null";

  TFile *file1 = new TFile("Signal.root");
  TFile *file2 = new TFile("LowerSideband.root");
  TFile *file3 = new TFile("UpperSideband.root");
  double purity_pair = 0.605;
  double purity_antipair = 0.522;
  double pTmin = 1.4;
  double pTmax = 4.0;
 
  TH1F *histo6 = new TH1F("histo6","histo6",nbins,0,3);
  TH1F *histo7 = new TH1F("histo7","histo7",nbins,0,3);

  for(int i = 0;i <= 2; i++){

  char ParticlePair[20] = "Particle0_Particle2";
  char ParticleDist[20] = "PairDist";
  char ParticleNames[20] = "DeuteronProton";
  char ParticleAcronym[30] = "d-p";
  gStyle->SetTitleY(0.98);
  //if(i==0){
  //savefile1->cd();
  //}
  if(i==1){
    strcpy(ParticlePair,"Particle1_Particle3");
    strcpy(ParticleDist,"AntiPairDist");
    strcpy(ParticleNames,"AntideuteronAntiproton");
    strcpy(ParticleAcronym,"#bar{d}-#bar{p}");
    gStyle->SetTitleY(1.0);
    //savefile2->cd();
    std::cout << "Deuteron:\n" << std::endl;
  }else if(i==2){
    strcpy(ParticleAcronym,"d-p #otimes #bar{d}-#bar{p}");
    gStyle->SetTitleY(1.0);
    //savefile2->cd();
    std::cout << "Antideuteron:\n" << std::endl;
  }

  if(i==0 || i ==1){
   
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  TCanvas *c3 = new TCanvas("c3","c3",800,600);

  TList *ParticleList1 = (TList*) (file1->FindObjectAny(Form("%s",ParticleDist)));
  TList *ParticleList2 = (TList*) (file2->FindObjectAny(Form("%s",ParticleDist)));
  TList *ParticleList3 = (TList*) (file3->FindObjectAny(Form("%s",ParticleDist)));

  TList *Rebinned1 = nullptr;
  TList *Rebinned2 = nullptr;
  TList *Rebinned3 = nullptr;

  Rebinned1 = (TList*) ParticleList1->FindObject("PairRebinned");
  Rebinned2 = (TList*) ParticleList2->FindObject("PairRebinned");
  Rebinned3 = (TList*) ParticleList3->FindObject("PairRebinned");

  TH1F *histo1 = new TH1F();  
  TH1F *histo2 = new TH1F();  
  TH1F *histo3 = new TH1F();  

  histo1 = (TH1F*) Rebinned1->FindObject(Form("CFDist_%s_clone_Rebinned_10",ParticlePair));
  histo2 = (TH1F*) Rebinned2->FindObject(Form("CFDist_%s_clone_Rebinned_10",ParticlePair));
  histo3 = (TH1F*) Rebinned3->FindObject(Form("CFDist_%s_clone_Rebinned_10",ParticlePair));

  c1->cd();
  c1->SetGrid();
  c1->SetTicks();

  histo2->Draw("E");
  histo2->SetLineColor(Color2);
  histo2->SetLineWidth(3);
  histo2->GetXaxis()->SetNdivisions(ndiv,kFALSE);
  histo2->GetXaxis()->SetRangeUser(range_min,range_max);
  histo2->GetXaxis()->SetLimits(limit_min,limit_max);
  histo2->SetMinimum(z_min);
  histo2->SetMaximum(z_max);
  histo2->GetYaxis()->SetDecimals(1);
  histo2->GetYaxis()->SetTitle("CF(#it{k}*)");
  histo2->GetXaxis()->SetTitle("#it{k}* (MeV/#it{c})");
  histo2->SetTitle(Form("%s correlation functions (%.1f < #it{p}_{T} < %.1f)",ParticleAcronym,pTmin,pTmax));

  histo3->Draw("same E");
  histo3->SetLineColor(Color3);
  histo3->SetLineWidth(3);
  histo3->GetXaxis()->SetRangeUser(range_min,range_max);
  histo3->GetXaxis()->SetLimits(limit_min,limit_max);

  TH1F *histo4 = new TH1F("histo4","histo4",nbins,0,3);
  histo4->Draw("same AE");
  histo4->SetLineColor(Color4);
  histo4->SetLineWidth(3);
  histo4->GetXaxis()->SetRangeUser(range_min,range_max);
  histo4->GetXaxis()->SetLimits(limit_min,limit_max);
  histo4->Add(histo2,0.5);
  histo4->Add(histo3,0.5);

  TLegend *leg = new TLegend(0.4,0.7,0.91,0.88);
  leg->SetTextSize(0.03);
  leg->AddEntry(histo2,"lower sideband, norm range: 500 - 2000","l");
  leg->AddEntry(histo3,"upper sideband, norm range: 500 - 2000","l");
  leg->AddEntry(histo4,"both sidebands","l");
  leg->Draw();    

  DrawDataType();
  c1->SaveAs(Form("SidebandComparison_%s.eps",ParticleNames));

  TCanvas *c1_new = new TCanvas("c1_new","c1_new",800,600);
  c1_new->cd();
  c1_new->SetGrid();
  c1_new->SetTicks();

  histo2->Draw();
  histo2->GetXaxis()->SetRangeUser(0,3000);
  histo2->SetMinimum(0);
  histo2->SetMaximum(3);
  histo3->Draw("same E");
  histo3->GetXaxis()->SetRangeUser(0,3000);
  histo4->Draw("same AE");
  histo4->GetXaxis()->SetRangeUser(0,3000);
  leg->Draw();
  DrawDataType();
  c1_new->SaveAs(Form("SidebandComparison_%s_long.eps",ParticleNames));

  c2->cd();
  c2->SetGrid();
  c2->SetTicks();

  histo1->Draw("E");
  histo1->SetLineColor(Color1);
  histo1->SetLineWidth(3);
  histo1->GetXaxis()->SetNdivisions(ndiv,kFALSE);
  histo1->GetXaxis()->SetRangeUser(range_min,range_max);
  histo1->GetXaxis()->SetLimits(limit_min,limit_max);
  histo1->SetMinimum(z_min);
  histo1->SetMaximum(z_max);
  histo1->GetYaxis()->SetDecimals(1);
  histo1->GetYaxis()->SetTitle("CF(#it{k}*)");
  histo1->GetXaxis()->SetTitle("#it{k}* (MeV/#it{c})");
  histo1->SetTitle(Form("%s correlation functions (%.1f < #it{p}_{T} < %.1f)",ParticleAcronym,pTmin,pTmax));

  histo4->Draw("same AE");

  TLegend *leg2 = new TLegend(0.4,0.75,0.91,0.88);
  leg2->SetTextSize(0.03);
  leg2->AddEntry(histo1,"signal, norm range: 200 - 500","l");
  leg2->AddEntry(histo4,"both sidebands","l");
  leg2->Draw();    

  DrawDataType();
  c2->SaveAs(Form("Signal_and_Sideband_%s.eps",ParticleNames));

  TCanvas *c2_new = new TCanvas("c2_new","c2_new",800,600);
  c2_new->cd();
  c2_new->SetGrid();
  c2_new->SetTicks();

  histo1->Draw("E");
  histo1->GetXaxis()->SetRangeUser(0,3000);
  histo1->SetMinimum(0);
  histo1->SetMaximum(3);
  histo4->Draw("same AE");
  histo4->GetXaxis()->SetRangeUser(0,3000);
  leg2->Draw();
  DrawDataType();
  c2_new->SaveAs(Form("Signal_and_Sideband_%s_long.eps",ParticleNames));

  c3->cd();
  c3->SetGrid();
  c3->SetTicks();

  double signal;
  double sideband;
  double signal_err;
  double sideband_err;
  double wanted;
  double wanted_err;

  TH1F *histo5 = new TH1F("histo5","histo5",nbins,0,3);
        
  for(int j = 0; j < nbins; j++){

    signal = histo1->GetBinContent(j);
    signal_err = histo1->GetBinError(j);
    sideband = histo4->GetBinContent(j);
    sideband_err = histo4->GetBinError(j);
     
    if(i == 0){ 
      wanted = (signal - (sideband*(1-purity_pair)))/purity_pair;
      wanted_err = TMath::Sqrt(((signal_err*signal_err)/(purity_pair*purity_pair)) + ((sideband_err*sideband_err)*((1-purity_pair)*(1-purity_pair))/(purity_pair*purity_pair)));
    }else if(i == 1){
      wanted = (signal - (sideband*(1-purity_antipair)))/purity_antipair;
      wanted_err = TMath::Sqrt(((signal_err*signal_err)/(purity_antipair*purity_antipair)) + ((sideband_err*sideband_err)*((1-purity_antipair)*(1-purity_antipair))/(purity_antipair*purity_antipair)));
    }

    histo5->SetBinContent(j,wanted);
    histo5->SetBinError(j,wanted_err);

  }

  histo5->Draw("E");
  histo5->SetLineColor(Color5);
  histo5->SetLineWidth(3);
  histo5->GetXaxis()->SetNdivisions(ndiv,kFALSE);
  histo5->SetMinimum(z_min);
  histo5->SetMaximum(z_max);
  histo5->GetYaxis()->SetDecimals(1);
  histo5->GetYaxis()->SetTitle("CF(#it{k}*)");
  histo5->GetXaxis()->SetTitle("#it{k}* (MeV/#it{c})");
  histo5->SetTitle(Form("%s correlation function (%.1f < #it{p}_{T} < %.1f)",ParticleAcronym,pTmin,pTmax));

  if(i == 0){
    histo6 = (TH1F*) histo5->Clone("histo6");
  }else if(i == 1){
    histo7 = (TH1F*) histo5->Clone("histo7");
  }
  
  histo5->GetXaxis()->SetRangeUser(range_min,range_max);
  histo5->GetXaxis()->SetLimits(limit_min,limit_max);

  TLegend *leg3 = new TLegend(0.56,0.8,0.91,0.88);
  leg3->SetTextSize(0.03);
  leg3->AddEntry(histo5,"Signal without sidebands","l");
  leg3->Draw();    
  
  c3->SaveAs(Form("FinalCF_%s.eps",ParticleNames));


  if(i == 0){
    TFile *savefile1 = new TFile("3Sigma-Norm1-Deuteron-Proton-Pair.root","RECREATE");
    savefile1->cd();
    histo1->Write();
    histo2->Write();
    histo3->Write();
    histo4->Write();
    histo5->Write();
    savefile1->Close();
  }else if(i==1){
    TFile *savefile2 = new TFile("3Sigma-Norm1-Deuteron-Proton-Antipair.root","RECREATE");
    savefile2->cd();
    histo1->Write();
    histo2->Write();
    histo3->Write();
    histo4->Write();
    histo5->Write();
    savefile2->Close();
  }

  c1->Destructor();
  c2->Destructor();
  c1_new->Destructor();
  c2_new->Destructor();
  c3->Destructor();
  histo1->Delete();
  histo2->Delete();
  histo3->Delete();
  histo4->Delete();
  histo5->Delete();

  }else if(i==2){

    TCanvas *c4 = new TCanvas("c4","c4",800,600);
    c4->cd();
    c4->SetGrid();
    c4->SetTicks();
    
    TH1F *histo8 = new TH1F("histo8","histo8",nbins,0,3);

    histo8->Add(histo6,0.5);
    histo8->Add(histo7,0.5);
    histo8->Draw("E");
    histo8->SetLineColor(Color5);
    histo8->SetLineWidth(3);
    histo8->GetXaxis()->SetNdivisions(ndiv,kFALSE);
    histo8->GetXaxis()->SetRangeUser(range_min,range_max);
    histo8->GetXaxis()->SetLimits(limit_min,limit_max);
    histo8->SetMinimum(0);
    histo8->SetMaximum(3.0);
    histo8->GetYaxis()->SetDecimals(1);
    histo8->GetYaxis()->SetTitle("CF(#it{k}*)");
    histo8->GetXaxis()->SetTitle("#it{k}* (MeV/#it{c})");
    histo8->SetTitle(Form("%s correlation function (%.1f < #it{p}_{T} < %.1f)",ParticleAcronym,pTmin,pTmax));

    TFile *savefile3 = new TFile("3Sigma-Norm1-Deuteron-Proton-Combined.root","RECREATE");
    histo8->Write();
    savefile3->Close();
    c4->SaveAs("FinalCF_Combined.eps");
    c4->Destructor();
      
    }

  }
  
  histo6->Delete();
  histo7->Delete();

}





void DrawDataType(){

  TPaveText *text4 = new TPaveText(0.01,0.92,0.12,0.98,"NDC");
  text4->SetTextSize(0.03);
  text4->SetBorderSize(1);
  text4->SetFillColor(kWhite);
  text4->SetTextAlign(22);
  text4->AddText("AOD");
  text4->Draw();

}
