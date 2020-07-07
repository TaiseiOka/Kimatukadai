#pragma once
#define BUFFSIZE 1024
#define DAYS 366
#define MDAYS 31
#define MONTH 12
#define NUMDATA 3
#define CHARBUFF 124

//ç\ë¢ëÃ
struct dayData {
	const char *day;
	double aveClowdAmo;
	double precipitationAmo;
	double maxTemperature;
	double minTemperature;
	dayData *nextYear;
};



//ä÷êîêÈåæ
void CSVtranceINI(const char *fileName, const char *inifileName);

void weatherForcast(struct dayData *data, double forcastdata[NUMDATA]);
void aveTemperature(struct dayData *data, double forcastdata[NUMDATA]);
void inputData(const char *day, double forcastdata[NUMDATA]);
void outputData(const char *fileName, const char *year, double data[MONTH][NUMDATA]);
void getGurrentDirectory(char *currentDirectory);
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath);
bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath);
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath);
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath);
bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath);
bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath);

