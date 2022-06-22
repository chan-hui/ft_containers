/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:18:34 by chanhuil          #+#    #+#             */
/*   Updated: 2022/06/15 23:18:34 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include "./utils.hpp"
# include "./random_access_iterator.hpp"
# include "./reverse_iterator.hpp"
# include "./red_black_tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T>> >
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef pair<const key_type,mapped_type>						value_type;
			typedef Compare													key_compare;
			class value_compare : ft::binary_function<value_type,value_type,bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;

				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef 		iterator;
			typedef 		const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

			explicit map (const key_compare& comp = key_compare(),
            	const allocator_type& alloc = allocator_type())
				
			{}
		private:
			ft::red_black_tree	_tree;
	};
}

#endif