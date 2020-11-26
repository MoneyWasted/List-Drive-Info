#include <windows.h>
#include <stdio.h>
#define BUFSIZE MAX_PATH

int wmain(void) 
{
    WCHAR volumeName[MAX_PATH + 1] = { 0 };
    WCHAR fileSystemName[MAX_PATH + 1] = { 0 };
    DWORD serialNumber = 0;
    DWORD maxComponentLen = 0;
    DWORD fileSystemFlags = 0;
    WCHAR Drive[] = L"A:\\";
    WCHAR I;

    // Walk through legal drive letters, skipping floppies.
    for (I = 'A'; I < 'Z'; I++) 
    {
        Drive[0] = I;
        bool DriveInfo = GetVolumeInformation(Drive, volumeName, sizeof(volumeName), &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystemName, sizeof(fileSystemName));
        if (DriveInfo)
        {
            if (wcscmp(volumeName, L"") != 0) {
                wprintf(L"Volume Name: %s\n", volumeName);
            } else {
                wprintf(L"Volume Name: Local Disk\n");
            }

            wprintf(L"Drive Path: %s\n", Drive);
            wprintf(L"Serial Number: %lu\n", serialNumber);
            wprintf(L"File System Name : %s\n", fileSystemName);
            wprintf(L"Max Component Length : %lu\n", maxComponentLen);
            wprintf(L"File system flags : 0x%.08X\n", fileSystemFlags);
            wprintf(L"\n");
        }
        else if (DriveInfo == FALSE) {} else {
            wprintf(L"Something went wrong! Error: %u\n", GetLastError());
        }
    }
    system("pause");
}