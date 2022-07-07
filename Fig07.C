#include "inc/PyJetUtils.h"

void Fig07(){
 
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

  const TString sj("Jet10");
  const TString sd("pp13d00TeV");  // pp13d00TeV:   pp at 13   TeV
                                    // pp05d02TeVrs: pp at 5.02 TeV
                                    //               with rapidity shift
                                    //               used to fit p-Pb acceptance

  TH1D *hJE[np][nm]; TGraphErrors *gJE[np]; TH1D* hJEm[nm-1];TH1D* hJEMid[np]; TH1D* hJEMin[np]; TH1D* hJEMax[np];
  TH1D *hIn[np][nm]; TGraphErrors *gIn[np]; TH1D* hInm[nm-1];TH1D* hInMid[np]; TH1D* hInMin[np]; TH1D* hInMax[np];

  for (auto i=0; i<nm; ++i){
    hIn[0][i] = RatioLK(i, sd);
    hIn[1][i] = RatioXK(i, sd);
    hIn[2][i] = RatioOK(i, sd);
    hIn[3][i] = RatioXL(i, sd);
    hIn[4][i] = RatioOL(i, sd);
    hIn[5][i] = RatioOX(i, sd);

    hJE[0][i] = RatioLK(i, sd, sj, "JC04", "PC04");
    hJE[1][i] = RatioXK(i, sd, sj, "JC04", "PC04");
    hJE[2][i] = RatioOK(i, sd, sj, "JC04", "PC04");
    hJE[3][i] = RatioXL(i, sd, sj, "JC04", "PC04");
    hJE[4][i] = RatioOL(i, sd, sj, "JC04", "PC04");
    hJE[5][i] = RatioOX(i, sd, sj, "JC04", "PC04");
  }

  for(int p = 0; p<np; p++ ){
    hInm[0] = hIn[p][0];
    hJEm[0] = hJE[p][0];
    hInm[1] = hIn[p][2];
    hJEm[1] = hJE[p][2];
    hInm[2] = hIn[p][3];
    hJEm[2] = hJE[p][3];
    hInMax[p] = MaxHistograms(3, hInm);
    hInMin[p] = MinHistograms(3, hInm);
    hInMid[p] = (TH1D*)hInMax[p]->Clone(Form("Inmid_%s", sp[p].Data()));
    hInMid[p]->Add(hInMin[p]);
    hInMid[p]->Scale(0.5);
    const int nBins = hInMid[p]->GetNbinsX();
    double X[nBins];
    double Y[nBins];
    double eX[nBins];
    double eY[nBins];
    for(int j = 1; j<= hInMid[p]->GetNbinsX(); j++){
      X[j-1] = hInMid[p]->GetBinCenter(j);
      eX[j-1] = 0.;
      Y[j-1] = hInMid[p]->GetBinContent(j);
      eY[j-1] = (hInMax[p]->GetBinContent(j) - hInMin[p]->GetBinContent(j))/2.;
    }
    gIn[p] = new TGraphErrors(nBins, X, Y, eX, eY);
    
    hJEMax[p] = MaxHistograms(3, hJEm);
    hJEMin[p] = MinHistograms(3, hJEm);
    hJEMid[p] = (TH1D*)hJEMax[p]->Clone(Form("JEmid_%s", sp[p].Data()));
    hJEMid[p]->Add(hJEMin[p]);
    hJEMid[p]->Scale(0.5);
    const int nbins = hJEMid[p]->GetNbinsX();
    double x[nbins];
    double y[nbins];
    double ex[nbins];
    double ey[nbins];
    for(int j = 1; j<= hJEMid[p]->GetNbinsX(); j++){
      x[j-1] = hJEMid[p]->GetBinCenter(j);
      ex[j-1] = 0.;
      y[j-1] = hJEMid[p]->GetBinContent(j);
      ey[j-1] = (hJEMax[p]->GetBinContent(j) - hJEMin[p]->GetBinContent(j))/2.;
    }
    gJE[p] = new TGraphErrors(nbins, x, y, ex, ey);
  }

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.07), dfuy(0.62);
  
  auto dlsx(0.074), dlsy(0.074);
  auto dtsx(0.07), dtsy(0.07);
  auto dtox(1.20), dtoy(1.05);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("Baryon-to-meson ratio");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  auto can(MakeCanvas("Fig07", 1200, 700));
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
  //DrawHisto(h[0][2], wcl[2], wmk[1], "same"); DrawGraph(gE[0][2], wcl[2], "E2");
  DrawHisto(h[0][3], wcl[1], wmk[3], "same"); DrawGraph(gE[0][3], wcl[1], "E2");
  DrawGraphError(gIn[0],  wcl[0], wcl[0], "E3");
  DrawGraphError(gJE[0],  wcl[1], wcl[1], "E3");
 
  
  can->cd();
  pad2->cd();
  dfly = 0.0001; dfuy=0.11;
  auto hfm2(pad2->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm2, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm2->GetXaxis()->SetNdivisions(510);
  hfm2->GetYaxis()->SetNdivisions(505);
  DrawHisto(h[1][0], wcl[0], wmk[0], "same"); DrawGraph(gE[1][0], wcl[0], "E2");
  //DrawHisto(h[1][1], wcl[3], wmk[2], "same"); DrawGraph(gE[1][1], wcl[3], "E2");
  //DrawHisto(h[1][2], wcl[2], wmk[1], "same"); DrawGraph(gE[1][2], wcl[2], "E2");
  DrawHisto(h[1][3], wcl[1], wmk[3], "same"); DrawGraph(gE[1][3], wcl[1], "E2");
  DrawGraphError(gIn[1],  wcl[0], wcl[0], "E3");
  DrawGraphError(gJE[1],  wcl[1], wcl[1], "E3");
  
  auto Leg(new TLegend(0.62, 0.8, 0.95, 0.9)); SetupLegend(Leg);
  Leg->AddEntry(gIn[3], "CR-BLC", "F")->SetTextSizePixels(24);
  Leg->Draw();
  can->cd();
  pad3->cd();
  dfly = 0.; dfuy=.024;
  auto hfm3(pad3->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm3, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm3->GetXaxis()->SetNdivisions(510);
  hfm3->GetYaxis()->SetNdivisions(503);
  DrawHisto(h[2][0], wcl[0], wmk[0], "same"); DrawGraph(gE[2][0], wcl[0], "E2");
  //DrawHisto(h[2][1], wcl[3], wmk[2], "same"); DrawGraph(gE[2][1], wcl[3], "E2");
  //DrawHisto(h[2][2], wcl[2], wmk[1], "same"); DrawGraph(gE[2][2], wcl[2], "E2");
  DrawHisto(h[2][3], wcl[1], wmk[3], "same"); DrawGraph(gE[2][3], wcl[1], "E2");
  DrawGraphError(gIn[2],  wcl[0], wcl[0], "E3");
  DrawGraphError(gJE[2],  wcl[1], wcl[1], "E3");

  can->cd();
  pad4->cd();
  dfly = 0.04; dfuy=0.23;
  auto hfm4(pad4->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm4, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm4->GetXaxis()->SetNdivisions(510);
  hfm4->GetYaxis()->SetNdivisions(503);
  DrawHisto(h[3][0], wcl[0], wmk[0], "same"); DrawGraph(gE[3][0], wcl[0], "E2");
  //DrawHisto(h[3][1], wcl[3], wmk[2], "same"); DrawGraph(gE[3][1], wcl[3], "E2");
  //DrawHisto(h[3][2], wcl[2], wmk[1], "same"); DrawGraph(gE[3][2], wcl[2], "E2");
  DrawHisto(h[3][3], wcl[1], wmk[3], "same"); DrawGraph(gE[3][3], wcl[1], "E2");
  DrawGraphError(gIn[3],  wcl[0], wcl[0], "E3");
  DrawGraphError(gJE[3],  wcl[1], wcl[1], "E3");
 
  can->cd();
  pad5->cd();
  dfly = 0.; dfuy=0.07;
  auto hfm5(pad5->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm5, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm5->GetXaxis()->SetNdivisions(510);
  hfm5->GetYaxis()->SetNdivisions(503);
  DrawHisto(h[4][0], wcl[0], wmk[0], "same"); DrawGraph(gE[4][0], wcl[0], "E2");
  //DrawHisto(h[4][1], wcl[3], wmk[2], "same"); DrawGraph(gE[4][1], wcl[3], "E2");
  //DrawHisto(h[4][2], wcl[2], wmk[1], "same"); DrawGraph(gE[4][2], wcl[2], "E2");
  DrawHisto(h[4][3], wcl[1], wmk[3], "same"); DrawGraph(gE[4][3], wcl[1], "E2");
  DrawGraphError(gIn[4],  wcl[0], wcl[0], "E3");
  DrawGraphError(gJE[4],  wcl[1], wcl[1], "E3");
  
  auto leg(new TLegend(0.45, 0.6, 0.97, 0.9)); SetupLegend(leg);
  leg->AddEntry(h[0][0], "Inclusive", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[0][3], "Particle in jets", "P")->SetTextSizePixels(24);
  leg->Draw();

  can->cd();
  pad6->cd();
  dfly = 0.; dfuy=.35;
  auto hfm6(pad6->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm6, "", "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm6->GetXaxis()->SetNdivisions(510);
  hfm6->GetYaxis()->SetNdivisions(503);
  DrawHisto(h[5][0], wcl[0], wmk[0], "same"); DrawGraph(gE[5][0], wcl[0], "E2");
  //DrawHisto(h[5][1], wcl[3], wmk[2], "same"); DrawGraph(gE[5][1], wcl[3], "E2");
  //DrawHisto(h[5][2], wcl[2], wmk[1], "same"); DrawGraph(gE[5][2], wcl[2], "E2");
  DrawHisto(h[5][3], wcl[1], wmk[3], "same"); DrawGraph(gE[5][3], wcl[1], "E2");
  DrawGraphError(gIn[5],  wcl[0], wcl[0], "E3");
  DrawGraphError(gJE[5],  wcl[1], wcl[1], "E3");
 


  can->cd();
  pad7->cd();
  pad7->SetFillStyle(4000);

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(11);
  tex->DrawLatex(0.1, 0.94, "ALICE pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.81, 0.94, "Particle |#it{#eta}| < 0.75");
  tex->DrawLatex(0.825, 0.45, "Jet: anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.845, 0.4, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}");
  tex->DrawLatex(0.89, 0.35, "|#it{#eta}_{jet}| < 0.35");

  
  tex->DrawLatex(0.28, 0.63, "#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}");
  tex->DrawLatex(0.60, 0.63, "#frac{#Xi^{-} + #bar{#Xi}^{+}}{2K^{0}_{S}}");
  tex->DrawLatex(0.91, 0.83, "#frac{#Omega^{-} + #bar{#Omega}^{+}}{2K^{0}_{S}}");
  tex->DrawLatex(0.28, 0.15, "#frac{#Xi^{-} + #bar{#Xi}^{+}}{#Lambda + #bar{#Lambda}}");
  tex->DrawLatex(0.42, 0.4, "#frac{#Omega^{-} + #bar{#Omega}^{+}}{#Lambda + #bar{#Lambda}}");
  tex->DrawLatex(0.91, 0.25, "#frac{#Omega^{-} + #bar{#Omega}^{+}}{#Xi^{-} + #bar{#Xi}^{+}}");
  
  auto TEX(new TLatex());
  TEX->SetNDC();
  TEX->SetTextSizePixels(13);
  TEX->DrawLatex(0.89, 0.02, stnx);

  auto Tex(new TLatex());
  Tex->SetNDC();
  Tex->SetTextSizePixels(13);
  Tex->SetTextAngle(90);
  Tex->DrawLatex(0.03, 0.63, stny);
  stny="Baryon-to-baryon ratio";
  Tex->DrawLatex(0.03, 0.14, stny);

  can->cd();  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

