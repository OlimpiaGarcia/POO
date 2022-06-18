// =========================================================
// File: vox.h
// Author:
// Date:
// Description:
// =========================================================

#ifndef InternetOperator_H
#define InternetOperator_H

#include "operator.h"

class InternetOperator : public Operator {
private:
  const double LIMITGB = 10.0;

public:
  InternetOperator(int, double, double, double, int, OperatorType);
  InternetOperator(const InternetOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

InternetOperator::InternetOperator(int ID, double TC, double MC, double NC, int discount, OperatorType t)
  : Operator(ID, TC, MC, NC, discount, t)
{

}

InternetOperator::InternetOperator(const InternetOperator &other)
: Operator(other)
{
  
}

double InternetOperator::calculateTalkingCost (int minutes, int age)
{
  if (minutes <= 0 || age < 0)
  {
    return 0;
  }
  if (minutes < 2)
  {
    return (talkingCharge * minutes) - (talkingCharge * minutes * (discountRate/100.0)); //esta o 
  }
  return talkingCharge * minutes;

}

double InternetOperator::calculateMessageCost(int quantity, int thisOpid, int otherOpId)
{
  if (quantity <= 0)
  {
    return 0;
  }
  if (quantity < 3)
  {
    return (quantity * messageCost) - (messageCost * quantity * (discountRate/100.0)); // esta?
  }
  return messageCost * quantity;
  
}

double InternetOperator::calculateNetworkCost(double gb)
{
  if (gb <= 0)
  {
   return 0;
  }
  if (gb > 1) 
  {
    return networkCharge * (gb-1);
  }
  return networkCharge *gb;
}


#endif
