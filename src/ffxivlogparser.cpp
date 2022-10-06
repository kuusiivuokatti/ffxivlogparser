#include <filesystem>
#include <iostream>
#include <fstream>

#define PATHLOG "../log/"

int main(){

	std::ifstream istream(PATHLOG"00000000.log",std::fstream::binary);
	
	if(istream.is_open()){
		
		int32_t lenContent,lenFile,offsetMsg,lenMsg;
		//get file and content length
		istream.read(reinterpret_cast<char *>(&lenContent),sizeof(int32_t));
		istream.seekg(4,istream.beg);
		istream.read(reinterpret_cast<char *>(&lenFile),sizeof(int32_t));
		
		//message length starts here
		istream.seekg(8,istream.beg);
		istream.read(reinterpret_cast<char *>(&lenMsg),sizeof(int32_t));
		
		offsetMsg=(lenFile-lenContent)*4+8;
		std::cout<<lenContent<<'\n'<<lenFile<<'\n'<<lenMsg<<'\n'<<offsetMsg<<'\n';

		int32_t timestamp; //most likely a unix timestamp
		istream.seekg(offsetMsg,istream.beg);
		istream.read(reinterpret_cast<char *>(&timestamp),sizeof(int32_t));
		std::cout<<timestamp<<'\n';
		offsetMsg+=4;
	
		int32_t type; //code?
		istream.seekg(offsetMsg,istream.beg);
		istream.read(reinterpret_cast<char *>(&type),sizeof(int32_t));
		std::cout<<type<<'\n';
		offsetMsg+=4;

		offsetMsg+=2; //separator before the message?
		lenMsg-=10;

		istream.seekg(offsetMsg,istream.beg);
		char *msg=new char(lenMsg);
		istream.read(msg,lenMsg);

		std::cout<<msg;

		istream.close();
		delete[] msg;
	
	}else{
		std::cout<<"File not open"<<std::endl;
	}

	return 0;
}
