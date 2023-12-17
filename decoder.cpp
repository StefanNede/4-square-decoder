#include <bits/stdc++.h>
#include <cstdlib>
#include <map>
#include "trigrams.hpp"

#define ll long long
#define nL endl
#define mp make_pair
#define pb push_back
#define umap unordered_map

using namespace std;

const string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

string fourSquareDecode(string cipherText, string key1, string key2) {
    string resText;
    vector<string> pairs;
    for (int i=0; i<cipherText.length(); i+=2) {
        pairs.pb(cipherText.substr(i, 2));
    }

    for (auto pair : pairs) {
        char c1 = pair[0];
        char c2 = pair[1];

        int coor1 [2] = {(floor(key1.find(c1)/5)), (key1.find(c1) % 5)};
        int coor2 [2] = {(floor(key2.find(c2)/5)), (key2.find(c2) % 5)};
        // int coor1 [2] = {0,1};
        // int coor2 [2] = {0,1};

        int decryptedCoor1 [2] = {coor1[0], coor2[1]};
        int decryptedCoor2 [2] = {coor2[0], coor1[1]};

        char decryptedLetter1 = alphabet[decryptedCoor1[0]*5 + decryptedCoor1[1]];
        char decryptedLetter2 = alphabet[decryptedCoor2[0]*5 + decryptedCoor2[1]];

        resText += (string(1, decryptedLetter1) + decryptedLetter2);
    }
    
    return resText;
}

float trigramFitness(string s) {
    float score = 0;
    for (int i=0; i<s.length()-2; i++) {
        score += trigrams[s.substr(i, 3)];
    }
    return score;
}

string swap_two(string s)
{
    int B = rand()%25;
    int C = rand()%25;
    char temp = s[B];
    s[B] = s[C];
    s[C] = temp;
    return s;
}

int main() {
    // contains the genetic algorithm for the four square decoder
    string cipherText = "hello world";
    string bestKey1 = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    string bestKey2 = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    string bestDecode = fourSquareDecode(cipherText, bestKey1, bestKey2);
    float bestScore = trigramFitness(bestDecode);
    int counter = 0;
    cout << "starting decoding - this may take a few minutes" << endl;
    cout << "starting fitness: " << bestScore << endl;

    while (counter < 10000) {
        cout << "current best keys: " << bestKey1 << ", " << bestKey2 << endl;
        string childKey1, childKey2;
        childKey1 = swap_two(bestKey1);
        childKey2 = swap_two(bestKey2);
        string interDecoded = fourSquareDecode(cipherText, childKey1, childKey2);
        float interScore = trigramFitness(interDecoded);

        if ((interScore > bestScore) || ((interScore > bestScore-10) && (rand()%19 + 1) == 1)) {
            bestKey1 = childKey1;
            bestKey2 = childKey2;
            bestDecode = interDecoded;
            bestScore = interScore;
            counter = 0;
        } else {
            counter++;
        }
    }
    cout << bestDecode << endl;
    cout << "Keys: " << bestKey1 << ", " << bestKey2 << endl;
    return 0;
}