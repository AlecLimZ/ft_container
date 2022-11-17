/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestClass1.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:46:55 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/17 16:59:29 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestClass1.hpp"

template <typename T1, typename T2>
void TestClass::templateFunction(T1 var1, T2 var2)
{
	cout << "var1: " << var1 << ", ";
	cout << "var2: " << var2 << ", ";
	cout << "m_bool1: " << m_bool1 << "\n";
}

template void TestClass::templateFunction<char const*, char const*>(char const*, char const*);
