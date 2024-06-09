#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "Graph.hpp"

namespace ariel
{
    class Algorithms
    {
    private:
        static size_t cycle_start;
        static size_t cycle_end;
        static bool bellmanFord(ariel::Graph &g, std::size_t s, std::vector<int>& d, std::vector<std::size_t>& p, std::size_t& lp);
        static void relax(std::size_t u, std::size_t v, int w, std::vector<int>& d, std::vector<std::size_t>& p);
        static bool isContainsCycleUtil(int v, std::vector<bool> visited, std::vector<int> &parent, std::vector<std::vector<int>>& adj);
        static bool isContainsCycleUtil(int v, std::vector<bool> visited, std::vector<bool> &recStack, std::vector<std::vector<int>>& adj,std::vector<int> &parent);

    public:
        static bool isConnected(Graph& g);
        static std::string shortestPath(Graph& g,int start,int end);
        static std::string isContainsCycle(Graph& g);
        static std::string isBipartite(Graph& g);
        static bool negativeCycle(Graph& g);
    };
}


