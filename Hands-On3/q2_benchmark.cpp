#include<iostream>
#include<ctime>
#include<chrono>

using namespace std;

auto get_unix_time() {
    auto now = chrono::system_clock::now();

    auto duration = now.time_since_epoch();

    return chrono::duration_cast<chrono::milliseconds>(duration).count();
}

unsigned long function(unsigned long n) {
    unsigned long x = 1, i, j;

    for(i=1; i<=n; i++) {
        for(j=1; j<=n; j++) {
            x = x + 1;
        }
    }

    return x;
}


int main()
{
    unsigned long test_cases[] = {250, 1250, 1500, 2000, 7500, 15000, 20000, 35000, 75000, 125000, 150000, 175000, 200000, 225000, 250000, 275000, 300000};
    int T = sizeof(test_cases)/sizeof(test_cases[0]);

    for(int t=0; t<T; t++) {
        auto start = get_unix_time();
        function(test_cases[t]);
        auto stop = get_unix_time();
        cout << test_cases[t]<< " : " <<stop - start << endl;
    } 

    return 0;
}