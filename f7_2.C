#include "inc/PyJetUtils.h"


void f7_2(){

  auto f = TFile::Open("./data/pp.root", "read");
  auto l = (TList*)f->Get("Xi_toKRatio");
  f->Close();
  TH1D *h[4]; TGraph *gE[4];
  h[0] = (TH1D*)l->FindObject(Form("hInR")); gE[0] = (TGraphErrors*)l->FindObject(Form("InRerr"));
  h[1] = (TH1D*)l->FindObject(Form("hJCR")); gE[1] = (TGraphErrors*)l->FindObject(Form("JCRerr"));
  h[2] = (TH1D*)l->FindObject(Form("hUER")); gE[2] = (TGraphErrors*)l->FindObject(Form("UERerr"));
  h[3] = (TH1D*)l->FindObject(Form("hJER")); gE[3] = (TGraphErrors*)l->FindObject(Form("JERerr"));

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.), dfuy(0.25);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("(#Xi^{-} + #bar{#Xi}^{+}) / 2K_{S}^{0}");
 
  SetStyle(kTRUE);

  auto can(MakeCanvas("f7_2"));
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(503);

  DrawHisto(h[0], wcl[0], wmk[0], "same"); DrawGraph(gE[0], wcl[0], "E2");
  DrawHisto(h[1], wcl[3], wmk[0], "same"); DrawGraph(gE[1], wcl[3], "E2");
  DrawHisto(h[2], wcl[2], wmk[0], "same"); DrawGraph(gE[2], wcl[2], "E2");
  DrawHisto(h[3], wcl[1], wmk[0], "same"); DrawGraph(gE[3], wcl[1], "E2");

  auto leg(new TLegend(0.72, 0.5, 0.98, 0.75)); SetupLegend(leg);
  leg->AddEntry(h[0], "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h[1], "JC", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h[2], "UE", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h[3], "JE", "LP")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.16, 0.82, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");
  tex->DrawLatex(0.16, 0.72, "#it{R}(particle, jet) < 0.4, |#eta_{particle}| < 0.75");
  
  //tex->DrawLatex(0.16, 0.82, "#frac{#Xi^{-} + #bar{#Xi}^{+}}{2K^{0}_{S}}");
  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

