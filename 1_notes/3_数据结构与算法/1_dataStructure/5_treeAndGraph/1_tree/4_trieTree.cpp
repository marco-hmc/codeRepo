#include <iostream>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
  unordered_map<char, TrieNode *> children;
  bool isEndOfWord;

  TrieNode() { isEndOfWord = false; }
};

class Trie {
private:
  TrieNode *root;

public:
  Trie() { root = new TrieNode(); }

  void insert(string word) {
    TrieNode *current = root;
    for (char c : word) {
      if (current->children.find(c) == current->children.end()) {
        current->children[c] = new TrieNode();
      }
      current = current->children[c];
    }
    current->isEndOfWord = true;
  }

  bool search(string word) {
    TrieNode *current = root;
    for (char c : word) {
      if (current->children.find(c) == current->children.end()) {
        return false;
      }
      current = current->children[c];
    }
    return current->isEndOfWord;
  }

  bool startsWith(string prefix) {
    TrieNode *current = root;
    for (char c : prefix) {
      if (current->children.find(c) == current->children.end()) {
        return false;
      }
      current = current->children[c];
    }
    return true;
  }
};

int main() {
  Trie trie;

  // 插入单词
  trie.insert("apple");
  trie.insert("banana");
  trie.insert("orange");

  // 验证单词是否存在
  cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not Found")
       << endl;
  cout << "Search 'banana': " << (trie.search("banana") ? "Found" : "Not Found")
       << endl;
  cout << "Search 'orange': " << (trie.search("orange") ? "Found" : "Not Found")
       << endl;
  cout << "Search 'grape': " << (trie.search("grape") ? "Found" : "Not Found")
       << endl;

  // 验证前缀是否存在
  cout << "Starts with 'app': " << (trie.startsWith("app") ? "Yes" : "No")
       << endl;
  cout << "Starts with 'ban': " << (trie.startsWith("ban") ? "Yes" : "No")
       << endl;
  cout << "Starts with 'ora': " << (trie.startsWith("ora") ? "Yes" : "No")
       << endl;
  cout << "Starts with 'gr': " << (trie.startsWith("gr") ? "Yes" : "No")
       << endl;

  return 0;
}