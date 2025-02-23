#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

const size_t BLOCK_SIZE = 4096; // Kích thước khối đọc từ file (4 KB)

// 📌 Đọc file nhị phân thành các khối
bool searchInBinaryFile(const string& filename, int target) {
    ifstream file(filename, ios::binary); // Mở file nhị phân
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return false;
    }

    vector<int> buffer(BLOCK_SIZE / sizeof(int)); // Bộ đệm chứa số nguyên

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

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <target_number> <repetitions>" << endl;
        return 1;
    }

    int target = strtol(argv[1], nullptr, 10);
    int repetitions = strtol(argv[2], nullptr, 10);

    string filename = "data.bin"; // Đọc từ file nhị phân

    auto start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; ++i) {
        searchInBinaryFile(filename, target);
    }
    auto end = high_resolution_clock::now();

    cout << "Execution Time: " 
         << duration_cast<milliseconds>(end - start).count() 
         << " ms" << endl;

    return 0;
}
