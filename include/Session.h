#ifndef SESSION_H_
#define SESSION_H_
#include <queue>
#include <vector>
#include <string>
#include "Graph.h"
#include "Agent.h"

class Agent; // ???

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string &path); //constructor
    Session(); //empty constructor
    Session(const Session &other); //copy constructor
    const Session &operator=(const Session &other); //copy assignment operator
    Session(Session&& other); //move constructor
    const Session &operator=(Session &&other); //move assignment operator
    virtual ~Session(); //destructor
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    int getCurrCycle() const;
    const Graph& getGraph() const;
    std::queue<int> getInfectedQueue() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int counterCurrCycle;
    std::queue<int> infectedQueue;


    void clear();
};

#endif
