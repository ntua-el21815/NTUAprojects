#include<iostream>
#include<queue>

class Tree{
    private:
        class Node{
            public:
                int data;
                Node* left;
                Node* right;
                Node(int data){
                    this->data = data;
                    this->left = NULL;
                    this->right = NULL;
                }
        };
        Node* root;
        Node * copy(Node* root){
            if(root == NULL)
                return NULL;
            Node* newNode = new Node(root->data);
            newNode->left = copy(root->left);
            newNode->right = copy(root->right);
            return newNode;
        }
        void preOrder(Node* root){
            if (root == nullptr){
                return;
            }
            std::cout<<root->data<<" ";
            preOrder(root->left);
            preOrder(root->right);
        }
        void inOrder(Node * root){
            if (root == nullptr){
                return;
            }
            inOrder(root->left);
            std::cout<<root->data<<" ";
            inOrder(root->right);
        }
        void postOrder(Node * root){
            if (root == nullptr){
                return;
            }
            postOrder(root->left);
            postOrder(root->right);
            std::cout<<root->data<<" ";
        }
        void levelOrder(Node * root){
            if (root == nullptr){
                return;
            }
            std::queue<Node*> q;
            q.push(root);
            while(!q.empty()){
                Node* temp = q.front();
                q.pop();
                std::cout<<temp->data<<" ";
                if(temp->left != NULL){
                    q.push(temp->left);
                }
                if(temp->right != NULL){
                    q.push(temp->right);
                }
            }
        }
        bool search(Node* root, int data){
                if(root == NULL)
                    return false;
                if(root->data == data)
                    return true;
                return search(root->left, data) || search(root->right, data);
            }
    public:
        Tree(){
            this->root = NULL;
        }
        Tree(const Tree & t){
            this->root = NULL;
            this->root = copy(t.root);
        }
        void insert(int data){
            Node* newNode = new Node(data);
            if(this->root == NULL){
                this->root = newNode;
                return;
            }
            Node* current = this->root;
            while(current != NULL){
                if(data < current->data){
                    if(current->left == NULL){
                        current->left = newNode;
                        return;
                    }
                    current = current->left;
                }
                if(data > current->data){
                    if(current->right == NULL){
                        current->right = newNode;
                        return;
                    }
                    current = current->right;
                }
                if (data == current->data){
                    std::cout<<"Duplicate data"<<std::endl;
                    return;
                }
            }
        }
        void printPreOrder(){
            preOrder(this->root);
            std::cout<<std::endl;
        }
        void printInOrder(){
            inOrder(this->root);
            std::cout<<std::endl;
        }
        void printPostOrder(){
            postOrder(this->root);
            std::cout<<std::endl;
        }
        void printLevelOrder(){
            levelOrder(this->root);
            std::cout<<std::endl;
        } 
        bool search(int data){
            return search(data);
        }
};

int main(){
    Tree t;
    //insert numbers from 0 to 10 randomly !! into the tree
    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        t.insert(rand()%10);
    }
    t.printPreOrder();
    t.printInOrder();
    t.printPostOrder();
    t.printLevelOrder();
    return 0;
}