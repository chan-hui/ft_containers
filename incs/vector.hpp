/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:21:07 by chanhuil          #+#    #+#             */
/*   Updated: 2022/07/04 14:26:48 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "./utils/utils.hpp"
# include "./utils/random_access_iterator.hpp"
# include "./utils/reverse_iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T														value_type;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::random_access_iterator<value_type>					iterator;
		typedef ft::random_access_iterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type		difference_type;
		typedef typename allocator_type::size_type						size_type;

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
        vector (typename enable_if< !is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last, const allocator_type& alloc = allocator_type())
			:
			_alloc(alloc),
			_begin(ft_nullptr),
			_end(ft_nullptr),
			_capacity(ft_nullptr)
		{
			// if (ii != iter)
			// 	exception;
			difference_type n = ft::distance(first, last);
			_begin = _alloc.allocate(n);
			_end = _begin;
			_capacity = _begin + n;
			for (int i=0;i<n;i++)
			{
				_alloc.construct(_end, *first);
				_end++;
				first++;
			}
		}

		vector (const vector& x)
			:
			_alloc(x._alloc),
			_begin(ft_nullptr),
			_end(ft_nullptr),
			_capacity(ft_nullptr)
		{
			insert(end(), x.begin(), x.end());
		}

		~vector()
		{
			clear();
			if (_begin)
				_alloc.deallocate(_begin, capacity());
		}

		vector& operator= (const vector& x)
		{
			if (x == *this)
				return *this;
			clear();
			insert(end(), x.begin(), x.end());
			return *this;
		}

		iterator begin() {return iterator(_begin);}
		const_iterator begin() const {return const_iterator(_begin);}
		iterator end() {return iterator(_end);}
		const_iterator end() const {return const_iterator(_end);}

		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator rend() {return reverse_iterator(begin());}
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

		size_type size() const {return (_end - _begin);}
		size_type max_size() const {return allocator_type().max_size();}

		void resize (size_type n, value_type val = value_type())
		{
			if (n > max_size())
				throw std::overflow_error("vector is too big");
			else if (n < size())
			{
				while (size() > n)
				{
					--_end;
					_alloc.destroy(_end);
				}
			}
			else
				insert(end(), n - size(), val);
		}

		size_type capacity() const
		{
			return (_capacity - _begin);
		}

		bool empty() const
		{
			if (size() == 0)
				return true;
			return false;
		}

		void reserve (size_type n)
		{
			if (n > max_size())
				throw std::overflow_error("vector is too big");
			else if (n > capacity())
			{
				pointer temp_begin = _begin;
				pointer temp_end = _end;
				size_type temp_size = size();
				size_type temp_capacity = capacity();

				_begin = _alloc.allocate(n);
				_end = _begin;
				_capacity = _begin + n;
				while (temp_begin != temp_end)
				{
					_alloc.construct(_end, *temp_begin);
					_alloc.destroy(temp_begin);
					_end++;
					temp_begin++;
				}
				if (temp_begin)
					_alloc.deallocate(temp_begin - temp_size, temp_capacity);
			}
		}

		reference operator[] (size_type n) {return *(_begin + n);}
		const_reference operator[] (size_type n) const {return *(_begin + n);}

		reference at (size_type n)
		{
			if (n >= size())
				throw std::out_of_range("vector out of range");
			return (*this)[n];
		}

		const_reference at (size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("vector out of range");
			return (*this)[n];
		}

		reference front() {return *_begin;}
		const_reference front() const {return *_begin;}

		reference back() {return *(_end - 1);}
		const_reference back() const {return *(_end - 1);}

		template <class InputIterator>
		void assign (typename enable_if< !is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last)
		{
			// if (ii != iter)
			// 	exception;
			clear();
			size_type n = ft::distance(first, last);
			if (capacity() >= n)
			{
				for (;first != last;_end++,first++)
				{
					_alloc.construct(_end, *first);
				}
			}
			else
			{
				pointer temp_begin = _alloc.allocate(n);
				pointer temp_end = temp_begin;
				pointer temp_capacity = temp_begin + n;

				for (;first != last;temp_end++,first++)
				{
					_alloc.construct(temp_end, *first);
				}
				if (_begin)
					_alloc.deallocate(_begin, capacity());

				_begin = temp_begin;
				_end = temp_end;
				_capacity = temp_capacity;
			}
		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			if (n == 0)
				return ;
			if (capacity() >= n)
			{
				for (int i=0;i<n;i++,_end++)
				{
					_alloc.construct(_end, val);
				}
			}
			else
			{
				if (_begin)
					_alloc.deallocate(_begin, capacity());

				_begin = _alloc.allocate(n);
				_end = _begin;
				_capacity = _begin + n;

				for (int i=0;i<n;i++,_end++)
				{
					_alloc.construct(_end, val);
				}
			}
		}

		void push_back (const value_type& val)
		{
			if (_end == _capacity)
			{
				if (capacity() == 0)
					reserve(1);
				else
					reserve(capacity() * 2);
			}
			_alloc.construct(_end++, val);
		}

		void pop_back()
		{
			_alloc.destroy(--_end);
		}

		iterator insert (iterator position, const value_type& val)
		{
			if (size() < capacity())
			{
				for (pointer i = _end;i != &(*position);i--)
					_alloc.construct(i, *(i - 1));
				_alloc.construct(&(*position), val);
				_end++;
			}
			else
			{
				int new_cap = capacity() == 0 ? 1 : capacity() * 2;
				pointer temp_begin = _alloc.allocate(new_cap);
				pointer temp_end = temp_begin;
				pointer temp_capacity = temp_begin + new_cap;
				
				for (iterator i=begin();i != position;i++,temp_end++)
				{
					_alloc.construct(temp_end, *i);
				}
				_alloc.construct(temp_end++, val);
				for (iterator i=position;i != end();i++,temp_end++)
				{
					_alloc.construct(temp_end, *i);
				}

				clear();
				if (_begin)
					_alloc.deallocate(_begin, capacity());

				_begin = temp_begin;
				_end = temp_end;
				_capacity = temp_capacity;
			}
			return position;
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return ;
			if (n > max_size())
				throw std::overflow_error("vector is too big");
			if (capacity() - size() >= n)
			{
				for (pointer i = _end + n - 1;i != &(*position) + n - 1;i--)
					_alloc.construct(i, *(i - n));
				for (pointer i = &(*position);i != &(*position) + n;i++)
					_alloc.construct(i, val);
				_end += n;
			}
			else
			{
				int new_cap = capacity() == 0 ? 1 : capacity() * 2;
				if (n + size() > new_cap)
					new_cap = n + size();
				pointer temp_begin = _alloc.allocate(new_cap);
				pointer temp_end = temp_begin;
				pointer temp_capacity = temp_begin + new_cap;
				
				for (iterator i=begin();i != position;i++,temp_end++)
				{
					_alloc.construct(temp_end, *i);
				}
				for (int i=0;i<n;i++)
				{
					_alloc.construct(temp_end++, val);
				}
				for (iterator i=position;i != end();i++,temp_end++)
				{
					_alloc.construct(temp_end, *i);
				}

				clear();
				if (_begin)
					_alloc.deallocate(_begin, capacity());

				_begin = temp_begin;
				_end = temp_end;
				_capacity = temp_capacity;
			}
		}

		template <class InputIterator>
		void insert (iterator position, typename enable_if< !is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last)
		{
			// if (ii != iter)
			// 	exception;
			
			size_type n = ft::distance(first, last);
			if (n == 0)
				return ;
			if (capacity() - size() >= n)
			{
				for (pointer i = _end + n - 1;i != &(*position) + n - 1;i--)
					_alloc.construct(i, *(i - n));
				for (pointer i = &(*position);first != last;i++,first++)
					_alloc.construct(i, *first);
				_end += n;
			}
			else
			{
				int new_cap = capacity() == 0 ? 1 : capacity() * 2;
				if (n + size() > new_cap)
					new_cap = n + size();
				pointer temp_begin = _alloc.allocate(new_cap);
				pointer temp_end = temp_begin;
				pointer temp_capacity = temp_begin + new_cap;
				
				for (iterator i=begin();i != position;i++,temp_end++)
				{
					_alloc.construct(temp_end, *i);
				}
				for (InputIterator i=first;i != last;i++)
				{
					_alloc.construct(temp_end++, *i);
				}
				for (iterator i=position;i != end();i++,temp_end++)
				{
					_alloc.construct(temp_end, *i);
				}

				clear();
				if (_begin)
					_alloc.deallocate(_begin, capacity());

				_begin = temp_begin;
				_end = temp_end;
				_capacity = temp_capacity;
			}
		}

		iterator erase (iterator position)
		{
			pointer temp = &(*position);
			_alloc.destroy(temp);
			if (temp + 1 != _end)
			{
				for (;temp != _end;temp++)
				{
					_alloc.construct(temp, *(temp + 1));
					_alloc.destroy(temp + 1);
				}
			}
			_end--;
			return (position);
		}

		iterator erase (iterator first, iterator last)
		{
			pointer temp = &(*first);
			for (pointer i = temp;i != last;i++)
				_alloc.destroy(i);
			if (&(*last) != _end)
			{
				for (pointer f=temp, l=&(*last);l != _end;f++,l++)
				{
					_alloc.construct(f, *l);
					_alloc.destroy(l);
				}
			}
			_end -= (ft::distance(first, last));
			return (first);
		}

		void swap (vector& x)
		{
			allocator_type temp_alloc = x._alloc;
			pointer temp_begin = x._begin;
			pointer temp_end = x._end;
			pointer temp_capacity = x._capacity;

			x._alloc = _alloc;
			x._begin = _begin;
			x._end = _end;
			x._capacity = _capacity;

			_alloc = temp_alloc;
			_begin = temp_begin;
			_end = temp_end;
			_capacity = temp_capacity;
		}

		void clear()
		{
			size_type e = size();
			for (size_type i = 0;i<e;i++)
			{
				_end--;
				_alloc.destroy(_end);
			}
		}

		allocator_type get_allocator() const {return _alloc;}

	private:
		allocator_type	_alloc;
		pointer			_begin;
		pointer			_end;
		pointer			_capacity;
	};
	
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif