#include "inc/PyJetUtils.h"

void fpPb_Incl_Omega(){
//=============================================================================
  auto f = TFile::Open("./data/pPb.root", "read");
  auto l = (TList*)f->Get(Form("Omega_0100"));
  f->Close();
  auto h = (TH1D*)l->FindObject(Form("InclCen")); auto gE = (TGraphErrors*)l->FindObject(Form("Inclerr"));

  TGraph *g[nm+2];
  const TString sj("Jet10");
  const TString sd("pp05d02TeVrs");  // pp13d00TeV:   pp at 13   TeV
                                    // pp05d02TeVrs: pp at 5.02 TeV
                                    //               with rapidity shift
				    //               used to fit p-Pb acceptance

  for (auto i=0; i<nm; ++i) g[i] = new TGraph(Spectrum(i, sd, "Omega"));
  //for (auto i=0; i<nm; ++i) for (auto j=0; j<4; ++j) g[j][i]->SetLineStyle(9);

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(2e-6), dfuy(6e-2);
  
  auto dlsx(0.06), dlsy(0.06);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.20), dtoy(1.05);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas(Form("pPb_Incl_Omega")));
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

  auto leg(new TLegend(0.62, 0.55, 0.98, 0.92)); SetupLegend(leg);
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
  tex->DrawLatex(0.16, 0.90, "ALICE p-Pb at #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex->DrawLatex(0.16, 0.80, Form("Inclusive #Omega^{-} + #bar{#Omega}^{+}"));
  tex->DrawLatex(0.16, 0.70, "PYTHIA 8");
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  
  return;  
}
