#include<iostream>
#include<cmath>

double f(double x){
    return sin(x);
}

double integrate (double a,double b,double f(double),int iterations){
    double result = 0;
    for(int i=0;i<iterations;i++){
        result += ((b-a)/iterations)*(f(a+i*((b-a)/iterations)));
    }
    return result;
}

int main(){
    std::cout<<integrate(0,M_PI,f,10000)<<std::endl;
    return 0;
}