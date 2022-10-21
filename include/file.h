#ifndef LOGFILE_H
#define LOGFILE_H

class File{

private:
int32_t _intVal; // TODO : Consider replacing this logic
std::string _logSuffix=".log";

struct _Message{
	int32_t timestamp;
	int32_t type;
	std::string separator; // TODO : This needs more testing on what it represents. Consider changing to char, seems to be static in size
	std::string msg;
};

public:
std::vector<_Message> Msg;
bool CheckLogFileValidity(const std::filesystem::directory_entry& logFile);
bool OpenLogFile(const std::filesystem::directory_entry& logFile);
bool StoreFile(std::vector<_Message>& msg);
int32_t ParseInt(std::ifstream& istream,int32_t seekPos);
std::string ParseString(std::stringstream& log,int32_t seekPos,int32_t len);
void ParseMsg(std::ifstream& istream,std::stringstream& log,int32_t msgStart,int32_t seekPos,std::vector<_Message>& msg);

};

#endif
