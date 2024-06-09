#include "Algorithms.hpp"
#include <stack>
#include <set>
#include <limits>
#include <iostream>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <climits>

size_t ariel::Algorithms::cycle_start = -1;
size_t ariel::Algorithms::cycle_end = -1;


bool ariel::Algorithms::isConnected(Graph &g)
{
    std::vector<std::vector<int>> adj = g.getAdj();
    size_t n = adj.size();
    size_t v = 0;
    std::set<int> visited;
    std::stack<size_t> current;
    bool d = g.isDirected();
    current.push(v); // changed from *v.begin() which is the

    while (!current.empty())
    {
        size_t curr = current.top();
        visited.insert(curr);
        current.pop();

        for (size_t i = 0; i < n; i++)
        {
            if (adj[curr][i] != 0 && visited.find(i) == visited.end())
            {
                current.push(i);
                visited.insert(i);
            }
        }
    }

    if (visited.size() != n)
    {
        return false;
    }

    // If it's a directed graph, reverse the edges and rechech from the same vertex
    if (d)
    {
        // create reversed adjacency matrix
        std::vector<std::vector<int>> adjT(n, std::vector<int>(n, 0));
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                adjT[i][j] = adj[j][i];
            }
        }

        visited.clear();
        current.push(v);

        while (!current.empty())
        {
            size_t curr = current.top();
            visited.insert(curr);
            current.pop();

            for (size_t i = 0; i < n; i++)
            {
                if (adjT[curr][i] != 0 && visited.find(i) == visited.end())
                {
                    current.push(i);
                    visited.insert(i);
                }
            }
        }
    }
    return visited.size() == n;
}
// check if the reversed graph is connected

void ariel::Algorithms::relax(std::size_t u, std::size_t v, int w, std::vector<int> &d, std::vector<std::size_t> &p)
{
    if (d[v] > d[u] + w)
    {
        d[v] = d[u] + w;
        p[v] = u;
    }
}

bool ariel::Algorithms::bellmanFord(ariel::Graph &g, std::size_t s, std::vector<int> &d, std::vector<std::size_t> &p, std::size_t &lp)
{
    for (long i = 0; i < g.getVs().size(); i++)
    {
        d.insert(d.begin() + i, __INT_MAX__);
        p.insert(p.begin() + i, __INT_MAX__);
    }

    d[s] = 0;

    for (int i = 0; i < g.getVs().size() - 1; i++)
    {
        for (const auto &pr : g.getEdges())
        {
            relax(pr.first.first, pr.first.second, pr.second, d, p);
        }
    }
    for (const auto &pr : g.getEdges())
    {
        if (d[pr.first.second] > d[pr.first.first] + pr.second)
        {
            lp = pr.first.second;
            return false;
        }
    }
    return true;
}

std::string ariel::Algorithms::shortestPath(ariel::Graph &g, int start, int end)
{
    // Check if start and end vertices are valid
    if (start < 0 || end < 0 || start >= g.getVs().size() || end >= g.getVs().size())
    {
        throw std::invalid_argument("Vertex out of range");
    }

    // Initialize distance and parent arrays
    std::vector<int> d(g.getVs().size(), INT_MAX);
    std::vector<std::size_t> p(g.getVs().size(), -1);

    // Perform Bellman-Ford algorithm
    d[start] = 0;
    for (int i = 0; i < g.getVs().size() - 1; ++i)
    {
        for (const auto &pr : g.getEdges())
        {
            if (d[pr.first.first] != INT_MAX && d[pr.first.first] + pr.second < d[pr.first.second])
            {
                d[pr.first.second] = d[pr.first.first] + pr.second;
                p[pr.first.second] = pr.first.first;
            }
        }
    }

    // Check for negative cycles
    for (const auto &pr : g.getEdges())
    {
        if (d[pr.first.first] != INT_MAX && d[pr.first.first] + pr.second < d[pr.first.second])
        {
            return "-1";
        }
    }

    // Reconstruct the shortest path
    std::vector<std::size_t> path;
    std::size_t current = end;
    while (current != static_cast<std::size_t>(start))
    {
        if (current == -1)
        {
            return "-1";
        }
        path.push_back(current);
        current = p[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    // Construct the string representation of the shortest path
    std::string result;
    for (std::size_t i = 0; i < path.size(); ++i)
    {
        result += std::to_string(path[i]);
        if (i != path.size() - 1)
        {
            result += "->";
        }
    }

    return result;
}


bool ariel::Algorithms::negativeCycle(ariel::Graph &g)
{
    std::vector<int> d;
    std::vector<std::size_t> p;
    std::string s;
    std::size_t lp = std::numeric_limits<int>::max();
    if (!bellmanFord(g, 0, d, p, lp))
    {
        std::size_t p1 = p[lp];
        s += std::to_string(lp) + ",";
        while (p[p1] != lp)
        {
            s += std::to_string(p1) + ",";
            int t = p[p1];
            p1 = t;
        }
        s += std::to_string(p1) + "\n";
        // std::cout << s;
        return true;
    }
    return false;
}

std::string ariel::Algorithms::isContainsCycle(ariel::Graph &g)
{
    std::vector<std::vector<int>> adj = g.getAdj();
    size_t n = adj.size();
    std::vector<bool> visited(n, false);
    std::vector<int> parent(n, -1);

    if (g.isDirected())
    {
        std::vector<bool> recStack(n, false);
        for (size_t i = 0; i < n; i++)
        {
            if (isContainsCycleUtil(i, visited, recStack, adj, parent))
            {
                size_t v1 = cycle_end;
                size_t v2 = cycle_start;


                std::string s = "->" + std::to_string(v1);
                s+= "->" + std::to_string(v2);
                while (parent[v1] != v2)
                {
                    v1 = parent[v1];
                    // if v2 has and edge to v1 this is the smallest cycle
                    if (adj[v2][v1] != 0)
                    {
                        s.insert(0, "->" + std::to_string(v1));
                        break;
                    }
                    s.insert(0,"->" + std::to_string(v1));
                }

                s.insert(0, "The cycle is: " + std::to_string(v2));

                return s;
            }
        }

        return "-1";
    }

    for (size_t i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (isContainsCycleUtil(i, visited, parent, adj))
            {
                // return the path of the cycle
                size_t v1 = i;
                size_t v2 = i;

                std::string s = std::to_string(v1);
                s.insert(0, "->");
                while (parent[v1] != v2)
                {
                    v1 = parent[v1];
                    s.insert(0, std::to_string(v1)).insert(0, "->");
                }

                s.insert(0, "The cycle is: " + std::to_string(v2));

                return s;
            }
        }
    }

    return "-1";
}

std::string ariel::Algorithms::isBipartite(ariel::Graph &g)
{
    std::vector<int> color(g.getVs().size(), -1); // Initialize color array
    std::vector<std::vector<int>> adj = g.getAdj();
    size_t n = adj.size();
    std::vector<size_t> setA;
    std::vector<size_t> setB;
    std::queue<size_t> q;

    for (size_t i = 0; i < adj.size(); i++)
    {
        if (color[i] == -1)
        {
            q.push(i);
            color[i] = 1;
            setA.push_back(i);
        }

        while (!q.empty())
        {
            size_t u = q.front();
            q.pop();

            for (size_t v = 0; v < n; v++)
            {
                if (adj[u][v] != 0 && color[v] == -1)
                {
                    color[v] = 1 - color[u];
                    if (color[v] == 1)
                    {
                        setA.push_back(v);
                    }
                    else
                    {
                        setB.push_back(v);
                    }

                    q.push(v);
                }
                else if (adj[u][v] != 0 && color[v] == color[u])
                {
                    // std::cout << "0" << std::endl; // Not bipartite
                    return "0";
                }
            }
        }
    }

    std::string s;

    // Print the bipartite sets
    s += "The graph is bipartite: A={";
    for (int j = 0; j < setA.size(); ++j)
    {
        s += std::to_string(setA[j]);
        if (j < setA.size() - 1)
        {
            s += ", ";
        }
    }
    s += "}, B={";
    for (int j = 0; j < setB.size(); ++j)
    {
        s += std::to_string(setB[j]);
        if (j < setB.size() - 1)
        {
            s += ", ";
        }
    }
    s += "}";
    // std::cout << s << std::endl;
    return s;
}

bool ariel::Algorithms::isContainsCycleUtil(int v, std::vector<bool> visited, std::vector<int> &parent, std::vector<std::vector<int>> &adj)
{
    visited[v] = true;
    for (size_t i = 0; i < adj[v].size(); i++)
    {
        if (adj[v][i] != 0)
        {
            if (!visited[i])
            {
                parent[i] = v;
                if (isContainsCycleUtil(i, visited, parent, adj))
                {
                    return true;
                }
            }
            else if (parent[v] != i)
            {
                parent[i] = v;
                cycle_start = i;
                cycle_end = v;
                return true;
            }
        }
    }
    return false;
}

bool ariel::Algorithms::isContainsCycleUtil(int v, std::vector<bool> visited, std::vector<bool> &recStack, std::vector<std::vector<int>> &adj, std::vector<int> &parent)
{
    if (!visited[v])
    {
        visited[v] = true;
        recStack[v] = true;

        for (size_t i = 0; i < adj[v].size(); i++)
        {
            if (adj[v][i] != 0)
            {
                if (!visited[i] && isContainsCycleUtil(i, visited, recStack, adj, parent))
                {
                    parent[i] = v;
                    return true;
                }
                if (recStack[i])
                {
                    parent[i] = v;
                    cycle_start = i;
                    cycle_end = v;
                    return true;
                }
            }
        }
    }
    recStack[v] = false;
    return false;
}