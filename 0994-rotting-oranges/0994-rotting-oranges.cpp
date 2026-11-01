class Solution {
public:
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    vector<vector<bool> > visited;
    vector<vector<int> > time;
    int countNormalOranges;
    int countRotOranges;

    int bfs(vector<pair<int, int> > rot_orranges, vector<vector<int> > grid) {
        queue<pair<int, int> > q;
        int res = 0;

        for (int i=0; i < rot_orranges.size(); i++) {
            visited[rot_orranges[i].first][rot_orranges[i].second] = true;
            q.push(rot_orranges[i]);
        }

        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();
            grid[current.first][current.second] = 2;

            int current_time = time[current.first][current.second];
            res = max(res, current_time);

            cout << "x: " << current.first << ' ' << "y: " << current.second << endl;

            for (int i=0; i < 4; i++) {
                int nx = current.first + dx[i];
                int ny = current.second + dy[i];

                if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()) {
                    continue;
                }

                if (grid[nx][ny] == 0) {
                    continue;
                }

                if (grid[nx][ny] == 2) {
                    continue;
                }

                if (visited[nx][ny]) {
                    continue;
                }

                time[nx][ny] = current_time + 1;
                visited[nx][ny] = true;
                countRotOranges++;
                q.push(make_pair(nx, ny));
            }
        }

        // cout << countNormalOranges << endl;
        // cout << countRotOranges << endl;


        if (countRotOranges == countNormalOranges) {
            return res;
        } else {
            return -1;
        }
    }

    int orangesRotting(vector<vector<int>>& grid) {
        vector<pair<int, int> > rot_orranges;
        visited.assign(grid.size(), vector<bool>(grid[0].size(), false));
        time.assign(grid.size(), vector<int>(grid[0].size(), 0));

        // countNormalOranges = 0;
        // countRotOranges = 0;

        for (int i=0; i < grid.size(); i++) {
            for (int j=0; j < grid[i].size(); j++) {
                if (grid[i][j] == 1) {
                    countNormalOranges++;
                }

                if (grid[i][j] == 2) {
                    rot_orranges.push_back(make_pair(i, j));
                }
            }
        }

        if (countNormalOranges == 0) {
            return 0;
        }

        // cout << "countNormalOranges: " << countNormalOranges << ' ' << "countRotOranges: " << countRotOranges << endl;

        int res = bfs(rot_orranges, grid);

        return res;
    }
};