#include <bits/stdc++.h>
using namespace std;


int n, m;
struct Point {
    int x;
    int y;
    bool isOK() {
        bool flag = (x >= 0 && x <n && y >= 0 && y < m) ? true : false;
        return flag;
    }
    friend bool operator==(const Point &p1, const Point &p2) {
        return (p1.x == p2.x && p1.y == p2.y)?true:false;
    }
    Point() : x(-1), y(-1){}
    Point(int x, int y) : x(x), y(y) {}
};

Point dst;
int ret;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

inline bool isVisited(Point cur, vector<vector<bool>> &visited) {
    if(visited[cur.x][cur.y] == true)
        return true;
    else
        return false;
}

inline bool isPath(Point cur, vector<vector<char>> &maze) {
    if(maze[cur.x][cur.y] == '.')
        return true;
    else
        return false;
}

bool isValid(Point cur, vector<vector<char>> &maze, vector<vector<bool>> &visited){
    return isPath(cur, maze) && !isVisited(cur, visited);
}

int bfs(Point cur, vector<vector<char>> &maze, vector<vector<bool>> &visited, vector<vector<int>> &dp){
    queue<Point> q;
    q.push(cur);
    while(!q.empty()){
        Point tmp =q.front();
        if(tmp == dst)
            return dp[tmp.x][tmp.y];
        q.pop();
        for (int i = 0; i < 4;i++){
            Point next(tmp.x + dx[i], tmp.y + dy[i]);
            if(next.isOK() && isValid(next, maze, visited)){
                visited[next.x][next.y] = true;
                q.push(next);
                dp[next.x][next.y] = dp[tmp.x][tmp.y] + 1;
            }
        }
    }
    return -1;
}

int main() {
    cin >> n >> m;
    Point cur;
    cin >> cur.x >> cur.y;
    cin >> dst.x >> dst.y;
    cur.x -= 1; cur.y -= 1;
    dst.x -= 1; dst.y -= 1;
    vector<vector<char>> maze(n, vector<char>(m));
    vector<vector<bool> > visited(n, vector<bool>(m, false));
    vector<vector<int> > dp(n, vector<int>(m, 0));
    visited[cur.x][cur.y] = true;
    ret = INT_MAX;
    for (int i = 0; i < n; i++)
        for(int j=0; j<m; j++)
            cin>>maze[i][j];
    int ret = bfs(cur, maze, visited, dp);
    cout<<ret<<endl;
    return 0;
}