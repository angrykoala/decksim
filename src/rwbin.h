/* (C) Programmed by:Demiurgos  */
//Version:1.2
//

//max size of containers
typedef unsigned short max_size;
//Writes an element in a binary file
//TEMPLATES R/W
template <typename T>
void binary_write(const T &element,ofstream &out);
template <typename T>
void binary_read(T &element,ifstream &input);
//PAIR R/W
template <typename T,typename P>
void binary_write(const pair<T,P> &element,ofstream &out);
template <typename T,typename P>
void binary_read(pair<T,P> &element,ifstream &input);
//VECTOR R/W
template <typename T>
void binary_write(const vector<T> &v,ofstream &out);
template <typename T>
void binary_read(vector<T> &v,ifstream &input);
//STRING R/W
void binary_write(const string &element,ofstream &out);
void binary_read(string &element,ifstream &input);
//SET R/W
template <typename T>
void binary_write(const set<T> &v,ofstream &out);
template <typename T>
void binary_read(set<T> &v,ifstream &input);
//DEQUE R/W
template <typename T>
void binary_write(const deque<T> &v,ofstream &out);
template <typename T>
void binary_read(deque<T> &v,ifstream &input);
//MAP R/W
template <typename T,typename K>
void binary_write(const map<K,T> &m,ofstream &out);
template <typename T,typename K>
void binary_read(map<K,T> &m,ifstream &input);


//TEMPLATES R/W
template <typename T>
void binary_write(const T &element,ofstream &out) {
    out.write((char *)&element,sizeof(T));
}
//Reads an element from a binary file
template <typename T>
void binary_read(T &element,ifstream &input) {
    input.read((char *) &element,sizeof(T));
}

//PAIR R/W
//Writes a pair in a binary file
template <typename T,typename P>
void binary_write(const pair<T,P> &element,ofstream &out) {
    binary_write(element.first,out);
    binary_write(element.second,out);
}
//Reads a pair from a binary file
template <typename T,typename P>
void binary_read(pair<T,P> &element,ifstream &input) {
    binary_read(element.first,input);
    binary_read(element.second,input);
}

//VECTOR R/W
//Writes a vector in a binary file, it writes the size of the vector first (unsigned)
template <typename T>
void binary_write(const vector<T> &v,ofstream &out) {
    max_size siz=v.size();
    T elem;
    binary_write(siz,out); //writes vector size
    for(max_size i=0; i<siz; i++) {
        elem=v[i];
        binary_write(elem,out); //writes each element
    }
}
//Reads a vector from a binary file
template <typename T>
void binary_read(vector<T> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read vector size
    T elem;
    v.clear();
    v.reserve(siz); //so its not necessary to change vector capacity later
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        v.push_back(elem);
    }
}
//STRING R/W
//Read/Write string cases (usign a write as a vector)
void binary_write(const string &element,ofstream &out) {
    vector<char> data(element.begin(), element.end());
    binary_write(data,out);
}

void binary_read(string &element,ifstream &input) {
    vector<char> data;
    binary_read(data,input);
    element.clear();
    string str(data.begin(),data.end());
    element=str;
}
//SET R/W
template <typename T>
void binary_write(const set<T> &v,ofstream &out) {
    max_size siz=v.size();
    typename set<T>::const_iterator it;
    T elem;
    binary_write(siz,out); //writes set size
    for(it=v.begin(); it!=v.end(); it++) {
        elem=*it;
        binary_write(elem,out); //writes each element
    }
}

template <typename T>
void binary_read(set<T> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read set size
    T elem;
    v.clear();
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        v.insert(elem);
    }
}
//DEQUE R/W
template <typename T>
void binary_write(const deque<T> &v,ofstream &out) {
    max_size siz=v.size();
    typename deque<T>::const_iterator it;
    T elem;
    binary_write(siz,out); //writes set size
    for(it=v.begin(); it!=v.end(); it++) {
        elem=*it;
        binary_write(elem,out); //writes each element
    }
}

template <typename T>
void binary_read(deque<T> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read set size
    T elem;
    v.clear();
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        v.push_back(elem);
    }
}

//map<card_num,card_name> card_names; //names of cards
//MAP R/W
template <typename T,typename K>
void binary_write(const map<K,T> &m,ofstream &out) {
    max_size siz=m.size();
    binary_write(siz,out); //writes map size
    typename map<K,T>::const_iterator it;
    pair<K,T> elem;
    for(it=m.begin(); it!=m.end(); it++) {
        elem=*it;
        binary_write(elem,out); //writes each pair of elements
    }
}

template <typename T,typename K>
void binary_read(map<K,T> &m,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read map size
    pair<K,T> elem;
    m.clear();
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        m.insert(elem);
    }
}

