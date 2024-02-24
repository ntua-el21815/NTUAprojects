#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

int absVal(int n){
    if(n<0) return -n;
    return n;
}

rational::rational(int n,int d){
    nom=n;
    den=d;
}

rational operator + (const rational &x,const rational &y){
    rational result(1,1);
    int n=x.nom*y.den + x.den*y.nom;
    int d=y.den*x.den;
    result.nom=n;
    result.den=d;
    return result;
}

rational operator - (const rational &x,const rational &y){
    rational result(1,1);
    int n=x.nom*y.den - x.den*y.nom;
    int d=y.den*x.den;
    result.nom=n;
    result.den=d;
    return result;
}

rational operator * (const rational &x,const rational &y){
    rational result(1,1);
    int n=(x.nom*y.nom);
    int d=(x.den*y.den);
    result.nom=n;
    result.den=d;
    return result;
}

rational operator / (const rational &x,const rational &y){
    rational result(1,1);
    int n=(x.nom*y.den);
    int d=(y.nom*x.den);
    result.nom=n;
    result.den=d;
    return result;
}

std::ostream &operator << (std::ostream &out,const rational &x){
    int sign=+1;
    if(x.nom<0 && x.den>0) sign = -1; 
    else if(x.den<0 && x.nom>0) sign=-1;
    else sign=+1;
    out<<sign*absVal(x.nom/rational::gcd(x.nom,x.den))<<"/"<<absVal(x.den/rational::gcd(x.nom,x.den));
    return out;
}

int rational::gcd(int a,int b){
    if(a==0){
        return a+b;
    }
        return gcd(b%a,a);
}