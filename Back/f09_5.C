#include "inc/PyJetUtils.h"

void f09_5(){
  
  TList* l[2]; TFile *f[2];
  f[0] = TFile::Open("./data/pp.root", "read");
  f[1] = TFile::Open("./data/pPb.root", "read");
  l[1] = (TList*)f[0]->Get(Form("Omega_toLRatio"));
  
  l[0] = (TList*)f[1]->Get(Form("Omega_toLRatio_0100"));
  f[0]->Close(); 
  f[1]->Close();
  
  TH1D *h[2]; TGraph *gE[2];
  for(Int_t i = 0; i<2; i++){
    h[i] = (TH1D*)l[i]->FindObject(Form("hJER"));
    gE[i] = (TGraphErrors*)l[i]->FindObject(Form("JERerr"));
  }
  const TString sj("Jet10");
  const TString sd("pp13d00TeV");  // pp13d00TeV:   pp at 13   TeV
                                    // pp05d02TeVrs: pp at 5.02 TeV
                                    //               with rapidity shift
                                    //               used to fit p-Pb acceptance

  TGraph *g[nm];
  for (auto i=0; i<nm; ++i) g[i] = new TGraph(RatioOL(i, sd, sj, "JC04", "PC04"));

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.), dfuy(0.17);

  auto dlsx(0.06), dlsy(0.06);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.20), dtoy(1.05);

  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("(#Omega^{-} + #bar{#Omega}^{+}) / (#Lambda + #bar{#Lambda})");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);

  auto can(MakeCanvas("f09_5"));
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(505);
  
  DrawHisto(h[0], wcl[0], wmk[0], "same"); DrawGraph(gE[0], wcl[0], "E2");
  DrawHisto(h[1], wcl[4], wmk[4], "same"); DrawGraph(gE[1], wcl[4], "E2");
  
  g[1]->SetLineStyle(9);
  DrawGraph(g[1],  wcl[8], "C");
  auto leg(new TLegend(0.72, 0.40, 1., 0.75)); SetupLegend(leg);
  leg->AddEntry(h[0], "p-Pb", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[1], "pp", "P")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "ALICE p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV and pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.16, 0.8, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");
  tex->DrawLatex(0.16, 0.7, "#it{R}(particle, jet) < 0.4, |#eta_{particle}| < 0.75");
  tex->DrawLatex(0.16, 0.6, "Particles in jets, UE subtracted");
  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}
