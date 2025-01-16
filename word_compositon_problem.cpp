#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <fstream>
using namespace std;

struct TrieNode {
    bool isEndOfWord;
    vector<TrieNode*> child;

    TrieNode() {
        isEndOfWord = false;
        child.resize(26, nullptr); 
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->child[index]) {
                curr->child[index] = new TrieNode();
            }
            curr = curr->child[index];
        }
        curr->isEndOfWord = true;
    }
bool search(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->child[index]) {
                return false;
            }
            curr = curr->child[index];
        }
        return curr->isEndOfWord;
    }
vector<string> getPrefixes(const string& word) {
        vector<string> prefixes;
        TrieNode* current = root;
        string pre;
        for (char c : word) {
            int index = c - 'a';
            if (!current->child[index]) {
                break;
            }
            pre += c;
            current = current->child[index];
            if (current->isEndOfWord) {
                prefixes.push_back(pre);
            }
        }
        return prefixes;
    }
};

class Solution {
public:
    Trie trie;
    queue<pair<string, string>> q; 
    void buildTrie(const string& filePath) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Error " << filePath << endl;
            exit(1); 
        }
        string word;
        while (getline(file, word)) {
            vector<string> prefixes = trie.getPrefixes(word);
            for (const string& prefix : prefixes) {
                q.push({word, word.substr(prefix.length())});
            }
            trie.insert(word);
        }

        file.close();
    }
    pair<string, string> findLongestCompoundWords() {
        string longestWord = "";
        int longestLength = 0;
        string secondLongestWord = "";

        while (!q.empty()) {
            pair<string, string> p = q.front();
            q.pop();
            string word = p.first;
            string suffix = p.second;

            if (trie.search(suffix)) {
                if (word.length() > longestLength) {
                    secondLongestWord = longestWord;
                    longestWord = word;
                    longestLength = word.length();
                }
            } else {
                vector<string> prefixes = trie.getPrefixes(suffix);
                for (const string& prefix : prefixes) {
                    q.push({word, suffix.substr(prefix.length())});
                }
            }
        }

        return make_pair(longestWord, secondLongestWord);
    }
};

int main() {
  Solution solinputfile1;
  Solution solinputfile2;
  clock_t start = clock();  

  solinputfile1.buildTrie("Input_01.txt"); 
  pair<string, string> result = solinputfile1.findLongestCompoundWords();
  clock_t end = clock();
  double duration = double(end - start) / double(CLOCKS_PER_SEC); 
//   cout << "Longest Compound Word: " << result.first << endl;
//   cout << "Second Longest Compound Word: " << result.second << endl;
//   cout << "Time taken to process file Input_01.txt : " << duration << " seconds" << endl << endl;

  solinputfile2.buildTrie("Input_02.txt"); 
  end = clock();
  result = solinputfile2.findLongestCompoundWords();
  duration = double(end - start) / double(CLOCKS_PER_SEC); 
  cout << "Longest Compound Word: " << result.first << endl;
  cout << "Second Longest Compound Word: " << result.second << endl;
  cout << "Time taken to process file Input_02.txt : " << duration << " seconds" << endl;

  return 0;
}