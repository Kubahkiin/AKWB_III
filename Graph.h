#ifndef AKWB3_GRAPH_H
#define AKWB3_GRAPH_H

#include "Node.h"
#include <cstdlib>

class Graph {
public:
    Graph(vector < vector < char > > &sequences, int word_size) {
        vector < Node* > to_fill;
        string oligo_tmp;
        for(int seq = 0; seq < sequences.size(); seq++) {
            sequences_of_nodes.push_back(to_fill);
            for(int pos = 0; pos < sequences[seq].size() - (word_size - 1); pos++) {
                oligo_tmp = "";
                for(int character = 0; character < word_size; character++) {
                    oligo_tmp += sequences[seq][pos + character];
                }
                addNode(seq, pos, oligo_tmp, sequences_of_nodes[seq]);
            }
        }
    }

    void addNode(int seqId, int position, string oligo, vector < Node* > &nodes) {
        Node* node = new Node(seqId,position,oligo);
        nodes.push_back(node);
    }

//    void purge_when_quality_lower_class_editon(vector< vector < int > > &quals, int min_qual)
//    {
//        for(int vec = 0; vec < quals.size(); vec++)
//        {
//            for(int pos = 0; pos < quals[vec].size(); pos++)
//            {
//                if (quals[vec][pos] < min_qual) {
//                    quals[vec].erase(begin(quals[vec]) + pos);
//                    sequences_of_nodes[vec].erase(begin(sequences_of_nodes[vec]) + pos);
//                    pos--;
//                }
//            }
//        }
//    }

    void connectNodes(int max_distance) {
        int distance = 0;
        for(int seq = 0; seq < sequences_of_nodes.size()-1; seq++) {
            for(int pos = 0; pos < sequences_of_nodes[seq].size(); pos++) {
                Node* node = sequences_of_nodes[seq][pos];
                for(int seq2 = seq; seq2 < sequences_of_nodes.size(); seq2++) {
                    if (seq == seq2)
                        continue;
                    for(int pos2 = 0; pos2 < sequences_of_nodes[seq2].size(); pos2++) {
                        Node* node2 = sequences_of_nodes[seq2][pos2];
                        distance = abs(node->getPosition() - node2->getPosition());
                        if (distance > max_distance){
                            continue;
                        }
                        if (node->getOligo() == node2->getOligo()) {
                            addEdge(node, node2);
                        }
                    }
                }
            }
        }
    }

    void addEdge(Node* node1, Node* node2) {
        node1->addNeighbor(node2);
        node2->addNeighbor(node1);
    }

    void findMotive() {
        Node* candidate;
        vector < Node* > candidate_neighbors;
        vector < Node* > motive;
        for(int seq = 0; seq < sequences_of_nodes.size(); seq++) {
            for(int pos = 0; pos < sequences_of_nodes[seq].size(); pos++) {
                candidate = sequences_of_nodes[seq][pos];
                candidate_neighbors = candidate->getNeighbors();
                if (candidate_neighbors.size() < sequences_of_nodes.size() - 1)
                    continue;
                motive.push_back(candidate);
                cout << "\nTestowanie kandydata " << candidate->getOligo() << " z sekwencji nr "
                     << candidate->getSeqId() << ":\n";
                for (int seqId = 0; seqId < sequences_of_nodes.size(); seqId++) {
                    if (candidate->getSeqId() == seqId)
                        continue;
                    cout << "Szukanie reprezentanta sekwencji: " << seqId << "...";
                    for (Node *neighbor: candidate_neighbors) {
                        if (neighbor->getSeqId() == seqId) {
                            cout << " Jest!\n";
                            cout << "\t-> " << neighbor->getOligo() << " z sekwencji nr " << neighbor->getSeqId()
                                 << " na pozycji " << neighbor->getPosition() << "\n";
                            motive.push_back(neighbor);
                            break;
                        }
                    }
                    if (motive.size() != seqId + 1) {
                        cout << "Zly kandydat!\n";
                    }
                }
                if (motive.size() == sequences_of_nodes.size()) {
                    cout << "Znaleziono motyw:\n";
                    display_motive(motive);
                    return;
                }
                cout << "Szukam innego kandydata...\n";
                motive.clear();
            }
            if (motive.size() == sequences_of_nodes.size()) {
                cout << "Znaleziono motyw:\n";
                display_motive(motive);
                return;
            }
            cout << "Szukam kandydata w innej sekwencji...\n";
            motive.clear();

        }
        if (motive.size() == sequences_of_nodes.size()) {
            cout << "Znaleziono motyw:\n";
            display_motive(motive);
            return;
        }
        cout << "Brak motywu.\n";
        motive.clear();
    }

    void display_motive(vector < Node* > motive) {
        for (Node* node: motive) {
            cout << node->getOligo() << " w sekwencji " << node->getSeqId() << " na pozycji " << node->getPosition()+1 << "\n";
        }
    }


    vector < vector < Node* > >getSequences_of_nodes() const {
        return sequences_of_nodes;
    }
    void display_nodes() {
        int i = 0;
        for(const auto& sequence: sequences_of_nodes) {
            cout << "\nSekwencja" << ++i << "\n";
            for(auto node: sequence)
                cout << node->getOligo() << " ";
        }
    }

private:
    vector < vector< Node* > > sequences_of_nodes;
};


#endif //AKWB3_GRAPH_H
