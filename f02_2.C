#include "inc/PyJetUtils.h"

void f02_2(){
  TString sType[] = {"Kshort", "Lambda", "Xi", "Omega"};
  TString sLeg[] = {"K^{0}_{S}", "#Lambda", "#Xi", "#Omega"};
  
  Int_t n = sizeof(sType)/sizeof(TString); 
 
  TH1D* hJE[5]; TH1D* hIn[5]; TH1D* hR[5];
  for(Int_t i = 0; i<n; i++){
    auto f = TFile::Open(Form("./data/pPb/JE/%s/AnalysisOutputs_EffCorrJE.root", sType[i].Data()), "read");
    auto l = (TList*)f->Get(Form("listEffCorrJE_%s_Default_JC_0100", sType[i].Data())); f->Close();    
    hJE[i] = (TH1D*)l->FindObject("hPtEffi");hJE[i]->SetName(Form("hJE_%d", i)); 
    f = TFile::Open(Form("./data/pPb/JE/%s/AnalysisOutputs_EffInclMC.root", sType[i].Data()), "read");
    l = (TList*)f->Get(Form("listEffInclMC_%s_Default_0100", sType[i].Data())); f->Close();    
    hIn[i] = (TH1D*)l->FindObject("hPtEffi"); hIn[i]->SetName(Form("hIn_%d", i));
    hR[i] = (TH1D*)hJE[i]->Clone(Form("hR_%d", i));hR[i]->SetName(Form("hR_%d", i));   
    hR[i]->Divide(hIn[i]);
  } 
//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.0001), dfuy(0.75);
  
  auto dlsx(0.05), dlsy(0.06);
  auto dtsx(0.05), dtsy(0.06);
  auto dtox(1.30), dtoy(0.80);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("Efficiency");
  
  SetStyle(kTRUE);
  
  auto can(MakeCanvas("f02_2"));
  auto padT = MakePadT("padT"); can->cd();
  auto padB = MakePadB("padB"); can->cd();
  padT->cd(); 
  auto hfm(padT->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);
  
  for(Int_t i =0; i<n; i++){
    DrawHisto(hIn[i], wcl[i], wmk[0], "same");
    DrawHisto(hJE[i], wcl[i], wmk[2], "same");
  }

  auto leg(new TLegend(0.83, 0.40, 1.1, 0.76)); SetupLegend(leg);
  auto Leg(new TLegend(0.55, 0.50, 0.8, 0.75)); SetupLegend(leg);
  //leg -> SetNColumns(3);
  for(Int_t i =0; i<n; i++){
    leg->AddEntry(hIn[i], sLeg[i], "L")->SetTextSizePixels(20);
  
  }
  Leg->AddEntry(hIn[0], "Inclusive", "LP")->SetTextSizePixels(20);
  Leg->AddEntry(hJE[0], "#it{R}(Par, jet) < 0.4", "LP")->SetTextSizePixels(20);
  Leg->Draw();
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(20);
  tex->DrawLatex(0.16, 0.91, "ALICE p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV, |#eta| < 0.75");
  tex->DrawLatex(0.16, 0.81, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");

  can->cd();
  padB->cd(); 
  dfly = 0.8, dfuy = 1.5999;
  
  dlsx = 0.11; dlsy = 0.11;
  dtsx = 0.11; dtsy = 0.11;
  dtox = 1.10; dtoy = 0.40;
  stny = "Ratio to inclusive";
  
  auto hfmb(padB->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfmb, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfmb->GetXaxis()->SetNdivisions(510);
  hfmb->GetYaxis()->SetNdivisions(505);
  hfmb->GetXaxis()->SetTickLength(0.07);
  
  for(Int_t i =0; i<n; i++){
    DrawHisto(hR[i], wcl[i], wmk[3], "same");
  }

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));  
  CanvasEnd(can);

  return;
}

