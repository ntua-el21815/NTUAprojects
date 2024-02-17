#include<iostream>
#include<stdexcept>

class Move{
    public:
        //Παίρνω sc κέρματα από το heap sh και τα βάζω στο heap th
        Move(int sh,int sc,int th,int tc){
            source = sh;
            target = th;
            sourceCoins = sc;
            targetCoins = tc;
        }
        int getSource () const{
            return source;
        }
        int getSourceCoins () const{
            return sourceCoins;
        }
        int getTarget () const{
            return target;
        }
        int getTargetCoins () const{
            return targetCoins;
        }

        friend std::ostream & operator << (std::ostream & out, const Move & move){
            if(move.targetCoins>0){
                out<< "takes " << move.sourceCoins << " coins from heap " << move.source << " and puts " << move.targetCoins << " coins to heap " << move.target ;
            }
            else{
                out<< "takes " << move.sourceCoins << " coins from heap " << move.source << " and puts nothing";
            }
            return out;
        }
    private:
        int source;
        int sourceCoins;
        int target;
        int targetCoins;
};

class State {
	public:
		State (int h, const int c[], int n){
            heaps = h;
            heap = new int[heaps];
            for(int i=0;i<h;i++){
                heap[i] = c[i];
            }
            players = n;
            playing = 0;
        }
		~State (){
            delete[] heap;

        }

		void next (const Move& move){
            int source = move.getSource();
            int target = move.getTarget();
            int sourceCoins = move.getSourceCoins();
            int targetCoins = move.getTargetCoins();
            if(source<0 || source>=heaps){
                throw std::logic_error("Source heap is out of range");
            }
            if(target<0 || target>=heaps){
                throw std::logic_error("Target heap is out of range");
            }
            if(sourceCoins<0 || sourceCoins>heap[source]){
                throw std::logic_error("Invalid heap");
            }
            if(targetCoins<0 || targetCoins>=sourceCoins){
                throw std::logic_error("Invalid heap");
            }
            heap[source] -= sourceCoins;
            heap[target] += targetCoins;
            if(playing<players-1){
                playing++;
            }
            else{
                playing = 0;
            }
        }
		bool winning () const{
            for(int i=0;i<heaps;i++){
                if(heap[i]!=0){
                    return false;
                }
            }
            return true;
        }

		int getHeaps () const{
            return heaps;
        }
		int getCoins (int h) const{
            if(h<0 || h>=heaps){
                throw std::logic_error("Invalid heap");
            }
            return heap[h];
        }

		int getPlayers () const{
            return players;
        }
		int getPlaying () const{
            return playing;
        }

		friend std::ostream& operator << (std::ostream& out, const State& state){
            for(int i=0;i<state.heaps-1;i++){
                out<< state.heap[i] << ", " ;
            }
            out<< state.heap[state.heaps-1];
            out<< " with " << state.playing << "/" << state.players << " playing next" ;
            return out;
        }
    private:
        int heaps;
        int *heap;
        int players;
        int playing;
};


/*int main(){
    int n,h,c[100];
    std::cin >> n >> h;
    for(int i=0;i<h;i++){
        std::cin >> c[i];
    }
    State state(h,c,n);
    Move move(0,2,2,1);
    state.next(move);
    std::cout << state;
    return 0;
}*/
