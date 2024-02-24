#include<iostream>

class bstree { 
public: 
  bstree    (){  
        root=nullptr;
    }; /* κατασκευαστής: κατασκευάζει ένα κενό ΔΔΑ */
  int  height    (){
      return height_aux(root);
  };  /* επιστρέφει το ύψος του ΔΔΑ (το κενό ΔΔΑ έχει ύψος 0) */ 
  void insert    (int x){ 
      root = insert_aux(root,x);
  };  /* εισάγει τον αριθμό x στο ΔΔΑ */
  int  search    (int x){
      return search_aux(root,x);
  };  /* ψάχνει τον αριθμό x στο ΔΔΑ και επιστρέφει το επίπεδο στο οποίο
                              βρίσκεται (η ρίζα βρίσκεται στο επίπεδο 1) ή 0 αν δεν υπάρχει */
  int  min (){
      return min_aux(root);
  };       /* επιστρέφει το ελάχιστο στοιχείο του ΔΔΑ */
  int  max       (){
      return max_aux(root);
  };       /* επιστρέφει το μέγιστο στοιχείο του ΔΔΑ */
  void inorder   (){
      inorder_aux(root);
  };       /* εκτυπώνει τα στοιχεία του ΔΔΑ με ενδοδιατεταγμένη διάσχιση */
  void preorder  (){
      preorder_aux(root);
  };       /* εκτυπώνει τα στοιχεία του ΔΔΑ με προδιατεταγμένη διάσχιση */
  void postorder (){
      postorder_aux(root);
  };       /* εκτυπώνει τα στοιχεία του ΔΔΑ με μεταδιατεταγμένη διάσχιση */
  int count(){
      return count_aux(root);
  };
  int sumOddLeaf(){
      return sumOddLeaves(root);
  }
private:
    struct node{
        int info;
        node* left,*right;
    };
    node* root;
    node* insert_aux(node* tree,int x){
        if(tree==nullptr){
            node* p=new node;
            p->info=x;
            p->left=p->right=nullptr;
            return p;
        }
        if(tree->info>x){
            tree->left = insert_aux(tree->left,x);
        }
        else{
            tree->right = insert_aux(tree->right,x);
        }
        return tree;
    }
    void preorder_aux(node* tree){
        if(tree!=nullptr){
            std::cout<<tree->info<<" ";
            preorder_aux(tree->left);
            preorder_aux(tree->right);
        }
    }
    void inorder_aux(node* tree){
        if(tree!=nullptr){
            inorder_aux(tree->left);
            std::cout<<tree->info<<" ";
            inorder_aux(tree->right);
        }
    }
    void postorder_aux(node* tree){
        if(tree!=nullptr){
            postorder_aux(tree->left);
            postorder_aux(tree->right);
            std::cout<<tree->info<<" ";
        }
    }
    int max_aux(node* tree){
        node* p=tree;
        while(p->right!=nullptr){
            p=p->right;
        }
        return p->info;
    }
    int min_aux(node* tree){
        node* p=tree;
        while(p->left!=nullptr){
            p=p->left;
        }
        return p->info;
    }
    int search_aux(node* tree,int y){
        node* p=tree;
        int level=1;
        while(p!=nullptr){
            if(p->info==y){
                return level;
            }
            if(p->info>y){
                p=p->left;
                level++;
            }
            else{
                p=p->right;
                level++;
            }
        }
        return 0;
    }
    int height_aux(node* tree){
        if(tree==nullptr){
            return 0;
        }
        return 1 + std::max(height_aux(tree->left),height_aux(tree->right));
    }
    int traverse(node *p,int depth){
        if(p==nullptr) return 0;
        int k1=traverse(p->left,depth+1);
        int k2=traverse(p->right,depth+1);
        if(height_aux(p)==depth){
            return k1+k2+1;
        }
        else{
            return k1+k2;
        }
    }
    int count_aux(node* t){
        return traverse(t,1);
    }
    int sumOddLeaves(node* t){
        if(t==nullptr) return 0;
        int sum1=sumOddLeaves(t->left);
        int sum2=sumOddLeaves(t->right);
        if(t->left==nullptr && t->right==nullptr && t->info%2){
            return t->info + sum1 + sum2;
        }
        return sum1+sum2;
    }
};



int main(){
    bstree mytree;
    int N;
    std::cin>>N;
    for(int i=0;i<N;i++){
        int x;
        std::cin>>x;
        mytree.insert(x);
    }
    std::cout<<mytree.sumOddLeaf()<<'\n';
}