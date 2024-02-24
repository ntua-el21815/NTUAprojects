int sumOddLeaves(tree t){
    if(t==nullptr) return 0;
    if(t->left == nullptr && t->right == nullptr){
        if(t->data % 2 == 1 ) return t->data;
    }
    if(t->data % 2 == 1) return t->data + summOddLeaves(t->left) + sumOddLeaves(t->right);
    return summOddLeaves(t->left) + sumOddLeaves(t->right);
}