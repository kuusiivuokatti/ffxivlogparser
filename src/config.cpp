#include <iostream>
#include <filesystem>
#include <map>
#include <fstream>
#include <string>

#include "../include/config.h"

//extern std::map<int,std::string>TypeMap;
std::map<int,std::string>TypeMap;

bool Config::ReadConfigFile(){

	int confFileCount=1;
	std::string confFileCollection[confFileCount];
	confFileCollection[0]="type.map";

	std::cout<<"Checking if config files exist\n";

	for(int i=0;i<confFileCount;i++){
		if(std::filesystem::exists(_confDir+confFileCollection[i])){
			std::cout<<confFileCollection[i]<<" found"<<'\n';
		}else{
			std::cout<<confFileCollection[i]<<" not found"<<'\n';
			return false;
		};
	};

	// TODO : Make this more dynamic if more config files are needed
	try{
		std::ifstream istream(_confDir+confFileCollection[0]);
		istream.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		std::string line,key,value;
		while(std::getline(istream,line)){
			try{
				key=line.substr(0,line.find(';'));
				value=line.substr(line.find(';')+1);
				TypeMap.insert(std::pair<int,std::string>(std::stoi(key),value)); // TODO : Considering changing away from stoi
			}catch(const char* errMsg){
				std::cerr<<"Error parsing config file "<<confFileCollection[0]<<" ("<<errMsg<<")"<<'\n';
			};
		};
		istream.close();
	}catch(const char* errMsg){
		std::cerr<<"Error reading config file "<<confFileCollection[0]<<" ("<<errMsg<<")"<<'\n';
		return false;
	};

	return true;

};

std::string Config::MapType(int type){
	
	std::string value;
	value=TypeMap[type];
	if(value.empty()){
		value=std::to_string(type);
	};
	return value;

};
