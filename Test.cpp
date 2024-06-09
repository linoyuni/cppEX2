#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

TEST_CASE("Test graph multiplication by scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    g1 *= -2;
    vector<vector<int>> expectedGraph = {
        {0, -2, 0},
        {-2, 0, -2},
        {0, -2, 0}};
    ariel::Graph g2;
    g2.loadGraph(expectedGraph);
    CHECK(g1.printGraph() == g2.printGraph());
}


TEST_CASE("Plus With Valid Graphs") {
    ariel::Graph g1, g2;
    std::vector<std::vector<int>> m1 = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    std::vector<std::vector<int>> m2 = {{1, 0, 1}, {0, 1, 0}, {1, 0, 1}};
    g1.loadGraph(m1);
    g2.loadGraph(m2);
    ariel::Graph g3 = g1 + g2;
    std::vector<std::vector<int>> expected = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    ASSERT_EQ(g3.getAdj(), expected);
}

//TEST(GraphTest, OperatorPlusWithInvalidGraphs) {
//ariel::Graph g1, g2;
//std::vector<std::vector<int>> m1 = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
//std::vector<std::vector<int>> m2 = {{1, 0}, {0, 1}};
//g1.loadGraph(m1);
//g2.loadGraph(m2);
//ASSERT_THROW(g1 + g2, std::invalid_argument);
//}
//
//TEST(GraphTest, OperatorEqualWithEqualGraphs) {
//ariel::Graph g1, g2;
//std::vector<std::vector<int>> m = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
//g1.loadGraph(m);
//g2.loadGraph(m);
//ASSERT_TRUE(g1 == g2);
//}
//
//TEST(GraphTest, OperatorEqualWithNonEqualGraphs) {
//ariel::Graph g1, g2;
//std::vector<std::vector<int>> m1 = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
//std::vector<std::vector<int>> m2 = {{1, 0, 1}, {0, 1, 0}, {1, 0, 1}};
//g1.loadGraph(m1);
//g2.loadGraph(m2);
//ASSERT_FALSE(g1 == g2);
//}