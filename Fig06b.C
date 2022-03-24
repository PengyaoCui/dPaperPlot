#include "inc/PyJetUtils.h"

void Fig06b(){
//=============================================================================

  TString sp[] = {"Kshort", "Lambda_sum", "Xi", "Omega"};
  const auto np = 4; 

  const TString sj("Jet10");
  const TString sd("pp13d00TeV");  // pp13d00TeV:   pp at 13   TeV
                                    // pp05d02TeVrs: pp at 5.02 TeV
                                    //               with rapidity shift
                                    //               used to fit p-Pb acceptance



  TList* l[np]; TH1D* h[np]; TGraphErrors*gE[np]; TH1D*hE[np]; TGraph* g[np][nm]; TH1D* hPy[np][nm];
  TFile *f;
  f = TFile::Open("./data/pp.root", "read");
  for(int p = 0; p<np; p++ ){
    l[p] = (TList*)f->Get(sp[p]);
    h[p]  = (TH1D*)l[p]->FindObject(Form("JECen")); 
    gE[p] = (TGraphErrors*)l[p]->FindObject(Form("JEerr"));
    hE[p] = (TH1D*)l[p]->FindObject(Form("JEErr"));
    int n = h[p]->GetNbinsX();
    if(p==0) {h[p]->Scale(16.); gE[p] = ScaleGraphErrors(gE[p], 16., n);}
    if(p==1) {h[p]->Scale(4.); gE[p] = ScaleGraphErrors(gE[p], 4., n);}
    if(p==2) {h[p]->Scale(2.); gE[p] = ScaleGraphErrors(gE[p], 2., n);}
    for (auto i=0; i<nm; ++i){
      if(p==1){
        hPy[p][i] = (TH1D*)Spectrum(i, sd, "Lambda",sj, "JC04", "PC04");
      }else{
        hPy[p][i] = (TH1D*)Spectrum(i, sd, sp[p], sj, "JC04", "PC04");
      }
      if(p==0) hPy[p][i]->Scale(16.);
      if(p==1) hPy[p][i]->Scale(4.);
      if(p==2) hPy[p][i]->Scale(2.);
      g[p][i] = new TGraph(hPy[p][i]);

    }
  }
  f->Close();

//pythia to Data ratio
//=============================================================================
  TH1D* hR[np][nm]; TH1D* hMax[np]; TH1D* hMin[np]; TH1D* hMid[np]; TH1D* hRm[nm];
  TH1D* hRE[np]; TGraph*gR[np][nm]; TGraphErrors*gRE[np];
  for(int p = 0; p<np; p++ ){
    for (auto i=0; i<nm; ++i){
      hR[p][i] = (TH1D*)hPy[p][i]->Clone(Form("%s_%s", sp[np].Data(), sm[i].Data()));
      DeNormBinningHistogram(hR[p][i]);
      hR[p][i] = MakeRebinTH1D(hR[p][i], h[p]);
      hR[p][i]->Divide(h[p]);
      NormBinningHistogram(hR[p][i]);
      //hRm[i] = hR[p][i];
      //gR[p][i] = new TGraph(hR[p][i]); 
    }
    hRm[0] = hR[p][0];
    hRm[1] = hR[p][2];
    hRm[2] = hR[p][3];
    hMax[p] = MaxHistograms(3, hRm);
    hMin[p] = MinHistograms(3, hRm);
    hMid[p] = (TH1D*)hMax[p]->Clone(Form("mid_%s", sp[np].Data()));
    hMid[p]->Add(hMin[p]);
    hMid[p]->Scale(0.5);
    const int nbins = hMid[p]->GetNbinsX();
    double x[nbins];
    double y[nbins];
    double ex[nbins];
    double ey[nbins];
    for(int j = 1; j<= hMid[p]->GetNbinsX(); j++){
      x[j-1] = hMid[p]->GetBinCenter(j); 
      ex[j-1] = 0.; 
      y[j-1] = hMid[p]->GetBinContent(j); 
      ey[j-1] = (hMax[p]->GetBinContent(j) - hMin[p]->GetBinContent(j))/2.;
    
    }
    gRE[p] = new TGraphErrors(nbins, x, y, ex, ey);
  }

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(5e-5), dfuy(8e1);

  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.045), dtsy(0.05);
  auto dtox(1.30), dtoy(1.21);

  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");

  SetStyle(kTRUE);
  gStyle->SetErrorX(0);

//=============================================================================
  
  
  auto can(MakeCanvas("Fig06b", 600, 800));
 
  
  
  auto padT = MakePadT("padT", 0.42); can->cd();
  auto pad1 = MakePad("pad1", 0., 0.33, 1., 0.42); can->cd();
  auto pad2 = MakePad("pad2", 0., 0.24, 1., 0.33); can->cd();
  auto pad3 = MakePad("pad3", 0., 0.15, 1., 0.24); can->cd();
  auto pad4 = MakePadB("pad4", 0.151); pad4->SetBottomMargin(0.43); can->cd();
  auto pad5 = MakePad("pad5", 0., 0.15, 1., 0.42); pad5->SetBottomMargin(0.43); can->cd();
  
  padT->cd();
  padT->SetLogy();
  auto hfmT(padT->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfmT, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfmT->GetXaxis()->SetNdivisions(510);
  hfmT->GetYaxis()->SetNdivisions(510);

  for(int p = 0; p<np; p++ ){
    DrawHisto(h[p], wcl[p], wmk[p], "same"); 
    DrawGraph(gE[p], wcl[p], "E2");
    g[p][0]->SetLineStyle(0);
    g[p][2]->SetLineStyle(2);
    g[p][3]->SetLineStyle(5);
    for (auto i=0; i<nm; ++i) {
      if(i !=1 ) DrawGraph(g[p][i],  wcl[p], "C");
    
    }
  }


  //auto leg(new TLegend(0.7, 0.8, 0.95, 0.87)); SetupLegend(leg);
  auto leg(new TLegend(.36, 0.63, 0.61, 0.87)); SetupLegend(leg);
  //leg->SetNColumns(2);
  leg->AddEntry(h[0], "#color[1]{K^{0}_{S} (#times 16)}", "P")->SetTextSizePixels(20);
  leg->AddEntry(h[1], "#color[633]{#Lambda + #bar{#Lambda} (#times 4)}", "P")->SetTextSizePixels(20);
  leg->AddEntry(h[2], "#color[601]{#Xi^{-} + #bar{#Xi}^{+} (#times 2)}", "P")->SetTextSizePixels(20);
  leg->AddEntry(h[3], "#color[419]{#Omega^{-} + #bar{#Omega}^{+}}", "P")->SetTextSizePixels(20);
  leg->Draw();
  
  auto Leg(new TLegend(0.61, 0.63, 0.92, 0.87)); SetupLegend(Leg);
  Leg->SetHeader("PYTHIA 8");
  Leg->AddEntry(g[0][0], "CR-BLC mode 0", "L")->SetTextSizePixels(20);
  Leg->AddEntry(g[0][2], "CR-BLC mode 2", "L")->SetTextSizePixels(20);
  Leg->AddEntry(g[0][3], "CR-BLC mode 3", "L")->SetTextSizePixels(20);
  Leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(22);
  tex->DrawLatex(0.15, 0.91, "ALICE pp #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.68, 0.91, Form("Particle in jets"));
  
  //tex->DrawLatex(0.85, 0.62, "K^{0}_{S}");
  //tex->DrawLatex(0.75, 0.47, "#color[633]{#Lambda + #bar{#Lambda}}");
  //tex->DrawLatex(0.63, 0.25, "#color[601]{#Xi^{-} + #bar{#Xi}^{+}}");
  //tex->DrawLatex(0.58, 0.1, "#color[419]{#Omega^{-} + #bar{#Omega}^{+}}");
  //tex->DrawLatex(0.16, 0.3, "#it{R}(par, jet) < 0.4, |#eta_{par}| < 0.75");
  //tex->DrawLatex(0.16, 0.2, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");

  can->cd();
  pad1->cd();
  
  dfly = 0.5, dfuy = 2.5;

  dlsx = 0.33; dlsy = 0.33;
  dtsx = 0.29; dtsy = 0.29;
  dtox = 1.10; dtoy = 0.2;
  stny = "";

  auto hfm1(pad1->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm1, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm1->GetXaxis()->SetNdivisions(510);
  hfm1->GetYaxis()->SetNdivisions(503);
  hfm1->GetXaxis()->SetTickLength(0.07);

  DrawGraphError(gRE[0],  wcl[0], wcl[0], "E3");
  
  auto tex1(new TLatex());
  tex1->SetNDC();
  tex1->SetTextSizePixels(22);
  tex1->DrawLatex(0.85, 0.15, "K^{0}_{S}");
  

  can->cd();
  pad2->cd();
  dfly = 0.5, dfuy = 2.9;
  auto hfm2(pad2->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm2, stnx, "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm2->GetXaxis()->SetNdivisions(510);
  hfm2->GetYaxis()->SetNdivisions(503);
  hfm2->GetXaxis()->SetTickLength(0.07);
  
  DrawGraphError(gRE[1],  wcl[1], wcl[1], "E3");
  
  auto tex2(new TLatex());
  tex2->SetNDC();
  tex2->SetTextSizePixels(22);
  tex2->DrawLatex(0.83, 0.15, "#color[633]{#Lambda + #bar{#Lambda}}");
  
  can->cd();
  pad3->cd();
  dfly = 2.01, dfuy = 6.5;
 
  auto hfm3(pad3->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm3, stnx, "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm3->GetXaxis()->SetNdivisions(510);
  hfm3->GetYaxis()->SetNdivisions(503);
  hfm3->GetXaxis()->SetTickLength(0.07);
  DrawGraphError(gRE[2],  wcl[2], wcl[2], "E3");
  
  auto tex3(new TLatex());
  tex3->SetNDC();
  tex3->SetTextSizePixels(22);
  tex3->DrawLatex(0.83, 0.15, "#color[601]{#Xi^{-} + #bar{#Xi}^{+}}");
  
  can->cd();
  pad4->cd();
  
  dfly = 0.2, dfuy = 1.7;
 
  dlsx = 0.19; dlsy = 0.19;
  dtsx = 0.19; dtsy = 0.17;
  dtox = 1.1; dtoy = 0.4;
  auto hfm4(pad4->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm4, stnx, "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm4->GetXaxis()->SetNdivisions(510);
  hfm4->GetYaxis()->SetNdivisions(503);
  hfm4->GetXaxis()->SetTickLength(0.07);
  hfm4->GetYaxis()->SetLabelOffset(0.011);
 
  DrawGraphError(gRE[3],  wcl[3], wcl[3], "E3");
  
  auto tex4(new TLatex());
  tex4->SetNDC();
  tex4->SetTextSizePixels(22);
  tex4->DrawLatex(0.83, 0.5, "#color[419]{#Omega^{-} + #bar{#Omega}^{+}}");

  auto leg4(new TLegend(0.63, 0.6, 0.88, 0.9)); SetupLegend(leg4);
  leg4->AddEntry(gRE[0], "CR-BLC", "F")->SetTextSizePixels(20);
  leg4->Draw();
 
  can->cd();
  pad5->cd();
  pad5->SetFillStyle(4000);
  auto Tex(new TLatex());
  Tex->SetNDC();
  Tex->SetTextSizePixels(13);
  Tex->SetTextAngle(90);
  Tex->DrawLatex(0.032, 0.1, "PYTHIA/Data");
  
  

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);


  return;
}

