#ifndef sorting_hpp
#define sorting_hpp

#include <cstddef>
#include <vector>

namespace ns_sorting {

    template<typename T>
    void insertion_sort(std::vector<T>& items) {
        std::size_t size = items.size();
        if (size <= 1) return;
        for(std::ptrdiff_t j = 1, i = 0; j < size; ++j, i = j - 1) {
            auto key = items[j];
            while(i >= 0 && items[i] > key) {
                items[i + 1] = items[i];
                --i;
            } 
            items[i + 1] = key;
        }
    }
}

#endif /* sorting_hpp */
