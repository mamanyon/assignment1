#ifndef GRAPH_H_
#define GRAPH_H_
#include <queue>
#include <vector>
class Tree;
class Session;

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
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Tree *BFS(const Session &session , int root) const;
    void BFS_run(const Session &session , std::queue<Tree*>&q, std::vector<bool>&VisitedArr) const;
    void quarantine(int);
    int getGraphSize() const;


    bool TestTermination(Graph *pGraph);
    void printStatus();

private:
    std::vector<std::vector<int>> edges;
    std::vector<condition> status;

};

#endif
