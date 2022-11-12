#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace Utils {

// 利用局部静态变量只被初始化一次的思路重写单例模式
template <typename T>
    class Singleton {
    public:
        static T& GetInstance() {
            static T obj;
            return obj;
        }

        Singleton(const Singleton &) = delete;
        
        Singleton(Singleton &&) = delete;
    };

}


#endif