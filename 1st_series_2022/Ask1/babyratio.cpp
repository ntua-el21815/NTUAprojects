#ifndef CONTEST
#include "babyratio.hpp"
#endif

int absVal(int n){
    if(n<0) return -n;
    return n;
}

rational::rational(int n,int d){
    nom=n;
    den=d;
}

rational rational::add(rational r){
    rational result(1,1);
    int n=nom*r.den + den*r.nom;
    int d=r.den*den;
    result.nom=n;
    result.den=d;
    return result;
}

rational rational::sub(rational r){
    rational result(1,1);
    int n=nom*r.den - den*r.nom;
    int d=r.den*den;
    result.nom=n;
    result.den=d;
    return result;
}

rational rational::mul(rational r){
    rational result(1,1);
    int n=(nom*r.nom);
    int d=(r.den*den);
    result.nom=n;
    result.den=d;
    return result;
}

rational rational::div(rational r){
    rational result(1,1);
    int n=(nom*r.den);
    int d=(r.nom*den);
    result.nom=n;
    result.den=d;
    return result;
}

void rational::print(){
    int sign=+1;
    if(nom<0 && den>0) sign = -1; 
    else if(den<0 && nom>0) sign=-1;
    else sign=+1;
    std::cout<<sign*absVal(nom/gcd(nom,den))<<"/"<<absVal(den/gcd(nom,den));
}

int rational::gcd(int a,int b){
    if(a==0){
        return a+b;
    }
        return gcd(b%a,a);
}

