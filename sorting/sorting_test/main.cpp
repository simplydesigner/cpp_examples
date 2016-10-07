#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include <vector>
#include <iostream>

int main(int argc, char *argv[]) {
    using ns_sorting::insertion_sort;
	std::vector<int> items =  {10, 3, 5, 3, 2, 1, 7};
	insertion_sort(items);
	for(auto x: items) {
		std::cout << x << std::endl;
	}
}
