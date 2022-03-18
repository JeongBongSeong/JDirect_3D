#include<windows.h>
#include<iostream>

void main()
{
    //{
    //    setlocale(LC_ALL, "KOREAN");
    //
    //    HANDLE hFile = CreateFile(
    //        L"test.txt",
    //        GENERIC_WRITE,
    //        0,
    //        NULL,
    //        CREATE_ALWAYS,
    //        FILE_ATTRIBUTE_NORMAL,
    //        NULL);
    //    if (hFile != NULL)
    //    {
    //        WCHAR buffer[] = L"하이";
    //        DWORD dwLength = sizeof(buffer);
    //        DWORD dwWritten;
    //        WORD wd = 0xFEFF;
    //
    //        BOOL bRet = WriteFile(
    //            hFile,
    //            &wd,
    //            2,
    //            0,
    //            NULL
    //        );
    //
    //        BOOL ret = WriteFile(
    //            hFile,
    //            buffer,
    //            dwLength,
    //            &dwWritten,
    //            NULL //_Inout_opt_ LPOVERLAPPED lpOverlapped       //이 속성이 있어야 비동기 입출력이 가능하다
    //        );
    //        if (ret == TRUE)
    //        {
    //            std::cout << "성공" << std::endl;
    //        }
    //        CloseHandle(hFile);
    //    }
    //
    //    HANDLE hFileRead = CreateFile(
    //        L"test.txt",
    //        GENERIC_READ,
    //        0,
    //        NULL,
    //        OPEN_EXISTING,
    //        FILE_ATTRIBUTE_NORMAL,
    //        NULL);
    //    if (hFileRead != NULL)
    //    {
    //        WCHAR buffer[256] = { 0, };
    //        DWORD dwLength = sizeof(buffer);
    //        DWORD dwRead;
    //        DWORD numberOfBytes;
    //        WORD wd = 0xFEFF;
    //        BOOL bret = ReadFile(
    //            hFileRead,
    //            &wd,
    //            sizeof(wd),
    //            &numberOfBytes,
    //            NULL
    //        );
    //
    //        BOOL ret = ReadFile(
    //            hFileRead,
    //            buffer,
    //            dwLength,
    //            &dwRead,
    //            NULL
    //        );
    //        if (ret == TRUE)
    //        {
    //            std::wcout << buffer;
    //        }
    //        CloseHandle(hFileRead);
    //    }
    //}
    
    LARGE_INTEGER filesize;
    OVERLAPPED g_ReadOV = { 0, };
    OVERLAPPED g_WriteOV = { 0, };
    
    HANDLE hFile = CreateFile(
        L"test1.txt",
        GENERIC_WRITE | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        );
    if (hFile != NULL)
    {
        WCHAR buffer[] = L"aaaaabbbbbcccccddddd";
        DWORD dwLength = sizeof(buffer);
        DWORD dwWritten;
        BOOL ret = WriteFile(
            hFile,
            buffer,
            dwLength,
            &dwWritten,
            NULL //_Inout_opt_ LPOVERLAPPED lpOverlapped       //이 속성이 있어야 비동기 입출력이 가능하다
        );
        if (ret == TRUE)
        {
            std::cout << "성공" << std::endl;
        }
        CloseHandle(hFile);
    }
}

//if (GetLastError() != WAIT_TIMEOUT)
//{
//    ::SetEvent(pServer->m_hKillEvent);
//}