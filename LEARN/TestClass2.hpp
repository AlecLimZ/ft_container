/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestClass2.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:42:00 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/17 16:54:13 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTCLASS2_H
# define TESTCLASS2_H
#include "TestClass1.hpp"

class TestClass2
{
	private:
		bool	m_abc1;
	public:
		TestClass2(bool abc1) : m_abc1(abc1) {
			if (m_abc1)
				cout << "";
		}
		void	printTest();
};

#endif
