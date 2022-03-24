#include "inc/PyJetUtils.h"

void pPb_Ratio_010(){
 
  TString sp[] = {"Lambda_sum_toKRatio", "Xi_toKRatio", "Omega_toKRatio", "Xi_toLRatio", "Omega_toLRatio", "Omega_toXRatio"};
  TString sc[] = {"Incl", "JC", "UE", "JE"};
  const auto np = 6;
  const auto nc = 4;
  TList* l[np]; TH1D* h[np][nc]; TGraph *gE[np][nc];
  auto f = TFile::Open("./data/pPb.root", "read");


  for(int p = 0; p<np; p++ ){
    l[p] = (TList*)f->Get(Form("%s_010",sp[p].Data()));
    h[p][0] = (TH1D*)l[p]->FindObject(Form("hInR"));   gE[p][0] = (TGraphErrors*)l[p]->FindObject(Form("InRerr"));
    h[p][1] = (TH1D*)l[p]->FindObject(Form("hJCR"));   gE[p][1] = (TGraphErrors*)l[p]->FindObject(Form("JCRerr"));
    h[p][2] = (TH1D*)l[p]->FindObject(Form("hUER"));   gE[p][2] = (TGraphErrors*)l[p]->FindObject(Form("UERerr"));
    h[p][3] = (TH1D*)l[p]->FindObject(Form("hJER"));   gE[p][3] = (TGraphErrors*)l[p]->FindObject(Form("JERerr"));
  }
  f->Close();

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.02), dfuy(0.85);
  
  auto dlsx(0.07), dlsy(0.07);
  auto dtsx(0.07), dtsy(0.07);
  auto dtox(1.20), dtoy(1.05);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("Baryon-to-meson ratios");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  auto can(MakeCanvas("pPb_Ratio_010", 900, 800));
//=====Make pads===============================================================
  TPad *pad1 = new TPad("pad1", "pad1", 0., 1., 0.52, 0.52);
  pad1->Range(0., 0., 1., 1.);
  pad1->SetFillColor(0);
  pad1->SetBorderMode(0);
  pad1->SetBorderSize(0);
  pad1->SetRightMargin(0.03);
  pad1->SetLeftMargin(0.2);
  pad1->SetTopMargin(0.02);
  pad1->SetBottomMargin(0.1);
  pad1->SetFrameFillStyle(0);
  pad1->SetFrameBorderMode(0);
  pad1->SetTickx();
  pad1->SetTicky();
  pad1->Draw();

  TPad *pad2 = new TPad("pad2", "pad2", 0.52, 1., 1., 0.52);
  pad2->Range(0., 0., 1., 1.);
  pad2->SetFillColor(0);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(0);
  pad2->SetRightMargin(0.03);
  pad2->SetLeftMargin(0.12);
  pad2->SetTopMargin(0.02);
  pad2->SetBottomMargin(0.1);
  pad2->SetFrameFillStyle(0);
  pad2->SetFrameBorderMode(0);
  pad2->SetTickx();
  pad2->SetTicky();
  pad2->Draw();

  TPad *pad3 = new TPad("pad3", "pad3", 0., 0.52, 0.52, 0.);
  pad3->Range(0., 0., 1., 1.);
  pad3->SetFillColor(0);
  pad3->SetBorderMode(0);
  pad3->SetBorderSize(0);
  pad3->SetRightMargin(0.03);
  pad3->SetLeftMargin(0.2);
  pad3->SetTopMargin(0.02);
  pad3->SetBottomMargin(0.2);
  pad3->SetFrameFillStyle(0);
  pad3->SetFrameBorderMode(0);
  pad3->SetTickx();
  pad3->SetTicky();
  pad3->Draw();

  TPad *pad4 = new TPad("pad4", "pad4", 0.52, 0.52, 1., 0.);
  pad4->Range(0., 0., 1., 1.);
  pad4->SetFillColor(0);
  pad4->SetBorderMode(0);
  pad4->SetBorderSize(0);
  pad4->SetRightMargin(0.03);
  pad4->SetLeftMargin(0.12);
  pad4->SetTopMargin(0.02);
  pad4->SetBottomMargin(0.2);
  pad4->SetFrameFillStyle(0);
  pad4->SetFrameBorderMode(0);
  pad4->SetTickx();
  pad4->SetTicky();
  pad4->Draw();

  auto pad0 = MakePad("pad7", 0., 1., 1., 0.); pad0->SetBottomMargin(0.); pad0->SetLeftMargin(0.); can->cd();

  pad1->cd();
  auto hfm1(pad1->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm1, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm1->GetXaxis()->SetNdivisions(510);
  hfm1->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[0][0], wcl[0], wmk[0], "same"); DrawGraph(gE[0][0], wcl[0], "E2");
  //DrawHisto(h[0][1], wcl[3], wmk[2], "same"); DrawGraph(gE[0][1], wcl[3], "E2");
  DrawHisto(h[0][2], wcl[2], wmk[1], "same"); DrawGraph(gE[0][2], wcl[2], "E2");
  DrawHisto(h[0][3], wcl[1], wmk[3], "same"); DrawGraph(gE[0][3], wcl[1], "E2");
  
  
  can->cd();
  pad2->cd();
  dfly = 0.000; dfuy=0.23;
  auto hfm2(pad2->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm2, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm2->GetXaxis()->SetNdivisions(510);
  hfm2->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[1][0], wcl[0], wmk[0], "same"); DrawGraph(gE[1][0], wcl[0], "E2");
  //DrawHisto(h[1][1], wcl[3], wmk[2], "same"); DrawGraph(gE[1][1], wcl[3], "E2");
  DrawHisto(h[1][2], wcl[2], wmk[1], "same"); DrawGraph(gE[1][2], wcl[2], "E2");
  DrawHisto(h[1][3], wcl[1], wmk[3], "same"); DrawGraph(gE[1][3], wcl[1], "E2");
  
  can->cd();
  pad3->cd();
  dfly = 0.; dfuy=.49;
  auto hfm3(pad3->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm3, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm3->GetXaxis()->SetNdivisions(510);
  hfm3->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[3][0], wcl[0], wmk[0], "same"); DrawGraph(gE[3][0], wcl[0], "E2");
  //DrawHisto(h[3][1], wcl[3], wmk[2], "same"); DrawGraph(gE[3][1], wcl[3], "E2");
  DrawHisto(h[3][2], wcl[2], wmk[1], "same"); DrawGraph(gE[3][2], wcl[2], "E2");
  DrawHisto(h[3][3], wcl[1], wmk[3], "same"); DrawGraph(gE[3][3], wcl[1], "E2");


  can->cd();
  //pad4->cd();

  pad0->cd();
  pad0->SetFillStyle(4000);
  auto leg(new TLegend(0.5, 0.5, 0.7, 0.34)); SetupLegend(leg);
  leg->AddEntry(h[0][0], "Inclusive", "P")->SetTextSizePixels(12);
  leg->AddEntry(h[0][2], "Perp. cone", "P")->SetTextSizePixels(12);
  //leg->AddEntry(h[0][1], "#it{R}(par, jet) < 0.4", "P")->SetTextSizePixels(12);
  leg->AddEntry(h[0][3], "Particle in jets", "P")->SetTextSizePixels(12);
  //leg->AddEntry(gE[0], "Sys. Error", "f")->SetTextSizePixels(12);
  leg->Draw();


  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(12);
  tex->DrawLatex(0.13, 0.95, "ALICE p#minusPb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex->DrawLatex(0.53, 0.28, "Particle:|#eta| < 0.75");
  tex->DrawLatex(0.53, 0.2, "Jet: anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.58, 0.15, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}");
  tex->DrawLatex(0.58, 0.1, "|#eta_{jet}| < 0.35");

  tex->DrawLatex(0.25, 0.02, stnx);
  tex->DrawLatex(0.75, 0.5, stnx);
  tex->DrawLatex(0.85, 0.3, "0-10%");
  
  tex->DrawLatex(0.38, 0.83, "#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}");
  tex->DrawLatex(0.88, 0.83, "#frac{#Xi^{-} + #bar{#Xi}^{+}}{2K^{0}_{S}}");
  tex->DrawLatex(0.38, 0.33, "#frac{#Xi^{-} + #bar{#Xi}^{+}}{#Lambda + #bar{#Lambda}}");

  auto Tex(new TLatex());
  Tex->SetNDC();
  Tex->SetTextSizePixels(12);
  Tex->SetTextAngle(90);
  Tex->DrawLatex(0.03, 0.65, stny);
  stny("Baryon-to-baryon ratio");
  Tex->DrawLatex(0.03, 0.15, stny);

  can->cd();  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

