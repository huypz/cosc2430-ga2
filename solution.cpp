#include <fstream>
#include <iostream>
#include <string>
#include <climits>
#include "ArgumentManager.h"
#include "BSTree.h"

using std::string;
using std::cout;

bool passed;
int** entries;  // two alternative indices for each entry
int n;
int* hash_table;

void place(const int& entry, const int& index_id, const int& count) {
    if (count == n) {
        passed = false;
        return;
    }
    //cout << entry << "|" << index_id << "|" << count << endl;
    if (hash_table[entries[entry][index_id]] != INT_MIN) {
        int displaced = hash_table[entries[entry][index_id]];
        hash_table[entries[entry][index_id]] = entry;
        place(displaced, (index_id + 1) % 2, count + 1);
    }
    else {
        hash_table[entries[entry][index_id]] = entry;
    }
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    std::ifstream ifs(am.get("input"));
    std::ofstream ofs(am.get("output"));


    int m;
    string input;
    getline(ifs, input, ' ');
    m = std::stoi(input);
    getline(ifs, input, '\n');
    n = std::stoi(input);
    //cout << "SIZE:" << n << endl;

    entries = new int*[m];
    for (int i = 0; i < m; i++)
        entries[i] = new int[2];

    hash_table = new int[n];
    for (int i = 0; i < n; i++)
        hash_table[i] = INT_MIN;

    passed = true;
    for (int i = 0; i < m; i++) {
        //cout << "ENTRY:" << i << endl;
        getline(ifs, input, ' ');
        int index1 = std::stoi(input);
        entries[i][0] = index1;
        getline(ifs, input, '\n');
        int index2 = std::stoi(input);
        entries[i][1] = index2;
        //cout << "indices:" << entries[i][0] << "|" << entries[i][1] << endl;
        place(i, 0, 0);
        //cout << "TABLE:";
        // for (int i = 0; i < n; i++)
        //     cout << hash_table[i] <<  " ";
        // cout << endl;
        if (!passed) {
            ofs << "Failed";
            return 0;
        }
    }
    ofs << "Passed\n";

    // Ignore blank lines
    while (getline(ifs, input) && input.size() <= 0);
    int k;
    k = std::stoi(input);

    BSTree* tree = new BSTree();
    while (k-- && getline(ifs, input)) {
        int employee = std::stoi(input);
        tree->addNode(employee);
    }
    //cout << "size:" << tree->size() << endl;
    int start, end;
    getline(ifs, input, ' ');
    end = std::stoi(input);
    getline(ifs, input, '\n');
    start = std::stoi(input);
    ofs << "Looking for: " << end << "\n";
    ofs << "Starting from: " << start << "\n";
    ofs << tree->track(tree->find(start), end) << "\n";
    tree->traverseAndPrint(tree->find(start), tree->find(end), ofs);

    ofs.flush();
    ofs.close();
    ifs.close();

    delete [] entries;
    delete hash_table;
    delete tree;

    return 0;
}