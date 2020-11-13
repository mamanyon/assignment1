#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"

enum condition{
    healthy,
    sick,
    carrier
};
class Graph{

public:
    Graph();
    Graph(std::vector<std::vector<int>> matrix);
    std::vector<std::vector<int>> getEdges() const;
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Tree *BFS(const Session &session , int root);
    void printStatus();

    static bool TestTermination(Graph *pGraph);
private:
    std::vector<std::vector<int>> edges;

};

#endif
