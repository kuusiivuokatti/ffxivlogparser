#include <iostream>
#include <sstream>
#include <iomanip>

int main(){

	time_t timestamp=1562306887;
	tm* ltm=localtime(&timestamp);
	std::string testString;
	std::stringstream testStringStream;
	testStringStream<<1900+ltm->tm_year<<'-'
		<<std::setfill('0')<<std::setw(2)<<1+ltm->tm_mon<<'-'
		<<std::setfill('0')<<std::setw(2)<<ltm->tm_mday<<'|'
		<<std::setfill('0')<<std::setw(2)<<ltm->tm_hour<<':'
		<<std::setfill('0')<<std::setw(2)<<ltm->tm_min<<':'
		<<std::setfill('0')<<std::setw(2)<<ltm->tm_sec;


	testStringStream>>testString;
	std::cout<<testString;

	return 0;

};
