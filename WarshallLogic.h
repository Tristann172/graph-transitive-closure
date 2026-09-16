#ifndef WARSHALL_LOGIC_H
#define WARSHALL_LOGIC_H

#include <string>
#include "Common.h"

void MaximizeConsole();
void setConsoleColor(int color);
void clearInputBuffer();
int showConsoleMenu();
void printConsoleMatrix(int matrix[MAX][MAX], int n, const std::string& title, int color);

bool loadInputFromFile(int choice, int &n, int adj[MAX][MAX], int R[MAX][MAX]);
bool loadInputFromKeyboard(int &n, int adj[MAX][MAX], int R[MAX][MAX]);
void runWarshall(int R[MAX][MAX], int n, int next_node[MAX][MAX]);
void tracePath(int n, int next_node[MAX][MAX]);

#endif // WARSHALL_LOGIC_H