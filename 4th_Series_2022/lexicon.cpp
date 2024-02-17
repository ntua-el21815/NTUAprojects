#include<iostream>
#include<string>

class lexicon
{
    public:
        lexicon(){
            root = nullptr;
        }
        ~lexicon(){
            purge(root);
        }
        void insert(const std::string & s){
            insert_aux(root, s);
        }
        int lookup(const std::string & s) const{
            return lookup_aux(root, s);
        }
        int depth(const std::string & s) const{
            return depth_aux(root, s);
        }
        void replace(const std::string & s, const std::string & t){
            replace_aux(root, s, t);
        }
        friend std::ostream & operator << (std::ostream & out, const lexicon & l){
            print_aux(l.root, out);
            return out;
        }
    private:
        struct node{
            std::string data;
            int frequency;
            node *left;
            node *right;
            node(const std::string & s, int f, node *l, node *r){
                data = s;
                frequency = f;
                left = l;
                right = r;
            }
        };
        node *root;
        void purge(node *n){
            if(n != nullptr){
                purge(n->left);
                purge(n->right);
                delete n;
            }
        }
        void insert_aux(node * & n, const std::string & s, int f = 1){
            if(n == nullptr){
                n = new node(s , f , nullptr, nullptr);
                return;
            }
            else if(s < n->data){
                insert_aux(n->left, s , f);
            }
            else if(s > n->data){
                insert_aux(n->right, s ,f);
            }
            else{
                n->frequency += f;
                return;
            }
        }
        int lookup_aux(node *n, const std::string & s) const{
            if(n == nullptr){
                return 0;
            }
            else if(s < n->data){
                return lookup_aux(n->left, s);
            }
            else if(s > n->data){
                return lookup_aux(n->right, s);
            }
            else{
                return n->frequency;
            }
        }
        int depth_aux(node * n, const std::string & s) const{
            int depth = 0;
            if(lookup_aux(n, s) == 0){
                return -1;
            }
            while(n->data != s){
                if(s < n->data){
                    n = n->left;
                }
                else{
                    n = n->right;
                }
                depth++;
            }
            return depth;
        }
        void replace_aux(node * & n, const std::string & s, const std::string & t){
            int freq = lookup_aux(n, s);
            if(freq == 0){
                return;
            }
            else{
                n = delete_aux(n, s);
                insert_aux(n, t, freq);
            }
        }
        // delete_aux deletes a node from the tree and returns the new root
        struct node* delete_aux(node * n, const std::string & s){
            if(n == nullptr){
                return n;
            }
            else if(s < n->data){
                n->left = delete_aux(n->left, s);
            }
            else if(s > n->data){
                n->right = delete_aux(n->right, s);
            }
            else{
                if(n->left == nullptr && n->right == nullptr){
                    delete n;
                    n = nullptr;
                    return n;
                }
                else if(n->left == nullptr){
                    node *temp = n;
                    n = n->right;
                    delete temp;
                    return n;
                }
                else if(n->right == nullptr){
                    node *temp = n;
                    n = n->left;
                    delete temp;
                    return n;
                }
                else{
                    // find the node that has the word that is exactly the next smaller than the word in the node to be deleted
                    node *temp = n->left;
                    while(temp->right != nullptr){
                        temp = temp->right;
                    }
                    n->data = temp->data;
                    n->frequency = temp->frequency;
                    n->left = delete_aux(n->left, temp->data);
                    
                }
            }
            return n;
        }
        // print_aux prints the lexicon in alphabetical order from smaller to larger
        static void print_aux(node *n, std::ostream & out){
            if(n != nullptr){
                print_aux(n->left, out);
                out << n->data << " " << n->frequency << std::endl;
                print_aux(n->right, out);
            }
        }
};


/*int main () {
    lexicon l;
    l.insert("the");
    l.insert("first");
    l.insert("electronic");
    l.insert("computers");
    l.insert("were");
    l.insert("monstrous");
    l.insert("contraptions");
    l.insert("filling");
    l.insert("several");
    l.insert("rooms");
    l.insert("consuming");
    l.insert("as");
    l.insert("much");
    l.insert("electricity");
    l.insert("as");
    l.insert("a");
    l.insert("good");
    l.insert("size");
    l.insert("factory");
    l.insert("and");
    l.insert("costing");
    l.insert("millions");
    l.insert("of");
    l.insert("dollars");
    l.insert("but");
    l.insert("with");
    l.insert("the");
    l.insert("computing");
    l.insert("power");
    l.insert("of");
    l.insert("a");
    l.insert("modern");
    l.insert("hand");
    l.insert("held");
    l.insert("calculator");
    l.insert("the");
    l.insert("programmers");
    l.insert("who");
    l.insert("used");
    l.insert("these");
    l.insert("machines");
    l.insert("believed");
    l.insert("that");
    l.insert("the");
    l.insert("computer");
    l.insert("s");
    l.insert("time");
    l.insert("was");
    l.insert("more");
    l.insert("valuable");
    l.insert("than");
    l.insert("theirs");
    l.insert("they");
    l.insert("programmed");
    l.insert("in");
    l.insert("machine");
    l.insert("language");
    int count = 0;
    std::cout<< ++count << ": "<< l;
    std::cout<< ++count << ": "<< "a is now found "<< l.lookup("a") << " time(s) at depth " << l.depth("a") << std::endl;
    std::cout<< ++count << ": "<< "and is now found "<< l.lookup("and") << " time(s) at depth " << l.depth("and") << std::endl;
    std::cout<< ++count << ": "<< "as is now found "<< l.lookup("as") << " time(s) at depth " << l.depth("as") << std::endl;
    std::cout<< ++count << ": "<< "but is now found "<< l.lookup("but") << " time(s) at depth " << l.depth("but") << std::endl;
    std::cout<< ++count << ": "<< "calculator is now found "<< l.lookup("calculator") << " time(s) at depth " << l.depth("calculator") << std::endl;
    std::cout<< ++count << ": "<< "computer is now found "<< l.lookup("computer") << " time(s) at depth " << l.depth("computer") << std::endl;
    std::cout<< ++count << ": "<< "computers is now found "<< l.lookup("computers") << " time(s) at depth " << l.depth("computers") << std::endl;
    std::cout<< ++count << ": "<< "computing is now found "<< l.lookup("computing") << " time(s) at depth " << l.depth("computing") << std::endl;
    std::cout<< ++count << ": "<< "consuming is now found "<< l.lookup("consuming") << " time(s) at depth " << l.depth("consuming") << std::endl;
    std::cout<< ++count << ": "<< "contraptions is now found "<< l.lookup("contraptions") << " time(s) at depth " << l.depth("contraptions") << std::endl;
    std::cout<< ++count << ": "<< "costing is now found "<< l.lookup("costing") << " time(s) at depth " << l.depth("costing") << std::endl;
    std::cout<< ++count << ": "<< "dollars is now found "<< l.lookup("dollars") << " time(s) at depth " << l.depth("dollars") << std::endl;
    std::cout<< ++count << ": "<< "electricity is now found "<< l.lookup("electricity") << " time(s) at depth " << l.depth("electricity") << std::endl;
    std::cout<< ++count << ": "<< "electronic is now found "<< l.lookup("electronic") << " time(s) at depth " << l.depth("electronic") << std::endl;
    std::cout<< ++count << ": "<< "factory is now found "<< l.lookup("factory") << " time(s) at depth " << l.depth("factory") << std::endl;
    std::cout<< ++count << ": "<< "filling is now found "<< l.lookup("filling") << " time(s) at depth " << l.depth("filling") << std::endl;
    std::cout<< ++count << ": "<< "first is now found "<< l.lookup("first") << " time(s) at depth " << l.depth("first") << std::endl;
    std::cout<< ++count << ": "<< "good is now found "<< l.lookup("good") << " time(s) at depth " << l.depth("good") << std::endl;
    std::cout<< ++count << ": "<< "hand is now found "<< l.lookup("hand") << " time(s) at depth " << l.depth("hand") << std::endl;
    std::cout<< ++count << ": "<< "held is now found "<< l.lookup("held") << " time(s) at depth " << l.depth("held") << std::endl;
    std::cout<< ++count << ": "<< "in is now found "<< l.lookup("in") << " time(s) at depth " << l.depth("in") << std::endl;
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "machine is now found "<< l.lookup("machine") << " time(s) at depth " << l.depth("machine") << std::endl;
    std::cout<< ++count << ": "<< "machines is now found "<< l.lookup("machines") << " time(s) at depth " << l.depth("machines") << std::endl;
    std::cout<< ++count << ": "<< "millions is now found "<< l.lookup("millions") << " time(s) at depth " << l.depth("millions") << std::endl;
    std::cout<< ++count << ": "<< "modern is now found "<< l.lookup("modern") << " time(s) at depth " << l.depth("modern") << std::endl;
    std::cout<< ++count << ": "<< "monstrus is now found "<< l.lookup("monstrus") << " time(s) at depth " << l.depth("monstrus") << std::endl;
    std::cout<< ++count << ": "<< "more is now found "<< l.lookup("more") << " time(s) at depth " << l.depth("more") << std::endl;
    std::cout<< ++count << ": "<< "much is now found "<< l.lookup("much") << " time(s) at depth " << l.depth("much") << std::endl;
    std::cout<< ++count << ": "<< "of is now found "<< l.lookup("of") << " time(s) at depth " << l.depth("of") << std::endl;
    std::cout<< ++count << ": "<< "power is now found "<< l.lookup("power") << " time(s) at depth " << l.depth("power") << std::endl;
    std::cout<< ++count << ": "<< "programmed is now found "<< l.lookup("programmed") << " time(s) at depth " << l.depth("programmed") << std::endl;
    std::cout<< ++count << ": "<< "programmers is now found "<< l.lookup("programmers") << " time(s) at depth " << l.depth("programmers") << std::endl;
    std::cout<< ++count << ": "<< "rooms is now found "<< l.lookup("rooms") << " time(s) at depth " << l.depth("rooms") << std::endl;
    std::cout<< ++count << ": "<< "s is now found "<< l.lookup("s") << " time(s) at depth " << l.depth("s") << std::endl;
    std::cout<< ++count << ": "<< "several is now found "<< l.lookup("several") << " time(s) at depth " << l.depth("several") << std::endl;
    std::cout<< ++count << ": "<< "size is now found "<< l.lookup("size") << " time(s) at depth " << l.depth("size") << std::endl;
    std::cout<< ++count << ": "<< "than is now found "<< l.lookup("than") << " time(s) at depth " << l.depth("than") << std::endl;
    std::cout<< ++count << ": "<< "that is now found "<< l.lookup("that") << " time(s) at depth " << l.depth("that") << std::endl;
    std::cout<< ++count << ": "<< "the is now found "<< l.lookup("the") << " time(s) at depth " << l.depth("the") << std::endl;
    std::cout<< ++count << ": "<< "theirs is now found "<< l.lookup("theirs") << " time(s) at depth " << l.depth("theirs") << std::endl;
    std::cout<< ++count << ": "<< "these is now found "<< l.lookup("these") << " time(s) at depth " << l.depth("these") << std::endl;
    std::cout<< ++count << ": "<< "they is now found "<< l.lookup("they") << " time(s) at depth " << l.depth("they") << std::endl;
    std::cout<< ++count << ": "<< "time is now found "<< l.lookup("time") << " time(s) at depth " << l.depth("time") << std::endl;
    std::cout<< ++count << ": "<< "used is now found "<< l.lookup("used") << " time(s) at depth " << l.depth("used") << std::endl;
    std::cout<< ++count << ": "<< "valuable is now found "<< l.lookup("valuable") << " time(s) at depth " << l.depth("valuable") << std::endl;
    std::cout<< ++count << ": "<< "was is now found "<< l.lookup("was") << " time(s) at depth " << l.depth("was") << std::endl;
    std::cout<< ++count << ": "<< "were is now found "<< l.lookup("were") << " time(s) at depth " << l.depth("were") << std::endl;
    std::cout<< ++count << ": "<< "who is now found "<< l.lookup("who") << " time(s) at depth " << l.depth("who") << std::endl;
    std::cout<< ++count << ": "<< "with is now found "<< l.lookup("with") << " time(s) at depth " << l.depth("with") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("a", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("and", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("as", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("believed", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("but", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("calculator", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("computer", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("computers", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("computing", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("consuming", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("contraptions", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("costing", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("dollars", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("electricity", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("electronic", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("factory", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
    std::cout<< ++count << ": "<< "dummy is now found "<< l.lookup("dummy") << " time(s) at depth " << l.depth("dummy") << std::endl;
    l.replace("filling", "dummy");
    std::cout<< ++count << ": "<< "language is now found "<< l.lookup("language") << " time(s) at depth " << l.depth("language") << std::endl;
}*/

