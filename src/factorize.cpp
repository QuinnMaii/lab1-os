#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

// Function to find prime factors
vector<int> factorize(int n) {
    vector<int> factors;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <number> <repetitions>" << endl;
        return 1;
    }

    int number = strtol(argv[1], nullptr, 10);
    int repetitions = strtol(argv[2], nullptr, 10);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; ++i) {
        factorize(number);
    }
    auto end = high_resolution_clock::now();

    cout << "Execution Time: " 
         << duration_cast<milliseconds>(end - start).count() 
         << " ms" << endl;

    return 0;
}
