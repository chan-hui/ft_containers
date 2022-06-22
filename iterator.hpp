/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 02:10:07 by chanhuil          #+#    #+#             */
/*   Updated: 2022/05/27 02:10:07 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template <class Iterator>
	class iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag  iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag  iterator_category;
	};

	template <class Category,
				class T,
				class Distance = ptrdiff_t,
				class Pointer = T*,
				class Reference = T&>
	class iterator
	{
		public:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
	};
}

#endif