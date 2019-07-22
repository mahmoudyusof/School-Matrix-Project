#include <string>
#include <vector>

using namespace std;

/**
 * splits a giving string by a givin character
 * @param string s string to be split
 * @param char d character by which the string is split
 * @return a vector containing all substrings
*/
vector<string> split(string s, char d);
/**
 * trims white space from the beginning of a string
 * @param string s the string to be trimed
 * @return trimed string
*/
string ltrim(string s);
/**
 * trims white space from the end of a string
 * @param string s the string to be trimed
 * @return trimed string
*/
string rtrim(string s);
/**
 * trims white space from the beginning and end of a string
 * @param string s the string to be trimed
 * @return trimed string
*/
string trim(string s);


class Cplx{
    public:
        /**
         * create a zero number
        */
        Cplx();
        /**
         * Creates a complex number out of a string
        */
        Cplx(string s);
        /**
         * Creates a complex number out of it's two components
        */
        Cplx(double real, double im);
        /**
         * addition
        */
        Cplx operator + (Cplx &other);
        /**
         * multiplication
        */
        Cplx operator * (Cplx &other);
        /**
         * subtraction
        */
        Cplx operator - (Cplx &other);
        /**
         * division
        */
        Cplx operator / (Cplx &other);
        /**
         * addition
        */
        Cplx operator + (double &num);
        /**
         * multiplication
        */
        Cplx operator * (double &num);
        /**
         * subtraction
        */
        Cplx operator - (double &num);
        /**
         * division
        */
        Cplx operator / (double &num);
        /**
         * increment
        */
        void operator += (Cplx &other);
        /**
         * decrement
        */
        void operator -= (Cplx other);
        /**
         * self multiply
        */
        void operator *= (Cplx &other);
        /**
         * output
        */
        friend ostream & operator << (ostream &out, Cplx &it);
        double real();
        double im();
        /**
         * shows the number -temporary-
        */
        void show();
    private:
        double r;
        double i;
};



class Matrix{
    public:
        /**
         * Consturcts an error matrix
        */
        Matrix();
        /**
         * Constructs a matrix using a vector of vectors
         * @param vector< vector<Cplx> > matr
         * @return Matrix
        */
        Matrix(vector< vector<Cplx> > matr);
        /**
         * Makes an identity matrix of diminsion i x i
        */
        Matrix(int i);
        /**
         * Constructs a matrix using a string of the following format
         * [a b;c d] where a, b, c and d are doubles
         * @param vector< vector<Cplx> > matr
         * @return Matrix
        */
        Matrix(string buf);
        /**
         * Adds two matrices
         * @param &other references the second matrix
         * @return Matrix result of addition operation and an error matrix if invalid
        */
        Matrix operator + (Matrix & other);
        /**
         * Subtracts two matrices
         * @param &other references the second matrix
         * @return Matrix result of subtraction operation and an error matrix if invalid
        */
        Matrix operator - (Matrix & other);
        /**
         * Multiplys two matrices
         * @param &other references the second matrix
         * @return Matrix result of multiplication operation and an error matrix if invalid
        */
        Matrix operator * (Matrix & other);
        /**
         * Creates the transpose of the matrix
        */
        Matrix T();
        /**
         * Calculates the upper triangle equivilant of the matrix
        */
        Matrix U();
        /**
         * Calculates the determinant of the matrix
        */
        Cplx deter();
        /**
         * Raises the matrix to a given power
         * @param int p the power
         * @return Matrix raised
        */
        Matrix pow(int d);
        /**
         * outputs the string representation of the matrix
        */
        void show();
        /**
         * Fetches the 2D vector of values in the matrix
        */
        vector< vector<Cplx> > get_vals();
        /**
         * Fetches the number of rows in matrix
        */
        int get_rows();
        /**
         * Fetches the number of columns in matrix
        */
        int get_cols();
        /**
         * checks wheather there is an error in the matrix
        */
        bool error();
    private:
        int n; // number of rows
        int m; // number of columns
        vector< vector<Cplx> > vecs; // values
        bool err; // well, error !! dah.
};

