#include "Save.h"
#include "string.h"

Save::Save() {
	strcpy(this->name, "default");
	creat_time = time(nullptr);
	save_time = creat_time;
}

Save::Save(char* name) {
	strcpy(this->name, name);
	creat_time = time(nullptr);
	save_time = creat_time;
}

char* Save::getCreatTime() const {
	return ctime(&creat_time);
}

char* Save::getSaveTime() const {
	return ctime(&creat_time);
}

const char* Save::getName() const {
	return name;
}

void Save::update() {
	creat_time = time(nullptr);
	//Date = Date;
}
