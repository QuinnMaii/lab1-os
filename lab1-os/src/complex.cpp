#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

// Function to read data from file
vector<int> readDataFromFile(const string& filename) {
    vector<int> data;
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(1);
    }
    int num;
    while (file >> num) {
        data.push_back(num);
    }
    file.close();
    return data;
}

// Function to search for a number in an array
bool searchElement(const vector<int>& data, int target) {
    for (int num : data) {
        if (num == target) return true;
    }
    return false;
}

// Function to perform prime factorization
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

// Thread function for ema-search
void ema_search(int target, int repetitions) {
    vector<int> data = readDataFromFile("data.txt");
    for (int i = 0; i < repetitions; ++i) {
        searchElement(data, target);
    }
}

// Thread function for factorization
void factorize_task(int number, int repetitions) {
    for (int i = 0; i < repetitions; ++i) {
        factorize(number);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <target_number> <factorization_number> <repetitions>" << endl;
        return 1;
    }

    int target = strtol(argv[1], nullptr, 10);
    int number = strtol(argv[2], nullptr, 10);
    int repetitions = strtol(argv[3], nullptr, 10);

    auto start = high_resolution_clock::now();

    // Launching two threads
    thread t1(ema_search, target, repetitions);
    thread t2(factorize_task, number, repetitions);

    t1.join();
    t2.join();

    auto end = high_resolution_clock::now();

    cout << "Total Execution Time: " 
         << duration_cast<milliseconds>(end - start).count() 
         << " ms" << endl;

    return 0;
}
