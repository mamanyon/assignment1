#include <vector>
#include "../h/Graph.h"
#include "queue"

using namespace std;

    Graph::Graph(vector<vector<int>> matrix):edges(matrix),status(edges.size()){
    }
    void Graph::infectNode(int nodeInd) {}
    bool Graph::isInfected(int nodeInd){}

Graph::Graph() {}

bool Graph::TestTermination(Graph *pGraph) {
    return false;
}

void Graph::printStatus() {

}


void Graph::BFS_run(const Session &session, queue<Tree *> &que, vector<bool> &visitedArr) {
    while (!que.empty()) {
        int currVertex = que.front()->getRoot();
        que.pop();

        for (int i =0; i<=i; i++) {
            int adjVertex = *i;
            if (!visitedArr[adjVertex]) {
                visitedArr[adjVertex] = true;
                Tree *child= Tree::createTree(session, adjVertex);
                Tree::addChild(child);
                que.push(adjVertex);
            }


        }
    }
    return newTree;
}

condition Graph::getStatus(int a) const {
    return status[a];
}

void Graph::setStatus(int a) {
        if(status[a]== carrier) {
            status[a] == sick;
        }
        else
            status[a] == carrier;
}

std::vector<std::vector<int>> Graph::getEdges() const {
    return edges;
}

int Graph::getGraphSize() const {
        int size= getEdges().size();
    return size;
}

void Graph::quarantine(int a) {
    for (int i = 0; i <edges.size() ; i++) {
        edges[a][i]=0;
    }
    for (int i = 0; i < edges.size(); i++) {
        edges[i][a]=0;
    }
}


Tree *BFS(const Session &session, int root) {
       Tree *newTree = Tree::createTree(session, root);
       int size = getGraphSize();
       vector <bool> visited(size);
       for (int i = 0; i < size; i++)
           visited[i] = false;
       //create queue for bfs
       queue<Tree*> *que = new ::queue<Tree*>;
       //Mark the curr node as visited and enqueue
       visited[root] = true;
       que->push(newTree);
       que->front()->BFS_run(session,*que , visited);
       delete que;
       return newTree;


   }



