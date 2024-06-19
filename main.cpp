#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int boardSize = 10;
const int numShips = 5;

class Board {
private:
    vector<vector<char>> grid;
public:
    Board() : grid(boardSize, vector<char>(boardSize, '~')) {}

    void display() {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool placeShip(int x, int y, int length, char direction) {
        if (direction == 'H') {
            if (y + length > boardSize) return false;
            for (int i = 0; i < length; ++i) {
                if (grid[x][y + i] != '~') return false;
            }
            for (int i = 0; i < length; ++i) {
                grid[x][y + i] = 'S';
            }
        } else if (direction == 'V') {
            if (x + length > boardSize) return false;
            for (int i = 0; i < length; ++i) {
                if (grid[x + i][y] != '~') return false;
            }
            for (int i = 0; i < length; ++i) {
                grid[x + i][y] = 'S';
            }
        } else {
            return false;
        }
        return true;
    }

    bool attack(int x, int y) {
        if (grid[x][y] == 'S') {
            grid[x][y] = 'X';
            return true;
        } else if (grid[x][y] == '~') {
            grid[x][y] = 'O';
            return false;
        }
        return false;
    }
};

class Game {
private:
    Board playerBoard;
    Board enemyBoard;

    void placeEnemyShips() {
        srand(time(0));
        int lengths[numShips] = {5, 4, 3, 3, 2};
        for (int i = 0; i < numShips; ++i) {
            bool placed = false;
            while (!placed) {
                int x = rand() % boardSize;
                int y = rand() % boardSize;
                char direction = (rand() % 2 == 0) ? 'H' : 'V';
                placed = enemyBoard.placeShip(x, y, lengths[i], direction);
            }
        }
    }

public:
    Game() {
        placeEnemyShips();
    }

    void displayBoards() {
        cout << "Player's Board:" << endl;
        playerBoard.display();
        cout << "Enemy's Board:" << endl;
        enemyBoard.display();
    }

    void playerMove(int x, int y) {
        if (enemyBoard.attack(x, y)) {
            cout << "Hit!" << endl;
        } else {
            cout << "Miss!" << endl;
        }
    }
};

int main() {
    Game game;
    game.displayBoards();

    int x, y;
    while (true) {
        cout << "Enter coordinates to attack (x y): ";
        cin >> x >> y;
        game.playerMove(x, y);
        game.displayBoards();
    }

    return 0;
}
