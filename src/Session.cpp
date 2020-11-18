#include <fstream>
#include <iostream>
#include "../json.hpp"
#include "../include/Session.h"

using namespace std;
using json = nlohmann::json;

//rule of 5
Session::Session(const std::string &path) : g(), treeType(Root), agents(),counterCurrCycle(0) {
    ifstream file("config1.json");
    json j;
    file >> j;
    g = Graph(j["graph"]);
    //for(auto& elem: j["agents"]){}

    treeType = TreeType(j["tree"]);
}

TreeType Session::getTreeType() const {
    return treeType;
}


void Session::addAgent(const Agent &agent) {
    Agent *newAgent = agent.clone();
    agents.push_back(newAgent);
}

//copy constructor
Session::Session(const Session &other) : g(other.getGraph()), treeType(other.getTreeType()), agents(),
                                         counterCurrCycle(other.getCurrCycle()) {
    for (int i = 0; i < other.agents.size(); i++) {

    }
}

int Session::getCurrCycle() const {
    return counterCurrCycle;
}

void Session::simulate() {
    bool over = false;
    while (!over) {
        int size = agents.size();
        for (int i = 0; i < size & !over; i++) {
            agents[i]->act(*this);
            if (g.TestTermination(&g)) {
                over = true;
            }
            counterCurrCycle++;
            g.printStatus();
        }

        vector<int> infected_vertices;
        for (int i = 0; i < g.getGraphSize(); i++) {
            if (g.getStatus(i) == sick)
                infected_vertices.push_back(i);
        }
        nlohmann::json j;
        j["infected"] = infected_vertices;
        j["graph"] = g.getEdges();
        std::ofstream o("output.json");
        o << j << std::endl;
    }
}

//destructor
Session::~Session() {
    for (auto &agent:agents)
        if (agent != nullptr)
            delete agent;
    agents.clear();
}

void Session::setGraph(const Graph &graph) { g = graph; }

const Graph &Session::getGraph() const {
    return g;
}

void Session::enqueueInfected(int a) {
    infectedQueue.push(a);
}

queue<int> Session::getInfectedQueue() const {
    return infectedQueue;
}

int Session::dequeueInfected() {
    int output = infectedQueue.front();
    infectedQueue.pop();
    return output;
}
