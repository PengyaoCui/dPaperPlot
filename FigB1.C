#include "inc/PyJetUtils.h"

void FigB1(){
 
  TString sp[] = {"Kshort", "Lambda_sum", "Xi", "Omega"};
  TString sc[] = {"Incl", "JC", "UE", "JE"};
  const auto np = 4;
  const auto nc = 4;
  TList* l[np]; TH1D* h[np][nc]; TGraph *gE[np][nc];
  auto f = TFile::Open("./data/pPb.root", "read");


  for(int p = 0; p<np; p++ ){
    l[p] = (TList*)f->Get(Form("%s_010", sp[p].Data()));
    h[p][0] = (TH1D*)l[p]->FindObject(Form("InclCen")); gE[p][0] = (TGraphErrors*)l[p]->FindObject(Form("Inclerr"));
    h[p][1] = (TH1D*)l[p]->FindObject(Form("JCCen"));   gE[p][1] = (TGraphErrors*)l[p]->FindObject(Form("JCerr"));
    h[p][2] = (TH1D*)l[p]->FindObject(Form("UECen"));   gE[p][2] = (TGraphErrors*)l[p]->FindObject(Form("UEerr"));
    h[p][3] = (TH1D*)l[p]->FindObject(Form("JECen"));   gE[p][3] = (TGraphErrors*)l[p]->FindObject(Form("JEerr"));
  }
  f->Close();

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(1e-5), dfuy(2e0);
  
  auto dlsx(0.065), dlsy(0.065);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.20), dtoy(1.05);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  auto can(MakeCanvas("FigB1", 1000, 350));
//=====Make pads===============================================================

  auto pad1(MakePads("pad1", 0.04, 1., 0.36, 0.)); pad1->SetBottomMargin(0.15); pad1->SetLeftMargin(0.12); pad1->SetRightMargin(0.03); pad1->SetLogy(); can->cd();
  auto pad2(MakePads("pad2", 0.36, 1., 0.68, 0.)); pad2->SetBottomMargin(0.15); pad2->SetLeftMargin(0.12); pad2->SetRightMargin(0.03); pad2->SetLogy(); can->cd();
  auto pad3(MakePads("pad3", 0.68, 1., 1.,   0.)); pad3->SetBottomMargin(0.15); pad3->SetLeftMargin(0.12); pad3->SetRightMargin(0.03); pad3->SetLogy(); can->cd(); 
  auto pad0 = MakePad("pad7", 0., 1., 1., 0.); pad0->SetBottomMargin(0.); pad0->SetLeftMargin(0.); can->cd();

  pad1->cd();
  auto hfm1(pad1->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm1, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm1->GetXaxis()->SetNdivisions(510);
  hfm1->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[0][0], wcl[0], wmk[0], "same"); DrawGraph(gE[0][0], wcl[0], "E2");
  DrawHisto(h[0][1], wcl[3], wmk[2], "same"); DrawGraph(gE[0][1], wcl[3], "E2");
  DrawHisto(h[0][2], wcl[2], wmk[1], "same"); DrawGraph(gE[0][2], wcl[2], "E2");
  DrawHisto(h[0][3], wcl[1], wmk[3], "same"); DrawGraph(gE[0][3], wcl[1], "E2");
  
  //auto leg(new TLegend(0.41, 0.62, 0.97, 0.95)); SetupLegend(leg);
  auto leg(new TLegend(0.12, 0.16, 0.6, 0.47)); SetupLegend(leg);
  leg->AddEntry(h[0][0], "Inclusive", "P")->SetTextSizePixels(20);
  leg->AddEntry(h[0][2], "Perp. cone", "P")->SetTextSizePixels(20);
  leg->AddEntry(h[0][1], "#it{R}(par, jet) < 0.4", "P")->SetTextSizePixels(20);
  leg->AddEntry(h[0][3], "Particle in jets", "P")->SetTextSizePixels(20);
  //leg->AddEntry(gE[0], "Sys. Error", "f")->SetTextSizePixels(20);
  leg->Draw();

  
  can->cd();
  pad2->cd();
  dfly = 3e-6; dfuy=4e-1;
  auto hfm2(pad2->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm2, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm2->GetXaxis()->SetNdivisions(510);
  hfm2->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[1][0], wcl[0], wmk[0], "same"); DrawGraph(gE[1][0], wcl[0], "E2");
  DrawHisto(h[1][1], wcl[3], wmk[2], "same"); DrawGraph(gE[1][1], wcl[3], "E2");
  DrawHisto(h[1][2], wcl[2], wmk[1], "same"); DrawGraph(gE[1][2], wcl[2], "E2");
  DrawHisto(h[1][3], wcl[1], wmk[3], "same"); DrawGraph(gE[1][3], wcl[1], "E2");
  
  can->cd();
  pad3->cd();
  dfly = 2e-5; dfuy=4e-2;
  auto hfm3(pad3->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm3, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm3->GetXaxis()->SetNdivisions(510);
  hfm3->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[2][0], wcl[0], wmk[0], "same"); DrawGraph(gE[2][0], wcl[0], "E2");
  DrawHisto(h[2][1], wcl[3], wmk[2], "same"); DrawGraph(gE[2][1], wcl[3], "E2");
  DrawHisto(h[2][2], wcl[2], wmk[1], "same"); DrawGraph(gE[2][2], wcl[2], "E2");
  DrawHisto(h[2][3], wcl[1], wmk[3], "same"); DrawGraph(gE[2][3], wcl[1], "E2");

  

  can->cd();
  pad0->cd();
  pad0->SetFillStyle(4000);

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(20);
  tex->DrawLatex(0.09, 0.9, "ALICE p#minusPb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex->DrawLatex(0.92, 0.9, "0#minus10%");
  tex->DrawLatex(0.47, 0.9, "Particle |#it{#eta}| < 0.75");
  tex->DrawLatex(0.41, 0.2, "Jet: anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.41, 0.3, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}");
  tex->DrawLatex(0.41, 0.4, "|#it{#eta}_{jet}| < 0.35");

  
  tex->DrawLatex(0.3,  0.75, "K^{0}_{S}");
  tex->DrawLatex(0.6,  0.75, "#Lambda + #bar{#Lambda}");
  tex->DrawLatex(0.92, 0.75, "#Xi^{-} + #bar{#Xi}^{+}");
  
  auto TEX(new TLatex());
  TEX->SetNDC();
  TEX->SetTextSizePixels(22);
  //TEX->DrawLatex(0.16, 0.03, stnx);
  //TEX->DrawLatex(0.48, 0.03, stnx);
  TEX->DrawLatex(0.89, 0.03, stnx);

  auto Tex(new TLatex());
  Tex->SetNDC();
  Tex->SetTextSizePixels(22);
  Tex->SetTextAngle(90);
  Tex->DrawLatex(0.025, 0.4, stny);

  can->cd();  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

