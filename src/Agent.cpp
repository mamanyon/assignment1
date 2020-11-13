#include "../h/Agent.h"
Agent::Agent() {};
void Agent::act(Session &session) {}

Agent::~Agent() {};
ContactTracer::ContactTracer() {};
void ContactTracer::act(Session &session) {
    Tree *bfs = session.getGraph().BFS(session, );
    int Remove = bfs->traceTree();
    Graph* updated = session.getGraph();
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
};
Virus::Virus(int nodeInd):nodeInd(nodeInd) {}

void Virus::act(Session &session) {
Tree *bfs = session.getGraph().BFS(session,nodeInd);
int Remove = bfs->traceTree();
Graph* updated = session.getGraph();


delete bfs;
}

Agent *Virus::clone() const {
    return new Virus(*this);
}
