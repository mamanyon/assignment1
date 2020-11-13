#include <vector>
#include "../h/Tree.h"
#include "../h/Session.h"
using namespace std;
//rule of 5

Tree::~Tree(){ //destructor
    int size = children.size();
    for(int i=0; i <size; i++)
        delete children[i];
}
Tree::Tree(int rootLabel) : node(rootLabel) {}; //constructor

//copy constructor
Tree::Tree(const Tree &otherT):node(otherT.node),children(std::vector<Tree*>(otherT.children.size())){
    copyChildren(otherT);
}
//copy assignment
Tree &Tree::operator=(const Tree &otherT) {
    if (this != &otherT) {
        node = 0;
        children.clear();
        //___________
        node = otherT.node;
        copyChildren(otherT);
    }
    return *this;
}
void Tree::copyChildren(const Tree &otherT) {
    int length = otherT.children.size();
    for (int i = 0; i < length; i++) {
        children[i] = otherT.children[i]->clone();
    }
}


//make another methode name copy .
//make clear function  otherT.node = 0;
//        otherT.children.clear();
Tree::Tree(Tree &&otherT) : node(otherT.node) { //move constructor
    int length = otherT.children.size();
    for (int i = 0; i < length; i++)
        children.push_back(otherT.children[i]);
    otherT.node = 0;
    otherT.children.clear();
}


Tree & Tree::operator=(const Tree &&otherT) { //move assignment
    if(this != &otherT){

    }

}


void Tree::addChild(const Tree &child) {
    Tree *newTree = child.clone();
    this->children.push_back(newTree);

}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    Tree *output;
    if(type = MaxRank)
        output= new MaxRankTree(rootLabel);
    if(type= Root)
        output= new RootTree(rootLabel);
    if(type = Cycle)
        output= new CycleTree(rootLabel,session.getCurrCycle());
    return output;
}

const Tree &Tree::getChild(int ind) const { //given an index returns the child in the specific index
    return *children[ind];
}

int Tree::NumberOfChildren() {
    return children.size();
}

void Tree::clear() {
node=0;

}



//____________________________________________________________________________________
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel) {//constructor
    this->currCycle=currCycle;
};

Tree * CycleTree::clone() const { //shallow copy
    return new CycleTree(*this);
}

int CycleTree::traceTree() {
    if(currCycle==0)return node;
    int depth= 0;

    return 0;
}


//_______________________________________________________________________________________
MaxRankTree::MaxRankTree(int rootLabel) : Tree(node) {};

int MaxRankTree::traceTree() {
int maximumRank = children.size();
for(int i=1; i<children.size(); i++) {
    int numChild = (children[i]->NumberOfChildren());
    if (maximumRank < numChild)
        maximumRank = i;
}
    return maximumRank;
}

Tree *MaxRankTree::clone() const{
    return new MaxRankTree(*this);
}

//__________________________________________________________________________________________
RootTree::RootTree(int rootLabel) : Tree(node) {};

int RootTree::traceTree() { return node;}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}