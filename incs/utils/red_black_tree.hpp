/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:51:59 by chanhuil          #+#    #+#             */
/*   Updated: 2022/07/06 19:09:08 by chanhuil         ###   ########.fr       */
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
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
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
			typedef typename Alloc::template rebind<Node<T> >::other		node_alloc;
			typedef typename node_alloc::pointer							node_pointer;
			typedef Node<const T>*											const_node_pointer;

			red_black_tree()
				:
				_alloc(allocator_type()),
				_nalloc(node_alloc()),
				_comp(value_compare()),
				_root(ft_nullptr),
				_temp(ft_nullptr),
				_size(0)
			{
				initialize();
				_root = _end;
			}

			red_black_tree(const Compare& comp, const Alloc& alloc = allocator_type())
				:
				_alloc(alloc),
				_nalloc(node_alloc()),
				_comp(comp),
				_root(ft_nullptr),
				_temp(ft_nullptr),
				_size(0)
			{
				initialize();
				_root = _end;
			}

			template<class InputIterator>
			red_black_tree(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last,
			const Compare& comp, const Alloc& alloc = allocator_type())
		  	 	:
				_alloc(alloc),
				_nalloc(node_alloc()),
				_comp(comp),
				_root(ft_nullptr),
				_temp(ft_nullptr),
				_size(0)
			{
				initialize();
				_root = _end;
				for (;first != last;first++)
					insert(*first);
			}

			red_black_tree(const red_black_tree& tree)
				:
				_comp(tree._comp)
			{
				*this = tree;
			}

			red_black_tree& operator=(const red_black_tree& tree)
			{
				if (tree == *this)
					return *this;
				_alloc = tree._alloc;
				_nalloc = tree._nalloc;
				_comp = tree._comp;
				_size = tree._size;
				_temp = ft_nullptr;
				if (!_root)
					initialize();
				else
					free_tree(_root);
				
				if (tree._size == 0)
					_root = _end;
				else
					_root = node_dup_rec(tree._root, ft_nullptr, tree._end);

				node_pointer temp_end = maximum(_root);
				temp_end->right = _end;
				_end->p = temp_end;

				return *this;
			}

			~red_black_tree()
			{
				if(!empty())
					free_tree(_root);
				_alloc.destroy(_end->v);
				_alloc.deallocate(_end->v, 1);
				_nalloc.deallocate(_end, 1);
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
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			bool empty() const
			{
				return (_size == 0);
			}

			size_type size() const
			{
				return _size;
			}

			ft::pair<iterator,bool> insert (const value_type& val)
			{
				node_pointer check = find_node(val, _root);
				if (!nil(check))
					return ft::pair<iterator, bool>(iterator(check), false);
				node_pointer temp = _nalloc.allocate(1);
				_nalloc.construct(temp, Node<value_type>(alloc_value(val)));
				temp->left = ft_nullptr;
				temp->right = ft_nullptr;
				_insert(temp);
				_insert_fix(temp);
				_size++;
				node_pointer temp_end = maximum(_root);
				temp_end->right = _end;
				_end->p = temp_end;
				return ft::pair<iterator, bool>(iterator(temp), true);
			}

			iterator insert (iterator position, const value_type& val)
			{
				node_pointer check = find_node(val, _root);
				if (!nil(check))
					return iterator(check);
				node_pointer temp = _nalloc.allocate(1);
				_nalloc.construct(temp, Node<value_type>(alloc_value(val)));
				temp->left = ft_nullptr;
				temp->right = ft_nullptr;
				if (position == begin() && position != end() && _comp(val, *position))
					_insert_at(temp, minimum(_root));
				else if (position == end() && position != begin() && _comp(*(--position), val))
					_insert_at(temp, _end->p);
				else
					_insert_at(temp, _root);
				_insert_fix(temp);
				_size++;
				node_pointer temp_end = maximum(_root);
				temp_end->right = _end;
				_end->p = temp_end;
				return iterator(temp);
			}

			template <class InputIterator>
			void insert (typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last)
			{
				for (;first != last;first++)
					insert(*first);
			}

			void erase (iterator position)
			{
				node_pointer y = position.base();
				node_pointer x = ft_nullptr;
				bool is_black = y->black;
				
				std::cout << _root << "|" << _root->black << "\n";

				if (nil(y->left))
				{
					if (!(y->right))
					{
						y->right = init_temp();
						_temp->p = y;
						_temp->black = true;
					}
					x = y->right;
					transplant(y, y->right);
				}
				else if (nil(y->right))
				{
					if (!(y->left))
					{
						y->left = init_temp();
						_temp->p = y;
						_temp->black = true;
					}
					x = y->left;
					transplant(y, y->left);
				}
				else
				{
					std::cout << "holy fuck\n";
					node_pointer temp = y->right; //4422
					node_pointer temp_min = minimum(temp); //4422
					is_black = temp_min->black;
					if (!(temp_min->right))
					{
						temp_min->right = init_temp();
						_temp->p = temp_min;
						_temp->black = true;
					}
					x = temp_min->right; // 9999
					if (temp_min->p != temp)
					{
						transplant(temp_min, temp_min->right);
						temp_min->right = temp->right;
						temp->right->p = temp_min;
					}
					transplant(temp, temp_min);
					temp_min->left = temp->left;
					temp_min->left->p = temp_min; // seg_fault
					temp_min->black = temp->black;
				}
				free_node(y);
				if (is_black)
				{
					_erase_fix(x);
				}
				if (_temp)
					dest_temp();
				_size--;
				if (_size == 0)
					_root = _end;
				else
				{
					node_pointer temp_end = maximum(_root);
					temp_end->right = _end;
					_end->p = temp_end;
				}
			}

			size_type erase (const value_type& k)
			{
				node_pointer temp = find_node(k, _root);
				if (temp)
				{
					erase(iterator(temp));
					return (1);
				}
				return (0);
			}

			void erase (iterator first, iterator last)
			{
				for (;first != last;first++)
					erase(first);
			}

			void swap (red_black_tree& x)
			{
				allocator_type temp_alloc = x._alloc;
				node_alloc temp_nalloc = x._nalloc;
				value_compare temp_comp = x._comp;
				node_pointer temp_root = x._root;
				node_pointer temp_end = x._end;
				size_type temp_size = x._size;

				x._alloc = _alloc;
				x._nalloc = _nalloc;
				x._comp = _comp;
				x._root = _root;
				x._end = _end;
				x._size = _size;

				_alloc = temp_alloc;
				_nalloc = temp_nalloc;
				_comp = temp_comp;
				_root = temp_root;
				_end = temp_end;
				_size = temp_size;
			}

			void clear()
			{
				free_tree(_root);
				_root = _end;
				_end->p = ft_nullptr;
				_size = 0;
			}

			value_compare value_comp() const
			{
				return _comp;
			}

			iterator find (const value_type& k)
			{
				return iterator(find_node(k, _root));
			}

			const_iterator find (const value_type& k) const
			{
				return const_iterator(find_node(k, _root));
			}

			size_type count (const value_type& k) const
			{
				if (find(k) == end())
					return 0;
				return 1;
			}

			iterator lower_bound (const value_type& k)
			{
				for (iterator i=begin();i != end();i++)
				{
					if (!_comp(*i, k))
						return i;
				}
				return (end());
			}

			const_iterator lower_bound (const value_type& k) const
			{
				for (const_iterator i=begin();i != end();i++)
				{
					if (!_comp(*i, k))
						return i;
				}
				return (end());
			}

			iterator upper_bound (const value_type& k)
			{
				for (iterator i=begin();i != end();i++)
				{
					if (_comp(k, *i))
						return i;
				}
				return (end());
			}

			const_iterator upper_bound (const value_type& k) const
			{
				for (const_iterator i=begin();i != end();i++)
				{
					if (_comp(k, *i))
						return i;
				}
				return (end());
			}

			pair<const_iterator,const_iterator>	equal_range (const value_type& k) const
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			pair<iterator,iterator>	equal_range (const value_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			allocator_type get_allocator() const
			{
				return _alloc;
			}
			
		private:
			allocator_type	_alloc;
			node_alloc		_nalloc;
			value_compare	_comp;
			node_pointer	_root;
			node_pointer	_end;
			node_pointer	_temp;
			size_type		_size;

			bool nil(node_pointer n) const
			{
				if (!n || n == _end || n == _temp)
					return true;
				return false;
			}

			void initialize()
			{
				_end = _nalloc.allocate(1);
				_nalloc.construct(_end, Node<T>());
				_end->v = _alloc.allocate(1);
				_alloc.construct(_end->v, T());
				_end->black = true;
			}

			node_pointer minimum(node_pointer n) const
			{
				while (n && !nil(n->left))
					n = n->left;
				return n;
			}

			node_pointer maximum(node_pointer n) const
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

			node_pointer _insert(node_pointer n)
			{
				if (_root == _end)
					_root = n;
				else
					_insert_to(_root, n);
				return n;
			}

			node_pointer _insert_at(node_pointer n, node_pointer pos)
			{
				if (_root == _end)
					_root = n;
				else
					_insert_to(pos, n);
				return n;
			}

			node_pointer _insert_to(node_pointer pos, node_pointer n)
			{
				if (_comp(*(n->v), *(pos->v)))
				{
					if (!nil(pos->left))
						return _insert_to(pos->left, n);
					pos->left = n;
				}
				else
				{
					if (!nil(pos->right))
						return _insert_to(pos->right, n);
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
				else if (origin == origin->p->left)
					origin->p->left = n;
				else
					origin->p->right = n;
				n->p = origin->p;
			}

			node_pointer find_node(const value_type& value, node_pointer n) const
			{
				if (nil(n))
					return _end;
				else if (_comp(value, *(n->v)))
					return find_node(value, n->left);
				else if (_comp(*(n->v), value))
					return find_node(value, n->right);
				return n;
			}

			node_pointer node_dup(node_pointer n, node_pointer e)
			{
				if (!n || n == e)
					return ft_nullptr;
				node_pointer temp = _nalloc.allocate(1);
				_nalloc.construct(temp, Node<T>());
				temp->black = n->black;
				if (n->v)
				{
					temp->v = _alloc.allocate(1);
					_alloc.construct(temp->v, *(n->v));
				}
				return temp;
			}

			node_pointer node_dup_rec(node_pointer n, node_pointer p, node_pointer e)
			{
				node_pointer temp = node_dup(n, e);
				if (temp)
				{
					temp->p = p;
					temp->left = node_dup_rec(n->left, temp, e);
					temp->right = node_dup_rec(n->right, temp, e);
				}
				return temp;
			}

			pointer alloc_value(const value_type& v)
			{
				pointer temp = _alloc.allocate(1);
				_alloc.construct(temp, v);
				return temp;
			}

			void _insert_fix(node_pointer n)
			{
				node_pointer uncle = ft_nullptr;
				if (n != _root && n->p != _root)
				{
					while (n != _root && !n->p->black)
					{
						if (n->p == n->p->p->left)
						{
							uncle = n->p->p->right;
							if (!uncle || uncle->black)
							{
								if (n == n->p->right)
								{
									n = n->p;
									rotate_left(n);
								}
								n->p->black = true;
								n->p->p->black = false;
								rotate_right(n->p->p);
							}
							else
							{
								n->p->black = true;
								uncle->black = true;
								n->p->p->black = false;
								n = n->p->p;
							}
						}
						else
						{
							uncle = n->p->p->left;
							if (!uncle || uncle->black)
							{
								if (n == n->p->left)
								{
									n = n->p;
									rotate_right(n);
								}
								n->p->black = true;
								n->p->p->black = false;
								rotate_left(n->p->p);
							}
							else
							{
								n->p->black = true;
								uncle->black = true;
								n->p->p->black = false;
								n = n->p->p;
							}
						}
					}
				}
				_root->black = true;
			}

			void _erase_fix(node_pointer n)
			{
				node_pointer brother = ft_nullptr;
				
				while (n != _root && n->black)
				{
					if (n == n->p->left)
					{
						brother = n->p->right;
						if (brother && !brother->black)
						{
							brother->black = true;
							n->p->black = false;
							rotate_left(n->p);
							brother = n->p->right;
						}
						if ((!brother->left || brother->left->black) && (!brother->right || brother->right->black))
						{
							brother->black = false;
							n = n->p;
						}
						else
						{
							if (!brother->right || brother->right->black)
							{
								brother->left->black = true;
								brother->black = false;
								rotate_right(brother);
								brother = n->p->right;
							}
							brother->black = n->p->black;
							n->p->black = true;
							brother->right->black = true;
							rotate_left(n->p);
							n = _root;
						}
					}
					else
					{
						brother = n->p->left;
						if (brother && !brother->black)
						{
							brother->black = true;
							n->p->black = false;
							rotate_right(n->p);
							brother = n->p->right;
						}
						if ((!brother->left || brother->left->black) && (!brother->right || brother->right->black))
						{
							brother->black = false;
							n = n->p;
						}
						else
						{
							if (!brother->left || brother->left->black)
							{
								brother->right->black = true;
								brother->black = false;
								rotate_left(brother);
								brother = n->p->left;
							}
							brother->black = n->p->black;
							n->p->black = true;
							brother->left->black = true;
							rotate_right(n->p);
							n = _root;
						}
					}
				}
			}

			node_pointer init_temp()
			{
				_temp = _nalloc.allocate(1);
				_nalloc.construct(_temp, Node<T>());
				_temp->v = _alloc.allocate(1);
				_alloc.construct(_temp->v, T());
				_temp->black = true;
				return _temp;
			}

			void dest_temp()
			{
				if (_temp->p)
				{
					if (_temp->p->left == _temp)
						_temp->p->left = ft_nullptr;
					else
						_temp->p->right = ft_nullptr;
				}
				_alloc.destroy(_temp->v);
				_alloc.deallocate(_temp->v, 1);
				_nalloc.deallocate(_temp, 1);
				_temp = ft_nullptr;
			}
	};

	template<class T, class Compare, class Alloc>
	bool operator==(const red_black_tree<T, Compare, Alloc>& lhs, const red_black_tree<T, Compare, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class T, class Compare, class Alloc>
	bool operator<(const red_black_tree<T, Compare, Alloc>& lhs, const red_black_tree<T, Compare, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
}

#endif