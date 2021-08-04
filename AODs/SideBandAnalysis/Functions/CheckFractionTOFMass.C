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

Double_t GetDeuteronMass2Mean_pp(float pT){

// These values were obtained by fitting the mean values of the deuteron mass2 projections calculated with the AOD dataset (2016,2017,2018)
  TF1 *fit = new TF1("fit","[0]+[1]*pow((1-([2]/(x))),[3])",0.6,4.0);
  fit->FixParameter(0,3.52478e+00);
  fit->FixParameter(1,1.35169e-13);
  fit->FixParameter(2,-7.78509e+04);
  fit->FixParameter(3,2.50751e+00);

  Double_t value = fit->Eval(pT);
  fit->Delete();
  return value;

}

Double_t GetDeuteronMass2Sigma_pp(float pT){

// These values were obtained by fitting the sigma values of the deuteron mass2 projections calculated with the AOD dataset (2016,2017,2018)
  TF1 *fit = new TF1("fit","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",0.6,4.0);
  fit->FixParameter(0,1.03688e+00);
  fit->FixParameter(1,-2.14030e+00);
  fit->FixParameter(2,1.86493e+00);
  fit->FixParameter(3,-7.79532e-01);
  fit->FixParameter(4,1.58122e-01);
  fit->FixParameter(5,-1.23721e-02);

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
  return TMath::Exp(par1 * xval + par2 * xval * xval+ par3 * xval * xval * xval+ par4  * xval* xval * xval * xval)+par0;
}
double fSigma1(Double_t xval) {
  Float_t par0 = 1.19287e-02;
  Float_t par1 = 0.202460e-02;
  Float_t par2 = 1.23058e-02;//par[2];
  Float_t par3 = 30.23644e-04;
  Float_t par4 = 45.80006e-05;
  return 0.088 +0.1*(par0 * xval + par1 * xval * xval + par2 * xval * xval* xval+ par3 * xval * xval* xval* xval+ par4 * xval * xval* xval* xval* xval);
}


TH2F* MassHisto(const char *PathAnalysisFile, int Addon) {

  TString FileName = "AnalysisResults.root";
  TFile *FileData = TFile::Open(TString::Format("%s%s", PathAnalysisFile,FileName.Data()), "READ");
  TDirectoryFile *MyTaskDirectory1 = (TDirectoryFile*) (FileData->FindObjectAny(Form("HMDeuteronDCA%i", Addon)));
  TList *MyTaskList= (TList*) (MyTaskDirectory1->FindObjectAny(Form("HMDeuteronDCA%i", Addon)));


  TH2F*hMass1 = (TH2F*) MyTaskList->FindObject("fDeuteronRestMass");
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

TH2F* MassHistoTPC(const char *PathAnalysisFile, int Addon) {

  TString FileName = "AnalysisResults.root";
  TFile *FileData = TFile::Open(TString::Format("%s%s", PathAnalysisFile,FileName.Data()), "READ");
  TDirectoryFile *MyTaskDirectory1 = (TDirectoryFile*) (FileData->FindObjectAny(Form("HMDeuteronMass%i", Addon)));
  TList *MyTaskList= (TList*) (MyTaskDirectory1->FindObjectAny(Form("HMDeuteronMass%i", Addon)));


  TH2F*hMass1 = (TH2F*) MyTaskList->FindObject("fDeuteronRestMassNoTOF");
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

void GetFractionofSignal(const char *PathAnalysisFile, int Addon, TString name,double yRangeLow,double yRangeHigh) {


  TH2F* hMassTPCTOF = (TH2F*)MassHisto(PathAnalysisFile,  Addon);
  TGraph*gMean =new TGraph();
  TMultiGraph*gMultRation =new TMultiGraph();
  TGraph*gRatio =new TGraph();
  TGraph*gbase =new TGraph();
  TH1F* hMassSqaured;


   SetStyle(true);
   gStyle->SetOptStat(0);


   double ptval =  0.0;
   double Intlow = 2.0;
   double Intup =  6.0;
   double IntlowCurve = 0.0;
   double IntupCruve =  0.0;
   double MassIntEntireBin = 0.0;
   double MassIntCurveBin = 0.0;
   int ptpoint = 0;
   for (Int_t PtBin = 10; PtBin < 35; PtBin++) {



     Double_t BinLowerEdge = hMassTPCTOF->GetXaxis()->GetBinLowEdge(PtBin);
     Double_t BinUpperEdge = hMassTPCTOF->GetXaxis()->GetBinUpEdge(PtBin);
     hMassSqaured = (TH1F*)(hMassTPCTOF->ProjectionY("Projected", PtBin,PtBin ));

     TAxis *axis = hMassSqaured->GetXaxis();
     int bmin = axis->FindBin(Intlow);
     int bmax = axis->FindBin(Intup);
     MassIntEntireBin = hMassSqaured->Integral(bmin,bmax);
     //MassIntEntireBin -= hMassSqaured->GetBinContent(bmin)*(Intlow-axis->GetBinLowEdge(bmin))/axis->GetBinWidth(bmin);
    // MassIntEntireBin -= hMassSqaured->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-Intup)/axis->GetBinWidth(bmax);

     ptval  = hMassTPCTOF->GetXaxis()->GetBinCenter(PtBin);

     IntlowCurve  = fMean1(ptval)-3.5*fSigma1(ptval);
     IntupCruve   = fMean1(ptval)+3.0*fSigma1(ptval);



     int cbmin = axis->FindBin(IntlowCurve);
     int cbmax = axis->FindBin(IntupCruve);

     MassIntCurveBin = hMassSqaured->Integral(cbmin,cbmax);
    // MassIntCurveBin -= hMassSqaured->GetBinContent(cbmin)*(Intlow-axis->GetBinLowEdge(cbmin))/axis->GetBinWidth(cbmin);
    // MassIntCurveBin -= hMassSqaured->GetBinContent(cbmax)*(axis->GetBinUpEdge(cbmax)-Intup)/axis->GetBinWidth(cbmax);
     std::cout << "*******************************" << std::endl;
     std::cout << "Counting in pT bin: " << PtBin << "ptVal "<< ptval << std::endl;
     std::cout << "Values: " <<MassIntCurveBin/MassIntEntireBin *100 << std::endl;
     std::cout << "*******************************" << std::endl;
    //MassIntEntireBin = hMassSqaured->Integral(Intlow, Intup, 0.001) / (hMassSqaured->GetXaxis()->GetBinWidth(1));
   // MassIntCurveBin = hMassSqaured->Integral(IntlowCurve, IntupCruve, 0.001) / (hMassSqaured->GetXaxis()->GetBinWidth(1));
    gbase->SetPoint(ptpoint,ptval,100.0);
    gRatio->SetPoint(ptpoint,ptval,MassIntCurveBin/MassIntEntireBin *100);
    ptpoint++;
   }

    TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
    TString pdfMassName = Form("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/ChcekFractionForDeuteronPlotFor%s.pdf", name.Data()); //plots are output as .pdf If you prefer other formats simply change the ending
    Plot->SetLeftMargin(0.12);
    Plot->SetRightMargin(0.13);
    Plot->SetTopMargin(0.9505);
    Plot->SetBottomMargin(0.135);
    gMultRation->SetTitle("; #it{p}_{T} (GeV/#it{c}); Ratio");
    //gRatio->GetXaxis()->SetLabelSize(0.045);
   // gRatio->GetXaxis()->SetTitleSize(0.06);
   // gRatio->GetXaxis()->SetTitleOffset(0.89);
   // gRatio->GetYaxis()->SetTitleSize(0.05);
   // gRatio->GetYaxis()->SetTitleOffset(0.75);
    gRatio->GetYaxis()->SetRangeUser(0, 102);
    gRatio->GetXaxis()->SetRangeUser(1.4, 4.2);
    gRatio->SetTitle(0);
    gRatio->SetTitle(0);
    gRatio->SetLineColor(kBlue);
    gRatio->SetLineColor(kBlue);
    gRatio->SetMarkerStyle(8);
    gRatio->SetMarkerSize(1.3);
    gRatio->SetMarkerColor(kBlue);
    gRatio->SetLineWidth(2);
    gRatio->SetLineStyle(8);

    gbase->SetLineColor(kRed);
    gbase->SetLineColor(kRed);
    gbase->SetMarkerStyle(8);
    gbase->SetMarkerSize(1.3);
    gbase->SetMarkerColor(kRed);
    gbase->SetLineWidth(2);
    gbase->GetYaxis()->SetRangeUser(0, 102);
    gbase->GetXaxis()->SetRangeUser(1.4, 4.2);
    gMultRation->GetYaxis()->SetRange(0, 102);
    gMultRation->GetXaxis()->SetRangeUser(1.4, 4.2);
    TLegend *legPlotFu = new TLegend( 0.2, 0.3, 0.5, 0.5);
    legPlotFu->SetTextSize(0.05);
    legPlotFu->AddEntry(gRatio, "m^{2}_{TOF}:  \mu -3.5\sigma  \leg signal \leq \mu +3.0 \sigma");
    legPlotFu->AddEntry(gbase, "m^{2}_{TOF} : #sqrt{N\sigma_{TPC}^2}+N\sigma_{TPC}^2}}\leq 3.0");
    //legPlotFu->AddEntry(gMean, "#mu TOF m^{2}");
  //  legPlotFu->AddEntry(gSigmaUp, "#mu +3 #sigma");
  //  legPlotFu->AddEntry(gSigmaLow, "#mu -3.5 #sigma");
    legPlotFu->SetLineColor(0);
    std::cout<<"Reached-1"<<std::endl;

    std::cout<<"Reached-2"<<std::endl;
    gMultRation->Add(gRatio);
    gMultRation->Add(gbase);

    gRatio->Draw("2AP");
    gbase->Draw("2AP SAME");
    gMultRation->Draw("ACP");
    legPlotFu->Draw("same");
    //gRatio->Draw("2AP");
   // gbase->Draw("2AP SAME");
   // gMean->Draw("same");
   // legPlotFu->Draw("same");
   // gMean->Draw("same");
   // gSigmaUp->Draw("same");
   // gSigmaLow->Draw("same");

    Plot->Print(pdfMassName);

    delete Plot;
    delete gRatio;
    delete legPlotFu;
}
void CompareM2plot(const char *PathAnalysisFile, int Addon, TString name) {


  TH2F* hMassTPCTOF = (TH2F*)MassHisto(PathAnalysisFile,  Addon);
  TH2F* hMassTPC = (TH2F*)MassHistoTPC(PathAnalysisFile,  Addon);


  TH1F* hMassSqauredTPCTOF;
  TH1F* hMassSqauredTPC;


   SetStyle(true);
   gStyle->SetOptStat(0);

    Double_t BinLowerEdge = hMassTPCTOF->GetXaxis()->GetBinLowEdge(9);
    Double_t BinUpperEdge = hMassTPCTOF->GetXaxis()->GetBinUpEdge(34);
    hMassSqauredTPCTOF = (TH1F*)(hMassTPCTOF->ProjectionY("hMassSqauredTPCTOF", 9,34));
    hMassSqauredTPC = (TH1F*)(hMassTPC->ProjectionY("hMassSqauredTPC", 9, 34));

    TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
    TString pdfMassName = Form("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/ComparedM2TPCandM2TOFDeuteronPlotFor%s.pdf", name.Data()); //plots are output as .pdf If you prefer other formats simply change the ending
    Plot->SetLeftMargin(0.15);
    Plot->SetRightMargin(0.05);
    Plot->SetTopMargin(0.9005);
    Plot->SetBottomMargin(0.135);

    hMassSqauredTPCTOF->SetTitle("; #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2}); Counts");

    hMassSqauredTPCTOF->GetXaxis()->SetLabelSize(0.045);
    //hMassSqauredTPCTOF->GetYaxis()->SetLabelSize(0.045);
    hMassSqauredTPCTOF->GetXaxis()->SetTitleSize(0.06);
    hMassSqauredTPCTOF->GetXaxis()->SetTitleOffset(0.89);
   // hMassSqauredTPCTOF->GetYaxis()->SetTitleSize(0.045);
   // hMassSqauredTPCTOF->GetYaxis()->SetTitleOffset(0.0);
    hMassSqauredTPCTOF->GetYaxis()->SetRangeUser(0, 30000);
    hMassSqauredTPCTOF->GetXaxis()->SetRangeUser(1.0, 6.0);
    hMassSqauredTPCTOF->SetTitle(0);
    hMassSqauredTPCTOF->SetTitle(0);
    hMassSqauredTPCTOF->SetLineColor(kBlue);
    hMassSqauredTPCTOF->SetLineColor(kBlue);
    hMassSqauredTPCTOF->SetMarkerStyle(8);
    hMassSqauredTPCTOF->SetMarkerSize(0.8);
    hMassSqauredTPCTOF->SetMarkerColor(kBlue);
    hMassSqauredTPCTOF->SetLineWidth(2);
   // hMassSqauredTPCTOF->SetLineStyle(8);

    hMassSqauredTPC->SetLineColor(kRed);
    hMassSqauredTPC->SetLineColor(kRed);
    hMassSqauredTPC->SetMarkerStyle(8);
    hMassSqauredTPC->SetMarkerSize(0.8);
    hMassSqauredTPC->SetMarkerColor(kRed);
    hMassSqauredTPC->SetLineWidth(2);
    hMassSqauredTPC->GetYaxis()->SetRangeUser(0, 30000);
    hMassSqauredTPC->GetXaxis()->SetRangeUser(1.0, 6.0);
    TLegend *legPlotFu = new TLegend( 0.6, 0.65, 0.75, 0.8);
    legPlotFu->SetTextSize(0.05);
    legPlotFu->AddEntry(hMassSqauredTPCTOF, "m^{2} TPC+TOF");
    legPlotFu->AddEntry(hMassSqauredTPC, "m^{2} TPC Only");
    legPlotFu->SetLineColor(0);

    hMassSqauredTPCTOF->Draw("");
    hMassSqauredTPC->Draw("same");
    legPlotFu->Draw("same");

    Plot->Print(pdfMassName);

    delete Plot;
   // delete hMassSqauredTPCTOF;
   // delete hMassSqauredTPCTOF;
    delete legPlotFu;
}
//Just to check if michael does correct!
void MakeMichaelMassPlotAll(const char *PathAnalysisFile, int Addon, TString name,double yRangeLow,double yRangeHigh) {


  TH2F* hMassTPCTOF = (TH2F*)MassHisto(PathAnalysisFile,  Addon);
  TGraph*gMean =new TGraph();
  TGraph*gSigmaUp =new TGraph();
  TGraph*gSigmaLow =new TGraph();
  TGraph*gSidebandSigmaUp =new TGraph();
  TGraph*gSidebandSigmaLow =new TGraph();
  TGraph*gSidebandSigmaUp1 =new TGraph();
  TGraph*gSidebandSigmaLow1 =new TGraph();
 int npoint = 0;
   for(double pt = 0.8;pt<= 4.05; pt+=0.05){

     gMean->SetPoint(npoint,pt,GetDeuteronMass2Mean_pp(pt));
     gSigmaUp->SetPoint(npoint,pt,GetDeuteronMass2Mean_pp(pt)+3.0*GetDeuteronMass2Sigma_pp(pt));
     gSigmaLow->SetPoint(npoint,pt,GetDeuteronMass2Mean_pp(pt)-3.0*GetDeuteronMass2Sigma_pp(pt));
     gSidebandSigmaUp->SetPoint(npoint,pt,fMean1(pt)+6.5*fSigma1(pt));
     gSidebandSigmaLow->SetPoint(npoint,pt,fMean1(pt)-7.4*fSigma1(pt));
     gSidebandSigmaUp1->SetPoint(npoint,pt,fMean1(pt)+3.6*fSigma1(pt));
     gSidebandSigmaLow1->SetPoint(npoint,pt,fMean1(pt)-4.1*fSigma1(pt));
   /*  gMean->SetPoint(npoint,pt,fMean1(pt));
     gSigmaUp->SetPoint(npoint,pt,fMean1(pt)+3*fSigma1(pt,0.007,0.018));
     gSigmaLow->SetPoint(npoint,pt,fMean1(pt)-3*fSigma1(pt,0.007,0.018));*/
     npoint++;
   }
   SetStyle(true);
   gStyle->SetOptStat(0);
    TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
    TString pdfMassName = Form("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/MichaelFinalForDeuteronComparePlotFor%s.pdf", name.Data()); //plots are output as .pdf If you prefer other formats simply change the ending
    Plot->SetLeftMargin(0.12);
    Plot->SetRightMargin(0.13);
    Plot->SetTopMargin(0.9505);
    Plot->SetBottomMargin(0.135);
   // gMean->Draw("ALP");
   // gMean->SetTitleSize(0.05);
    hMassTPCTOF->SetTitle("; #it{p}_{T} (GeV/#it{c}); #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2})");
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

    TLegend *legPlotFu = new TLegend( 0.35, 0.7, 0.7, 0.92);
    legPlotFu->SetTextSize(0.05);
    legPlotFu->AddEntry(hMassTPCTOF, "m^{2}, #sqrt{#sigma^{2}_{TPC}+#sigma^{2}_{TOF}}#leq 3.0");
    legPlotFu->AddEntry(gMean, "#mu TOF m^{2}");
    legPlotFu->AddEntry(gSigmaUp, "#mu +3 #sigma");
    legPlotFu->AddEntry(gSigmaLow, "#mu -3.0 #sigma");
    legPlotFu->SetLineColor(0);
    std::cout<<"Reached-1"<<std::endl;

    std::cout<<"Reached-2"<<std::endl;
    hMassTPCTOF->Draw("colz");
    gMean->Draw("same");
    legPlotFu->Draw("same");
    gMean->Draw("same");
    gSigmaUp->Draw("same");
    gSigmaLow->Draw("same");

  //  gSidebandSigmaUp->Draw("same");
   // gSidebandSigmaUp1->Draw("same");
  // // gSidebandSigmaLow->Draw("same");
  //  gSidebandSigmaLow1->Draw("same");

    Plot->Print(pdfMassName);


    delete Plot;
    delete gMean;
    delete gSigmaLow;
    delete gSigmaUp;
    delete legPlotFu;
}


void GetMichaelFractionofSignal(const char *PathAnalysisFile, int Addon, TString name,double yRangeLow,double yRangeHigh) {


  TH2F* hMassTPCTOF = (TH2F*)MassHisto(PathAnalysisFile,  Addon);
  TMultiGraph*gMultRation =new TMultiGraph();
  TGraph*gRatio =new TGraph();
  TGraph*gRatioM =new TGraph();
  TGraph*gbase =new TGraph();
  TH1F* hMassSqaured;


   SetStyle(true);
   gStyle->SetOptStat(0);


   double ptval =  0.0;
   double Intlow = 2.0;
   double Intup =  6.0;
   double IntlowCurve = 0.0;
   double IntupCruve =  0.0;
   double IntlowCurveM = 0.0;
   double IntupCruveM =  0.0;
   double MassIntEntireBin = 0.0;
   double MassIntCurveBin = 0.0;
   double MassIntCurveBinM = 0.0;
   int ptpoint = 0;
   for (Int_t PtBin = 10; PtBin < 35; PtBin++) {



     Double_t BinLowerEdge = hMassTPCTOF->GetXaxis()->GetBinLowEdge(PtBin);
     Double_t BinUpperEdge = hMassTPCTOF->GetXaxis()->GetBinUpEdge(PtBin);
     hMassSqaured = (TH1F*)(hMassTPCTOF->ProjectionY("Projected", PtBin,PtBin ));

     TAxis *axis = hMassSqaured->GetXaxis();
     int bmin = axis->FindBin(Intlow);
     int bmax = axis->FindBin(Intup);
     MassIntEntireBin = hMassSqaured->Integral(bmin,bmax);
     //MassIntEntireBin -= hMassSqaured->GetBinContent(bmin)*(Intlow-axis->GetBinLowEdge(bmin))/axis->GetBinWidth(bmin);
    // MassIntEntireBin -= hMassSqaured->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-Intup)/axis->GetBinWidth(bmax);

     ptval  = hMassTPCTOF->GetXaxis()->GetBinCenter(PtBin);

     IntlowCurveM  = GetDeuteronMass2Mean_pp(ptval)-3.0*GetDeuteronMass2Sigma_pp(ptval);
     IntupCruveM   = GetDeuteronMass2Mean_pp(ptval)+3.0*GetDeuteronMass2Sigma_pp(ptval);

     IntlowCurve  = fMean1(ptval)-3.5*fSigma1(ptval);
     IntupCruve   = fMean1(ptval)+3.0*fSigma1(ptval);



     int cbmin = axis->FindBin(IntlowCurve);
     int cbmax = axis->FindBin(IntupCruve);

     int cbminM = axis->FindBin(IntlowCurveM);
     int cbmaxM = axis->FindBin(IntupCruveM);

     MassIntCurveBin = hMassSqaured->Integral(cbmin,cbmax);
     MassIntCurveBinM = hMassSqaured->Integral(cbminM,cbmaxM);
    // MassIntCurveBin -= hMassSqaured->GetBinContent(cbmin)*(Intlow-axis->GetBinLowEdge(cbmin))/axis->GetBinWidth(cbmin);
    // MassIntCurveBin -= hMassSqaured->GetBinContent(cbmax)*(axis->GetBinUpEdge(cbmax)-Intup)/axis->GetBinWidth(cbmax);
     std::cout << "*******************************" << std::endl;
     std::cout << "Counting in pT bin: " << PtBin << "ptVal "<< ptval << std::endl;
     std::cout << "Values: " <<MassIntCurveBin/MassIntEntireBin *100 << std::endl;
     std::cout << "*******************************" << std::endl;
    //MassIntEntireBin = hMassSqaured->Integral(Intlow, Intup, 0.001) / (hMassSqaured->GetXaxis()->GetBinWidth(1));
   // MassIntCurveBin = hMassSqaured->Integral(IntlowCurve, IntupCruve, 0.001) / (hMassSqaured->GetXaxis()->GetBinWidth(1));
    gbase->SetPoint(ptpoint,ptval,100.0);
    gRatio->SetPoint(ptpoint,ptval,MassIntCurveBin/MassIntEntireBin *100);
    gRatioM->SetPoint(ptpoint,ptval,MassIntCurveBinM/MassIntEntireBin *100);
    ptpoint++;
   }

    TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
    TString pdfMassName = Form("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/MichaelChcekFractionForDeuteronPlotFor%s.pdf", name.Data()); //plots are output as .pdf If you prefer other formats simply change the ending
    Plot->SetLeftMargin(0.12);
    Plot->SetRightMargin(0.13);
    Plot->SetTopMargin(0.9505);
    Plot->SetBottomMargin(0.135);
    gMultRation->SetTitle("; #it{p}_{T} (GeV/#it{c}); Ratio");
    //gRatio->GetXaxis()->SetLabelSize(0.045);
   // gRatio->GetXaxis()->SetTitleSize(0.06);
   // gRatio->GetXaxis()->SetTitleOffset(0.89);
   // gRatio->GetYaxis()->SetTitleSize(0.05);
   // gRatio->GetYaxis()->SetTitleOffset(0.75);
    gRatio->GetYaxis()->SetRangeUser(0, 102);
    gRatio->GetXaxis()->SetRangeUser(1.4, 4.2);
    gRatio->SetTitle(0);
    gRatio->SetTitle(0);
    gRatio->SetLineColor(kBlue);
    gRatio->SetLineColor(kBlue);
    gRatio->SetMarkerStyle(8);
    gRatio->SetMarkerSize(1.3);
    gRatio->SetMarkerColor(kBlue);
    gRatio->SetLineWidth(2);
    gRatio->SetLineStyle(8);

    gRatioM->SetLineColor(kBlack);
    gRatioM->SetLineColor(kBlack);
    gRatioM->SetMarkerStyle(8);
    gRatioM->SetMarkerSize(1.3);
    gRatioM->SetMarkerColor(kBlack);
    gRatioM->SetLineWidth(2);
    gRatioM->SetLineStyle(8);


    gbase->SetLineColor(kRed);
    gbase->SetLineColor(kRed);
    gbase->SetMarkerStyle(8);
    gbase->SetMarkerSize(1.3);
    gbase->SetMarkerColor(kRed);
    gbase->SetLineWidth(2);
    gbase->GetYaxis()->SetRange(0.0, 102);
    gRatio->GetYaxis()->SetRange(0.0, 102);
    gbase->GetXaxis()->SetRangeUser(1.4, 4.2);
    gMultRation->GetYaxis()->SetRange(0.0, 102);
    gMultRation->GetXaxis()->SetRangeUser(1.4, 4.2);
    TLegend *legPlotFu = new TLegend( 0.15, 0.3, 0.5, 0.5);
    legPlotFu->SetTextSize(0.05);
    legPlotFu->AddEntry(gRatio, "m^{2}_{TOF}:  #mu -3.5#sigma  #leq signal #leq #mu +3.0 #sigma");
    legPlotFu->AddEntry(gbase, "m^{2}_{TOF} : #sqrt{N#sigma_{TPC}^2+N#sigma_{TPC}^2}}#leq 3.0");
   // legPlotFu->AddEntry(gRatioM, "Ratio Michael");
    //legPlotFu->AddEntry(gbase, "100%");
    //legPlotFu->AddEntry(gMean, "#mu TOF m^{2}");
  //  legPlotFu->AddEntry(gSigmaUp, "#mu +3 #sigma");
  //  legPlotFu->AddEntry(gSigmaLow, "#mu -3.5 #sigma");
    legPlotFu->SetLineColor(0);
    std::cout<<"Reached-1"<<std::endl;

    std::cout<<"Reached-2"<<std::endl;
    gMultRation->Add(gRatio);
    gMultRation->Add(gbase);
   // gMultRation->Add(gRatioM);

    gRatio->Draw("2AP");
    gbase->Draw("2AP SAME");
    gMultRation->Draw("ACP");
    legPlotFu->Draw("same");
    //gRatio->Draw("2AP");
   // gbase->Draw("2AP SAME");
   // gMean->Draw("same");
   // legPlotFu->Draw("same");
   // gMean->Draw("same");
   // gSigmaUp->Draw("same");
   // gSigmaLow->Draw("same");

    Plot->Print(pdfMassName);

    delete Plot;
    delete gRatio;
    delete gRatioM;
    delete legPlotFu;
}





void M2plotTPCTOF(const char *PathAnalysisFile, int Addon, TString name) {

  TH2F* hMassTPCTOF = (TH2F*)MassHisto(PathAnalysisFile,  Addon);
   SetStyle(true);
   gStyle->SetOptStat(0);


    TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
    TString pdfMassName = Form("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/M2TPCandTOFDeuteronPlotFor%s.pdf", name.Data()); //plots are output as .pdf If you prefer other formats simply change the ending
    Plot->SetLeftMargin(0.15);
    Plot->SetRightMargin(0.12);
    Plot->SetTopMargin(0.9005);
    Plot->SetBottomMargin(0.135);
    hMassTPCTOF->GetXaxis()->SetTitle(0);
    hMassTPCTOF->GetYaxis()->SetTitle(0);
    hMassTPCTOF->SetTitle(";#it{p}_{T}(GeV/#it{c}); #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2})");

    hMassTPCTOF->GetXaxis()->SetLabelSize(0.045);
    hMassTPCTOF->GetYaxis()->SetLabelSize(0.045);
    hMassTPCTOF->GetXaxis()->SetTitleSize(0.06);
    hMassTPCTOF->GetXaxis()->SetTitleOffset(0.89);
    hMassTPCTOF->GetYaxis()->SetTitleSize(0.045);
    hMassTPCTOF->GetYaxis()->SetTitleOffset(0.0);
    hMassTPCTOF->GetYaxis()->SetRangeUser(1.5, 6);
    hMassTPCTOF->GetXaxis()->SetRangeUser(0.5, 4.3);
    hMassTPCTOF->SetTitle(0);

    TLegend *legPlotFu = new TLegend( 0.6, 0.65, 0.75, 0.8);
    legPlotFu->SetTextSize(0.05);
    //legPlotFu->AddEntry(nullptr, "m^{2} TPC+TOF");
    legPlotFu->SetLineColor(0);

    hMassTPCTOF->Draw("colz");
   // legPlotFu->Draw("same");

    Plot->Print(pdfMassName);

    delete Plot;
    delete legPlotFu;
}
void M2plotTPC(const char *PathAnalysisFile, int Addon, TString name) {


  TH2F* hMassTPC = (TH2F*)MassHistoTPC(PathAnalysisFile,  Addon);
   SetStyle(true);
   gStyle->SetOptStat(0);


    TCanvas *Plot = new TCanvas("cPlot", "cPlot", 0, 0, 900, 600);
    TString pdfMassName = Form("/home/sbhawani/cernbox/ProtonDeuteron/Outputs/AODs/SideBandAnalysis/Functions/M2TPCDeuteronPlotFor%s.pdf", name.Data()); //plots are output as .pdf If you prefer other formats simply change the ending
    Plot->SetLeftMargin(0.15);
    Plot->SetRightMargin(0.12);
    Plot->SetTopMargin(0.9005);
    Plot->SetBottomMargin(0.135);
    hMassTPC->GetXaxis()->SetTitle(0);
    hMassTPC->GetYaxis()->SetTitle(0);
    hMassTPC->SetTitle(";#it{p}_{T}(GeV/#it{c}); #it{m}_{TOF}^{2}(GeV^{2}/#it{c}^{2})");

    hMassTPC->GetXaxis()->SetLabelSize(0.045);
    hMassTPC->GetYaxis()->SetLabelSize(0.045);
    hMassTPC->GetXaxis()->SetTitleSize(0.06);
    hMassTPC->GetXaxis()->SetTitleOffset(0.89);
    hMassTPC->GetYaxis()->SetTitleSize(0.045);
    hMassTPC->GetYaxis()->SetTitleOffset(0.0);
    hMassTPC->GetYaxis()->SetRangeUser(1.5, 6);
    hMassTPC->GetXaxis()->SetRangeUser(0.5, 4.3);
    hMassTPC->SetTitle(0);

    TLegend *legPlotFu = new TLegend( 0.6, 0.65, 0.75, 0.8);
    legPlotFu->SetTextSize(0.05);
   // legPlotFu->AddEntry(TObject(), "m^{2} TPC+TOF");
    legPlotFu->SetLineColor(0);

    hMassTPC->Draw("colz");
    //legPlotFu->Draw("same");

    Plot->Print(pdfMassName);

    delete Plot;
    delete legPlotFu;
}
void CheckFractionTOFMass() {
  TString FileNameData0,FileNameData1, FileNameData2;

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
  //hMean->Draw("hist P");
  if (!hSigma) {
    std::cout << "No hSigma" << std::endl;
    return;
  }
  if (!hMean) {
    std::cout << "No hMean" << std::endl;
    return;
  }

  GetFractionofSignal(FileNameData0,0,"AllFunctions",0,105);
  GetMichaelFractionofSignal(FileNameData0,0,"Micheal",0,105);
  CompareM2plot(FileNameData0,0,"AllFunctions");
  M2plotTPCTOF(FileNameData0,0,"TPCTOF");
  M2plotTPC(FileNameData0,0,"TPC");
  MakeMichaelMassPlotAll(FileNameData0,0,"AllFunctions",1.5,6);
  return;
}
