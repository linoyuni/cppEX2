#include <iostream>
#include <set>
#include <map>
#include <vector>
#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace ariel
{
    class Graph
    {
        private: 
            std::set<int> v;
            std::map <std::pair<std::size_t, std::size_t>, int> e;
            std::vector<std::vector<int>> adj;

        public:
            void loadGraph(std::vector<std::vector<int>>); //this function loads the graph
            std::string printGraph(); // this function prints the num of vertices and edges this graph has
            bool isDirected();
            std::set<int> getVs();
            std::map <std::pair<std::size_t, std::size_t>, int> getEdges();
            std::vector<std::vector<int>> getAdj();

            Graph operator+(const Graph& g) const;
            Graph &operator+=(const Graph& g);
            Graph &operator+();
            Graph operator-(const Graph& g) const;
            Graph &operator-=(const Graph& g);
            Graph &operator-();

            bool operator==(const Graph &) const;
            bool operator!=(const Graph & other)  const {return !(*this == other);};
            bool operator>(const Graph &)  const;
            bool operator<(const Graph &other) const {return other == *this;};
            bool operator>=(const Graph & other) const {return (*this > other) || (*this == other);};
            bool operator<=(const Graph & other) const {return (*this < other) || (*this == other);};;

            Graph operator++();
            Graph operator--();
            Graph operator++(int);
            Graph operator--(int);
            Graph operator*=(int n);
            Graph operator*(const Graph& g) const;
            Graph operator/=(int n);
            Graph operator/(int n const;

            friend std::ostream &operator<<(std::ostream &os, const Graph &g);
    };
}

#endif