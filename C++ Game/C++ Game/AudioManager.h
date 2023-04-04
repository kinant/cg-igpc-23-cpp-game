#pragma once
#include <windows.h>

class AudioManager 
{
	private:
		static AudioManager* s_pInstance;

		bool m_bIsSoundOn = true;

		AudioManager() 
		{
	
		}

	public:
		static AudioManager* GetInstance() 
		{
			if (s_pInstance == nullptr) 
			{
				s_pInstance = new AudioManager;
			}

			return s_pInstance;
		}

		static void DestroyInstance() 
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		void ToggleSound() 
		{
			m_bIsSoundOn = !m_bIsSoundOn;
		}

		bool IsSoundOn() 
		{
			return m_bIsSoundOn;
		}

		void PlayDoorClosedSound() const
		{
			if (!m_bIsSoundOn) return;

			Beep(500, 75);
			Beep(500, 75);
		}

		void PlayDoorOpenSound() const 
		{
			if (!m_bIsSoundOn) return;

			Beep(1397, 200);
		}

		void PlayKeyPickupSound() const
		{
			if (!m_bIsSoundOn) return;

			Beep(1568, 200);
		}

		void PlayMoneySound() const
		{
			if (!m_bIsSoundOn) return;

			Beep(1568, 50);
		}

		void PlayLoseLifeSound() const
		{
			if (!m_bIsSoundOn) return;

			Beep(200, 100);
		}

		void PlayLoseSound() const
		{
			if (!m_bIsSoundOn) return;

			Beep(500, 75);
			Beep(500, 75);
			Beep(500, 75);
			Beep(500, 75);
		}

		void PlayWinSound() const
		{
			if (!m_bIsSoundOn) return;

			Beep(1568, 200);
			Beep(1568, 200);
			Beep(1568, 200);
			Beep(1245, 1000);
			Beep(1397, 200);
			Beep(1397, 200);
			Beep(1397, 200);
			Beep(1175, 1000);
		}
};