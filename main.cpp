#include <iostream>
#include <string>
#include "Common.h"
#include "WarshallLogic.h"
#include "GraphGUI.h"

using namespace std;

int main() {
    MaximizeConsole();
    
    while (true) {
        int choice = showConsoleMenu();
        
        if (choice == 0) {
            setConsoleColor(12);
            cout << "\n  [!] Da thoat chuong trinh.\n" << endl;
            setConsoleColor(15);
            break;
        }

        int n = 0;
        int adj[MAX][MAX], R[MAX][MAX], next_node[MAX][MAX];
        bool dataLoaded = false;
        string inputSourceName = "";

        if (choice == 1) {
            int testCase;
            setConsoleColor(14);
            cout << "  => Nhap so thu tu Input ban muon test trong file (VD: 1, 2...): ";
            setConsoleColor(15);
            while (!(cin >> testCase) || testCase <= 0) {
                clearInputBuffer();
                setConsoleColor(12); 
                cout << "  [!] Lua chon khong hop le! Nhap lai: "; 
                setConsoleColor(15);
            }
            inputSourceName = "FILE - TEST CASE " + to_string(testCase);
            dataLoaded = loadInputFromFile(testCase, n, adj, R);
        } else if (choice == 2) {
            inputSourceName = "BAN PHIM";
            dataLoaded = loadInputFromKeyboard(n, adj, R);
        }

        if (dataLoaded) {
            printConsoleMatrix(adj, n, "MA TRAN INPUT", 11);
            runWarshall(R, n, next_node);
            printConsoleMatrix(R, n, "MA TRAN OUTPUT (BAO DONG)", 10);
            runGraphicsApp(inputSourceName, n, adj, R);
            tracePath(n, next_node);
        }
    }
    
    return 0;
}