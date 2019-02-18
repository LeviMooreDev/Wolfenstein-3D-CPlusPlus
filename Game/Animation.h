#pragma once
class Animation
{
private:
	int index;
	float nextTime;
	float time;

public:
	Animation();
	~Animation();

	int maxIndex;
	bool loop = true;
	float waitTime;

	void Reset();
	void UpdateTime(float time);
	int GetIndex();
};

