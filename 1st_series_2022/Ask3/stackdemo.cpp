#include<iostream>

using namespace std;

template <typename T>

class stack{
    public:
        stack(int size){
            size_of_stack=0;
            max_size = size;
            array = new T[size];
        }
        stack(const stack &s){
            T *temp = new T[s.max_size];
            for(int i=0;i<s.size_of_stack;i++){
                temp[i] = s.array[i];
            }
            array = temp;
            size_of_stack = s.size_of_stack;
        }
        ~stack(){
            delete [] array;
        }
        const stack & operator = (const stack &s){
            T *temp = new T[s.max_size];
            delete [] array;
            for(int i=0;i<s.size_of_stack;i++){
                temp[i] = s.array[i];
            }
            array = temp;
            size_of_stack = s.size_of_stack;
            return *this;
        }

        bool empty(){
            return size_of_stack == 0;
        }
        void push(const T &x){
            array[size_of_stack++]=x;
        }
        T pop(){
            return array[--size_of_stack];
        }
        int size (){
            return size_of_stack;
        }

        friend ostream & operator << (ostream & out,const stack &s){
            out<<"[";
            if(s.size_of_stack>0){
            for(int i=0;i<s.size_of_stack-1;i++){
                out<<s.array[i]<<", ";
            }
            out<<s.array[s.size_of_stack-1];
            }
            out<<"]";
            return out;
        }
    private:
        int size_of_stack;
        int max_size;
        T *array;
};


/*int main(){
    stack<int> s(10);
    cout<< s << endl;
    s.push(42);
    cout<< s << endl;
    s.push(34);
    s.push(17);
    cout<< s << endl;
    cout<<s.size()<<endl;
    stack<int> t(5);
    t.push(7);
    cout<< t << endl;
    t=s;
    cout<< t << endl;
    cout<< s.pop() << endl;
    s.push(8);
    stack<int> a(s);
    t.push(99);
    a.push(77);
    cout<< t << endl;
    cout<< s << endl;
    cout<< a << endl;
    stack<double> c(4);
    c.push(3.14);
    c.push(2.543);
    cout<< c << endl;
    stack<char> k(4);
    k.push('$');
    cout<<k<<endl;
    stack<char> g(5);
    g=k;
    cout<<g<<endl;
    cout<<g.size()<<endl;
}*/