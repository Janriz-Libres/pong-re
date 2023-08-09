#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "Paddle.h"

class Hud
{
public:
	Hud();
	
	Hud(const std::string&);

	void update(const sf::Time&);

	void render(sf::RenderWindow&);

	void incrementScore(const Paddle::Side&);

	void resetScores();

	void changeMode();

	bool isLoaded();

private:
	static const unsigned int SCORE_SIZE = 200;
	static constexpr float OFFSET = 400;
	static constexpr float TOP_MARGIN = 100;

	static constexpr float T_SCORE = 1;
	static const unsigned int MAX_SCORE = 5;

	void initializeText(sf::Text&, const std::string&, unsigned int, float, float = 0);

	sf::Font m_Font;

	sf::Text m_Title, m_Subtitle, m_Mode, m_Changer;
	sf::Text m_LeftScore, m_RightScore, m_Paused;
	sf::Text m_GameOver, m_Repeat, m_Exit;

	float m_ScoreTimer = T_SCORE;
	bool m_IsLoaded = true;
};

