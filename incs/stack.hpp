/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:37:24 by chanhuil          #+#    #+#             */
/*   Updated: 2022/07/04 14:28:56 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

			explicit stack (const container_type& ctnr = container_type())
				:
				_c(ctnr)
			{}

			~stack ()
			{}

			bool empty() const {return _c.empty();}
			size_type size() const {return _c.size();}

			value_type& top() {return _c.back();}
			const value_type& top() const {return _c.back();}

			void push (const value_type& val) {_c.push_back(val);}
			void pop() {_c.pop_back();}
			
			template <class V, class Cont>
			friend bool operator== (const stack<V,Cont>& lhs, const stack<V,Cont>& rhs);

			template <class V, class Cont>
			friend bool operator!= (const stack<V,Cont>& lhs, const stack<V,Cont>& rhs);

			template <class V, class Cont>
			friend bool operator<  (const stack<V,Cont>& lhs, const stack<V,Cont>& rhs);
			
			template <class V, class Cont>
			friend bool operator<= (const stack<V,Cont>& lhs, const stack<V,Cont>& rhs);
			
			template <class V, class Cont>
			friend bool operator>  (const stack<V,Cont>& lhs, const stack<V,Cont>& rhs);
			
			template <class V, class Cont>
			friend bool operator>= (const stack<V,Cont>& lhs, const stack<V,Cont>& rhs);
			
		protected:
			container_type _c;
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c == rhs._c);
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c != rhs._c);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c < rhs._c);
	}
	
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c <= rhs._c);
	}
	
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c > rhs._c);
	}
	
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c >= rhs._c);
	}
}

#endif