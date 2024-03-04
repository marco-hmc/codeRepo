#include <iostream>
#include <vector>

using namespace std;

int n, m;
struct Point {
    int x;
    int y;
    friend bool operator==(const Point &p1, const Point &p2) {
        return (p1.x == p2.x && p1.y == p2.y)?true:false;
    }
    bool isOK() {
        bool flag = (x >= 0 && x <n && y >= 0 && y < m) ? true : false;
        return flag;
    }
    Point() : x(-1), y(-1){}
    Point(int x, int y) : x(x), y(y){}
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
    return !isVisited(cur, visited) && isPath(cur, maze);
}

void backTracking(Point cur, int cnt, vector<vector<char>> &maze, vector<vector<bool>> &visited){
    if(cur == dst){
        ret = min(cnt, ret);
    }
    for(int i=0; i<4; i++){
        Point tmp(cur.x+dx[i], cur.y+dy[i]);
        if(tmp.isOK()&&isValid(tmp, maze, visited)){
            visited[tmp.x][tmp.y] = true;
            backTracking(tmp, ++cnt, maze, visited);
            visited[tmp.x][tmp.y] = false;
        }
    }
}

int main() {
    cin >> n >> m;
    Point cur;
    cin >> cur.x >> cur.y;
    cin >> dst.x >> dst.y;
    cur.x -= 1; cur.y -= 1;
    dst.x -= 1; dst.y -= 1;
    vector<vector<char> > maze(n, vector<char>(m));
    vector<vector<bool> > visited(n, vector<bool>(m, false));
    ret = INT_MAX;
    for (int i = 0; i < n; i++) {
        for(int j=0; j<m; j++){
            cin>>maze[i][j];
        }
    }
    backTracking(cur, 0, maze, visited);
    cout<<ret<<endl;
    return 0;
}