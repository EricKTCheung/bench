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

int plot2(string graph1="", string graph2="", string graph_name="2 graphs", int sample_size=0, int bin_number=0)
{
    using namespace std;

    // data for y-axis(walltime)
    vector<double> graph1_y;
    vector<double> graph2_y;
    
    // error bar data for y-axis
    vector<double> graph1_ey;
    vector<double> graph2_ey;
    
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
    populateVector(graph1, &graph1_y, &graph1_ey, sample_size, bin_number);
    populateVector(graph2, &graph2_y, &graph2_ey, sample_size, bin_number);
    
    // ugly work-around for constructing TGraphErrors
    double* y1 = &graph1_y[0];
    double* y2 = &graph2_y[0];
    double* ey1 = &graph1_ey[0];
    double* ey2 = &graph2_ey[0];

    TCanvas *c1 = new TCanvas("c1","Test",200,10,1920,1080);
    c1->SetGrid();


    TGraphErrors *gr1 = new TGraphErrors(bin_number, percentage, y1, NULL, ey1);
    gr1->SetTitle(graph_name.c_str());
    gr1->GetXaxis()->SetTitle("Percentage of total number of events read(%)");
    gr1->GetYaxis()->SetTitle("Wall time(s)");
    gr1->GetXaxis()->CenterTitle();
    gr1->GetYaxis()->CenterTitle();


    gr1->SetMarkerColor(2);
    gr1->SetLineColor(2);
    gr1->SetMarkerStyle(21);
    gr1->SetLineWidth(2);
    gr1->Draw("ALP");

    gr1->GetYaxis()->SetRangeUser(4.0,16.0);
    gr1->Draw("ALP");

    TGraphErrors *gr2 = new TGraphErrors(bin_number, percentage, y2, NULL, ey2);   
    gr2->SetMarkerColor(4);
    gr2->SetLineColor(4);
    gr2->SetMarkerStyle(21);
    gr2->SetLineWidth(2);
    gr2->Draw("LP");


    TLegend *leg = new TLegend(0.1,0.75,0.3,0.9);
    leg->AddEntry(gr1,"AsyncPrefetching Off","lp");
    leg->AddEntry(gr2,"AsyncPrefetching On","lp");
    leg->AddEntry("", "Error bar(SD)", "le");
    leg->Draw();

    

    c1->Update();

    return 0;
}


