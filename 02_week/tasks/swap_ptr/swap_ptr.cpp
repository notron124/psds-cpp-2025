#include <stdexcept>

template<typename T>
void SwapPtr(T &ptr1, T &ptr2) {
    T tmp = ptr1;
    ptr1 = ptr2;
    ptr2 = tmp;
}

// Можно сделать перегрузкой, но мы же любим компактность :)
//void SwapPtr(const int* &ptr1, const int* &ptr2) {
//    const int* tmp = ptr1;
//    ptr1 = ptr2;
//    ptr2 = tmp;
//}

//void SwapPtr(int** &ptr1, int** &ptr2) {
//    int** tmp = ptr1;
//    ptr1 = ptr2;
//    ptr2 = tmp;
//}
