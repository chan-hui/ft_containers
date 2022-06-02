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
	
}

#endif