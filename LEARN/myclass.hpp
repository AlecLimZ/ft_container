/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myclass.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:31:06 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/18 09:35:41 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

template <typename T>
class MyClass
{
	public:
		MyClass(T t) { (void)t;}
		std::string getType() const;
};
