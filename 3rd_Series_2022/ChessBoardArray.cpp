#include <iostream>  
#include <iomanip>  
#include <cmath>  
  
//Implementation of matrix that only has non zero elements on the white squares of the chess board.

class ChessBoardArray{  
    protected:  
        class Row{  
            public:  
                Row(ChessBoardArray &a,int i) : arr(a),row(i){}  
                int &operator[](int i)const{  
                    return arr.select(row,i);  
                }  
            private:  
                ChessBoardArray &arr;  
                int row;  
        };  
        class ConstRow{  
            public:  
                ConstRow(const ChessBoardArray &a,int i) : arr(a),row(i){}  
                int operator[](int i) const{  
                    return arr.select(row,i);  
                }  
            private:  
                const ChessBoardArray &arr;  
                int row;  
        };  
    public:  
        ChessBoardArray(unsigned int size = 0,unsigned int base = 0){  
            this->size = size;  
            this->base = base;
            this->arr_size = this->size*(this->size/2)+((this->size/2)+1)*((this->size+2)%2);
            this->array = new int[this->arr_size]; 
            //All the elements are initialized to 0. 
            for(int i = 0; i < this->arr_size; i++){  
                this->array[i] = 0;  
            }  
        }  
        ChessBoardArray(const ChessBoardArray &a){  
            this->size = a.size;  
            this->base = a.base;  
            this->array = new int[a.arr_size];  
            for(int i = 0; i < a.arr_size; i++){  
                this->array[i] = a.array[i];  
            }  
        }  
        ~ChessBoardArray(){  
            delete[] array;  
        }  
        ChessBoardArray &operator=(const ChessBoardArray &a){  
            if(this != &a){  
                delete[] array;//Deletes Dynamic Array if not equal  
                this->size = a.size;  
                this->base = a.base;  
                this->array = new int[a.arr_size];  
                for(int i = 0; i < a.arr_size; i++){  
                    this->array[i] = a.array[i];  
                }  
            }  
            return *this;  
        }  
        int &select(int i,int j){  
            return array[loc(i,j)];  
        }  
        int select (int i,int j) const{  
            return array[loc(i,j)];  
        }  
        const Row operator[](int i){  
            return Row(*this,i);  
        }  
        const ConstRow operator[](int i) const{  
            return ConstRow(*this,i);  
        }  
        friend std::ostream &operator << (std::ostream &out,const ChessBoardArray &a){  
            //Prints out value of element if on white square or 0 if on black square  
            //Both indices are either odd or even if the element is on a white square!  
            for(unsigned int i = a.base; i < a.size+a.base; i++){  
                out << std::setw(4);  
                for(unsigned int j = a.base; j < a.size+a.base; j++){  
                    if(((i-a.base)%2 && (j-a.base)%2) || (!((i-a.base)%2) && !((j-a.base)%2))){
                        out << a.select(i,j) << std:: setw(4);  
                    } 
                    else out << "0"<< std::setw(4);  
                }  
                out << std::endl;  
            }  
            return out;  
        }  
  
    private:  
        unsigned int size;  
        unsigned int base;  
        int *array;  
        unsigned int arr_size; //Actual integers needed to represent chess board array
        //Function to locate the index of the array given that the only the elements of the array   
        //on white squares of the chessboard are stored.  
        int loc(int i,int j) const {  
            //Error if out of bounds
            if (i-this->base < 0 || j-this->base < 0 || i-this->base >= size || j-this->base >= size) {
                throw std::out_of_range("This is a chessboard so no elments except 0 on black squares!"); 
            } 
            if(((i-this->base)%2 && (j-this->base)%2) || !((i-this->base)%2) && !((j-this->base)%2)) {  
                if (this->size%2==0)return (i-this->base)*std::ceil(double(this->size)/2) + (j-this->base)/2;
                else return (i-this->base)*std::ceil(double(this->size)/2) + (j-this->base)/2 - (i-this->base)/2;  
            }  
            throw std::out_of_range("This is a chessboard so no elments except 0 on black squares!");  
            //Error in case that the element is not on a white square since then it can't be modified.  
        }  
};  
  
/*int main(){ 
    ChessBoardArray a(4,1); 
    a[3][1] = 42; 
    a[4][4] = 17; 
    try{ 
        a[2][1] = 7; 
    } 
    catch(std::out_of_range &e){ 
        std::cout << "a[2][1] is black" << std::endl; 
        std::cout << e.what() << std::endl; 
    } 
    std::cout << a ; 
}*/ 