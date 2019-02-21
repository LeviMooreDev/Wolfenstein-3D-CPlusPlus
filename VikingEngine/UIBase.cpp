#include "UIBase.h"

int UIBase::nextId = 0;

UIBase::UIBase()
{
	id = nextId;
	UIBase::nextId++;
}

int UIBase::GetId() const
{
	return id;
}