#ifndef LOGFILE_H
#define LOGFILE_H

class LogFile{

private:
int32_t _intVal;

struct _Message{
	int32_t timestamp;
	int32_t type;
	char* separator; // TODO : This needs more testing on what it represents
	char* msg;
};

public:
std::vector<_Message> Msg;

int32_t ParseInt(std::ifstream& istream,int32_t seekPos);
char* ParseChar(std::ifstream& istream,int32_t seekPos,int32_t len);
void InitMsgStruct(std::vector<_Message>& msg,int32_t count);
void ParseMsg(std::ifstream& istream,int32_t msgStart,int32_t seekPos,int32_t index,std::vector<_Message>& msg);

};

#endif
