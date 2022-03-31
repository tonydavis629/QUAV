#include <iterator>
#include <stdio.h>
#include <iostream>

#include <vector>
#include <string>

#include "unistd.h"
#include <sys/types.h>
#include <libusb-1.0/libusb.h>
#include "../source/UsbDriver.h"

#include <time.h>

////Joe's Time and date code //////
typedef struct DateAndTime {
    const char* power;
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int seconds;
    int msec;
} DateAndTime;
///////////////////////////////////



struct DateAndTime main(void)
{
//   printf("main. start\n");

////Joe's Date and time code////////////////////////
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
/////////////////////////////////////////////////////

    UsbDriver usbDriver;
    
    // detect
    std::vector<int> devices = usbDriver.detect();
    
//    printf("main. %d device(s) detected.\n", (int)devices.size());

//      std::string mode, command;
//      std::cout << "Do you want to enter interactive terminal mode? [y/n] ";
//      std::getline(std::cin, mode);

//    if(mode == "y")
//    {
//      	while(command != "exit")
//   	{
//      	  	std::cout << "Please enter command: [command/exit] ";
//      	    std::getline(std::cin, command);
//      	    if(command != "exit" )
//      	    {
//      	    	std::string response = usbDriver.executeCommand(0, command);
//      	    	printf("response = %s", response.c_str());
//      	    }
//    	}
//    }

//    std::cout << "Do you want to enter continuous send mode? [y/n] ";
//      std::cin >> mode;

//     if(mode == "y")
//     {
		for (std::vector<int>::iterator it = devices.begin(); it < devices.end(); ++it)
		{
		  int channelId = *it;

		  // continues send mode
		  usbDriver.startMeasuring(channelId);
		}

		int counter = 0;
//		while (devices.size() > 0 && counter < 1000)
//		{
			for (std::vector<int>::iterator it = devices.begin(); it < devices.end();)
			{
				int channelId = *it;
				std::string reading = usbDriver.getReading(channelId);
				if(!reading.empty())
				{
					if(reading == CHANNEL_CLOSE)
					{
						// stop measuring
						usbDriver.stopMeasuring(channelId);

						// close channel
						usbDriver.close(channelId);

						// remove channel from devices list
						it = devices.erase(it);
						continue;
					}
					else
					{
						 date_and_time.power = reading.c_str();
//						 printf("%s", reading.c_str());
						 printf("%s", date_and_time.power);
                                                 printf("%02d:%02d:%02d.%03d %02d-%02d-%04d\n",
                                                      date_and_time.hour,
                                                      date_and_time.minutes,
                                                      date_and_time.seconds,
                                                      date_and_time.msec,
                                                      date_and_time.day,
                                                      date_and_time.month,
                                                      date_and_time.year);

					}
				}
				++it;
			}
			usleep(100000); // 100 milliseconds
			counter++;
//		}

		for (std::vector<int>::iterator it = devices.begin(); it < devices.end(); ++it)
		{
			int channelId = *it;
			usbDriver.stopMeasuring(channelId);
		}
//	}
    
	printf("main. end\n");
    return date_and_time;
}



