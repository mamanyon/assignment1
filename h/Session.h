#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

class Agent; // ???

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    virtual ~Session(); //destructor
    Session(const Session& other); //copy constructor
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    int getCurrCycle() const;
    Graph getGraph() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int counterCurrCycle;
}

#endif
