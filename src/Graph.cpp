#include <vector>
#include "../include/Graph.h"
#include "queue"

using namespace std;

Graph::Graph(vector<vector<int>> matrix) : edges(matrix), status(edges.size()) {
    for(int i=0; i < status.size(); i++)
        status[i]=healthy;
}

void Graph::infectNode(int nodeInd) {
    if (status[nodeInd] == carrier) {
        status[nodeInd] == sick;
    } else
        status[nodeInd] == carrier;
}

bool Graph::isInfected(int nodeInd) {
    if(status[nodeInd] == sick | status[nodeInd]== carrier)
        return true;
    else
        return false;
}

bool Graph::TestTermination(Graph *pGraph) {
    bool terminate = true;
    for (int i = 0; i < pGraph->getGraphSize() & terminate; i++) {
        if (status[i] != sick) //is fully infected?
            terminate=false;
    }
    // need to check if there's a virus in a c.c.



    return terminate;
}

void Graph::printStatus() {

}


void Graph::BFS_run(const Session &session, queue<Tree *> &que, vector<bool> &visitedArr) {
    while (!que.empty()) {
        int currVertex = que.front()->getRoot();
        que.pop();

        for (int i = 0; i <= i; i++) {
            int adjVertex = *i;
            if (!visitedArr[adjVertex]) {
                visitedArr[adjVertex] = true;
                Tree *child = Tree::createTree(session, adjVertex);
                Tree::addChild(child);
                que.push(adjVertex);
            }


        }
    }
}

condition Graph::getStatus(int a) const {
    return status[a];
}

std::vector<std::vector<int>> Graph::getEdges() const {
    return edges;
}

int Graph::getGraphSize() const {
    int size = getEdges().size();
    return size;
}

void Graph::quarantine(int a) {
    for (int i = 0; i < edges.size(); i++) {
        edges[a][i] = 0;
    }
    for (int i = 0; i < edges.size(); i++) {
        edges[i][a] = 0;
    }
}


Tree *BFS(const Session &session, int root) {
    Tree *newTree = Tree::createTree(session, root);
    int size = getGraphSize();
    vector<bool> visited(size);
    for (int i = 0; i < size; i++)
        visited[i] = false;
    //create queue for bfs
    queue<Tree *> *que = new ::queue<Tree *>;
    //Mark the curr node as visited and enqueue
    visited[root] = true;
    que->push(newTree);
    que->front()->BFS_run(session, *que, visited);
    delete que;
    return newTree;


}



