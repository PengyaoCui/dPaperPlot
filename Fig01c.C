#include "inc/PyJetUtils.h"

void Fig01c(){

  auto f = TFile::Open("./data/pPb/Incl/Xi/AnalysisOutputs_FitInvMrd.root", "read");
  auto l = (TList*)f->Get("listFitInvMrd_Xi_Default_0100");
  f->Close();
  auto hInvM = (TH1D*)l->FindObject("hFitInvM_2");
  auto fS = (TF1*)hInvM->GetFunction("fFitInvM_2");

  f = TFile::Open("./data/pPb/Incl/Xi/AnalysisOutputs_FitCbinRD.root", "read");
  l = (TList*)f->Get("listFitCbinRD_Xi_Default_0100");
  f->Close();
  
  auto fB = (TF1*)l->FindObject("fBkgVarF_2");
  fB->SetLineWidth(3);
  fB->SetLineColor(kRed);
  fB->SetLineStyle(2);
  
  Double_t dWidth = fS->GetParameter(2);
  Double_t dMass = fS->GetParameter(1);
  auto hL = (TH1D*)hInvM->Clone("HIST_L");
  hL->GetXaxis()->SetRangeUser(dMass-8*dWidth, dMass-4*dWidth);
  hL->SetFillColor(15);
  hL->SetLineColor(1);
  auto hR = (TH1D*)hInvM->Clone("HIST_R");
  hR->GetXaxis()->SetRangeUser(dMass+4*dWidth, dMass+8*dWidth);
  hR->SetFillColor(15);
  hR->SetLineColor(1);

//=============================================================================
  auto dflx(1.3), dfux(1.345);
  auto dfly(4e2), dfuy(2e4);
  
 
  auto dlsx(0.06), dlsy(0.06);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.20), dtoy(1.05);

 
  TString stnx("#it{M}_{#Lambda#pi^{-}} (GeV/#it{c}^{2})");
  TString stny("Count");
  
  SetStyle(kTRUE);
  
  auto can(MakeCanvas("Fig01c"));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(510);

  hR->Draw("histsame");
  hL->Draw("histsame");
  DrawHisto(hInvM, wcl[0], wmk[0], "same");
  fB->Draw("same");

  //auto leg(new TLegend(0.72, 0.60, 0.98, 0.92)); SetupLegend(leg);
  //leg->AddEntry(hInvM, "Inclusive", "LP")->SetTextSizePixels(24);
  //leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(26);
  tex->DrawLatex(0.16, 0.9, "ALICE p#minusPb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex->DrawLatex(0.16, 0.8, "|#it{#eta}| < 0.75");
  tex->DrawLatex(0.78, 0.9, "#Xi^{-} #rightarrow #Lambda#pi^{-}");
  tex->DrawLatex(0.62, 0.8, "0.7 < #it{p}_{T} < 0.8 GeV/#it{c}");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));  
  CanvasEnd(can);

  return;
}

