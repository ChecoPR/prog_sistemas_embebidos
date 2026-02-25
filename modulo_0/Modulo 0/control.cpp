#include <iostream>
#include <vector>

int main() {
    /*
    if (true)  { cout << "yes\n"; }   // imprime yes
    if (false) { cout << "yes\n"; }   // no imprime nada
    if (23)    { cout << "yes\n"; }   // 23 → true → imprime yes
    if (0)     { cout << "yes\n"; }   // 0 → false → no imprime

    int i = 0;
    cin >> i;

    if (i < 0) { 
    cout << "negative\n"; 
    } 
    else if (i == 0) {
    cout << "zero\n"; 
    } 
    else {
    cout << "positive\n"; 
    }
    using std::cout;
    using std::cin;
    int i = 0;
    cin >> i;
    int m = i;
    switch (m) {
        case 0:
            cout << "caso 0 m es " << m << "\n";
            break;
        case 1:
            cout << "caso 1 m es " << m << "\n";
            break;
        case 3:
            cout << "caso 3 m es " << m << "\n";
            break;
        default:
            cout << "estamos en default. m es " << m << "\n";
    }
    */
    using std::cout;
    std::vector<int> v {1,2,3,4,5};

    for (int x : v) {
        std::cout << x << ' ';
    }
    return 0;
}