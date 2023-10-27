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

int dijkstraShortestPathFinding(vector<vector<int>>& heightMap, Node& start, Node& end) {
    int row = heightMap.size();
    int col = heightMap[0].size();
    int distance = 0;
    vector<vector<int>> dist(row, vector<int>(col, infinity));
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(start);
    std::vector<int> dr{ -1, -1, 0, 1, 1, 0 };
    std::vector<int> dc{ 0, 1, 1, 0, -1, -1 };
    dist[start.x][start.y] = 0;
    int currCost = 0;
    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();
        if (curr.x == end.x && curr.y == end.y) {

            return curr.dist;
        }
        if (curr.dist > dist[curr.x][curr.y]) {
            continue;
        }
        cout << "Current  [x, y] = " << "[" << curr.x << ", " << curr.y << "] Cost: " << currCost << endl;
        for (int i = 0; i < dr.size(); ++i) {
            int nx = curr.x + dr[i];
            int ny = curr.y + dc[i];
                if (nx < 0 || nx >= row || ny < 0 || ny >= col) {
                    continue;
                }
                cout << "Value [nx, ny] = " << "[" << nx << ", " << ny << "]" << endl;
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
    
    return -1;
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
  
    /*
    1 2 3
    4 5 6
    7 8 9

    0  1  2
    5  6  7
    10 11 12
    */

    // dr : -1, -1, 0, 1, 1, 0
    // dc : 0, 1, 1, 0, -1, -1
    /*Node start{0, 0, 0};
    Node end{2, 2, 0};*/
    Node start;
    Node end;
    //User Inputs for start and end vertex point
    cout << "Enter x-coordinate for Start node: ";
    std::cin >> start.x;
    cout << "Enter y-coordinate for Start node: ";
    std::cin >> start.y;
    cout << "Enter x-coordinate for End node: ";
    std::cin >> end.x;
    cout << "Enter y-coordinate for End node: ";
    std::cin >> end.y;


    cout << endl << "preEruptionHeightMap" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "[ [" << i << "][" << j << "] = " << preEruptionHeightMap[i][j] << " ]" << "   ";
        }
        cout << endl;
    }
    int preEruptionDist = dijkstraShortestPathFinding(preEruptionHeightMap, start, end);

    cout << endl << "" << endl;
    cout << endl << "postEruptionHeightMap" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "[ [" << i << "][" << j << "] = " << postEruptionHeightMap[i][j] << " ]" << "   ";
        }
        cout << endl;
    }
    int postEruptionDist = dijkstraShortestPathFinding(postEruptionHeightMap, start, end);
    cout << "Surface distance from point A to point B in pre-eruption height map: " << preEruptionDist << " meters" << endl;
    cout << "Surface distance from point A to point B in post-eruption height map: " << postEruptionDist << " meters" << endl;
    cout<< "Difference in surface distance between Pre-Eruption and Post-Eruption: " << abs(preEruptionDist - postEruptionDist) << " meters" << endl;

}