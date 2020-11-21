#include <vector>
#include "../include/Graph.h"
#include "queue"
#include "../include/Tree.h"
#include "../include/Session.h"
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


void Graph::BFS_run(const Session &session, queue<Tree *> &que, vector<bool> &visitedArr) const {
    while (!que.empty()) {
        Tree * curr=que.front();
        int currVertex = (*curr).getRoot();
        que.pop();

        for (int i = 0; i <= session.getGraph().getGraphSize(); i++) {
            int adjVertex = i;
            if(getEdges()[currVertex][adjVertex]==1) {
                if (!visitedArr[adjVertex]) {
                    visitedArr[adjVertex] = true;
                    Tree *child = Tree::createTree(session, adjVertex);
                    (curr)->addChild(*child);
                    que.push(child);
                }
            }


        }
    }
}

Tree *Graph::BFS(const Session &session, int root) const {
    Tree *newTree = Tree::createTree(session, root);
    int size = session.getGraph().getGraphSize();
    vector<bool> visited(size);
    for (int i = 0; i < size; i++)
        visited[i] = false;
    //create queue for bfs
    queue<Tree *> que ;
    //Mark the curr node as visited and enqueue
    visited[root] = true;
    que.push(newTree);
    this->BFS_run(session,que,visited);
    return newTree;
}



