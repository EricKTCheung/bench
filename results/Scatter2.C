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

int populateVector(string filename, vector<double>* y)
{
    ifstream datafile(filename.c_str());
    if(!datafile.is_open())
    {
        cout << "Failed to open file -> " << filename << endl;
        return 1;
    }
    
    string temp;
    double data;

    int counter = 0;
    while(datafile.good())
    {
        //if(counter>200) 
        //    break;
        getline(datafile, temp);
        data = strtod(temp.c_str(), NULL);
        y->push_back(data);

        //counter++;
    }
    datafile.close();

    if(y->size() != 200)
    {
        cout << "Problem constructing data vector, file = " << filename << " size = " << y->size() << endl;
        return 1;
    }
   
    cout <<  "vector size = " << y->size() << endl;
    return 0;
}

int Scatter2(string graph1="", string graph2="", string graph_name="Benchmark Results")
{
    using namespace std;

    // data for y-axis(walltime)
    vector<double> y1;
    vector<double> y2;

    double percentage[200];

    int percent = 5;
    for(int i=0; i<20; ++i)
    {
        for(int j=0; j<10; ++j)
        { 
            percentage[j+(i*10)] = percent;
        }
        percent += 5;
    }

    // populate the data vector
    populateVector(graph1, &y1);
    populateVector(graph2, &y2);

    double* y1_ptr = &y1[0];
    double* y2_ptr = &y2[0];

    TCanvas *c1 = new TCanvas("c1","Test",200,10,1920,1080);
    c1->SetGrid();
    
    TGraph *g1 = new TGraph(200, percentage, y1_ptr);
    g1->SetTitle(graph_name.c_str());
    g1->GetXaxis()->SetTitle("Percentage of total number of events read(%)");
    g1->GetYaxis()->SetTitle("Wall time(s)");
    g1->GetXaxis()->CenterTitle();
    g1->GetYaxis()->CenterTitle();
    g1->SetMarkerColor(2);
    g1->Draw("AP*");

    g1->GetYaxis()->SetRangeUser(4.0,16.0);
    g1->Draw("AP*");

    TGraph *g2 = new TGraph(200, percentage, y2_ptr);
    g2->SetMarkerColor(4);
    g2->Draw("P*");


    TLegend *leg = new TLegend(0.1,0.75,0.3,0.9);
    leg->AddEntry(g1,"AsyncPrefetching off","p");
    leg->AddEntry(g2,"AsyncPrefetching on","p");
    leg->Draw();

    c1->Update();
    return 0;
}
