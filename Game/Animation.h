#pragma once

//useful for keeping track of what animation frame to show
class Animation
{
private:
	//current frame
	int frame;
	//next time to change frame
	float nextTime;
	//the time Animation thinks it is
	float time;

public:
	//the amount of frames the animation have
	int frames;
	//true if the animation is looping
	bool loop = true;
	//wait time between frames
	float waitTime;
	//true if the animation is running
	float run = true;

	//reset the animation
	void Reset();

	//update the time used to change frames
	//time: second since last UpdateTime() call.
	void UpdateTime(float time);

	//returns the current frame
	int GetIndex();
};

