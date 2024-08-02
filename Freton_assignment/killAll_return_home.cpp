#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

// Directions: 0: East, 1: North, 2: West, 3: South
const int dx[4] = {0, -1, 0, 1}; // Movement offsets for East, North, West, South
const int dy[4] = {1, 0, -1, 0};

// Function to check if a cell is within the board boundaries
bool isValid(int x, int y) {
    return x >= 0 && x < 9 && y >= 0 && y < 9;
}

// Function to print the chessboard
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Function to recursively find all unique paths and count them
void findPaths(vector<vector<int>>& board, int x, int y, int home_x, int home_y, int direction, set<string>& visitedPaths, int& pathCount) {
    // Base case: Check if we reached the home castle
    if (x == home_x && y == home_y) {
        pathCount++;
        return;
    }

    string pathKey = to_string(x) + "," + to_string(y) + "," + to_string(direction);
    if (visitedPaths.find(pathKey) != visitedPaths.end()) return;
    visitedPaths.insert(pathKey);

    // Move in the current direction
    int new_x = x + dx[direction];
    int new_y = y + dy[direction];

    if (isValid(new_x, new_y)) {
        if (board[new_x][new_y] == 1) {
            // Kill the soldier and move to the left
            board[new_x][new_y] = -1;
            int new_direction = (direction + 3) % 4; // Turn left
            findPaths(board, new_x, new_y, home_x, home_y, new_direction, visitedPaths, pathCount);
            board[new_x][new_y] = 1; // Restore the cell
        } else if (board[new_x][new_y] == -1) {
            // Jump over an empty cell
            findPaths(board, new_x, new_y, home_x, home_y, direction, visitedPaths, pathCount);
        }
    }

    // Turn left and continue
    int new_direction = (direction + 1) % 4;
    string new_pathKey = to_string(x) + "," + to_string(y) + "," + to_string(new_direction);
    if (visitedPaths.find(new_pathKey) == visitedPaths.end()) {
        findPaths(board, x, y, home_x, home_y, new_direction, visitedPaths, pathCount);
    }
}
int main() {
    int num_soldiers;
    cout << "Enter the number of soldiers: ";
    cin >> num_soldiers;

    vector<vector<int>> chessboard(9, vector<int>(9, -1)); // -1: Empty, 1: Soldier

    cout << "Enter the coordinates for the soldiers (format x,y):" << endl;
        for (int i = 0; i < num_soldiers; ++i) {
            string temp;
            cin>>temp; // Declare a char variable for comma
            int x =temp[0]-'0';
            int y=temp[2]-'0';
            chessboard[x][y] = 1;
        }

    int start_x, start_y;
    cout << "Enter the coordinates for the starting castle (format x,y): ";
    char comma; // Declare a char variable for comma
    cin >> start_x >> comma >> start_y;

    int home_x, home_y;
    cout << "Enter the coordinates for the home castle (format x,y): ";
    cin >> home_x >> comma >> home_y;

    // Set to keep track of visited paths
    set<string> visitedPaths;
    int pathCount = 0;

    

    // Find and count all unique paths
    findPaths(chessboard, start_x, start_y, home_x, home_y, 0, visitedPaths, pathCount);

    // Print the total number of unique paths
    cout << "Thanks. There are " << pathCount << " unique paths for your ‘special_castle’" << endl;

    return 0;
}
