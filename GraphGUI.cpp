#include "GraphGUI.h"
#include "WarshallLogic.h"
#include <iostream>
#include <cmath>
#include <optional>

void drawGrid(sf::RenderWindow& window) {
    sf::Color gridColor(255, 255, 255, 8);
    for (float i = 0; i < 1600.f; i += 30.f) {
        sf::Vertex line[] = {{{i, 0.f}, gridColor}, {{i, 950.f}, gridColor}};
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
    for (float i = 0; i < 950.f; i += 30.f) {
        sf::Vertex line[] = {{{0.f, i}, gridColor}, {{1600.f, i}, gridColor}};
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void drawMatrix(sf::RenderWindow& window, const sf::Font& font, int matrix[MAX][MAX], 
                int n, float startX, float startY, const std::string& title, float maxWidth) {
    float cellSize = maxWidth / (n + 0.5f);
    if (cellSize > 50.f) cellSize = 50.f;
    
    float titleH = 35.f;
    float pad = 12.f;
    
    sf::RectangleShape bg(sf::Vector2f(cellSize * n + pad * 2, cellSize * n + titleH + pad * 2));
    bg.setFillColor(COLOR_PANEL);
    bg.setOutlineThickness(1.5f);
    bg.setOutlineColor(COLOR_BORDER);
    bg.setPosition({startX, startY});
    window.draw(bg);
    
    sf::Text titleText(font);
    titleText.setString(title);
    titleText.setCharacterSize(15);
    titleText.setFillColor(COLOR_ACCENT);
    titleText.setPosition({startX + pad + 2.f, startY + pad});
    window.draw(titleText);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float x = startX + pad + j * cellSize;
            float y = startY + titleH + pad + i * cellSize;
            
            sf::RectangleShape cell(sf::Vector2f(cellSize - 2.f, cellSize - 2.f));
            cell.setFillColor(matrix[i][j] == 1 ? COLOR_CELL_1 : COLOR_CELL_0);
            cell.setOutlineThickness(1.f);
            cell.setOutlineColor(COLOR_BORDER);
            cell.setPosition({x, y});
            window.draw(cell);
            
            sf::Text num(font);
            num.setString(std::to_string(matrix[i][j]));
            num.setCharacterSize(16);
            num.setFillColor(COLOR_TEXT_PRIMARY);
            sf::FloatRect bounds = num.getLocalBounds();
            num.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
            num.setPosition({x + cellSize / 2.f, y + cellSize / 2.f - 2.f});
            window.draw(num);
        }
    }
}

void drawGraph(sf::RenderWindow& window, const sf::Font& font, int R[MAX][MAX], int n,
               float panelX, float panelY, float panelW, float panelH, float& animTime) {
    float centerX = panelX + panelW / 2.f;
    float centerY = panelY + panelH / 2.f;
    float radius = 230.f;
    
    sf::Vector2f nodePos[MAX];
    for (int i = 0; i < n; i++) {
        float angle = 2 * 3.14159f * i / n - 3.14159f / 2.f;
        nodePos[i] = sf::Vector2f(centerX + radius * cosf(angle), centerY + radius * sinf(angle));
    }
    
    float alpha = (sin(animTime) + 1.f) / 2.f;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (R[i][j] == 1 && i != j) {
                float dx = nodePos[j].x - nodePos[i].x;
                float dy = nodePos[j].y - nodePos[i].y;
                float dist = sqrt(dx*dx + dy*dy);
                
                if (dist > 0.1f) {
                    float ux = dx / dist, uy = dy / dist;
                    sf::Vector2f start = { nodePos[i].x + ux * NODE_RADIUS, nodePos[i].y + uy * NODE_RADIUS };
                    sf::Vector2f end = { nodePos[j].x - ux * NODE_RADIUS, nodePos[j].y - uy * NODE_RADIUS };
                    
                    int glowAlpha = 120 + (int)(80 * alpha);
                    sf::Color lineCol = COLOR_LINE;
                    lineCol.a = glowAlpha;
                    
                    sf::Vertex line[2] = { {start, lineCol}, {end, lineCol} };
                    window.draw(line, 2, sf::PrimitiveType::Lines);
                    
                    float angle = atan2(dy, dx);
                    sf::ConvexShape arrow;
                    arrow.setPointCount(3);
                    arrow.setPoint(0, end);
                    arrow.setPoint(1, sf::Vector2f(end.x - 14.f * cosf(angle - 0.45f), end.y - 14.f * sinf(angle - 0.45f)));
                    arrow.setPoint(2, sf::Vector2f(end.x - 14.f * cosf(angle + 0.45f), end.y - 14.f * sinf(angle + 0.45f)));
                    arrow.setFillColor(lineCol);
                    window.draw(arrow);
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        sf::CircleShape circle(NODE_RADIUS);
        circle.setFillColor(COLOR_NODE);
        circle.setOutlineThickness(2.5f);
        circle.setOutlineColor(COLOR_NODE_OUT);
        circle.setOrigin({NODE_RADIUS, NODE_RADIUS});
        circle.setPosition(nodePos[i]);
        window.draw(circle);
        
        sf::Text num(font);
        num.setString(std::to_string(i + 1));
        num.setCharacterSize(18);
        num.setFillColor(COLOR_NODE_TEXT);
        sf::FloatRect bounds = num.getLocalBounds();
        num.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        num.setPosition(nodePos[i]);
        window.draw(num);
    }
}

void drawStats(sf::RenderWindow& window, const sf::Font& font, int R[MAX][MAX], int adj[MAX][MAX], int n,
               float x, float y, float w) {
    int edgesIn = 0, edgesOut = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (adj[i][j]) edgesIn++;
                if (R[i][j]) edgesOut++;
            }
        }
    }
    
    sf::RectangleShape box(sf::Vector2f(w, 130.f));
    box.setFillColor(COLOR_PANEL);
    box.setOutlineThickness(1.5f);
    box.setOutlineColor(COLOR_BORDER);
    box.setPosition({x, y});
    window.draw(box);
    
    sf::Text title(font);
    title.setString("THONG KE HE THONG");
    title.setCharacterSize(16);
    title.setFillColor(COLOR_ACCENT);
    title.setPosition({x + 20.f, y + 15.f});
    window.draw(title);
    
    sf::Text s1(font);
    s1.setString("Tong so Dinh: " + std::to_string(n));
    s1.setCharacterSize(15);
    s1.setFillColor(COLOR_TEXT_SECONDARY);
    s1.setPosition({x + 20.f, y + 45.f});
    window.draw(s1);
    
    sf::Text s2(font);
    s2.setString("So canh Input: " + std::to_string(edgesIn));
    s2.setCharacterSize(15);
    s2.setFillColor(COLOR_TEXT_SECONDARY);
    s2.setPosition({x + 20.f, y + 70.f});
    window.draw(s2);
    
    sf::Text s3(font);
    s3.setString("So canh Output: " + std::to_string(edgesOut));
    s3.setCharacterSize(15);
    s3.setFillColor(COLOR_CELL_1);
    s3.setPosition({x + 20.f, y + 95.f});
    window.draw(s3);
}

void drawLegend(sf::RenderWindow& window, const sf::Font& font, float x, float y, float w) {
    sf::RectangleShape box(sf::Vector2f(w, 130.f));
    box.setFillColor(COLOR_PANEL);
    box.setOutlineThickness(1.5f);
    box.setOutlineColor(COLOR_BORDER);
    box.setPosition({x, y});
    window.draw(box);
    
    sf::Text title(font);
    title.setString("CHU THICH");
    title.setCharacterSize(16);
    title.setFillColor(COLOR_ACCENT);
    title.setPosition({x + 20.f, y + 15.f});
    window.draw(title);
    
    sf::CircleShape dot(10.f);
    dot.setFillColor(COLOR_NODE);
    dot.setOutlineThickness(1.5f);
    dot.setOutlineColor(COLOR_NODE_OUT);
    dot.setOrigin({10.f, 10.f});
    dot.setPosition({x + 35.f, y + 55.f});
    window.draw(dot);
    
    sf::Text txt1(font);
    txt1.setString("= Dinh he thong");
    txt1.setCharacterSize(15);
    txt1.setFillColor(COLOR_TEXT_SECONDARY);
    txt1.setPosition({x + 60.f, y + 47.f});
    window.draw(txt1);
    
    sf::Vertex line[2] = {
        {{x + 25.f, y + 85.f}, COLOR_LINE},
        {{x + 45.f, y + 85.f}, COLOR_LINE}
    };
    window.draw(line, 2, sf::PrimitiveType::Lines);
    
    sf::Text txt2(font);
    txt2.setString("= Canh Bao Dong");
    txt2.setCharacterSize(15);
    txt2.setFillColor(COLOR_TEXT_SECONDARY);
    txt2.setPosition({x + 60.f, y + 77.f});
    window.draw(txt2);
    
    sf::RectangleShape cell(sf::Vector2f(18.f, 18.f));
    cell.setFillColor(COLOR_CELL_1);
    cell.setOutlineThickness(1.f);
    cell.setOutlineColor(COLOR_BORDER);
    cell.setPosition({x + 26.f, y + 101.f});
    window.draw(cell);
    
    sf::Text txt3(font);
    txt3.setString("= Ton tai duong di");
    txt3.setCharacterSize(15);
    txt3.setFillColor(COLOR_TEXT_SECONDARY);
    txt3.setPosition({x + 60.f, y + 102.f});
    window.draw(txt3);
}

void drawInstructions(sf::RenderWindow& window, const sf::Font& font) {
    sf::Text instructions(font);
    instructions.setString("PRESS [SPACE] TO RETURN TO CONSOLE");
    instructions.setCharacterSize(16);
    instructions.setFillColor(COLOR_TEXT_SECONDARY);
    
    sf::FloatRect bounds = instructions.getLocalBounds();
    instructions.setPosition({(1600.f - bounds.size.x) / 2.f, 910.f});
    window.draw(instructions);
}

void runGraphicsApp(const std::string& inputSourceName, int n, int adj[MAX][MAX], int R[MAX][MAX]) {
    setConsoleColor(14);
    std::cout << "\n  >>> DANG MO CUA SO DO HOA SFML...\n";
    std::cout << "  >>> BAM PHIM [SPACE] TREN CUA SO DO HOA DE DONG VA TIEP TUC!\n";
    setConsoleColor(15);

    sf::RenderWindow window(sf::VideoMode({1600, 950}), "PBL1 - Warshall Algorithm");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "  [!] Khong the tai Font chu!" << std::endl;
        return;
    }

    float animTime = 0.f;
    bool spacePressed = false;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPress->code == sf::Keyboard::Key::Space) {
                    spacePressed = true;
                }
            }
        }

        if (spacePressed) {
            window.close();
            break;
        }

        animTime += 0.05f;
        window.clear(COLOR_BG);
        
        drawGrid(window);

        sf::RectangleShape header(sf::Vector2f(1600.f, 65.f));
        header.setFillColor(COLOR_HEADER);
        window.draw(header);

        sf::Text title(font);
        title.setString(L"PBL1 - WARSHALL'S ALGORITHM");
        title.setCharacterSize(22);
        title.setFillColor(COLOR_ACCENT);
        title.setPosition({25.f, 18.f});
        window.draw(title);

        sf::Text info(font);
        info.setString("NGUON DU LIEU: " + inputSourceName + "  |  TONG SO DINH: " + std::to_string(n));
        info.setCharacterSize(14);
        info.setFillColor(COLOR_TEXT_SECONDARY);
        info.setPosition({1200.f, 25.f});
        window.draw(info);

        float graphWidth = 1600.f * 0.6f;
        float leftWidth = 1600.f * 0.4f;
        float rightX = graphWidth + 10.f;
        float matrixWidth = (leftWidth - 35.f) / 2.f;

        sf::RectangleShape graphBg(sf::Vector2f(graphWidth - 20.f, 850.f));
        graphBg.setFillColor(COLOR_PANEL);
        graphBg.setOutlineThickness(1.5f);
        graphBg.setOutlineColor(COLOR_BORDER);
        graphBg.setPosition({10.f, 75.f});
        window.draw(graphBg);

        sf::Text graphTitle(font);
        graphTitle.setString("HE THONG DO THI");
        graphTitle.setCharacterSize(16);
        graphTitle.setFillColor(COLOR_ACCENT);
        graphTitle.setPosition({25.f, 90.f});
        window.draw(graphTitle);

        drawGraph(window, font, R, n, 10.f, 75.f, graphWidth - 20.f, 850.f, animTime);
        drawMatrix(window, font, adj, n, rightX, 75.f, "MA TRAN INPUT", matrixWidth);
        drawMatrix(window, font, R, n, rightX + matrixWidth + 8.f, 75.f, "MA TRAN OUTPUT", matrixWidth);

        float cellSize = matrixWidth / (n + 0.5f);
        if (cellSize > 50.f) cellSize = 50.f;
        float matrixHeight = (n * cellSize) + 35.f + 24.f;
        float statsY = 75.f + matrixHeight + 15.f;

        drawStats(window, font, R, adj, n, rightX, statsY, leftWidth - 30.f);
        drawLegend(window, font, rightX, statsY + 145.f, leftWidth - 30.f);
        drawInstructions(window, font);

        window.display();
    }
}