#include "Save.h"
#include "cstring"

Save::Save() {
	strcpy(this->name, "default");
	create_time = time(nullptr);
	save_time = create_time;
}

Save::Save(char* name) {
	strcpy(this->name, name);
	create_time = time(nullptr);
	save_time = create_time;
}

char* Save::getCreateTime() const {
	return ctime(&create_time);
}

char* Save::getSaveTime() const {
	return ctime(&save_time);
}

const char* Save::getName() const {
	return name;
}

void Save::update() {
	save_time = time(nullptr);
	//Date = Date;
}
