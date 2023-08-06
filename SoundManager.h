#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <array>
#include <unordered_map>

class SoundManager
{
public:
	static void play(const std::string&);

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

private:
	static const std::size_t kSoundNum = 4;

	SoundManager();

	static SoundManager m_Sounder;

	std::array<sf::SoundBuffer, kSoundNum> m_SoundBuffers;
	std::unordered_map<std::string, sf::Sound> m_SoundMap;
};

