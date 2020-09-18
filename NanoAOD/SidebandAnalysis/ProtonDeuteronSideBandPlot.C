#ifdef __CLING__
#include <iostream>
#include <list>
#endif

//histograms
void ProtonDeuteronSideBandPlot() {

  TString FileNameData1, FileNameData2;

  int Var_SBW = 3;  // Peak of Mass
  int Var_SBL = 7;  // LeftSideband
  int Var_SBR = 13;  // RightSideband
  bool pTIntegrated = true;
  TString OutputdirName =
      "~/cernbox/ProtonDeuteron/Outputs/NanoAODs/SidebandStduy/plots/";
  TString Outputfilename = "MassSquaredplot.png";

  FileNameData1 =
      "~/cernbox/ProtonDeuteron/rootfiles/NanoAODs/Data/SideBandStudy/AnalysisResults_1.root";
  FileNameData2 =
      "~/cernbox/ProtonDeuteron/rootfiles/NanoAODs/Data/SideBandStudy/AnalysisResults_2.root";

  TFile *FileData1 = TFile::Open(FileNameData1.Data(), "READ");
  TFile *FileData2 = TFile::Open(FileNameData2.Data(), "READ");

  TDirectoryFile *MyTaskDirectorySBW = (TDirectoryFile*) (FileData2
      ->FindObjectAny(Form("HMDeuteron%i", Var_SBW)));
  TList *MyTaskSBW = (TList*) (MyTaskDirectorySBW->FindObjectAny(
      Form("HMDeuteron%i", Var_SBW)));

  TDirectoryFile *MyTaskDirectorySBL = (TDirectoryFile*) (FileData2
      ->FindObjectAny(Form("HMDeuteron%i", Var_SBL)));
  TList *MyTaskSBL = (TList*) (MyTaskDirectorySBL->FindObjectAny(
      Form("HMDeuteron%i", Var_SBL)));

  TDirectoryFile *MyTaskDirectorySBR = (TDirectoryFile*) (FileData1
      ->FindObjectAny(Form("HMDeuteron%i", Var_SBR)));
  TList *MyTaskSBR = (TList*) (MyTaskDirectorySBR->FindObjectAny(
      Form("HMDeuteron%i", Var_SBR)));

  TH2F *hMassSBW1, *hMassSBL1, *hMassSBR1;
  hMassSBW1 = (TH2F*) MyTaskSBW->FindObject("TOFMassSquared");
  TH2F *hMassSBW = (TH2F*) hMassSBW1->Clone("MassSBW");
  hMassSBW->Sumw2();
  hMassSBL1 = (TH2F*) MyTaskSBL->FindObject("TOFMassSquared");
  TH2F *hMassSBL = (TH2F*) hMassSBL1->Clone("hMassSBL");
  hMassSBL->Sumw2();
  hMassSBR1 = (TH2F*) MyTaskSBR->FindObject("TOFMassSquared");
  TH2F *hMassSBR = (TH2F*) hMassSBR1->Clone("hMassSBL");
  hMassSBR->Sumw2();

  if (pTIntegrated) {

    TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 1000, 1000);
    cMassplot->SetLeftMargin(0.1505);
    cMassplot->SetRightMargin(0.035);
    gStyle->SetOptStat(0);
    int fbin = hMassSBW->FindBin(1.4);  //->GetxAxis()
    int lbin = hMassSBW->FindBin(4.05);  //->GetxAxis()

    TH1F *hProjMassSBW = (TH1F*) hMassSBW->ProjectionY("hProjMassSBW", 29, 81);
    TH1F *hProjMassSBL = (TH1F*) hMassSBL->ProjectionY("hProjMassSBL", 29, 81);
    TH1F *hProjMassSBR = (TH1F*) hMassSBR->ProjectionY("hProjMassSBR", 29, 81);

    hProjMassSBW->SetTitleSize(0.05);
    hProjMassSBW->GetXaxis()->SetLabelSize(0.045);
    hProjMassSBW->GetXaxis()->SetTitleSize(0.05);
    hProjMassSBW->GetXaxis()->SetTitleOffset(0.89);
    hProjMassSBW->GetXaxis()->SetTitle("m^{2}_{d} (GeV/#it{c}^{2})^{2}");
    hProjMassSBW->GetYaxis()->SetLabelSize(0.035);
    hProjMassSBW->GetYaxis()->SetTitleSize(0.05);
    hProjMassSBW->GetYaxis()->SetTitleOffset(0.95);
    hProjMassSBW->GetYaxis()->SetTitle("#it{Counts}");
    hProjMassSBW->GetXaxis()->SetRangeUser(1.0, 6);
    hProjMassSBW->GetYaxis()->SetRangeUser(1000, 40000);

    hProjMassSBW->SetLineColorAlpha(kBlue, 0.35);
    hProjMassSBL->SetLineColorAlpha(kRed, 0.35);
    hProjMassSBR->SetLineColorAlpha(kGreen, 0.35);

    hProjMassSBW->SetMarkerStyle(4);
    hProjMassSBL->SetMarkerStyle(4);
    hProjMassSBR->SetMarkerStyle(4);

    hProjMassSBW->SetMarkerSize(1.0);
    hProjMassSBL->SetMarkerSize(1.0);
    hProjMassSBR->SetMarkerSize(1.0);

    hProjMassSBW->SetFillColorAlpha(kBlue + 2, 0.8);
    hProjMassSBL->SetFillColorAlpha(kRed + 2, 0.8);
    hProjMassSBR->SetFillColorAlpha(kGreen + 4, 0.8);

    hProjMassSBW->SetFillStyle(3001);
    hProjMassSBL->SetFillStyle(3001);
    hProjMassSBR->SetFillStyle(3001);

    hProjMassSBW->SetMarkerColor(kBlue + 0);
    hProjMassSBL->SetMarkerColor(kRed + 0);
    hProjMassSBR->SetMarkerColor(kGreen + 0);

    hProjMassSBW->SetLineWidth(2);
    hProjMassSBW->SetLineWidth(2);
    hProjMassSBW->SetLineWidth(2);
    hProjMassSBW->Draw("hist same");
    hProjMassSBL->Draw("hist same");
    hProjMassSBR->Draw("hist same");
    hProjMassSBW->Write();
    hProjMassSBL->Write();
    hProjMassSBR->Write();
    cMassplot->Print(Form("%s%s", OutputdirName.Data(), Outputfilename.Data()));
  }
  return;

}

