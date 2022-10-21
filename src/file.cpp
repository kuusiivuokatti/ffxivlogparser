#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <filesystem>
#include <iostream>

#include "../include/file.h"

bool File::CheckLogFileValidity(const std::filesystem::directory_entry& inFile){
// Check if the current file is valid before starting to try and read it

	const std::string inFileStr=inFile.path().string();

	if(std::filesystem::is_directory(inFile) || _logSuffix.size()>inFileStr.size()){
		return false;
	}else{
		return std::equal(inFileStr.begin()+inFileStr.size()-_logSuffix.size(),inFileStr.end(),_logSuffix.begin());
	};	

};

bool File::OpenLogFile(const std::filesystem::directory_entry& inFile){
// Open a single log file and go through each message

	bool returnValue=true;
	int32_t fileLen,contentLen,msgStart,msgCount,curPos,curMsgPos,curOffset;
	std::vector<int32_t> msgOffset;
	
	std::ifstream istream(inFile.path().string(),std::fstream::binary);

	if(istream.is_open()){

		try{
			// Read the log in its entirety
			std::stringstream logContent;
			logContent<<istream.rdbuf();

			// Get file and content lengths
			fileLen=ParseInt(istream,4);
			contentLen=ParseInt(istream,0);
			msgStart=(fileLen-contentLen)*4+8;

			// Read all the message offsets into a vector
			curPos=8;
			msgOffset.clear();
			do{
				msgOffset.push_back(ParseInt(istream,curPos));
				curPos+=4;
			}while(curPos<msgStart);
			msgCount=msgOffset.size();

			// Start going through the messages
			curMsgPos=msgStart;
			curOffset=msgOffset[0];
			for(int32_t i=0;i<msgCount;i++){
				if(i>0){curOffset=msgOffset[i]-msgOffset[i-1];};
				ParseMsg(istream,logContent,curMsgPos,curOffset,Msg);
				curMsgPos=msgStart+msgOffset[i]; // Add current offset to the next message start 	
			};
		}catch(const char* errMsg){
			std::cerr<<"Error while parsing the log file "<<errMsg<<'\n';
			returnValue=false;
		};
		
		istream.close();

	}else{
		std::cout<<"Couldn't open file.";
		returnValue=false;
	}

	return returnValue;

};

bool File::StoreFile(std::vector<_Message>& msg){
// Store the vector contents into a file

	std::ofstream outFile("./out.log");
	
	try{
		for(auto const& it : msg){
			outFile<<it.timestamp<<";"<<it.type<<";"<<it.separator<<";"<<it.msg<<'\n';
		};
	}catch(const char* errMsg){
		std::cerr<<"Error when saving log output "<<errMsg<<'\n';
		return false;
	};

	outFile.close();

	return true;

};

int32_t File::ParseInt(std::ifstream& istream,int32_t seekPos){
// Parse message information that can be cast as int
	istream.seekg(seekPos,istream.beg);
	istream.read(reinterpret_cast<char*>(&_intVal),sizeof(int32_t));
	return _intVal;
};

std::string File::ParseString(std::stringstream& log,int32_t seekPos,int32_t len){
// Parse message information that can be cast as string
	std::string strVal=log.str().substr(seekPos,len);
	return strVal;
};

void File::ParseMsg(std::ifstream& istream,std::stringstream& log,int32_t msgStart,int32_t seekPos,std::vector<_Message>& msg){
// Parse raw message contents
	msg.push_back({ParseInt(istream,msgStart),ParseInt(istream,msgStart+4),ParseString(log,msgStart,2),ParseString(log,msgStart,seekPos)});
};
