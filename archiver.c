#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include <time.h>

int main() {
    _mkdir("archive");

    while (1) {
        Sleep(5000); // 5 секунд

        WIN32_FILE_ATTRIBUTE_DATA fad;
        if (GetFileAttributesExA("logs/current.log", GetFileExInfoStandard, &fad)) {

            // преобразуем FILETIME -> SYSTEMTIME
            FILETIME ft = fad.ftCreationTime;
            SYSTEMTIME stUTC, stLocal;
            FileTimeToSystemTime(&ft, &stUTC);
            SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

            // формируем имя вида log_YYYYMMDD_HHMMSS.log
            char newname[256];
            sprintf(
                newname,
                "archive/log_%04d%02d%02d_%02d%02d%02d.log",
                stLocal.wYear, stLocal.wMonth, stLocal.wDay,
                stLocal.wHour, stLocal.wMinute, stLocal.wSecond
            );

            // перенос файла
            MoveFileA("logs/current.log", newname);
        }
    }
    return 0;
}
