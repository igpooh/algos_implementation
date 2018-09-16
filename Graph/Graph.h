#pragma once
#include <set>
#include <map>
#include <list>

class Graph
{
public:
    Graph() = default;
    ~Graph() = default;
    using node_id_t = std::uint32_t;
    using cost_t = std::uint32_t;

    void read_graph(std::string filename);

    struct DijkstraOutput
    {
        bool is_linked;
        cost_t overall_cost;
    };

    DijkstraOutput run_dijkstra(node_id_t in_node, node_id_t out_node);

private:
    std::set<node_id_t> nodes;
    std::map<node_id_t, std::list<std::pair<node_id_t, cost_t>>> relations;
};