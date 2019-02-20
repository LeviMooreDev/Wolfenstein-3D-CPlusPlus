#include "Animation.h"
#include "Time.h"

void Animation::Reset()
{
	frame = 0;
	time = Time::GetTimeSinceStart();
	nextTime = Time::GetTimeSinceStart() + waitTime;
}

void Animation::UpdateTime(float deltaTime)
{
	//if the animation is not running, stop here.
	if (!run)
		return;

	//add delta time and check if we need to change frame
	time += deltaTime;
	if (time > nextTime)
	{
		frame++;
		if (frame > frames)
		{
			//if we are looping change frame to 0, else leave it at the last frame
			if (loop)
				frame = 0;
			else
				frame = frames;
		}

		//set next time we need to change frame
		nextTime = Time::GetTimeSinceStart() + waitTime;
	}
}

int Animation::GetIndex()
{
	return frame;
}
