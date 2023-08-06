#include "SoundManager.h"

SoundManager SoundManager::m_Sounder;

SoundManager::SoundManager()
{
	std::array<std::string, kSoundNum> filenames = {
		"audio/beep.wav", "audio/boop.wav", "audio/confirmbeep.wav", "audio/fire.wav"
	};

	for (std::size_t i = 0; i < m_SoundBuffers.size(); i++)
	{
		m_SoundBuffers[i].loadFromFile(filenames[i]);
		m_SoundMap[filenames[i]].setBuffer(m_SoundBuffers[i]);
	}
}

void SoundManager::play(const std::string& filename)
{
	m_Sounder.m_SoundMap[filename].play();
}

