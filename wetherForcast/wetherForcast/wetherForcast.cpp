// wetherForcast.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "Setting.h"
#include <string.h>
#include <Windows.h>
#include <curses.h>
int main(int argc, char *argv[])
{
	//CSVtranceINI("2019data.csv", "2019data.ini");
	//CSVtranceINI("2018data.csv", "2018data.ini");
	//CSVtranceINI("2017data.csv", "2017data.ini");

	//curses�̓���
	char *str = "Weather Forcast";

	int inmonth, inday;
	char inDay[CHARBUFF];
	double forcastData[NUMDATA];

	fprintf_s(stdout, "Input month and day\n");
	while (1) {
		fprintf_s(stdout, "month = ");
		scanf_s("%d", &inmonth);
		if (inmonth > 12) {
			fprintf_s(stdout, "ERROR\n");
		}
		else {
			break;
		}
	}
	fprintf_s(stdout, "\n");
	while (1) {
		fprintf_s(stdout, "day = ");
		scanf_s("%d", &inday);
		if (inmonth == 2 && inday >28) {
			fprintf_s(stdout, "ERROR\n");
		}
		else if((inmonth == 4 || inmonth == 6 || inmonth == 9 || inmonth == 11) && inday > 30) {
			fprintf_s(stdout, "ERROR");
		}
		else {
			break;
		}
	}
	fprintf_s(stdout, "\n");

	sprintf_s(inDay, "%d/%d", inmonth, inday);

	inputData(inDay, forcastData);


	// ������
	if (initscr() == NULL) {
		return 1;
	}

	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);	// �F1 �͍��n�ɗΕ���
	init_pair(2, COLOR_WHITE, COLOR_RED);	// �F2 �͐Ԓn�ɔ�����
	init_pair(3, COLOR_RED, COLOR_BLACK);	// �F3 �͍��n�ɐԕ���
	init_pair(4, COLOR_BLACK, COLOR_RED);	// �F4 �͐Ԓn�ɍ�����
	init_pair(5, COLOR_BLACK, COLOR_CYAN);	// �F5 �̓V�A���n�ɍ�����
	init_pair(6, COLOR_BLACK, COLOR_BLUE);	// �F6 �͐n�ɍ�����
	init_pair(7, COLOR_BLACK, COLOR_WHITE);	// �F7 �͔��n�ɍ�����
	init_pair(8, COLOR_BLUE, COLOR_BLACK);	// �F8 �͍��n�ɐ���
	init_pair(9, COLOR_WHITE, COLOR_BLACK);	// �F9 �͍��n�ɔ�����
	init_pair(10, COLOR_WHITE, COLOR_BLUE);	// �F10 �͐n�ɔ�����
	init_pair(11, COLOR_BLUE, COLOR_BLACK);	// �F11 �͍��n�ɐ���
	init_pair(12, COLOR_YELLOW, COLOR_BLACK);// �F12 �͍��n�ɉ�����

	
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	int key;
	int month,day;


	int screenNum = 0;

	while (true) {
		
		switch (screenNum)
		{
		case 0:
			// ��ʂ��N���A
			erase();
			// �������

			attrset(COLOR_PAIR(4));
			mvprintw(8, 47, "PREASE INPUT SAME DAY ");
			attrset(COLOR_PAIR(3));
			mvprintw(9, 49, "YOUR INPUT = %d/%d", inmonth,inday);

			attrset(COLOR_PAIR(1));
			mvprintw(4, 51, "%s", str);
			attrset(COLOR_PAIR(2));
			mvaddstr(11, 48, "Month");
			mvaddstr(11, 61, "Day");

			attrset(COLOR_PAIR(12));
			mvprintw(15, 49, "RETURN KEY = LEFT");
			attrset(COLOR_PAIR(12));
			mvprintw(16, 49, "DECIDED KEY = E");


			// ��ʂ��X�V
			refresh();

			key = getch();
			if (key == '1' || key == '2' || key == '3'|| key == '4'|| key == '5'|| key == '6'|| key == '7'|| key == '8' || key == '9' ) {
				attrset(COLOR_PAIR(3));
				month = 0;
				month = key - 48;
				mvprintw(11, 56, "%d", month);

				// ��ʂ��X�V
				refresh();

				while (1) {
					key = getch();
					if (month == 1 && (key == '0' || key == '1' || key == '2')) {
						month = (month * 10) + (key - 48);
						mvprintw(11, 55, "%d", month);
					}
					if (key == KEY_RIGHT) {
						screenNum = 1;
						break;
					}
					else if (key == KEY_LEFT) {
						screenNum = 0;
						break;
					}
				}
			}

			break;
		case 1:
			key = getch();
			day = 0;

			if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') {
				attrset(COLOR_PAIR(3));
				day = key - 48;
				mvprintw(11, 67, "%d", day);
				// ��ʂ��X�V
				refresh();
				while (1) {
					key = getch();
					if ((day == 1 || day == 2 || day == 3) && (key == 0 || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9')) {
						day = (day * 10) + (key - 48);
						mvprintw(11, 67, "%d", day);
					}
					if(key == KEY_LEFT) {
						screenNum = 0;
						break;
					}
					else if (key == 'e') {
						if (inmonth != month || inday != day) {
							attrset(COLOR_PAIR(4));
							mvprintw(13, 51, "Input Day Error");
						}
						else {
							screenNum = 2;
							break;
						}
					}
				}
			}
			break;
		case 2:
			
			// ��ʂ��N���A
			erase();			//���ʏo�͉��			attrset(COLOR_PAIR(12));
			mvaddstr(9, 50, "Forcast Result");			//���͂��ꂽ������V�C��\��			

			attrset(COLOR_PAIR(12));
			mvaddstr(7, 56, inDay);

			//�\�����o��
			if (forcastData[0] == 1 && forcastData[2] < 3) {
				attrset(COLOR_PAIR(5));
				mvaddstr(11, 55, "Snowy");
			}
			else if (forcastData[0] == 1) {
				attrset(COLOR_PAIR(6));
				mvaddstr(11, 55, "Rainy");
			}
			else if (forcastData[0] == 2) {
				attrset(COLOR_PAIR(7));
				mvaddstr(11, 54, "Cloudy");
			}
			else {
				attrset(COLOR_PAIR(4));
				mvaddstr(11, 55, "Suny");
			}

			attrset(COLOR_PAIR(9));
			mvaddstr(15, 1, "MaxTemperature");
			mvaddstr(17, 1, "MinTemperature");
			for (int i = 0; i < 6; i++) {
				attrset(COLOR_PAIR(9));
				mvaddstr(14 + i, 17, "|");
			}

			attrset(COLOR_PAIR(2));
			mvprintw(15, 20, "%lf", forcastData[1]);

			attrset(COLOR_PAIR(10));
			mvprintw(17, 20, "%lf", forcastData[2]);
			
			
			while (1) {
				key = getch();
				if (key == KEY_LEFT) {
					screenNum = 0;
					break;
				}
				else if (key == 'e') {
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	

	while (1) {
			napms(1000);
	}
	
	
}

//CSV�t�@�C����ini�t�@�C���ɕϊ�
void CSVtranceINI(const char *fileName, const char *inifileName) {
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, fileName, "r");

	int i, k, cnt = 0;
	double temp, itemp;
	char days[BUFFSIZE], month_day[BUFFSIZE];
	char delim[] = ", /";//�f���~�^
	char *p1, *ctx, *year, *month, *day;

	i = 0;
	if (error != 0)
		fprintf_s(stderr, "failed toopen");
	else {
		for (k = 0; k < 6; k++) {
			fgets(days, BUFFSIZE, fp);
		}
		while (fgets(days, BUFFSIZE, fp) != NULL) {

			year = strtok_s(days, delim, &ctx);//20XX
			month = strtok_s(NULL, delim, &ctx);//X��
			day = strtok_s(NULL, delim, &ctx);//X��
			sprintf_s(month_day, "%s/%s", month, day);//X��X���̕�����ɂ���
			p1 = strtok_s(NULL, delim, &ctx);//���ω_��
			temp = atof(p1);
			writeDouble("AverageCloudAmount", month_day, temp, inifileName);
			p1 = strtok_s(NULL, delim, &ctx);
			p1 = strtok_s(NULL, delim, &ctx);
			p1 = strtok_s(NULL, delim, &ctx);//�~����
			temp = atof(p1);
			writeDouble("PrecipitationAmount", month_day, temp, inifileName);
			p1 = strtok_s(NULL, delim, &ctx);
			p1 = strtok_s(NULL, delim, &ctx);
			p1 = strtok_s(NULL, delim, &ctx);
			p1 = strtok_s(NULL, delim, &ctx);//�ō��C��
			temp = atof(p1);
			writeDouble("MaxTemperature", month_day, temp, inifileName);
			p1 = strtok_s(NULL, delim, &ctx);
			p1 = strtok_s(NULL, delim, &ctx);
			p1 = strtok_s(NULL, delim, &ctx);//�Œ�C��
			temp = atof(p1);
			writeDouble("MinTemperature", month_day, temp, inifileName);


		}
		fclose(fp);
	}
}

void weatherForcast(struct dayData *data, double forcastdata[NUMDATA]) {
	int cntRain = 0;
	int cntCloudy = 0;
	int cntSun = 0;
	while (data != NULL) {
		if (data->precipitationAmo > 0.1) {
			cntRain++;
		}
		else if(data->aveClowdAmo > 8 && data->precipitationAmo == 0) {
			cntCloudy++;
		}
		else {
			cntSun++;
		}
		data = data->nextYear;
	}

	fprintf_s(stdout, "sun = %d  rain = %d cloudy = %d\n", cntSun, cntRain, cntCloudy);

	if (cntRain >= cntSun && cntRain >= cntCloudy) {
		forcastdata[0] = 1;//�J
	}
	else if (cntSun > cntRain && cntSun >= cntCloudy) {
		forcastdata[0] = 3;//����
	}
	else {
		forcastdata[0] = 2;//�܂�
	}


}
//�C���̕��ς��o��
void aveTemperature(struct dayData *data , double forcastdata[NUMDATA]) {
	double tmpMax = 0;
	double tmpMin = 0;
	double aveMax, aveMin;
	int cnt = 0;

	while (data != NULL) {
		tmpMax = tmpMax + data->maxTemperature;
		tmpMin = tmpMin + data->minTemperature;
		cnt++;
		data = data->nextYear;
	}
	aveMax = tmpMax / cnt;
	aveMin = tmpMin / cnt;

	forcastdata[1] = aveMax;
	forcastdata[2] = aveMin;

}
//�f�[�^���\���̂ɓ����B
void inputData(const char *day, double forcastdata[NUMDATA]) {
	
	char fileName[CHARBUFF];

	dayData *previousDay = NULL;
	dayData *firstYear = NULL;//�\���̂̓�

	for (int i = 0; i < 3; i++) {
		dayData *tmp = new dayData();
		tmp->day = day;
		sprintf_s(fileName, "201%ddata.ini", 9 - i);
		tmp->aveClowdAmo = readDouble("AverageCloudAmount", day, -1, fileName);
		tmp->precipitationAmo = readDouble("PrecipitationAmount", day, -1, fileName);
		tmp->maxTemperature = readDouble("MaxTemperature", day, 0, fileName);
		tmp->minTemperature = readDouble("MinTemperature", day, 0, fileName);
		tmp->nextYear = NULL;
		if (i == 0) {
			firstYear = tmp;
		}
		else {
			previousDay->nextYear = tmp;
		}
		previousDay = tmp;
	}
	previousDay = firstYear;

	weatherForcast(previousDay, forcastdata);
	aveTemperature(previousDay, forcastdata);
	

}
//�t�@�C�����o��
void getGurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char readsection[CHARBUFF];
	sprintf_s(readsection, section);
	char readkeyWord[CHARBUFF];
	sprintf_s(readkeyWord, keyword);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, filePath);

	return GetPrivateProfileInt(readsection, readkeyWord, defaultValue, settingFile);
}
bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath) {
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char readsection[CHARBUFF];
	sprintf_s(readsection, section);
	char readkeyWord[CHARBUFF];
	sprintf_s(readkeyWord, keyword);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, filePath);

	if (GetPrivateProfileString(readsection, readkeyWord, defaultValue, returnValue, CHARBUFF, settingFile) != 0) {
		return returnValue;
	}
	else {
		return false;
	}

}
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath) {
	char *endptr;
	double returnNum;
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char readsection[CHARBUFF];
	sprintf_s(readsection, section);
	char readkeyWord[CHARBUFF];
	sprintf_s(readkeyWord, keyword);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, filePath);
	char returnValue[CHARBUFF];

	if (GetPrivateProfileString(readsection, readkeyWord, "none", returnValue, CHARBUFF, settingFile) != 0) {
		returnNum = strtod(returnValue, &endptr);
		return returnNum;
	}
	else {
		return defaultValue;
	}
}
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath) {
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char readsection[CHARBUFF];
	sprintf_s(readsection, section);
	char readkeyWord[CHARBUFF];
	sprintf_s(readkeyWord, keyword);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, filePath);

	return WritePrivateProfileString(readsection, readkeyWord, returnValue, settingFile);
}
bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath) {
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char readsection[CHARBUFF];
	sprintf_s(readsection, section);
	char readkeyWord[CHARBUFF];
	sprintf_s(readkeyWord, keyword);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, filePath);
	char returnValueI[CHARBUFF];
	sprintf_s(returnValueI, "%d", returnValue);

	return WritePrivateProfileString(readsection, readkeyWord, returnValueI, settingFile);
}
bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath) {
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char readsection[CHARBUFF];
	sprintf_s(readsection, section);
	char readkeyWord[CHARBUFF];
	sprintf_s(readkeyWord, keyword);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, filePath);
	char returnValued[CHARBUFF];
	sprintf_s(returnValued, "%lf", returnValue);

	return WritePrivateProfileString(readsection, readkeyWord, returnValued, settingFile);
}