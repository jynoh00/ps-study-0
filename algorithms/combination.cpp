#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 4
#define endl "\n"

struct Fish {
    int num, dir;
    Fish() : num(0), dir(0) {}
    Fish(int n, int d) : num(n), dir(d) {}
};

int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};

int ans = 0;

void copyBoard(Fish src[MAX][MAX], Fish dst[MAX][MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

void moveFishes(Fish board[MAX][MAX], int shark_x, int shark_y) {
    for (int fish_num = 1; fish_num <= 16; fish_num++) {
        int fx = -1, fy = -1;
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (board[i][j].num == fish_num) {
                    fx = i; fy = j;
                    break;
                }
            }
            if (fx != -1) break;
        }
        
        if (fx == -1) continue;
        
        int dir = board[fx][fy].dir;
        for (int i = 0; i < 8; i++) {
            int new_dir = (dir + i) % 8;
            int nx = fx + dx[new_dir];
            int ny = fy + dy[new_dir];
            
    
            if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX) continue;
            if (nx == shark_x && ny == shark_y) continue;
            
            board[fx][fy].dir = new_dir;
            
            Fish temp = board[fx][fy];
            board[fx][fy] = board[nx][ny];
            board[nx][ny] = temp;
            break;
        }
    }
}

vector<pair<int, int>> getSharkMoves(Fish board[MAX][MAX], int shark_x, int shark_y, int shark_dir) {
    vector<pair<int, int>> moves;
    
    for (int step = 1; step <= 3; step++) {
        int nx = shark_x + dx[shark_dir] * step;
        int ny = shark_y + dy[shark_dir] * step;
        
        if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX) break;
        
        if (board[nx][ny].num > 0) {
            moves.push_back({nx, ny});
        }
    }
    
    return moves;
}

void solution(Fish board[MAX][MAX], int shark_x, int shark_y, int shark_dir, int score) {
    Fish temp_board[MAX][MAX];
    copyBoard(board, temp_board);
    
    moveFishes(temp_board, shark_x, shark_y);
    
    vector<pair<int, int>> possible_moves = getSharkMoves(temp_board, shark_x, shark_y, shark_dir);
    
    if (possible_moves.empty()) {
        ans = max(ans, score);
        return;
    }
    
    for (pair<int, int> move : possible_moves) {
        int nx = move.first;
        int ny = move.second;
        
        Fish next_board[MAX][MAX];
        copyBoard(temp_board, next_board);
        
        Fish eaten_fish = next_board[nx][ny];
        next_board[nx][ny] = Fish(0, 0);
        
        solution(next_board, nx, ny, eaten_fish.dir, score + eaten_fish.num);
    }
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    Fish board[MAX][MAX];
    
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            int num, dir;
            cin >> num >> dir;
            dir--;
            board[i][j] = Fish(num, dir);
        }
    }
    
    int initial_score = board[0][0].num;
    int initial_dir = board[0][0].dir;
    board[0][0] = Fish(0, 0);
    
    solution(board, 0, 0, initial_dir, initial_score);
    
    cout << ans << endl;
    
    return 0;
}