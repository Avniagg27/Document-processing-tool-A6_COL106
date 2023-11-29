#include "dict.h"

string toLowerCase(string input) {
    for (char &c : input) {
        c = tolower(c); 
    }
    return input;
}

node::node(){
    count = 0;
    bachha = vector<node*>(128,NULL);
    EndofWord = false;
}

helperdict::helperdict(){
    root = new node();
}

helperdict::~helperdict(){
    delete root;
}

void helperdict::insert_word(const string& word){
    if(root==NULL){
        return;
    }
    node* curr = root;
    for(char c: word){
        int index = static_cast<int>(c);
        if(curr->bachha[index] ==NULL){
            curr->bachha[index] = new node();
        }
        curr = curr->bachha[index];
    }
    curr->count++;
    curr->EndofWord = true;
}

int helperdict::get_word_count(const string& word){
    if(root==NULL){
        return 0;
    }
    node* curr = root;
    for(char c: word){
        int index = static_cast<int>(c);
        if(curr->bachha[index] ==NULL){
            return 0;
        }
        curr = curr->bachha[index];
    }
    if(curr!= NULL && curr->EndofWord){
        return curr->count;
    }
    else{
        return 0;
    }
}

// void dump_trie(node* node, string word, ofstream& outFile){
//     if(node->count>0){
//         outFile<<word<<", "<<node->count<<endl;
//     }

//     for(int i =0; i<128; i++){
//         if(node->bachha[i] != NULL){
//             dump_trie(node->bachha[i], word+char(i), outFile);
//         }
//     }
// }

void dump_trie(node* root, string word, ofstream& outFile) {
    vector<pair<node*, string>> stk;
    stk.push_back({root, ""});

    while (!stk.empty()) {
        pair<node*, string> currentPair = stk.back();
        stk.pop_back();
        node* currentNode = currentPair.first;
        string currentWord = currentPair.second;

        if (currentNode->count > 0) {
            outFile << currentWord << ", " << currentNode->count << endl;
        }

        for (int i = 0; i < 128; i++) {
            if (currentNode->bachha[i] != NULL) {
                stk.push_back({currentNode->bachha[i], currentWord + char(i)});
            }
        }
    }
}

Dict::Dict(){
    help = new helperdict();
}

Dict::~Dict(){
    delete help;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    string separators = " .,-:!\"'()?—[]“”‘’˙;@";
    string word = "";
    int word_start = 0;

    for(int i = 0; i<sentence.length(); i++){
        char curr_char = sentence[i];
        if(separators.find(curr_char) != string::npos){
            word = sentence.substr(word_start, i-word_start);
            word_start = i+1;
            if(!word.empty()){
                word = toLowerCase(word);
                help->insert_word(word);
            }
        }
    }
    word = sentence.substr(word_start);
    if(!word.empty()){
        word = toLowerCase(word);
        help->insert_word(word);
    }
}

int Dict::get_word_count(string word){
    if(help== NULL){
        return -1; 
    }
    return help->get_word_count(word);
}

void Dict::dump_dictionary(string filename){
    ofstream outFile(filename);
    dump_trie(help->root, "", outFile);
    outFile.close();
    return;
}
