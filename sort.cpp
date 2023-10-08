#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

template <typename E>
void inssort2(E A[], int n, int incr) {
    for (int i=incr; i<n; i+=incr)
        for (int j=i; (j>=incr) && ((A[j] < A[j-incr])); j-=incr)
            swap(A[j], A[j-incr]);
}
template <typename E>
void shellsort(E A[], int n) {
    for (int i=n/2; i>2; i/=2)
        for (int j=0; j<i; j++){
            inssort2<E>(&A[j], n-j, i);
            for (int i =0; i<n;i++){
                cout << setw(3) << A[i] << " ";
            }
            cout << "*"<< endl;
    }
    inssort2<E>(A, n, 1);
}
int main(){
    int A[16] = {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    for (int i = 0; i < 16; i++){
        cout << setw(3) << A[i] << " ";
    }
    cout << endl;
    shellsort<int>(A, 16);
    for (int i = 0; i < 16; i++){
        cout << setw(3) << A[i] << " ";
    }
    return 0;
}

// string decoder (string res, int times, string a)
// {
//     if (times == 0) return res;
//     return decoder(res + a,times-1,a);
// }
// string expand(string a) {
     
//     unsigned int bg = a.find_last_of('(');
//     if (bg > a.length()) return a;
//     int times = int(a[bg-1])-'0';
//     unsigned int end = a.find(')',bg);
   
//     // if (end > a.length()) return a;
//     return expand(a.substr(0, bg-1) + decoder("", times,a.substr(bg+1,end - bg-1))+ a.substr(end+1,a.length()-end-1));
// }

// int main(){
//     cout << expand("3(abc)4(ab)2(c)") << endl;
//     return 0;
// }