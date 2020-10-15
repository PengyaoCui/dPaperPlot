#include "inc/PyJetUtils.h"

void f11_1(){

  auto f = TFile::Open("./data/pPb.root", "read");
  TList* l[4];
  l[0]= (TList*)f->Get(Form("Kshort_0100"));
  l[1]= (TList*)f->Get(Form("Kshort_010"));
  l[2]= (TList*)f->Get(Form("Kshort_1040"));
  l[3]= (TList*)f->Get(Form("Kshort_40100"));
  f->Close();
  TH1D *h[4]; TGraph *gE[4];
  for(Int_t i = 0; i<4; i++){
    h[i] = (TH1D*)l[i]->FindObject(Form("JECen")); gE[i] = (TGraphErrors*)l[i]->FindObject(Form("JEerr"));
  }

  TGraph *g[nm];
  const TString sj("Jet10");
  const TString sd("pp05d02TeVrs");  // pp13d00TeV:   pp at 13   TeV
                                    // pp05d02TeVrs: pp at 5.02 TeV
                                    //               with rapidity shift
                                    //               used to fit p-Pb acceptance

  for (auto i=0; i<nm; ++i){
    g[i] = new TGraph(Spectrum(i, sd, "Kshort", sj, "JC04", "PC04"));
  }

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(1e-4), dfuy(1e1);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  
  auto can(MakeCanvas(Form("f10_1")));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h[0], wcl[0], wmk[0], "same"); DrawGraph(gE[0], wcl[0], "E2");
  DrawHisto(h[1], wcl[1], wmk[1], "same"); DrawGraph(gE[1], wcl[1], "E2");
  DrawHisto(h[2], wcl[2], wmk[2], "same"); DrawGraph(gE[2], wcl[2], "E2");
  DrawHisto(h[3], wcl[3], wmk[3], "same"); DrawGraph(gE[3], wcl[3], "E2");

  g[0]->SetLineStyle(7);

  //DrawGraph(g[1],  wcl[0], "C");
  //DrawGraph(g[0],  wcl[1], "C");
  //DrawGraph(g[2],  wcl[2], "C");
  DrawGraph(g[0],  wcl[1], "C");


  auto leg(new TLegend(0.72, 0.60, 0.98, 0.92)); SetupLegend(leg);
  leg->AddEntry(h[0], "0-100%",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(h[1], "0-10%",   "LP")->SetTextSizePixels(24);
  leg->AddEntry(h[2], "10-40%",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(h[3], "40-100%", "LP")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "PYTHIA", "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex->DrawLatex(0.16, 0.82, Form("K^{0}_{S} in jet"));
  tex->DrawLatex(0.16, 0.72, "PYTHIA 8 BLC mode 0");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);


  return;
}

