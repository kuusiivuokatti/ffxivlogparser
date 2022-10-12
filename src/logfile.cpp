#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "../include/logfile.h"

int32_t LogFile::ParseInt(std::ifstream& istream,int32_t seekPos){
// Parse message information that can be cast as int
	istream.seekg(seekPos,istream.beg);
	istream.read(reinterpret_cast<char*>(&_intVal),sizeof(int32_t));
	return _intVal;
};

std::string LogFile::ParseString(std::stringstream& log,int32_t seekPos,int32_t len){
// Parse message information that can be cast as string
	std::string strVal=log.str().substr(seekPos,len);
	return strVal;
};

void LogFile::InitMsgStruct(std::vector<_Message>& msg,int32_t count){
	msg.clear();
};

void LogFile::ParseMsg(std::ifstream& istream,std::stringstream& log,int32_t msgStart,int32_t seekPos,std::vector<_Message>& msg){
// Parse raw message contents
// TODO : Consider renaming msg to something else to differentiate it from the struct msg
	msg.push_back({ParseInt(istream,msgStart),ParseInt(istream,msgStart+4),ParseString(log,msgStart,2),ParseString(log,msgStart,seekPos)});
};
