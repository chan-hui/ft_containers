/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:51:59 by chanhuil          #+#    #+#             */
/*   Updated: 2022/06/17 04:51:59 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <memory>
# include "./utils.hpp"
# include "./map_iterator.hpp"
# include "./reverse_iterator.hpp"

namespace ft
{
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T>>
	class red_black_tree
	{
		public:
			typedef T														value_type;
			typedef Compare													value_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::map_iterator<value_type>							iterator;
			typedef ft::map_iterator<const value_type>						const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;
			typedef typename Alloc::template rebind<Node<T>>::other			node_alloc;
			typedef typename node_alloc::pointer							node_pointer;

			red_black_tree(const Compare& comp, const Alloc& a = allocator_type())
				:
				_alloc(a),
				_nalloc(node_alloc()),
				_comp(comp),
				_root(ft_nullptr),
				_size(0)
			{
				initialize();
				_root = _end;
			}

			iterator begin()
			{
				if (_size == 0)
					return iterator(_end);
				return iterator(minimum(_root));
			}

			const_iterator begin() const
			{
				if (_size == 0)
					return const_iterator(_end);
				return const_iterator(minimum(_root));
			}

			iterator end()
			{
				return iterator(_end);
			}

			const_iterator end() const
			{
				return const_iterator(_end);
			}

			reverse_iterator rbegin()
			{
				reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const
			{
				const_reverse_iterator(end());
			}

			reverse_iterator rend()
			{
				reverse_iterator(begin());
			}

			const_reverse_iterator rend() const
			{
				const_reverse_iterator(begin());
			}

			bool empty() const
			{
				return (_size == 0);
			}

			size_type size() const
			{
				return _size;
			}

			size_type max_size() const
			{
				return _alloc.max_size();
			}

		private:
			allocator_type	_alloc;
			node_alloc		_nalloc;
			value_compare	_comp;
			node_pointer	_root;
			node_pointer	_end;
			size_type		_size;

			bool nil(node_pointer n)
			{
				if (!n || n == _end)
					return true;
				return false
			}

			void initialize()
			{
				_end = _nalloc.allocate(1);
				_nalloc.construct(_end, Node<T>());
				_end->v = _alloc.allocate(1);
				_alloc.construct(_end->v, T());
				_end->black = true;
			}

			node_pointer minimum(node_pointer n)
			{
				while (n && !nil(n->left))
					n = n->left;
				return n;
			}

			node_pointer maximum(node_pointer n)
			{
				while (n && !nil(n->right))
					n = n->right;
				return n;
			}

			void rotate_right(node_pointer n)
			{
				node_pointer y = n->left;
				n->left = y->right;
				if (!nil(y->right))
					y->right->p = n;
				y->p = n->p;
				if (!(n->p))
					_root = y;
				else if (n == n->p->left)
					n->p->left = y;
				else
					n->p->right = y;
				y->right = n;
				n->p = y;
			}

			void rotate_left(node_pointer n)
			{
				node_pointer y = n->right;
				n->right = y->left;
				if (!nil(y->left))
					y->left->p = n;
				y->p = n->p;
				if (!(n->p))
					_root = y;
				else if (n == n->p->left)
					n->p->left = y;
				else
					n->p->right = y;
				y->left = n;
				n->p = y;
			}

			node_pointer insert(node_pointer n)
			{
				if (_root == _end)
					_root = n;
				else
					insert_to(_root, n);
				return n;
			}

			node_pointer insert_to(node_pointer pos, node_pointer n)
			{
				if (_comp(*(n->v), *(pos->v)))
				{
					if (!nil(pos->left))
						return insert_to(pos->left, n);
					pos->left = n;
				}
				else
				{
					if (!nil(pos->right))
						return insert_to(pos->right, n);
					pos->right = n;
				}
				n->p = pos;
				return n;
			}

			void free_node(node_pointer n)
			{
				_alloc.destroy(n->v);
				_alloc.deallocate(n->v, 1);
				_nalloc.deallocate(n, 1);
			}

			void free_tree(node_pointer n)
			{
				if (!nil(n))
				{
					free_tree(n->left);
					free_tree(n->right);
					free_node(n);
				}
			}

			void transplant(node_pointer origin, node_pointer n)
			{
				if (origin == _root)
					_root = n;
				else if (origin = origin->p->left)
					origin->p->left = n;
				else
					origin->p->right = n;
				n->p = origin->p;
			}
	};
}

#endif