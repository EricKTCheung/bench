#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TVectorT.h"
#include "TH1F.h"
#include "TFrame.h"
#include "TLegend.h"
#include "TMath.h"

int populateVector(string filename, vector<double>* y, vector<double>* ey, int sam_size, int bin_num)
{
    ifstream datafile(filename.c_str());
    if(!datafile.is_open())
    {
        cout << "Failed to open file -> " << filename << endl;
        return 1;
    }
    
    string temp;
    double data[100];
    double mean = 0;
    vector<double> sample_vec;

    int counter = 0;
    while(datafile.good())
    {
        for(int i=0; i<sam_size; ++i)
        {   
            getline(datafile, temp);
            data[i] = strtod(temp.c_str(), NULL);
            mean += data[i];
            sample_vec.push_back(data[i]);
        }
        mean /= sam_size;
        y->push_back(mean);

        // calculate SD here
        ey->push_back(TMath::RMS(sample_vec.begin(), sample_vec.end()));
        sample_vec.clear();

        if(counter>= bin_num) 
            break;
        mean = 0;
        counter++;
    }
    datafile.close();

    if(y->size() < bin_num)
    {
        cout << "Problem constructing data vector, file = " << filename << " size = " << y->size() << endl;
        return 1;
    }
    
    return 0;
}

int plotxrdbench(string xrdClient="", string xrdCL="", string davix="", string graph_name="Xrd Benchmark Results", int sample_size=0, int bin_number=0)
{
    using namespace std;

    // data for y-axis(walltime)
    vector<double> davix_y;
    vector<double> xrdClient_y;
    vector<double> xrdCL_y;
    
    // error bar data for y-axis
    vector<double> davix_ey;
    vector<double> xrdClient_ey;
    vector<double> xrdCL_ey;
    
    // data for x-axis(percentage of file read)
    
    double percentage[20];

    int percent = 5;
    for(int i=0; i<=20; ++i)
    {
        percentage[i] = percent;
        percent += 5;
    }

    // error bar for x-axis
    vector<double> x_error;   

    // populate the data vectors
    populateVector(xrdClient, &xrdClient_y, &xrdClient_ey, sample_size, bin_number);
    populateVector(xrdCL, &xrdCL_y, &xrdCL_ey, sample_size, bin_number);
    populateVector(davix, &davix_y, &davix_ey, sample_size, bin_number);
    
    // ugly work-around for constructing TGraphErrors
    //int size = 20;
    double* y1 = &xrdClient_y[0];
    double* y2 = &xrdCL_y[0];
    double* y3 = &davix_y[0];
    double* ey1 = &xrdClient_ey[0];
    double* ey2 = &xrdCL_ey[0];
    double* ey3 = &davix_ey[0];

    TCanvas *c1 = new TCanvas("c1","Test",200,10,1920,1080);
    c1->SetGrid();

/*
    TGraphErrors *gr1 = new TGraphErrors(bin_number, percentage, y1, NULL, ey1);
    gr1->SetTitle(graph_name.c_str());
    gr1->GetXaxis()->SetTitle("Percentage of total number of events read(%)");
    gr1->GetYaxis()->SetTitle("Wall time(s)");
    gr1->GetXaxis()->CenterTitle();
    gr1->GetYaxis()->CenterTitle();

    gr1->SetMarkerColor(4);
    gr1->SetLineColor(4);
    gr1->SetMarkerStyle(21);
    gr1->SetLineWidth(2);
    gr1->Draw("ALP");

    TGraphErrors *gr2 = new TGraphErrors(bin_number, percentage, y2, NULL, ey2);   
    gr2->SetMarkerColor(8);
    gr2->SetLineColor(8);
    gr2->SetMarkerStyle(21);
    gr2->SetLineWidth(2);
    gr2->Draw("LP");

    TGraphErrors *gr3 = new TGraphErrors(bin_number, percentage, y3, NULL, ey3);
    gr3->SetMarkerColor(2);
    gr3->SetLineColor(2);
    gr3->SetMarkerStyle(21);
    gr3->SetLineWidth(2);
    gr3->Draw("LP");
*/

    TGraphErrors *gr3 = new TGraphErrors(bin_number, percentage, y3, NULL, ey3);
    
    gr3->SetTitle(graph_name.c_str());
    gr3->GetXaxis()->SetTitle("% of total number of events read");
    gr3->GetYaxis()->SetTitle("Wall time(s)");
    gr3->GetXaxis()->CenterTitle();
    gr3->GetYaxis()->CenterTitle();

    gr3->SetMarkerColor(2);
    gr3->SetLineColor(2);
    gr3->SetMarkerStyle(21);
    gr3->SetLineWidth(2);
    gr3->Draw("ALP");

    TGraphErrors *gr1 = new TGraphErrors(bin_number, percentage, y1, NULL, ey1);
    gr1->SetMarkerColor(4);
    gr1->SetLineColor(4);
    gr1->SetMarkerStyle(21);
    gr1->SetLineWidth(2);
    gr1->Draw("LP");

    TGraphErrors *gr2 = new TGraphErrors(bin_number, percentage, y2, NULL, ey2);   
    gr2->SetMarkerColor(8);
    gr2->SetLineColor(8);
    gr2->SetMarkerStyle(21);
    gr2->SetLineWidth(2);
    gr2->Draw("LP");



    TLegend *leg = new TLegend(0.1,0.75,0.3,0.9);
    leg->AddEntry(gr1,"XrdClient","lp");
    leg->AddEntry(gr2,"XrdCL","lp");
    leg->AddEntry(gr3,"Davix","lp");
    leg->AddEntry("", "Error bar(SD)", "le");
    leg->Draw();

    c1->Update();

    return 0;
}


