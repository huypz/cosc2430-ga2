#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
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
    if (hash_table[entries[entry][index_id]] != INT_MIN) {
        int displaced = hash_table[entries[entry][index_id]];
        hash_table[entries[entry][index_id]] = entry;
        int dis_index_id = (entries[entry][index_id] == entries[displaced][0]) ? 1 : 0;
        place(displaced, dis_index_id, count + 1);
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
    string parsed_input;
    std::stringstream strs;
    while (getline(ifs, input) && input.size() <= 0);
    strs.clear();
    strs << input;
    getline(strs, parsed_input, ' ');
    m = std::stoi(parsed_input);
    getline(strs, parsed_input, '\n');
    n = std::stoi(parsed_input);

    entries = new int*[m];
    for (int i = 0; i < m; i++)
        entries[i] = new int[2];

    hash_table = new int[n];
    for (int i = 0; i < n; i++)
        hash_table[i] = INT_MIN;
    passed = true;

    for (int i = 0; i < m; i++) {
        getline(ifs, input);
        if (input.size() <= 0) {
            i--;
            continue;
        }
        strs.clear();
        strs << input;
        getline(strs, parsed_input, ' ');
        int index1 = std::stoi(parsed_input);
        entries[i][0] = index1;
        getline(strs, parsed_input, '\n');
        int index2 = std::stoi(parsed_input);
        entries[i][1] = index2;
        place(i, 0, 0);
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
    if (k <= 0) {
        delete [] entries;
        delete hash_table;
        return 0;
    }

    BSTree* tree = new BSTree();
    while (k && getline(ifs, input)) {
        if (input.size() <= 0) continue;
        int employee = std::stoi(input);
        tree->addNode(employee);
        k--;
    }

    // Ignore blank lines
    while (getline(ifs, input) && input.size() <= 0);
    strs.clear();
    strs << input;
    int start, end;
    getline(strs, parsed_input, ' ');
    end = std::stoi(parsed_input);
    getline(strs, parsed_input, '\n');
    start = std::stoi(parsed_input);
    ofs << "Looking for: " << end << "\n";
    ofs << "Starting from: " << start << "\n";
    BSTree::Node* start_p = tree->find(start);
    if (tree->find(start) == nullptr)
        start_p = tree->getRoot();
    ofs << tree->track(start_p, end) << "\n";
    tree->traverseAndPrint(start_p, tree->find(end), ofs);

    ofs.flush();
    ofs.close();
    ifs.close();

    delete [] entries;
    delete hash_table;
    delete tree;
    return 0;
}