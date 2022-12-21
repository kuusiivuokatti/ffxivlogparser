#ifndef LOGFILE_H
#define LOGFILE_H

#include "config.h"

class File{

private:
const std::string _logSuffix=".log";
const std::string _logHeader="date;time;type;separator;message";

struct _Message{
	std::string timestamp;
	std::string type;
	std::string separator; // TODO : This needs more testing on what it represents. Consider changing to char, seems to be static in size
	std::string msg;
};

int32_t ParseInt(std::ifstream& istream,int32_t seekPos);
std::string ParseString(std::stringstream& log,int32_t seekPos,int32_t len);
std::string ConvertTimestampToDateTime(int32_t timestamp);
void ParseMsg(std::ifstream& istream,std::stringstream& log,int32_t msgStart,int32_t seekPos,std::vector<_Message>& msg);

public:
std::vector<_Message> Msg;
bool CheckLogFileValidity(const std::filesystem::directory_entry& logFile);
bool OpenLogFile(const std::filesystem::directory_entry& logFile);
bool StoreFile(std::vector<_Message>& msg);
};

#endif
