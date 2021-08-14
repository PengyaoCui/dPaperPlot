#include "inc/PyJetUtils.h"

void fpPb_JE_OLRatio(){
//=============================================================================

  TList* l; TFile *f;
  f = TFile::Open("./data/pPb.root", "read");
  l = (TList*)f->Get(Form("Omega_toLRatio_0100"));
  f->Close();

  auto h = (TH1D*)l->FindObject(Form("hJER")); 
  auto gE = (TGraphErrors*)l->FindObject(Form("JERerr"));
  auto hE = (TH1D*)l->FindObject(Form("heJER"));

  const TString sj("Jet10");
  const TString sd("pp05d02TeVrs");  // pp13d00TeV:   pp at 13   TeV
                                    // pp05d02TeVrs: pp at 5.02 TeV
                                    //               with rapidity shift
                                    //               used to fit p-Pb acceptance

  TGraph *g[nm]; TH1D *hm[nm];
  TGraph *gR[nm]; TH1D *hmR[nm];  
  for (auto i=0; i<nm; ++i){ 
    hm[i] = (TH1D*)(RatioOL(i, sd, sj, "JC04", "PC04"));
    g[i] = new TGraph(hm[i]);
    hmR[i] = (TH1D*)hm[i]->Clone(Form("hR_%d", i));
    DeNormBinningHistogram(hmR[i]);
    hmR[i] = MakeRebinTH1D(hmR[i], h);
    NormBinningHistogram(hmR[i]);
    hmR[i]->Divide(h);
    gR[i] = new TGraph(hmR[i]);
  }
//Data double ratio
//=============================================================================

  auto hR = (TH1D*) h->Clone(); hR->Reset();
  auto hRE = (TH1D*) h->Clone(); hRE->Reset();
  TGraph* gRE;
  for(auto i = 1; i<= h->GetNbinsX(); i++){
    hR->SetBinContent(i, 1.); 
    hR->SetBinError(i, h->GetBinError(i)/h->GetBinContent(i)); 
    hRE->SetBinContent(i, hE->GetBinContent(i)); 
  }
  gRE = ConvHistogramToGraphErrors(hR, hRE, h->GetNbinsX());


//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.0), dfuy(0.16);

  auto dlsx(0.05), dlsy(0.06);
  auto dtsx(0.05), dtsy(0.06);
  auto dtox(1.30), dtoy(0.9);

  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("(#Omega^{-} + #bar{#Omega}^{+}) / (#Lambda + #bar{#Lambda})");

  SetStyle(kTRUE);
  gStyle->SetErrorX(0);

//=============================================================================
  
  
  auto can(MakeCanvas("pPb_JE_OLRatio", 700, 600));
  auto padT = MakePadT("padT"); can->cd();
  auto padB = MakePadB("padB"); can->cd();
  padT->cd();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(505);

  DrawHisto(h, wcl[0], wmk[0], "same"); DrawGraph(gE, wcl[0], "E2");
  //g[1]->SetLineStyle(9);

  //DrawGraph(g[1],  wcl[0], "C");
  DrawGraph(g[0],  wcl[1], "C");
  DrawGraph(g[2],  wcl[2], "C");
  DrawGraph(g[3],  wcl[3], "C");

  auto leg(new TLegend(0.68, 0.46, 1., 0.71)); SetupLegend(leg);
  //leg->AddEntry(g[1], "Monash", "L")->SetTextSizePixels(24);
  leg->AddEntry(h, "Data", "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "BLC mode 0", "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "BLC mode 2", "L")->SetTextSizePixels(24);
  leg->AddEntry(g[3], "BLC mode 3", "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "ALICE p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex->DrawLatex(0.16, 0.8, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");
  tex->DrawLatex(0.16, 0.7, "#it{R}(particle, jet) < 0.4, |#eta_{particle}| < 0.75");
  tex->DrawLatex(0.16, 0.6, "Particles in jets, UE subtracted");

  can->cd();
  padB->cd();
  dfly = 0., dfuy = 1.9;

  dlsx = 0.11; dlsy = 0.11;
  dtsx = 0.11; dtsy = 0.11;
  dtox = 1.10; dtoy = 0.40;
  stny = "Ratio to data";

  auto hfmb(padB->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfmb, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfmb->GetXaxis()->SetNdivisions(510);
  hfmb->GetYaxis()->SetNdivisions(505);
  hfmb->GetXaxis()->SetTickLength(0.07);

  DrawHisto(hR, wcl[0], wmk[0], "same"); DrawGraph(gRE, wcl[0], "E2");
  DrawGraph(gR[0],  wcl[1], "C");
  DrawGraph(gR[2],  wcl[2], "C");
  DrawGraph(gR[3],  wcl[3], "C");

  TLine* line = new TLine(dflx, 1., dfux, 1.);
  //line->SetLineColor(kRed);
  line->SetLineWidth(2);
  line->SetLineStyle(2);
  line->Draw("same");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);


  return;
}

