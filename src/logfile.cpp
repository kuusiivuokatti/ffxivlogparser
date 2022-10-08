#include <fstream>
#include <vector>

#include "../include/logfile.h"

int32_t LogFile::ParseInt(std::ifstream& istream,int32_t seekPos){
// Parse message information that can be cast as int
	istream.seekg(seekPos,istream.beg);
	istream.read(reinterpret_cast<char *>(&_intVal),sizeof(int32_t));
	return _intVal;
};

char* LogFile::ParseChar(std::ifstream& istream,int32_t seekPos,int32_t len){
// Parse message information that can be cast as char
	char* charVal=new char[len]; // TODO : Add delete to this
	istream.seekg(seekPos,istream.beg);
	istream.read(charVal,len);
	return charVal;
};

void LogFile::InitMsgStruct(std::vector<_Message>& msg,int32_t count){
	msg.clear();
	msg.push_back(_Message());
	msg.reserve(count);
};

void LogFile::ParseMsg(std::ifstream& istream,int32_t msgStart,int32_t seekPos,int32_t index,std::vector<_Message>& msg){
// Parse raw message contents
	msg[index].timestamp=ParseInt(istream,msgStart+seekPos);
	seekPos+=4;
	msg[index].type=ParseInt(istream,msgStart+seekPos);
	seekPos+=4;
	msg[index].separator=ParseChar(istream,msgStart+seekPos,2);
	seekPos+=2;
	msg[index].msg=ParseChar(istream,msgStart+seekPos,seekPos);
};
