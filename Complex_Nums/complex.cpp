#include<iostream>

struct complex{
  double re; double im;  
};

complex c_make(double r,double i){
    complex c;
    c.re=r;
    c.im=i;
    return c;
}

complex c_add(complex c1,complex c2){
    complex result;
    result.re = c1.re + c2.re;
    result.im = c1.im + c2.im;
    return result;
}

void printComplex(complex c){
    std::cout<<c.re<<"+"<<c.im<<"i"<<std::endl;
}

int main(){
    complex c1 = c_make(4,5);
    complex c2 = c_make(2,3);
    complex c3 = c_add(c1,c2);
    printComplex(c3);
}
