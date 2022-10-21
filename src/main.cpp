#include <iostream>
#include <vector>
#include <filesystem>

#include "../include/main.h"

int main(){

	File log;

	std::error_code errCode;
	bool canExit=false;
	std::string inDir;

	do{
		std::cout<<"Enter log file path (q to exit)\n";
		std::cin>>inDir;
	
		if(std::filesystem::is_directory(inDir,errCode)){
			std::cout<<"Directory set to: "<<inDir<<'\n';
			for(const std::filesystem::directory_entry& inFile:std::filesystem::directory_iterator(inDir)){
				if(log.CheckLogFileValidity(inFile)){
					if(log.OpenLogFile(inFile)){
						std::cout<<"File "<<inFile.path()<<" read succesfully\n";
					};
				}else{
					std::cout<<inFile.path()<<" is not a valid log file, ignoring\n";
				};
			};
			if(log.Msg.size()>0){
				std::cout<<"Saving log output to file\n";
				if(log.StoreFile(log.Msg)){
					std::cout<<"File saved succesfully\n";
				};
			}else{
				std::cout<<"No log files read\n";
			};

			log.Msg.clear();

		}else if(inDir=="q"){
			std::cout<<"Exiting\n";
			canExit=true;
		}else{
			std::cerr<<"Error while reading directory: "<<errCode.message()<<'\n';
		};
	}while(canExit==false);

	return 0;

};
