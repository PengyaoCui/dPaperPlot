#include "inc/PyJetUtils.h"

void f06_7(){

  auto f = TFile::Open("./data/pPb.root", "read");
  TList* l;
  l= (TList*)f->Get(Form("Omega_0100"));
  f->Close();
  TH1D *h; TGraph *gE;
  h = (TH1D*)l->FindObject(Form("JECen")); gE = (TGraphErrors*)l->FindObject(Form("JEerr"));
 

  TGraph *g[nm];
  const TString sj("Jet10");
  const TString sd("pp05d02TeVrs");  // pp13d00TeV:   pp at 13   TeV
                                    // pp05d02TeVrs: pp at 5.02 TeV
                                    //               with rapidity shift
                                    //               used to fit p-Pb acceptance

  for (auto i=0; i<nm; ++i){
    g[i] = new TGraph(Spectrum(i, sd, "Omega", sj, "JC04", "PC04"));
  }

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(9e-6), dfuy(8e-2);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas(Form("f06_7")));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h, wcl[0], wmk[0], "same"); DrawGraph(gE, wcl[0], "E2");

  g[0]->SetLineStyle(7);

  DrawGraph(g[1],  wcl[0], "C");
  //DrawGraph(g[0],  wcl[1], "C");
  //DrawGraph(g[2],  wcl[2], "C");
  //DrawGraph(g[3],  wcl[3], "C");


  auto leg(new TLegend(0.65, 0.60, 0.98, 0.87)); SetupLegend(leg);
  leg->AddEntry(h, "Data 0-100%",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex->DrawLatex(0.16, 0.82, Form("#Omega^{-} + #bar{#Omega}^{+} in jet"));
  //tex->DrawLatex(0.16, 0.72, "PYTHIA 8 BLC mode 0");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);


  return;
}

