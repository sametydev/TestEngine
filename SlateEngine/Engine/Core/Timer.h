#pragma once
#include <chrono>
#include <SlateEngine/Engine/Utils.h>

class ENGINE_API Timer
{
public:
	Timer();
	float deltaTime() const; 
	void OnReset(); 
	void OnTick();

	float fps;

	static Timer* Instance;
private:
	float m_deltaTime;
	std::chrono::system_clock::time_point m_prevTime;
	std::chrono::system_clock::time_point m_currentTime;
	std::chrono::duration<double> m_elapsedSecond;
	bool bIsActive;
	int frameCount = 0;
	float totalTime = 0;
};
