#include<iostream>

using namespace std;

template <typename T>

class stack{
    public:
        stack(int size) : size_of_stack (0) , max_size(size) , top(nullptr) {}
        stack(const stack &s) : size_of_stack(s.size_of_stack) , max_size(s.max_size) {
             copy(top, s.top);
        }
        ~stack(){
            while(top != nullptr){
                node *temp = top;
                top = top->next;
                delete temp;
            }
        }
        const stack & operator = (const stack &s){
            if(this != &s){
                while(top != nullptr){
                    node *temp = top;
                    top = top->next;
                    delete temp;
                }
                size_of_stack = s.size_of_stack;
                max_size = s.max_size;
                copy(top, s.top);
            }
            return *this;
        }

        bool empty(){
            return size_of_stack == 0;
        }
        void push(const T &x){
            node *temp = new node(x,top);
            top = temp;
            size_of_stack++;
        }
        T pop(){
            T x = top->data;
            node *temp = top;
            top = top->next;
            delete temp;
            size_of_stack--;
            return x;
        }
        int size (){
            return size_of_stack;
        }

        friend ostream & operator << (ostream & out,const stack &s){
            out<<"[";
            if(s.size_of_stack>0){
                node *temp = s.top;
                node_print(out,temp);
            }
            out<<"]";
            return out;
        }
    private:
        struct node{
            T data;
            node *next;
            node(const T &x, node* p) : data(x) , next(p) {}
        };
        static void copy(node *&dest, node *src){
            if(src != nullptr){
                dest = new node(src->data,nullptr);
                copy(dest->next,src->next);
            }
        }
        static void node_print(ostream & out,node *temp){
            if(temp != nullptr){
                node_print(out,temp->next);
                if(temp->next != nullptr){
                    out<<", ";
                }
                out<<temp->data;
            }
        }
        node *top;
        int size_of_stack;
        int max_size;
};


/*int main () {  
	// let’s play with integers...  
	stack<int> s(10);  
	cout << "s is empty: " << s << endl;  
	s.push(42);  
	cout << "s has one element: " << s << endl;  
	s.push(17);  
	s.push(34);  
	cout << "s has more elements: " << s << endl;  
	cout << "How many? " << s.size() << endl;  
	stack<int> t(5);  
	t.push(7);  
	cout << "t: " << t << endl;  
	t = s;  
	cout << "popping from s: " << s.pop() << endl;  
	s.push(8);  
	stack<int> a(s);  
	t.push(99);  
	a.push(77);  
	cout << "s: " << s << endl;  
	cout << "t: " << t << endl;  
	cout << "a: " << a << endl;  
	// now with doubles...  
	stack<double> c(4);  
	c.push(3.14);  
	c.push(1.414);  
	cout << "c contains doubles " << c << endl;  
	// and with characters...  
	stack<char> k(4);  
	k.push('$');  
	cout << "k contains a character " << k << endl;  
}*/