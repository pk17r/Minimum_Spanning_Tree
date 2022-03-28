C++ for C Programmers Part 1

Minimum Spanning Tree Algorithm using Prim Algorithm

Homework 3: Compute the minimum spanning tree for an inputted graph

Objective

Trees are an important subcategory of graphs. Trees such as binary trees and red-black trees are important data structures used throughout computer science. Again it is hoped that this topic is mostly review for active participants in this class.

This assignment requires the implementation of a minimum spanning tree (MST) algorithm for a weighted undirected graph (Graph). A spanning tree for a Graph is a tree that reaches all the nodes of the graph. The cost for such a spanning tree is the sum of all the edge costs (weights) in the spanning tree’s edge set. Over all possible spanning trees, the MST is the one with the least total cost (it may not be unique).

Two efficient methods will be explained in this week’s Module, namely Prim’s algorithm and Kruskal’s algorithm. Additionally, the assignment makes the following simplifying assumptions about the unweighted Graph:

1) Graph is connected. This assumption enables the following invariant: MST invariant states that the edge set for a MST must (i) consist of a set of (V-1) edges and (ii) no edge can create a cycle.

2) Edge weights may be zero or non-negative. Non-negative edge weights are not a requirement for constructing a MST, but may simplify our implementation.

3) Edge weights are NOT necessarily different.


Update your Homework 2 graph class to add two more methods. Add a constructor that can read in a graph from a file. The file format will be an initial integer that is the node size of the graph and the further values will be integer triples: (i, j, cost). See Sample Test Data here.

Implement either the Prim or Kruskal Minimum Spanning Tree Algorithm. These algorithms are similar in flavor to Dijkstra’s shortest path algorithm. Links to these algorithms are provided besides being explained in the videos.

http://en.wikipedia.org/wiki/Kruskal's_algorithm

http://en.wikipedia.org/wiki/Prim_algorithm 

http://en.wikipedia.org/wiki/Minimum_spanning_tree 

The output for MST should be the cost and the tree (the edges). 