#include <iostream>
#include <vector>

using namespace std;


ostream& operator<<(ostream &stream, vector<int> a){
    for (int el: a) {
        stream << el;
    }
    return stream;
}

vector<int> reverseVector(vector<int> vec){
    vector<int> res;
    for (int i = vec.size()-1; i < vec.size(); --i) {
        res.push_back(vec[i]);
    }

    return res;
}
bool operator>( vector<int> a,  vector<int> b) {
    if(a.size() > b.size()){
        return true;
    }else if(a.size() < b.size()){
        return false;
    }else if(a.size() == b.size()){
        for (int i = 0; i < a.size(); ++i) {
            if(a[i] > b[i]){
                return true;
            }
        }
    }
    return false;
}

vector<int> vectorAdding(vector<int> a, vector<int> b){
    vector<int> res;
    vector<int> other_digits_rev = reverseVector(a);
    vector<int> digits_rev = reverseVector(b);
    int carry =  0;

    int max_len = digits_rev.size() > other_digits_rev.size() ? digits_rev.size() : other_digits_rev.size();

    for (int i = 0; i < max_len; ++i) {
        int d = 0;
        if (i < digits_rev.size()){
            d += digits_rev[i];
        }
        if (i < other_digits_rev.size()){
            d += other_digits_rev[i];
        }

        res.push_back((d + carry)%10);
        carry = (d + carry)/10;
    }

    if (carry > 0){
        res.push_back(carry);
    }

    return reverseVector(res);
}
vector<int> vectorSubtract(vector<int> a, vector<int> b){
    vector<int> res;
    a = reverseVector(a);
    b = reverseVector(b);
    if(a.size() < b.size()){
        int stop = b.size() - a.size();
        for (int i = 0; i < stop; ++i) {
            a.push_back(0);
        }
    }else{
        int stop = a.size() - b.size();
        for (int i = 0; i < stop; ++i) {
            b.push_back(0);
        }
    }
    int max_len = a.size() > b.size() ? a.size() : b.size();

    for (int i = 0; i < max_len; ++i) {
        int d = 0;
        d = a[i] - b[i];
        if (d >= 0){
            res.push_back(d);
        }else{
            d = a[i]+10-b[i];
            if(i+1 == max_len && a[i+1] == 0){
                break;
            }
            a[i+1] = a[i+1] - 1;
            res.push_back(d);
        }
    }

    res  = reverseVector(res);
    for (int i = 0; i < res.size(); ++i) {
        if(res[i] != 0){
            break;
        }else if(res[i] == 0){
            res.erase(res.begin()+i-1);
        }
    }
    return res;
}

vector<int> operator-(vector<int> a, vector<int> b){
    if(a[0] < 0 && b[0] > 0){
        a[0] = -a[0];
        vector<int> res = vectorAdding(a, b);
        res[0] = -res[0];
        return res;
    }else if(a[0] > 0 && b[0] < 0){
        b[0] = -b[0];
        vector<int> res = vectorAdding(a, b);
        return res;
    } else if(a[0] < 0 && b[0] < 0) {
        a[0] = -a[0];
        b[0] = -b[0];
        if(a > b){
            return vectorSubtract(a, b);
        }else{
            vector<int> res = vectorSubtract(b, a);
            res[0] = -res[0];
            return res;
        }
    }
    if(a > b){
        return vectorSubtract(a, b);
    }else{
        vector<int> res = vectorSubtract(b, a);
        res[0] = -res[0];
        return res;
    }
}
vector<int> operator+(vector<int> a, vector<int> b){
    if(a[0] < 0){
        a[0] = -a[0];
        return b - a;
    } else if (b[0] < 0){
        b[0] = -b[0];
        return a - b;
    }
    return vectorAdding(a, b);
}

vector<int> operator* (vector<int> a, vector<int> b){
    int counter = 0;
    vector<int> res = {0};
    for (int i = b.size() - 1; i >= 0 ; --i) {
        vector<int> tmp = {};
        for (int j = 0; j < counter; ++j) {
            tmp.push_back(0);
        }

        int carry = 0;
        for (int j = a.size() - 1; j >= 0 ; --j) {
            int mult = b[i]*a[j];
            if(j == 0 && mult+carry >= 10){
                tmp.push_back((mult+carry)%10);
                tmp.push_back((mult+carry)/10);
                break;
            }
            tmp.push_back((mult+carry)%10);
            carry = (mult+carry)/10;
        }
        counter = counter + 1;
        res = reverseVector(tmp) + res;
    }
    return res;

}

vector<int> operator* (vector<int> a, int int_b){
    vector<int> b;
    for(int i = 0; i != -1; ++i)
    {
        if(int_b < 10){
            b.push_back(int_b);
            break;
        }
        b.push_back(int_b%10);
        int_b = (int_b - int_b%10)/10;
    }
    b = reverseVector(b);
    return a*b;
}
