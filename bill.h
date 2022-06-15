// =========================================================
// File: bill.h
// Author: Olimpia García Huerta
// Date:
// Description:
// =========================================================

#ifndef BILL_H
#define BILL_H
using namespace std;

class Bill  
{
private:
  double limitAmount, currentDebt, totalMoneySpent;

public:
  Bill();
  Bill(double);
  Bill(const Bill&);

  double getLimitAmount() const;
  double getCurrentDebt() const;
  double getTotalMoneySpent() const;

  void add(double);
  void pay(double);
  void changeTheLimit(double);
  bool check(double);
};

Bill::Bill()
{
  limitAmount = 0;
  currentDebt = 0;
  totalMoneySpent = 0;
};

Bill::Bill(double amount)
{
  limitAmount = amount > 0? amount : 0;
  currentDebt = 0;
  totalMoneySpent = 0;
};

Bill::Bill(const Bill &other)
{
  limitAmount = other.limitAmount;
  currentDebt = other.currentDebt;
  totalMoneySpent = other.totalMoneySpent;
};

double Bill::getLimitAmount() const
{
  return limitAmount;
}

double Bill::getCurrentDebt() const
{
  return currentDebt;
}

double Bill::getTotalMoneySpent() const
{
  return totalMoneySpent;
}

void Bill::add(double charges)
{
  if (charges <=0)
  {
    return; 
  }

  currentDebt += charges;
}

void Bill::pay(double pay)
{
 if (pay <= 0)
 {
   return;
 }
 if (pay > currentDebt)
 {
   totalMoneySpent += currentDebt;
   currentDebt = 0;
 }
else
{
  currentDebt -= pay;
  totalMoneySpent +=pay;
}
};

void Bill::changeTheLimit(double newLimit)
{
  if (newLimit <= currentDebt)
  {
    return;
  }
  if (newLimit <= 0)
  {
    return;
  }
  limitAmount = newLimit;
};

bool Bill::check(double charges)
{
  if ((charges + currentDebt) < limitAmount)
  {
    return true;
  }
  else 
  {
    return false;
  }
};

#endif
