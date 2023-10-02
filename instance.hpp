#ifndef AKWB3_INSTANCE_HPP
#define AKWB3_INSTANCE_HPP
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
using namespace std;
string instance = "3";

void display_vector(vector< vector < string > > &wektor)
{
    int i = 0;
    for(const auto& x: wektor)
    {
        cout << "\nSekwencja" << ++i << "\n";
        for(auto y: x)
            cout << y << " ";
    }
}

void display_vector(vector< vector < char > > &wektor)
{
    int i = 0;
    for(const auto& x: wektor)
    {
        cout << "\nSekwencja" << ++i << "\n";
        for(auto y: x)
            cout << y;
    }
}
void display_vector(vector< vector < int > > &wektor)
{
    int i = 0;
    for(const auto& x: wektor)
    {
        cout << "\nSekwencja" << ++i << "\n";
        for(auto y: x)
            cout << y << ' ';
    }
}

void load_vector(vector< vector < char > > &wektor)
{
    vector < char > seq;
    ifstream fh;
    fh.open("instances/fasta"+instance+".txt");
    string line;

    int i = 0;
    while ( getline (fh,line) )
    {
        if (line[0] == '>')
            continue;

        wektor.push_back(seq);

        for(auto a: line)
            wektor[i].push_back(a);
        i++;
    }
    fh.close();
}
void load_vector(vector< vector < int > > &wektor)
{
    ifstream qh;
    qh.open("instances/qual"+instance+".txt");
    string line;

    while ( getline (qh,line) )
    {
        if (line[0] == '>')
            continue;

        istringstream row(line);
        wektor.emplace_back(istream_iterator<int>(row), istream_iterator<int>());
    }
    qh.close();
}

void purge_when_quality_lower(vector< vector < char > > &nucs, vector< vector < int > > &quals, int min_qual)
{
    for(int vec = 0; vec < quals.size(); vec++)
    {
        for(int pos = 0; pos < quals[vec].size(); pos++)
        {
            if (quals[vec][pos] < min_qual) {
                quals[vec].erase(begin(quals[vec]) + pos);
                nucs[vec].erase(begin(nucs[vec]) + pos);
                pos--;
            }
        }
    }
}

void create_oligos(vector < vector < char > > &sequences, int word_size, vector < vector < string > > &oligos)
{
    vector < string > to_fill;
    string oligo_tmp;
    for(int seq = 0; seq < sequences.size(); seq++)
    {
        oligos.push_back(to_fill);
        for(int pos = 0; pos < sequences[seq].size() - (word_size - 1); pos++)
        {
            oligo_tmp = "";
            for(int character = 0; character < word_size; character++)
            {
                oligo_tmp += sequences[seq][pos+character];
            }
            oligos[seq].push_back(oligo_tmp);
        }
    }
}

#endif
