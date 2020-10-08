#!/bin/bash

cp ./Kshort/AnalysisOutputs_LoopJetRD.root ./merged/AnalysisOutputs_LoopJetRD_K.root

cp ./Lambda/AnalysisOutputs_LoopJetRD.root ./merged/AnalysisOutputs_LoopJetRD_L.root

cp ./AntiLa/AnalysisOutputs_LoopJetRD.root ./merged/AnalysisOutputs_LoopJetRD_A.root

cp ./Xi/AnalysisOutputs_LoopJetRD.root ./merged/AnalysisOutputs_LoopJetRD_X.root

cp ./Omega/AnalysisOutputs_LoopJetRD.root ./merged/AnalysisOutputs_LoopJetRD_O.root

hadd ./AnalysisOutputs_LoopJetRD.root ./merged/AnalysisOutputs_LoopJetRD_*.root
