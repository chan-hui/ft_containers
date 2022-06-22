/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 00:00:48 by chanhuil          #+#    #+#             */
/*   Updated: 2022/06/01 00:00:48 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "./iterator.hpp"

const
class nullptr_t
{
public:
	template<class T>
	operator T*() const
	{ return 0; }

	template<class C, class T>
	operator T C::*() const
	{ return 0; }
private:
	void operator&() const;
} ft_nullptr = {};

namespace ft
{
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distance (InputIterator first, InputIterator last)
	{
		typename iterator_traits<InputIterator>::difference_type c = 0;
		while (first != last)
		{
			first++;
			c++;
		}
		return c;
	}

	template<bool B, class T = void>
	struct enable_if {};
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <class T, T v>
	struct integral_constant
	{
		typedef integral_constant type;
		typedef T value_type;
		enum {
			value = v
		};
	};
	
	template<typename> struct is_integral_base: ft::integral_constant<bool, false> {};
	template<> struct is_integral_base<bool>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<char>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<signed char>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<short int>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<int>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<long int>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<long long int>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<unsigned char>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<unsigned short int>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<unsigned int>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<unsigned long int>: ft::integral_constant<bool, true> {};
	template<> struct is_integral_base<unsigned long long int>: ft::integral_constant<bool, true> {};

	template<typename T> struct is_integral: is_integral_base<T> {};

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type first;
			second_type second;

			pair()
			:
				first(),
				second()
			{}

			template<class U, class V>
			pair (const pair<U,V>& pr)
			:
				first(pr.first),
				second(pr.second)
			{}

			pair (const first_type& a, const second_type& b)
			:
				first(a),
				second(b)
			{}

			pair& operator= (const pair& pr)
			{
				if (pr == *this)
					return (*this);
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			}
	};

	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	template <class T1,class T2>
	ft::pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( ft::pair<T1,T2>(x,y) );
	}
}

#endif