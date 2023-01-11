#include "exercise2_utils.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

class BST
{
private:

    Node* root;

    void addLeafPrivate(int score, bool is_home, int shirt_no, Node* node){
        if (root == NULL){
            root = createLeaf(score, is_home, shirt_no);
        }
        else if(score <= node->score){
            if (node->left != NULL){
                addLeafPrivate(score, is_home, shirt_no, node->left);
            }
            else
            {
                node->left = createLeaf(score, is_home, shirt_no);
            }

        }
        else if(score > node->score){
            if(node->right != NULL){
                addLeafPrivate(score, is_home, shirt_no, node->right);
            }
            else{
                node->right = createLeaf(score, is_home, shirt_no);
            }
        }
        else
        {
            cout << "The data -- " << score << ',' << is_home << ',' << shirt_no
                 << " -- is already in tree.\n";
        }
    }

    void inOrderTraversalRangePrivate(int low, int high, Node* node){
        if(root != NULL){
            if (node->left != NULL){
                inOrderTraversalRangePrivate(low, high, node->left);
            }
            if (node->score <= high && node->score >= low){
                if (node->is_home == true){
                    cout << "H ";
                }
                else{
                    cout << "A ";
                }
                cout << node->shirt_no << ' ' << node->score << endl;
            }
            if (node->right != NULL){
                inOrderTraversalRangePrivate(low, high, node->right);
            }
        }         
    }
    
    
public:
    BST(){
        root = NULL;
    };

    Node* createLeaf(int score, bool is_home, int shirt_no){
        Node* n = new Node;
        
        n->score = score;
        n->is_home = is_home;
        n->shirt_no = shirt_no;
        n->left = NULL;
        n->right = NULL;

        return n;
    };

    void addLeaf(int score, bool is_home, int shirt_no){
        addLeafPrivate(score, is_home, shirt_no, root);
    }

    void printTree(){
        
        print_binary_tree(*root);
    }

    void inOrderTraversalRange(int low, int high){
        inOrderTraversalRangePrivate(low, high, root);
    }
    

};


vector<string> splitString(string str, char delimiter){
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}


int main(int argc, char** argv) {

    string path = argv[1];
    //cout << "path = " << path << endl;

    int s_min = atoi(argv[2]);
    //cout << "s_min = " << s_min << endl;

    int s_max = atoi(argv[3]);
    //cout << "s_max = " << s_max << endl;

    
    BST bst = BST();
    
    // Read the file
    string text;
    ifstream scoreFile(path);
    vector<string> data;
    int score, shirt_no;
    bool is_home;

    getline(scoreFile, text);

    if (scoreFile.is_open())
    {

        while (getline(scoreFile, text) && text != "")
        {
            
            data = splitString(text, ',');
            score = atoi(data[2].c_str());
            is_home = (data[0] == "H");
            shirt_no = atoi(data[1].c_str());
            bst.addLeaf(score, is_home, shirt_no);
            bst.printTree();
            
        }
        scoreFile.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    // Display the players whose scores are in [s_min, s_max].
    bst.inOrderTraversalRange(s_min, s_max);

    
    return 0;
}
