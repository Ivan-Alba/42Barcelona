/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:35:28 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/16 15:05:22 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Account.hpp"

static int Account::getNbAccounts(void)
{
	return _nbAccounts;
}

static int Account::getTotalAmount(void)
{
	return _totalAmount;
}

static int Account::getNbDeposits(void)
{
	return _totalNbDeposits;
}

static int Account::getNbWithdrawals(void)
{
	return _totalNbWithdrawals;
}

static void	displayAccountsInfos(void)
{
	std::cout << "accounts:" + getNbAccounts() + ";total:" + getTotalAmount() +
		";deposits:" + getNbDeposits() + ";withdrawals:" + getNbWithdrawals
		<< endl;
}
