#ifndef CONFIG_H
#define CONFIG_H

class Config{

private:
const std::string _confDir="../config/";

public:
bool ReadConfigFile();
std::string MapType(int type);

};

#endif
