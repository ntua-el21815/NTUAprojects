/*
 * Simple examples for STL
 * V Vescoukis for NTUA ECE progtech course 2021-2022
 *
 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <array>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <tuple>
#include <set>
#include <map>
#include <utility>

using namespace std;

void showlist(list<int> l) {
    list<int>::iterator it;
    cout << "size= " << l.size() << "  contents= ";
    for (it = l.begin(); it!= l.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

void showvector(vector<int> v) {
    cout << "size= " << v.size() << "  contents= ";
    vector<int>::iterator it;
    for(int i : v)
        cout << i << " ";
//    for (int d: v) cout << d << " ";
//    cout << endl;

}

template <typename T>
void showanything(T load) {
    typename T::iterator it;
    cout << "size= " << load.size() << "  contents= ";
    for (it=load.begin(); it!=load.end(); ++it) cout << *it << " ";
    cout << endl;
}

void showq(queue<int> Q) {
    queue<int> sq = Q;
    while (!sq.empty()) {
        cout << sq.front() << " ";
        sq.pop();
    }
    cout << endl;
}

void lect5_string_demo() {
    string s = "to be, or not to be? that is the question!";
    string q = s;
    cout << q << endl;
    q += " _W.Shakespeare!";
    cout << q << endl;
    cout << "s.size=" << s.size() << " length=" << s.length() <<endl;
    cout << s[1] << endl;
    cout << s.substr(3, 2) << endl;
    s.replace(21,4,"THAT");
    cout << s << endl;

    s.insert(28, " indeed");;
    cout << s << endl;
    int w = s.find("indeed",0);
    cout << w << endl;
    w = s.find("really",0);
    cout << w << endl;
    cout << s.data() << endl;
    w = s.find("o");
    int x = s.rfind("o");
    cout << w << " " << x << endl;
}

void lect5_array_demo() {
    array<int, 10> a10{};
    for (int i=0; i<a10.size(); i++) a10.at(i) = i * 10;
    for (int i=0; i<a10.size(); i++) cout << a10.at(i) << " "; cout << endl;

    for (int d:a10) cout << d << " "; cout << endl;

    array<array<int, 10>, 10> a100{};
    for (int i=0; i<10; i++)
        for (int j=0; j<10; j++)
            a100[i][j] = i + j;

    for (array<int,10> line:a100) {
        for (int d: line)
            cout << d << "\t";
        cout << endl;
    }

}

void lect5_vector_demo() {
    vector<int> v;
    for (int i=0; i<5; i++) v.push_back(i);
    showvector(v);
    v.push_back(5); showvector(v);
    v.pop_back(); showvector(v);

    v.insert(v.begin()+2,40);
    cout << "size=" << v.size() << " contents= ";
    showvector(v);

    vector<int> r(5,10);
    showvector(r);

    r.resize(8); r[7] = 20;
    showvector(r);

    r.resize(3);
    showvector(r);
    cout <<"max size would be          " << r.max_size()  << endl;

}

void lect5_list_demo() {

    list<int> l;
    for (int i=1; i<5; i++) l.push_back(i);
    for (int i=0; i<5; i++) l.push_front(-i);
    showlist(l);

    for (int i=1; i<5; i++) {
        cout << l.front() << " " << l.back() << " ";
        l.pop_front(); l.pop_back(); }
    cout << endl;
    showlist(l);

    for (int i=1; i<=5; i++) l.push_back(i);
    for (int i=9; i>=5; i--) l.push_back(i);
    showlist(l);

    cout << "front=" << l.front() << endl;
    showlist(l);

    l.reverse();
    showlist(l);
    l.sort();
    showlist(l);
    l.push_back(5);
    showlist(l);
    l.unique();
    showlist(l);

    list<int> ll(5,10);
    showlist(ll);
    showanything(ll);

}


void lect5_stack_demo() {
    stack<int> s;
    for (int i=0; i<5; i++) s.push(i*10);
    for (int i=0; i<10; i++) if (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
}


void lect5_queue_demo() {
    queue<int> q;
    for (int i=1; i<=5; i++) q.push(i*10);
    showq(q);
    for (int i=1; i<=5; i++) {
        q.pop();
        showq(q);
    }
}


// pairs...
double measure(const pair<double, double> d) {
    return sqrt(d.first * d.first + d.second * d.second);
}


void lect5_pair_demo() {
    pair<double, double> c1 (3, 4);
    pair<double, double> c2;
    c2 = make_pair(1, 1);
    cout << measure(c1) << "  " << measure(c2) << endl;
}


// tuples...
typedef tuple<int, string, int> myDate;

void printdate(const myDate &d, const string &dateFormat) {
    if (dateFormat == "us")
        cout << get<1>(d) << " " << get<0>(d) <<", " << get<2>(d) << endl;
    else
        cout << get<0>(d) << " " << get<1>(d) <<" " << get<2>(d) << endl;
}


void lect5_tuple_demo() {
    // tuple<int, string, int> easter22;
    myDate easter22, easter23(16, "April", 2023);
    easter22 = make_tuple(22,"April", 2022);
    // printdate(date1, "eu");
    printdate(easter22, "us");
    printdate(easter23, "eu");
}


/*void lect5_set_demo() {
    set<int> someInts = { 10, 15, 3, 19, 2, 67, 69, 68 };
    for (int i:someInts) cout << i << " "; cout << endl;

    someInts.insert(11);
    for (int i:someInts) cout << i << " "; cout << endl;

    set<int> moreInts = { 70, 8, 81, 5, 10, 69, 67, 31, 3 };
    set<int> unionDemo;
    set_union(someInts.begin(), someInts.end(), moreInts.begin(), moreInts.end(), inserter(unionDemo, unionDemo.begin()));
    for (int i:unionDemo) cout << i << " "; cout << endl;

    set<int> intersectionDemo;
    set_intersection(someInts.begin(), someInts.end(), moreInts.begin(), moreInts.end(), inserter(intersectionDemo, intersectionDemo.begin()));
    for (int i:intersectionDemo) cout << i << " "; cout << endl;
}*/


void lect5_map_demo() {
    map<int, string> m;
    m.insert(make_pair(1, "one"));
    m.insert(make_pair(2, "two"));
    m.insert(make_pair(3, "three"));
    int x;
    cout<< "what? "; cin >> x;
    map<int, string>::iterator p;
    p = m.find(x);
    if (p != m.end())
        cout << p->second << endl;
}


void lect5_map_demo2() {
    map<int, string> m;
    m[1] ="one";
    m[2] ="two";
    m[3] ="three";
    int x;
    cout<< "what? "; cin >> x;
    if (!m[x].empty()) cout << m[x] << endl;

    for (x=0; x<5; x++)
        cout << x << " ->  (" << m[x] <<")" <<endl;
}


int memo_fib(int n) {
    static map<int, int> cache;

    // Αν είναι εύκολο, τελείωνε!
    if (n < 2) return n;

    // Αν υπάρχει ήδη, μην το υπολογίσεις.
    map<int, int>::iterator p = cache.find(n);
    if (p != cache.end()) return p->second;

    // Αλλιώς υπολόγισε και αποθήκευσέ το.
    int v = memo_fib(n-1) + memo_fib(n-2);
    cache[n] = v;
    cout << "[cal fib(" <<n<<")] ";
    return v;
}

void lect5_map_demo3() {
    int x;
    do {
        cout << "what? ";
        cin >> x;
        cout << "memo_fib= " << memo_fib(x) << endl;
    } while (x);
}


void lect5_map_demo4() {
    map<string, string> m;
    string en[] = {"one", "two", "three", "four"};
    string it[] = {"uno", "due", "tre", "quattro"};
    for (int i=0; i < 4; i++)
        m[en[i]] = it[i];
    for (string n:en)
        cout << n << " ->  (" << m[n] <<")" <<endl;
    for (string const &n:en)
        cout << "m[\"" << n <<"\"] = \"" << m[n] <<"\"" <<endl;
}


void lect6_atl1() {
    int rows=3, columns=6, loc;
    int i, j;
    for (i=0; i < rows; i++) {
        for (j=0; j < columns; j++) {
            loc = columns * i + j ;
            cout << "(" << i << "," << j << ")->" << loc << "\t";
        }
        cout << endl;
    }
    cout << endl;

    for (loc=0; loc < rows * columns; loc++) {
        i = loc / columns;
        j = loc % columns;
        cout << loc <<"->(" << i << "," << j << ")" << "\t";
    }

    cout << "\n\nxxx\n";
    for (j=0; j < columns; j++) {
        for (i = 0; i < rows; i++) {
            loc = rows * j + i;
            cout << "(" << i << "," << j << ")->" << loc << "\t";
        }
        cout << endl;
    }
    cout << endl;
    for (loc=0; loc<rows*columns; loc++) {
        if (loc % rows == 0) cout << endl;
        j = loc / rows;
        i = loc % rows;
        cout << loc <<"->(" << i << "," << j << ")" << "\t";
    }
}


// lecture 6 example
char phonetic2char(const string &searchString) {
    static const string word[] = {"alpha", "bravo", "charlie",
                                  "delta", "echo", "foxtrot",
                                  "golf", "hotel", "india",
                                  "juliett", "kilo", "lima",
                                  "mike", "november", "oscar",
                                  "papa", "quebec", "romeo",
                                  "sierra", "tango", "uniform",
                                  "victor", "whiskey", "x-ray",
                                  "yankee", "zulu", " ", "@", "."};
    map<string, char> invPhonetic;
    for (string wrd: word) invPhonetic[wrd] = wrd.front();

    map<string, char>::iterator ipi = invPhonetic.find(searchString);

    if (ipi == invPhonetic.end())
        return '?';

    return ipi -> second;
}


string phonetic2word(string src) {
    string result = "";
    string oneWord;

    istringstream stringStream(src);
    while (stringStream >> oneWord) {
        result += phonetic2char(oneWord);
    }
    return result;
}


string char2phonetic(const char &c) {
    const string phoneticWords[] = {"alpha", "bravo", "charlie",
                                    "delta", "echo", "foxtrot",
                                    "golf", "hotel", "india",
                                    "juliett", "kilo", "lima",
                                    "mike", "november", "oscar",
                                    "papa", "quebec", "romeo",
                                    "sierra", "tango", "uniform",
                                    "victor", "whiskey", "x-ray",
                                    "yankee", "zulu", " ", "@", "." };
    map<char, string> phonetic;

     //instead of this:
      // for (int i=0; i<26; i++) phonetic['a'+i] = phoneticWords[i];
       //phonetic[' '] = " ";
    // prefer this:
    for (string ww:phoneticWords) phonetic[ww.front()] = ww;

    if (phonetic.find(c) == phonetic.end() )
        return "?";

    return phonetic[c];
}


// Start from this...
string string2phonetic_good(const string & ss) {
    string result = "";
    for (char cc:ss) result += char2phonetic(cc) + " ";
    // result = result.substr(0,result.length()-1);
    return result.substr(0,result.length()-1);
}

// Talk them into this... (discuss if find() is any faster (is it?) )
string string2phonetic_better(const string ss) {
    static map<string, string> cachedWords;

    // search for known word
    map<string, string>::iterator cw = cachedWords.find(ss);
    if (cw != cachedWords.end())
        return cw->second;   // +"!"

    // word not known
    string result="";
    for (char cc:ss) result += char2phonetic(cc) +" ";
    cachedWords[ss] = result;

    return result;
}


class readable {
private:
    string  normalText;
    string phoneticText;
    map<char, string> phoneticMap;
    map<string, char> invPhoneticMap;
    static const string phoneticWords[29];

    string char2phonetic(const char &c) ;           // direct
    string text2phonetic(const string &txt) ;

    char phonetic2char(const string &searchString); // reverse
    string phonetic2text(const string &t) ;

public:
    readable();
    readable(const string & sometext);
    string phonetic();  // getter
    string text();    // getter
    void setPhonetic(const string & pText) ;
    void setText(const string & nText) ;
};

const string readable::phoneticWords[29] = {
        "alpha", "bravo", "charlie", "delta", "echo", "foxtrot",
        "golf", "hotel", "india", "juliett", "kilo", "lima",
        "mike", "november", "oscar", "papa", "quebec", "romeo",
        "sierra", "tango", "uniform", "victor", "whiskey", "x-ray",
        "yankee", "zulu", " ", "@", "."};

string readable::char2phonetic(const char &c) {
    return phoneticMap.find(c) == phoneticMap.end() ? "?" : phoneticMap[c];
}

string readable::text2phonetic(const string &txt) {
    string result = "";
    for (char cc:txt) result += char2phonetic(cc) + " ";
    return result.substr(0,result.length()-1);
}

char readable::phonetic2char(const string &searchString) {
        auto ipi = invPhoneticMap.find(searchString);
        return ipi == invPhoneticMap.end()? '?' : ipi->second;
}

string readable::phonetic2text(const string &t) {
    string w = "", result = "";
    istringstream stringStream(t);
    while (stringStream >> w) result += phonetic2char(w);
    return result;
}

readable::readable(): normalText(""), phoneticText("") {
    for (string word:phoneticWords) {
        phoneticMap[word.front()] = word;
        invPhoneticMap[word] = word.front();
    }
}

readable::readable(const string & sometext): normalText(sometext) {
    for (string word:phoneticWords) {
        phoneticMap[word.front()] = word;
        invPhoneticMap[word] = word.front();
    }
    phoneticText = text2phonetic(sometext);
}

string readable::phonetic() { return phoneticText; }
string readable::text()   { return normalText; }

void readable::setPhonetic(const string & pText) {
    phoneticText = pText;
    normalText   = phonetic2text(pText);
}

void readable::setText(const string &nText)  {
    normalText = nText;
    phoneticText = text2phonetic(nText);
}  // --------------------- end of class readable -------------------------


void lect6_example1() {
    // put your own path here!
    ifstream inFile("/Users/vescoukis/CLionProjects/helloMySTLWorld/poem.txt");
    string inWord;
    if (!inFile.is_open()) {
        cout << "oops";
        exit(1);
    }

    string originalText = "";
    string oneWord, originalWord;

    while(inFile >> inWord) {
        string p = string2phonetic_better(inWord);
        cout << p << " " << endl;

        originalWord = phonetic2word(p);
        originalText += originalWord + " / ";
    }

    cout << "\n\n\n" << originalText<<"\n";

}



void lect6_example2() {
    // put your own path here!
    ifstream inFile("/Users/vescoukis/CLionProjects/helloMySTLWorld/poem.txt");
    string inWord;
    if (!inFile.is_open()) {
        cout << "oops";
        exit(1);
    }

    vector<readable> rvector;
    while(inFile >> inWord) {
        readable newr(inWord);
        rvector.push_back(newr);
    }

    for (readable item:rvector)
        cout << item.phonetic() << " / ";
    cout << endl;

    for (readable item:rvector)
        cout << item.text() << " / ";
    cout << endl;

//    vector<readable>::iterator lit;
//    for (lit = rvector.begin(); lit != rvector.end(); ++lit)
//        cout << lit->phonetic() << endl;
//    cout << endl;

}


int main() {
    //lect5_string_demo();
    //lect5_array_demo();
    //lect5_vector_demo();
    //lect5_list_demo();
    //lect5_stack_demo();
    //lect5_queue_demo();
    //lect5_pair_demo();
    //lect5_tuple_demo();
    //lect5_map_demo4();
    lect6_atl1();
    // lect6_example1();
    // lect6_example2();
    return 0;
}

#pragma clang diagnostic pop