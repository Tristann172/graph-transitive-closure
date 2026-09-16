#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.hpp>

#define MAX 20
const float NODE_RADIUS = 28.f;

// Bảng màu hệ thống (Dark Theme & Neon Glow)
const sf::Color COLOR_BG = sf::Color(10, 14, 20);
const sf::Color COLOR_HEADER = sf::Color(18, 24, 34);
const sf::Color COLOR_PANEL = sf::Color(15, 20, 28);
const sf::Color COLOR_BORDER = sf::Color(45, 60, 85);
const sf::Color COLOR_CELL_0 = sf::Color(20, 25, 35);
const sf::Color COLOR_CELL_1 = sf::Color(0, 220, 120, 180);
const sf::Color COLOR_NODE = sf::Color(255, 200, 0, 210);
const sf::Color COLOR_NODE_OUT = sf::Color(255, 255, 255, 90);
const sf::Color COLOR_NODE_TEXT = sf::Color::Black;
const sf::Color COLOR_LINE = sf::Color(0, 255, 255, 220);
const sf::Color COLOR_TEXT_PRIMARY = sf::Color::White;
const sf::Color COLOR_TEXT_SECONDARY = sf::Color(140, 160, 190);
const sf::Color COLOR_ACCENT = sf::Color(0, 255, 200);

struct Dinh {
    sf::Vector2f pos;
};

#endif // COMMON_H