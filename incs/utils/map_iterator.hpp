/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:21:22 by chanhuil          #+#    #+#             */
/*   Updated: 2022/07/06 17:48:26 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "./utils.hpp"

namespace ft
{
	template <class T>
	class Node {
		public:
			T*		v;
			Node*	p;
			Node*	left;
			Node*	right;	
			bool	black;

			explicit Node(T* v = ft_nullptr)
				:
				v(v),
				p(ft_nullptr),
				left(ft_nullptr),
				right(ft_nullptr),
				black(false)
			{}

			virtual ~Node(){}
	};

	template<typename T>
	class map_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef T*																			pointer;
			typedef T&																			reference;
			typedef Node<typename ft::remove_const<value_type>::type>*															node_pointer;

			map_iterator()
				: _p(ft_nullptr)
			{}

			map_iterator(node_pointer p)
				: _p(p)
			{}
			
			map_iterator(const map_iterator& iter)
				: _p(iter._p)
			{}

			map_iterator& operator=(const map_iterator& iter)
			{
				if (iter == *this)
					return *this;
				this->_p = iter.base();
				return *this;
			}

			virtual ~map_iterator()
			{}

			node_pointer base() const {return _p;}

			reference operator*() const {return *(_p->v);}
			pointer operator->() const {return _p->v;}

			map_iterator& operator++()
			{
				if (_p->right)
				{
					_p = minimum(_p->right);
				}
				else
				{
					node_pointer temp = _p->p;
					while (temp && _p == temp->right)
					{
						_p = temp;
						temp = temp->p;
					}
					_p = temp;
				}
				return *this;
			}

			map_iterator  operator++(int)
			{
				map_iterator temp = *this;
				++(*this);
				return temp;
			}

			map_iterator& operator--()
			{
				if (_p->left)
				{
					_p = maximum(_p->left);
				}
				else
				{
					node_pointer temp = _p->p;
					while (temp && _p == temp->left)
					{
						_p = temp;
						temp = temp->p;
					}
					_p = temp;
				}
				return *this;
			}

			map_iterator  operator--(int)
			{
				map_iterator temp = *this;
				--(*this);
				return temp;
			}

			operator map_iterator<const T> () const
            { return (map_iterator<const T>(this->_p)); }

		private:
			node_pointer _p;
			
			node_pointer minimum(node_pointer n)
			{
				while (n->left)
					n = n->left;
				return n;
			}

			node_pointer maximum(node_pointer n)
			{
				while (n->right)
					n = n->right;
				return n;
			}
	};

	template <class T>
	bool operator== (const map_iterator<T>& lhs,
					const map_iterator<T>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class TL, class TR>
	bool operator== (const map_iterator<TL>& lhs,
					const map_iterator<TR>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T>
	bool operator!= (const map_iterator<T>& lhs,
					const map_iterator<T>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class TL, class TR>
	bool operator!= (const map_iterator<TL>& lhs,
					const map_iterator<TR>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
}

#endif