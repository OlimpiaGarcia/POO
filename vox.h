// =========================================================
// File: vox.h
// Author: Olimpia García Huerta
// Date: 18/06/2022
// Description: this file creates an vox operator
// =========================================================

#ifndef VOXOPERATOR_H
#define VOXOPERATOR_H

#include "operator.h"

class VoxOperator : public Operator {
public:
  VoxOperator(int, double, double, double, int, OperatorType);
  VoxOperator(const VoxOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

//constructor que invoca al constructor de operartor
VoxOperator::VoxOperator(int ID, double TC, double MC, double NC, int discount, OperatorType t)
  : Operator(ID, TC, MC, NC, discount, t)
{

}

//constructor copia que invoca a operator
VoxOperator::VoxOperator(const VoxOperator &other)
: Operator(other)
{

}


double VoxOperator::calculateTalkingCost (int minutes, int age)
{
  if (minutes <= 0 || age < 0)
  {
    return 0;
  }
  if (age < 18 || age > 65)
  {
    return (talkingCharge * minutes) - (messageCost * minutes * (discountRate/100.0)); 
  }
  return (talkingCharge * minutes);
}

double VoxOperator::calculateMessageCost(int quantity, int thisOpid, int otherOpId)
{
  if (quantity <= 0)
  {
    return 0;
  }
  double cost = quantity * messageCost;
  if (thisOpid == otherOpId)
  {
    cost *= ((100.0 - discountRate) / 100.0);
  }
  return cost;
  
}

double VoxOperator::calculateNetworkCost(double gb)
{
  if (gb < 0)
  {
    return 0;
  }

  return networkCharge * gb;
  
}

#endif
