#ifndef __TN_TRIE_H__
#define __TN_TRIE_H__
// a-z OR 0-9 OR '.'
#define ALPHABET_LENGTH 37

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

typedef struct tn_trie_node {
	struct tn_trie_node* children[ALPHABET_LENGTH];

	/* true caso esse no seja o no final de uma palavra*/
	bool is_end_of_word;
} tn_trie_node;

//typedef struct tn_trie_node tn_trie_node;

tn_trie_node *new_node();
int insert(tn_trie_node* root, string key);
bool search(tn_trie_node *root, string key);
void print_all(tn_trie_node* root);
void tn_suggest(tn_trie_node* root, string query);

#endif
