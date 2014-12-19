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

int plotScatter(string file="", string graph_name="Xrd Benchmark Results")
{
    using namespace std;

    // data for y-axis(walltime)
    vector<double> y;
    
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
    populateVector(file, &y);
    
    double* y_ptr = &y[0];

    TCanvas *c1 = new TCanvas("c1","Test",200,10,1920,1080);
    c1->SetGrid();
    
    TGraph *g = new TGraph(200, percentage, y_ptr);
    g->SetTitle(graph_name.c_str());
    g->GetXaxis()->SetTitle("Percentage of total number of events read(%)");
    g->GetYaxis()->SetTitle("Wall time(s)");
    g->GetXaxis()->CenterTitle();
    g->GetYaxis()->CenterTitle();

    g->SetMarkerColor(2);

    g->Draw("AP*");

    c1->Update();
    return 0;
}
