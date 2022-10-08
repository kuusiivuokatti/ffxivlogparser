#include <iostream>
#include <fstream>
#include <vector>

#include "../include/main.h"

#define PATHLOG "../log/"

int main(){

	LogFile log;
	int32_t fileLen,contentLen,msgStart,msgCount,curPos;
	std::vector<int32_t> msgOffset;
	
	std::ifstream istream(PATHLOG"00000000.log",std::fstream::binary);

	if(istream.is_open()){

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
	
		/*for(int32_t i=0;i<msgCount;i++){
			std::cout<<msgOffset[i]<<'\n';
		};

		return 0;*/

		std::cout<<"File length: "<<fileLen<<", content length: "<<contentLen<<", message start: "<<msgStart<<", message count: "<<msgCount<<'\n';

		// Start going through the actual messages
		log.InitMsgStruct(log.Msg,msgCount);
		for(int32_t i=0;i<msgCount;i++){
			log.ParseMsg(istream,msgStart,msgOffset[i],i,log.Msg);
			std::cout<<i<<" | "<<log.Msg[i].timestamp<<" | "<<log.Msg[i].type<<" | "<<log.Msg[i].separator<< " | "<<log.Msg[i].msg<<'\n';
		};

		istream.close();
	
	}else{
		std::cout<<"File not open"<<std::endl;
	}

	return 0;
};
