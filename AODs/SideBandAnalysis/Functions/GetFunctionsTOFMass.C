#ifdef __CLING__
#include"TF1.h"
#include <iostream>
#include <list>
#endif
using namespace std;
double fMean(Double_t *x, Double_t *par) {
  Float_t xval = x[0];
  Float_t par0 = par[0];
  Float_t par1 = par[1];
  Float_t par2 = par[2];
  Float_t par3 = par[3];
  Float_t par4 = par[4];
  return TMath::Exp(par1 * xval + par2 * xval * xval+ par3 * xval * xval * xval+ par4  * xval* xval * xval * xval)+par0;
}
double fSigma(Double_t *x, Double_t *par) {
  Float_t xval = x[0];
  Float_t par0 = par[0];///par[0];
  Float_t par1 = par[1];//par[1];
  Float_t par2 = par[2];//par[2];
  Float_t par3 = par[3];
  Float_t par4 = par[4];
  return 0.0899 +0.1*(par0 * xval + par1 * xval * xval + par2 * xval * xval* xval+ par3 * xval * xval* xval* xval+ par4 * xval * xval* xval* xval* xval);
}

double fMean1(Double_t xval) {
  Float_t par0 = 3.55375e+00;
  Float_t par1 = -1.25749e+00;
  Float_t par2 = -3.60444e-01;
  Float_t par3 = -1.00250e-01;
  Float_t par4 = -1.00782e-02;

  /*Float_t par0 = par[0];
  Float_t par1 = par[1];
  Float_t par2 = par[2];
  Float_t par3 = par[3];
  Float_t par4 = par[4];*/
  return TMath::Exp(par1 * xval + par2 * xval * xval+ par3 * xval * xval * xval+ par4  * xval* xval * xval * xval)+par0;
}
double fSigma1(Double_t xval) {
  Float_t par0 = 5.19287e-02;
  Float_t par1 = 1.72460e-02;
  Float_t par2 = 1.33058e-02;//par[2];
  Float_t par3 = 3.03644e-04;
  Float_t par4 = 1.00006e-05;
  return 0.0899 +0.1*(par0 * xval + par1 * xval * xval + par2 * xval * xval* xval+ par3 * xval * xval* xval* xval+ par4 * xval * xval* xval* xval* xval);
}

void MakeMassPlot(TH1F*h,TF1*Fit,TString name,double yRangeLow,double yRangeHigh,double chisqs_NDF) {
    TCanvas *Plot = new TCanvas("Plot", "Plot", 0, 0, 800, 600);
    TString pdfMassName = Form("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/PlotFor%s.pdf", name.Data()); //plots are output as .pdf If you prefer other formats simply change the ending

    h->Draw("hist p");
    h->SetTitleSize(0.05);
    h->GetXaxis()->SetLabelSize(0.045);
    h->GetXaxis()->SetTitleSize(0.05);
    h->GetXaxis()->SetTitleOffset(0.89);
    h->GetXaxis()->SetTitle("p_{T} (GeV/#it{c})");
    h->GetYaxis()->SetLabelSize(0.035);
    h->GetYaxis()->SetTitleSize(0.05);
    h->GetYaxis()->SetTitleOffset(0.95);
    h->GetYaxis()->SetTitle("#it{Counts}");
    h->GetYaxis()->SetRangeUser(yRangeLow, yRangeHigh);
    h->SetLineColorAlpha(kBlue, 0.35);
    h->SetMarkerStyle(4);
    h->SetMarkerSize(1.3);
    h->SetMarkerColor(kBlue + 1);
    h->SetLineWidth(2);

    TLegend *legPlotFu = new TLegend( 0.15, 0.8, 0.3, 0.88);
    legPlotFu->SetTextSize(0.03);
    legPlotFu->AddEntry(h, "Data");
    legPlotFu->AddEntry(Fit, Form("Fit with #chi^{2}/NDF = %f",chisqs_NDF));
    legPlotFu->SetLineColor(0);
    legPlotFu->Draw("same");
    Fit->DrawCopy("same");
    Plot->Print(pdfMassName);
    delete Plot;
    delete legPlotFu;
}

void MakeMassPlotAll(Double_t *parMean,Double_t* parSig,TString name,double yRangeLow,double yRangeHigh) {


   /*TH1F*hmean;
   TH1F*hSigmaUp;
   TH1F*hSigmaLow;


   hmean  = new TH1F(Form("hmean", "hmean", 100 , 0.0, 4.1);
   hSigmaUp  = new TH1F(Form("hSigmaUp", "hSigmaUp", 100 , 0.0, 4.1);
   hSigmaLow  = new TH1F(Form("hSigmaLow", "hSigmaLow", 100 , 0.0, 4.1);*/
  std::cout<<"Reached-1"<<std::endl;
  TGraph*gMean =new TGraph();
  TGraph*gSigmaUp =new TGraph();
  TGraph*gSigmaLow =new TGraph();
 int npoint = 0;
   for(double pt = 0.8;pt<= 4.05; pt+=0.1){

     gMean->SetPoint(npoint,pt,fMean1(pt));
     gSigmaUp->SetPoint(npoint,pt,fMean1(pt)+1.5*fSigma1(pt));
     gSigmaLow->SetPoint(npoint,pt,fMean1(pt)-1.5*fSigma1(pt));
   /*  gMean->SetPoint(npoint,pt,fMean1(pt));
     gSigmaUp->SetPoint(npoint,pt,fMean1(pt)+3*fSigma1(pt,0.007,0.018));
     gSigmaLow->SetPoint(npoint,pt,fMean1(pt)-3*fSigma1(pt,0.007,0.018));*/
     npoint++;
   }

    TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
    TString pdfMassName = Form("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/PlotFor%s.pdf", name.Data()); //plots are output as .pdf If you prefer other formats simply change the ending
    Plot->SetLeftMargin(0.09);
    Plot->SetRightMargin(0.035);
    Plot->SetTopMargin(0.9505);
    Plot->SetBottomMargin(0.135);
   // gMean->Draw("ALP");
   // gMean->SetTitleSize(0.05);
    gMean->GetXaxis()->SetLabelSize(0.045);
    gMean->GetXaxis()->SetTitleSize(0.05);
    gMean->GetXaxis()->SetTitleOffset(0.89);
    gMean->GetXaxis()->SetTitle("p_{T} (GeV/#it{c})");
    gMean->GetYaxis()->SetLabelSize(0.035);
    gMean->GetYaxis()->SetTitleSize(0.05);
    gMean->GetYaxis()->SetTitleOffset(0.75);
    gMean->GetYaxis()->SetTitle("#it{Counts}");
    gMean->GetYaxis()->SetRangeUser(yRangeLow, yRangeHigh);
    gMean->GetXaxis()->SetLimits(0.0, 4.05);
    gMean->SetLineColorAlpha(kBlue, 0.35);
    gMean->SetMarkerStyle(4);
    gMean->SetMarkerSize(1.3);
    gMean->SetMarkerColor(kBlue + 1);
    gMean->SetLineWidth(2);

    gSigmaUp->SetLineColorAlpha(kRed, 0.35);
    gSigmaUp->SetMarkerStyle(4);
    gSigmaUp->SetMarkerSize(1.3);
    gSigmaUp->SetMarkerColor(kRed + 1);
    gSigmaUp->SetLineWidth(2);

    gSigmaLow->SetLineColorAlpha(kGreen, 0.35);
    gSigmaLow->SetMarkerStyle(4);
    gSigmaLow->SetMarkerSize(1.3);
    gSigmaLow->SetMarkerColor(kGreen + 1);
    gSigmaLow->SetLineWidth(2);

    TLegend *legPlotFu = new TLegend( 0.15, 0.7, 0.4, 0.88);
    legPlotFu->SetTextSize(0.03);
    legPlotFu->AddEntry(gMean, "Mean TOF Mass^{2}");
    legPlotFu->AddEntry(gSigmaUp, "gSigmaUp");
    legPlotFu->AddEntry(gSigmaLow, "gSigmaLow");
    legPlotFu->SetLineColor(0);
    std::cout<<"Reached-1"<<std::endl;
    gMean->Draw("ALP");
    std::cout<<"Reached-2"<<std::endl;
    legPlotFu->Draw("same");
    gSigmaUp->Draw("same");
    gSigmaLow->Draw("same");
    Plot->Print(pdfMassName);
    delete Plot;
    delete gMean;
    delete gSigmaLow;
    delete gSigmaUp;
    delete legPlotFu;
}


void GetFunctionsTOFMass() {
  TString FileNameData1, FileNameData2;

  int Var = 0;  // Peak of Mass

  FileNameData1 =
      "/home/sbhawani/Desktop/Fit/AODFIT/HM/BetterMacroForDeuteornMassFit/RootFiles/Mean_Deuteron.root";

  FileNameData2 =
      "/home/sbhawani/Desktop/Fit/AODFIT/HM/BetterMacroForDeuteornMassFit/RootFiles/Sigma_Deuteron.root";

  TFile *FileData1 = TFile::Open(FileNameData1.Data(), "READ");
  TFile *FileData2 = TFile::Open(FileNameData2.Data(), "READ");

  TH1F *hSigma1, *hSigma, *hMean1, *hMean;
  hMean1 = (TH1F*) FileData1->FindObjectAny("hMeanDeuteron");
  hSigma1 = (TH1F*) FileData2->FindObjectAny("hSigmaDeuteron");
  hMean = (TH1F*) hMean1->Clone("hMean");
  hSigma = (TH1F*) hSigma1->Clone("hSigma");
  hMean->Sumw2();
  hSigma->Sumw2();
  hMean->Draw("hist P");
  if (!hSigma) {
    std::cout << "No hSigma" << std::endl;
    return;
  }
  if (!hMean) {
    std::cout << "No hMean" << std::endl;
    return;
  }

  //hSigma->Draw("");

  TF1 *FitMean = new TF1("FitMean", fMean, 1.0, 4.05, 5);
  TF1 *FitSigma = new TF1("FitSigma", fSigma,1.0, 4.05, 5);

  Double_t parSig[5];
  Double_t parMean[5];
  FitMean->SetParameters(3.55, -1, -0.3,-0.2,-0.03);
  FitMean->SetParLimits(0, 3.5, 3.6);
  FitMean->SetParLimits(1, -2.0,-0.01 );
  FitMean->SetParLimits(2, -0.5, -0.1);
  FitMean->SetParLimits(3, -0.5, -0.1);
  FitMean->SetParLimits(4, -0.05, -0.01);

  FitSigma->SetParameters(0.007, 0.012,0.012,0.0013,0.0013);
  FitSigma->SetParLimits(0, 0.0001, 0.1);
  FitSigma->SetParLimits(1, 0.0003,0.02 );
  FitSigma->SetParLimits(2, 0.0001, 0.1);
  FitSigma->SetParLimits(3, 0.0003,0.02 );
  FitSigma->SetParLimits(4, 0.00001, 0.1);
  /*FitSigma->FixParameter(0, 0.01);
  FitSigma->FixParameter(1, 0.02);
  FitSigma->FixParameter(2, 0.01);
  FitSigma->FixParameter(3, 0.0);
  FitSigma->FixParameter(4, 0.0);*/

  hMean->Fit(FitMean, "SB", "", 1.0, 4.05);
  hSigma->Fit(FitSigma, "SB", "", 1.0, 4.05);
  FitMean->GetParameters(parMean);
  FitSigma->GetParameters(parSig);

  double ChisqBinMean = (FitMean->GetChisquare()/ FitMean->GetNDF());
  double ChisqBinSigma = (FitSigma->GetChisquare()/ FitSigma->GetNDF());
  for (int i = 0; i < 5; i++) {
    std::cout << Form("parMean[%d] = ",i) << parMean[i] << std::endl;
  }
  for (int i = 0; i < 2; i++) {
    std::cout << Form("parSig[%d] = ",i) << parSig[i] << std::endl;
  }
  MakeMassPlot(hMean,FitMean,"DeuteronMeanTOFMassFit",3.4 ,4,ChisqBinMean);
  MakeMassPlot(hSigma,FitSigma,"DeuteronSigmaTOFMassFit",0.0,0.5,ChisqBinSigma);
  MakeMassPlotAll(parMean,parSig,"AllFunctions",2.5,4.5);
  return;
}
