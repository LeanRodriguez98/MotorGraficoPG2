#include "Animation.h"
#include "Time.h"



Animation::Animation(float _cantFrames)
{
	cantFrames = _cantFrames;
	actualFrame = 0;
	frameWidth = 1.0f / cantFrames;
	frame = new float[8];
	frameTimer = 0.2;

	timer = frameTimer;
}


Animation::~Animation()
{
}

float * Animation::UpdateFrame() 
{
	timer += (float)Time::GetDT();

	if (timer>frameTimer)
	{
		frame[0] = 0.0f;
		frame[1] = 0.0f;
		frame[2] = frameWidth;
		frame[3] = 0.0f;
		frame[4] = 0.0f;
		frame[5] = 1.0f;
		frame[6] = frameWidth;
		frame[7] = 1.0f;

		for (int i = 0; i < actualFrame; i++)
		{
			frame[0] += frameWidth;
			frame[2] += frameWidth;
			frame[4] += frameWidth;
			frame[6] += frameWidth;
			
		}

		actualFrame++;
		
		if (actualFrame >= cantFrames)
		{
			actualFrame = 0;
		}
		
		timer = 0;
	}


	return frame;
}
