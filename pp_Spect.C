#include "inc/PyJetUtils.h"

void pp_Spect(){
 
  TString sp[] = {"Kshort", "Lambda_sum", "Xi", "Omega"};
  TString sc[] = {"Incl", "JC", "UE", "JE"};
  const auto np = 4;
  const auto nc = 4;
  TList* l[np]; TH1D* h[np][nc]; TGraph *gE[np][nc];
  auto f = TFile::Open("./data/pp.root", "read");


  for(int p = 0; p<np; p++ ){
    l[p] = (TList*)f->Get(sp[p]);
    h[p][0] = (TH1D*)l[p]->FindObject(Form("InclCen")); gE[p][0] = (TGraphErrors*)l[p]->FindObject(Form("Inclerr"));
    h[p][1] = (TH1D*)l[p]->FindObject(Form("JCCen"));   gE[p][1] = (TGraphErrors*)l[p]->FindObject(Form("JCerr"));
    h[p][2] = (TH1D*)l[p]->FindObject(Form("UECen"));   gE[p][2] = (TGraphErrors*)l[p]->FindObject(Form("UEerr"));
    h[p][3] = (TH1D*)l[p]->FindObject(Form("JECen"));   gE[p][3] = (TGraphErrors*)l[p]->FindObject(Form("JEerr"));
    cout<<sp[p]<<" UE fraction in first p_T bin "<<h[p][2]->GetXaxis()->GetBinLowEdge(1)<<"-"<<h[p][2]->GetXaxis()->GetBinUpEdge(1)<<" = "<<(h[p][2]->GetBinContent(1)/h[p][1]->GetBinContent(1))*100.<<"%"<<endl;

  }
  f->Close();

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(2e-6), dfuy(4e-1);
  
  auto dlsx(0.06), dlsy(0.06);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.20), dtoy(1.05);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  auto can(MakeCanvas("pp_Spect", 900, 800));
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
  pad1->SetLogy();

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
  pad2->SetLogy();

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
  pad3->SetLogy();

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
  pad4->SetLogy();


  //auto pad1(MakePads("pad1", 0., 1., 0.5, 0.5)); pad1->SetLogy(); can->cd(); 
  //auto pad2(MakePads("pad2", 0.5, 1., 1., 0.5)); pad2->SetLogy(); can->cd(); 
  //auto pad3(MakePads("pad3", 0., 0.5, 0.5, 0.)); pad3->SetLogy(); can->cd(); 
  auto pad5 = MakePad("pad5", 0., 1., 1., 0.); pad5->SetBottomMargin(0.); pad5->SetLeftMargin(0.); can->cd();

  pad1->cd();
  auto hfm1(pad1->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm1, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm1->GetXaxis()->SetNdivisions(510);
  hfm1->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[0][0], wcl[0], wmk[0], "same"); DrawGraph(gE[0][0], wcl[0], "E2");
  DrawHisto(h[0][1], wcl[3], wmk[2], "same"); DrawGraph(gE[0][1], wcl[3], "E2");
  DrawHisto(h[0][2], wcl[2], wmk[1], "same"); DrawGraph(gE[0][2], wcl[2], "E2");
  DrawHisto(h[0][3], wcl[1], wmk[3], "same"); DrawGraph(gE[0][3], wcl[1], "E2");
  
  
  can->cd();
  pad2->cd();
  dfly = 1e-6; dfuy=2e-1;
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
  dfly = 2e-6; dfuy=8e-3;
  auto hfm3(pad3->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm3, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm3->GetXaxis()->SetNdivisions(510);
  hfm3->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[2][0], wcl[0], wmk[0], "same"); DrawGraph(gE[2][0], wcl[0], "E2");
  DrawHisto(h[2][1], wcl[3], wmk[2], "same"); DrawGraph(gE[2][1], wcl[3], "E2");
  DrawHisto(h[2][2], wcl[2], wmk[1], "same"); DrawGraph(gE[2][2], wcl[2], "E2");
  DrawHisto(h[2][3], wcl[1], wmk[3], "same"); DrawGraph(gE[2][3], wcl[1], "E2");

  can->cd();
  pad4->cd();
  dfly = 3e-6; dfuy=4e-3;
  auto hfm4(pad4->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm4, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm4->GetXaxis()->SetNdivisions(510);
  hfm4->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[3][0], wcl[0], wmk[0], "same"); DrawGraph(gE[3][0], wcl[0], "E2");
  DrawHisto(h[3][1], wcl[3], wmk[2], "same"); DrawGraph(gE[3][1], wcl[3], "E2");
  DrawHisto(h[3][2], wcl[2], wmk[1], "same"); DrawGraph(gE[3][2], wcl[2], "E2");
  DrawHisto(h[3][3], wcl[1], wmk[3], "same"); DrawGraph(gE[3][3], wcl[1], "E2");
  
  auto leg(new TLegend(0.48, 0.62, 0.95, 0.92)); SetupLegend(leg);
  leg->AddEntry(h[0][0], "Inclusive", "P")->SetTextSizePixels(22);
  leg->AddEntry(h[0][2], "Perp. cone", "P")->SetTextSizePixels(22);
  leg->AddEntry(h[0][1], "#it{R}(par, jet) < 0.4", "P")->SetTextSizePixels(22);
  leg->AddEntry(h[0][3], "Particle in jets", "P")->SetTextSizePixels(22);
  //leg->AddEntry(gE[0], "Sys. Error", "f")->SetTextSizePixels(22);
  leg->Draw();


  can->cd();
  pad5->cd();
  pad5->SetFillStyle(4000);

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(11);
  tex->DrawLatex(0.23, 0.95, "ALICE pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.77, 0.95, "Particle:|#it{#eta}| < 0.75");
  tex->DrawLatex(0.27, 0.46, "Jet: anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.3, 0.42, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}");
  tex->DrawLatex(0.36, 0.38, "|#it{#eta}_{jet}| < 0.35");

  tex->DrawLatex(0.25, 0.03, stnx);
  tex->DrawLatex(0.73, 0.03, stnx);
  
  tex->DrawLatex(0.125, 0.6, "K^{0}_{S}");
  tex->DrawLatex(0.59, 0.6, "#Lambda + #bar{#Lambda}");
  tex->DrawLatex(0.125, 0.125, "#Xi^{-} + #bar{#Xi}^{+}");
  tex->DrawLatex(0.59, 0.125, "#Omega^{-} + #bar{#Omega}^{+}");

  auto Tex(new TLatex());
  Tex->SetNDC();
  Tex->SetTextSizePixels(11);
  Tex->SetTextAngle(90);
  Tex->DrawLatex(0.03, 0.7, stny);
  Tex->DrawLatex(0.03, 0.2, stny);

  can->cd();  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

