/*
 * main.cpp
 *
 *  Created on: Feb 27, 2024
 *      Author: HP
 */
#include "logger.h"

int main()
{
	Logger::LogFile_cfg("D:/Tourkey/Logger_File/log.txt");
    Logger::SelectOutputChannel(File_ch);
    Logger::set_priority(Info);
    Logger::log_write(Info,"Amina Info  %d",520);
    Logger::log_write(Error,"Error %d",404);
    Logger::log_write(Critical,"hi from critical %s","critcal mot");
    //Logger::free_file();
}





