#include "inc/PyJetUtils.h"

void fpPb_JE_Lambda_Cent(){
//=============================================================================

  auto f = TFile::Open("./data/pPb.root", "read");
  TList* l[4];
  l[0]= (TList*)f->Get("Lambda_sum_0100");
  l[1]= (TList*)f->Get("Lambda_sum_010");
  l[2]= (TList*)f->Get("Lambda_sum_1040");
  l[3]= (TList*)f->Get("Lambda_sum_40100");
  f->Close();
  TH1D *h[4]; TH1D *hE[4]; TGraph *gE[4]; TH1D* hR[3]; TH1D* heR[3]; TGraph* geR[3];
  for(Int_t i = 0; i<4; i++){
    h[i]  = (TH1D*)l[i]->FindObject(Form("JECen"));
    hE[i] = (TH1D*)l[i]->FindObject(Form("JEErr"));
    gE[i] = (TGraphErrors*)l[i]->FindObject(Form("JEerr"));
  }

  for(Int_t i = 1; i<4; i++){
    hR[i-1] = (TH1D*)h[i]->Clone(Form("hR_%d", i));// hR[i-1]->Reset();
    hR[i-1]->Divide(h[0]);
    heR[i-1]=(TH1D*)h[0]->Clone(Form("heR_%d", i)); heR[i-1]->Reset();
    for(Int_t j = 1; j<=h[0]->GetNbinsX(); j++){
      auto dErr0 = hE[0]->GetBinContent(j);
      auto dErr1 = hE[i]->GetBinContent(j);
      heR[i-1]->SetBinContent(j, TMath::Sqrt(dErr0*dErr0 + dErr1*dErr1)); 
      //heR[i-1]->SetBinContent(j, TMath::Sqrt((dErr0-dErr1)*(dErr0-dErr1))); 
    }
    geR[i-1] = ConvHistogramToGraphErrors(hR[i-1], heR[i-1], h[0]->GetNbinsX());
  }

  TGraph *g[nm];
  const TString sj("Jet10");
  const TString sd("pp05d02TeVrs");  // pp13d00TeV:   pp at 13   TeV
                                    // pp05d02TeVrs: pp at 5.02 TeV
                                    //               with rapidity shift
                                    //               used to fit p-Pb acceptance

  for (auto i=0; i<nm; ++i){
    g[i] = new TGraph(Spectrum(i, sd, "Lambda", sj, "JC04", "PC04"));
  }

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(4e-4), dfuy(8e-2);
  
  auto dlsx(0.05), dlsy(0.06);
  auto dtsx(0.05), dtsy(0.06);
  auto dtox(1.30), dtoy(0.9);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("fpPb_JE_Lambda_Cent", 700, 600));
  auto padT = MakePadT("padT"); can->cd();
  auto padB = MakePadB("padB"); can->cd();
  padT->cd();
  padT->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h[1], wcl[1], wmk[1], "same"); DrawGraph(gE[1], wcl[1], "E2");
  DrawHisto(h[2], wcl[2], wmk[2], "same"); DrawGraph(gE[2], wcl[2], "E2");
  DrawHisto(h[3], wcl[3], wmk[3], "same"); DrawGraph(gE[3], wcl[3], "E2");
  DrawHisto(h[0], wcl[0], wmk[0], "same"); DrawGraph(gE[0], wcl[0], "E2");

  //g[1]->SetLineStyle(9);

  //DrawGraph(g[1],  wcl[8], "C");
  //DrawGraph(g[0],  wcl[1], "C");
  //DrawGraph(g[2],  wcl[2], "C");
  //DrawGraph(g[3],  wcl[3], "C");

  auto leg(new TLegend(0.65, 0.55, 1., 0.94)); SetupLegend(leg);
  leg->AddEntry(h[1], "0-10%",   "P")->SetTextSizePixels(24);
  leg->AddEntry(h[2], "10-40%",  "P")->SetTextSizePixels(24);
  leg->AddEntry(h[3], "40-100%", "P")->SetTextSizePixels(24);
  leg->AddEntry(h[0], "MB",  "P")->SetTextSizePixels(24);
  //leg->AddEntry(g[1], "PYTHIA 8", "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "ALICE p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex->DrawLatex(0.16, 0.27, "#Lambda + #bar{#Lambda} in jets, UE subtracted");
  tex->DrawLatex(0.16, 0.17, "#it{R}(#Lambda, jet) < 0.4, |#eta_{#Lambda}| < 0.75");
  tex->DrawLatex(0.16, 0.07, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");
  can->cd();
  padB->cd();
  dfly = 0.3, dfuy = 1.7;

  dlsx = 0.11; dlsy = 0.11;
  dtsx = 0.11; dtsy = 0.11;
  dtox = 1.10; dtoy = 0.40;
  stny = "Ratio to MB";

  auto hfmb(padB->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfmb, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfmb->GetXaxis()->SetNdivisions(510);
  hfmb->GetYaxis()->SetNdivisions(505);
  hfmb->GetXaxis()->SetTickLength(0.07);

  DrawHisto(hR[0], wcl[1], wmk[1], "same"); DrawGraph(geR[0], wcl[1], "E2");
  DrawHisto(hR[1], wcl[2], wmk[2], "same"); DrawGraph(geR[1], wcl[2], "E2");
  DrawHisto(hR[2], wcl[3], wmk[3], "same"); DrawGraph(geR[2], wcl[3], "E2");

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

