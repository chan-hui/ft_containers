/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 01:58:20 by chanhuil          #+#    #+#             */
/*   Updated: 2022/07/03 01:58:20 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <vector>
#include <stack>
#include <map>
#include <set>

#include "./incs/vector.hpp"
#include "./incs/stack.hpp"
#include "./incs/map.hpp"
#include "./incs/set.hpp"

void vector_test()
{
	vector_test_iter();
	vector_test_size();
	vector_test_element();
	vector_test_assign();
	vector_test_push_back();
	vector_test_pop_back();
	vector_test_insert();
	vector_test_erase();
	vector_test_swap();
	vector_test_clear();
	vector_test_alloc();
	vector_test_non_member();
}

int main()
{
	std::cout << "======== Vector Test ========\n";
	vector_test();
}