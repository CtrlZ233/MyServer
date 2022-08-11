#include <iostream>
#include<unistd.h>
// #include "../include/Timer.h"
// #include "Timer.h"
// #include "../include/ObjectPool.h"
// #include "../include/Singleton.h"
#include "ObjectPool.h"
#include "Singleton.h"
#include "SafeList.h"
#include <thread>
using namespace std;

void test_object_pool() {
	auto& pool = Utils::Singleton<ObjectPool::ObjectPool<double>>::GetInstance();
	{
		auto a = pool.acquire();
		auto b = pool.acquire();
		{
			auto c = pool.acquire();
		}
	}
}

void addOne(int  i) {
	i = i + 1;
}
void print(int i) {
	std::cout << i << std::endl;
}

int main() {
	// test_object_pool();
	SafeContainer::SafeList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.traverse(addOne);
	l.traverse(print);
}

