#ifdef __CLING__
#include"TF1.h"
#include"Plotstyle.h"
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
  return TMath::Exp(
      par1 * xval + par2 * xval * xval + par3 * xval * xval * xval
          + par4 * xval * xval * xval * xval) + par0;
}
double fSigma(Double_t *x, Double_t *par) {
  Float_t xval = x[0];
  Float_t par0 = par[0];  ///par[0];
  Float_t par1 = par[1];  //par[1];
  Float_t par2 = par[2];  //par[2];
  Float_t par3 = par[3];
  Float_t par4 = par[4];
  return 0.0899
      + 0.1
          * (par0 * xval + par1 * xval * xval + par2 * xval * xval * xval
              + par3 * xval * xval * xval * xval
              + par4 * xval * xval * xval * xval * xval);
}

Double_t GetDeuteronMass2Mean_pp(float pT) {

// These values were obtained by fitting the mean values of the deuteron mass2 projections calculated with the AOD dataset (2016,2017,2018)
  TF1 *fit = new TF1("fit", "[0]+[1]*pow((1-([2]/(x))),[3])", 0.6, 4.0);
  fit->FixParameter(0, 3.52478e+00);
  fit->FixParameter(1, 1.35169e-13);
  fit->FixParameter(2, -7.78509e+04);
  fit->FixParameter(3, 2.50751e+00);

  Double_t value = fit->Eval(pT);
  fit->Delete();
  return value;

}

Double_t GetDeuteronMass2Sigma_pp(float pT) {

// These values were obtained by fitting the sigma values of the deuteron mass2 projections calculated with the AOD dataset (2016,2017,2018)
  TF1 *fit = new TF1("fit",
                     "[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",
                     0.6, 4.0);
  fit->FixParameter(0, 1.03688e+00);
  fit->FixParameter(1, -2.14030e+00);
  fit->FixParameter(2, 1.86493e+00);
  fit->FixParameter(3, -7.79532e-01);
  fit->FixParameter(4, 1.58122e-01);
  fit->FixParameter(5, -1.23721e-02);

  Double_t value = fit->Eval(pT);
  fit->Delete();
  return value;

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
  return TMath::Exp(
      par1 * xval + par2 * xval * xval + par3 * xval * xval * xval
          + par4 * xval * xval * xval * xval) + par0;
}
double fSigma1(Double_t xval) {
  Float_t par0 = 1.19287e-02;
  Float_t par1 = 0.202460e-02;
  Float_t par2 = 1.23058e-02;  //par[2];
  Float_t par3 = 30.23644e-04;
  Float_t par4 = 45.80006e-05;
  return 0.088
      + 0.1
          * (par0 * xval + par1 * xval * xval + par2 * xval * xval * xval
              + par3 * xval * xval * xval * xval
              + par4 * xval * xval * xval * xval * xval);
}

void MakeMassPlot(TH1F *h, TF1 *Fit, TString name, double yRangeLow,
                  double yRangeHigh, double chisqs_NDF) {
  TCanvas *Plot = new TCanvas("Plot", "Plot", 0, 0, 800, 600);
  TString pdfMassName =
      Form(
          "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/PlotFor%s.pdf",
          name.Data());  //plots are output as .pdf If you prefer other formats simply change the ending

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

  TLegend *legPlotFu = new TLegend(0.15, 0.8, 0.3, 0.88);
  legPlotFu->SetTextSize(0.03);
  legPlotFu->AddEntry(h, "Data");
  legPlotFu->AddEntry(Fit, Form("Fit with #chi^{2}/NDF = %f", chisqs_NDF));
  legPlotFu->SetLineColor(0);
  legPlotFu->Draw("same");
  Fit->DrawCopy("same");
  Plot->Print(pdfMassName);
  delete Plot;
  delete legPlotFu;
}

void CheckGapMass(TString name, double yRangeLow, double yRangeHigh) {

  TMultiGraph *g0 = new TMultiGraph();
  TGraph *gGapUp = new TGraph();
  TGraph *gGapLow = new TGraph();

  int npoint = 0;
  for (double pt = 1.4; pt <= 4.05; pt += 0.05) {
    gGapUp->SetPoint(npoint, pt, 0.6 * fSigma1(pt));
    gGapLow->SetPoint(npoint, pt, 0.6 * fSigma1(pt));
    npoint++;
  }
  SetStyle(true);
  gStyle->SetOptStat(0);
  TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
  TString pdfMassName =
      Form(
          "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/GapInMassSquared.pdf",
          name.Data());  //plots are output as .pdf If you prefer other formats simply change the ending
  Plot->SetLeftMargin(0.12);
  Plot->SetRightMargin(0.13);
  Plot->SetTopMargin(0.9505);
  Plot->SetBottomMargin(0.135);
  // gMean->Draw("ALP");
  // gMean->SetTitleSize(0.05);
  g0->SetTitle(
      "; #it{p}_{T} (GeV/#it{c}); Gap #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2})");
  gGapLow->SetTitle(
      "; #it{p}_{T} (GeV/#it{c}); Gap #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2})");
  gGapLow->GetXaxis()->SetLabelSize(0.045);
  gGapLow->GetXaxis()->SetTitleSize(0.06);
  gGapLow->GetXaxis()->SetTitleOffset(0.89);
  gGapLow->GetYaxis()->SetTitleSize(0.05);
  gGapLow->GetYaxis()->SetTitleOffset(0.75);
  gGapLow->GetYaxis()->SetRangeUser(yRangeLow, yRangeHigh);
  gGapLow->GetXaxis()->SetRangeUser(0.0, 4.2);
  gGapLow->SetTitle(0);
  gGapLow->SetTitle(0);

  gGapLow->SetLineColor(kRed);
 // gGapLow->SetMarkerStyle(4);
  gGapLow->SetMarkerSize(1.3);
  gGapLow->SetMarkerColor(kRed);
  gGapLow->SetLineWidth(2);
  gGapLow->SetLineStyle(10);
  gGapUp->SetLineColor(kGreen);
  //gGapUp->SetMarkerStyle(4);
  gGapUp->SetLineStyle(4);
  gGapUp->SetMarkerSize(1.3);
  gGapUp->SetMarkerColor(kGreen);
  gGapUp->SetLineWidth(2);

  TLegend *legPlotFu = new TLegend(0.15, 0.75, 0.5, 0.92);
  legPlotFu->SetTextSize(0.05);
  legPlotFu->AddEntry(gGapLow, "m^{2}: Gap Lower Sideband");
  legPlotFu->AddEntry(gGapUp, "m^{2}: Gap Upper Sideband");
  legPlotFu->SetLineColor(0);

  gGapLow->Draw("ALP");
  gGapUp->Draw("ALP");
  g0->Add(gGapLow);

  g0->Add(gGapUp);
  g0->Draw("ALP");
  legPlotFu->Draw("same");

  Plot->Print(pdfMassName);

  delete Plot;
  delete gGapLow;
  delete gGapUp;
  delete g0;
  delete legPlotFu;
}

void MakeMassPlotAll(Double_t *parMean, Double_t *parSig, TString name,
                     double yRangeLow, double yRangeHigh) {

  /*TH1F*hmean;
   TH1F*hSigmaUp;
   TH1F*hSigmaLow;


   hmean  = new TH1F(Form("hmean", "hmean", 100 , 0.0, 4.1);
   hSigmaUp  = new TH1F(Form("hSigmaUp", "hSigmaUp", 100 , 0.0, 4.1);
   hSigmaLow  = new TH1F(Form("hSigmaLow", "hSigmaLow", 100 , 0.0, 4.1);*/
  std::cout << "Reached-1" << std::endl;
  TGraph *gMean = new TGraph();
  TGraph *gSigmaUp = new TGraph();
  TGraph *gSigmaLow = new TGraph();
  int npoint = 0;
  for (double pt = 0.8; pt <= 4.05; pt += 0.1) {

    gMean->SetPoint(npoint, pt, GetDeuteronMass2Mean_pp(pt));
    gSigmaUp->SetPoint(
        npoint, pt,
        GetDeuteronMass2Mean_pp(pt) + 2.0 * GetDeuteronMass2Sigma_pp(pt));
    gSigmaLow->SetPoint(
        npoint, pt,
        GetDeuteronMass2Mean_pp(pt) - 2.0 * GetDeuteronMass2Sigma_pp(pt));
    /*  gMean->SetPoint(npoint,pt,fMean1(pt));
     gSigmaUp->SetPoint(npoint,pt,fMean1(pt)+3*fSigma1(pt,0.007,0.018));
     gSigmaLow->SetPoint(npoint,pt,fMean1(pt)-3*fSigma1(pt,0.007,0.018));*/
    npoint++;
  }

  TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
  TString pdfMassName =
      Form(
          "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/PlotFor%s.pdf",
          name.Data());  //plots are output as .pdf If you prefer other formats simply change the ending
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
  gMean->GetXaxis()->SetRangeUser(0.0, 4.05);
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

  TLegend *legPlotFu = new TLegend(0.15, 0.7, 0.4, 0.88);
  legPlotFu->SetTextSize(0.03);
  legPlotFu->AddEntry(gMean, "Mean TOF Mass^{2}");
  legPlotFu->AddEntry(gSigmaUp, "gSigmaUp");
  legPlotFu->AddEntry(gSigmaLow, "gSigmaLow");
  legPlotFu->SetLineColor(0);
  std::cout << "Reached-1" << std::endl;
  gMean->Draw("ALP");
  std::cout << "Reached-2" << std::endl;
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

TH2F* MassHisto(const char *PathAnalysisFile, int Addon) {

  TString FileName = "AnalysisResults.root";
  TFile *FileData = TFile::Open(
      TString::Format("%s%s", PathAnalysisFile, FileName.Data()), "READ");
  TDirectoryFile *MyTaskDirectory1 = (TDirectoryFile*) (FileData->FindObjectAny(
      Form("HMDeuteronDCA%i", Addon)));
  TList *MyTaskList = (TList*) (MyTaskDirectory1->FindObjectAny(
      Form("HMDeuteronDCA%i", Addon)));

  TH2F *hMass1 = (TH2F*) MyTaskList->FindObject("fDeuteronRestMass");
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

void CompareMassPlotAll(const char *PathAnalysisFile, int Addon,
                        Double_t *parMean, Double_t *parSig, TString name,
                        double yRangeLow, double yRangeHigh) {

  TH2F *hMassTPCTOF = (TH2F*) MassHisto(PathAnalysisFile, Addon);
  TGraph *gMean = new TGraph();
  TGraph *gSigmaUp = new TGraph();
  TGraph *gSigmaLow = new TGraph();
  TGraph *gSidebandSigmaUp = new TGraph();
  TGraph *gSidebandSigmaLow = new TGraph();
  TGraph *gSidebandSigmaUp1 = new TGraph();
  TGraph *gSidebandSigmaLow1 = new TGraph();
  int npoint = 0;
  for (double pt = 0.8; pt <= 4.05; pt += 0.05) {

    gMean->SetPoint(npoint, pt, fMean1(pt));
    gSigmaUp->SetPoint(npoint, pt, fMean1(pt) + 3.0 * fSigma1(pt));
    gSigmaLow->SetPoint(npoint, pt, fMean1(pt) - 3.5 * fSigma1(pt));
    gSidebandSigmaUp->SetPoint(npoint, pt, fMean1(pt) + 10.1 * fSigma1(pt));
    gSidebandSigmaLow->SetPoint(npoint, pt, fMean1(pt) - 10.6 * fSigma1(pt));
    gSidebandSigmaUp1->SetPoint(npoint, pt, fMean1(pt) + 3.6 * fSigma1(pt));
    gSidebandSigmaLow1->SetPoint(npoint, pt, fMean1(pt) - 4.1 * fSigma1(pt));
    /*  gMean->SetPoint(npoint,pt,fMean1(pt));
     gSigmaUp->SetPoint(npoint,pt,fMean1(pt)+3*fSigma1(pt,0.007,0.018));
     gSigmaLow->SetPoint(npoint,pt,fMean1(pt)-3*fSigma1(pt,0.007,0.018));*/
    npoint++;
  }
  SetStyle(true);
  gStyle->SetOptStat(0);
  TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
  TString pdfMassName =
      Form(
          "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/WiderSidebandForDeuteronComparePlotFor%s.pdf",
          name.Data());  //plots are output as .pdf If you prefer other formats simply change the ending
  Plot->SetLeftMargin(0.12);
  Plot->SetRightMargin(0.13);
  Plot->SetTopMargin(0.9505);
  Plot->SetBottomMargin(0.135);
  // gMean->Draw("ALP");
  // gMean->SetTitleSize(0.05);
  hMassTPCTOF->SetTitle(
      "; #it{p}_{T} (GeV/#it{c}); #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2})");
  hMassTPCTOF->GetXaxis()->SetLabelSize(0.045);
  hMassTPCTOF->GetXaxis()->SetTitleSize(0.06);
  hMassTPCTOF->GetXaxis()->SetTitleOffset(0.89);
  hMassTPCTOF->GetYaxis()->SetTitleSize(0.05);
  hMassTPCTOF->GetYaxis()->SetTitleOffset(0.75);
  hMassTPCTOF->GetYaxis()->SetRangeUser(yRangeLow, yRangeHigh);
  hMassTPCTOF->GetXaxis()->SetRangeUser(0.0, 4.2);
  hMassTPCTOF->SetTitle(0);
  hMassTPCTOF->SetTitle(0);
  gMean->SetLineColor(kBlack);
  gMean->SetMarkerStyle(4);
  gMean->SetMarkerSize(1.3);
  gMean->SetMarkerColor(kBlack);
  gMean->SetLineWidth(2);

  gSigmaUp->SetLineColor(kRed);
  gSigmaUp->SetMarkerStyle(4);
  gSigmaUp->SetMarkerSize(1.3);
  gSigmaUp->SetMarkerColor(kRed);
  gSigmaUp->SetLineWidth(2);

  gSidebandSigmaUp->SetLineColor(kMagenta);
  gSidebandSigmaUp->SetMarkerStyle(4);
  gSidebandSigmaUp->SetMarkerSize(1.3);
  gSidebandSigmaUp->SetMarkerColor(kMagenta);
  gSidebandSigmaUp->SetLineWidth(2);

  gSidebandSigmaUp1->SetLineColor(kMagenta);
  gSidebandSigmaUp1->SetMarkerStyle(4);
  gSidebandSigmaUp1->SetMarkerSize(1.3);
  gSidebandSigmaUp1->SetMarkerColor(kMagenta);
  gSidebandSigmaUp1->SetLineWidth(2);

  gSidebandSigmaLow->SetLineColor(kOrange);
  gSidebandSigmaLow->SetMarkerStyle(4);
  gSidebandSigmaLow->SetMarkerSize(1.3);
  gSidebandSigmaLow->SetMarkerColor(kOrange);
  gSidebandSigmaLow->SetLineWidth(2);

  gSidebandSigmaLow1->SetLineColor(kOrange);
  gSidebandSigmaLow1->SetMarkerStyle(4);
  gSidebandSigmaLow1->SetMarkerSize(1.3);
  gSidebandSigmaLow1->SetMarkerColor(kOrange);
  gSidebandSigmaLow1->SetLineWidth(2);

  gSigmaLow->SetLineColorAlpha(kGreen, 0.35);
  gSigmaLow->SetMarkerStyle(4);
  gSigmaLow->SetMarkerSize(1.3);
  gSigmaLow->SetMarkerColor(kGreen);
  gSigmaLow->SetLineWidth(2);

  TLegend *legPlotFu = new TLegend(0.35, 0.7, 0.7, 0.92);
  legPlotFu->SetTextSize(0.05);
  legPlotFu->AddEntry(
      hMassTPCTOF, "m^{2}, #sqrt{#sigma^{2}_{TPC}+#sigma^{2}_{TOF}}#leq 3.0");
  legPlotFu->AddEntry(gMean, "#mu TOF m^{2}");
  legPlotFu->AddEntry(gSigmaUp, "#mu +3 #sigma");
  legPlotFu->AddEntry(gSigmaLow, "#mu -3.5 #sigma");
  legPlotFu->SetLineColor(0);
  std::cout << "Reached-1" << std::endl;

  std::cout << "Reached-2" << std::endl;
  hMassTPCTOF->Draw("colz");
  gMean->Draw("same");
  legPlotFu->Draw("same");
  gMean->Draw("same");
  gSigmaUp->Draw("same");
  gSigmaLow->Draw("same");

  gSidebandSigmaUp->Draw("same");
  gSidebandSigmaUp1->Draw("same");
  gSidebandSigmaLow->Draw("same");
  gSidebandSigmaLow1->Draw("same");

  Plot->Print(pdfMassName);

  delete Plot;
  delete gMean;
  delete gSigmaLow;
  delete gSigmaUp;
  delete legPlotFu;
}

void GetFunctionsDeuteronTOFMass() {
  TString FileNameData0, FileNameData1, FileNameData2;

  FileNameData0 =
      "/home/sbhawani/cernbox/ProtonDeuteron/AnalysisResultsRootfiles/AODs/ResultsFromAODTrain/Data/FinalCuts/FullpTRange/";
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
  TF1 *FitSigma = new TF1("FitSigma", fSigma, 1.0, 4.05, 5);

  Double_t parSig[5];
  Double_t parMean[5];
  FitMean->SetParameters(3.55, -1, -0.3, -0.2, -0.03);
  FitMean->SetParLimits(0, 3.5, 3.6);
  FitMean->SetParLimits(1, -2.0, -0.01);
  FitMean->SetParLimits(2, -0.5, -0.1);
  FitMean->SetParLimits(3, -0.5, -0.1);
  FitMean->SetParLimits(4, -0.05, -0.01);

  FitSigma->SetParameters(0.007, 0.012, 0.012, 0.0013, 0.0013);
  FitSigma->SetParLimits(0, 0.0001, 0.1);
  FitSigma->SetParLimits(1, 0.0003, 0.02);
  FitSigma->SetParLimits(2, 0.0001, 0.1);
  FitSigma->SetParLimits(3, 0.0003, 0.02);
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

  double ChisqBinMean = (FitMean->GetChisquare() / FitMean->GetNDF());
  double ChisqBinSigma = (FitSigma->GetChisquare() / FitSigma->GetNDF());
  for (int i = 0; i < 5; i++) {
    std::cout << Form("parMean[%d] = ", i) << parMean[i] << std::endl;
  }
  for (int i = 0; i < 2; i++) {
    std::cout << Form("parSig[%d] = ", i) << parSig[i] << std::endl;
  }
  //MakeMassPlot(hMean,FitMean,"DeuteronMeanTOFMassFit",3.4 ,4,ChisqBinMean);
  // MakeMassPlot(hSigma,FitSigma,"DeuteronSigmaTOFMassFit",0.0,0.5,ChisqBinSigma);
  //MakeMassPlotAll(parMean,parSig,"AllFunctions",2.5,4.5);
  CompareMassPlotAll(FileNameData0, 0, parMean, parSig, "AllFunctions", 0, 8);
  CheckGapMass("Deuteron", 0, 0.2);
  return;
}
