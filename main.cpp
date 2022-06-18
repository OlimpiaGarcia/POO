// =========================================================
// File: main.cpp
// Author:
// Date:
// Description:
// To compile: g++ -std=c++11 main.cpp -o app
// To execute: ./app input_file output_file
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"

using namespace std;

int main(int argc, char* argv[]) 
{
  ifstream inputFile;
  ofstream outputFile;
  int C, O, N, ins; //C= # de clientes, O = # de operadores, N = # de eventos, ope = auxiliar
  int custcreat, opecreat;
  string name;
  int age, opId ;
  int opType, discountRate;
  int id1,id2,time, quantity;
  double gb, amount, limitAmount;
  double talkingCharge, messageCost, networkCharge;
  vector<Customer*> customers;
  vector<Operator*> op;

 if (argc != 3) 
 {
  cout << "usage: " << argv[0] << " input_file output_file\n";
  return -1;
 }

  inputFile.open(argv[1]);
  if (!inputFile.is_open()) 
  {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }
  
  outputFile.open(argv[2]);

  inputFile >> C >> O >> N;
  customers.resize(C);
  op.resize(O);
  custcreat = 0;
  opecreat = 0;

  for (int i = 0; i < N; i++ )
  {
    inputFile >> ins;

    switch (ins)
    {
    case 1: 
    cout << "1" << endl;
    inputFile >> name >> age >> opId >> limitAmount;
    customers[custcreat] = new Customer(custcreat, name, age, op[opId], limitAmount);
    custcreat ++; 
    break;
  
    case 2: 
    cout << "2" << endl; 
    inputFile >> opType >> talkingCharge >> messageCost >> networkCharge >> discountRate;
   if (opType == 1)
   { 
    op[opecreat] = new VoxOperator(opecreat,talkingCharge, messageCost, networkCharge, discountRate, VOX);
    opecreat++;
   }
   else 
   {
    op[opecreat] = new InternetOperator(opecreat, talkingCharge, messageCost, networkCharge, discountRate, INTERNET);
   opecreat++;
   }
   
    break;

    case 3: 
    cout << "3" << endl; 
    inputFile >> id1 >> id2 >> time;
    customers[id1]->talk(time, *customers[id2]);
    break;

    case 4: 
    cout << "4" << endl;
    inputFile >> id1 >> id2 >> quantity;
    customers[id1]->message(quantity, *customers[id2]);
    break;

    case 5: 
    cout << "5" << endl;
    inputFile >> id1 >> gb;
    customers[id1]->connection(gb);
    break;

    case 6: //apuntador a customer? 
    cout << "6" << endl;
    inputFile >> id1 >> amount;
    customers[id1]->getBill()->pay(amount);
    break;

    case 7: // apuntador a operator?
    cout << "7" << endl;
    inputFile >> id1 >> opId;
    customers[id1]->setOperator(op[opId]);
    break;

    case 8: 
    cout << "8" << endl;
    inputFile >> id1 >> limitAmount;
    customers[id1]->getBill()->changeTheLimit(limitAmount);
    break;
    }
  }


for (Operator *oper : op)

{
  outputFile << oper->toString() << "\n"; 
  
}


for (Customer *C: customers)
{
  outputFile << C->toString() << "\n";
}

//meterlo a un for como el de arriba que itera customer

Customer *moretalk = customers[0];
Customer *moregb = customers[0];
Customer *moresms = customers[0];
for (Customer *C: customers)
{
  if (C->getTotalSpentTalkingTime()  >  moretalk->getTotalSpentTalkingTime())
  {
    moretalk = C;
  }
  if (C->getTotalMessageSent()  >  moresms->getTotalMessageSent())
  {
    moresms = C;
  }
  if (C->getTotalInternetUsage()  >  moregb->getTotalInternetUsage())
  {
    moregb = C;
  } 
}

outputFile << "more talk " << moretalk->getTotalSpentTalkingTime() << "\n";
outputFile << "more sms " << moresms->getTotalMessageSent() << "\n";
outputFile << "more gb " << moregb->getTotalInternetUsage() << "\n";

inputFile.close();
outputFile.close();
 
return 0;
}

