#include "inc/PyJetUtils.h"

void FigB6(){
 
  TString sc[] = {"010", "1040", "40100", "0100"};
  const auto nc = 4;
  TList* l[nc]; TH1D* h[3][nc]; TGraph *gE[3][nc];//Incl, UE, JE

  auto f = TFile::Open("./data/pPb.root", "read");

  for(int c = 0; c<nc; c++ ){
    l[c] = (TList*)f->Get(Form("Xi_toLRatio_%s", sc[c].Data()));
    h[0][c] = (TH1D*)l[c]->FindObject(Form("hInR")); gE[0][c] = (TGraphErrors*)l[c]->FindObject(Form("InRerr"));
    h[1][c] = (TH1D*)l[c]->FindObject(Form("hUER")); gE[1][c] = (TGraphErrors*)l[c]->FindObject(Form("UERerr"));
    h[2][c] = (TH1D*)l[c]->FindObject(Form("hJER")); gE[2][c] = (TGraphErrors*)l[c]->FindObject(Form("JERerr"));
  }

  f->Close();

//=============================================================================
  auto dflx(0.), dfux(12.4);
  auto dfly(0.0), dfuy(0.35);
  
  auto dlsx(0.065), dlsy(0.065);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.20), dtoy(1.05);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("(#Xi^{-} + #bar{#Xi}^{+})/(#Lambda + #bar{#Lambda})");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  auto can(MakeCanvas("FigB6", 1000, 350));
//=====Make pads===============================================================

  //auto pad1(MakePads("pad1", 0.04, 1., 0.36, 0.)); pad1->SetBottomMargin(0.15); pad1->SetLeftMargin(0.12); pad1->SetRightMargin(0.03); can->cd();
  //auto pad2(MakePads("pad2", 0.36, 1., 0.68, 0.)); pad2->SetBottomMargin(0.15); pad2->SetLeftMargin(0.12); pad2->SetRightMargin(0.03); can->cd();
  //auto pad3(MakePads("pad3", 0.68, 1., 1.,   0.)); pad3->SetBottomMargin(0.15); pad3->SetLeftMargin(0.12); pad3->SetRightMargin(0.03); can->cd(); 
  auto pad1(MakePads("pad1", 0.03, 1., 0.37, 0.)); pad1->SetBottomMargin(0.15); pad1->SetLeftMargin(0.12); pad1->SetRightMargin(0.); can->cd();
  auto pad2(MakePads("pad2", 0.37, 1., 0.69, 0.)); pad2->SetBottomMargin(0.15); pad2->SetLeftMargin(0.);   pad2->SetRightMargin(0.); can->cd();
  auto pad3(MakePads("pad3", 0.69, 1., 1.,   0.)); pad3->SetBottomMargin(0.15); pad3->SetLeftMargin(0.);   pad3->SetRightMargin(0.03); can->cd(); 
  auto pad0 = MakePad("pad7", 0., 1., 1., 0.); pad0->SetBottomMargin(0.); pad0->SetLeftMargin(0.); can->cd();

  pad1->cd();
  auto hfm1(pad1->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm1, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm1->GetXaxis()->SetNdivisions(510);
  hfm1->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[0][0], wcl[0], wmk[0], "same"); DrawGraph(gE[0][0], wcl[0], "E2");
  DrawHisto(h[1][0], wcl[2], wmk[1], "same"); DrawGraph(gE[1][0], wcl[2], "E2");
  DrawHisto(h[2][0], wcl[1], wmk[3], "same"); DrawGraph(gE[2][0], wcl[1], "E2");
  //DrawHisto(h[0][3], wcl[1], wmk[1], "same"); DrawGraph(gE[0][3], wcl[1], "E2");
  
  
  can->cd();
  pad2->cd();
  dflx = 0.0001;
 // dfly = 3e-6; dfuy=4e-1;
  auto hfm2(pad2->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm2, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm2->GetXaxis()->SetNdivisions(510);
  hfm2->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[0][1], wcl[0], wmk[0], "same"); DrawGraph(gE[0][1], wcl[0], "E2");
  DrawHisto(h[1][1], wcl[2], wmk[1], "same"); DrawGraph(gE[1][1], wcl[2], "E2");
  DrawHisto(h[2][1], wcl[1], wmk[3], "same"); DrawGraph(gE[2][1], wcl[1], "E2");
  //DrawHisto(h[0][3], wcl[1], wmk[1], "same"); DrawGraph(gE[0][3], wcl[1], "E2");
  
 
  can->cd();
  pad3->cd();
  //dfly = 2e-5; dfuy=4e-2;
  auto hfm3(pad3->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm3, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm3->GetXaxis()->SetNdivisions(510);
  hfm3->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[0][2], wcl[0], wmk[0], "same"); DrawGraph(gE[0][2], wcl[0], "E2");
  DrawHisto(h[1][2], wcl[2], wmk[1], "same"); DrawGraph(gE[1][2], wcl[2], "E2");
  DrawHisto(h[2][2], wcl[1], wmk[3], "same"); DrawGraph(gE[2][2], wcl[1], "E2");
  
  //auto leg(new TLegend(0.41, 0.62, 0.97, 0.95)); SetupLegend(leg);
  auto leg(new TLegend(0.50, 0.75, 0.9, 0.95)); SetupLegend(leg);
  leg->AddEntry(h[0][0], "Inclusive", "P")->SetTextSizePixels(18);
  leg->AddEntry(h[1][0], "Perp. cone", "P")->SetTextSizePixels(18);
  leg->AddEntry(h[2][0], "Particle in jets", "P")->SetTextSizePixels(18);
  //leg->AddEntry(h[0][3], "MB p#minusPb", "P")->SetTextSizePixels(20);
  leg->Draw();



  can->cd();
  pad0->cd();
  pad0->SetFillStyle(4000);

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(20);
  tex->DrawLatex(0.08, 0.9, "ALICE p#minusPb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  //tex->DrawLatex(0.92, 0.9, "0#minus10%");
  tex->DrawLatex(0.53, 0.2, "Particle |#it{#eta}| < 0.75");
  tex->DrawLatex(0.51, 0.9, "Jet: anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.535, 0.8, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}");
  tex->DrawLatex(0.58, 0.7, "|#it{#eta}_{jet}| < 0.35");

  
  tex->DrawLatex(0.30,  0.6, "0#minus10%");
  tex->DrawLatex(0.61,  0.6, "10#minus40%");
  tex->DrawLatex(0.90,  0.6, "40#minus100%");
  
  
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
  Tex->DrawLatex(0.022, 0.5, stny);

  can->cd();  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

