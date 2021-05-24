#include <iostream>
using namespace std;

template <typename T>
void fun(const T& t){
	cout << t << '\n';
}
 
template <typename T, typename ... Args>
void fun(const T& t, Args ... args){
	cout << t << ',';
    cout << sizeof(T) << endl;
	fun(args...);//递归解决，利用模板推导机制，每次取出第一个，缩短参数包的大小。
}

int main() {
    fun(1, 2, 3);
}