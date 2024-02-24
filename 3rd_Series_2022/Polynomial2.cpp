#include<iostream>
#include<list>
#include<cmath>

//Polynomial with linked list from STL library

class Polynomial{
    protected:
        class Term{
            public:
                int coeff;
                int exp;
                Term(int exp, int coeff){
                    this->coeff = coeff;
                    this->exp = exp;
                }
                friend class Polynomial;
        };
    private:
        std::list<Term> terms;
    public:
        Polynomial(){
            terms.clear();
        }
        Polynomial(const Polynomial& other){
            terms.clear();
            for(auto it = other.terms.begin(); it != other.terms.end(); it++){
                terms.push_back(*it);
            }
        }
        ~Polynomial(){
            terms.clear();
        }
        Polynomial & operator=(const Polynomial& other){
            terms.clear();
            for(auto it = other.terms.begin(); it != other.terms.end(); it++){
                terms.push_back(*it);
            }
            return *this;
        }
        void addTerm(int exp, int coeff){
            auto it = terms.begin();
            while(it != terms.end() && it->exp > exp){
                it++;
            }
            if(it == terms.end() || it->exp != exp){
                if(coeff != 0) terms.insert(it, Term(exp, coeff));
            }
            else{
                if((it->coeff += coeff) == 0){
                    terms.erase(it);
                }
            }
        }
        double evaluate(double x){
            double result = 0;
            for(auto it = terms.begin(); it != terms.end(); it++){
                result += it->coeff * std::pow(x, it->exp);
            }
            return result;
        }
        friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2){
            Polynomial result;
            auto it1 = p1.terms.begin();
            auto it2 = p2.terms.begin();
            while(it1 != p1.terms.end() && it2 != p2.terms.end()){
                if(it1->exp == it2->exp){
                    if(it1->coeff + it2->coeff != 0){
                        result.addTerm(it1->exp, it1->coeff + it2->coeff);
                    }
                    it1++;
                    it2++;
                }
                else if(it1->exp > it2->exp){
                    result.addTerm(it1->exp, it1->coeff);
                    it1++;
                }
                else{
                    result.addTerm(it2->exp, it2->coeff);
                    it2++;
                }
            }
            while(it1 != p1.terms.end()){
                result.addTerm(it1->exp, it1->coeff);
                it1++;
            }
            while(it2 != p2.terms.end()){
                result.addTerm(it2->exp, it2->coeff);
                it2++;
            }
        return result;
        }
        friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2){
            Polynomial result;
            for(auto it1 = p1.terms.begin(); it1 != p1.terms.end(); it1++){
                for(auto it2 = p2.terms.begin(); it2 != p2.terms.end(); it2++){
                    result.addTerm(it1->exp + it2->exp, it1->coeff * it2->coeff);
                }
            }
            return result;
        }
        friend std::ostream& operator<<(std::ostream& out, const Polynomial& p){
            if(p.terms.empty()){
                out << "0";
                return out;
            };
            for(auto it = p.terms.begin(); it != p.terms.end(); it++){
                    if(it->exp == 0){
                        if(it->coeff == 0) continue;
                        if(it->coeff > 0 && it != p.terms.begin()) out<< "+ ";
                        if(it->coeff < 0) out<< "- ";
                        out<< std::abs(it->coeff);
                    } 
                    else{
                        if(it->coeff == 0) continue;
                        if(it->coeff > 0 && it != p.terms.begin()) out<< "+ ";
                        if(it->coeff < 0) out<< "- ";
                        if(std::abs(it->coeff) != 1) out << std::abs(it->coeff);
                        out<< "x";
                        it->exp == 1 ? out<< "" : out<< "^" << it->exp;
                        it == --p.terms.end() ? out<< "" : out<< " ";
                    }
            }
            return out;
        }
};
/*int main() {
	Polynomial p;
	p.addTerm(0, 5); // 5x^0
	p.addTerm(1, 6); // 6x^1

	Polynomial q;

	std::cout << "P(x) = " << p << std::endl;
	std::cout << "P(1) = " << p.evaluate(1) << std::endl;
	std::cout << "Q(x) = " << q << std::endl;
	std::cout << "Q(1) = " << q.evaluate(1) << std::endl;
	std::cout << "(P+Q)(x) = " << p+q << std::endl;
	std::cout << "(P*Q)(x) = " << p*q << std::endl;
}*/
/* EXPECTED OUTPUT
P(x) = x^2 + 3x - 1
P(1) = 3
Q(x) = x^2 - 1
Q(1) = 0
(P+Q)(x) = 2x^2 + 3x - 2
(P*Q)(x) = x^4 + 3x^3 - 2x^2 - 3x + 1
 */