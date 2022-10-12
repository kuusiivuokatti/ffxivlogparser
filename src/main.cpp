#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "../include/main.h"

#define PATHLOG "../log/"

int main(){

	LogFile log;
	int32_t fileLen,contentLen,msgStart,msgCount,curPos,curMsgPos,curOffset;
	std::vector<int32_t> msgOffset;
	
	std::ifstream istream(PATHLOG"00000000.log",std::fstream::binary);

	if(istream.is_open()){

		// Read the log in its entirety
		std::stringstream logContent;
		logContent<<istream.rdbuf();

		// Get file and content lengths
		fileLen=log.ParseInt(istream,4);
		contentLen=log.ParseInt(istream,0);
		msgStart=(fileLen-contentLen)*4+8;

		// Read all the message offsets into a vector
		curPos=8;
		msgOffset.clear();
		do{
			msgOffset.push_back(log.ParseInt(istream,curPos));
			curPos+=4;
		}while(curPos<msgStart);
		msgCount=msgOffset.size();
		
		std::cout<<"File length: "<<fileLen<<", content length: "<<contentLen<<", message start: "<<msgStart<<", message count: "<<msgCount<<'\n';

		// Start going through the messages
		log.InitMsgStruct(log.Msg,msgCount);
		curMsgPos=msgStart;
		curOffset=msgOffset[0];
		for(int32_t i=0;i<msgCount;i++){
					
			if(i>0){curOffset=msgOffset[i]-msgOffset[i-1];};

			log.ParseMsg(istream,logContent,curMsgPos,curOffset,log.Msg);
			std::cout<<i<<" | "<<curMsgPos<<" | "<<msgOffset[i]<<" | "<<log.Msg[i].timestamp<<" | "<<log.Msg[i].type<<" | "<<log.Msg[i].separator<< " | "<<log.Msg[i].msg<<'\n';
			curMsgPos=msgStart+msgOffset[i]; // Add current offset to the next message start 	
		};
		
		istream.close();

	}else{
		std::cout<<"File not open"<<std::endl;
	}

	return 0;
};
