#include <iostream>
#include<unistd.h>
// #include "../include/Timer.h"
// #include "Timer.h"
// #include "../include/ObjectPool.h"
// #include "../include/Singleton.h"
#include "ObjectPool.h"
#include "Singleton.h"
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

int main() {
	test_object_pool();
}

