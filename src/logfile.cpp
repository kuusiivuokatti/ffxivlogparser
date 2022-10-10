#include <fstream>
#include <vector>
#include <string.h>

#include <iostream>

#include "../include/logfile.h"

int32_t LogFile::ParseInt(std::ifstream& istream,int32_t seekPos){
// Parse message information that can be cast as int
	istream.seekg(seekPos,istream.beg);
	istream.read(reinterpret_cast<char *>(&_intVal),sizeof(int32_t));
	return _intVal;
};

void LogFile::ParseChar(std::ifstream& istream,int32_t seekPos,int32_t len,char* charVal){
// Parse message information that can be cast as char
// TODO : rewrite this

	char outChar[len];

	istream.seekg(seekPos,istream.beg);
	istream.read(outChar,len);
	
	strncpy(charVal,outChar,len);

// TODO : check what triggers this error state
	if(!istream){
		std::cout<<"ERROR WHILE READING, BYTES READ: "<<istream.gcount()<<" RESETTING"<<'\n';
		istream.clear();
	};
			
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
// TODO : rewrite this
	char charVal[2];
	ParseChar(istream,msgStart+seekPos,2,charVal);
	msg[index].separator=charVal;
	seekPos+=2;
	char charVal2[seekPos];
	ParseChar(istream,msgStart+seekPos,seekPos,charVal2);
	msg[index].msg=charVal2;
};
