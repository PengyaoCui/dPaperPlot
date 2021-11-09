#include "inc/PyJetUtils.h"

void pp_Ratio(){
 
  TString sp[] = {"Lambda_sum_toKRatio", "Xi_toKRatio", "Omega_toKRatio", "Xi_toLRatio", "Omega_toLRatio", "Omega_toXRatio"};
  TString sc[] = {"Incl", "JC", "UE", "JE"};
  const auto np = 6;
  const auto nc = 4;
  TList* l[np]; TH1D* h[np][nc]; TGraph *gE[np][nc];
  auto f = TFile::Open("./data/pp.root", "read");


  for(int p = 0; p<np; p++ ){
    l[p] = (TList*)f->Get(sp[p]);
    h[p][0] = (TH1D*)l[p]->FindObject(Form("hInR"));   gE[p][0] = (TGraphErrors*)l[p]->FindObject(Form("InRerr"));
    h[p][1] = (TH1D*)l[p]->FindObject(Form("hJCR"));   gE[p][1] = (TGraphErrors*)l[p]->FindObject(Form("JCRerr"));
    h[p][2] = (TH1D*)l[p]->FindObject(Form("hUER"));   gE[p][2] = (TGraphErrors*)l[p]->FindObject(Form("UERerr"));
    h[p][3] = (TH1D*)l[p]->FindObject(Form("hJER"));   gE[p][3] = (TGraphErrors*)l[p]->FindObject(Form("JERerr"));
  }
  f->Close();

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.07), dfuy(0.62);
  
  auto dlsx(0.07), dlsy(0.07);
  auto dtsx(0.07), dtsy(0.07);
  auto dtox(1.20), dtoy(1.05);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("Baryon-to-meson ratio");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  auto can(MakeCanvas("pp_Ratio", 1200, 700));
//=====Make pads===============================================================

  auto pad1(MakePads("pad1", 0.04, 1., 0.36, 0.52)); can->cd(); 
  auto pad2(MakePads("pad2", 0.36, 1., 0.68, 0.52));  can->cd(); 
  auto pad3(MakePads("pad3", 0.68, 1., 1., 0.52));  can->cd(); 
  auto pad4(MakePads("pad4", 0.04, 0.52, 0.36, 0.04)); can->cd(); 
  auto pad5(MakePads("pad5", 0.36, 0.52, 0.68, 0.04)); can->cd(); 
  auto pad6(MakePads("pad6", 0.68, 0.52, 1., 0.04)); can->cd(); 
  auto pad7 = MakePad("pad7", 0., 1., 1., 0.); pad7->SetBottomMargin(0.); pad7->SetLeftMargin(0.); can->cd();

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
  dfly = 0.0001; dfuy=0.11;
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
  dfly = 0.; dfuy=.024;
  auto hfm3(pad3->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm3, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm3->GetXaxis()->SetNdivisions(510);
  hfm3->GetYaxis()->SetNdivisions(503);
  DrawHisto(h[2][0], wcl[0], wmk[0], "same"); DrawGraph(gE[2][0], wcl[0], "E2");
  //DrawHisto(h[2][1], wcl[3], wmk[2], "same"); DrawGraph(gE[2][1], wcl[3], "E2");
  DrawHisto(h[2][2], wcl[2], wmk[1], "same"); DrawGraph(gE[2][2], wcl[2], "E2");
  DrawHisto(h[2][3], wcl[1], wmk[3], "same"); DrawGraph(gE[2][3], wcl[1], "E2");

  can->cd();
  pad4->cd();
  dfly = 0.04; dfuy=0.23;
  auto hfm4(pad4->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm4, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm4->GetXaxis()->SetNdivisions(510);
  hfm4->GetYaxis()->SetNdivisions(503);
  DrawHisto(h[3][0], wcl[0], wmk[0], "same"); DrawGraph(gE[3][0], wcl[0], "E2");
  //DrawHisto(h[3][1], wcl[3], wmk[2], "same"); DrawGraph(gE[3][1], wcl[3], "E2");
  DrawHisto(h[3][2], wcl[2], wmk[1], "same"); DrawGraph(gE[3][2], wcl[2], "E2");
  DrawHisto(h[3][3], wcl[1], wmk[3], "same"); DrawGraph(gE[3][3], wcl[1], "E2");
 
  can->cd();
  pad5->cd();
  dfly = 0.; dfuy=0.07;
  auto hfm5(pad5->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm5, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm5->GetXaxis()->SetNdivisions(510);
  hfm5->GetYaxis()->SetNdivisions(503);
  DrawHisto(h[4][0], wcl[0], wmk[0], "same"); DrawGraph(gE[4][0], wcl[0], "E2");
  //DrawHisto(h[4][1], wcl[3], wmk[2], "same"); DrawGraph(gE[4][1], wcl[3], "E2");
  DrawHisto(h[4][2], wcl[2], wmk[1], "same"); DrawGraph(gE[4][2], wcl[2], "E2");
  DrawHisto(h[4][3], wcl[1], wmk[3], "same"); DrawGraph(gE[4][3], wcl[1], "E2");

  can->cd();
  pad6->cd();
  dfly = 0.; dfuy=.35;
  auto hfm6(pad6->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm6, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm6->GetXaxis()->SetNdivisions(510);
  hfm6->GetYaxis()->SetNdivisions(503);
  DrawHisto(h[5][0], wcl[0], wmk[0], "same"); DrawGraph(gE[5][0], wcl[0], "E2");
  //DrawHisto(h[5][1], wcl[3], wmk[2], "same"); DrawGraph(gE[5][1], wcl[3], "E2");
  DrawHisto(h[5][2], wcl[2], wmk[1], "same"); DrawGraph(gE[5][2], wcl[2], "E2");
  DrawHisto(h[5][3], wcl[1], wmk[3], "same"); DrawGraph(gE[5][3], wcl[1], "E2");
 
  auto leg(new TLegend(0.45, 0.6, 0.97, 0.9)); SetupLegend(leg);
  leg->AddEntry(h[0][0], "Inclusive", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[0][2], "Perp. cone", "P")->SetTextSizePixels(24);
  //leg->AddEntry(h[0][1], "#it{R}(par, jet) < 0.4", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[0][3], "Particle in jets", "P")->SetTextSizePixels(24);
  //leg->AddEntry(gE[0], "Sys. Error", "f")->SetTextSizePixels(24);
  leg->Draw();


  can->cd();
  pad7->cd();
  pad7->SetFillStyle(4000);

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(11);
  tex->DrawLatex(0.47, 0.94, "ALICE pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.81, 0.94, "Particle:|#it{#eta}| < 0.75");
  tex->DrawLatex(0.50, 0.45, "Jet: anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.52, 0.4, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}");
  tex->DrawLatex(0.56, 0.35, "|#it{#eta}_{jet}| < 0.35");

  tex->DrawLatex(0.5, 0.02, stnx);
  
  tex->DrawLatex(0.28, 0.63, "#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}");
  tex->DrawLatex(0.60, 0.63, "#frac{#Xi^{-} + #bar{#Xi}^{+}}{2K^{0}_{S}}");
  tex->DrawLatex(0.91, 0.63, "#frac{#Omega^{-} + #bar{#Omega}^{+}}{2K^{0}_{S}}");
  tex->DrawLatex(0.28, 0.15, "#frac{#Xi^{-} + #bar{#Xi}^{+}}{#Lambda + #bar{#Lambda}}");
  tex->DrawLatex(0.60, 0.15, "#frac{#Omega^{-} + #bar{#Omega}^{+}}{#Lambda + #bar{#Lambda}}");
  tex->DrawLatex(0.91, 0.15, "#frac{#Omega^{-} + #bar{#Omega}^{+}}{#Xi^{-} + #bar{#Xi}^{+}}");

  auto Tex(new TLatex());
  Tex->SetNDC();
  Tex->SetTextSizePixels(11);
  Tex->SetTextAngle(90);
  Tex->DrawLatex(0.03, 0.63, stny);
  stny="Baryon-to-baryon ratio";
  Tex->DrawLatex(0.03, 0.15, stny);

  can->cd();  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

