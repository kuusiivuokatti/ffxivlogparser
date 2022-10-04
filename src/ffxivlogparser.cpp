#include <filesystem>
#include <iostream>
#include <fstream>

#define PATHLOG "../log/"

int main(){

	std::ifstream istream(PATHLOG"00000000.log",std::fstream::binary);
	
	if(istream.is_open()){
		
		int32_t lenContent,lenFile,offsetMsg,lenMsg;
		istream.read(reinterpret_cast<char *>(&lenContent),sizeof(int32_t));
		istream.seekg(4,istream.beg);
		istream.read(reinterpret_cast<char *>(&lenFile),sizeof(int32_t));
		istream.seekg(8,istream.beg);
		//istream.seekg(12,istream.beg);
		istream.read(reinterpret_cast<char *>(&lenMsg),sizeof(int32_t));
		
		offsetMsg=(lenFile-lenContent)*4;
		std::cout<<lenContent<<'\n'<<lenFile<<'\n'<<lenMsg<<'\n'<<offsetMsg<<'\n';

		istream.seekg(offsetMsg,istream.beg);
		char *buffer=new char(lenMsg);
		istream.read(buffer,lenMsg);
		istream.close();

		for(int i=0;i<lenMsg;i+=1){
			std::cout<<buffer[i];
		}

		delete[] buffer;

		return 0;
	
	}else{
		std::cout<<"File not open"<<std::endl;
	}

	return 0;
}
