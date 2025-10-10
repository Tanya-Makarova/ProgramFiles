#include <iostream>
#include <vector>
using namespace std;

// ��������� ������ ��� �������� ����� �����
struct Edge {
    int src, dest;
};

// ����� ��� ������������� ������� �����
class Graph
{
public:
    // D����� �������� ��� ������������� ������ ���������
    vector<vector<int>> adjList;

    // ����������� ������
    Graph(vector<Edge> const& edges, int n)
    {
        // �������� ������ �������, ����� �� ������ n ��������� ���� vector<int>
        adjList.resize(n);

        // ��������� ���� � ��������������� ����
        for (auto& edge : edges)
        {
            // ��������� � �����
            adjList[edge.src].push_back(edge.dest);

            // ���� ���� �����������������, �� ������� ����������� �� ��������� ������
            // adjList[edge.dest].push_back(edge.src);
        }
    }
};

// �������, ����� ������� ���� � ������ � ���������
void printGraph(Graph const& graph, int n)
{
    for (int i = 0; i < n; i++)
    {
        // ������� ������� ����� �������
        cout << i << " --> ";

        // ������� �� ����� ��� ������� ������� � ������� ��������
        for (int v : graph.adjList[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

// ���������� ����� � �������������� STL
int main()
{
    //  ����������� ���� � ������������ �� ������
    vector<Edge> edges =
    {
        {7, 1}, {1, 2}, {2, 1}, {3, 2}, {4, 5}, {5, 4}, {3, 4}, {4, 3}, {5, 6}, {6, 7}, {0, 3}
    };

    // ����� ���������� �����
    int n = 8;

    // ����������� ������
    Graph graph(edges, n);

    // ������� ���� � ���� ������ ���������
    printGraph(graph, n);

    return 0;
}