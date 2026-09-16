#include "WarshallLogic.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <windows.h>

using namespace std;

void MaximizeConsole() {
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int showConsoleMenu() {
    int choice;
    system("cls");
    setConsoleColor(11); 
    cout << "\n  +--------------------------------------------------------+\n";
    cout << "  |        CHUONG TRINH TIM MA TRAN BAO DONG - PBL1        |\n";
    cout << "  +--------------------------------------------------------+\n\n";
    
    setConsoleColor(14); 
    cout << "  [ MENU DIEU KHIEN ]\n";
    setConsoleColor(15); 
    cout << "  1. Nhap do thi tu file input.txt (Theo so thu tu Test case)\n";
    cout << "  2. Nhap do thi thu cong tu ban phim\n";
    cout << "  0. KET THUC chuong trinh.\n\n";
    
    setConsoleColor(10); 
    cout << "  => Lua chon cua ban: ";
    setConsoleColor(15); 
    
    while (!(cin >> choice) || choice < 0 || choice > 2) {
        clearInputBuffer();
        setConsoleColor(12);
        cout << "  [!] Lua chon khong hop le! Vui long nhap lai (0, 1 hoac 2): ";
        setConsoleColor(15);
    }
    return choice;
}

void printConsoleMatrix(int matrix[MAX][MAX], int n, const string& title, int color) {
    setConsoleColor(color);
    cout << "\n  --- " << title << " (Kich thuoc " << n << "x" << n << ") ---\n";
    setConsoleColor(15);
    for (int i = 0; i < n; i++) {
        cout << "  ";
        for (int j = 0; j < n; j++) cout << matrix[i][j] << " ";
        cout << "\n";
    }
}

bool loadInputFromFile(int choice, int &n, int adj[MAX][MAX], int R[MAX][MAX]) {
    ifstream file("input.txt");
    if (!file.is_open()) {
        setConsoleColor(12);
        cout << "  [!] Loi: Khong tim thay file input.txt!\n";
        Sleep(1500);
        return false;
    }

    bool found = false;
    for (int i = 1; i <= choice; ++i) {
        if (!(file >> n)) break;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                int temp;
                file >> temp;
                if (i == choice) {
                    adj[r][c] = temp;
                    R[r][c] = temp;
                    found = true;
                }
            }
        }
    }
    file.close();

    if (!found) {
        setConsoleColor(12);
        cout << "\n  [!] KHONG TIM THAY INPUT SO " << choice << " TRONG FILE!\n";
        Sleep(1500);
    }
    return found;
}

bool loadInputFromKeyboard(int &n, int adj[MAX][MAX], int R[MAX][MAX]) {
    setConsoleColor(14);
    cout << "\n  --- NHAP DU LIEU TU BAN PHIM ---\n";
    setConsoleColor(15);
    
    cout << "  Nhap so luong dinh N (1 <= N <= " << MAX << "): ";
    while (!(cin >> n) || n < 1 || n > MAX) {
        clearInputBuffer();
        setConsoleColor(12);
        cout << "  [!] N khong hop le. Vui long nhap lai (Tu 1 den " << MAX << "): ";
        setConsoleColor(15);
    }

    cout << "  Nhap ma tran ke " << n << "x" << n << " (Chi chap nhan gia tri 0 hoac 1):\n";
    for (int i = 0; i < n; i++) {
        cout << "  -> Hang " << i + 1 << ": ";
        for (int j = 0; j < n; j++) {
            while (!(cin >> adj[i][j]) || (adj[i][j] != 0 && adj[i][j] != 1)) {
                clearInputBuffer();
                setConsoleColor(12);
                cout << "  [!] Gia tri tai [" << i+1 << "][" << j+1 << "] phai la 0 hoac 1. Nhap lai tu phan tu nay: ";
                setConsoleColor(15);
            }
            R[i][j] = adj[i][j];
        }
    }
    return true;
}

void runWarshall(int R[MAX][MAX], int n, int next_node[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (R[i][j] == 1) next_node[i][j] = j;
            else next_node[i][j] = -1;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (R[i][k] && R[k][j]) {
                    if (R[i][j] == 0) {
                        R[i][j] = 1;
                        next_node[i][j] = next_node[i][k];
                    }
                }
            }
        }
    }
}

void tracePath(int n, int next_node[MAX][MAX]) {
    while (true) {
        int a, b;
        setConsoleColor(14);
        cout << "\n  --- TRUY VET DUONG DI ---\n";
        setConsoleColor(15);
        
        cout << "  Nhap dinh bat dau A (Tu 1 den " << n << ") hoac nhap 0 de thoat truy vet: ";
        if (!(cin >> a) || a == 0) {
            clearInputBuffer();
            break;
        }
        
        cout << "  Nhap dinh ket thuc B (Tu 1 den " << n << "): ";
        if (!(cin >> b)) {
            clearInputBuffer();
            cout << "  [!] Dau vao khong hop le!\n";
            continue;
        }
        
        if (a < 1 || a > n || b < 1 || b > n) {
            setConsoleColor(12);
            cout << "  [!] Dinh khong ton tai! Vui long nhap tu 1 den " << n << ".\n";
            continue;
        }
        
        int start = a - 1;
        int end = b - 1;
        
        if (next_node[start][end] == -1) {
            setConsoleColor(12);
            cout << "  => Khong ton tai duong di tu dinh " << a << " den dinh " << b << "!\n";
        } else {
            setConsoleColor(10);
            cout << "  => Duong di: " << a;
            int u = start;
            int steps = 0;
            bool loopDetected = false;

            while (u != end) {
                u = next_node[u][end];
                cout << " -> " << u + 1;
                steps++;
                if (steps > n) {
                    loopDetected = true;
                    break;
                }
            }
            if (loopDetected) {
                setConsoleColor(12);
                cout << " (Phat hien chu trinh lap!)";
            }
            cout << "\n";
        }
    }
}