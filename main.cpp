#include <iostream>
#include <math.h>

using namespace std;

class Node {
public:
    Node() {

    }

    Node *up = nullptr;
    Node *down = nullptr;
};

Node *generateTree(int size) {
    Node *topBuf = new Node();
    Node *cursor = new Node();
    cursor->up = topBuf;
    topBuf->down = new Node();
    for (int i = 2; i <= size; i++) {
        topBuf = cursor;
        cursor = new Node();
        cursor->up = topBuf;
        for (int t = 0; t < i - 1; t++) {
            topBuf->down = new Node();
            topBuf->down->up = topBuf->up->down;
            topBuf = topBuf->down->up;
        }
        topBuf->down = new Node();
    }
    return cursor;
}

char *copyText(char *source, int length) {
    char *result = new char[length];
    for (int i = 0; i < length; i++)
        result[i] = source[i];
    return result;
}

int countCorrectBrackets(Node *tree, int countSelectBrackets, char *sequance, int countBrackets) {
    if (countSelectBrackets == countBrackets) {
        cout << sequance << endl;
        delete[]sequance;
        return 1;
    }
    char *copy = sequance;
    if (tree->up != nullptr && tree->down != nullptr)
        copy = copyText(sequance, countBrackets);
    int up = 0;
    int down = 0;
    if (tree->up) {
        copy[countSelectBrackets] = '(';
        up = countCorrectBrackets(tree->up, countSelectBrackets + 1, copy, countBrackets);
    }
    if (tree->down) {
        sequance[countSelectBrackets] = ')';
        down = countCorrectBrackets(tree->down, countSelectBrackets + 1, sequance, countBrackets);
    }
    if (tree->down == nullptr && tree->up == nullptr) {
        delete[] sequance;
        return 0;
    }
    return up + down;
}

int countCorrectBrackets(int count){
    double result = 1;
    for(double i=2;i<=count;i++){
        result*= (2*(2*i-1))/(i+1);
    }
    return (int) result;
}

int main() {
    int countOpenBrackets = 10;
    cout <<  "enter count of brackets _";
    cin >> countOpenBrackets;
    Node *tree = generateTree(countOpenBrackets);
    char *sequance = new char[countOpenBrackets * 2];
    int result = countCorrectBrackets(tree, 0, new char[countOpenBrackets * 2], countOpenBrackets * 2);
    cout << "Tree :: \t\t\t\t"<<result << endl;
    cout << "Recurrent formula :: \t" << countCorrectBrackets(countOpenBrackets);
    return 0;
}