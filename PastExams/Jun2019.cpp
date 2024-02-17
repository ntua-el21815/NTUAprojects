#include<iostream>
#include<string>
#include<vector>

template<typename T>
class Visitor{
    public:
    virtual void visit(const T &x) = 0;
};

template<typename T>
class Collection{
    public:
    virtual void add(const T &x) = 0;
    virtual void accept(Visitor<T> &v) = 0; 
};

class BitString : public Collection<bool> {
    public:
        void add(const bool &x) override {
            vec.push_back(x);
        }
        void accept(Visitor<bool> &v) override {
            for(bool b :vec){
                v.visit(b);
            }
        }
    private:
        std::vector<bool> vec;
};


class CountingBitsVisitor : public Visitor<bool>{
    public:
        CountingBitsVisitor() : counter(0){}
        void visit(const bool &x){
            counter += x;
        }
        int count(){
            return counter;
        }
    private:
        int counter;
};

int countBits(Collection<bool> &c){
    CountingBitsVisitor v;
    c.accept(v);
    return v.count();
}

int main(){
    BitString bits;
    bits.add(true);
    bits.add(false);
    bits.add(false);
    bits.add(true);
    bits.add(true);
    bits.add(false);
    bits.add(false);
    bits.add(true);
    std::cout<< countBits(bits);
}