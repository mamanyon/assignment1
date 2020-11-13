#include <vector>
#include "../h/Graph.h"
#include "queue"
using namespace std;

    Graph::Graph(vector<vector<int>> matrix){
        int length=  matrix.size();
        for(int i=0; i<=length; i++){
            edges[i]= matrix[i];
        }
    }
    void Graph::infectNode(int nodeInd) {}
    std::vector<std::vector<int>> Graph::getEdges() const {return edges;}
    bool Graph::isInfected(int nodeInd){}

Graph::Graph() {}

bool Graph::TestTermination(Graph *pGraph) {
    return false;
}

void Graph::printStatus() {

}

Tree *BFS(const Session &session, int root) {
       Tree *newTree = Tree::createTree(session, root);
       int size = edges.size();
       bool *visited = new bool[size];
       for (int i = 0; i < size; i++)
           visited[i] = false;
       //create queue for bfs
       queue<int> queue;
       //Mark the curr node as visited and enqueue
       visited[root] = true;
       queue.push(root);


       while (!queue.empty()) {
           int currVertex = queue.front();
           queue.pop();

           for (i = edges[currVertex].begin(); i != adjLists[currVertex].end(); ++i) {
               int adjVertex = *i;
               if (!visited[adjVertex]) {
                   visited[adjVertex] = true;
                   queue.push_back(adjVertex);
               }


           }
       }
       return newTree;
   }


