#include <iostream>
#include <string>
#include "Mat.h"
using namespace std;

int main(){

    string buf;
    string buf2;
    string op;

    getline(cin, buf);
    Matrix mat(buf);

    if(!mat.error()){

        getline(cin, op);
        // mat.show();
        if(op == "+"){
            getline(cin, buf2);
            Matrix mat2(buf2);
            Matrix all = mat + mat2;
            if(!all.error()) {
                all.show();
            }else{
                cout << "ERROR\n";
            }
        }else if(op == "-"){
            getline(cin, buf2);
            Matrix mat2(buf2);
            Matrix all = mat - mat2;
            if(!all.error()) {
                all.show();
            }else{
                cout << "ERROR\n";
            }
        }else if(op == "*"){
            getline(cin, buf2);
            Matrix mat2(buf2);
            Matrix all = mat * mat2;
            if(!all.error()) {
                all.show();
            }else{
                cout << "ERROR\n";
            }
        }else if(op == "D"){
            Cplx d = mat.deter();
            cout << d << endl;
        }else if(op == "^") {
            int num;
            cin >> num;
            Matrix Power = mat.pow(num);
            Power.show();
        }else if(op == "T"){
            Matrix transpose = mat.T();
            transpose.show();
        }else if(op == "eye"){
            Matrix eye = Matrix(3);
            eye.show();
        }
        else{
            cout << "ERROR\n";
        }
    }else{
        cout << "ERROR\n";
    }

    return 0;
}
