#include<iostream>
#include<fstream>
#include<string>
using namespace std;



class node{
    public:
        char info;
        string Word;
        class node* ptrs[256];
        node(){
            for(int i=0;i<256;i++){
            	
                ptrs[i]=NULL;
            }
            Word="";
        }
};

void insertword(string word,int pos,class node * root){
    if(word.length()==pos) {
        root->Word=word;
        return;
    }
    if( root-> ptrs[word[pos]] == NULL ) {
        node *newnode;
        newnode= new node;
        newnode->info=word[pos];
        root->ptrs[word[pos]]=newnode;
        insertword(word,pos+1,root->ptrs[word[pos]]);
    }
    else
        insertword(word,pos+1,root->ptrs[word[pos]]);
}

int found=0;

void find(string key,int pos, class node * root) {
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL))
        find(key,pos+1,root->ptrs[key[pos]]);
    else if(key==root->Word){
        cout<<"The spelling of the word '"<<root->Word<<"' is correct"<<endl;
        found=1;
    }
}



void printall(class node * root) {
    for(int i=0;i<256;i++)
        if(root->ptrs[i]!=NULL) {
            printall(root->ptrs[i]);
        }
    if(root->Word != "")
        cout<<" -> "<<root->Word<<endl;
}

void suggest(string key,int pos, class node * root) {
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL)) {
            suggest(key,pos+1,root->ptrs[key[pos]]);
    }
    else{
            printall(root);
    }
}

int main(){
	char infile[20];
	cout << "Enter the name of dictionary file: ";
	cin >> infile;
    ifstream in(infile);
    string word,current="",key;
    node *root;
    root = new node;
    while(in) {
        in>>word;
        insertword(word,0,root);
    }
    in.close();
    cout<<"Enter the word to check: ";
    cin>>key;
    find(key,0,root);
    if(!found) {
        cout<<endl<<"The spelling is incorrect, Possible suggestions are :"<<endl;
        suggest(key,0,root);
    }
    return 0;
}
