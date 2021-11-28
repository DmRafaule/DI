#include "Mem.hpp"
#include <iostream>

#ifdef DEBUG

void* operator new(size_t size){
	void* ptr = malloc(size);
	std::cout << "DI-> Alloc mem: " << size << " bytes, " << ptr << std::endl;
	return ptr;
}
void operator delete(void* ptr){
	std::cout << "DI-> Dealloc mem " << ptr << std::endl;
	free(ptr);
}
void* operator new[](size_t size){
	void* ptr = malloc(size);
	std::cout << "DI-> Alloc mem[]: " << size << " bytes, " << ptr << std::endl;
	return ptr;
}
void operator delete[](void* ptr){
	std::cout << "DI-> Dealloc mem[] " << ptr << std::endl;
	free(ptr);
}

#endif