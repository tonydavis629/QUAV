#include <sys/time.h>
#include <time.h>
#include <stdio.h>

typedef struct DateAndTime {
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int seconds;
    int msec;
} DateAndTime;

int
main(void)
{
    DateAndTime date_and_time;
    struct timeval tv;
    struct tm *tm;

    gettimeofday(&tv, NULL);

    tm = localtime(&tv.tv_sec);

    // Add 1900 to get the right year value
    // read the manual page for localtime()
    date_and_time.year = tm->tm_year + 1900;
    // Months are 0 based in struct tm
    date_and_time.month = tm->tm_mon + 1;
    date_and_time.day = tm->tm_mday;
    date_and_time.hour = tm->tm_hour;
    date_and_time.minutes = tm->tm_min;
    date_and_time.seconds = tm->tm_sec;
    date_and_time.msec = (int) (tv.tv_usec / 1000);

    fprintf(stdout, "%02d:%02d:%02d.%03d %02d-%02d-%04d\n",
        date_and_time.hour,
        date_and_time.minutes,
        date_and_time.seconds,
        date_and_time.msec,
        date_and_time.day,
        date_and_time.month,
        date_and_time.year
    );
    return 0;
}


