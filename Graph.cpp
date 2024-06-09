#include "Graph.hpp"
#include <iostream>

//friend std::ostream &ariel::operator<<(std::ostream &os, const ariel::Graph &g)
//{
//    std::string s = "{";
//    for(int i=0; i<g.adj.size(); i++){
//        s+="{";
//        for(int j=0; j<g.adj.size()-1; j++){
//            s+=std::to_string(g.adj.at(i).at(j)) + ", ";
//        }
//        s+=std::to_string(g.adj.at(i).at(j)) + "}";
//    }
//    s+="}";
//    os << s;
//    return os;
//}

void ariel::Graph::loadGraph(std::vector<std::vector<int>> m)
{
    this->v.clear();
    this->e.clear();
    for (std::size_t i = 0; i < m.size(); i++)
    {
        if (m.at(i).size() != m.size())
        {
            throw std::invalid_argument("not enough v");
        }
    }

    this->adj = m;

    for (int i = 0; i < m.size(); i++)
    {
        this->v.insert(i);
    }
    for (std::size_t i = 0; i < m.size(); i++)
    {
        for (std::size_t j = 0; j < m.size(); j++)
        {
            if (m.at(i).at(j) != 0)
            {
                e[std::make_pair(i, j)] = m.at(i).at(j);
            }
        }
    }
}

bool ariel::Graph::isDirected()
{
    for (auto it = e.begin(); it != e.end(); ++it)
    {
        std::size_t u = it->first.first;
        std::size_t v = it->first.second;
        int weight = it->second;

        // Check if the reverse edge (v, u) exists with the same weight
        auto reverse_edge = e.find(std::make_pair(v, u));
        if (reverse_edge == e.end() || reverse_edge->second != weight)
        {
            // If the reverse edge doesn't exist or has a different weight, the graph is directed
            return true;
        }
    }
    // If all reverse edges exist with the same weight, the graph is undirected
    return false;
}

std::string ariel::Graph::printGraph()
{
    std::string s = "Graph with " + std::to_string(v.size()) + " vertices and " + std::to_string(e.size()) + " edges.\n";

    std::cout << "Graph with " << v.size() << " vertices and " << e.size() << " edges.\n";

    return s;
}

std::set<int> ariel::Graph::getVs()
{
    return v;
}

std::map<std::pair<std::size_t, std::size_t>, int> ariel::Graph::getEdges()
{
    return e;
}

std::vector<std::vector<int>> ariel::Graph::getAdj()
{
    return adj;
}

Graph ariel::Graph::operator+(const Graph& g) const{
    if(this->adj.size() != g.adj.size()){
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    Graph g1;
    g1.loadGraph(this->adj);
    for (std::size_t i = 0; i < g.adj.size(); i++)
    {
        for (std::size_t j = 0; j < g.adj.size(); j++)
        {
            g1.adj.at(i).at(j) += g.adj.at(i).at(j);
        }
    }
    return g1;
}

Graph &ariel::Graph::operator+=(const Graph& g){
    if(this->adj.size() != g.adj.size()){
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    for (std::size_t i = 0; i < g.adj.size(); i++)
    {
        for (std::size_t j = 0; j < g.adj.size(); j++)
        {
            this->adj.at(i).at(j) += g.adj.at(i).at(j);
        }
    }
    return *this;
}

Graph &ariel::Graph::operator+(){
    for (std::size_t i = 0; i < this->adj.size(); i++)
    {
        for (std::size_t j = 0; j < this->adj.size(); j++)
        {
            this->adj.at(i).at(j) *= 1;
        }
    }
    return *this;
}

Graph ariel::Graph::operator-(const Graph& g) const{
    if(this->adj.size() != g.adj.size()){
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    Graph g1;
    g1.loadGraph(this->adj);
    for (std::size_t i = 0; i < g.adj.size(); i++)
    {
        for (std::size_t j = 0; j < g.adj.size(); j++)
        {
            g1.adj.at(i).at(j) -= g.adj.at(i).at(j);
        }
    }
    return g1;
}

Graph &ariel::Graph::operator-=(const Graph& g){
    if(this->adj.size() != g.adj.size()){
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    for (std::size_t i = 0; i < g.adj.size(); i++)
    {
        for (std::size_t j = 0; j < g.adj.size(); j++)
        {
            this->adj.at(i).at(j) -= g.adj.at(i).at(j);
        }
    }
    return *this;
}

Graph &ariel::Graph::operator-(){
    for (std::size_t i = 0; i < this->adj.size(); i++)
    {
        for (std::size_t j = 0; j < this->adj.size(); j++)
        {
            this->adj.at(i).at(j) *= -1;
        }
    }
    return *this;
}

bool ariel::Graph::operator==(const Graph &g) const{
    if(this->v.size() != g.v.size() || this->e.size() != g.e.size()){
        return false;
    }
    for (std::size_t i = 0; i < g.adj.size(); i++)
    {
        for (std::size_t j = 0; j < g.adj.size(); j++)
        {
            if(this->adj.at(i).at(j) != g.adj.at(i).at(j)){
                return false;
            }
        }
    }
    return true;
}

bool ariel::Graph::operator!=(const Graph &g) const{
    return !(*this == g);
}

bool ariel::Graph::operator>(const Graph& g) const{
    if(this->e.size()<g.e.size() || this->v.size()<g.v.size()){
        return false;
    }
    if(*this == g){
        return false;
    }
    for(int i=0; i<=this->adj.size()-g.adj.size(); i++){
        for(int j=0; j<=this->adj.size()-g.adj.size(); j++){
            bool flag = true;
            for(int k=0; k<g.adj.size(); k++){
                for(int l=0; l<g.adj.size(); l++){
                    if(g.adj.at(k).at(l) != 0 && this->adj.at(i+k).at(j+l) == 0){
                        flag = false;
                        break;
                    }
                }
                if(!flag){
                    break;
                }
            }
            if(flag){
                return true;
            }
        }
    }
    return false;
}

bool ariel::Graph::operator>=(const Graph& g) const{
    return (*this > g) || (*this == g);
}

bool ariel::Graph::operator<(const Graph& g) const{
    return g >= *this;
}

bool ariel::Graph::operator<=(const Graph& g) const{
    return g > *this || g == *this;
}

Graph ariel::Graph::operator++(){
    for (std::size_t i = 0; i < this->adj.size(); i++)
    {
        for (std::size_t j = 0; j < this->adj.size(); j++)
        {
            if(this->adj.at(i).at(j) != 0) {
                this->adj.at(i).at(j)++;
            }
        }
    }
    return *this;
}

Graph ariel::Graph::operator--(){
    for (std::size_t i = 0; i < this->adj.size(); i++)
    {
        for (std::size_t j = 0; j < this->adj.size(); j++)
        {
            if(this->adj.at(i).at(j) != 0) {
                this->adj.at(i).at(j)--;
            }
        }
    }
    return *this;
}

Graph ariel::Graph::operator++(int){
    Graph g = *this;
    ++*this;
    return g;
}

Graph ariel::Graph::operator--(int){
    Graph g = *this;
    --*this;
    return g;
}

Graph ariel::Graph::operator*=(int n){
    for (std::size_t i = 0; i < this->adj.size(); i++)
    {
        for (std::size_t j = 0; j < this->adj.size(); j++)
        {
            this->adj.at(i).at(j) *= n;
        }
    }
    return *this;
}

Graph ariel::Graph::operator*(const Graph& g) const{
    if(this->adj.size() != g.adj.size()){
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    Graph g1;
    std::vector<std::vector<int>> m(this->adj.size(), std::vector<int>(this->adj.size(), 0));
    for(int i=0; i<this->adj.size(); i++){
        for(int j=0; j<this->adj.size(); j++){
            int sum = 0;
            for(int k=0; k<this->adj.size(); k++){
                sum += this->adj.at(i).at(k) * g.adj.at(k).at(j);
            }
            m.at(i).at(j) = sum;
        }
    }
    g1.loadGraph(m);
    return g1;
}

Graph ariel::Graph::operator/=(int n){
    for (std::size_t i = 0; i < this->adj.size(); i++)
    {
        for (std::size_t j = 0; j < this->adj.size(); j++)
        {
            this->adj.at(i).at(j) /= n;
        }
    }
    return *this;
}

Graph ariel::Graph::operator/(int n) const{
    Graph g = *this;
    g /= n;
    return g;
}

std::ostream &ariel::operator<<(std::ostream &os, const ariel::Graph &g)
{
    std::string s = "{";
    for(int i=0; i<g.adj.size(); i++){
        s+="{";
        for(int j=0; j<g.adj.size()-1; j++){
            s+=std::to_string(g.adj.at(i).at(j)) + ", ";
        }
        s+=std::to_string(g.adj.at(i).at(j)) + "}";
    }
    s+="}";
    os << s;
    return os;
}