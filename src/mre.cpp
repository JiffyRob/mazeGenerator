#include <iostream>
#include <vector>

using std::vector;

void doLoop(vector<vector<int>>& nodes)
{
    int width = 500;
    int height = 500;
    for (int row = 0; row < height; row++) {
        vector<int> nested = {};
        for (int col = 0; col < height; col++) {
            nested.push_back(0);
        }
        nodes.push_back(nested);
    }

    nodes.clear();
}

int main()
{

    vector<vector<int>> nodes;

    for (size_t i = 0; i<100; i++)
    {
        doLoop(nodes);
    }

    return 0;
}