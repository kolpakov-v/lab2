#include <iostream>
#include <vector>
#include "overloadings.h"

using namespace std;

class Multer{
public:
   virtual vector<int> multiply(vector<int> a, vector<int> b) = 0;
};

class basic : public Multer{
public:
    vector<int> multiply(vector<int> a, vector<int> b) {
        cout << "Multiplication was not set" << endl << "All multiplications will be equal 1";
    }
};

class Karatsuba : public Multer{

public:
    vector<vector<int>> split_at(vector<int> vec, int m2){
        int size = vec.size();
        vector<vector<int>> res;
        vector<int> high;
        vector<int> low;

        for (int i = 0; i < vec.size(); ++i) {
            if(i < size - m2){
                high.push_back(vec[i]);
            }else{
                low.push_back(vec[i]);
            }
        }
        res = {high, low};
        return  res;
    }

    vector<int> multiply(vector<int> digits_a, vector<int> digits_b) {
        if(digits_a.size() == 1 && digits_b.size() == 1){
            int mult = digits_a[0] * digits_b[0];
            if(mult >=  10){
                vector<int> res = {mult/10, mult%10};
                return res;
            }
            vector<int> res = {mult};
            return res;
        }else if (digits_a.size() == 1 && digits_b.size() > 1){
            return digits_a*digits_b;
        }else if (digits_a.size() > 1 && digits_b.size() == 1){
            vector<int> res = digits_a*digits_b;
            return res;
        }

        int m = digits_a.size() < digits_b.size() ? digits_a.size() : digits_b.size();
        int m2 = m/2;

        vector<int> high1 = split_at(digits_a, m2)[0];
        vector<int> low1 = split_at(digits_a, m2)[1];
        vector<int> high2 = split_at(digits_b, m2)[0];
        vector<int> low2 = split_at(digits_b, m2)[1];

        vector<int> z0 = multiply(low1, low2);
        vector<int> z2 = multiply(high1, high2);
        vector<int> z1 = multiply(high1+low1, high2+low2) - z2 - z0;

        return z2 * pow(10, m2 * 2) + z1 * pow(10, m2) + z0;
    }
};

class Lint{

    static Multer *multer;
    string s_num;
public:
    vector<int> digits;
public:
    Lint(){ }
    Lint(string num): s_num(num){
        for (int i = 0; i < s_num.size(); ++i) {
            digits.push_back(s_num[i] - '0');
        }
    }

    static void setMultMode(Multer *newMulter){
        multer = newMulter;
    }

    vector<int> operator* (Lint other){
        vector<int> res = multer->multiply(digits, other.digits);
        return res;
    };

};

// we have to initialize multer, before we can assign any value to multer, because of it is static
basic b;
Multer* Lint::multer = &b;

int main() {
    Lint a("66"), b("45");

//    select multiplication mode
    Lint::setMultMode(new Karatsuba());
    vector<int> c = a*b;
    cout << c;
    return 0;
}
