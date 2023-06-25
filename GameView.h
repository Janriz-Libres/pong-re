#pragma once

#include <SFML/Graphics.hpp>
#include <numeric>

struct AspectRatio
{
	float x, y;
};

class GameView : public sf::View
{
private:
	AspectRatio m_Ratio = {0, 0};
	float m_AR = 0, m_ARInverted = 0;

public:
	GameView() = default;

	GameView(const sf::Vector2u& v_size, const sf::Vector2u& win_size)
	: sf::View(sf::FloatRect(0, 0, v_size.x, v_size.y))
	{
		float gcd = std::gcd(v_size.x, v_size.y);

		m_Ratio = {v_size.x / gcd, v_size.y / gcd};
		m_AR = m_Ratio.x / m_Ratio.y;
		m_ARInverted = m_Ratio.y / m_Ratio.x;

		float init_width = m_AR * win_size.y;
		float width_ratio = init_width / win_size.x;
		float x_pos = (1 - width_ratio) / 2;

		setViewport(sf::FloatRect(x_pos, 0, width_ratio, 1));
	}

	void adjustView(const sf::Event::SizeEvent& size)
	{
		float real_ar = size.width / (float) size.height;

		if (m_AR < real_ar) // If new aspect ratio is greater, then width has increased
		{
			float init_width = m_AR * size.height;
			float width_ratio = init_width / size.width;
			float x_pos = (1 - width_ratio) / 2;

			setViewport(sf::FloatRect(x_pos, 0, width_ratio, 1));
		}
		else
		{
			float init_height = m_ARInverted * size.width;
			float height_ratio = init_height / size.height;
			float y_pos = (1 - height_ratio) / 2;

			setViewport(sf::FloatRect(0, y_pos, 1, height_ratio));
		}
	}
};