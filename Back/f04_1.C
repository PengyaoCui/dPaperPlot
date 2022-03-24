#include "inc/PyJetUtils.h"

void f04_1(){
  
  auto f = TFile::Open("./data/pp.root", "read");
  auto l = (TList*)f->Get("Kshort");
  f->Close();
  TH1D *h[4]; TGraph *gE[4];
  h[0] = (TH1D*)l->FindObject(Form("InclCen")); gE[0] = (TGraphErrors*)l->FindObject(Form("Inclerr"));
  h[1] = (TH1D*)l->FindObject(Form("JCCen"));   gE[1] = (TGraphErrors*)l->FindObject(Form("JCerr"));
  h[2] = (TH1D*)l->FindObject(Form("UECen"));   gE[2] = (TGraphErrors*)l->FindObject(Form("UEerr"));
  h[3] = (TH1D*)l->FindObject(Form("JECen"));   gE[3] = (TGraphErrors*)l->FindObject(Form("JEerr"));

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(1e-6), dfuy(2.);
  
  auto dlsx(0.06), dlsy(0.06);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.20), dtoy(1.05);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  auto can(MakeCanvas("f04_1"));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(505);

  DrawHisto(h[0], wcl[0], wmk[0], "same"); DrawGraph(gE[0], wcl[0], "E2");
  DrawHisto(h[1], wcl[3], wmk[2], "same"); DrawGraph(gE[1], wcl[3], "E2");
  DrawHisto(h[2], wcl[2], wmk[1], "same"); DrawGraph(gE[2], wcl[2], "E2");
  DrawHisto(h[3], wcl[1], wmk[3], "same"); DrawGraph(gE[3], wcl[1], "E2");

  auto leg(new TLegend(0.63, 0.68, 0.98, 0.95)); SetupLegend(leg);
  leg->AddEntry(h[0], "Inclusive", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[2], "Perp. cone", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[1], "#it{R}(K^{0}_{S}, jet) < 0.4", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[3], "K^{0}_{S} in jets", "P")->SetTextSizePixels(24);
  //leg->AddEntry(gE[0], "Sys. Error", "f")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "ALICE pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.16, 0.3, "K^{0}_{S}, |#eta_{K^{0}_{S}}| < 0.75");
  tex->DrawLatex(0.16, 0.2, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");
  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

