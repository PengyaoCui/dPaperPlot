#include "inc/PyJetUtils.h"

void pPb_InclSpect(){
//=============================================================================

  TString sp[] = {"Kshort", "Lambda_sum", "Xi", "Omega"};
  const auto np = 4; 


  const TString sd("pp05d02TeVrs");  // pp13d00TeV:   pp at 13   TeV


  TList* l[np]; TH1D* h[np]; TGraphErrors*gE[np]; TH1D*hE[np]; TGraph* g[np][nm]; TH1D* hPy[np][nm];
  TFile *f;
  f = TFile::Open("./data/pPb.root", "read");
  for(int p = 0; p<np; p++ ){
    l[p] = (TList*)f->Get(Form("%s_0100", sp[p].Data()));
    h[p]  = (TH1D*)l[p]->FindObject(Form("InclCen")); 
    gE[p] = (TGraphErrors*)l[p]->FindObject(Form("Inclerr"));
    hE[p] = (TH1D*)l[p]->FindObject(Form("InclErr"));
    int n = h[p]->GetNbinsX();
    if(p==0) {h[p]->Scale(16.); gE[p] = ScaleGraphErrors(gE[p], 16., n);}
    if(p==1) {h[p]->Scale(4.); gE[p] = ScaleGraphErrors(gE[p], 4., n);}
    if(p==2) {h[p]->Scale(2.); gE[p] = ScaleGraphErrors(gE[p], 2., n);}
    for (auto i=0; i<nm; ++i){
      if(p==1){
        hPy[p][i] = (TH1D*)Spectrum(i, sd, "Lambda");
      }else{
        hPy[p][i] = (TH1D*)Spectrum(i, sd, sp[p]);
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
  TH1D* hR[np][nm]; TH1D* hMax[np]; TH1D* hMin[np]; TH1D* hMid[np]; TH1D* hRm[nm-1];
  TH1D* hRE[np]; TGraph*gR[np][nm]; TGraphErrors*gRE[np];
  TH1D* hPym[nm-1];TH1D* hPyMid[np]; TH1D* hPyMin[np]; TH1D* hPyMax[np]; TGraphErrors*gPyE[np];
  for(int p = 0; p<np; p++ ){
    for (auto i=0; i<nm; ++i){
      hR[p][i] = (TH1D*)hPy[p][i]->Clone(Form("%s_%s", sp[np].Data(), sm[i].Data()));
      DeNormBinningHistogram(hR[p][i]);
      hR[p][i] = MakeRebinTH1D(hR[p][i], h[p]);
      hR[p][i]->Divide(h[p]);
      NormBinningHistogram(hR[p][i]);
      //hRm[i] = hR[p][i];
      //hPym[i] = hPy[p][i];
      //gR[p][i] = new TGraph(hR[p][i]); 
    }
    hRm[0] = hR[p][0];
    hRm[1] = hR[p][2];
    hRm[2] = hR[p][3];
    hPym[0] = hPy[p][0];
    hPym[1] = hPy[p][2];
    hPym[2] = hPy[p][3];
    hPyMax[p] = MaxHistograms(3, hPym);
    hPyMin[p] = MinHistograms(3, hPym);
    hPyMid[p] = (TH1D*)hPyMax[p]->Clone(Form("Pymid_%s", sp[np].Data()));
    hPyMid[p]->Add(hPyMin[p]);
    hPyMid[p]->Scale(0.5);
    const int nBins = hPyMid[p]->GetNbinsX();
    double X[nBins];
    double Y[nBins];
    double eX[nBins];
    double eY[nBins];
    for(int j = 1; j<= hPyMid[p]->GetNbinsX(); j++){
      X[j-1] = hPyMid[p]->GetBinCenter(j); 
      eX[j-1] = 0.; 
      Y[j-1] = hPyMid[p]->GetBinContent(j); 
      eY[j-1] = (hPyMax[p]->GetBinContent(j) - hPyMin[p]->GetBinContent(j))/2.;
    }
    gPyE[p] = new TGraphErrors(nBins, X, Y, eX, eY);

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
  auto dfly(2e-6), dfuy(4e0);

  auto dlsx(0.045), dlsy(0.045);
  auto dtsx(0.045), dtsy(0.045);
  auto dtox(1.30), dtoy(1.3);

  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");

  SetStyle(kTRUE);
  gStyle->SetErrorX(0);

//=============================================================================
  
  
  auto can(MakeCanvas("pPb_Incl_Spect", 600, 900));
 
  
  
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
    //DrawGraph(gE[p], wcl[p], "E2");
    //g[p][0]->SetLineStyle(0);
    //g[p][2]->SetLineStyle(2);
    //g[p][3]->SetLineStyle(5);
    //for (auto i=0; i<nm; ++i) {
    //  if(i !=1 ) DrawGraph(g[p][i],  wcl[p], "C");
    //
    //}
    //DrawGraphError(gPyE[p],  wcl[p], wcl[p], "E3 C");
    DrawGraphError(gPyE[p],  wcl[p], wcl[p], "E3 C");
  }


  auto leg(new TLegend(0.7, 0.53, 0.95, 0.87)); SetupLegend(leg);
  //leg->SetNColumns(2);
  leg->AddEntry(h[0], "#color[1]{K^{0}_{S} (#times 16)}", "P")->SetTextSizePixels(20);
  leg->AddEntry(h[1], "#color[633]{#Lambda + #bar{#Lambda} (#times 4)}", "P")->SetTextSizePixels(20);
  leg->AddEntry(h[2], "#color[601]{#Xi^{-} + #bar{#Xi}^{+} (#times 2)}", "P")->SetTextSizePixels(20);
  leg->AddEntry(h[3], "#color[419]{#Omega^{-} + #bar{#Omega}^{+}}", "P")->SetTextSizePixels(20);
  leg->AddEntry(gPyE[0], "BLC", "LF")->SetTextSizePixels(20);
  //leg->AddEntry(h[0], "PYTHIA 8", "")->SetTextSizePixels(20);
  //leg->AddEntry(g[0][0], "BLC mode 0", "L")->SetTextSizePixels(20);
  //leg->AddEntry(g[0][2], "BLC mode 2", "L")->SetTextSizePixels(20);
  //leg->AddEntry(g[0][3], "BLC mode 3", "L")->SetTextSizePixels(20);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(22);
  tex->DrawLatex(0.32, 0.9, "ALICE p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV, |#eta| < 0.75");

  can->cd();
  pad1->cd();
  
  dfly = 0.05, dfuy = 0.29;

  dlsx = 0.29; dlsy = 0.29;
  dtsx = 0.29; dtsy = 0.29;
  dtox = 1.10; dtoy = 0.2;
  stny = "";

  auto hfm1(pad1->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm1, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm1->GetXaxis()->SetNdivisions(510);
  hfm1->GetYaxis()->SetNdivisions(503);
  hfm1->GetXaxis()->SetTickLength(0.07);

  DrawGraphError(gRE[0],  wcl[0], wcl[0], "E3 C");
  
  auto tex1(new TLatex());
  tex1->SetNDC();
  tex1->SetTextSizePixels(22);
  tex1->DrawLatex(0.85, 0.15, "K^{0}_{S}");
  

  can->cd();
  pad2->cd();
  dfly = 0.02, dfuy = 0.29;
  auto hfm2(pad2->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm2, stnx, "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm2->GetXaxis()->SetNdivisions(510);
  hfm2->GetYaxis()->SetNdivisions(503);
  hfm2->GetXaxis()->SetTickLength(0.07);
  
  DrawGraphError(gRE[1],  wcl[1], wcl[1], "E3 C");
  
  auto tex2(new TLatex());
  tex2->SetNDC();
  tex2->SetTextSizePixels(22);
  tex2->DrawLatex(0.83, 0.15, "#color[633]{#Lambda + #bar{#Lambda}}");
  
  can->cd();
  pad3->cd();
  dfly = 0.01, dfuy = .22;
 
  auto hfm3(pad3->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm3, stnx, "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm3->GetXaxis()->SetNdivisions(510);
  hfm3->GetYaxis()->SetNdivisions(503);
  hfm3->GetXaxis()->SetTickLength(0.07);
  DrawGraphError(gRE[2],  wcl[2], wcl[2], "E3 C");
  
  auto tex3(new TLatex());
  tex3->SetNDC();
  tex3->SetTextSizePixels(22);
  tex3->DrawLatex(0.83, 0.15, "#color[601]{#Xi^{-} + #bar{#Xi}^{+}}");
  
  can->cd();
  pad4->cd();
  
  dfly = 0.0, dfuy = .07;
 
  dlsx = 0.17; dlsy = 0.17;
  dtsx = 0.17; dtsy = 0.17;
  dtox = 1.10; dtoy = 0.4;
  auto hfm4(pad4->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm4, stnx, "", dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm4->GetXaxis()->SetNdivisions(510);
  hfm4->GetYaxis()->SetNdivisions(503);
  hfm4->GetXaxis()->SetTickLength(0.07);
  
  //DrawGraphError(gRE[3],  wcl[3], wcl[3], "E3 C");
  DrawGraphError(gRE[3],  wcl[3], wcl[3], "E3");
  
  auto tex4(new TLatex());
  tex4->SetNDC();
  tex4->SetTextSizePixels(22);
  tex4->DrawLatex(0.83, 0.5, "#color[419]{#Omega^{-} + #bar{#Omega}^{+}}");

  //auto leg4(new TLegend(0.53, 0.6, 0.85, 0.9)); SetupLegend(leg4);
  //leg4->AddEntry(gRE[0], "BLC", "LF")->SetTextSizePixels(20);
  //leg4->Draw();
 
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

