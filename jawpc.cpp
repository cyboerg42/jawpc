// Just another pi calc - 02_04_2017 - Meks Pwnschlager & Peter Kowalsky (acheloos)
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>

using namespace std;

#define M_PI 3.141592653589793238462643383279502884197169399375

// int rand1 = rand() % MAX_RANDOM

long double get_pi_from_prob(int count, int iter){
    long double c = (long double)count/(long double)iter;
    return sqrtl((long double)6/c);  
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

template<typename T>
string toString(T x)
{
    ostringstream result;
    result << x;
    return result.str();
}

int main (int argc, char *argv[]) {
    if (argc <= 1) {
        cout << "Usage : jaci max_random max_iter <-d>" << endl;
        cout << "-d -> Debug, display every 100th coprime result (&disable fileoutput)" << endl;
        return 0;
    }
    int max_random = atoi(argv[1]);
    int max_iter = atoi(argv[2]);
    if (max_random == 0 || max_iter == 0) {
        cout << "Usage : jaci max_random max_iter <-d>\n";
        cout << "-d -> Debug, display every 100th coprime result (disables fileoutput)" << endl;
        return 0;
    }

    int seed = time(NULL);
    cout << "Using " << seed << " as seed for rand()." << endl;
    srand (seed);
    long double best_pi;
    long double s_err = 1;
    int c_best = 0, i_best = 0, rand1_best = 0, rand2_best= 0;

    int count = 0;
    register unsigned int rand1, rand2;
    ofstream graphd;
    string filename = "datapoint_" + toString(seed) + "_" + toString(max_random) + "_" + toString(max_iter);
    if(argc!=4)graphd.open(filename.c_str());
    for(int i = 1; i < max_iter; i++) {
        rand1 = int(rand()% max_random); rand2 = int(rand()% max_random);
        if (gcd(rand1,rand2) == 1) count++;
        if (count > 0) {
            long double d = get_pi_from_prob(count, i);
            long double err = abs(d - M_PI);
            if(argc==4){ if(count%100 == 0) cout << "[" << i << "/" << max_iter << "] Pi / Error: " << d << "/" << err << "\n";}
            else graphd << err << endl; 
            if (err < s_err) {
                s_err = err;
                best_pi = d;
                rand1_best = rand1; rand2_best = rand2; c_best = count; i_best = i;
            }
        }
    }
    graphd.close();
    cout << "Best pi found -> " << setprecision(40) << best_pi << " error -> " << s_err << "\n";
    cout << "pi should be  -> " << M_PI << endl;
    cout << "found at -> count: " << c_best << "; iter: " << i_best << "; rand1: " << rand1_best << "; rand2: " << rand2_best << endl;
    return 0;
}

