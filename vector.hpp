/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:21:07 by chanhuil          #+#    #+#             */
/*   Updated: 2022/05/25 19:21:07 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "./utils.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T>>
	class vector
	{
	public:
		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		// typedef ft::random_access_iterator<value_type>			iterator;
		// typedef ft::random_access_iterator<const value_type>	const_iterator;
		// typedef ft::reverse_iterator<iterator>					reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		// typedef iterator_traits<iterator>::difference_type		difference_type;
		typedef allocator_type::size_type						size_type;

		explicit vector (const allocator_type& alloc = allocator_type())
			:
			_alloc(alloc),
			_begin(ft_nullptr),
			_end(ft_nullptr),
			_capacity(ft_nullptr)
		{}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			:
			_alloc(alloc),
			_begin(ft_nullptr),
			_end(ft_nullptr),
			_capacity(ft_nullptr)
		{
			_begin = _alloc.allocate(n);
			_end = _begin;
			_capacity = _begin + n;
			for (int i=0;i<n;i++)
			{
				_alloc.construct(_end, val);
				_end++;
			}
		}

		template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			:
			_alloc(alloc)
		{
			
		}

		vector (const vector& x)
		{}
	private:
		allocator_type	_alloc;
		pointer			_begin;
		pointer			_end;
		pointer			_capacity;
	};
	
}

#endif