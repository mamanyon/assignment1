#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    //______________rule of 5_____
    virtual ~Tree(); //destructor
    Tree(const Tree & otherT ); //copy constructor
    Tree(Tree && otherT); //move constructor
    Tree & operator=(const Tree &otherT); // copy assignment
    Tree & operator=(const Tree && otherT); //move assignment
    //_________________________________________

    virtual Tree *clone() const=0;

    const Tree& getChild(int) const;
    int NumberOfChildren();
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;



protected:
    int node;
    std::vector<Tree*> children;

private:
    void clear();
    void copyChildren(const Tree &other);

};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree *clone() const;
protected:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree *clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree *clone() const;
};

#endif
