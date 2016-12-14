#include "Log.h"

void Log(std::string message)
{
	std::ofstream fout(LOGFILE, std::ofstream::app);
	fout << message << "\n";
	fout.close();
}

void LogErr(std::string message)
{
	Log(message);
	exit(1);
}
