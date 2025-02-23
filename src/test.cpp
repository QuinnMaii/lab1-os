#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream file("data.bin", ios::binary);
    if (!file) {
        cerr << "Error: Cannot create file!" << endl;
        return 1;
    }

    for (int i = 1; i <= 1000000; ++i) { // Ghi 1 triệu số nguyên
        file.write(reinterpret_cast<const char*>(&i), sizeof(int));
    }

    file.close();
    cout << "Binary file data.bin created successfully!" << endl;
    return 0;
}
