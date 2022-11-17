/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestClass1.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:59 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/17 16:59:23 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTCLASS1_H
# define TESTCLASS1_H

# include <iostream>

using std::endl;
using std::cout;
using std::cin;

class TestClass
{
	private:
		bool	m_bool1;
	public:
		TestClass(bool bool1): m_bool1(bool1) {}

		// just the template declaration
		template <typename T1, typename T2>
		void	templateFunction(T1 var1, T2 var2);
};

#endif
