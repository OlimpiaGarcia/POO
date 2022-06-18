// =========================================================
// File: operator.h
// Author:
// Date:
// Description:
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


typedef enum{VOX, INTERNET} OperatorType;

class Operator {
protected:
  int id, discountRate;
  double talkingCharge, messageCost, networkCharge, totalInternetUsage;
  int totalSpentTalkingTime, totalMessageSent;
  OperatorType type;

public:
  Operator(int, double, double, double, int, OperatorType);
  Operator(const Operator&);

  int getId() const;
  int getDiscountRate() const;
  double getTalkingChage() const;
  double getMessageCost() const;
  double getNetworkCharge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  OperatorType getType() const;

  void addTalkingTime(int);
  void addTotalMessageSent(int);
  void addTotalInternetUsage(double);

  std::string toString() const;

  virtual double calculateTalkingCost(int, int) = 0;
  virtual double calculateMessageCost(int, int, int) = 0;
  virtual double calculateNetworkCost(double) = 0;
};

Operator::Operator(int ID, double TC, double MC, double NC, int discount, OperatorType t)
{
  id = ID;
  talkingCharge = TC;
  messageCost = MC;
  networkCharge = NC;
  discountRate = discount;
  type = t;
  totalSpentTalkingTime = 0;
  totalMessageSent = 0;
  totalInternetUsage = 0;
}

Operator::Operator(const Operator &other)
{
  id = other.id;
  talkingCharge = other.talkingCharge;
  messageCost = other.messageCost;
  networkCharge = other.networkCharge;
  discountRate = other.discountRate;
  type = other.type;
  totalSpentTalkingTime = other.totalSpentTalkingTime;
  totalMessageSent = other.totalMessageSent;
  totalInternetUsage = other.totalInternetUsage;
}

int Operator::getId() const
{
  return id;
}

int Operator::getDiscountRate() const
{
  return discountRate;
}

double Operator::getTalkingChage() const
{
  return talkingCharge;
}

double Operator::getMessageCost() const
{
  return messageCost;
}

double Operator::getNetworkCharge() const
{
  return networkCharge;
}

int Operator::getTotalSpentTalkingTime() const
{
  return totalSpentTalkingTime;
}

int Operator::getTotalMessageSent() const
{
  return totalMessageSent;
}

double Operator::getTotalInternetUsage() const
{
  return totalInternetUsage;
}

OperatorType Operator::getType() const
{
  return type;
}

void Operator::addTalkingTime(int minutes)
{
  if (minutes < 0)
  {
    return;
  }
  totalSpentTalkingTime += minutes;

 }

void Operator::addTotalMessageSent(int quantity)
{
  if (quantity < 0)
  {
    return;
  }
  totalMessageSent += quantity;
}

void Operator::addTotalInternetUsage(double gb)
{
  if (gb < 0)
  {
    return;
  }
  totalInternetUsage += gb;

}

//to string 

std::string Operator::toString() const
{
  std::stringstream aux;

  aux << "Operator" << std::fixed <<std::setprecision(2) << getId()
  <<" " << std::fixed <<std::setprecision(2) <<  getTotalSpentTalkingTime()
  << " " << std::fixed <<std::setprecision(2) << getTotalMessageSent()
  << " " << std::fixed <<std::setprecision(2) << getTotalInternetUsage();

  return aux.str();
}


#endif
