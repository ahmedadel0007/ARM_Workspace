#pragma once

#include <stdio.h>
#include <mutex>
#include <ctime>
using namespace std::chrono_literals;

enum LogType
{
	Info,
    Warning,
    Error,
    Critical
};

enum OutputChannel
{
    Console_ch,
    File_ch
};

class Logger
{
private:
	static LogType priority;
	//static std::mutex log_mutex;
    static const char* filepath;
	static FILE* file;
    static OutputChannel output;
	template<typename... Args>

	static void log(const char* message_priority_str, LogType message_priority, const char* message, Args... args)
	{
		if (priority <= message_priority)
		{
            std::time_t current_time = std::time(0);
			    std::tm* timestamp = std::localtime(&current_time);
			    char buffer[80];
			    strftime(buffer, 80, "%c", timestamp);
            if(output==Console_ch)
            {

			//std::scoped_lock lock(log_mutex);
			printf("%s\t", buffer);
			printf(message_priority_str);
			printf(message, args...);
			printf("\n");
            }
			else if (output==File_ch)
			{
				fprintf(file, "%s\t", buffer);
				fprintf(file, message_priority_str);
				fprintf(file, message, args...);
				fprintf(file, "\n");
			}
		}
	}
public:

	static void set_priority(LogType new_priority)
	{
		priority = new_priority;
	}

	template<typename... Args>
	static void log_write(LogType Type, const char* message, Args... args)
	{

                 if (priority<=Type)
            {
                    if (Type <= Info)
		            {
			            log("[INFO]\t", Info, message, args...);
		            }
                    else if (priority <= Warning)
                    {
                        log("[WARNING]\t", Warning, message, args...);
                    }
                    else if (priority <= Error)
                    {
                        log("[ERROR]\t", Error, message, args...);
                    }
                    else
                    {
                        log("[CRITICAL]\t", Error, message, args...);
                    }
            }


    }
    static void SelectOutputChannel(OutputChannel output_ch)
    {
        output=output_ch;
        if (output_ch==File_ch)
        {
            file = fopen(filepath, "a");

        }
    }

    static void LogFile_cfg (const char* new_file_path)
    {
        filepath=new_file_path;
    }

	static void free_file()
	{
		fclose(file);
		file = 0;
	}

};

LogType Logger::priority = Info;
//std::mutex Logger::log_mutex;
const char* Logger::filepath = 0;
FILE* Logger::file = 0;
OutputChannel Logger::output=Console_ch;


