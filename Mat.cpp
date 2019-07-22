#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include "Mat.h"

using namespace std;


vector<string> split(string s, char d){
    vector<string> words;
    string word = "";
    for (int i=0; i<s.length(); i++){
        if(s[i] == d){
            words.push_back(word);
            word = "";
        }else{
            word += s[i];
        }
    }
    if(word != ""){
        words.push_back(word);
    }
    return words;
}

string ltrim(string s){
    if(s[0] == ' '){
        return ltrim(s.substr(1, s.length()-1));
    }else{
        return s;
    }
}

string rtrim(string s){
    if(s[s.length()-1] == ' '){
        return rtrim(s.substr(0, s.length()-1));
    }else{
        return s;
    }
}

string trim(string s){
    return ltrim(rtrim(s));
}

Matrix::Matrix(){
    n = 0;
    m = 0;
    err = true;
}

Matrix::Matrix(int d){
    vector<Cplx> row(d);
    for(int i=0; i<d; i++){
        for(int j=0; j<d; j++){
            if(i == j){
                row[j] = Cplx(1, 0);
            }else{
                row[j] = Cplx(0, 0);
            }
        }
        vecs.push_back(row);
    }
    n = vecs.size();
    m = vecs[0].size();
    err = false;
}

Matrix::Matrix(vector< vector<Cplx> > matr){
    vecs = matr;
    n = matr.size();
    if(n != 0){
        m = matr[0].size();
        err = false;
    }else{
        err = true;
    }
}

Matrix::Matrix(string buf){
    if(buf[0] == '[' && buf[buf.length() - 1] == ']'){
        vector<string> rows = split(buf.substr(1, buf.length()-2), ';');
        vector<string> nums;
        vector<Cplx> row;
        string temp;
        err = false;

        for(int i=0; i<rows.size(); i++){
            nums = split(rows[i], ' ');
            for(int j=0; j<nums.size();j++){
                row.push_back(Cplx(nums[j]));
            }
            vecs.push_back(row);
            row.clear();
        }
        n = vecs.size();
        if(n != 0){
            int ref = vecs[0].size();
            for(int k=1; k<n; k++){
                if(vecs[k].size() != ref){
                    err = true;
                    break;
                }
            }
            m = vecs[0].size();
        }else{
            cout << "one\n";
            err = true;
        }
    }else{
        cout << "two\n";
        err = true;
    }
}

int Matrix::get_rows(){
    return n;
}
int Matrix::get_cols(){
    return m;
}

vector< vector<Cplx> > Matrix::get_vals(){
    return vecs;
}

Matrix Matrix::operator + (Matrix & other){
    if(n == other.get_rows() && m == other.get_cols()){
        vector< vector<Cplx> > sum(n, vector<Cplx>(m));
        vector< vector<Cplx> > other_vecs = other.get_vals();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                sum[i][j] = vecs[i][j] + other_vecs[i][j];
            }
        }
        Matrix done(sum);
        return done;
    }else{
        Matrix erro;
        return erro;
    }
}

Matrix Matrix::operator - (Matrix &other){
    if(n == other.get_rows() && m == other.get_cols()){
        vector< vector<Cplx> > dif(n, vector<Cplx>(m));
        vector< vector<Cplx> > other_vecs = other.get_vals();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                dif[i][j] = vecs[i][j] - other_vecs[i][j];
            }
        }
        Matrix done(dif);
        return done;
    }else{
        Matrix erro;
        return erro;
    }
}

Matrix Matrix::operator * (Matrix &other){
    if(m == other.get_rows()){
        // int mm = other.get_rows();
        Cplx sum(0, 0);
        vector< vector<Cplx> > other_vals = other.get_vals();
        vector< vector<Cplx> > prod(n, vector<Cplx>(other.get_cols()));
        Cplx num_prod(0, 0);
        for(int i=0; i<n; i++){
            for(int j=0; j<other.get_cols();j++){
                for(int k=0; k<m; k++){
                    num_prod = vecs[i][k] * other_vals[k][j];
                    sum += num_prod;
                    // sum = sum + (vecs[i][k] * other_vals[k][j]);
                }
                prod[i][j] = sum;
                sum = Cplx(0, 0);
            }
        }

        Matrix product(prod);
        return product;
    }else{
        Matrix erro;
        return erro;
    }
}

Matrix Matrix::T(){
    vector< vector<Cplx> > t(m, vector<Cplx>(n));
    for(int i=0; i<vecs.size();i++){
        for(int j=0; j<vecs[0].size(); j++){
            t[j][i] = vecs[i][j];
        }
    }
    return Matrix(t);
}

Matrix Matrix::U(){
    if(n == m){
        Cplx ratio(0, 0);
        vector< vector<Cplx> > other = vecs;
        for(int i=0; i<n-1;i++){
            for(int j=i+1; j<n; j++){
                ratio = other[j][i] / other[i][i];
                for(int k=0; k<m; k++){
                    other[j][k] -= other[i][k] * ratio;
                }
            }
        }
        return Matrix(other);
    }else{
        // err = true;
        return Matrix();
    }
}

Cplx Matrix::deter(){
    if(n == m){
        Matrix upper = U();
        vector< vector<Cplx> > values = upper.get_vals();
        Cplx prod(1, 0);
        for(int i=0; i<m; i++){
            prod *= values[i][i];
        }
        return prod;
    }
}

Matrix Matrix::pow(int d){
    if(n == m){
        Matrix eye(n);
        Matrix me(vecs);
        for(int i=0;i<d;i++){
            eye = eye * me;
        }
        return eye;
    }else{
        return Matrix();
    }
}

void Matrix::show() {
    cout << '[';
    for(int i=0; i<vecs.size();i++){
        for(int j=0; j<vecs[i].size(); j++){
            cout << vecs[i][j];
            if(j!=vecs[i].size()-1){
                cout << ' ';
            }
        }
        if(i != vecs.size()-1)
            cout << ';';
    }
    cout << "]\n";
}

bool Matrix::error(){
    return err;
}

Cplx::Cplx(){
    i = 0;
    r = 0;
}

Cplx::Cplx(string s){
    if(s.find("+", 1) != -1 || s.find("-", 1) != -1){
        double rl, img;
        char sign;
        stringstream ss(s);
        ss >> r >> sign >> img;
        if(sign == '+'){
            i = img;
        }else if(sign == '-'){
            i = -1.0*img;
        }
    }else{
        if(s.find('i') != -1){
            r = 0;
            stringstream ss(s);
            ss >> i;
        }else{
            stringstream ss(s);
            ss >> r;
            i = 0;
        }
    }
}


Cplx::Cplx(double real, double im){
    r = real;
    i = im;
}

double Cplx::real() {
    return r;
}

double Cplx::im() {
    return i;
}

Cplx Cplx::operator + (Cplx &other){
    return Cplx(r+other.real(), i+other.im());
}

Cplx Cplx::operator - (Cplx &other){
    return Cplx(r-other.real(), i-other.im());
}

Cplx Cplx::operator * (Cplx &other){
    return Cplx(r*other.real() - i*other.im(), r*other.im() + i*other.real());
}

Cplx Cplx::operator / (Cplx &other){
    double denom = other.real()*other.real() + other.im()*other.im();
    return Cplx( (r*other.real() + i*other.im()) /  denom, (i*other.real() - r*other.im()) / denom );
}

Cplx Cplx::operator + (double &num){
    return Cplx(r+num, i);
}

Cplx Cplx::operator - (double &num){
    return Cplx(r-num, i);
}

Cplx Cplx::operator * (double &num){
    return Cplx(r*num, i*num);
}

Cplx Cplx::operator / (double &num){
    return Cplx(r/num, i/num);
}


void Cplx::operator += (Cplx &other){
    r += other.real();
    i += other.im();
}

void Cplx::operator -= (Cplx other){
    r -= other.real();
    i -= other.im();
}

void Cplx::operator *= (Cplx &other){
    double tempr = r;
    double tempi = i;
    r = tempr * other.real() - tempi * other.im();
    i = tempr * other.im() + tempi * other.real();
}


ostream & operator << (ostream &out, Cplx &it){
    if(it.real() != 0){
        out << it.real();
    }
    if(it.im() >= 0 && it.real() != 0 && it.im() != 0){
        out << '+';
    }
    if(it.im() != 0){
        out << it.im() << 'i';
    }else{
        out << "";
    }
    if(it.im() == 0 && it.real() == 0){
        out << '0';
    }else{
        out << "";
    }
}

void Cplx::show() {
    if(r != 0)
        cout << r;
    if(i >= 0 && r != 0 && i != 0){
        cout << '+';
    }
    if(i != 0)
        cout << i << 'i';
    
    cout << endl;
}
