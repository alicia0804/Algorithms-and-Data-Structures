#include <iostream>                 
#include <vector>                 
#include <queue>              
#include <utility>                 

using namespace std;               

//we have a class that represents the puzzle board
class PuzzleBoard {
private:
    vector<vector<int>> board;    
    int n;                        

public:
    
    PuzzleBoard(const vector<vector<int>>& inputBoard) {
        board = inputBoard;
        n = board.size();
    }

   //we solve the puzzle using Breadth First Search because we track the visited cells,
   //we store it in a queue, we start at 0,0 and mark it as visited 
    int solve() {
        vector<vector<bool>> visited(n, vector<bool>(n, false)); 
        queue<pair<pair<int, int>, int>> q;                    

        q.push(make_pair(make_pair(0, 0), 0));  
        visited[0][0] = true;                  

        int dx[] = {0, 1};  
        int dy[] = {1, 0};  

        while (!q.empty()) {
            pair<pair<int, int>, int> front = q.front(); 
            q.pop();

            int x = front.first.first;
            int y = front.first.second;
            int steps = front.second;   

           //if we reach the destination we return the number of steps
            if (x == n - 1 && y == n - 1) {
                return steps;           
            }

            int move = board[x][y];      
            for (int dir = 0; dir < 2; ++dir) {
                int newX = x + dx[dir] * move;
                int newY = y + dy[dir] * move;

                //we check the bounds to see whether the new cell is unvisited
                if (newX >= 0 && newX < n && newY >= 0 && newY < n && !visited[newX][newY]) {
                    visited[newX][newY] = true;//we mark it as visited
                    //we enqueue with step count
                    q.push(make_pair(make_pair(newX, newY), steps + 1));
                }
            }
        }

        return -1; 
    }
};

int main() {
    int n;
    cout << "the size of the board: ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n));
    cout << "the board values (row by row):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
        }
    }

    PuzzleBoard puzzle(board);       
    int result = puzzle.solve();     

    if (result != -1) {
        cout << "minimum steps to reach the end: " << result << endl;
    } else {
        cout << "there isn't a path to the end that exists" << endl;
    }

    return 0;
}
