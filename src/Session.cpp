#include <fstream>
#include <iostream>
#include "../json.hpp"
#include "../h/Session.h"

using namespace std;
using json = nlohmann::json;

//rule of 5
Session::Session(const std::string &path): g(), treeType(), agents() {
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

Graph Session::getGraph() const {
    return g;
}

void Session::addAgent(const Agent &agent) {

}

Session::Session(const Session& other):g(other.getGraph()),treeType(other.getTreeType()),agents(),counterCurrCycle(other.getCurrCycle()) {//copy constructor
    for(int i=0; i<other.agents.size() ; i++){
        Agent* newAgent = (other.agents[i])->clone();
        agents.push_back(newAgent);
    }
}

int Session::getCurrCycle() const {
    return counterCurrCycle;
}

void Session::simulate(){
    bool over = false;
    while(!over){
        cout << "________Round " << counterCurrCycle << "__________" << endl;
        vector<Agent*> agents_second(this->agents);
        for (Agent *agent: agents_second) {
            agent->act(*this);
        }
        if(Graph::TestTermination(&g)){
            over=true;
        }
        counterCurrCycle++;
        g.printStatus();
    }

    vector<int> infected_vertices;
    for(auto& agent: agents){
        if(Virus* v = dynamic_cast<Virus*>(agent)){
            infected_vertices.push_back((v->getNode()))
        }
    }
    nlohmann::json j;
    j["infected"] = infected_vertices;
    j["graph"] = g.getEdges();
    std::ofstream  o("output.json");
    o << j << std::endl;
}


Session::~Session() {
    for(auto &agent:agents)
        if(agent!= nullptr)delete agent;

    agents.clear();
}

void Session::setGraph(const Graph &graph) {g=graph;}
