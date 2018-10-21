//
// Created by Khyber on 10/18/2018.
//

#ifndef TRIE_H
#define TRIE_H

struct TrieNode;
typedef struct TrieNode TrieNode;
struct TrieNode {
    char c;
    
};

typedef struct Trie {
    TrieNode *node;
} Trie;

#endif // TRIE_H
