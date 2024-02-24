#include<iostream>

class AVLtree{
    public:
        AVLtree () : root(nullptr){}
        ~AVLtree () {
            purge(root);
        }
        bool insert(int data){}
        bool delete_node(int data){}
        bool find(int data){}
        void print_tree(){}
    private:
        class node{
            public:
                int data;
                int height;
                node* left;
                node* right;
                node(int dt) : data(dt) , height(0), left(nullptr),right(nullptr) {}
        };
        node* root;
        void purge(node* root){
            if(root != nullptr){
                purge(root->left);
                purge(root->right);
            }
            delete root;
            return;
        }
        node* insert_aux(int num,node* nd){
            if(nd == nullptr){
                return new node(num);
            }
            if(num > root->data){
                nd->right = insert_aux(num,nd->right);
            }
            else if(num < root->data){
                nd->left = insert_aux(num,nd->left);
            }
            else{
                return nd;
            }
            
        }
};