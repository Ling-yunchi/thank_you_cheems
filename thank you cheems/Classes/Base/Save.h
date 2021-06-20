/**
 * ¥Êµµ¿‡
 * @author wr
 */
#pragma once
#include <ctime>
class Save
{
	char name[10];
	time_t creat_time;
	time_t save_time;
	// Data
public:
	Save();
	Save(char* name);
	char* getCreatTime() const;
	char* getSaveTime() const;
	const char* getName() const;
	void update();
};

