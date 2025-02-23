#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

const size_t BLOCK_SIZE = 4096; // Kích thước khối đọc từ file (4 KB)

// 📌 Đọc file nhị phân thành các khối và tìm số nguyên
bool searchInBinaryFile(const string& filename, int target) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return false;
    }

    vector<int> buffer(BLOCK_SIZE / sizeof(int));

    while (file.read(reinterpret_cast<char*>(buffer.data()), BLOCK_SIZE)) {
        size_t read_count = file.gcount() / sizeof(int);
        for (size_t i = 0; i < read_count; ++i) {
            if (buffer[i] == target) {
                return true;
            }
        }
    }

    // Kiểm tra phần dữ liệu còn lại nếu chưa đầy khối
    size_t remaining = file.gcount() / sizeof(int);
    for (size_t i = 0; i < remaining; ++i) {
        if (buffer[i] == target) {
            return true;
        }
    }

    return false;
}

// 📌 Chạy `ema_search-int.exe` nhưng trong chương trình
void ema_search(int target, int repetitions) {
    string filename = "data.bin"; // File nhị phân
    for (int i = 0; i < repetitions; ++i) {
        searchInBinaryFile(filename, target);
    }
}

// 📌 Phân tích thừa số nguyên tố
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

// 📌 Chạy `factorize.exe` nhưng trong chương trình
void factorize_task(int number, int repetitions) {
    for (int i = 0; i < repetitions; ++i) {
        factorize(number);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <target_number> <search_repetitions> <factorization_number> <factorization_repetitions>" << endl;
        return 1;
    }

    int target = strtol(argv[1], nullptr, 10);
    int search_repetitions = strtol(argv[2], nullptr, 10);
    int number = strtol(argv[3], nullptr, 10);
    int factorization_repetitions = strtol(argv[4], nullptr, 10);

    int num_threads = thread::hardware_concurrency(); // Xác định số lượng lõi CPU
    if (num_threads < 2) num_threads = 2; // Ít nhất 2 luồng

    cout << "Running with " << num_threads << " threads..." << endl;

    auto start = high_resolution_clock::now();

    vector<thread> threads;

    // Chia đều số lượng luồng
    int half_threads = num_threads / 2;

    for (int i = 0; i < half_threads; ++i) {
        threads.emplace_back(ema_search, target, search_repetitions);
    }
    for (int i = 0; i < num_threads - half_threads; ++i) {
        threads.emplace_back(factorize_task, number, factorization_repetitions);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end = high_resolution_clock::now();

    cout << "Total Execution Time: " 
         << duration_cast<milliseconds>(end - start).count() 
         << " ms" << endl;

    return 0;
}
