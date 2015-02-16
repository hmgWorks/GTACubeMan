#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	DWORD m_dwLastUpdateTime;
	DWORD m_dwDeltaTime;
	DWORD m_dwAccTime;
	DWORD m_dwFPS;
	DWORD m_dwFrameCount;
	SINGLETONE(cTimeManager);
	
public:
	void Update();
	float GetDeltaTime()
	{
		return m_dwDeltaTime / 1000.f;
	}
	DWORD GetFPS()
	{
		return m_dwFPS;
	}
};

