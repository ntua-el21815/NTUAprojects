#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include "move.cpp"

class Player {
    public:
		Player (const std::string &n){
            name = n;
        }
		virtual ~Player (){};

		virtual const std::string& getType () const = 0;
		virtual Move play (const State& s) = 0;

		friend std::ostream& operator<< (std::ostream& out, const Player& player){
            out << player.getType() << " player " << player.name;
            return out;
        }
    protected:
        std::string Type;
        int findMaxHeap(const State& s){
                int heaps = s.getHeaps();
                int maxheap = 0;
                for(int i=0;i<heaps;i++){
                    if(s.getCoins(i)>s.getCoins(maxheap)){
                        maxheap = i;
                    }
                }
                return maxheap;
            }
        int findMinHeap(const State& s){
                int heaps = s.getHeaps();
                int minheap = 0;
                for(int i=0;i<heaps;i++){
                    if(s.getCoins(i)<s.getCoins(minheap)){
                        minheap = i;
                    }
                }
                return minheap;
            }
        int findMinHeapPos(const State& s){
                int heaps = s.getHeaps();
                int min_coins = 1000000;
                int minheap = -1;
                for(int i=0;i<heaps;i++){
                    if(s.getCoins(i)<min_coins&& s.getCoins(i)>0){
                        minheap = i; min_coins = s.getCoins(i);
                    }
                }
                return minheap;
            }
    private:
        std::string name;
};


class GreedyPlayer : public Player{
    public:
        GreedyPlayer (const std::string &n):Player(n){
            Type = "Greedy";
        }
        ~GreedyPlayer(){}
        const std::string& getType() const override{
            return Type;
        }
        Move play (const State& s) override{
            int maxheap = findMaxHeap(s);
            int source = maxheap;
            int sourcecoins = s.getCoins(source);
            int target = 0;
            int targetcoins = 0;
            return Move(source,sourcecoins,target,targetcoins);
        }
};

class SpartanPlayer : public Player{
    public:
        SpartanPlayer (const std::string &n) : Player(n) {
            Type = "Spartan";
        }
        ~SpartanPlayer(){}
        const std:: string& getType() const override{
            return Type;
        }
        Move play (const State& s) override{
            int maxheap = findMaxHeap(s);
            int source = maxheap;
            int sourcecoins = 1;
            int target = 0;
            int targetcoins = 0;
            return Move(source,sourcecoins,target,targetcoins);
        }
};

class SneakyPlayer : public Player{
    public:
        SneakyPlayer (const std::string &n) : Player(n) {
            Type = "Sneaky";
        }
        ~SneakyPlayer(){}
        const std:: string& getType() const override{
            return Type;
        }
        Move play (const State& s) override{
            int minheap = findMinHeapPos(s);
            int source = minheap;
            int sourcecoins = s.getCoins(source);
            int target = 0;
            int targetcoins = 0;
            return Move(source,sourcecoins,target,targetcoins);
        }
};

class RighteousPlayer : public Player{
    public:
        RighteousPlayer (const std::string &n) : Player(n) {
            Type = "Righteous";
        }
        ~RighteousPlayer(){}
        const std:: string& getType() const override{
            return Type;
        }
        Move play (const State& s) override{
            int maxheap = findMaxHeap(s);
            int minheap = findMinHeap(s);
            int source = maxheap;
            int sourcecoins = std::ceil (double(s.getCoins(source))/2);
            int target = minheap;
            int targetcoins = std::ceil (double(s.getCoins(source))/2) -1;
            return Move(source,sourcecoins,target,targetcoins);
        }
};