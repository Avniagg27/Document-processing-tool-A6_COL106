// Do NOT add any other includes
#include "search.h"

string toLowerCase(string input);
vector<int> offsearch(string pattern, vector<int> lps ,string curr_sen);

SearchPair::SearchPair() : indval(4, 0){};

SearchEngine::SearchEngine(){
}

SearchEngine::~SearchEngine(){
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    SearchPair* S = new SearchPair();
    S->indval[0] = book_code;
    S->indval[1] = page;
    S->indval[2] = paragraph;
    S->indval[3] = sentence_no;
    S->s = sentence;
    sentence_record.push_back(S);
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    Node* head = new Node();
    Node* tail = new Node();
    head->left = nullptr;
    head->right = tail;
    tail->left = head;
    tail->right = nullptr;

    pattern = toLowerCase(pattern);
    vector<int>LPS = SearchEngine::findlps(pattern);

    for(SearchPair* traversal : sentence_record) {
        traversal->s = toLowerCase(traversal->s);
        vector<int>off_no = offsearch(pattern, LPS , traversal->s);
        int book_no = traversal->indval[0];
        int page_no = traversal->indval[1];
        int para_no = traversal->indval[2];
        int s_no = traversal->indval[3];
        for(int i = 0; i < off_no.size(); i++) {
            tail->left->right = new Node(book_no, page_no, para_no, s_no, off_no[i]);
            tail->left = tail->left->right;
        }
        n_matches += off_no.size();
    }
    Node* newhead = head->right;
    newhead->left = nullptr;
    delete head;
    delete tail;  
    return newhead;
}

vector<int> SearchEngine::findlps(const string& pat){
    int n = pat.length();
    vector<int> lps(n,0);
    int prevlps = 0;
    int i = 1;

    while(i<n){

        if(pat[i]==pat[prevlps]){
            prevlps++;
            lps[i]=prevlps;
            i++;
        }

        else if(prevlps ==0){
            lps[i]=0;
            i++;
        }

        else{
            prevlps = lps[prevlps-1];
        }
    }

    return lps;
}

vector<int> offsearch(string pattern, vector<int> lps ,string curr_sen){
    int i = 0;
    int j = 0;
    int m = pattern.length();
    int n = curr_sen.length();
    vector<int> v;

    while((n-i) >= (m-j)){

        if(curr_sen[i]==pattern[j]){
            i++;
            j++;
        }
        
        if(j==m){
            v.push_back(i-j);
            j = lps[j-1];
        }

        else if(i<n && pattern[j]!= curr_sen[i]){

            if(j==0){
                i++;
            }
            else{
                j = lps[j-1];
            }
        }
    }
    return v;
}

string toLowerCase(string input) {
    for (char &c : input) {
        c = tolower(c); 
    }
    return input;
}
