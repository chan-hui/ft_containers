/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 01:28:22 by chanhuil          #+#    #+#             */
/*   Updated: 2022/07/04 17:12:11 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "./utils.hpp"

namespace ft
{
	template<typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef T*																			pointer;
			typedef T&																			reference;

			random_access_iterator()
				: _p(ft_nullptr)
			{}

			random_access_iterator(pointer p)
				: _p(p)
			{}
			
			random_access_iterator(const random_access_iterator& iter)
				: _p(iter._p)
			{}

			random_access_iterator& operator=(const random_access_iterator& iter)
			{
				if (iter == *this)
					return *this;
				this->_p = iter.base();
				return *this;
			}

			virtual ~random_access_iterator()
			{}

			pointer base() const {return _p;}

			reference operator*() const {return *_p;}
			pointer operator->() const {return _p;}

			random_access_iterator& operator++()
			{
				++_p;
				return *this;
			}

			random_access_iterator  operator++(int)
			{
				random_access_iterator temp = *this;
				++(*this);
				return temp;
			}

			random_access_iterator& operator--()
			{
				--_p;
				return *this;
			}

			random_access_iterator  operator--(int)
			{
				random_access_iterator temp = *this;
				--(*this);
				return temp;
			}

			random_access_iterator operator+ (difference_type n) const
			{
				return (random_access_iterator(_p + n));
			}

			random_access_iterator operator- (difference_type n) const
			{
				return (random_access_iterator(_p - n));
			}

			random_access_iterator& operator+= (difference_type n)
			{
				_p += n;
				return *this;
			}

			random_access_iterator& operator-= (difference_type n)
			{
				_p -= n;
				return *this;
			}

			reference operator[] (difference_type n) const
			{
				return _p[n];
			}
		private:
			pointer _p;
	};

	template <class T>
	bool operator== (const random_access_iterator<T>& lhs,
					const random_access_iterator<T>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class TL, class TR>
	bool operator== (const random_access_iterator<TL>& lhs,
					const random_access_iterator<TR>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T>
	bool operator!= (const random_access_iterator<T>& lhs,
					const random_access_iterator<T>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class TL, class TR>
	bool operator!= (const random_access_iterator<TL>& lhs,
					const random_access_iterator<TR>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class T>
	bool operator<  (const random_access_iterator<T>& lhs,
					const random_access_iterator<T>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class TL, class TR>
	bool operator<  (const random_access_iterator<TL>& lhs,
					const random_access_iterator<TR>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class T>
	bool operator<= (const random_access_iterator<T>& lhs,
					const random_access_iterator<T>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class TL, class TR>
	bool operator<= (const random_access_iterator<TL>& lhs,
					const random_access_iterator<TR>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class T>
	bool operator>  (const random_access_iterator<T>& lhs,
					const random_access_iterator<T>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class TL, class TR>
	bool operator>  (const random_access_iterator<TL>& lhs,
					const random_access_iterator<TR>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class T>
	bool operator>= (const random_access_iterator<T>& lhs,
					const random_access_iterator<T>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class TL, class TR>
	bool operator>= (const random_access_iterator<TL>& lhs,
					const random_access_iterator<TR>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class T>
	random_access_iterator<T> operator+ (
				typename random_access_iterator<T>::difference_type n,
				const random_access_iterator<T>& ran_it)
	{
		return (ran_it+n);
	}
	
	template <class T>
	typename random_access_iterator<T>::difference_type operator- (
		const random_access_iterator<T>& lhs,
		const random_access_iterator<T>& rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <class TL, class TR>
	typename random_access_iterator<TL>::difference_type operator- (
		const random_access_iterator<TL>& lhs,
		const random_access_iterator<TR>& rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif