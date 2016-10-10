#ifndef MULTISET_H
#define MULTISET_H

#include <memory>
#include <functional>
#include <initializer_list>

#include "tree.hpp"

#include <iostream>
/*
	std::cout << __PRETTY_FUNCTION__ << std::endl;
*/

namespace ns_containers {

	template <typename key,
	          typename compare		= std::less<key>,
	          typename allocator	= std::allocator<key>>

	class multiset final {
	public:
		using key_type				= key;
		using value_type			= key_type;
		using key_compare			= compare;
		using value_compare			= key_compare;
		using reference				= value_type&;
		using const_reference		= const value_type&;	
		using allocator_type		= allocator;
	private:
		using base__				= tree<value_type, value_compare, allocator_type>;
		using alloc_traits__		= std::allocator_traits<allocator_type>;

		/*
		typedef typename __base::__node_holder					node_holder__;
		*/

		base__ tree__;

	public:
		multiset(): tree__(value_compare()) {
		}

		explicit multiset(const value_compare& __comp) {
		}

		multiset(const multiset& __s) {
		}

		multiset(std::initializer_list<value_type>& __il) {
		}
		/*
		multiset& operator=(std::initializer_list<value_type>& __il) {
		}

		multiset& operator=(const multiset& __s) {
		}
		*/

		multiset(multiset&& __s) {
		}
		/*
		multiset& operator=(multiset&& __s) {
		}
		*/

		~multiset() {
		}
	};
}

#endif
