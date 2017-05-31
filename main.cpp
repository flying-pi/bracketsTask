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

int getAlghorithmBrackets(int open, int close, int total) {
    if (open == 0)
        return 0;
    int result = 1;
    for (open - 1; open > 0; open--) {
        result += open * getAlghorithmBrackets(open, close - 1, total);
    }
}

int countCorrectBrackets(Node *tree, int countSelectBrackets, int countBrackets) {
    if (countSelectBrackets == countBrackets) {
        return 1;
    }
    int up = 0;
    int down = 0;
    if (tree->up) {
        up = countCorrectBrackets(tree->up, countSelectBrackets + 1, countBrackets);
    }
    if (tree->down) {
        down = countCorrectBrackets(tree->down, countSelectBrackets + 1, countBrackets);
    }
    if (tree->down == nullptr && tree->up == nullptr) {
        return 0;
    }
    return up + down;
}

int countCorrectBrackets(int count) {
    double result = 1;
    for (double i = 2; i <= count; i++) {
        result *= (2 * (2 * i - 1)) / (i + 1);
    }
    return (int) result;
}

int recursiveCacheTest = 0;
int recursionStep = 0;
int recursiceFunCall = 0;

int countBracketsRecursion(int open, int close, int **cache) {
    int result = 0;
    int forkResult = 0;
    int forksCache = 0;

    recursiceFunCall++;

    for (int i = 1; i < open; i++) {
        int forkCount = open - i + close;
        if (cache[i][forkCount] > 0) {
            recursionStep++;
            result = cache[i][forkCount];
//            cout << "adding from cache \t " << i << ":" << forkCount << "\t" << forkResult << endl;
            recursiveCacheTest++;
            continue;
        }
        forksCache = 0;
        for (int j = 0; j < forkCount; j++) {
            recursionStep++;
            if (cache[i][j] > 0) {
                forksCache = cache[i][j];
                recursiveCacheTest++;
                continue;
            }
            forksCache += countBracketsRecursion(i, j, cache);
            cache[i][j] = forksCache;
        }
        result += forksCache;
        cache[i][forkCount] = result;

    }
    return result;
}

int simpleCache = 0;
int simpleStep = 0;

int countBracketsWithoutRecursion(int size, int **cache) {
    int open = size - 1, close = 1, top = 0, right = 0, wayLength = 1;
    bool *way = new bool[size * 2];
    do {
        simpleStep++;
        if ((right = (close > 0 ? cache[open][close - 1] : 0)) == -1) {
            close--;
            way[wayLength++] = true;
        } else if ((top = (open > 0 ? cache[open - 1][close + 1] : 0)) == -1) {
            open--;
            close++;
            way[wayLength++] = false;
        } else {
            simpleCache++;
            cache[open][close] = top + right;
//            cout << "trace :: \t" << open << ":" << close << "\t" << cache[open][close] << endl;
            if (way[--wayLength]) {
                close++;
            } else {
                open++;
                close--;
            }
        }
    } while (cache[size - 1][1] <= 0);
    delete[]way;
    return cache[size - 1][1];
}

int getBrecetsBySquance(int num) {
    int *nums = new int[num + 1];
    nums[0] = 1;
    nums[1] = 1;
    for (int i = 2; i <= num; i++) {
        for (int j = 1; j < i; j++)
            nums[j] += nums[j - 1];
        nums[i] += nums[i - 1];
    }
    return nums[num];
}

int getBrecetsWithCache(int count, bool isUserRecursion) {
    if (count == 0)
        return 0;
    int cacheSize = count + 1;
    int **cache = new int *[cacheSize];
    for (int i = 0; i < cacheSize; i++) {
        cache[i] = new int[cacheSize];
        for (int j = 0; j < cacheSize; j++)
            cache[i][j] = -1;
    }

    for (int i = 0; i < cacheSize; i++) {
        cache[1][i] = i + 1;
        cache[0][i] = 1;
    }

    int result = 0;
    if (isUserRecursion)
        result = countBracketsRecursion(count, 0, cache);
    else
        result = countBracketsWithoutRecursion(count, cache);
    return result;

}

int main() {

    simpleCache = 0;
    recursiveCacheTest = 0;

    simpleStep = 0;

    recursionStep = 0;
    recursiceFunCall = 0;

    int countOpenBrackets = 10;
    cout << "enter count of brackets _";
    cin >> countOpenBrackets;
    Node *tree = generateTree(countOpenBrackets);
//    int result = countCorrectBrackets(tree, 0,  countOpenBrackets * 2);
//    cout << "Tree :: \t\t\t\t\t\t" << result << endl;
//    cout << "Recurrent formula :: \t\t\t" << countCorrectBrackets(countOpenBrackets) << endl;
    cout << "Cached alg with recursion :: \t" << getBrecetsWithCache(countOpenBrackets, true) << endl;
    cout << "Cached alg without recursion:: \t" << getBrecetsWithCache(countOpenBrackets, false) << endl;
    cout << "Using sequance:: \t\t\t\t" << getBrecetsBySquance(countOpenBrackets) << endl;

    cout << endl << endl << "\tnormal cache :: " << simpleCache << "\n\trecursion cache :: " << recursiveCacheTest;

    cout << endl << endl << "\tnormal step :: " << simpleStep << "\n\trecursion steps :: " << recursionStep
         << "\trecursion call ::" << recursiceFunCall;
    return 0;
}
