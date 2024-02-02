#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
using namespace std;


void WriteDataToFile(int i, double avgtime) {
    ofstream fout("data6.txt", ios::app);
    if (fout.is_open()) {
        fout<< i << " " << avgtime<< endl;
        fout.close();
    } else {
        cerr << "Unable to open file for writing data." << endl;
    }
}

void PlotChart() {
    FILE *gnuplotPipe = _popen("gnuplot -persist", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "plot 'data6.txt' with linespoints title 'Average Time'\n");
        _pclose(gnuplotPipe);
    } else {
        cerr << "Gnuplot not found. Please install Gnuplot." << endl;
    }
}


void tt(int n,string s) {
  if(n==0) return;
  tt(n-1,s+'T');
  tt(n-1,s+'F');
}


void Algorithm() {
    double time1, time2;
    for (int i = 3; i <= 20; i += 1) {
        time1 = (double)clock();
        for (int k = 0; k < 10; k++) {
            tt(i,"");
        }

        time2 = (double)clock();
        double avgtime = double(time2 - time1)*(1000.0)/double(CLOCKS_PER_SEC);
        cout << i << "-" <<(avgtime)<< endl;
        WriteDataToFile(i, avgtime);
    }
    PlotChart();
}

int main() {
    Algorithm();
    return 0;
}