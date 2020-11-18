#ifndef GRAPH_H_
#define GRAPH_H_
#include <queue>
#include <vector>
#include "Tree.h"
using namespace std;

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
    condition getStatus(int) const;
    void setStatus(int);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Tree *BFS(const Session &session , int root) const;
    void BFS_run(const Session &session , queue<Tree*>&q, vector<bool>&VisitedArr);
    void printStatus();
    int getGraphSize() const;
    bool TestTermination(Graph *pGraph);
    void quarantine(int);

private:
    std::vector<std::vector<int>> edges;
    vector<condition> status;

};

#endif
