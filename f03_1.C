#include "inc/PyJetUtils.h"

void f03_1(){

  TString sType[] = {"Lambda", "AntiLa"};
  TString sLeg[] = {"#Lambda", "#bar{#Lambda}"};

  Int_t n = sizeof(sType)/sizeof(TString);

  TH1D* hJE[2]; TH1D* hIn[2];
  for(Int_t i = 0; i<n; i++){
    auto f = TFile::Open(Form("./data/pp/JE/%s/AnalysisOutputs_MakeLaFdR.root", sType[i].Data()), "read");
    auto l = (TList*)f->Get(Form("listMakeLaFdR_%s_Default_JC", sType[i].Data())); f->Close();
    hJE[i] = (TH1D*)l->FindObject("hPtFdFrac");hJE[i]->SetName(Form("hJE_%d", i));
    f = TFile::Open(Form("./data/pp/JE/%s/AnalysisOutputs_MakeLaFdR.root", sType[i].Data()), "read");
    l = (TList*)f->Get(Form("listMakeLaFdR_%s_Default", sType[i].Data())); f->Close();
    hIn[i] = (TH1D*)l->FindObject("hPtFdFrac"); hIn[i]->SetName(Form("hIn_%d", i));
  }

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.), dfuy(0.32);
 
  auto dlsx(0.06), dlsy(0.06);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.20), dtoy(1.05);

  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("Feed-dow fraction");
  
  SetStyle(kTRUE);
  
  auto can(MakeCanvas("f03_1"));
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(505);

  DrawHisto(hIn[0], wcl[0], wmk[0], "same");
  DrawHisto(hJE[0], wcl[0], wmk[1], "same");
  
  DrawHisto(hIn[1], wcl[1], wmk[0], "same");
  DrawHisto(hJE[1], wcl[1], wmk[1], "same");

  auto leg(new TLegend(0.5, 0.65, 1.1, 0.82)); SetupLegend(leg);
  leg -> SetNColumns(2);
  leg->AddEntry(hIn[0], "#Lambda", "L")->SetTextSizePixels(24);
  leg->AddEntry(hIn[0], "Inclusive", "P")->SetTextSizePixels(24);

  leg->AddEntry(hIn[1], "#bar{#Lambda}", "L")->SetTextSizePixels(24);
  leg->AddEntry(hJE[0], "#it{R}(par, jet) < 0.4", "P")->SetTextSizePixels(24);

  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "ALICE pp #sqrt{#it{s}} = 13 TeV, |#eta| < 0.75");
  
  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

