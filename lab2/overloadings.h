#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

ostream& operator<<(ostream &stream, vector<int> a);
vector<int> reverseVector(vector<int> vec);
vector<int> vectorAdding(vector<int> a, vector<int> b);
vector<int> operator+(vector<int> a, vector<int> b);
vector<int> operator* (vector<int> a, vector<int> b);
vector<int> operator* (vector<int> a, int int_b);
bool operator>( vector<int> a,  vector<int> b);
vector<int> vectorSubtract(vector<int> a, vector<int> b);
vector<int> operator-(vector<int> a, vector<int> b);

