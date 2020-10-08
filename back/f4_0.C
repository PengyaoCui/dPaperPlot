#include "inc/PyJetUtils.h"

void f4_0(){
  
  auto f = TFile::Open("./data/pp.root", "read");
  auto lK = (TList*)f->Get("Kshort");
  auto lL = (TList*)f->Get("Lambda_sum");
  auto lX = (TList*)f->Get("Xi");
  auto lO = (TList*)f->Get("Omega");
  f->Close();

//=============================================================================
  TH1D *hK[4]; TH1D *hL[4]; TH1D *hX[4]; TH1D *hO[4]; TGraph *gEK[4]; TGraph *gEL[4]; TGraph *gEX[4]; TGraph *gEO[4];

  hK[0] = (TH1D*)lK->FindObject(Form("InclCen")); gEK[0] = (TGraphErrors*)lK->FindObject(Form("Inclerr"));
  hK[1] = (TH1D*)lK->FindObject(Form("JCCen"));   gEK[1] = (TGraphErrors*)lK->FindObject(Form("JCerr"));
  hK[2] = (TH1D*)lK->FindObject(Form("UECen"));   gEK[2] = (TGraphErrors*)lK->FindObject(Form("UEerr"));
  hK[3] = (TH1D*)lK->FindObject(Form("JECen"));   gEK[3] = (TGraphErrors*)lK->FindObject(Form("JEerr"));

  hL[0] = (TH1D*)lL->FindObject(Form("InclCen")); gEL[0] = (TGraphErrors*)lL->FindObject(Form("Inclerr"));
  hL[1] = (TH1D*)lL->FindObject(Form("JCCen"));   gEL[1] = (TGraphErrors*)lL->FindObject(Form("JCerr"));
  hL[2] = (TH1D*)lL->FindObject(Form("UECen"));   gEL[2] = (TGraphErrors*)lL->FindObject(Form("UEerr"));
  hL[3] = (TH1D*)lL->FindObject(Form("JECen"));   gEL[3] = (TGraphErrors*)lL->FindObject(Form("JEerr"));

  hX[0] = (TH1D*)lX->FindObject(Form("InclCen")); gEX[0] = (TGraphErrors*)lX->FindObject(Form("Inclerr"));
  hX[1] = (TH1D*)lX->FindObject(Form("JCCen"));   gEX[1] = (TGraphErrors*)lX->FindObject(Form("JCerr"));
  hX[2] = (TH1D*)lX->FindObject(Form("UECen"));   gEX[2] = (TGraphErrors*)lX->FindObject(Form("UEerr"));
  hX[3] = (TH1D*)lX->FindObject(Form("JECen"));   gEX[3] = (TGraphErrors*)lX->FindObject(Form("JEerr"));

  hO[0] = (TH1D*)lO->FindObject(Form("InclCen")); gEO[0] = (TGraphErrors*)lO->FindObject(Form("Inclerr"));
  hO[1] = (TH1D*)lO->FindObject(Form("JCCen"));   gEO[1] = (TGraphErrors*)lO->FindObject(Form("JCerr"));
  hO[2] = (TH1D*)lO->FindObject(Form("UECen"));   gEO[2] = (TGraphErrors*)lO->FindObject(Form("UEerr"));
  hO[3] = (TH1D*)lO->FindObject(Form("JECen"));   gEO[3] = (TGraphErrors*)lO->FindObject(Form("JEerr"));

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(5e-7), dfuy(5.);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  
  auto can(MakeCanvas("f4_0"));

  TPad *p1= nullptr; TPad *p2= nullptr; TPad *p3= nullptr; TPad *p4 = nullptr;

  p1 = MakePadTL("p1"); can->cd(); p1->SetLogy(); 
  p2 = MakePadTR("p2"); can->cd(); p2->SetLogy();
  p3 = MakePadBL("p3"); can->cd(); p3->SetLogy();
  p4 = MakePadBR("p4"); can->cd(); p4->SetLogy();

  p1->cd();
  auto hfm(p1->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);
  hfm->GetXaxis()->CenterTitle(kTRUE);
  DrawHisto(hK[0], wcl[0], wmk[0], "same"); DrawGraph(gEK[0], wcl[0], "E2");
  DrawHisto(hK[1], wcl[3], wmk[3], "same"); DrawGraph(gEK[1], wcl[3], "E2");
  DrawHisto(hK[2], wcl[2], wmk[2], "same"); DrawGraph(gEK[2], wcl[2], "E2");
  DrawHisto(hK[3], wcl[1], wmk[1], "same"); DrawGraph(gEK[3], wcl[1], "E2");
  //tex->DrawLatex(0.25, 0.1, "K^{0}_{S}");
  can->cd();
 
  p2->cd();
  hfm = p2->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);
  hfm->GetXaxis()->CenterTitle(kTRUE);
  DrawHisto(hL[0], wcl[0], wmk[0], "same"); DrawGraph(gEL[0], wcl[0], "E2");
  DrawHisto(hL[1], wcl[3], wmk[3], "same"); DrawGraph(gEL[1], wcl[3], "E2");
  DrawHisto(hL[2], wcl[2], wmk[2], "same"); DrawGraph(gEL[2], wcl[2], "E2");
  DrawHisto(hL[3], wcl[1], wmk[1], "same"); DrawGraph(gEL[3], wcl[1], "E2");
  //tex->DrawLatex(0.25, 0.1, "#Lambda + #bar{#Lambda}");
  can->cd();

  p3->cd();
  hfm = p3->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);
  hfm->GetXaxis()->CenterTitle(kTRUE);
  DrawHisto(hL[0], wcl[0], wmk[0], "same"); DrawGraph(gEL[0], wcl[0], "E2");
  DrawHisto(hL[1], wcl[3], wmk[3], "same"); DrawGraph(gEL[1], wcl[3], "E2");
  DrawHisto(hL[2], wcl[2], wmk[2], "same"); DrawGraph(gEL[2], wcl[2], "E2");
  DrawHisto(hL[3], wcl[1], wmk[1], "same"); DrawGraph(gEL[3], wcl[1], "E2");
  //tex->DrawLatex(0.25, 0.1, "#Lambda + #bar{#Lambda}");
  can->cd();
 
  p4->cd();
  hfm = p4->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);
  hfm->GetXaxis()->CenterTitle(kTRUE);
  DrawHisto(hL[0], wcl[0], wmk[0], "same"); DrawGraph(gEL[0], wcl[0], "E2");
  DrawHisto(hL[1], wcl[3], wmk[3], "same"); DrawGraph(gEL[1], wcl[3], "E2");
  DrawHisto(hL[2], wcl[2], wmk[2], "same"); DrawGraph(gEL[2], wcl[2], "E2");
  DrawHisto(hL[3], wcl[1], wmk[1], "same"); DrawGraph(gEL[3], wcl[1], "E2");
  //tex->DrawLatex(0.25, 0.1, "#Lambda + #bar{#Lambda}");
  can->cd();



  auto leg(new TLegend(0.72, 0.65, 0.98, 0.86)); SetupLegend(leg);
  leg->AddEntry(hK[0], "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hK[1], "JC", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hK[2], "UE", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hK[3], "JE", "LP")->SetTextSizePixels(24);
  //leg->AddEntry(gE[0], "Sys. Error", "f")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.16, 0.3, "#it{R}(K^{0}_{S}, jet) < 0.4, |#eta_{K^{0}_{S}}| < 0.75");
  tex->DrawLatex(0.16, 0.2, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");
  tex->DrawLatex(0.86, 0.9, "K^{0}_{S}");
  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

