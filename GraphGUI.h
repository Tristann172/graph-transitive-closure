#ifndef GRAPH_GUI_H
#define GRAPH_GUI_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Common.h"

void drawGrid(sf::RenderWindow& window);
void drawMatrix(sf::RenderWindow& window, const sf::Font& font, int matrix[MAX][MAX], 
                int n, float startX, float startY, const std::string& title, float maxWidth);
void drawGraph(sf::RenderWindow& window, const sf::Font& font, int R[MAX][MAX], int n,
               float panelX, float panelY, float panelW, float panelH, float& animTime);
void drawStats(sf::RenderWindow& window, const sf::Font& font, int R[MAX][MAX], int adj[MAX][MAX], int n,
               float x, float y, float w);
void drawLegend(sf::RenderWindow& window, const sf::Font& font, float x, float y, float w);
void drawInstructions(sf::RenderWindow& window, const sf::Font& font);
void runGraphicsApp(const std::string& inputSourceName, int n, int adj[MAX][MAX], int R[MAX][MAX]);

#endif // GRAPH_GUI_H