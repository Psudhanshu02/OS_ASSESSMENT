#include <stdio.h>
#include <windows.h>

int main()
{
    HANDLE file = CreateFile("sample.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    printf("File Created Successfully.\n");

    DWORD dwBytesWritten;
    DWORD dwBytesRead;

    char *c = (char *)calloc(100, sizeof(char));

    if (ReadFile(file, c, 256, &dwBytesRead, NULL))
    {
        c[dwBytesRead] = '\0';
        printf("\nContents of file are:\n");
        printf("%s", c);
    }

    BOOLEAN text = WriteFile(file, "Hello World!!\n", strlen("Hello World!!\n"), &dwBytesWritten, NULL);

    if (text)
        printf("Written in File Successfully.");
    else
        printf("Failed to write in file.");

    CloseHandle(file);

    HANDLE file_read = CreateFile("sample.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (ReadFile(file_read, c, 256, &dwBytesRead, NULL))
    {
        c[dwBytesRead] = '\0';
        printf("\nContents of file are:\n");
        printf("%s", c);
    }

    else
        printf("Failed to read file.");

    if (CloseHandle(file_read) == 0)
        printf("Failed to close.");
    else
        printf("File Closed Successfully.");

    return 0;
}
