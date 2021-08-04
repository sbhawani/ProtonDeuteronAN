#ifdef __CLING__
#include <iostream>
#include "Plotstyle.h"
#include <list>
#endif

TH1F* SetAnalysisFileSample(const char *PathAnalysisFile, const char *Prefix,
                            const char *Addon, const int WhichPart,
                            const int Whichhisto) {
  char *Part[4] = { "ProtonDCA", "AntiProtonDCA", "DeuteronDCA",
                    "AntiDeuteronDCA"
                  };
  TString Histo[4][2] = { { "fProtonpTSpectraMC", "fProtonpTSpectraMCreconst" },
    { "fAntiProtonTSpectraMC", "fAntiProtonTSpectraMCreconst" }, {
      "fDeuteronpTSpectraMC", "fDeuteronpTSpectraMCreconst"
    }, {
      "fAntiDeuteronpTSpectraMC", "fAntiDeuteronpTSpectraMCreconst"
    }
  };
  std::cout << "PathAnalysisFile: " << PathAnalysisFile << '\t' << " Prefix: "
            << Prefix << '\t' << " Addon: " << Addon << std::endl;

  if (Whichhisto > 2 && WhichPart > 3) {
    std::cout << "no histo available for part "
              << TString::Format("%s%d%s", Prefix, WhichPart, Addon).Data()
              << std::endl;
    return 0;
  }

  TFile *_file0 = TFile::Open(PathAnalysisFile, "READ");
  TDirectoryFile *dirPart = (TDirectoryFile*) (_file0->FindObjectAny(
                              TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));

  if (!dirPart) {
    std::cout << "no dir for particle "
              << TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()
              << std::endl;
    return 0;
  }
  TList *dirPart2 = nullptr;
  dirPart->GetObject(
    TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data(),
    dirPart2);
  if (!dirPart2) {
    std::cout << "No results List for "
              << TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()
              << std::endl;
    dirPart->ls();
    return 0;
  }

  TH1F* h = (TH1F*) dirPart2->FindObject(Histo[WhichPart][Whichhisto]);
  return h;
  dirPart2->Delete();
  dirPart->Close();
  _file0->Close();
  delete _file0;
}

TH2F* SetAnalysisFileSample2(const char *PathAnalysisFile, const char *Prefix,
                             const char *Addon, const int WhichPart,
                             const int Whichhisto) {
  char *Part[4] = { "ProtonDCA", "AntiProtonDCA", "DeuteronDCA",
                    "AntiDeuteronDCA"
                  };
  TString Histo[4][2] = { { "fProtonpTSpectraMC", "fProtonpTSpectraMCreconst" },
    { "fAntiProtonTSpectraMC", "fAntiProtonTSpectraMCreconst" }, {
      "fDeuteronpTSpectraMC", "fDeuteronpTSpectraMCreconst"
    }, {
      "fAntiDeuteronpTSpectraMC", "fAntiDeuteronpTSpectraMCreconst"
    }
  };
  std::cout << "PathAnalysisFile: " << PathAnalysisFile << '\t' << " Prefix: "
            << Prefix << '\t' << " Addon: " << Addon << std::endl;

  if (Whichhisto > 2 && WhichPart > 3) {
    std::cout << "no histo available for part "
              << TString::Format("%s%d%s", Prefix, WhichPart, Addon).Data()
              << std::endl;
    return 0;
  }

  TFile *_file0 = TFile::Open(PathAnalysisFile, "READ");
  TDirectoryFile *dirPart = (TDirectoryFile*) (_file0->FindObjectAny(
                              TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()));

  if (!dirPart) {
    std::cout << "no dir for particle "
              << TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()
              << std::endl;
    return 0;
  }
  TList *dirPart2 = nullptr;
  dirPart->GetObject(
    TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data(),
    dirPart2);
  if (!dirPart2) {
    std::cout << "No results List for "
              << TString::Format("%s%s%s", Prefix, Part[WhichPart], Addon).Data()
              << std::endl;
    dirPart->ls();
    return 0;
  }

  TH2F* h = (TH2F*) dirPart2->FindObject(Histo[WhichPart][Whichhisto]);

  return h;
  dirPart2->Delete();
  dirPart->Close();
  _file0->Close();
  delete _file0;
}



//histograms

void doComputeEfficiency(const char *filename, const char *prefix,
                         const char *addon = "", bool pap = false) {
  SetStyle(true);
  bool efficiecnyPantiP = false;
  bool efficiecnyDantiD = true;
  TString OutputdirName = "~/cernbox/ProtonDeuteron/Outputs/AODs/Efficiency/";
  TString Outputfilename = " ";
  if (pap) {
    Outputfilename = "pAntipEffCorrect.pdf";
  } else {

    Outputfilename = "dAntidEffCorrect.pdf";
  }

  TH2F *hProtonMC1;
  TH1F *hProtonMC1Projected;
  TH1F *hProtonMCreconst1;
  TH2F *hAntiProtonMC1;
  TH1F *hAntihProtonMC1Projected;
  TH1F *hAntiProtonMCreconst1;
  TH2F *hDeuteronMC1;
  TH1F *hDeuteronMC1Projected;
  TH1F *hDeuteronMCreconst1;
  TH2F *hAntiDeuteronMC1;
  TH1F *hAntiDeuteronMC1Projected;
  TH1F *hAntiDeuteronMCreconst1;

  hProtonMC1 = SetAnalysisFileSample2(filename, prefix, addon, 0, 0);
  hProtonMCreconst1 = SetAnalysisFileSample(filename, prefix, addon, 0, 1);
  hAntiProtonMC1 = SetAnalysisFileSample2(filename, prefix, addon, 1, 0);
  hAntiProtonMCreconst1 = SetAnalysisFileSample(filename, prefix, addon, 1, 1);
  hDeuteronMC1 = SetAnalysisFileSample2(filename, prefix, addon, 2, 0);
  hDeuteronMCreconst1 = SetAnalysisFileSample(filename, prefix, addon, 2, 1);
  hAntiDeuteronMC1 = SetAnalysisFileSample2(filename, prefix, addon, 3, 0);
  hAntiDeuteronMCreconst1 = SetAnalysisFileSample(filename, prefix, addon, 3,
                            1);

  TH2F *hProtonMC = (TH2F*) hProtonMC1->Clone("hProtonMC");
  hProtonMC->Sumw2();
  TH1F *hProtonMCreconst = (TH1F*) hProtonMCreconst1->Clone("hProtonMCreconst");
  hProtonMCreconst->Sumw2();

  TH2F *hAntiProtonMC = (TH2F*) hAntiProtonMC1->Clone("hAntiProtonMC");
  hAntiProtonMC->Sumw2();
  TH1F *hAntiProtonMCreconst = (TH1F*) hAntiProtonMCreconst1->Clone(
                                 "hAntiProtonMCreconst");
  hAntiProtonMCreconst->Sumw2();

  TH2F *hDeuteronMC = (TH2F*) hDeuteronMC1->Clone("hDeuteronMC");
  hDeuteronMC->Sumw2();
  TH1F *hDeuteronMCreconst = (TH1F*) hDeuteronMCreconst1->Clone(
                               "hDeuteronMCreconst");
  hDeuteronMCreconst->Sumw2();

  TH2F *hAntiDeuteronMC = (TH2F*) hAntiDeuteronMC1->Clone("hAntiDeuteronMC");
  hAntiDeuteronMC->Sumw2();
  TH1F *hAntiDeuteronMCreconst = (TH1F*) hAntiDeuteronMCreconst1->Clone(
                                   "hAntiDeuteronMCreconst");
  hAntiDeuteronMCreconst->Sumw2();


  //projected histos
  hProtonMC1Projected = (TH1F*)(hProtonMC->ProjectionX("hProtonMC1Projected", 1, 99));
  hAntihProtonMC1Projected = (TH1F*)(hAntiProtonMC->ProjectionX("hAntihProtonMC1Projected", 1, 99));
  hDeuteronMC1Projected = (TH1F*)(hDeuteronMC->ProjectionX("hDeuteronMC1Projected", 1, 99));
  hAntiDeuteronMC1Projected = (TH1F*)(hAntiDeuteronMC->ProjectionX("hAntiDeuteronMC1Projected", 1, 99));

  if (pap) {
    TH1F *hEffP;
    TH1F *hEffAp;
    TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 500, 400);
    cMassplot->SetLeftMargin(0.1605);
    cMassplot->SetRightMargin(0.035);
    cMassplot->SetTopMargin(0.1505);
    cMassplot->SetBottomMargin(0.18);
    gStyle->SetOptStat(0);
    TLegend *leg = new TLegend(0.5, 0.3, 0.73, 0.4);
    leg->SetFillStyle(0);
    leg->SetTextFont(43);
    leg->SetTextSizePixels(40);
    leg->SetFillStyle(0);
    leg->SetTextSize(12);
    hEffP = (TH1F*) hProtonMCreconst->Clone("hEffAp");
    hEffAp = (TH1F*) hAntiProtonMCreconst->Clone("hEffAp");
    hEffP->Sumw2();
    hEffAp->Sumw2();
    hEffP->Divide(hProtonMCreconst, hProtonMC1Projected);
    hEffAp->Divide(hAntiProtonMCreconst, hAntihProtonMC1Projected);

    hEffP->SetTitleSize(0.05);
    hEffP->GetXaxis()->SetLabelSize(0.05);
    hEffP->GetXaxis()->SetTitleSize(0.06);
    hEffP->GetXaxis()->SetTitleOffset(0.8);
    hEffP->GetXaxis()->SetTitle("p_{T} (GeV/#it{c})");
    hEffP->GetYaxis()->SetLabelSize(0.05);
    hEffP->GetYaxis()->SetTitleSize(0.06);
    hEffP->GetYaxis()->SetTitleOffset(0.9);
    hEffP->GetYaxis()->SetTitle("Efficiency x Acceptance");
    hEffP->GetXaxis()->SetRangeUser(0.4, 4.0);
    hEffP->GetYaxis()->SetRangeUser(0, 1.05);

    hEffP->SetTitle(0);
    hEffAp->SetTitle(0);

    hEffP->SetLineColor(kBlue);
    hEffAp->SetLineColor(kRed);

    hEffP->SetMarkerStyle(4);
    hEffAp->SetMarkerStyle(4);

    hEffP->SetMarkerSize(0.5);
    hEffAp->SetMarkerSize(0.5);

    hEffP->SetMarkerColor(kBlue);
    hEffAp->SetMarkerColor(kRed);

    hEffP->SetLineWidth(1);
    hEffAp->SetLineWidth(1);
    leg->AddEntry(hEffP, "proton TPC + TOF");
    leg->AddEntry(hEffAp, "antiproton TPC + TOF");

    hEffP->Draw("ep");
    hEffAp->Draw("ep same");
    leg->Draw("same");
    hEffP->Write();
    hEffAp->Write();
    cMassplot->Print(Form("%s%s", OutputdirName.Data(), Outputfilename.Data()));

    delete leg;
    delete cMassplot;
  } else {
    TH1F *hEffD;
    TH1F *hEffAd;
    TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 1200, 800);
    cMassplot->SetLeftMargin(0.1605);
    cMassplot->SetRightMargin(0.035);
    cMassplot->SetTopMargin(0.1505);
    cMassplot->SetBottomMargin(0.18);
    gStyle->SetOptStat(0);

    TLegend *leg = new TLegend(0.5, 0.3, 0.73, 0.4);
    leg->SetFillStyle(0);
    leg->SetTextFont(43);
    leg->SetTextSizePixels(40);
    hEffD = (TH1F*) hDeuteronMCreconst->Clone("hEffD");
    hEffAd = (TH1F*) hAntiProtonMCreconst->Clone("hEffAd");
    hEffD->Sumw2();
    hEffAd->Sumw2();
    hEffD->Divide(hDeuteronMCreconst, hDeuteronMC1Projected);
    hEffAd->Divide(hAntiDeuteronMCreconst, hAntiDeuteronMC1Projected);

    hEffD->SetTitleSize(0.05);
    hEffD->GetXaxis()->SetLabelSize(0.05);
    hEffD->GetXaxis()->SetTitleSize(0.06);
    hEffD->GetXaxis()->SetTitleOffset(0.95);
    hEffD->GetXaxis()->SetTitle("p_{T} (GeV/#it{c})");
    hEffD->GetYaxis()->SetLabelSize(0.05);
    hEffD->GetYaxis()->SetTitleSize(0.06);
    hEffD->GetYaxis()->SetTitleOffset(0.9);
    hEffD->GetYaxis()->SetTitle("Efficiency x Acceptance");
    hEffD->GetXaxis()->SetRangeUser(0.5, 4.0);
    hEffD->GetYaxis()->SetRangeUser(0, 1.01);
    hEffD->SetTitle(0);
    hEffAd->SetTitle(0);
    hEffD->SetLineColor(kBlue);
    hEffAd->SetLineColor(kRed);

    hEffD->SetMarkerStyle(4);
    hEffAd->SetMarkerStyle(4);

    hEffD->SetMarkerSize(0.5);
    hEffAd->SetMarkerSize(0.5);

    hEffD->SetMarkerColor(kBlue);
    hEffAd->SetMarkerColor(kRed);

    hEffD->SetLineWidth(1);
    hEffAd->SetLineWidth(1);
    leg->AddEntry(hEffD, "deuteron TPC + TOF");
    leg->AddEntry(hEffAd, "antideuteron TPC + TOF");
    hEffD->Draw("ep");
    hEffAd->Draw("ep same");
    leg->Draw("same");
    hEffD->Write();
    hEffAd->Write();
    cMassplot->Print(Form("%s%s", OutputdirName.Data(), Outputfilename.Data()));
    delete leg;
    delete cMassplot;
  }
  return;
}

void ComputeEfficiency() {
  bool pAp = true;
  TString path = "";
  if (pAp) {
    path = "/home/sbhawani/cernbox/ProtonDeuteron/AnalysisResultsRootfiles/AODs/EfficiencyCheck/MC/ProtonEfficiency/AnalysisResultsAllETA.root";
  } else {
    path = "/home/sbhawani/cernbox/ProtonDeuteron/AnalysisResultsRootfiles/AODs/EfficiencyCheck/MC/DeuteronEfficiency/AnalysisResultFullEta2018a2.root";

  }
  doComputeEfficiency(path, "HM", "0", pAp);
  return;
}
