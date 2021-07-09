#include "inc/PyJetUtils.h"


void f07_sixPad(){

  auto f = TFile::Open("./data/pp.root", "read");
  auto l11 = (TList*)f->Get("Lambda_sum_toKRatio");
  auto l12 = (TList*)f->Get("Xi_toKRatio");
  auto l13 = (TList*)f->Get("Omega_toKRatio");
  auto l21 = (TList*)f->Get("Xi_toLRatio");
  auto l22 = (TList*)f->Get("Omega_toLRatio");
  auto l23 = (TList*)f->Get("Omega_toXRatio");
  f->Close();
  TH1D *h11[4]; TGraph *gE11[4];
  h11[0] = (TH1D*)l11->FindObject(Form("hInR")); gE11[0] = (TGraphErrors*)l11->FindObject(Form("InRerr"));
  h11[1] = (TH1D*)l11->FindObject(Form("hJCR")); gE11[1] = (TGraphErrors*)l11->FindObject(Form("JCRerr"));
  h11[2] = (TH1D*)l11->FindObject(Form("hUER")); gE11[2] = (TGraphErrors*)l11->FindObject(Form("UERerr"));
  h11[3] = (TH1D*)l11->FindObject(Form("hJER")); gE11[3] = (TGraphErrors*)l11->FindObject(Form("JERerr"));
  TH1D *h12[4]; TGraph *gE12[4];
  h12[0] = (TH1D*)l12->FindObject(Form("hInR")); gE12[0] = (TGraphErrors*)l12->FindObject(Form("InRerr"));
  h12[1] = (TH1D*)l12->FindObject(Form("hJCR")); gE12[1] = (TGraphErrors*)l12->FindObject(Form("JCRerr"));
  h12[2] = (TH1D*)l12->FindObject(Form("hUER")); gE12[2] = (TGraphErrors*)l12->FindObject(Form("UERerr"));
  h12[3] = (TH1D*)l12->FindObject(Form("hJER")); gE12[3] = (TGraphErrors*)l12->FindObject(Form("JERerr"));
  TH1D *h13[4]; TGraph *gE13[4];
  h13[0] = (TH1D*)l13->FindObject(Form("hInR")); gE13[0] = (TGraphErrors*)l13->FindObject(Form("InRerr"));
  h13[1] = (TH1D*)l13->FindObject(Form("hJCR")); gE13[1] = (TGraphErrors*)l13->FindObject(Form("JCRerr"));
  h13[2] = (TH1D*)l13->FindObject(Form("hUER")); gE13[2] = (TGraphErrors*)l13->FindObject(Form("UERerr"));
  h13[3] = (TH1D*)l13->FindObject(Form("hJER")); gE13[3] = (TGraphErrors*)l13->FindObject(Form("JERerr"));
  
  TH1D *h21[4]; TGraph *gE21[4];
  h21[0] = (TH1D*)l21->FindObject(Form("hInR")); gE21[0] = (TGraphErrors*)l21->FindObject(Form("InRerr"));
  h21[1] = (TH1D*)l21->FindObject(Form("hJCR")); gE21[1] = (TGraphErrors*)l21->FindObject(Form("JCRerr"));
  h21[2] = (TH1D*)l21->FindObject(Form("hUER")); gE21[2] = (TGraphErrors*)l21->FindObject(Form("UERerr"));
  h21[3] = (TH1D*)l21->FindObject(Form("hJER")); gE21[3] = (TGraphErrors*)l21->FindObject(Form("JERerr"));
  TH1D *h22[4]; TGraph *gE22[4];
  h22[0] = (TH1D*)l22->FindObject(Form("hInR")); gE22[0] = (TGraphErrors*)l22->FindObject(Form("InRerr"));
  h22[1] = (TH1D*)l22->FindObject(Form("hJCR")); gE22[1] = (TGraphErrors*)l22->FindObject(Form("JCRerr"));
  h22[2] = (TH1D*)l22->FindObject(Form("hUER")); gE22[2] = (TGraphErrors*)l22->FindObject(Form("UERerr"));
  h22[3] = (TH1D*)l22->FindObject(Form("hJER")); gE22[3] = (TGraphErrors*)l22->FindObject(Form("JERerr"));
  TH1D *h23[4]; TGraph *gE23[4];
  h23[0] = (TH1D*)l23->FindObject(Form("hInR")); gE23[0] = (TGraphErrors*)l23->FindObject(Form("InRerr"));
  h23[1] = (TH1D*)l23->FindObject(Form("hJCR")); gE23[1] = (TGraphErrors*)l23->FindObject(Form("JCRerr"));
  h23[2] = (TH1D*)l23->FindObject(Form("hUER")); gE23[2] = (TGraphErrors*)l23->FindObject(Form("UERerr"));
  h23[3] = (TH1D*)l23->FindObject(Form("hJER")); gE23[3] = (TGraphErrors*)l23->FindObject(Form("JERerr"));

//=============================================================================
  auto dflx(1e-3), dfux(12.);
  auto dfly(1e-3), dfuy(0.7);
  
  auto dlsx(0.07), dlsy(0.08);
  auto dtsx(0.07), dtsy(0.09);
  auto dtox(1.30), dtoy(1.2);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("Baryon to meson ratio");
  
  auto dlsx2(0.07), dlsy2(0.07);
  auto dtsx2(0.07), dtsy2(0.08);
  auto dtox2(1.30), dtoy2(1.2);
  TString stny2("Baryon to baryon ratio");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);

  auto can(MakeCanvas("f07_sixPad", 1000, 600));

//=============================================================================
  can->cd();
  TPad* p11 = new TPad("cp11", "p11", 0., 0.55, 0.4, 1.);
  //p11->SetLogy();
  p11->Range(0., 0., 1., 1.);
  p11->SetFillColor(0);
  p11->SetBorderMode(0);
  p11->SetBorderSize(0);
  p11->SetRightMargin(0.);
  p11->SetLeftMargin(0.22);
  p11->SetTopMargin(0.02);
  p11->SetBottomMargin(0.);
  p11->SetFrameFillStyle(0);
  p11->SetFrameBorderMode(0);
  p11->Draw();
  p11->cd();
  auto hfm11(p11->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm11, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm11->GetXaxis()->SetNdivisions(505);
  hfm11->GetYaxis()->SetNdivisions(505);
  
  DrawHisto(h11[0], wcl[0], wmk[0], "same"); DrawGraph(gE11[0], wcl[0], "E2");
  DrawHisto(h11[1], wcl[3], wmk[2], "same"); DrawGraph(gE11[1], wcl[3], "E2");
  DrawHisto(h11[2], wcl[2], wmk[1], "same"); DrawGraph(gE11[2], wcl[2], "E2");
  DrawHisto(h11[3], wcl[1], wmk[3], "same"); DrawGraph(gE11[3], wcl[1], "E2");
 
//=============================================================================
  can->cd();
  TPad* p12 = new TPad("cp12", "p12", 0.4, 0.55, 0.7, 1.);
  //p12->SetLogy();
  p12->Range(0., 0., 1., 1.);
  p12->SetFillColor(0);
  p12->SetBorderMode(0);
  p12->SetBorderSize(0);
  p12->SetRightMargin(0.);
  p12->SetLeftMargin(0.);
  p12->SetTopMargin(0.02);
  p12->SetBottomMargin(0.);
  p12->SetFrameFillStyle(0);
  p12->SetFrameBorderMode(0);
  p12->Draw();
  p12->cd();
  auto hfm12(p12->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm12, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm12->GetXaxis()->SetNdivisions(505);
  hfm12->GetYaxis()->SetNdivisions(505);
  DrawHisto(h12[0], wcl[0], wmk[0], "same"); DrawGraph(gE12[0], wcl[0], "E2");
  DrawHisto(h12[1], wcl[3], wmk[2], "same"); DrawGraph(gE12[1], wcl[3], "E2");
  DrawHisto(h12[2], wcl[2], wmk[1], "same"); DrawGraph(gE12[2], wcl[2], "E2");
  DrawHisto(h12[3], wcl[1], wmk[3], "same"); DrawGraph(gE12[3], wcl[1], "E2");
 
//=============================================================================
  can->cd();
  TPad* p13 = new TPad("cp13", "p13", 0.7, 0.55, 1., 1.);
  //p13->SetLogy();
  p13->Range(0., 0., 1., 1.);
  p13->SetFillColor(0);
  p13->SetBorderMode(0);
  p13->SetBorderSize(0);
  p13->SetRightMargin(0.03);
  p13->SetLeftMargin(0.);
  p13->SetTopMargin(0.02);
  p13->SetBottomMargin(0.0);
  p13->SetFrameFillStyle(0);
  p13->SetFrameBorderMode(0);
  p13->Draw();
  p13->cd();
  auto hfm13(p13->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm13, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm13->GetXaxis()->SetNdivisions(505);
  hfm13->GetYaxis()->SetNdivisions(505);
  DrawHisto(h13[0], wcl[0], wmk[0], "same"); DrawGraph(gE13[0], wcl[0], "E2");
  DrawHisto(h13[1], wcl[3], wmk[2], "same"); DrawGraph(gE13[1], wcl[3], "E2");
  DrawHisto(h13[2], wcl[2], wmk[1], "same"); DrawGraph(gE13[2], wcl[2], "E2");
  DrawHisto(h13[3], wcl[1], wmk[3], "same"); DrawGraph(gE13[3], wcl[1], "E2");

//=============================================================================
  can->cd();
  TPad* p21 = new TPad("cp21", "p21", 0., 0.55, 0.4, 0.);
  p21->Range(0., 0., 1., 1.);
  p21->SetFillColor(0);
  p21->SetBorderMode(0);
  p21->SetBorderSize(0);
  p21->SetRightMargin(0.);
  p21->SetLeftMargin(0.22);
  p21->SetTopMargin(0.);
  p21->SetBottomMargin(0.2);
  p21->SetFrameFillStyle(0);
  p21->SetFrameBorderMode(0);
  p21->Draw();
  p21->cd();
  auto hfm21(p21->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm21, "", stny2, dlsx, dlsy2, dtsx, dtsy2, dtox, dtoy2);
  hfm21->GetXaxis()->SetNdivisions(505);
  hfm21->GetYaxis()->SetNdivisions(505);
  DrawHisto(h21[0], wcl[0], wmk[0], "same"); DrawGraph(gE21[0], wcl[0], "E2");
  DrawHisto(h21[1], wcl[3], wmk[2], "same"); DrawGraph(gE21[1], wcl[3], "E2");
  DrawHisto(h21[2], wcl[2], wmk[1], "same"); DrawGraph(gE21[2], wcl[2], "E2");
  DrawHisto(h21[3], wcl[1], wmk[3], "same"); DrawGraph(gE21[3], wcl[1], "E2");

//=============================================================================
  can->cd();
  TPad* p22 = new TPad("cp22", "p22", 0.4, 0.55, 0.7, 0.);
  p22->Range(0., 0., 1., 1.);
  p22->SetFillColor(0);
  p22->SetBorderMode(0);
  p22->SetBorderSize(0);
  p22->SetRightMargin(0.);
  p22->SetLeftMargin(0.);
  p22->SetTopMargin(0.0);
  p22->SetBottomMargin(0.2);
  p22->SetFrameFillStyle(0);
  p22->SetFrameBorderMode(0);
  p22->Draw();
  p22->cd();
  auto hfm22(p22->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm22, stnx, stny2, dlsx, dlsy2, dtsx, dtsy2, dtox, dtoy2);
  hfm22->GetXaxis()->SetNdivisions(505);
  hfm22->GetYaxis()->SetNdivisions(505);
  hfm22->GetXaxis()->CenterTitle();
  DrawHisto(h22[0], wcl[0], wmk[0], "same"); DrawGraph(gE22[0], wcl[0], "E2");
  DrawHisto(h22[1], wcl[3], wmk[2], "same"); DrawGraph(gE22[1], wcl[3], "E2");
  DrawHisto(h22[2], wcl[2], wmk[1], "same"); DrawGraph(gE22[2], wcl[2], "E2");
  DrawHisto(h22[3], wcl[1], wmk[3], "same"); DrawGraph(gE22[3], wcl[1], "E2");

//=============================================================================
  can->cd();
  TPad* p23 = new TPad("cp23", "p23", 0.7, 0.55, 1., 0.);
  p23->Range(0., 0., 1., 1.);
  p23->SetFillColor(0);
  p23->SetBorderMode(0);
  p23->SetBorderSize(0);
  p23->SetRightMargin(0.03);
  p23->SetLeftMargin(0.);
  p23->SetTopMargin(0.0);
  p23->SetBottomMargin(0.2);
  p23->SetFrameFillStyle(0);
  p23->SetFrameBorderMode(0);
  p23->Draw();
  p23->cd();
  auto hfm23(p23->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm23, "", stny2, dlsx, dlsy2, dtsx, dtsy2, dtox, dtoy2);
  hfm23->GetXaxis()->SetNdivisions(503);
  hfm23->GetYaxis()->SetNdivisions(505);
  DrawHisto(h23[0], wcl[0], wmk[0], "same"); DrawGraph(gE23[0], wcl[0], "E2");
  DrawHisto(h23[1], wcl[3], wmk[2], "same"); DrawGraph(gE23[1], wcl[3], "E2");
  DrawHisto(h23[2], wcl[2], wmk[1], "same"); DrawGraph(gE23[2], wcl[2], "E2");
  DrawHisto(h23[3], wcl[1], wmk[3], "same"); DrawGraph(gE23[3], wcl[1], "E2");
  

#if 0 


  auto leg(new TLegend(0.55, 0.5, 0.98, 0.75)); SetupLegend(leg);
  leg->AddEntry(h[0], "Inclusive", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[2], "Perp. cone", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[1], "#it{R}(particle, jet) < 0.4", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[3], "Particles in jets", "P")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.82, 0.9, "ALICE");
  tex->DrawLatex(0.16, 0.8, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");
  tex->DrawLatex(0.16, 0.7, "|#eta_{particle}| < 0.75");
  
  //tex->DrawLatex(0.16, 0.82, "#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}");
  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
#endif
  CanvasEnd(can);
  return;
}

