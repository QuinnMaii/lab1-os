#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

void print_time(SYSTEMTIME time) {
    printf("%02d/%02d/%04d %02d:%02d:%02d:%03d\n", 
        time.wDay, time.wMonth, time.wYear,
        time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
}

void execute_program(const char *command) {
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    char cmdline[1024];
    strcpy(cmdline, command);

    // Handle the "dir" command by redirecting it to cmd.exe
    if (strcmp(command, "dir") == 0) {
        strcpy(cmdline, "cmd.exe /C dir");
    } 
    // Handle notepad.exe with full path if necessary
    else if (strcmp(command, "notepad") == 0) {
        strcpy(cmdline, "C:\\Windows\\System32\\notepad.exe");
    }
    // Handle "mkdir" command
    else if (strncmp(command, "mkdir", 5) == 0) {
        char dir_name[1024];
        strcpy(dir_name, command + 6);
        if (CreateDirectory(dir_name, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
            printf("Directory created or already exists: %s\n", dir_name);
        } else {
            printf("Failed to create directory: %s\n", dir_name);
        }
        return;
    }
    // Handle "cd" command
    else if (strncmp(command, "cd", 2) == 0) {
        char dir_name[1024];
        strcpy(dir_name, command + 3);  // Get the directory part of the command
        if (SetCurrentDirectory(dir_name)) {
            printf("Changed directory to: %s\n", dir_name);
        } else {
            printf("Failed to change directory to: %s\n", dir_name);
        }
        return;
    }

    // Record start time
    SYSTEMTIME start_time;
    GetSystemTime(&start_time);
    printf("Start time: ");
    print_time(start_time);

    // Create process as user for other commands
    if (CreateProcessAsUser(NULL, NULL, cmdline, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Record end time
        SYSTEMTIME end_time;
        GetSystemTime(&end_time);
        printf("End time: ");
        print_time(end_time);

        // Calculate the elapsed time (completion time - start time)
        FILETIME ftStart, ftEnd;
        SYSTEMTIME stUTC, stLocal;
        DWORD elapsed_time;
        
        // Convert SYSTEMTIME to FILETIME
        SystemTimeToFileTime(&start_time, &ftStart);
        SystemTimeToFileTime(&end_time, &ftEnd);

        // Calculate the time difference in milliseconds
        elapsed_time = (ftEnd.dwLowDateTime - ftStart.dwLowDateTime) / 10000;
        printf("Program completed in %lu milliseconds.\n", elapsed_time);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("Error creating process: %d\n", GetLastError());
    }
}

int main() {
    char input[256];

    printf("Shell: ");
    while (fgets(input, sizeof(input), stdin)) {
        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Execute the command entered by user
        execute_program(input);

        printf("Shell: ");
    }

    return 0;
}
