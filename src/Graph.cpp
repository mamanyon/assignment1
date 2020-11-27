#include <vector>
#include "../include/Graph.h"
#include "queue"
#include "../include/Tree.h"
#include "../include/Session.h"
using namespace std;

Graph::Graph(vector<vector<int>> matrix) : edges(matrix), status(edges.size()) {
    int length = status.size();
    for(int i=0; i < length; i++)
        status[i]=healthy;
}

void Graph::infectNode(int nodeInd) {
    if(status[nodeInd] ==sick){
        return;
    }
    if (status[nodeInd] == carrier) {
        status[nodeInd] = sick;
    } else
        status[nodeInd] = carrier;
}

bool Graph::isInfected(int nodeInd) {
    if(status[nodeInd] == sick || status[nodeInd]== carrier)
        return true;
    else
        return false;
}

bool Graph::TestTermination(Graph *pGraph) {
    int length = edges.size();
    for (int i = 0; i < length; i++) {
        if (status[i] != healthy) {
            if(status[i] == carrier)
                return false;
            int neighbors = edges[i].size();
            for (int j = 0; j < neighbors; j++) {
                if (edges[i][j] == 1 && status[j] != sick) //is fully infected
                    return false;
            }
        }
    }
    return true;
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
    int length = edges.size();
    for (int i = 0; i < length; i++) {
        edges[a][i] = 0;
    }
    for (int i = 0; i < length; i++) {
        edges[i][a] = 0;
    }
}


void Graph::BFS_run(const Session &session, queue<Tree *> &que, vector<bool> &visitedArr) const {
    while (!que.empty()) {
        Tree * curr=que.front();
        int currVertex = (*curr).getRoot();
        que.pop();

        for (int i = 0; i < session.getGraph().getGraphSize(); i++) {
            int adjVertex = i;
            if(getEdges()[currVertex][adjVertex]==1) {
                if (!visitedArr[adjVertex]) {
                    visitedArr[adjVertex] = true;
                    Tree *child = Tree::createTree(session, adjVertex);
                    (curr)->addChild(*child);
                    que.push(curr->getChildren().back());
                    delete child;
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

Graph::Graph():edges(vector<vector<int>>()),status(vector<condition>()) {

}

//set vertex to carrier status
void Graph::setStatus(int i) {
    status[i] = carrier;
}



