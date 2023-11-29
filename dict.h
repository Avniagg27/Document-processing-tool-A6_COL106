#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct node{
    int count;
    vector<node*> bachha;
    node();
    bool EndofWord;
};

class helperdict{
    public:
        helperdict();
        ~helperdict();
        node* root;
        void insert_word(const string& word);
        int get_word_count(const string& word);
};

class Dict {
public:
    Dict();
    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, std::string sentence);
    int get_word_count(std::string word);
    void dump_dictionary(std::string filename);

private:
    helperdict* help;
};
