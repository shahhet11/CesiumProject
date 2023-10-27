using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
//#include <bits/stdc++.h>

vector<unsigned char> readBinaryFile(const std::string& filename) {
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


}