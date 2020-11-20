#include <fstream>
#include <iostream>
#include "../json.hpp"
#include "../include/Session.h"

using namespace std;
using json = nlohmann::json;

//rule of 5
//constructor
Session::Session(const std::string &path): g({}), treeType(), agents(),counterCurrCycle(0) {
    ifstream file("config1.json");
    json j;
    file >> j;
    g = Graph(j["graph"]);
    treeType = TreeType(j["tree"]);

    vector<int> CarryNodes = {};
    int CarryNode;
    Agent* agent;
    for(auto& elem: j["agents"]){
        if(elem.front() == "C")
            agent= new ContactTracer();
        else {
            CarryNode = elem.at(1);
            agent = new Virus(CarryNode);
            CarryNodes.push_back(CarryNode);
        }
        addAgent(*agent);
    }
}

//empty constructor
Session::Session(): g({}), treeType(), agents(),counterCurrCycle(0) {}

//copy constructor
Session::Session(const Session& other):g(other.g),treeType(other.treeType()),
                                       agents(std::vector<Agent *>()),counterCurrCycle(other.counterCurrCycle),
                                       infected(other.infected){//copy constructor
    for (auto agent : other.agents) {
        agents.push_back(agent->clone());
    }
}

//copy assignment operator
const Session &Session::operator=(const Session &other) {
    if (this != &other) {
        clear();

        g = other.g;
        treeType = other.treeType;
        infected = other.infected;
        counterCurrCycle = other.counterCurrCycle;

        agents.clear();
        for(auto& agent: other.agents){
            agents.push_back(agent->clone());
        }
    }
    return *this;
}
/*
Session *session = new Session();
for (auto *agent: agents) {
    if (Virus *v = dynamic_cast<Virus *>(agent)) {
        Virus v1(*v);
        session->addAgent(v1);
    } else if (ContactTracer *c = dynamic_cast<ContactTracer *>(agent)) {
        ContactTracer c1(*c);
        session->addAgent(c1);
    }
}
session->setGraph(g);
session->treeType= getTreeType();
session->counterCurrCycle = getCurrCycle();
session->infected = infected;

return session;
}
*/

//move constructor
Session::Session(Session &&other): g(other.g),treeType(other.treeType),
                                   agents(other.agents),counterCurrCycle(other.counterCurrCycle),
                                   infected(other.infected){

    other.agents.clear();
}

//move assignment operator
const Session &Session::operator=(Session &&other): {
if(this != &other) {
clear();

g = other.g;
treeType = other.treeType();
counterCurrCycle = other.counterCurrCycle;
agents = other.agents;
infected = other.infected;

other.agents.clear();
}

return *this;
}

//destructor
Session::~Session() {
    clear();
}

void Session::clear(){
    for(auto& agent: agents){
        if(agent != nullptr) {
            delete agent;
            agent = nullptr;
        }
    }
}

TreeType Session::getTreeType() const {
    return treeType;
}


void Session::addAgent(const Agent &agent) {
    Agent *newAgent = agent.clone();
    agents.push_back(newAgent);
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

void Session::createOutput() {
    json outputJson;

    std::vector<int> *infected;
    for (int i = 0; i < g.getGraphSize(); i++) {
        if(g.isInfected()) {
            infected->push_back(i);
        }
    }
    outputJson["graph"] = g.getEdges();
    outputJson["infected"] = *infected;

    std::ofstream outputFile("output.json");
}
