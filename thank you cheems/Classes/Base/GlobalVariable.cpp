#include "GlobalVariable.h"

Global* Global::instance_ = nullptr;

Global* Global::getInstance()
{
	if (instance_ == nullptr)
		instance_ = new Global();
	return instance_;
}

Global::Global()
	:userInfo_(new UserInformation()), displayStats(true)
{
}

Global::~Global()
{
	delete instance_;
	delete userInfo_;
}
