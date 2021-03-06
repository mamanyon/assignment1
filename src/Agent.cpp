#include "../include/Agent.h"

Agent::Agent() {};

void Agent::act(Session &session) {}

Agent::~Agent() {};

ContactTracer::ContactTracer() {};

void ContactTracer::act(Session &session) {
    if (!session.getInfectedQueue().empty()) {
        int infected = session.dequeueInfected();
        Tree *bfs = session.getGraph().BFS(session, infected);
        int Remove = bfs->traceTree();
        Graph updated = session.getGraph();

        updated.quarantine(Remove);
        session.setGraph(updated);

        delete bfs;

    }
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}


void Virus::act(Session &session) {
    Graph k = session.getGraph();
    if (k.getStatus(nodeInd) == carrier) {
        session.enqueueInfected(nodeInd);
        k.infectNode(nodeInd);
    }
    for (int i = 0; i < k.getGraphSize(); i++) {

        if (k.getStatus(i) == healthy && k.getEdges()[nodeInd][i] == 1) {
            Virus v(i);
            session.addAgent(v);
            k.infectNode(i);
            break;
        }
    }
    session.setGraph(k);

}

Agent *Virus::clone() const {
    return new Virus(*this);
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {
}

