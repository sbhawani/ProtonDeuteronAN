#ifdef __CLING__
#include <iostream>
#include <list>
#endif

//histograms
void ProtonDeuteronSideBandPlot() {

  TString FileNameData1, FileNameData2;

  int Var_SBW = 1;  // Peak of Mass
  int Var_SBL = 7;  // LeftSideband
  int Var_SBR = 16;  // RightSideband
  bool pTIntegrated = true;
  bool pTIntegratedNoTOF = false;
  TString OutputdirName =
      "~/cernbox/ProtonDeuteron/Outputs/NanoAODs/SidebandStduy/plots/";
  TString Outputfilename = "ProjectedLSBRSB_VeryNarrow.pdf";

  FileNameData1 =
      "~/cernbox/ProtonDeuteron/AnalysisResultsRootfiles/NanoAODs/Data/SideBandStudy/AnalysisResults_3.root";
  FileNameData2 =
      "~/cernbox/ProtonDeuteron/AnalysisResultsRootfiles/NanoAODs/Data/SideBandStudy/AnalysisResults_4.root";

  TFile *FileData1 = TFile::Open(FileNameData1.Data(), "READ");
  TFile *FileData2 = TFile::Open(FileNameData2.Data(), "READ");

  TDirectoryFile *MyTaskDirectorySBW = (TDirectoryFile*) (FileData2
      ->FindObjectAny(Form("HMDeuteron%i", Var_SBW)));
  TList *MyTaskSBW = (TList*) (MyTaskDirectorySBW->FindObjectAny(
      Form("HMDeuteron%i", Var_SBW)));

  TDirectoryFile *MyTaskDirectorySBL = (TDirectoryFile*) (FileData1
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

    TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 500, 400);
    cMassplot->SetLeftMargin(0.1605);
    cMassplot->SetRightMargin(0.035);
    cMassplot->SetTopMargin(0.1505);
    cMassplot->SetBottomMargin(0.18);
    gStyle->SetOptStat(0);
    int fbin = hMassSBW->FindBin(1.4);  //->GetxAxis()
    int lbin = hMassSBW->FindBin(4.05);  //->GetxAxis()

    TH1F *hProjMassSBW = (TH1F*) hMassSBW->ProjectionY("hProjMassSBW", 29, 81);
    TH1F *hProjMassSBL = (TH1F*) hMassSBL->ProjectionY("hProjMassSBL", 29, 81);
    TH1F *hProjMassSBR = (TH1F*) hMassSBR->ProjectionY("hProjMassSBR", 29, 81);

    hProjMassSBW->SetTitleSize(0.05);
    hProjMassSBW->GetXaxis()->SetLabelSize(0.05);
    hProjMassSBW->GetXaxis()->SetTitleSize(0.06);
    hProjMassSBW->GetXaxis()->SetTitleOffset(0.95);
    hProjMassSBW->GetXaxis()->SetTitle("m^{2}_{d} (GeV/#it{c}^{2})^{2}");
    hProjMassSBW->GetYaxis()->SetLabelSize(0.05);
    hProjMassSBW->GetYaxis()->SetTitleSize(0.06);
    hProjMassSBW->GetYaxis()->SetTitleOffset(1.3);
    hProjMassSBW->GetYaxis()->SetTitle("#it{Counts}");
    hProjMassSBW->GetXaxis()->SetRangeUser(1.8, 6);
    hProjMassSBW->GetYaxis()->SetRangeUser(0, 15000);

    hProjMassSBW->SetLineColorAlpha(kBlue, 0.35);
    hProjMassSBL->SetLineColorAlpha(kRed, 0.35);
    hProjMassSBR->SetLineColorAlpha(kYellow, 0.35);

    hProjMassSBW->SetMarkerStyle(4);
    hProjMassSBL->SetMarkerStyle(4);
    hProjMassSBR->SetMarkerStyle(4);

    hProjMassSBW->SetMarkerSize(1.1);
    hProjMassSBL->SetMarkerSize(1.1);
    hProjMassSBR->SetMarkerSize(1.1);

    hProjMassSBW->SetFillColorAlpha(kBlue - 2, 0.8);
    hProjMassSBL->SetFillColorAlpha(kRed - 2, 0.8);
    hProjMassSBR->SetFillColorAlpha(kYellow -3, 0.8);

    hProjMassSBW->SetFillStyle(1001);
    hProjMassSBL->SetFillStyle(1001);
    hProjMassSBR->SetFillStyle(1001);

    hProjMassSBW->SetMarkerColor(kBlue - 3);
    hProjMassSBL->SetMarkerColor(kRed - 2);
    hProjMassSBR->SetMarkerColor(kYellow - 3);

    hProjMassSBW->SetLineWidth(2);
    hProjMassSBW->SetLineWidth(2);
    hProjMassSBW->SetLineWidth(2);
    hProjMassSBW->Draw("hist");
    hProjMassSBL->Draw("hist same");
    hProjMassSBR->Draw("hist same");
    hProjMassSBW->Write();
    hProjMassSBL->Write();
    hProjMassSBR->Write();
    cMassplot->Print(Form("%s%s", OutputdirName.Data(), Outputfilename.Data()));
  }
  if (pTIntegratedNoTOF) {
    TDirectoryFile *MyTaskDirectoryNOTOF = (TDirectoryFile*) (FileData2
        ->FindObjectAny(Form("HMDeuteronNoTOF%i", Var_SBW)));
    TList *MyTaskNoTOF = (TList*) (MyTaskDirectoryNOTOF->FindObjectAny(
        Form("HMDeuteronNoTOF%i", Var_SBW)));

    TH2F *hMassNoTOF1;
    hMassNoTOF1 = (TH2F*) MyTaskNoTOF->FindObject("fDeuteronRestMassNoTOF");
    TH2F *hMassNoTOF = (TH2F*) hMassNoTOF1->Clone("hMassNoTOF");
    hMassNoTOF->Sumw2();

    TCanvas *cMassplot = new TCanvas("cMassplot", "cMassplot", 500, 400);
    cMassplot->SetLeftMargin(0.1605);
    cMassplot->SetRightMargin(0.035);
    cMassplot->SetTopMargin(0.1505);
    cMassplot->SetBottomMargin(0.18);
    gStyle->SetOptStat(0);

    TH1F *hProjMassNoTOF = (TH1F*) hMassNoTOF->ProjectionY("hProjMassSBW", 11, 35);

    hProjMassNoTOF->SetTitleSize(0.05);
    hProjMassNoTOF->GetXaxis()->SetLabelSize(0.05);
    hProjMassNoTOF->GetXaxis()->SetTitleSize(0.06);
    hProjMassNoTOF->GetXaxis()->SetTitleOffset(0.95);
    hProjMassNoTOF->GetXaxis()->SetTitle("m^{2}_{d} (GeV/#it{c}^{2})^{2}");
    hProjMassNoTOF->GetYaxis()->SetLabelSize(0.05);
    hProjMassNoTOF->GetYaxis()->SetTitleSize(0.06);
    hProjMassNoTOF->GetYaxis()->SetTitleOffset(1.3);
    hProjMassNoTOF->GetYaxis()->SetTitle("#it{Counts}");
    hProjMassNoTOF->GetXaxis()->SetRangeUser(2.0, 6);
    hProjMassNoTOF->GetYaxis()->SetRangeUser(0, 28000);

    hProjMassNoTOF->SetLineColorAlpha(kBlue, 0.35);
   // hProjMassSBL->SetLineColorAlpha(kRed, 0.35);
   // hProjMassSBR->SetLineColorAlpha(kGreen, 0.35);

    hProjMassNoTOF->SetMarkerStyle(4);
   // hProjMassSBL->SetMarkerStyle(4);
   // hProjMassSBR->SetMarkerStyle(4);

    hProjMassNoTOF->SetMarkerSize(1.0);
    //hProjMassSBL->SetMarkerSize(1.0);
   // hProjMassSBR->SetMarkerSize(1.0);

    //hProjMassNoTOF->SetFillColorAlpha(kBlue + 2, 0.8);
    //hProjMassSBL->SetFillColorAlpha(kRed + 2, 0.8);
    //hProjMassSBR->SetFillColorAlpha(kGreen + 4, 0.8);

   // hProjMassNoTOF->SetFillStyle(3001);
   // hProjMassSBL->SetFillStyle(3001);
   // hProjMassSBR->SetFillStyle(3001);

    hProjMassNoTOF->SetMarkerColor(kBlue - 2);
   // hProjMassSBL->SetMarkerColor(kRed + 0);
   // hProjMassSBR->SetMarkerColor(kGreen + 0);

    hProjMassNoTOF->SetLineWidth(1);
    hProjMassNoTOF->Draw("ep");
    //hProjMassSBL->Draw("hist same");
    //hProjMassSBR->Draw("hist same");
    hProjMassNoTOF->Write();
   // hProjMassSBL->Write();
   // hProjMassSBR->Write();
    cMassplot->Print(Form("%s%s", OutputdirName.Data(), Outputfilename.Data()));
  }
  return;

}

