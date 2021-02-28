#include "inc/PyJetUtils.h"

void f09_6(){
  
  TList* l[2]; TFile *f[2];
  f[0] = TFile::Open("./data/pp.root", "read");
  f[1] = TFile::Open("./data/pPb.root", "read");
  l[1] = (TList*)f[0]->Get(Form("Omega_toXRatio"));
  
  l[0] = (TList*)f[1]->Get(Form("Omega_toXRatio_0100"));
  f[0]->Close(); 
  f[1]->Close();
  
  TH1D *h[2]; TGraph *gE[2];
  for(Int_t i = 0; i<2; i++){
    h[i] = (TH1D*)l[i]->FindObject(Form("hJER"));
    gE[i] = (TGraphErrors*)l[i]->FindObject(Form("JERerr"));
  }
//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.), dfuy(1.9);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("(#Omega^{-} + #bar{#Omega}^{+}) / (#Xi^{-} + #bar{#Xi}^{+})");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);

  auto can(MakeCanvas("f09_6"));
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(505);
  
  DrawHisto(h[0], wcl[0], wmk[0], "same"); DrawGraph(gE[0], wcl[0], "E2");
  DrawHisto(h[1], wcl[4], wmk[4], "same"); DrawGraph(gE[1], wcl[4], "E2");
  
  auto leg(new TLegend(0.75, 0.50, 1., 0.75)); SetupLegend(leg);
  leg->AddEntry(h[0], "p-Pb", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[1], "pp", "P")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV and pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.82, 0.9, "ALICE");
  tex->DrawLatex(0.16, 0.8, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");
  tex->DrawLatex(0.16, 0.7, "#it{R}(particle, jet) < 0.4, |#eta_{particle}| < 0.75");
  tex->DrawLatex(0.16, 0.6, "Particles in jets, UE subtracted");
  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}
