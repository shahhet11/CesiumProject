using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
//#include <bits/stdc++.h>


int infinity = numeric_limits<int>::max();



struct Node {
    int x, y, dist;
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

int shortestPathFinding(vector<vector<int>>& heightMap, Node& start, Node& end) {
    int row = heightMap.size();
    int col = heightMap[0].size();
    /*cout << "Value of n:" << n << endl;
    cout << "Value of m:" << m << endl;*/
    int distance = 0;
    vector<vector<int>> dist(row, vector<int>(col, infinity));
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(start);
    dist[start.x][start.y] = 0;
    int currCost = 0;
    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();
        cout << "Current  [x, y] = " << "[" << curr.x << ", " << curr.y << "] Cost: " << currCost << endl;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                int nx = curr.x + dx;
                int ny = curr.y + dy;
                /*cout << "Value of nx " << nx << endl;
                cout << "Value of ny " << ny << endl;*/
                if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
                    continue;
                }
                int startPixelHeightVal = heightMap[curr.x][curr.y];
                int endPixelHeightVal = heightMap[nx][ny];
                int cost = sqrt(pow(30, 2) + pow(abs(startPixelHeightVal - endPixelHeightVal), 2));
                currCost = cost;
                //cout << "Value of cost " << cost << endl;
                if (dist[curr.x][curr.y] + cost < dist[nx][ny]) {
                    dist[nx][ny] = dist[curr.x][curr.y] + cost;
                    pq.push({ nx, ny, dist[nx][ny] });

                }
            }
        }
    }
    
    return 0;
}



vector< unsigned char> readBinaryFile(const std::string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);
    vector<unsigned char> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        throw runtime_error("Failed to read from file: " + filename);
    }
    return buffer;
}
int main() {
	cout << "Cesium Project" << endl;

    vector<vector<int>> preEruptionHeightMap(512, vector<int>(512));
    vector<vector<int>> postEruptionHeightMap(512, vector<int>(512));
    // read .data files into preEruptionHeightMap and postEruptionHeightMap
    vector<unsigned char> preEruptionData = readBinaryFile("pre.data");
    vector<unsigned char> postEruptionData = readBinaryFile("post.data");
    cout << preEruptionData.size() << endl;

    /*for (size_t i = 0; i < preEruptionData.size(); ++i) {
        unsigned char element = preEruptionData[i];
        cout << "Element at index " << i << ": " << static_cast<int>(element) << endl;
    }*/

    for (int i = 0; i < 512; ++i) {
        for (int j = 0; j < 512; ++j) {
            int index = i * 512 + j;
            preEruptionHeightMap[i][j] = preEruptionData[index] * 11;
            postEruptionHeightMap[i][j] = postEruptionData[index] * 11;
        }
    }
    // S_Distance = Sqrt(30^2 + |start.pixelVal - end.pixelVal|^2); pixelVal willb be in meters after multiplying with 11

    int startPixelHeightVal = preEruptionHeightMap[2][1];
    int endPixelHeightVal = preEruptionHeightMap[3][4];
    int distance = sqrt(pow(30, 2) + pow(abs(startPixelHeightVal - endPixelHeightVal), 2));
    cout << "Distance" << distance << endl;

    // std::vector<int> dr{-1, -1, 1, };
    // std::vector<int> dc{-1,  0, 1, 1, 0, -1, -1};

    /*
    1 2 3
    4 5 6
    7 8 9

    0  1  2
    5  6  7
    10 11 12
    */
    Node start{0, 0};
    Node end{2, 2};

    cout << endl << "preEruptionHeightMap" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "[ [" << i << "][" << j << "] = " << preEruptionHeightMap[i][j] << " ]" << "   ";
        }
        cout << endl;
    }
    int preEruptionDist = shortestPathFinding(preEruptionHeightMap, start, end);

    cout << endl << "" << endl;
    cout << endl << "postEruptionHeightMap" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "[ [" << i << "][" << j << "] = " << postEruptionHeightMap[i][j] << " ]" << "   ";
        }
        cout << endl;
    }
    int postEruptionDist = shortestPathFinding(postEruptionHeightMap, start, end);



}