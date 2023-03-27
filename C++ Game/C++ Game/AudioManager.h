#pragma once
#include <windows.h>

class AudioManager 
{
	private:
		static AudioManager* s_pInstance;

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
		void PlayDoorClosedSound() const
		{
			Beep(500, 75);
			Beep(500, 75);
		}

		void PlayDoorOpenSound() const 
		{
			Beep(1397, 200);
		}

		void PlayKeyPickupSound() const
		{
			Beep(1568, 200);
		}

		void PlayMoneySound() const
		{
			Beep(1568, 50);
		}

		void PlayLoseLifeSound() const
		{
			Beep(200, 100);
		}

		void PlayLoseSound() const
		{
			Beep(500, 75);
			Beep(500, 75);
			Beep(500, 75);
			Beep(500, 75);
		}

		void PlayWinSound() const
		{
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