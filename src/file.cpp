#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <filesystem>
#include <iostream>

#include "../include/file.h"

bool File::CheckLogFileValidity(const std::filesystem::directory_entry& inFile){

	const std::string inFileStr=inFile.path().string();

	if(std::filesystem::is_directory(inFile) || _logSuffix.size()>inFileStr.size()){
		return false;
	}else{
		return std::equal(inFileStr.begin()+inFileStr.size()-_logSuffix.size(),inFileStr.end(),_logSuffix.begin());
	};	

};

bool File::OpenLogFile(const std::filesystem::directory_entry& inFile){

	bool returnValue=true;
	std::ifstream istream(inFile.path().string(),std::fstream::binary);

	if(istream.is_open()){

		try{
			std::stringstream logContent;
			logContent<<istream.rdbuf();

			int32_t fileLen=ParseInt(istream,4);
			int32_t contentLen=ParseInt(istream,0);
			int32_t msgStart=(fileLen-contentLen)*4+8;
			
			int32_t curPos=8;
			std::vector<int32_t> msgOffset;
			msgOffset.clear();
			do{
				msgOffset.push_back(ParseInt(istream,curPos));
				curPos+=4;
			}while(curPos<msgStart);
			int32_t msgCount=msgOffset.size();

			int32_t curMsgPos=msgStart;
			int32_t curOffset=msgOffset[0];
			for(int32_t i=0;i<msgCount;i++){
				if(i>0){curOffset=msgOffset[i]-msgOffset[i-1];};
				ParseMsg(istream,logContent,curMsgPos,curOffset,Msg);
				curMsgPos=msgStart+msgOffset[i];
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
 
	std::ofstream outFile("./out.log");
	bool returnValue=true;
	
	try{
		outFile<<_logHeader<<'\n';
		for(auto const& it : msg){
			outFile<<it.timestamp<<";"<<it.type<<";"<<it.separator<<";"<<it.msg<<'\n';
		};
	}catch(const char* errMsg){
		std::cerr<<"Error when saving log output "<<errMsg<<'\n';
	};

	outFile.close();

	return returnValue;

};

int32_t File::ParseInt(std::ifstream& istream,int32_t seekPos){
	int32_t intVal;
	istream.seekg(seekPos,istream.beg);
	istream.read(reinterpret_cast<char*>(&intVal),sizeof(int32_t));
	return intVal;
};

std::string File::ParseString(std::stringstream& log,int32_t seekPos,int32_t len){
	std::string strVal=log.str().substr(seekPos,len);
	return strVal;
};

std::string File::ConvertTimestampToDateTime(int32_t timestamp){

	time_t time=timestamp;
	tm* ltm=localtime(&time);
	std::stringstream timeSs;
	timeSs<<1900+ltm->tm_year<<'-'
		<<std::setfill('0')<<std::setw(2)<<1+ltm->tm_mon<<'-'
		<<std::setfill('0')<<std::setw(2)<<ltm->tm_mday<<';'
		<<std::setfill('0')<<std::setw(2)<<ltm->tm_hour<<':'
		<<std::setfill('0')<<std::setw(2)<<ltm->tm_min<<':'
		<<std::setfill('0')<<std::setw(2)<<ltm->tm_sec;

	std::string timeStr;
	timeSs>>timeStr;

	return timeStr;

};

void File::ParseMsg(std::ifstream& istream,std::stringstream& log,int32_t msgStart,int32_t seekPos,std::vector<_Message>& msg){
	msg.push_back({ConvertTimestampToDateTime(ParseInt(istream,msgStart)),
	ParseInt(istream,msgStart+4),
	ParseString(log,msgStart,2),
	ParseString(log,msgStart,seekPos)});
};
