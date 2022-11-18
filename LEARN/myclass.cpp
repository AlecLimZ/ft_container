/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myclass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:32:24 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/18 09:33:15 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myclass.hpp"

template <typename T>
std::string MyClass<T>::getType() const
{
	return (typeid(T).name());
}

template class MyClass<int>;
