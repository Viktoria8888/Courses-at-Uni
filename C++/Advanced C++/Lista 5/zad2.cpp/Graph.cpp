#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>

class Graph
{
public:
    void addVertex(const std::string &vertex)
    {
        if (vertex.empty())
        {
            std::cerr << "Vertex has to have a name" << std::endl;
            return;
        }

        if (!vertices.count(vertex))
        {
            vertices.insert(vertex);
            adjacencyList[vertex] = {};
        }
        else
        {
            std::cerr << "Vertex  " << vertex << " already exists." << std::endl;
        }
    }

    void addEdge(const std::string &source, const std::string &target, double weight)
    {
        if (!vertices.count(source) || !vertices.count(target))
        {
            std::cerr << "Edge cannot be created" << std::endl;
            return;
        }

        adjacencyList[source][target] = weight;
        adjacencyList[target][source] = weight;
    }

    void removeVertex(const std::string &vertex)
    {
        if (vertices.count(vertex) > 0)
        {
            vertices.erase(vertex);
            adjacencyList.erase(vertex);

            for (auto &entry : adjacencyList)
            {
                entry.second.erase(vertex);
            }
        }
        else
        {
            std::cerr << "Vertex " << vertex << " does not exist." << std::endl;
        }
    }

    void removeEdge(const std::string &source, const std::string &target)
    {
        auto itSource = adjacencyList.find(source);
        auto itTarget = adjacencyList.find(target);

        if (itSource != adjacencyList.end() && itTarget != adjacencyList.end())
        {
            itSource->second.erase(target);
            itTarget->second.erase(source);
        }
    }

    void changeEdgeWeight(const std::string &source, const std::string &target, double newWeight)
    {
        adjacencyList[source][target] = newWeight;
        adjacencyList[target][source] = newWeight;
    }

    void displayGraph() const
    {
        for (const auto &[node, neighs] : adjacencyList)
        {
            std::cout << node << " -> ";
            for (const auto &[n, w] : neighs)
            {
                std::cout << "(" << n << ", " << w << ") ";
            }
            std::cout << std::endl;
        }
    }

    Graph findMST() const
    {
        Graph mst;
        std::unordered_set<std::string> visitedVertices;
        std::priority_queue<std::pair<double, std::pair<std::string, std::string>>,
                            std::vector<std::pair<double, std::pair<std::string, std::string>>>,
                            std::greater<>>
            pq;

        const std::string &startVertex = *vertices.begin();
        pq.push({0.0, {startVertex, ""}}); // wieght, start, parent

        while (!pq.empty())
        {
            double currentWeight = pq.top().first;
            std::string currentVertex = pq.top().second.first;
            std::string parentVertex = pq.top().second.second;
            pq.pop();

            if (visitedVertices.count(currentVertex) > 0)
            {
                continue;
            }

            visitedVertices.insert(currentVertex);
            mst.addVertex(currentVertex);

            if (!parentVertex.empty())
            {
                mst.addEdge(parentVertex, currentVertex, currentWeight);
            }

            for (const auto &edge : adjacencyList.at(currentVertex))
            {
                if (!visitedVertices.count(edge.first))
                {
                    pq.push({edge.second, {edge.first, currentVertex}});
                }
            }
        }

        return mst;
    }

private:
    std::unordered_set<std::string> vertices;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> adjacencyList;
};

int main()
{
    Graph graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");

    graph.addEdge("A", "B", 1.0);
    graph.addEdge("A", "C", 2.0);
    graph.addEdge("B", "C", 3.0);
    graph.addEdge("C", "D", 4.0);

    std::cout << "Original Graph:\n";
    graph.displayGraph();

    Graph mst = graph.findMST();
    std::cout << "\nMinimum Spanning Tree (MST):\n";
    mst.displayGraph();

    return 0;
}
