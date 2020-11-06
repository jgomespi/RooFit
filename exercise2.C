#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;
 
void exercise2()
{
 
   // In order to run this program, open the root file in a root session:
   // TFile *f = new TFile("DataSet_lowstat.root");
   // And then run:
   // .x exercise2.C

   // Declaring the mass variable
   RooRealVar mass("mass", "mass", 2., 6.);

   // Parameters of Crystall-Ball of J/Psi
   RooRealVar meanJpsi("meanJpsi", "Mean of J/#psi", 3.1, 2.8, 3.2);
   RooRealVar sigmaJpsi("sigmaJpsi", "Sigma of J/#psi", 0.3, 0.0001, 1.);
   RooRealVar alphaJpsi("alphaJpsi", "Alpha of J/#psi", 1.5,-5.,5.);
   RooRealVar nJpsi("nJpsi","n of J/#psi", 1.5,0.5,5.);

   // Declaring the Crystal Ball PDF for JPsi
   RooCBShape CB_Jpsi( "CB_Jpsi","The J/#psi Crystall Ball", mass , meanJpsi , sigmaJpsi , alphaJpsi , nJpsi );

   // For Upsilon(2S), we will user the same sigma value of JPsi
   RooRealVar meanPsi("meanPsi", "Mean of #psi(2S)", 3.7, 3.6, 3.8);
   RooRealVar sigmaPsi("sigmaPsi", "Sigma of #psi(2S)", 0.3,0.0001, 1.); 

   // Declaring the Gauss PDF for Psi
   RooGaussian gaussPsi("gaussPsi", "The #psi(2S) gaussian PDF", mass, meanPsi, sigmaPsi);

   // Declaring the polinomial parameters and PDF for background
   RooRealVar a1("a1", "a1", -0.7, -2.,2.);
   RooRealVar a2("a2", "a2", 0.3, -2.,2.);
   RooRealVar a3("a3", "a3", -0.03, -2.,2.);

   // Declaring the polinomial PDF for background
   RooPolynomial PolBG("PolBG", "Polinomial PDF for BG", mass, RooArgList(a1,a2,a3));

   // Declaring the widths, which is the number of each event (JPsi, Psi2S and BG):
   RooRealVar NJpsi("NJpsi", "Number of J/#psi events", 1500.,  0.1, 10000.);
   RooRealVar NPsi("NPsi", "Number of #psi (2S) events", 100.,  0.1, 5000.);
   RooRealVar NBG("NBG", "Number of background events",  5000., 0.1, 50000.);
   
   // Here we will create a PDF which is the sum of CB+Gauss+Pol PDFs
   // The weights are the number of each event
   RooAddPdf sumPDF("sumPDF", "Sum of PDFs", RooArgList(CB_Jpsi,gaussPsi,PolBG),RooArgList(NJpsi,NPsi,NBG));
   sumPDF.fitTo(*data);

   // Draw a frame with the data and the sum of PDF normalized 
   RooPlot *xframe = mass.frame();
   data->plotOn(xframe);
   sumPDF.plotOn(xframe,Normalization(1.0,RooAbsReal::RelativeExpected));
   xframe->Draw();
   xframe->SaveAs("results.pdf","pdf");

   RooWorkspace w("w");
   w.import(*data);
   w.import(sumPDF);
   w.writeToFile("Results.root");
}
