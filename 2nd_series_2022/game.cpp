#include <iostream>
#include <stdexcept>
#include <iterator>
#include "players.cpp"
#include <vector>

class Game {
    public:
        Game(int heaps, int players) : heaps_(heaps), players_(players) {
            heap = new int [heaps];
            heaps_count = 0;
            player_count = 0;
        }
        ~Game(){
            delete[] heap;
        }
        void addHeap (int coins){
            heap[heaps_count++] = coins;
            if(coins<0){
                throw std::logic_error("Negative coins");
            }
            if (heaps_count > heaps_){
                throw std::logic_error("Too many heaps");
            }
        }
        void addPlayer(Player *player){
            player_.push_back(player);
            player_count++;
            if (player_count > players_){
                throw std::logic_error("Too many players");
            }
            if(player == nullptr){
                throw std::logic_error("Player is null");
            }
        }
        void play(std:: ostream & out){
            Player *temp;
            State state(heaps_count, heap, player_count);
            while(!state.winning()){
                out <<"State: "<< state << std::endl;
                Move move = (*player_[state.getPlaying()]).play(state);
                temp = player_[state.getPlaying()];
                out << *temp << " ";
                state.next(move);
                out << move << std::endl;
            }
            out <<"State: "<< state << std::endl;
            out << *temp << " " << "wins" << std::endl;
        }
        int getPlayers () const{
            return player_count;
        }
        const Player* getPlayer(int p) const{
            return player_[p];
        }
    private:
        int heaps_;
        int heaps_count;
        int players_;
        int player_count;
        int *heap;
        std::vector<Player*> player_;
};

int main () {
	Game specker(3, 4);
	specker.addHeap(10);
	specker.addHeap(20);
	specker.addHeap(17);
	specker.addPlayer(new SneakyPlayer("Tom"));
	specker.addPlayer(new SpartanPlayer("Mary"));
	specker.addPlayer(new GreedyPlayer("Alan"));
	specker.addPlayer(new RighteousPlayer("Robin"));
    std:: cout << specker.getPlayers();
	specker.play(std::cout);
}