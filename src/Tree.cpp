#include <vector>
#include "../include/Tree.h"
#include "../include/Session.h"

using namespace std;
//rule of 5
//____________


//destructor
Tree::~Tree() {
    clear();
}

//constructor
Tree::Tree(int rootLabel) : node(rootLabel) {};

//copy constructor
Tree::Tree(const Tree &otherT) : node(otherT.node), children(std::vector<Tree *>(otherT.children.size())) {
    copyChildren(otherT);
}

//copy assignment
Tree &Tree::operator=(const Tree &otherT) {
    if (this != &otherT) {
        // node = 0;
        children.clear();
        //___________
        node = otherT.node;
        copyChildren(otherT);
    }
    return *this;
}

//_________________________
//copy & clear private functions
void Tree::copyChildren(const Tree &otherT) {
    int length = otherT.children.size();
    for (int i = 0; i < length; i++) {
        children[i] = otherT.children[i]->clone();
    }
}

void Tree::clear() {
    int length = children.size();
    for (int i = 0; i < length; i++)
        delete children[i];
}

//_________________________
Tree::Tree(Tree &&otherT) : node(otherT.node), children(otherT.children) { //move constructor
    int length = otherT.children.size();
    for (int i = 0; i < length; i++)
        children.push_back(otherT.children[i]);
    otherT.node = 0;
    otherT.children.clear();
}

//need to check if ok \/\/\/\/\/\/
//move assignment
Tree &Tree::operator=(const Tree &&otherT) {
    if (this != &otherT) {
        clear();
        this->node = otherT.node;
        children = otherT.children;
        //clear ??
    }
    return *this;
}


void Tree::addChild(const Tree &child) {
    Tree *newTree = child.clone();
    this->children.push_back(newTree);

}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    Tree *output;
    if (type == MaxRank)
        output = new MaxRankTree(rootLabel);
    if (type == Root)
        output = new RootTree(rootLabel);
    if (type == Cycle)
        output = new CycleTree(rootLabel, session.getCurrCycle());
    return output;
}

const Tree &Tree::getChild(int ind) const { //given an index returns the child in the specific index
    return *children[ind];
}

int Tree::NumberOfChildren() {
    return children.size();
}

int Tree::getRoot() {
    return node;
}


//____________________________________________________________________________________
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel) {//constructor
    this->currCycle = currCycle;
};

Tree *CycleTree::clone() const { //shallow copy
    return new CycleTree(*this);
}

int CycleTree::traceTree() {
    if (currCycle == 0)return node;
    int cycles = currCycle;
    CycleTree *tree = this;
    while (cycles != 0) {
        tree->children[0];
        cycles = cycles - 1;
    }
    return tree->node;

}


//_______________________________________________________________________________________
MaxRankTree::MaxRankTree(int rootLabel) : Tree(node) {};

int MaxRankTree::traceTree() {
    vector<int> indexAndChildren = tracing();
    return indexAndChildren[0];

}

vector<int> MaxRankTree::tracing() {
    vector<int> output(node, NumberOfChildren());
    for (unsigned int i = 0; i < NumberOfChildren(); i++) {
        vector<int> Compare = ((MaxRankTree *) (children[i]))->tracing();
        if (Compare[1] > output[1]) {
            output[0] = Compare[0];
            output[1] = Compare[1];
        }
    }
    return output;
}

Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

//__________________________________________________________________________________________
RootTree::RootTree(int rootLabel) : Tree(node) {};

int RootTree::traceTree() { return node; }

Tree *RootTree::clone() const {
    return new RootTree(*this);
}
