#include "Time.h"

#include "GLFW\glfw3.h"

double Time::lastTime;
double Time::time;
float Time::dt;
int Time::drawedObjets;

double Time::Measure() 
{
	time = glfwGetTime();
	dt = time - lastTime;
	lastTime = time;
	return  dt;
}
void Time::FirstMeasure() 
{
	lastTime = glfwGetTime();
}

double Time::GetDT() 
{
	return dt;
}



