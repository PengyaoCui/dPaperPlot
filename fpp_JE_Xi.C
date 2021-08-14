#include "inc/PyJetUtils.h"

void fpp_JE_Xi(){
//=============================================================================
  auto f = TFile::Open("./data/pp.root", "read");
  auto l = (TList*)f->Get(Form("Xi"));
  f->Close();
  auto h = (TH1D*)l->FindObject(Form("JECen")); auto gE = (TGraphErrors*)l->FindObject(Form("JEerr"));

  TGraph *g[nm+2];
  const TString sj("Jet10");
  const TString sd("pp13d00TeV");  // pp13d00TeV:   pp at 13   TeV
                                    // pp05d02TeVrs: pp at 5.02 TeV
                                    //               with rapidity shift
				    //               used to fit p-Pb acceptance

  for (auto i=0; i<nm; ++i){
    g[i] = new TGraph(Spectrum(i, sd, "Xi", sj, "JC04", "PC04"));
  }

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(4e-5), dfuy(4e-2);
  
  auto dlsx(0.06), dlsy(0.06);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.20), dtoy(1.05);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas(Form("pp_JE_Xi")));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(505);

  DrawHisto(h, wcl[0], wmk[0], "same"); DrawGraph(gE, wcl[0], "E2");
  
  //DrawGraph(g[1],  wcl[0], "C");
  DrawGraph(g[0],  wcl[1], "C");
  DrawGraph(g[2],  wcl[2], "C");
  DrawGraph(g[3],  wcl[3], "C");

  auto leg(new TLegend(0.66, 0.55, 0.98, 0.92)); SetupLegend(leg);
  leg->AddEntry(h, "Data", "P")->SetTextSizePixels(24);
  //leg->AddEntry(g[1], "Monash", "L")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "BLC mode 0", "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "BLC mode 2", "L")->SetTextSizePixels(24);
  leg->AddEntry(g[3], "BLC mode 3", "L")->SetTextSizePixels(24);
  leg->Draw();
  //leg->AddEntry(gE[0], "Sys. Error", "f")->SetTextSizePixels(24);

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.90, "ALICE pp at #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.16, 0.80, "PYTHIA 8");
  tex->DrawLatex(0.16, 0.4, Form("#Xi^{-} + #bar{#Xi}^{+} in jets, UE subtracted"));
  tex->DrawLatex(0.16, 0.3, "#it{R}(#Xi, jet) < 0.4, |#eta_{#Xi}| < 0.75");
  tex->DrawLatex(0.16, 0.2, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  
  return;  
}
