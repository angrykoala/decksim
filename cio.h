/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  */
//Version:1.0
//Basic input-output functions and templates

//max size of containers
typedef unsigned short max_size;

//Writes a vector on out ostream, if not osteam provided, v is written on standard output cout
template <typename T>
void write_vector(const vector<T> &v,ostream &out=cout) {
    max_size siz=v.size();
    for(int i=0; i<siz-1; i++) {
        out<<v[i]<<" ";
    }
    out<<v[siz-1];
}

//Writes an element in a binary file
template <typename T>
void binary_write(const T &element,ofstream &out) {
    out.write((char *)&element,sizeof(T));
}
//Reads an element from a binary file
template <typename T>
void binary_read(const T &element,ifstream &input) {
    input.read((char *) &element,sizeof(T));
}
//Writes a vector in a binary file, it writes the size of the vector first (unsigned)
template <typename T>
void binary_write_vector(const vector<T> &v,ofstream &out) {
    max_size siz=v.size();
    T elem;
    binary_write(siz,out); //writes vector size
    for(max_size i=0; i<siz; i++) {
        elem=v[i];
        binary_write(elem,out); //writes each element
    }
    //  out.write(reinterpret_cast<char *>(&v[0]),sizeof(T)*siz);//writes all the vector
}
//Reads a vector from a binary file
template <typename T>
void binary_read_vector(vector<T> &v,ifstream &input) {
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
//Read/Write string cases (usign a write as a vector)
void binary_write(const string &element,ofstream &out) {
    vector<char> data(element.begin(), element.end());
    binary_write_vector(data,out);
}

void binary_read(string &element,ifstream &input) {
    vector<char> data;
    binary_read_vector(data,input);
    element.clear();
    string str(data.begin(),data.end());
    element=str;
}

//Writes a pair in a binary file
template <typename T,typename P>
void binary_write(const pair<T,P> &element,ofstream &out) {
    binary_write(element.first,out);
    binary_write(element.second,out);
}
//Reads a pair from a binary file
template <typename T,typename P>
void binary_read(const pair<T,P> &element,ifstream &input) {
    binary_read(element.first,input);
    binary_read(element.second,input);
}
//read/write versions for vector<string>
void binary_write_vector(const vector<string> &v,ofstream &out) {
    max_size siz=v.size();
    string elem;
    binary_write(siz,out); //writes vector size
    for(max_size i=0; i<siz; i++) {
        elem=v[i];
        binary_write(elem,out); //writes each element
    }
}
void binary_read_vector(vector<string> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read vector size
    string elem;
    v.clear();
    v.reserve(siz); //so its not necessary to change vector capacity later
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        v.push_back(elem);
    }
}
