#include<iostream>
#include<cstdlib>
#include<time.h>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
void WriteDataToFile(long int i, double avgtime) {
    ofstream fout("data4.txt", ios::app);
    if (fout.is_open()) {
        fout<< i << " " << avgtime << endl;
        fout.close();
    } else {
        cerr << "Unable to open file for writing data." << endl;
    }
}
void PlotChart() {
    FILE *gnuplotPipe = _popen("gnuplot -persist", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "plot 'data4.txt' with linespoints title 'Average Time'\n");
        _pclose(gnuplotPipe);
    } else {
        cerr << "Gnuplot not found. Please install Gnuplot." << endl;
    }
}

void Generate(int a[], int i) {
    for (int j = 0; j <= i; j++) {
        a[j] = rand();
    }
}

int HornerRule(int arr[],int n,int m,int x){
   if(n==m) return arr[m];
   return arr[m] + x*HornerRule(arr,n,m+1,x);
}

void Algorithm() {
    double time1, time2;
    for (int i = 1000; i <= 50000; i += 1000) {
        int a[i];
        Generate(a, i);
        time1 = (double)clock();
        for (int k = 0; k < 10; k++) {
            int f=HornerRule(a,i,0,100);
        }

        time2 = (double)clock();
         double avgtime = double(time2 - time1)*(1000.0)/double(CLOCKS_PER_SEC);
        cout << i << "-" << avgtime << endl;
        WriteDataToFile(i, avgtime);
    }
    PlotChart();
}

int main() {
    Algorithm();
    return 0;
}