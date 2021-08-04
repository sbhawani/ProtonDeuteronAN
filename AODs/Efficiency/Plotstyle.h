#include "TStyle.h"
#include "TFile.h"
#include "TLatex.h"

void SetStyleHistoCF(TH1 *histo, int marker, int color, int labelsize) {
 histo->GetXaxis()->SetLabelSize(labelsize);
 histo->GetXaxis()->SetTitleSize(0.05);
 histo->GetXaxis()->SetLabelOffset(0.01);
 histo->GetXaxis()->SetTitleOffset(1.2);
 histo->GetXaxis()->SetLabelFont(43);
 histo->GetXaxis()->SetTitle("k* [MeV/c]");
  // histo->GetYaxis()->SetLabelSize(15);
 histo->GetYaxis()->SetTitleSize(0.05);
 histo->GetYaxis()->SetLabelOffset(0.01);
 histo->GetYaxis()->SetTitleOffset(1.25);
 histo->GetYaxis()->SetTitle("C(k^{*})");
 histo->SetMarkerSize(0.6);
 histo->SetMarkerStyle(marker);
 histo->SetMarkerColor(color);
 histo->SetLineColor(color);
}
void SetStyle(bool graypalette) {
  const int NCont = 255;
  gStyle->Reset("Plain");
  gStyle->SetNumberContours(NCont);
  //gStyle->SetOptTitle(title);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetOptStat(0);
  if (graypalette)
    gStyle->SetPalette(8, 0);
  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadTopMargin(0.025);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(2);
  gStyle->SetFuncColor(kGreen);
  gStyle->SetLineWidth(2);
  gStyle->SetLabelFont(43, "xyz");
  gStyle->SetTitleFont(43, "xyz");
  gStyle->SetLabelSize(28, "xyz");
  gStyle->SetTitleSize(28, "xyz");
  gStyle->SetLabelOffset(0.01, "xy");
  gStyle->SetLabelColor(kBlack, "xyz");
  gStyle->SetTitleOffset(1.25, "y");
  gStyle->SetTitleOffset(1.25, "x");
  gStyle->SetTextSizePixels(26);
  gStyle->SetTextFont(42);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);
  gStyle->SetLegendFont(42);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetErrorX(0.5);
  gStyle->SetHatchesLineWidth(1);
  gStyle->SetHatchesSpacing(0.5);
  gStyle->SetPalette(kCividis);
}
