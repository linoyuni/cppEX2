Ex2 - Operators

2. Graph Union

operator+

Description:
Combines the edges of two graphs G and H.

Returns:
A new graph that is the union of the two input graphs.

operator+=

Description:
Adds the edges of graph H to graph G.

Returns:
The modified graph G with the edges of H added.

operator+ (unary)

Description:
A no-op for the graph (it essentially returns the graph itself).

Returns:
The same graph without any modification.

2. Graph Intersection

Description:
The intersection of two graphs G and H is not directly implemented in the provided code.

3. Graph Difference

operator-

Description:
Removes the edges of graph H from graph G.

Returns:
A new graph that is the difference of the two input graphs.

operator-=

Description:
Removes the edges of graph H from graph G.

Returns:
The modified graph G with the edges of H removed.

4. Graph Complement

operator- (unary)

Description:
Inverts the presence of edges in the graph.

Returns:
The modified graph with the presence of edges inverted.

5. Graph Equality

operator==

Description:
Checks if two graphs are equal.

Returns:
true if the graphs are equal, false otherwise.

operator!=

Description:
Checks if two graphs are not equal.

Returns:
true if the graphs are not equal, false otherwise.

6. Graph Comparison

operator>

Description:
Checks if graph  G has more edges and vertices than graph  H.

Returns:
true if graph G is greater than graph  H, false otherwise.

operator>=

Description:
Checks if graph G is greater than or equal to graph H.

Returns:
true if graph 
G is greater than or equal to graph H, false otherwise.

operator<

Description:
Checks if graph G has fewer edges and vertices than graph H.

Returns:
true if graph G is less than graph H, false otherwise.

operator<=

Description:
Checks if graph G is less than or equal to graph H.

Returns:
true if graph G is less than or equal to graph H, false otherwise.

7. Graph Increment

operator++

Description:
Increments all edges of the graph by 1.

Returns:
The modified graph with all edges incremented by 1.

operator++(int)

Description:
Increments all edges of the graph by 1 (postfix).

Returns:
A copy of the graph before it was incremented.

8. Graph Decrement

operator--

Description:
Decrements all edges of the graph by 1.

Returns:
The modified graph with all edges decremented by 1.

operator--(int)

Description:
Decrements all edges of the graph by 1 (postfix).

Returns:
A copy of the graph before it was decremented.

9. Scalar Multiplication

operator*=

Description:
Multiplies the adjacency matrix of the graph by a scalar.

Returns:
The modified graph with its adjacency matrix multiplied by the scalar.

operator*(const Graph&)

Description:
Multiplies the adjacency matrices of two graphs.

Returns:
A new graph with its adjacency matrix being the product of the two input graphs' adjacency matrices.

10. Scalar Division

operator/=

Description:
Divides the adjacency matrix of the graph by a scalar.

Returns:
The modified graph with its adjacency matrix divided by the scalar.

operator/(int)

Description:
Divides the adjacency matrix of the graph by a scalar.

Returns:
A new graph with its adjacency matrix divided by the scalar.

11. Output Operator

operator<<

Description:
Outputs the adjacency matrix of the graph to an ostream.

Returns:
The ostream with the graph's adjacency matrix.