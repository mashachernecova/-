#include <iostream>
#include <algorithm>
#include <bitset>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

FILE *f, *g;

struct Forest{
    int weight;
    int root;
};

struct Tree{
    int left;
    int right;
    int parent;
};

Forest forest[256];
Tree tree[530];
map <char, string>  codes;

void getmin(Forest used[], int sze, int &p1, int &p2) {
    p1 = 0, p2 = 0;
    for (int i = 0; i < sze + 1; i++) {
        if (used[p1].weight > used[i].weight) {
            p1 = i;
        }
    }
    if (p2 == p1){
        p2 = 1;
    }
    for (int i = 0; i < sze + 1; i++) {
        if (used[p2].weight > used[i].weight && i != p1) {
            p2 = i;
        }
    }
}

void encod(int pos, string str, vector <pair<int, char>> &alphabet) {
    if (tree[pos].left == -1 && tree[pos].right == -1) {
        char letter = alphabet[pos].second;
        codes[letter] = str;
        return;
    }
    encod(tree[pos].left, str + "0", alphabet);
    encod(tree[pos].right, str + "1", alphabet);
}

int main()
{
     f = fopen("input.txt", "rb");
     freopen("output.txt", "wb", stdout);
     int freq[256];
     memset (freq, 0, sizeof freq);
     char ch;
     while (fscanf(f, "%c", &ch) != -1) {
        freq[ch]++;
     }

     int size_forest = 0, size_tree = 0;
     for (int i = 0; i < 256; i++) {
        if (freq[i] > 0){
            forest[size_forest].weight = freq[i];
            forest[size_forest].root = size_forest;
            tree[forest[size_forest].root].right = -1;
            tree[forest[size_forest].root].left = -1;
            tree[forest[size_forest].root].parent = -1;
            size_forest++;
        }
     }

     int p1, p2;
     size_forest--;
     size_tree = size_forest;
     while (size_forest > 0) {
        getmin(forest, size_forest, p1, p2);
        size_tree++;
        tree[size_tree].left = forest[p1].root;
        tree[size_tree].right = forest[p2].root;
        tree[size_tree].parent = -1;
        tree[forest[p1].root].parent = size_tree;
        tree[forest[p2].root].parent = size_tree;
        forest[p1].weight = forest[p1].weight + forest[p2].weight;
        forest[p1].root = size_tree;
        forest[p2] = forest[size_forest];
        size_forest--;

     }
     size_tree++;
     tree[size_tree].left = forest[0].root;
     tree[size_tree].right = forest[0].root;
     tree[size_tree].parent = -1;

     for (int i = 0; i < size_tree; i++) {
        cout << tree[i].left << ' ' << tree[i].right << ' ' << tree[i].parent << endl;
     }

     vector <pair <int, char>> alphabet;
     for(int i = 0; i < 257; i++) {
        if (freq[i] > 0) {
            alphabet.push_back({freq[i], i});
        }
     }

     string s;
     encod(size_tree - 1, s, alphabet);

     for (auto it = codes.begin(); it != codes.end()--; it++) {
        cout << it -> first << ' ' << it -> second << endl;
     }
}
