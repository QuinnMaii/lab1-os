#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

// 📌 Hàm lấy thời gian hiện tại
SYSTEMTIME getCurrentTime() {
    SYSTEMTIME time;
    GetSystemTime(&time);
    return time;
}

// 📌 Hàm tính thời gian chạy tiến trình
void printExecutionTime(SYSTEMTIME start_time, SYSTEMTIME end_time) {
    FILETIME ftStart, ftEnd;
    ULARGE_INTEGER uStart, uEnd;

    SystemTimeToFileTime(&start_time, &ftStart);
    SystemTimeToFileTime(&end_time, &ftEnd);

    uStart.LowPart = ftStart.dwLowDateTime;
    uStart.HighPart = ftStart.dwHighDateTime;
    uEnd.LowPart = ftEnd.dwLowDateTime;
    uEnd.HighPart = ftEnd.dwHighDateTime;

    DWORD elapsed_time = static_cast<DWORD>((uEnd.QuadPart - uStart.QuadPart) / 10000);
    cout << "Total Execution Time: " << elapsed_time << " ms" << endl;
}

// 📌 Hàm chạy tiến trình với các tham số
void executeCommand(const wstring& command, const vector<wstring>& args) {
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    wstring cmdLine = command;
    for (const auto& arg : args) {
        cmdLine += L" " + arg;
    }

    wchar_t cmd[MAX_PATH];
    wcscpy_s(cmd, cmdLine.c_str());

    SYSTEMTIME start_time = getCurrentTime();

    if (CreateProcessW(NULL, cmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hThread);
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
    } else {
        wcerr << L"Failed to execute: " << command << L" Error Code: " << GetLastError() << endl;
    }

    SYSTEMTIME end_time = getCurrentTime();
    printExecutionTime(start_time, end_time);
}

// 📌 Chạy `ema-search-int.exe` song song với tham số từ người dùng
void runEmaSearchParallel(int number, int iterations, int num_loaders) {
    vector<thread> threads;
    for (int i = 0; i < num_loaders; ++i) {
        threads.emplace_back([=]() {
            vector<wstring> args = { to_wstring(number), to_wstring(iterations) };
            executeCommand(L"ema-search-int.exe", args);
        });
    }
    for (auto& t : threads) {
        t.join();
    }
}

// 📌 Chạy `factorize.exe` song song với tham số từ người dùng
void runFactorizeParallel(int number, int iterations, int num_loaders) {
    vector<thread> threads;
    for (int i = 0; i < num_loaders; ++i) {
        threads.emplace_back([=]() {
            vector<wstring> args = { to_wstring(number), to_wstring(iterations) };
            executeCommand(L"factorize.exe", args);
        });
    }
    for (auto& t : threads) {
        t.join();
    }
}

// 📌 Chạy `complex.exe` với các tham số từ người dùng
void runComplexParallel(int ema_number, int ema_iterations, int fact_number, int fact_iterations, int num_loaders) {
    vector<thread> threads;
    for (int i = 0; i < num_loaders; ++i) {
        threads.emplace_back([=]() {
            vector<wstring> args = {
                to_wstring(ema_number),
                to_wstring(ema_iterations),
                to_wstring(fact_number),
                to_wstring(fact_iterations)
            };
            executeCommand(L"complex.exe", args);
        });
    }
    for (auto& t : threads) {
        t.join();
    }
}

// 📌 Lệnh `ls` - Hiển thị thư mục hiện tại
void ls() {
    cout << "Directory contents:\n";
    system("dir");
}

// 📌 Lệnh `echo` - In thông điệp
void echo(const string& message) {
    cout << message << endl;
}

// 📌 Hàm `shell()`
void shell() {
    while (true) {
        string userInput;
        cout << "shell> ";
        getline(cin, userInput);

        istringstream iss(userInput);
        string command;
        iss >> command;

        vector<string> args;
        string arg;
        while (iss >> arg) {
            args.push_back(arg);
        }

        if (command == "ls") {
            ls();
        } else if (command == "echo") {
            if (!args.empty()) {
                echo(userInput.substr(userInput.find(' ') + 1));
            } else {
                cout << "echo: Missing argument.\n";
            }
        } else if (command == "exit") {
            exit(0);
        } 
        // 📌 Chạy `ema-search-int.exe` với tham số từ người dùng
        else if (command == "ema-search") {
            if (args.size() < 3) {
                cout << "Usage: ema-search <number> <iterations> <num_loaders>\n";
                continue;
            }
            int number = stoi(args[0]);
            int iterations = stoi(args[1]);
            int num_loaders = stoi(args[2]);
            runEmaSearchParallel(number, iterations, num_loaders);
        } 
        // 📌 Chạy `factorize.exe` với tham số từ người dùng
        else if (command == "factorize") {
            if (args.size() < 3) {
                cout << "Usage: factorize <number> <iterations> <num_loaders>\n";
                continue;
            }
            int number = stoi(args[0]);
            int iterations = stoi(args[1]);
            int num_loaders = stoi(args[2]);
            runFactorizeParallel(number, iterations, num_loaders);
        }
        // 📌 Chạy `complex.exe` với tham số từ người dùng
        else if (command == "complex") {
            if (args.size() < 5) {
                cout << "Usage: complex <ema_number> <ema_iterations> <fact_number> <fact_iterations> <num_loaders>\n";
                continue;
            }
            int ema_number = stoi(args[0]);
            int ema_iterations = stoi(args[1]);
            int fact_number = stoi(args[2]);
            int fact_iterations = stoi(args[3]);
            int num_loaders = stoi(args[4]);
            runComplexParallel(ema_number, ema_iterations, fact_number, fact_iterations, num_loaders);
        } else {
            cout << "Unknown command!\n";
        }
    }
}

// 📌 Hàm `main()`
int main() {
    shell();
    return 0;
}
