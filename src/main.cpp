#include <iostream>
#include <vector>
#include <filesystem>

#include "../include/main.h"

bool CheckConfig(){

	bool returnValue=true;

	int confFileCount=1;
	std::string confDir="../config/"; // TODO : Consider making more easily maintainable
	std::string confCollection[confFileCount];

	confCollection[0]="type.map";

	std::cout<<"Checking if config files exist\n";

	for(int i=0;i<confFileCount;i++){
		if(std::filesystem::exists(confDir+confCollection[i])){
			std::cout<<confCollection[i]<<" found"<<'\n';
		}else{
			std::cout<<confCollection[i]<<" not found"<<'\n';
			returnValue=false;
		};
	};

	return returnValue;

};

int main(){

	File log;

	std::error_code errCode;
	bool canExit=false;
	std::string inDir;

	if(!CheckConfig()){
		std::cout<<"Error when trying to look for config files, exiting\n";
		return -1;
	}else{
		std::cout<<"Config files found\n";
	};

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
