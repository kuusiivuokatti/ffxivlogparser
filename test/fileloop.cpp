#include <iostream>
#include <filesystem>

int main(){

	std::error_code errCode;
	bool canExit=false;
	std::string logDir;

	do{
		std::cout<<"Enter log file path (q to exit)\n";
		std::cin>>logDir;
	
		if(std::filesystem::is_directory(logDir,errCode)){
			std::cout<<"Directory set to: "<<logDir<<'\n';
			for(const std::filesystem::directory_entry& logFile:std::filesystem::directory_iterator(logDir)){
				std::cout<<"Opening file: "<<logFile.path()<<'\n';
			};
		}else if(logDir=="q"){
			std::cout<<"Exiting\n";
			canExit=true;
		}else{
			std::cerr<<"Error while reading directory: "<<errCode.message()<<'\n';
		};
	}while(canExit==false);

	return 0;

};
