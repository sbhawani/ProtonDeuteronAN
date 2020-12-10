Double_t gaussian(Double_t *x, Double_t *par) {

  Float_t xval = x[0];
  Float_t par0 = par[0];
  Float_t par1 = par[1];
  Float_t par2 = par[2];
  return par0 * TMath::Gaus(xval, par1, par2);
}

Double_t gaussianSignal(Double_t *x, Double_t *par) {

  Float_t xval = x[0];
  Float_t par0 = par[0];
  Float_t par1 = par[1];
  Float_t par2 = par[2];
  Float_t par3 = par[3];
  if (xval < par1 + par3 * par2) {
    return par0 * 1
        / (TMath::Sqrt(0.5 * TMath::Pi())
            * (par2 + par2 * TMath::Erf(par3 / TMath::Sqrt(2)))
            + par2 / par3 * TMath::Exp(-par3 * par3 / 2))
        * TMath::Exp(-(xval - par1) * (xval - par1) / 2 / par2 / par2);
  } else {
    return par0 * 1
        / (TMath::Sqrt(0.5 * TMath::Pi())
            * (par2 + par2 * TMath::Erf(par3 / TMath::Sqrt(2)))
            + par2 / par3 * TMath::Exp(-par3 * par3 / 2))
        * TMath::Exp(-(xval - par1 - par3 * par2 * 0.5) * par3 / par2);
  }
}

Double_t background(Double_t *x, Double_t *par) {
  Float_t xval = x[0];
  Float_t par0 = par[0];
  Float_t par1 = par[1];
  Float_t par2 = par[2];
  return par0 * TMath::Exp(par1 * xval + par2 * xval * xval);
}

Double_t MassFitFunction(Double_t *x, Double_t *par) {
  return gaussianSignal(x, par) + background(x, &par[4]);
}

void MakeMassPlot(TString FolderName, TString Filename, TH1F *Mass2sq,
                  TF1 *Mass_Signal, TF1 *Mass_Background, TString PtRangeName,
                  float PurityPtbin) {
  TLatex ptBinRange;
  TLatex Purity;
  TCanvas *MassPlot = new TCanvas("MassPlot", "MassPlot", 0, 0, 800, 600);
  TString pdfMassName = Form("%s%s.pdf", FolderName.Data(), Filename.Data());  //plots are output as .pdf If you prefer other formats simply change the ending
  //gPad->SetLogy();

  Mass2sq->Draw("ep");
  Mass2sq->SetTitleSize(0.05);
  Mass2sq->GetXaxis()->SetLabelSize(0.045);
  Mass2sq->GetXaxis()->SetTitleSize(0.05);
  Mass2sq->GetXaxis()->SetTitleOffset(0.89);
  Mass2sq->GetXaxis()->SetTitle("m^{2}_{d} (GeV/#it{c}^{2})^{2}");
  Mass2sq->GetYaxis()->SetLabelSize(0.035);
  Mass2sq->GetYaxis()->SetTitleSize(0.05);
  Mass2sq->GetYaxis()->SetTitleOffset(0.95);
  Mass2sq->GetYaxis()->SetTitle("#it{Counts}");
  Mass2sq->SetLineColorAlpha(kBlue, 0.35);
  Mass2sq->SetMarkerStyle(4);
  Mass2sq->SetMarkerSize(1.3);
  Mass2sq->SetMarkerColor(kBlue + 1);
  Mass2sq->SetLineWidth(2);
  Mass2sq->GetXaxis()->SetRangeUser(2.8, 4.3);
  ptBinRange.SetNDC(kTRUE);
  ptBinRange.SetTextSize(0.035);
  ptBinRange.DrawLatex(.15, .7, PtRangeName);
  Purity.SetNDC(kTRUE);
  Purity.SetTextSize(0.035);
  Purity.DrawLatex(.15, .6, Form("Signal %0.2f%s", PurityPtbin * 100, "%"));
  TLegend *legPlotFu = new TLegend(0.15, 0.8, 0.3, 0.88);
  legPlotFu->SetTextSize(0.03);
  legPlotFu->AddEntry(Mass_Signal, "Signal");
  legPlotFu->AddEntry(Mass_Background, "BackGr");
  legPlotFu->SetLineColor(0);
  legPlotFu->Draw("same");
  Mass_Signal->DrawCopy("same");
  Mass_Background->DrawCopy("same");

  MassPlot->Print(pdfMassName);
  delete MassPlot;
}

void MassFitDeuteron(TString FolderName, TString Filename, TH1F *histo,
                     TF1 *Signal, TF1 *BackGr, TString PtRangeName) {

  std::cout << "Okay Lets Fit " << std::endl;
  TF1 *MassFit = new TF1("MassFit", MassFitFunction, 2.8, 4.3, 7);

  Double_t par[7];
  Double_t parSig[4];
  Double_t parBackGr[3];

  MassFit->SetParameters(600.5, 3.532, 0.1881, 0.6771, 32150, -3.372, 0.09);
  MassFit->SetParLimits(0, 20, 4800);
  MassFit->SetParLimits(1, 3.2, 4.3);
  MassFit->SetParLimits(2, 0.0001, 0.8);
  MassFit->SetParLimits(3, 0.1, 9.8);
  MassFit->SetParLimits(4, 0.02, 30000);
  MassFit->SetParLimits(5, -10, 2);
  MassFit->SetParLimits(6, -9, 4);

  TFitter::SetPrecision(10);
  MassFit->SetLineColor(kBlack);

  TFitResultPtr Result;
  gStyle->SetOptFit(1111);
  Result = histo->Fit(MassFit, "SB", "", 2.8, 4.5);
  histo->GetYaxis()->SetTitle("Counts");
  if (Signal && BackGr) {
    std::cout << "*******************************" << std::endl;
    std::cout << "Mass fit works **************** " << std::endl;
    std::cout << "*******************************" << std::endl;
  }
  MassFit->GetParameters(par);
  Signal->SetParameters(par);
  BackGr->SetParameters(&par[4]);
  Signal->SetLineColor(30);
  if (!BackGr) {
    std::cout << "*******************************" << std::endl;
    std::cout << "No BackGr **************** " << std::endl;
    std::cout << "*******************************" << std::endl;
  }
  if (!Signal) {
    std::cout << "*******************************" << std::endl;
    std::cout << "No Signal **************** " << std::endl;
    std::cout << "*******************************" << std::endl;
  }
  Double_t MassFitInt = 0;
  Double_t SignalInt = 0;
  Double_t sigma;
  Double_t gaussmean;
  sigma = par[2];
  gaussmean = par[1];

  Double_t Intlow = gaussmean - (3 * sigma);
  Double_t Intup = gaussmean + (3 * sigma);

  Double_t ChisqBin;
  ChisqBin = MassFit->GetChisquare() / MassFit->GetNDF();
  //calculation of Signal and respective error
  Double_t PurityPtbin;
  SignalInt = Signal->Integral(Intlow, Intup, 0.001)
      / (histo->GetXaxis()->GetBinWidth(1));
  MassFitInt = MassFit->Integral(Intlow, Intup, 0.001)
      / (histo->GetXaxis()->GetBinWidth(1));
  if (!(MassFitInt == 0))
    PurityPtbin = SignalInt / MassFitInt;
  Double_t errGlobal = MassFit->IntegralError(Intlow, Intup);
  Double_t errSignal1 = Signal->IntegralError(Intlow, Intup);
  Double_t RelError1;
  std::cout << "RelError"
      << TMath::Sqrt(
          (errSignal1 / SignalInt) * (errSignal1 / SignalInt)
              + (errGlobal / MassFitInt) * (errGlobal / MassFitInt))
      << std::endl;
  std::cout << "Purity" << PurityPtbin * 100 << std::endl;
  MakeMassPlot(FolderName, Filename, histo, Signal, BackGr, PtRangeName,
               PurityPtbin);
  return;
}

void EstimateDeuteronBackground(TString Name, TString FolderName,
                                TString Filename, TH2F *Mass2sqData) {
  TH1F *Mass2sq;
  TString PtRangeName;
  TF1 *Mass_Signal;
  TF1 *Mass_Background;
  Mass_Signal = new TF1("Signal", gaussianSignal, 2.5, 4.5, 4);
  Mass_Background = new TF1("BackGr", background, 2.5, 4.5, 3);

  std::cout << "*******************************" << std::endl;
  std::cout << "Mass fit of PtBin: " << std::endl;
  std::cout << Name.Data() << std::endl;
  std::cout << "*******************************" << std::endl;

  // TString MassName = Form("%s Bin %d", Name.Data(), PtBin);
  Double_t BinLowerEdge = Mass2sqData->GetXaxis()->GetBinLowEdge(10);
  Double_t BinUpperEdge = Mass2sqData->GetXaxis()->GetBinLowEdge(35);
  PtRangeName = Form("%1.2f< #it{p}_{T} <%1.2f", BinLowerEdge, BinUpperEdge);
  Mass2sq = (TH1F*) (Mass2sqData->ProjectionY(Name.Data(), 10, 35));
  std::cout << "**************Reached*****************" << std::endl;
  MassFitDeuteron(FolderName, Filename, Mass2sq, Mass_Signal, Mass_Background,
                  PtRangeName);
  return;
}

void EstimateDeuteronSBWeights(TString Name,TH2F *Mass2sqDataLSB,
                               TH2F *Mass2sqDataRSB) {
  TH1F *Mass2sqLSB;
  TH1F *Mass2sqRSB;
  TString PtRangeName;

  Double_t BinLowerEdge = Mass2sqDataLSB->GetXaxis()->GetBinLowEdge(10);
  Double_t BinUpperEdge = Mass2sqDataLSB->GetXaxis()->GetBinLowEdge(35);
  PtRangeName = Form("%1.2f< #it{p}_{T} <%1.2f", BinLowerEdge, BinUpperEdge);

  Mass2sqLSB = (TH1F*) (Mass2sqDataLSB->ProjectionY(Name.Data(), 10, 35));
  Mass2sqRSB = (TH1F*) (Mass2sqDataRSB->ProjectionY(Name.Data(), 10, 35));

  double wLSB = 0;
  double wRSB =0;
  double wTotal = 0;
  double cLSB = 0;
  double cRSB =0;
  double cTotal = 0;

  cLSB = Mass2sqLSB->Integral(Mass2sqLSB->GetBin(2.85), Mass2sqLSB->GetBin(3.4));
  cRSB = Mass2sqRSB->Integral(Mass2sqRSB->GetBin(3.775), Mass2sqRSB->GetBin(4.25));
  cTotal = cLSB+cRSB;

  wLSB = cLSB/cTotal;
  wRSB = cRSB/cTotal;

  std::cout << "**************** SideBand weights ***************" << std::endl;
  std::cout << "cLSB " << cLSB << std::endl;
  std::cout << "cRSB " << cRSB << std::endl;
  std::cout << "wLSB " << wLSB << std::endl;
  std::cout << "wRSB " << wRSB << std::endl;
  std::cout << "*************************************************" << std::endl;
  return;
}

