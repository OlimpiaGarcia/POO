// =========================================================
// File: customer.h
// Author: Olimpia Garcia Huerta
// Date: 18/06/2022
// Description: thiss file create a customer
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

class Customer {
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  std::string name;
  Operator* op;
  Bill *bill;

public:
  Customer(int, std::string, int, Operator*, double);
  Customer(const Customer&);
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  std::string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void setOperator(Operator*);

  std::string toString() const;

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
  void pay(double);
};

Customer::Customer(int ID, std::string N, int A, Operator* ope, double limit)
{
 bill = new Bill(limit); //objeto clase bill
 id = ID;
 name = N;
 age = A;
 op = ope;
 totalSpentTalkingTime = 0;
 totalMessageSent = 0;
 totalInternetUsage = 0;
}

Customer::Customer(const Customer &other)
{
  id = other.id;
  age = other.age;
  totalSpentTalkingTime = other.totalSpentTalkingTime;
  totalMessageSent = other.totalMessageSent;
  totalInternetUsage = other.totalInternetUsage;
  name = other.name;
  op = other.op;
  bill = other.bill;
}

Customer::~Customer()
{
  delete bill;
  bill = 0;
  op = 0;
}

int Customer::getId() const
{
  return id;
}

int Customer::getAge() const
{
  return age;
}

int Customer::getTotalSpentTalkingTime() const
{
  return totalSpentTalkingTime;
}

int Customer::getTotalMessageSent() const
{
  return totalMessageSent;
}

double Customer::getTotalInternetUsage() const
{
  return totalInternetUsage;
}

std::string Customer::getName() const
{
  return name;
}

Operator* Customer::getOperator() const
{
  return op;
}

Bill* Customer::getBill() const
{
  return bill;
}

void Customer::setOperator(Operator *other )
{
  op = other;
}

void Customer::talk(int minutes, Customer &other)
{
  if (minutes > 0 && id !=  other.id)
  {
    double charges = op->calculateTalkingCost(minutes, age); 
    if (bill->check(charges) == true)
  {
    bill->add(charges);
    op->addTalkingTime(minutes);
    totalSpentTalkingTime += minutes;

    if (op->getId() != other.op->getId())
  {
    other.op->addTalkingTime(minutes);
  }
  }
  }
}

void Customer::message(int quantity, const Customer &other)
{
  if (quantity > 0 && id !=  other.id)
  {
  double charges = op->calculateMessageCost(quantity, op->getId(), other.op->getId());
  if (bill->check(charges) == true)
  {
    bill->add(charges);
    op->addTotalMessageSent(quantity);
    totalMessageSent += quantity;
  }
  }
}

void Customer::connection(double amount)
{
  if (amount > 0)
  {
    double charges = op->calculateNetworkCost(amount);
    if (bill->check(charges) == true)
  {
    bill->add(charges);
    op->addTotalInternetUsage(amount);
    totalInternetUsage +=amount;
  }
  }
}

//tostring 
std::string Customer::toString() const
{
  std::stringstream aux;

  aux << "Customer " << std::fixed <<std::setprecision(2) << getId()
  <<" " << std::fixed <<std::setprecision(2) <<  bill->getTotalMoneySpent()
  << " " << std::fixed <<std::setprecision(2) << bill->getCurrentDebt();
  return aux.str();
}


#endif
