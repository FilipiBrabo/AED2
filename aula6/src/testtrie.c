#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include "../include/tn_trie.h"

using namespace std;


void print_search(tn_trie_node* root, string key){
    search(root, key)? cout << "Encontrou: " :  cout << "Nao encontrou: "; 
    cout << key << "\n";
}

int main () {
    tn_trie_node *root = new_node();
    string line, file_name = "", url;
    
    while(1) {
        cout << "Digite o nome do arquivo de entrada:" << endl;
        cin >> file_name;
        file_name = "../in/" + file_name;
        
        ifstream myfile(file_name.c_str());
        if (myfile.is_open()) {
            
            while (myfile >> line) {
                insert(root, line);
            }
            myfile.close();
            break;
            
        } else {
            cout << "Arquivo não encontrado/não existe.\n" 
                << "Certifique-se de que ele está no diretório \"in\"" << endl;
        }
    }
    
    //print_all(root);
    cout << "Digite a url:" << endl;
    cin >> url;
    tn_suggest(root, url.c_str());
    
    return 0;
}

/*
int main() 
{ 
    string keys[] = {"exemplo.com", "url123.org", 
                     "567.abcdefghijklamnopqrstuvwxzyz.com", 
                    "klsdjuewori", "www.dominio.net", "outro.exemplo.com", 
                     "567890.url.org", "teste.url.com.br" }; 
    int n = 8; 
  
    tn_trie_node *root = new_node(); 
  
    for (int i = 0; i < n; i++){
        insert(root, keys[i]); 
    }

    string s;

    while (cin >> s) {
        insert(root, s);
    } 
  
    print_search(root, keys[0]);
    print_search(root, keys[2]);
    print_search(root, "nao.existe.0123456789");
    print_search(root, "outro.erro");
    cout << "++++++++++++++++" << endl;
    //print_all(root);

    cout << "++++++++++++++++" << endl;
    tn_suggest(root, "pub.");

} */