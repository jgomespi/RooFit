#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;
 
void exercise1()
{
   // Declaring the variables
   RooRealVar x("x", "x", -10, 10);
   RooRealVar mean("mean", "mean of gaussian", 0, -10, 10);
   RooRealVar sigma("sigma", "width of gaussian", 1, 0.1, 10);
   // Declaring the gaussian distribuition 
   RooGaussian gauss("gauss", "gaussian PDF", x, mean, sigma);

   // Creating 1000 random gauss points
   RooDataSet *data1 = gauss.generate(x, 10000);
 
   // Declaring a frame
   RooPlot *xframe1 = x.frame(Title("Gaussian pdf with data"));
   // Plot the data and the gauss function on the frame
   data1->plotOn(xframe1);
   gauss.plotOn(xframe1);
   // Fit the gauss function to the data
   gauss.fitTo(*data1);
   
   // Declaring lambda varible to the expo dist
   RooRealVar lambda("lambda", "slope", -0.1, -5., 0.);
   // Declaring the exponential distribuition
   RooExponential expo("expo","exponential PDF", x, lambda);

   // Creatring 1000 random exponencial points
   RooDataSet *data2 = expo.generate(x, 10000);

   // Declaring another frame
   RooPlot *xframe2 = x.frame(Title("Exponential pdf with data"));
   // Plot the data and the expo function on the frame
   data2->plotOn(xframe2);
   expo.plotOn(xframe2);
   // Fit the expo dist to the data
   expo.fitTo(*data2);

   // Draw all frames on a canvas
   TCanvas *c = new TCanvas("Exercise_1", "Exercise_1", 800, 400);
   c->Divide(2);
   c->cd(1);
   gPad->SetLeftMargin(0.15);
   xframe1->GetYaxis()->SetTitleOffset(1.6);
   xframe1->Draw();
   c->cd(2);
   gPad->SetLeftMargin(0.15);
   xframe2->GetYaxis()->SetTitleOffset(1.6);
   xframe2->Draw();
}
