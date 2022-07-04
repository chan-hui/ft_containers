/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:31:04 by chanhuil          #+#    #+#             */
/*   Updated: 2022/07/01 10:31:04 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include <functional>
# include "./utils/utils.hpp"
# include "./utils/reverse_iterator.hpp"
# include "./utils/red_black_tree.hpp"

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T																		key_type;
			typedef T																		value_type;
			typedef Compare																	key_compare;
			typedef Compare																	value_compare;
			typedef Alloc																	allocator_type;
			typedef typename allocator_type::reference										reference;
			typedef typename allocator_type::const_reference								const_reference;
			typedef typename allocator_type::pointer										pointer;
			typedef typename allocator_type::const_pointer									const_pointer;
			typedef ft::map_iterator<value_type>											iterator;
			typedef ft::map_iterator<const value_type>										const_iterator;
			typedef ft::reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type					difference_type;
			typedef size_t																	size_type;

			typedef	typename ft::red_black_tree<value_type, value_compare, allocator_type>	tree_type;

			explicit set (const key_compare& comp = key_compare(),
            	const allocator_type& alloc = allocator_type())
				:
				_tree(tree_type(comp, alloc)),
				_comp(comp)
			{}

			template <class InputIterator>
			set (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				:
				_tree(tree_type(first, last, comp, alloc)),
				_comp(comp)
			{}

			set (const set& x)
			{
				*this = x;
			}

			~set()
			{}

			set& operator= (const set& x)
			{
				if (x == *this)
					return *this;
				_tree = x._tree;
				_comp = x._comp;
			}

			iterator begin()
			{
				return (_tree.begin());
			}
			
			const_iterator begin() const
			{
				return (_tree.begin());
			}

			iterator end()
			{
				return (_tree.end());
			}
			
			const_iterator end() const
			{
				return (_tree.end());
			}

			reverse_iterator rbegin()
			{
				return(_tree.rbegin());
			}

			const_reverse_iterator rbegin() const
			{
				return(_tree.rbegin());
			}

			reverse_iterator rend()
			{
				return(_tree.rend());
			}

			const_reverse_iterator rend() const
			{
				return(_tree.rend());
			}

			bool empty() const
			{
				return (_tree.empty());
			}

			size_type size() const
			{
				return (_tree.size());
			}

			size_type max_size() const
			{
				return (_tree.max_size());
			}

			pair<iterator, bool> insert(const value_type& val)
			{
				return (_tree.insert(val));
			}
				
			iterator insert(iterator position, const value_type& val)
			{
				return (_tree.insert(position, val));
			}
			
			template<class InputIterator>
			void insert(typename enable_if< !is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last)
			{
				_tree.insert(first, last);
			}

			void erase(iterator position)
			{
				_tree.erase(position);
			}

			size_type erase(const key_type& k)
			{
				return (_tree.erase(ft::make_pair(k, mapped_type())));
			}

			void erase(iterator first, iterator last)
			{
				_tree.erase(first, last);
			}

			void swap (map& x)
			{
				key_compare temp_comp = x._comp;
				x._comp = _comp;
				_comp = temp_comp;

				_tree.swap(x._tree);
			}

			void clear()
			{
				_tree.clear();
			}

			key_compare key_comp() const
			{
				return _comp;
			}

			value_compare value_comp() const
			{
				return _tree.value_comp();
			}

			iterator find (const key_type& k)
			{
				return _tree.find(make_pair(k, mapped_type()));
			}

			const_iterator find (const key_type& k) const
			{
				return _tree.find(make_pair(k, mapped_type()));
			}

			size_type count (const key_type& k) const
			{
				return _tree.count(make_pair(k, mapped_type()));
			}

			iterator lower_bound (const key_type& k)
			{
				return _tree.lower_bound(make_pair(k, mapped_type()));
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return _tree.lower_bound(make_pair(k, mapped_type()));
			}

			iterator upper_bound (const key_type& k)
			{
				return _tree.upper_bound(make_pair(k, mapped_type()));
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return _tree.upper_bound(make_pair(k, mapped_type()));
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return _tree.equal_range(make_pair(k, mapped_type()));
			}

			pair<iterator,iterator>             equal_range (const key_type& k)
			{
				return _tree.equal_range(make_pair(k, mapped_type()));
			}

			allocator_type get_allocator() const
			{
				return _tree.get_allocator();
			}
		private:
			tree_type			_tree;
			key_compare			_comp;
	};
}

#endif