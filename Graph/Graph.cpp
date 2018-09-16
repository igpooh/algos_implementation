#include "Graph.h"
#include <climits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

constexpr auto ENDLESS_PATH = std::numeric_limits<std::uint32_t>::max();

void Graph::read_graph(std::string filename)
{
    std::string s;
    std::ifstream file(filename);

    while (std::getline(file, s))
    {
        std::istringstream iss(s);

        node_id_t in_node, out_node;
        cost_t cost;
        try
        {
            iss >> in_node >> out_node >> cost;
        }
        catch (...)
        {
            throw;
        }
        relations[in_node].push_back(std::make_pair(out_node, cost));
        nodes.insert(in_node);
        nodes.insert(out_node);
    }

    file.close();
}

Graph::DijkstraOutput Graph::run_dijkstra(node_id_t in_node, node_id_t out_node)
{
    std::vector<std::vector<int >> w;
    auto n = nodes.size();

    std::vector<bool> visited(n, false);
    std::vector<cost_t> D(n, ENDLESS_PATH);

    auto node_it = relations.find(in_node);
    if (node_it == relations.end())
    {
        throw std::runtime_error("No in node found");
    }
    auto relatives = node_it->second;
    for (const auto& relative : relatives)
    {
        D[relative.first] = relative.second;
    }

    D[in_node] = 0;
    visited[in_node] = true;

    node_id_t index = 0;
    for (auto i = 0u; i < n; i++)
    {
        auto min = ENDLESS_PATH;
        for (auto j = 0u; j < n; j++)
        {
            if (!visited[j] && D[j]<min)
            {
                min = D[j];
                index = j;
            }
        }

        visited[index] = true;
        const auto index_it = relations.find(index);
        if (index_it == relations.end())
        {
            continue;
        }

        for (const auto relative : index_it->second)
        {
            if (!visited[relative.first] && relative.second != ENDLESS_PATH && D[index] != ENDLESS_PATH
                && (D[index] + relative.second < D[relative.first]))
            {
                D[relative.first] = D[index] + relative.second;
            }
        }
    }
    DijkstraOutput out = { D[out_node] != ENDLESS_PATH, D[out_node] };
    return out;
}


