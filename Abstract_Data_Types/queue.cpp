#include <iostream>

class queue {
public:
       queue   ();       /* κατασκευαστής:  κατασκευάζει μία κενή ουρά */
  bool empty   ();       /* ελέγχει αν η ουρά είναι κενή */
  void enqueue (int x);  /* εισάγει ένα στοιχείο στην ουρά */
  int  dequeue ();       /* αφαιρεί ένα στοιχείο από μια μη κενή ουρά */
  int  peek    ();       /* επιστρέφει (χωρίς να αφαιρεί) το πρώτο στοιχείο μιας μη κενής ουράς */

private:
    struct node{
        int info;
        node* next;
    };
    node* front;
    node* rear;

};

queue::queue(){
    front=rear=nullptr;
};

bool queue::empty(){
    return front==nullptr;
}

void queue::enqueue(int x){
    node *n;
    n = new node;
    n->info=x;
    n->next=nullptr;
    if(front==nullptr){
        front=n;
    }
    else{
        rear->next=n;
    }
    rear=n;
}

int queue::dequeue(){
    node* p;
    p=front;
    int result=front->info;
    front=front->next;
    if(front==nullptr){
        rear=front;
    }
    delete p;
    return result;
}

int queue::peek(){
    return front->info;
}

bool propertyCheck(queue q){
    queue q1,q2;
    bool same_succ=1;
    int count_neg=0;
    int count_pos=0;
    while(!q.empty()){
        if(q.peek()<0){
            count_neg++;
            q1.enqueue(-q.dequeue());
        }
        else{
            count_pos++;
            q2.enqueue(q.dequeue());
        }
    }
    if(count_neg == count_pos){
        while(!q1.empty() && !q2.empty()){
            if(q1.dequeue()!=q2.dequeue()){
                same_succ=0;
            }
        }
    }
    return same_succ && count_neg == count_pos;
}
int main(){
    queue q;
    int num=0;
    while(scanf("%d",&num)!=EOF){
        q.enqueue(num);
    }
    propertyCheck(q)? std::cout<<"yes"<<std::endl : std::cout<<"no"<<std::endl ;
}