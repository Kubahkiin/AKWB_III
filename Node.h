#ifndef AKWB3_NODE_H
#define AKWB3_NODE_H

#include<iostream>
#include<vector>

using namespace std;

class Node {
public:
    Node(int seqId, int position, string oligo){
        this->seq_id = seqId;
        this->position = position;
        this->oligo = oligo;

    }
    int getSeqId() const {
        return seq_id;
    }
    int getPosition() const {
        return position;
    }
    string getOligo() const {
        return oligo;
    }
    void addNeighbor(Node* neighbor) {
        neighbors.push_back(neighbor);
    }
    vector<Node*> getNeighbors() const {
        return neighbors;
    }

private:
    int seq_id;
    int position;
    string oligo;
    vector<Node*> neighbors;
};


#endif //AKWB3_NODE_H
