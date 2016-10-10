#ifndef TREE_H
#define TREE_H

#include <memory>
#include <functional>
#include <utility>
#include <type_traits>

namespace ns_containers {
	namespace {

		template <typename pointer_t>
		class tree_end_node {
		public:
			using pointer		= pointer_t;
			using const_pointer	= const pointer_t;

			tree_end_node(): left() {
			}

			//tree_end_node(const tree_end_node&)				= delete;
			//tree_end_node& operator=(const tree_end_node&)	= delete;
			//tree_end_node(tree_end_node&&)					= delete;
			//tree_end_node& operator=(tree_end_node&&)			= delete;

			pointer left;
		};

		template <typename void_ptr>
		class tree_node_base: public tree_end_node<
			typename std::pointer_traits<void_ptr>::template rebind<tree_node_base<void_ptr>>> {
		public:
			using pointer		= typename std::pointer_traits<void_ptr>::
								  template rebind<tree_node_base>;
			using const_pointer	= typename std::pointer_traits<void_ptr>::
								  template rebind<const tree_node_base>;
			using base			= tree_end_node<pointer>;

			tree_node_base(): right_(), parent(), is_black_() {
			}

			tree_node_base(const tree_node_base&)				= delete;
			tree_node_base& operator=(const tree_node_base&)	= delete;
			tree_node_base(tree_node_base&&)					= delete;
			tree_node_base& operator=(tree_node_base&&)			= delete;

			pointer	parent;
		private:
			pointer	right_;
			bool	is_black_;
		};

		template <typename T, typename void_ptr>
		class tree_node: public tree_node_base<void_ptr> {
		public:
			using value_type = T;
		private:
			value_type value_;
		};
	}

	template <typename T,
	          typename compare			= std::less<T>,
	          typename allocator		= std::allocator<T>>

	class tree final {
	public:
		using value_type				= T;
		using value_compare				= compare;
		using allocator_type			= allocator;
	private:
		using alloc_traits_t			= std::allocator_traits<allocator_type>;
		using void_pointer_t			= typename alloc_traits_t::void_pointer;
	public:
		using pointer					= typename alloc_traits_t::pointer;
		using const_pointer				= typename alloc_traits_t::const_pointer;
		using size_type					= typename alloc_traits_t::size_type;
		using difference_type			= typename alloc_traits_t::difference_type;
	private:
		using node_t					= tree_node<value_type, void_pointer_t>;
		using node_allocator_t			= typename alloc_traits_t::template rebind_alloc<node_t>;
		using node_alloc_traits_t		= std::allocator_traits<node_allocator_t>;
		using node_pointer_t			= typename node_alloc_traits_t::pointer;
		using node_const_pointer_t		= typename node_alloc_traits_t::const_pointer;

		using node_base_t				= tree_node_base<void_pointer_t>;
		using node_base_pointer_t		= typename node_base_t::pointer;
		using node_base_const_pointer_t	= typename node_base_t::const_pointer;

		using end_node_t				= typename node_base_t::base;
		using end_node_pointer_t		= typename std::pointer_traits<node_pointer_t>::
										  template rebind<end_node_t>;
		using end_node_const_pointer_t	= typename std::pointer_traits<node_const_pointer_t>::
										  template rebind<end_node_t>;

		node_pointer_t							begin_node_;
		std::pair<end_node_t, node_allocator_t>	pair1_;
		std::pair<size_type, value_compare>		pair3_;

	public:
		explicit tree(const value_compare& compare_);
		explicit tree(const allocator_type& allocator_);
		tree(const value_compare& compare_, const allocator_type& allocator_);
		tree(const tree& tree_);
		tree(tree&& tree_);
		tree(tree&& tree_, const allocator_type& allocator_);
		tree& operator=(const tree& tree_);

		/*
		tree& operator=(tree&& tree_);

		~tree();
		*/

		size_type& size() {
			return pair3_.first;
		}

		const size_type& size() const {
			return pair3_.first;
		}

	private:
		node_pointer_t& begin_node() {
			return begin_node_;
		}

		node_const_pointer_t& begin_node() const {
			return begin_node_;
		}

		node_pointer_t end_node() {
			return static_cast<node_pointer_t>(
				std::pointer_traits<end_node_pointer_t>::pointer_to(pair1_.first));
		}

		node_const_pointer_t end_node() const {
			return static_cast<node_const_pointer_t>(
				std::pointer_traits<end_node_pointer_t>::pointer_to(pair1_.first));
		}

		node_allocator_t& node_alloc() {
			return pair1_.second;
		}

		const node_allocator_t& node_alloc() const {
			return pair1_.second;
		}

		value_compare& value_comp() {
			return pair3_.second;
		}

		const value_compare& value_comp() const {
			return pair3_.second;
		}

		void copy_assign_alloc(const tree& tree_) {
			 copy_assign_alloc(tree_, std::integral_constant<bool,
				node_alloc_traits_t::propagate_on_container_copy_assignment::value>());
		}

		void copy_assign_alloc(const tree& tree_, std::true_type) {
			node_alloc() = tree_.node_alloc();
		}

		void copy_assign_alloc(const tree& tree_, std::false_type) {
		}

		template <class InputIterator>
		void assign_multi(InputIterator first_, InputIterator last_);
	};

	template<typename T, typename compare, typename allocator>
	tree<T, compare, allocator>::
	tree(const value_compare& compare_)
	
		:	pair3_(0, compare_) {

		begin_node() = end_node();
	}

	template<typename T, typename compare, typename allocator>
	tree<T, compare, allocator>::
	tree(const allocator_type& allocator_)

		:	pair1_(node_allocator_t(allocator_)),
			pair3_(0) {

		begin_node() = end_node();
	}

	template<typename T, typename compare, typename allocator>
	tree<T, compare, allocator>::
	tree(const value_compare& compare_, const allocator_type& allocator_)

		:	pair1_(node_allocator_t(allocator_)),
			pair3_(0, compare_) {

		begin_node() = end_node();
	}

	template<typename T, typename compare, typename allocator>
	tree<T, compare, allocator>::
	tree(const tree& tree_)

		:	pair1_(node_alloc_traits_t::select_on_container_copy_construction(tree_.node_alloc())),
			pair3_(0, tree_.value_compare) {

		begin_node() = end_node();
	}

	template<typename T, typename compare, typename allocator>
	tree<T, compare, allocator>::
	tree(tree&& tree_)

		:	begin_node_(std::move(tree_.begin_node_)),
			pair1_(std::move(tree_.pair1_)),
			pair3_(std::move(tree_.pair3_)) {

		if (size() == 0)
			begin_node() = end_node();
		else {
			end_node()->left->parent = static_cast<node_base_pointer_t>(end_node());
			tree_.begin_node() = tree_.end_node();
			tree_.end_node()->left = nullptr;
			tree_.size() = 0;
		}
	}

	template<typename T, typename compare, typename allocator>
	tree<T, compare, allocator>::
	tree(tree&& tree_, const allocator_type& allocator_)

		:	pair1_(node_allocator_t(allocator_)),
			pair3_(0, std::move(tree_.value_compare())) {

		if(allocator_ == tree_.alloc()) {
			if (size() == 0)
				begin_node() = end_node();
			else {
				begin_node() = tree_.begin_node();
				end_node()->left = tree_.end_node()->left;
				end_node()->left->parent = static_cast<node_base_pointer_t>(end_node());
				size() = tree_.size();
				tree_.begin_node() = tree_.end_node();
				tree_.end_node()->left = nullptr;
				tree_.size() = 0;
			}
		}
	}

	template<typename T, typename compare, typename allocator>
	tree<T, compare, allocator>& 
	tree<T, compare, allocator>::operator=(const tree& tree_) {
		if (this != &tree_) {
			value_comp() = tree_.value_comp();
			copy_assign_alloc(tree_);
			/*
__assign_multi(__t.begin(), __t.end());
			*/
		}

		return *this;
	}
}

#endif
