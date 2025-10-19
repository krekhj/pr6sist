#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include <time.h>

int main() {
    _mkdir("logs"); // создание папки если нет

    while (1) {
        FILE *f = fopen("logs/current.log", "a");
        if (!f) {
            perror("fopen");
            return 1;
        }

        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);

        char buffer[64];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S\n", tm_info);
        fputs(buffer, f);

        fclose(f);
        Sleep(1000); // 1 секунда
    }

    return 0;
}
