#pragma once
#include <fstream>
#include <string>

#define LOGFILE	"log.txt"
void Log(std::string message);    // logs a message to LOGFILE
void LogErr(std::string message); // logs a message; execution is interrupted