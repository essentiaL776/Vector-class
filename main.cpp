#include <iostream>
#include <vector>
#include "vector.h"

int main() {
    MyVector<int> vec;

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    std::cout << "Size of vector after push_back: " << vec.size() << std::endl;

    MyVector<int> vecCopy(vec);
    std::cout << "Size of copied vector: " << vecCopy.size() << std::endl;

    MyVector<int> vecAssign;
    vecAssign = vec;
    std::cout << "Size of assigned vector: " << vecAssign.size() << std::endl;

    vec.assign(5, 20);
    std::cout << "Size of vector after assign: " << vec.size() << std::endl;

    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    std::allocator<int>& alloc = vec.get_allocator();
    int* raw_memory = alloc.allocate(1);
    alloc.construct(raw_memory, 30);
    std::cout << "Value in raw memory: " << *raw_memory << std::endl;
    alloc.destroy(raw_memory);
    alloc.deallocate(raw_memory, 1);

    Timer a;
    unsigned int sz = 10000000;  // 100000, 1000000, 10000000, 100000000
    std::vector<int> v1;
    for (int i = 1; i <= sz; ++i){
      v1.push_back(i);
    }
    std::cout<<"Vector time: "<<a.elapsed()<<std::endl;;

    Timer b;
    MyVector<int> v2;
    for (int i = 1; i <= sz; ++i){
      v2.push_back(i);
    }
    std::cout<<"MyVector time: "<<b.elapsed()<<std::endl;

    return 0;
}





