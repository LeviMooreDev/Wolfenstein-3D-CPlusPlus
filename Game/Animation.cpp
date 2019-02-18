#include "Animation.h"
#include "Time.h"


Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::Reset()
{
	index = 0;
	time = Time::GetTimeSinceStart();
	nextTime = Time::GetTimeSinceStart() + waitTime;
}

void Animation::UpdateTime(float deltaTime)
{
	time += deltaTime;
	if (time > nextTime)
	{
		index++;
		if (index > maxIndex)
		{
			if (loop)
				index = 0;
			else
				index = maxIndex;
		}
		nextTime = Time::GetTimeSinceStart() + waitTime;
	}
}

int Animation::GetIndex()
{
	return index;
}
