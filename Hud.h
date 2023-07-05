#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

#include "Paddle.h"
#include "Constants.h"

class Hud
{
public:
	enum Mode { SINGLE, DOUBLE };
	Mode mode = SINGLE;
	
private:
	static const unsigned int SCORE_SIZE = 200;
	static constexpr float OFFSET = 400;
	static constexpr float TOP_MARGIN = 100;

	static constexpr float T_SCORE = 1;
	static const unsigned int MAX_SCORE = 1;

	sf::Font m_Font;

	sf::Text m_Title, m_Subtitle, m_Mode, m_Changer;
	sf::Text m_LeftScore, m_RightScore, m_Paused;
	sf::Text m_GameOver, m_Repeat, m_Exit;

	float m_ScoreTimer = T_SCORE;
	bool m_IsLoaded = true;

public:
	Hud()
	{
		m_LeftScore.setString("0");
		m_RightScore.setString("0");
	}
	
	Hud(const std::string& fontname)
	{
		if (!m_Font.loadFromFile(fontname))
		{
			m_IsLoaded = false;
			return;
		}

		initializeText(m_Title, "Pong", 175, 500);
		initializeText(m_Subtitle, "Press ENTER to play", 75, 950);
		initializeText(m_Mode, "1 Player Mode", 75, 1300);
		initializeText(m_Changer, "Press SPACE to change mode", 60, 1450);

		initializeText(m_LeftScore, "0", SCORE_SIZE, TOP_MARGIN, -OFFSET);
		initializeText(m_RightScore, "0", SCORE_SIZE, TOP_MARGIN, OFFSET);
		initializeText(m_Paused, "PAUSED", 250, -1);

		initializeText(m_GameOver, "", 140, 800);
		initializeText(m_Repeat, "Press ENTER to play again", 60, 1250);
		initializeText(m_Exit, "Press ESCAPE to go to main menu", 60, 1400);
	}

	void update(const sf::Time& dt)
	{
		if (state == SCORED)
		{
			m_ScoreTimer -= dt.asSeconds();

			if (m_ScoreTimer <= 0)
			{
				m_ScoreTimer = T_SCORE;
				state = PLAY;
			}
		}
	}

	void render(sf::RenderWindow& window)
	{
		if (state == MENU)
		{
			window.draw(m_Title);
			window.draw(m_Subtitle);
			window.draw(m_Mode);
			window.draw(m_Changer);
		}
		else if (state == PAUSED) window.draw(m_Paused);
		else if (state == GAME_OVER)
		{
			window.draw(m_GameOver);
			window.draw(m_Repeat);
			window.draw(m_Exit);
		}

		if (state != MENU)
		{
			window.draw(m_LeftScore);
			window.draw(m_RightScore);
		}
	}

	void incrementScore(const Paddle::Side& scorer)
	{
		sf::Text& score_label = scorer == Paddle::Side::LEFT ? m_LeftScore : m_RightScore;
		std::string s_score = score_label.getString();
		int score = std::stoi(s_score);
		score_label.setString(std::to_string(++score));

		if (score >= MAX_SCORE)
		{
			state = GAME_OVER;
			m_GameOver.setString(scorer == Paddle::Side::LEFT ? "Player 1 Wins!" : "Player 2 Wins!");
			m_GameOver.setPosition(
				VIRTUAL_SIZE.x / 2 - m_GameOver.getLocalBounds().width / 2,
				m_GameOver.getPosition().y
			);
		}
		else state = SCORED;
	}

	void resetScores()
	{
		m_LeftScore.setString("0");
		m_RightScore.setString("0");
	}

	void changeMode()
	{
		if (mode == SINGLE)
		{
			mode = DOUBLE;
			m_Mode.setString("2 Player Mode");
		}
		else
		{
			mode = SINGLE;
			m_Mode.setString("1 Player Mode");
		}
	}

	bool isLoaded()
	{
		return m_IsLoaded;
	}

private:
	void initializeText(sf::Text& text, const std::string& string, unsigned int font_size, float y,
		float offset = 0)
	{
		text.setString(string);
		text.setFont(m_Font);
		text.setCharacterSize(font_size);

		sf::Vector2f pos;
		pos.x = VIRTUAL_SIZE.x / 2 - text.getLocalBounds().width / 2 + offset;
		pos.y = y == -1 ? VIRTUAL_SIZE.y / 2 - text.getLocalBounds().height / 2 : y;
		text.setPosition(pos);
	}
};

