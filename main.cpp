/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 01:58:20 by chanhuil          #+#    #+#             */
/*   Updated: 2022/07/07 15:08:02 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <vector>
#include <stack>
#include <map>

#include "./incs/vector.hpp"
#include "./incs/stack.hpp"
#include "./incs/map.hpp"

void vector_print(std::string name, ft::vector<int> v)
{
	std::cout << "ft::vector " << name << " has [";
	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << ' ';
	std::cout << "✅ ]\n";
}

void vector_print(std::string name, std::vector<int> v)
{
	std::cout << "std::vector " << name << " has [";
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << ' ';
	std::cout << "✅ ]\n";
}

void vector_iterator_print(std::string name, ft::vector<int>::iterator it)
{
	std::cout << "ft::vector::iterator " << name << " is pointing [" << *it << "]\n";
}

void vector_iterator_print(std::string name, ft::vector<int>::reverse_iterator it)
{
	std::cout << "ft::vector::iterator " << name << " is pointing [" << *it << "]\n";
}

void vector_iterator_print(std::string name, std::vector<int>::iterator it)
{
	std::cout << "std::vector::iterator " << name << " is pointing [" << *it << "]\n";
}

void vector_iterator_print(std::string name, std::vector<int>::reverse_iterator it)
{
	std::cout << "std::vector::iterator " << name << " is pointing [" << *it << "]\n";
}

void map_print(std::string name, ft::map<int, std::string> m)
{
	std::cout << "ft::map " << name << " has [ ";
	for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << "(" << it->first << ", " << it->second << ") ";
	std::cout << "(✅ ) ]\n";
}

void map_print(std::string name, std::map<int, std::string> m)
{
	std::cout << "ft::map " << name << " has [ ";
	for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << "(" << it->first << ", " << it->second << ") ";
	std::cout << "(✅ ) ]\n";
}

void ft_vector_test_construct()
{

	ft::vector<int> first;                                // empty vector of ints
	ft::vector<int> second (4,100);                       // four ints with value 100
	ft::vector<int> third (second.begin(),second.end());  // iterating through second
	ft::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {4,2,42,4242};
	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	vector_print("first", first);
	vector_print("second", second);
	vector_print("third", third);
	vector_print("fourth", fourth);
	vector_print("fifth", fifth);
}

void std_vector_test_construct()
{

	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (4,100);                       // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {4,2,42,4242};
	std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	vector_print("first", first);
	vector_print("second", second);
	vector_print("third", third);
	vector_print("fourth", fourth);
	vector_print("fifth", fifth);
}

void vector_test_construct()
{
	std::cout << "---------------- ft::constructor ----------------\n";
	ft_vector_test_construct();
	std::cout << "\n";
	std::cout << "---------------- std::constructor ----------------\n";
	std_vector_test_construct();
	std::cout << "\n\n";
}

void ft_vector_test_iter()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );

	vector_iterator_print("begin", v.begin());
	vector_iterator_print("end", --v.end());
	vector_iterator_print("rbegin", v.rbegin());
	vector_iterator_print("rend", --v.rend());

	std::cout << "reversed ft::vector v has [";
	for (ft::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << ' ';
	std::cout << "✅ ]\n";
}

void std_vector_test_iter()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );

	vector_iterator_print("begin", v.begin());
	vector_iterator_print("end", --v.end());
	vector_iterator_print("rbegin", v.rbegin());
	vector_iterator_print("rend", --v.rend());

	std::cout << "reversed std::vector v has [";
	for (std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << ' ';
	std::cout << "✅ ]\n";
}

void vector_test_iter()
{
	std::cout << "---------------- ft::iterator ----------------\n";
	ft_vector_test_iter();
	std::cout << "\n";
	std::cout << "---------------- std::iterator ----------------\n";
	std_vector_test_iter();
	std::cout << "\n\n";
}

void ft_vector_test_size()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );

	vector_print("v", v);
	std::cout << "v.size : " << v.size() << "\n";
	std::cout << "v.max_size : " << v.max_size() << "\n";

	v.resize(3);
	vector_print("v", v);
	v.resize(8, 4422);
	vector_print("v", v);
  	v.resize(12);
	vector_print("v", v);

	std::cout << "\n";

	vector_print("v", v);
	std::cout << "v.empty : " << v.empty() << "\n";
	ft::vector<int> v2;
	vector_print("v2", v2);
	std::cout << "v2.empty : " << v2.empty() << "\n";
}

void std_vector_test_size()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );

	vector_print("v", v);
	std::cout << "v.size : " << v.size() << "\n";
	std::cout << "v.max_size : " << v.max_size() << "\n";

	v.resize(3);
	vector_print("v", v);
	v.resize(8, 4422);
	vector_print("v", v);
  	v.resize(12);
	vector_print("v", v);

	std::cout << "\n";

	vector_print("v", v);
	std::cout << "v.empty : " << v.empty() << "\n";
	std::vector<int> v2;
	vector_print("v2", v2);
	std::cout << "v2.empty : " << v2.empty() << "\n";
}

void vector_test_size()
{
	std::cout << "---------------- ft::size ----------------\n";
	ft_vector_test_size();
	std::cout << "\n";
	std::cout << "---------------- std::size ----------------\n";
	std_vector_test_size();
	std::cout << "\n\n";
}

void ft_vector_test_capacity()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );

	vector_print("v", v);
	std::cout << "v.size : " << v.size() << "\n";
	std::cout << "v.capacity : " << v.capacity() << "\n";
	v.push_back(4422);
	vector_print("v", v);
	std::cout << "v.size : " << v.size() << "\n";
	std::cout << "v.capacity : " << v.capacity() << "\n";

	std::cout << "\n";

	std::cout << "v.reserve(7)\n";
	v.reserve(7);
	std::cout << "v.capacity : " << v.capacity() << "\n";
	std::cout << "v.reserve(12)\n";
	v.reserve(12);
	std::cout << "v.capacity : " << v.capacity() << "\n";
}

void std_vector_test_capacity()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );

	vector_print("v", v);
	std::cout << "v.size : " << v.size() << "\n";
	std::cout << "v.capacity : " << v.capacity() << "\n";
	v.push_back(4422);
	vector_print("v", v);
	std::cout << "v.size : " << v.size() << "\n";
	std::cout << "v.capacity : " << v.capacity() << "\n";

	std::cout << "\n";

	std::cout << "v.reserve(7)\n";
	v.reserve(7);
	std::cout << "v.capacity : " << v.capacity() << "\n";
	std::cout << "v.reserve(12)\n";
	v.reserve(12);
	std::cout << "v.capacity : " << v.capacity() << "\n";
}

void vector_test_capacity()
{
	std::cout << "---------------- ft::capacity ----------------\n";
	ft_vector_test_capacity();
	std::cout << "\n";
	std::cout << "---------------- std::capacity ----------------\n";
	std_vector_test_capacity();
	std::cout << "\n\n";
}

void ft_vector_test_element()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v[1] : " << v[1] << "\n";
	std::cout << "v.at(2) : " << v.at(2) << "\n";
	try
	{
		std::cout << "v.at(5) : " << v.at(5) << "\n";
	}
	catch(const std::exception& e)
	{
		std::cout << "exception thrown!\n";
	}
	std::cout << "v.front : " << v.front() << "\n";
	std::cout << "v.back : " << v.back() << "\n";
}

void std_vector_test_element()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v[1] : " << v[1] << "\n";
	std::cout << "v.at(2) : " << v.at(2) << "\n";
	try
	{
		std::cout << "v.at(5) : " << v.at(5) << "\n";
	}
	catch(const std::exception& e)
	{
		std::cout << "exception thrown!\n";
	}
	std::cout << "v.front : " << v.front() << "\n";
	std::cout << "v.back : " << v.back() << "\n";
}

void vector_test_element()
{
	std::cout << "---------------- ft::element ----------------\n";
	ft_vector_test_element();
	std::cout << "\n";
	std::cout << "---------------- std::element ----------------\n";
	std_vector_test_element();
	std::cout << "\n\n";
}

void ft_vector_test_assign()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);

	std::cout << "v.assign(7,100)\n";
	v.assign(7,100);
	vector_print("v", v);
	std::cout << "v.assign(myints, myints + 3)\n";
	v.assign(myints, myints + 3);
	vector_print("v", v);
}

void std_vector_test_assign()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);

	std::cout << "v.assign(7,100)\n";
	v.assign(7,100);
	vector_print("v", v);
	std::cout << "v.assign(myints, myints + 3)\n";
	v.assign(myints, myints + 3);
	vector_print("v", v);
}

void vector_test_assign()
{
	std::cout << "---------------- ft::assign ----------------\n";
	ft_vector_test_assign();
	std::cout << "\n";
	std::cout << "---------------- std::assign ----------------\n";
	std_vector_test_assign();
	std::cout << "\n\n";
}

void ft_vector_test_push_back()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.push_back(4422)\n";
	v.push_back(4422);
	vector_print("v", v);
	std::cout << "v.push_back(424242)\n";
	v.push_back(424242);
	vector_print("v", v);
}

void std_vector_test_push_back()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.push_back(4422)\n";
	v.push_back(4422);
	vector_print("v", v);
	std::cout << "v.push_back(424242)\n";
	v.push_back(424242);
	vector_print("v", v);
}

void vector_test_push_back()
{
	std::cout << "---------------- ft::push_back ----------------\n";
	ft_vector_test_push_back();
	std::cout << "\n";
	std::cout << "---------------- std::push_back ----------------\n";
	std_vector_test_push_back();
	std::cout << "\n\n";
}

void ft_vector_test_pop_back()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.pop_back()\n";
	v.pop_back();
	vector_print("v", v);
	std::cout << "v.pop_back()\n";
	v.pop_back();
	vector_print("v", v);
}

void std_vector_test_pop_back()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.pop_back()\n";
	v.pop_back();
	vector_print("v", v);
	std::cout << "v.pop_back()\n";
	v.pop_back();
	vector_print("v", v);
}

void vector_test_pop_back()
{
	std::cout << "---------------- ft::pop_back ----------------\n";
	ft_vector_test_pop_back();
	std::cout << "\n";
	std::cout << "---------------- std::pop_back ----------------\n";
	std_vector_test_pop_back();
	std::cout << "\n\n";
}

void ft_vector_test_insert()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.insert(v.begin()+2, 4422)\n";
	v.insert(v.begin()+2, 4422);
	vector_print("v", v);
	std::cout << "v.insert(v.begin()+2, 4, 242)\n";
	v.insert(v.begin()+2, 4, 242);
	vector_print("v", v);
	std::cout << "v.insert(v.begin()+2, myints, myints + 3)\n";
	v.insert(v.begin()+2, myints, myints + 3);
	vector_print("v", v);
}

void std_vector_test_insert()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.insert(v.begin()+2, 4422)\n";
	v.insert(v.begin()+2, 4422);
	vector_print("v", v);
	std::cout << "v.insert(v.begin()+2, 4, 242)\n";
	v.insert(v.begin()+2, 4, 242);
	vector_print("v", v);
	std::cout << "v.insert(v.begin()+2, myints, myints + 3)\n";
	v.insert(v.begin()+2, myints, myints + 3);
	vector_print("v", v);
}

void vector_test_insert()
{
	std::cout << "---------------- ft::insert ----------------\n";
	ft_vector_test_insert();
	std::cout << "\n";
	std::cout << "---------------- std::insert ----------------\n";
	std_vector_test_insert();
	std::cout << "\n\n";
}

void ft_vector_test_erase()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.erase(v.begin()+2)\n";
	v.erase(v.begin()+2);
	vector_print("v", v);
	std::cout << "v.erase(v.begin(), v.end())\n";
	v.erase(v.begin(), v.end());
	vector_print("v", v);
}

void std_vector_test_erase()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.erase(v.begin()+2)\n";
	v.erase(v.begin()+2);
	vector_print("v", v);
	std::cout << "v.erase(v.begin(), v.end())\n";
	v.erase(v.begin(), v.end());
	vector_print("v", v);
}

void vector_test_erase()
{
	std::cout << "---------------- ft::erase ----------------\n";
	ft_vector_test_erase();
	std::cout << "\n";
	std::cout << "---------------- std::erase ----------------\n";
	std_vector_test_erase();
	std::cout << "\n\n";
}

void ft_vector_test_swap()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	int myints2[] = {44,22,4422,44224422};
	ft::vector<int> v2 (myints2, myints2 + sizeof(myints2) / sizeof(int) );
	
	vector_print("v", v);
	vector_print("v2", v2);

	std::cout << "v.swap(v2)\n";
	v.swap(v2);

	vector_print("v", v);
	vector_print("v2", v2);
}

void std_vector_test_swap()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	int myints2[] = {44,22,4422,44224422};
	std::vector<int> v2 (myints2, myints2 + sizeof(myints2) / sizeof(int) );
	
	vector_print("v", v);
	vector_print("v2", v2);

	std::cout << "v.swap(v2)\n";
	v.swap(v2);

	vector_print("v", v);
	vector_print("v2", v2);
}

void vector_test_swap()
{
	std::cout << "---------------- ft::swap ----------------\n";
	ft_vector_test_swap();
	std::cout << "\n";
	std::cout << "---------------- std::swap ----------------\n";
	std_vector_test_swap();
	std::cout << "\n\n";
}

void ft_vector_test_clear()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.clear()\n";
	v.clear();
	vector_print("v", v);
}

void std_vector_test_clear()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	
	vector_print("v", v);
	std::cout << "v.clear()\n";
	v.clear();
	vector_print("v", v);
}

void vector_test_clear()
{
	std::cout << "---------------- ft::clear ----------------\n";
	ft_vector_test_clear();
	std::cout << "\n";
	std::cout << "---------------- std::clear ----------------\n";
	std_vector_test_clear();
	std::cout << "\n\n";
}

void ft_vector_test_non_member()
{
	int myints[] = {4,2,42,4242};
	ft::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	ft::vector<int> v2 (myints, myints + sizeof(myints) / sizeof(int) );
	ft::vector<int> v3 (myints, myints + 2 );
	
	vector_print("v", v);
	vector_print("v2", v2);
	vector_print("v3", v3);
	std::cout << "v == v2 : " << (v == v2) << "\n";
	std::cout << "swap(v, v3)\n";
	swap(v, v3);
	vector_print("v", v);
	vector_print("v3", v3);
}

void std_vector_test_non_member()
{
	int myints[] = {4,2,42,4242};
	std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
	std::vector<int> v2 (myints, myints + sizeof(myints) / sizeof(int) );
	std::vector<int> v3 (myints, myints + 2 );
	
	vector_print("v", v);
	vector_print("v2", v2);
	vector_print("v3", v3);
	std::cout << "v == v2 : " << (v == v2) << "\n";
	std::cout << "swap(v, v3)\n";
	swap(v, v3);
	vector_print("v", v);
	vector_print("v3", v3);
}

void vector_test_non_member()
{
	std::cout << "---------------- ft::non_member ----------------\n";
	ft_vector_test_non_member();
	std::cout << "\n";
	std::cout << "---------------- std::non_member ----------------\n";
	std_vector_test_non_member();
	std::cout << "\n\n";
}

void vector_test()
{
	vector_test_construct();
	vector_test_iter();
	vector_test_size();
	vector_test_capacity();
	vector_test_element();
	vector_test_assign();
	vector_test_push_back();
	vector_test_pop_back();
	vector_test_insert();
	vector_test_erase();
	vector_test_swap();
	vector_test_clear();
	vector_test_non_member();
}

void ft_stack_test_size()
{
	ft::stack<int> s;
	s.push(4);
	s.push(2);
	s.push(42);
	s.push(4242);

	std::cout << "s.size() : " << s.size() << "\n";
}

void std_stack_test_size()
{
	std::stack<int> s;
	s.push(4);
	s.push(2);
	s.push(42);
	s.push(4242);

	std::cout << "s.size() : " << s.size() << "\n";
}

void stack_test_size()
{
	std::cout << "---------------- ft::size ----------------\n";
	ft_stack_test_size();
	std::cout << "\n";
	std::cout << "---------------- std::size ----------------\n";
	std_stack_test_size();
	std::cout << "\n\n";
}

void ft_stack_test_top()
{
	ft::stack<int> s;
	s.push(4);
	s.push(2);
	s.push(42);
	s.push(4242);

	std::cout << "s.top() : " << s.top() << "\n";
}

void std_stack_test_top()
{
	std::stack<int> s;
	s.push(4);
	s.push(2);
	s.push(42);
	s.push(4242);

	std::cout << "s.top() : " << s.top() << "\n";
}

void stack_test_top()
{
	std::cout << "---------------- ft::top ----------------\n";
	ft_stack_test_top();
	std::cout << "\n";
	std::cout << "---------------- std::top ----------------\n";
	std_stack_test_top();
	std::cout << "\n\n";
}

void ft_stack_test_push_pop()
{
	ft::stack<int> s;
	
	s.push(4);
	std::cout << "s.top() : " << s.top() << "\n";
	s.push(2);
	std::cout << "s.top() : " << s.top() << "\n";
	s.push(42);
	std::cout << "s.top() : " << s.top() << "\n";
	s.push(4242);
	std::cout << "s.top() : " << s.top() << "\n";
	s.pop();
	std::cout << "s.top() : " << s.top() << "\n";
	s.pop();
	std::cout << "s.top() : " << s.top() << "\n";
}

void std_stack_test_push_pop()
{
	std::stack<int> s;
	
	s.push(4);
	std::cout << "s.top() : " << s.top() << "\n";
	s.push(2);
	std::cout << "s.top() : " << s.top() << "\n";
	s.push(42);
	std::cout << "s.top() : " << s.top() << "\n";
	s.push(4242);
	std::cout << "s.top() : " << s.top() << "\n";
	s.pop();
	std::cout << "s.top() : " << s.top() << "\n";
	s.pop();
	std::cout << "s.top() : " << s.top() << "\n";
}

void stack_test_push_pop()
{
	std::cout << "---------------- ft::push-pop ----------------\n";
	ft_stack_test_push_pop();
	std::cout << "\n";
	std::cout << "---------------- std::push-pop ----------------\n";
	std_stack_test_push_pop();
	std::cout << "\n\n";
}

void ft_stack_test_non_member()
{
	ft::stack<int> s;
	ft::stack<int> s2;
	ft::stack<int> s3;
	
	s.push(4);
	s2.push(4);
	s3.push(2);

	std::cout << "s == s2 : " << (s == s2) << "\n";
	std::cout << "s == s3 : " << (s == s3) << "\n";
}

void std_stack_test_non_member()
{
	std::stack<int> s;
	std::stack<int> s2;
	std::stack<int> s3;
	
	s.push(4);
	s2.push(4);
	s3.push(2);

	std::cout << "s == s2 : " << (s == s2) << "\n";
	std::cout << "s == s3 : " << (s == s3) << "\n";
}

void stack_test_non_member()
{
	std::cout << "---------------- ft::non_member ----------------\n";
	ft_stack_test_non_member();
	std::cout << "\n";
	std::cout << "---------------- std::non_member ----------------\n";
	std_stack_test_non_member();
	std::cout << "\n\n";
}

void stack_test()
{
	stack_test_size();
	stack_test_top();
	stack_test_push_pop();
	stack_test_non_member();
}

void ft_map_test_construct()
{
	ft::map<int, std::string> m;
	map_print("m", m);

	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";

	ft::map<int, std::string> m2(m.begin(), m.end());
	map_print("m2", m2);

	ft::map<int, std::string> m3(m2);
	map_print("m3", m3);
}

void std_map_test_construct()
{
	std::map<int, std::string> m;
	map_print("m", m);

	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";


	std::map<int, std::string> m2(m.begin(), m.end());
	map_print("m2", m2);

	std::map<int, std::string> m3(m2);
	map_print("m3", m3);
}

void map_test_construct()
{
	std::cout << "---------------- ft::constructor ----------------\n";
	ft_map_test_construct();
	std::cout << "\n";
	std::cout << "---------------- std::constructor ----------------\n";
	std_map_test_construct();
	std::cout << "\n\n";
}

void ft_map_test_iter()
{
	ft::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";

	map_print("m", m);
	std::cout << "m.begin() : (" << m.begin()->first << ", " << m.begin()->second << ")\n";
	ft::map<int, std::string>::iterator temp = m.end();
	--temp;
	std::cout << "m.end() : (" << temp->first << ", " << temp->second << ")\n";
	for (ft::map<int, std::string>::reverse_iterator i = m.rbegin();i != m.rend(); i++)
	{
		std::cout << "(" << i->first << ", " << i->second << ") ";
	}
	std::cout << "\n";
}

void std_map_test_iter()
{
	std::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";

	map_print("m", m);
	std::cout << "m.begin() : (" << m.begin()->first << ", " << m.begin()->second << ")\n";
	std::map<int, std::string>::iterator temp = m.end();
	--temp;
	std::cout << "m.end() : (" << temp->first << ", " << temp->second << ")\n";
	for (std::map<int, std::string>::reverse_iterator i = m.rbegin();i != m.rend(); i++)
	{
		std::cout << "(" << i->first << ", " << i->second << ") ";
	}
	std::cout << "\n";
}

void map_test_iter()
{
	std::cout << "---------------- ft::iterator ----------------\n";
	ft_map_test_iter();
	std::cout << "\n";
	std::cout << "---------------- std::iterator ----------------\n";
	std_map_test_iter();
	std::cout << "\n\n";
}

void ft_map_test_size()
{
	ft::map<int, std::string> m;
	map_print("m", m);
	std::cout << "m.empty() : " << m.empty() << "\n";

	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	
	map_print("m", m);
	std::cout << "m.empty() : " << m.empty() << "\n";
	std::cout << "m.size() : " << m.size() << "\n";
	std::cout << "m.max_size() : " << m.max_size() << "\n";
}

void std_map_test_size()
{
	std::map<int, std::string> m;
	map_print("m", m);
	std::cout << "m.empty() : " << m.empty() << "\n";

	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	
	map_print("m", m);
	std::cout << "m.empty() : " << m.empty() << "\n";
	std::cout << "m.size() : " << m.size() << "\n";
	std::cout << "m.max_size() : " << m.max_size() << "\n";
}

void map_test_size()
{
	std::cout << "---------------- ft::size ----------------\n";
	ft_map_test_size();
	std::cout << "\n";
	std::cout << "---------------- std::size ----------------\n";
	std_map_test_size();
	std::cout << "\n\n";
}

void ft_map_test_element()
{
	ft::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	
	map_print("m", m);
	std::cout << "m[4] : " << m[4] << "\n";
}

void std_map_test_element()
{
	std::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	
	map_print("m", m);
	std::cout << "m[4] : " << m[4] << "\n";
}

void map_test_element()
{
	std::cout << "---------------- ft::element ----------------\n";
	ft_map_test_element();
	std::cout << "\n";
	std::cout << "---------------- std::element ----------------\n";
	std_map_test_element();
	std::cout << "\n\n";
}

void ft_map_test_insert()
{
	ft::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";

	map_print("m", m);

	std::cout << "m.insert(ft::pair<int, std::string>(4242, \"inserting\"))\n";
	m.insert(ft::pair<int, std::string>(4242, "inserting"));
	map_print("m", m);

	// second insert function version (with hint position):
	ft::map<int, std::string>::iterator it = m.begin();
	std::cout << "m.insert(it, ft::pair<int, std::string>(24, \"max efficiency inserting\"))\n";
	std::cout << "m.insert(it, ft::pair<int, std::string>(4422, \"no max efficiency inserting\"))\n";
	m.insert(it, ft::pair<int, std::string>(24, "max efficiency inserting"));
	m.insert(it, ft::pair<int, std::string>(4422, "no max efficiency inserting"));
	map_print("m", m);

	// third insert function version (range insertion):
	ft::map<int, std::string> m2;
	std::cout << "m2.insert(m.begin(), m.find(42))\n";
	m2.insert(m.begin(), m.find(42));
	map_print("m2", m2);
}

void std_map_test_insert()
{
	std::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";

	map_print("m", m);

	std::cout << "m.insert(std::pair<int, std::string>(4242, \"inserting\"))\n";
	m.insert(std::pair<int, std::string>(4242, "inserting"));
	map_print("m", m);

	// second insert function version (with hint position):
	std::map<int, std::string>::iterator it = m.begin();
	std::cout << "m.insert(it, std::pair<int, std::string>(24, \"max efficiency inserting\"))\n";
	std::cout << "m.insert(it, std::pair<int, std::string>(4422, \"no max efficiency inserting\"))\n";
	m.insert(it, std::pair<int, std::string>(24, "max efficiency inserting"));
	m.insert(it, std::pair<int, std::string>(4422, "no max efficiency inserting"));
	map_print("m", m);

	// third insert function version (range insertion):
	std::map<int, std::string> m2;
	std::cout << "m2.insert(m.begin(), m.find(42))\n";
	m2.insert(m.begin(), m.find(42));
	map_print("m2", m2);
}

void map_test_insert()
{
	std::cout << "---------------- ft::insert ----------------\n";
	ft_map_test_insert();
	std::cout << "\n";
	std::cout << "---------------- std::insert ----------------\n";
	std_map_test_insert();
	std::cout << "\n\n";
}

void ft_map_test_erase()
{
	ft::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	m[4242] = "random quote here";
	m[4422] = "final string";
	m[424242] = "extra one";

	map_print("m", m);

	m.erase(m.begin());
	std::cout << "m.erase(m.begin())\n";
	map_print("m", m);

	m.erase(4242);
	std::cout << "m.erase(4242)\n";
	map_print("m", m);

	m.erase(m.find(4), m.find(4422));
	std::cout << "m.erase(m.find(4), m.find(4422))\n";
	map_print("m", m);
}

void std_map_test_erase()
{
	std::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	m[4242] = "random quote here";
	m[4422] = "final string";
	m[424242] = "extra one";

	map_print("m", m);

	m.erase(m.begin());
	std::cout << "m.erase(m.begin())\n";
	map_print("m", m);

	m.erase(4242);
	std::cout << "m.erase(4242)\n";
	map_print("m", m);

	m.erase(m.find(4), m.find(4422));
	std::cout << "m.erase(m.find(4), m.find(4422))\n";
	map_print("m", m);
}

void map_test_erase()
{
	std::cout << "---------------- ft::erase ----------------\n";
	ft_map_test_erase();
	std::cout << "\n";
	std::cout << "---------------- std::erase ----------------\n";
	std_map_test_erase();
	std::cout << "\n\n";
}

void ft_map_test_swap()
{
	ft::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";

	ft::map<int, std::string> m2;
	m2[4242] = "random quote here";
	m2[4422] = "final string";
	m2[424242] = "extra one";

	map_print("m", m);
	map_print("m2", m2);

	m.swap(m2);
	std::cout << "m.swap(m2)\n";

	map_print("m", m);
	map_print("m2", m2);
}

void std_map_test_swap()
{
	std::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";

	std::map<int, std::string> m2;
	m2[4242] = "random quote here";
	m2[4422] = "final string";
	m2[424242] = "extra one";

	map_print("m", m);
	map_print("m2", m2);

	m.swap(m2);
	std::cout << "m.swap(m2)\n";

	map_print("m", m);
	map_print("m2", m2);
}

void map_test_swap()
{
	std::cout << "---------------- ft::swap ----------------\n";
	ft_map_test_swap();
	std::cout << "\n";
	std::cout << "---------------- std::swap ----------------\n";
	std_map_test_swap();
	std::cout << "\n\n";
}

void ft_map_test_clear()
{
	ft::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	
	map_print("m", m);

	m.clear();
	std::cout << "m.clear()\n";
	map_print("m", m);
}

void std_map_test_clear()
{
	std::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	
	map_print("m", m);

	m.clear();
	std::cout << "m.clear()\n";
	map_print("m", m);
}

void map_test_clear()
{
	std::cout << "---------------- ft::clear ----------------\n";
	ft_map_test_clear();
	std::cout << "\n";
	std::cout << "---------------- std::clear ----------------\n";
	std_map_test_clear();
	std::cout << "\n\n";
}

void ft_map_test_find()
{
	ft::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	
	map_print("m", m);

	std::cout << "m.find(4)->second : " << m.find(4)->second << "\n";
	std::cout << "m.find(42)->second : " << m.find(42)->second << "\n";

	std::cout << "m.count(4) : " << m.count(4) << "\n";
	std::cout << "m.count(42) : " << m.count(42) << "\n";
	std::cout << "m.count(4242) : " << m.count(4242) << "\n";
}

void std_map_test_find()
{
	std::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	
	map_print("m", m);

	std::cout << "m.find(4)->second : " << m.find(4)->second << "\n";
	std::cout << "m.find(42)->second : " << m.find(42)->second << "\n";

	std::cout << "m.count(4) : " << m.count(4) << "\n";
	std::cout << "m.count(42) : " << m.count(42) << "\n";
	std::cout << "m.count(4242) : " << m.count(4242) << "\n";
}

void map_test_find()
{
	std::cout << "---------------- ft::find ----------------\n";
	ft_map_test_find();
	std::cout << "\n";
	std::cout << "---------------- std::find ----------------\n";
	std_map_test_find();
	std::cout << "\n\n";
}

void ft_map_test_bound()
{
	ft::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	m[4242] = "random quote here";
	m[4422] = "final string";
	m[424242] = "extra one";
	
	map_print("m", m);

	for (ft::map<int, std::string>::iterator it = m.lower_bound(10); it != m.upper_bound(5000); ++it)
    	std::cout << "(" << it->first << ", " << it->second << ")\n";
}

void std_map_test_bound()
{
	std::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	m[4242] = "random quote here";
	m[4422] = "final string";
	m[424242] = "extra one";
	
	map_print("m", m);

	for (std::map<int, std::string>::iterator it = m.lower_bound(10); it != m.upper_bound(5000); ++it)
    	std::cout << "(" << it->first << ", " << it->second << ")\n";
}

void map_test_bound()
{
	std::cout << "---------------- ft::bound ----------------\n";
	ft_map_test_bound();
	std::cout << "\n";
	std::cout << "---------------- std::bound ----------------\n";
	std_map_test_bound();
	std::cout << "\n\n";
}

void ft_map_test_equal_range()
{
	ft::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	m[4242] = "random quote here";
	m[4422] = "final string";
	m[424242] = "extra one";
	
	map_print("m", m);

	std::cout << "lower bound to 42\n";
	std::cout << "(" << m.equal_range(42).first->first << ", " << m.equal_range(42).first->second << ")\n";
	std::cout << "upper bound to 42\n";
	std::cout << "(" << m.equal_range(42).second->first << ", " << m.equal_range(42).second->second << ")\n";
}

void std_map_test_equal_range()
{
	std::map<int, std::string> m;
	m[2] = "42Seoul";
	m[4] = "Hello, World!";
	m[42] = "lorem ipsum";
	m[4242] = "random quote here";
	m[4422] = "final string";
	m[424242] = "extra one";
	
	map_print("m", m);

	std::cout << "lower bound to 42\n";
	std::cout << "(" << m.equal_range(42).first->first << ", " << m.equal_range(42).first->second << ")\n";
	std::cout << "upper bound to 42\n";
	std::cout << "(" << m.equal_range(42).second->first << ", " << m.equal_range(42).second->second << ")\n";
}

void map_test_equal_range()
{
	std::cout << "---------------- ft::equal_range ----------------\n";
	ft_map_test_equal_range();
	std::cout << "\n";
	std::cout << "---------------- std::equal_range ----------------\n";
	std_map_test_equal_range();
	std::cout << "\n\n";
}

void map_test()
{
	map_test_construct();
	map_test_iter();
	map_test_size();
	map_test_element();
	map_test_insert();
	map_test_erase();
	map_test_swap();
	map_test_clear();
	map_test_find();
	map_test_bound();
	map_test_equal_range();
}

int main()
{	
	std::cout << "================ Vector Test ================\n\n";
	vector_test();
	std::cout << "================ Stack Test ================\n\n";
	stack_test();
	std::cout << "================ Map Test ================\n\n";
	map_test();
	// system("leaks ft_containers");
}