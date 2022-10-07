#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

#define PATHLOG "../log/"

class LogFile{

	private:
	int32_t _intVal;

	struct Message{
		int32_t timestamp;
		int32_t type;
		char* separator; // This needs more testing on what it represents
		char* msg;
	};

	public:
	std::vector<Message> Msg;
	
	int32_t ParseInt(std::ifstream& istream,int32_t seekPos){
	// Parse message information that can be cast as int
		istream.seekg(seekPos,istream.beg);
		istream.read(reinterpret_cast<char *>(&_intVal),sizeof(int32_t));
		return _intVal;
	};

	char* ParseChar(std::ifstream& istream,int32_t seekPos,int32_t len){
	// Parse message information that can be cast as char
		char* charVal=new char[len];
		istream.seekg(seekPos,istream.beg);
		istream.read(charVal,len);
		return charVal;
	};

	void InitMsgStruct(std::vector<Message>& msg,int32_t count){
		msg.clear();
		msg.push_back(Message());
		msg.reserve(count);
	};

	void ParseMsg(std::ifstream& istream,int32_t msgStart,int32_t seekPos,int32_t index,std::vector<Message>& msg){
	// Parse raw message contents
		msg[index].timestamp=ParseInt(istream,msgStart+seekPos);
		seekPos+=4;
		msg[index].type=ParseInt(istream,msgStart+seekPos);
		seekPos+=4;
		msg[index].separator=ParseChar(istream,msgStart+seekPos,2);
		seekPos+=2;
		msg[index].msg=ParseChar(istream,msgStart+seekPos,seekPos-10);
	};

};

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
		
		std::cout<<"File length: "<<fileLen<<", content length: "<<contentLen<<", message start: "<<msgStart<<", message count: "<<msgCount<<'\n';

		// Start going through the actual messages
		log.InitMsgStruct(log.Msg,msgCount);
		for(int32_t i=0;i<msgCount;i++){
			log.ParseMsg(istream,msgStart,msgOffset[i],i,log.Msg);
			std::cout<<log.Msg[i].timestamp<<" | "<<log.Msg[i].type<<" | "<<log.Msg[i].separator<< " | "<<log.Msg[i].msg<<'\n';
		};

		istream.close();
	
	}else{
		std::cout<<"File not open"<<std::endl;
	}

	return 0;
};
