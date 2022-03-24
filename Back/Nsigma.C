#include "inc/PyJetUtils.h"


void Nsigma(){
//=============================================================================

  auto f = TFile::Open("./data/pPb.root", "read");
  TList* l[3]; TH1D *h[4]; TH1D *hE[4]; TH1D *hR[3]; TGraph *gE[3];
  //l[0]= (TList*)f->Get(Form("Lambda_sum_toKRatio_010"));
  //l[1]= (TList*)f->Get(Form("Lambda_sum_toKRatio_40100"));
  //l[2]= (TList*)f->Get(Form("Lambda_sum_toKRatio_0100"));
  l[0]= (TList*)f->Get(Form("Xi_toKRatio_010"));
  l[1]= (TList*)f->Get(Form("Xi_toKRatio_40100"));
  l[2]= (TList*)f->Get(Form("Xi_toKRatio_0100"));
  f->Close();
  for(Int_t i = 0; i<3; i++){ h[i] = (TH1D*)l[i]->FindObject(Form("hJER"));   hE[i] = (TH1D*)l[i]->FindObject(Form("heJER")); }
  
  
  auto fF = TFile::Open("./data/pp.root", "read");
  auto lL= (TList*)fF->Get(Form("Xi_toKRatio"));
  fF->Close();
  h[3] = (TH1D*)lL->FindObject(Form("hJER"));   hE[3] = (TH1D*)lL->FindObject(Form("heJER")); 
  auto hNSigma0 = (TH1D*)h[0]->Clone("hNSigma0"); hNSigma0->Reset(); 
  auto hNSigma2 = (TH1D*)h[0]->Clone("hNSigma2"); hNSigma2->Reset();
  Double_t dCent[4]; Double_t dStat[4]; Double_t dSyst[4]; Double_t dErr[4];
  for(Int_t i = 1; i<= h[0]->GetNbinsX(); i++){
    dCent[0] =  h[0]->GetBinContent(i); dCent[1] =  h[1]->GetBinContent(i); dCent[2] =  h[2]->GetBinContent(i); dCent[3] =  h[3]->GetBinContent(i);
    dStat[0] =  h[0]->GetBinError(i);   dStat[1] =  h[1]->GetBinError(i);   dStat[2] =  h[2]->GetBinError(i);   dStat[3] =  h[3]->GetBinError(i);
    dSyst[0] = hE[0]->GetBinContent(i); dSyst[1] = hE[1]->GetBinContent(i); dSyst[2] = hE[2]->GetBinContent(i); dSyst[3] = hE[3]->GetBinContent(i);
    auto dNSigma0 = TMath::Abs(dCent[0] - dCent[1])/TMath::Sqrt(dStat[0]*dStat[0] + dSyst[0]*dSyst[0] + dStat[1]*dStat[1] + dSyst[1]*dSyst[1]);
    auto dNSigma2 = TMath::Abs(dCent[2] - dCent[3])/TMath::Sqrt(dStat[2]*dStat[2] + dSyst[2]*dSyst[2] + dStat[3]*dStat[3] + dSyst[3]*dSyst[3]);
    hNSigma0->SetBinContent(i, dNSigma0); hNSigma0->SetBinError(i, 0);
    hNSigma2->SetBinContent(i, dNSigma2); hNSigma2->SetBinError(i, 0);
  } 
    cout<<"=================================="<<endl;
    cout<<"L/K ratio"<<endl;
    cout<<"Nsigma between MB p-Pb and pp"<<endl;
    Double_t nSig[3];
    nSig[0] = hNSigma2->GetBinContent(2);
    nSig[1] = hNSigma2->GetBinContent(3);
    nSig[2] = hNSigma2->GetBinContent(4);
    cout<<"pT bin("<< hNSigma2->GetXaxis()->GetBinLowEdge(2)<<"-"<<hNSigma2->GetXaxis()->GetBinUpEdge(2)<<") = "<<nSig[0]<<endl;
    cout<<"pT bin("<< hNSigma2->GetXaxis()->GetBinLowEdge(3)<<"-"<<hNSigma2->GetXaxis()->GetBinUpEdge(3)<<") = "<<nSig[1]<<endl;
    cout<<"pT bin("<< hNSigma2->GetXaxis()->GetBinLowEdge(4)<<"-"<<hNSigma2->GetXaxis()->GetBinUpEdge(4)<<") = "<<nSig[2]<<endl;
    cout<<"Average in pT bin"<< hNSigma2->GetXaxis()->GetBinLowEdge(2)<<"-"<<hNSigma2->GetXaxis()->GetBinUpEdge(4)<<") = "<< (nSig[0]+nSig[1]+nSig[2])/3.<<endl;

    cout<<"Nsigma between 0-10\% and 40-100\% for p-Pb collision"<<endl;
    Double_t nsig[3];
    nsig[0] = hNSigma0->GetBinContent(2);
    nsig[1] = hNSigma0->GetBinContent(3);
    nsig[2] = hNSigma0->GetBinContent(4);
    cout<<"pT bin("<< hNSigma0->GetXaxis()->GetBinLowEdge(2)<<"-"<<hNSigma0->GetXaxis()->GetBinUpEdge(2)<<") = "<<nsig[0]<<endl;
    cout<<"pT bin("<< hNSigma0->GetXaxis()->GetBinLowEdge(3)<<"-"<<hNSigma0->GetXaxis()->GetBinUpEdge(3)<<") = "<<nsig[1]<<endl;
    cout<<"pT bin("<< hNSigma0->GetXaxis()->GetBinLowEdge(4)<<"-"<<hNSigma0->GetXaxis()->GetBinUpEdge(4)<<") = "<<nsig[2]<<endl;
    cout<<"Average in pT bin"<< hNSigma0->GetXaxis()->GetBinLowEdge(2)<<"-"<<hNSigma0->GetXaxis()->GetBinUpEdge(4)<<") = "<< (nsig[0]+nsig[1]+nsig[2])/3.<<endl;

//=============================================================================



  return;
}

