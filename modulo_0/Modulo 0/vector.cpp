#include <vector>
#include <iostream>

int main () {
using std::cout;
std::vector<int> v {2, 7, 9};
cout << v.size() << '\n';
cout << v[0] << '\n';
cout << v[1] << '\n';
v[1] = 4;
cout << v[1] << '\n';
cout << v.front() << '\n';
cout << v.back()  << '\n';
}
