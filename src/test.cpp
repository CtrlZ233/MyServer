#include <iostream>
#include<unistd.h>
// #include "../include/Timer.h"
#include "Timer.h"
#include <thread>
using namespace std;
void print() {
	std::cout << "hello" << std::endl;
	// cout << ++i << endl;
}

void print2() {
	cout << "Hi" << endl;
}
int main() {
	cout << "test" << endl;
	Timer::Timer timer;
	std::function<void()> func = std::bind(print);
	std::function<void()> func2 = std::bind(print2);
	auto pnode = timer.AddTimer(func, 100, 100);
	auto pnode2 = timer.AddTimer(func2, 50, 100);
	std::thread th(&Timer::Timer::Start, &timer, 10000);
	th.join();
}

