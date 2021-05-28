#include <iostream>
#include<unistd.h>
// #include "../include/Timer.h"

#include "Timer.h"
using namespace std;
void print() {
	std::cout << "hello" << std::endl;
}
int main() {
	cout << "test" << endl;
	Timer::Timer timer;
	std::function<void()> func = std::bind(print);
	
	timer.AddTimer(func, 100, 100);
	while(1) {
		usleep(10000);
		timer.Update();
	}
}