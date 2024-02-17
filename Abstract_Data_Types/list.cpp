#include <iostream>

class list {
public:
       list   ();              /* κατασκευαστής:  κατασκευάζει μία κενή λίστα */
  bool empty  ();              /* ελέγχει αν η λίστα είναι κενή */
  int  size   ();              /* επιστρέφει το μέγεθος της λίστας */
  void add    (int k, int x);  /* εισάγει το στοιχείο x στη θέση k της λίστας */
  int  get    (int k);         /* επιστρέφει την τιμή του στοιχείου στη θέση k της λίστας */
  void remove (int k);         /* διαγράφει το στοιχείο στη θέση k της λίστας */
private:
    struct node{
        int info;
        node* next;
    };
    node* start;
    int list_size;
};

list::list(){
    start = nullptr;
    list_size=0;
}

bool list::empty(){
    return start==nullptr;
}

int list:: size(){
    return list_size;
}

void list::add(int k, int x){
    node* p;
    p = new node;
    p->info=x;
    if(list_size==0){
        start=p;
        p->next=nullptr;
    }
    else if(k==1){
        node *q;
        q=start;
        start=p;
        p->next=q;
    }
    else{
        node *q;
        q=start;
        for(int i=1;i<k-1;i++){
            q=q->next;
        }
        p->next=q->next;
        q->next=p;
    }
    list_size++;
}

int list::get(int k){
    node *q;
    q=start;
    for(int i=1;i<k;i++){
        q=q->next;
    }
    return q->info;
}

void list::remove(int k){
    node *q;
    q=start;
    if(list_size==1){
        start=nullptr;
        delete q;
    }
    else if(k==1){
        start=q->next;
        delete q;

    }
    else{
        for(int i=1;i<k-1;i++){
            q=q->next;
        }
        node* p;
        p=q->next;
        q->next=p->next;
        delete p;
    }
    list_size--;
}

void print_list(list l){
    for(int i=1;i<=l.size();i++){
        std::cout<<l.get(i)<<" ";
    }
}

int main(){
    list l;
    int N,K,X,M,Z;
    std::cin>>N;
    for(int i=0;i<N;i++){
        std::cin>>K>>X;
        l.add(K,X);
    }
    //print_list(l);std::cout<<'\n';
    std::cin>>M;
    for(int i=0;i<M;i++){
        std::cin>>K;
        l.remove(K);
    }
    //print_list(l);std::cout<<'\n';
    std::cin>>Z;
    std::cout<<l.size()<<" "<<l.get(Z)<<'\n';
}