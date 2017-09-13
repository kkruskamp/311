/**
 * @file restaurant.cc
 *
 * @brief
 *    Main simulation creates myDiner Restaurant object and calls functions on it.
 *
 *
 * @author Judy Challinger & Kyle Kruskamp
 * @date 2/10/16
 */


#include <iostream>
#include "restaurant.h"
#include "doublylinkedlist.h"
#include "table.h"
#include "party.h"

int main()
{
   Restaurant myDiner;
   myDiner.getInput();
   myDiner.serveParties();

   return 0;
}

//getInput function asks for input and then creates, and appends table and party objects to the available and waiting lists.
void Restaurant :: getInput()
{
   string input, tableID, serverName, resName;
   int numCust, numSeats, timeReq;

   while (input != "end")
   {
      std :: cin >> input;

      if (input == "table")
      {
         std :: cin >> tableID >> numSeats >> serverName;
         Table* table = new Table(tableID, numSeats, serverName);
         available.append(table);
      }

      else if (input == "party")
      {
         std :: cin >> numCust >> resName >> timeReq;
         Party* party = new Party(resName, numCust, timeReq);
         waiting.append(party);
      }
   }
}
void Restaurant :: serveParties ()
{
   //While the occupied list or the waiting list is not empty
   while (!occupied.empty() || !waiting.empty())
   {
      // the serveParties function will create a temp Table pointer and make it point to the first node in occupied
      Table* occTable = occupied.first();

      //While first one in occTable in not nullptr decrement timer
      while (occTable != nullptr)
      {
         occTable->decrementTimer();

         //if timer on table reaches 0 print guest name and table ID. 
         //Clear the table and append that table to the available list.
         //remove the node and move occTable pointer to next 
         //else just move the pointer to next on the list
         if (occTable->getTimer() == 0)
         {
            std :: cout << *(occTable->getParty()->getReservationName()) << " finished at " << *(occTable->getTableID())  << std :: endl;
            occTable->clearTable();
            available.append(occTable);
            occTable = occupied.remove();   
         }

         else
         {
            occTable = occupied.next();
         }
      }

      //create temp party pointer and point to first node in waiting list
      //while the pointer in not null create a second temp party variable and set it to party
      //point a temp table pointer to the first node in available list
      Party *party = waiting.first();

      while (party != nullptr)
      {
         Party *waitParty = party;
         Table *availTable = available.first();

         //while the pointer to the first node is not pointing to nullptr
         //if number of guests is less or equal to the number of seats
         //seat the the first party on the waiting list and set their timer to the time required given by input
         //print guest name and table name
         //keep track of server total by adding a running total of guests
         //remove and update party pointer
         //append first table on available list into the occupied list
         //remove and update availTable pointer
         while (availTable != nullptr)
         {  
            if (party->getNumDiners() <= availTable->getNumSeats())
            {
               availTable->seatParty(party);
               availTable->setTimer(party->getTimeRequired());
               std :: cout << *(party->getReservationName()) << " seated at " << *(availTable->getTableID()) << std :: endl;
               servers[*(availTable->getServerName())] += party->getNumDiners();
               party = waiting.remove();
               occupied.append(availTable);
               availTable = available.remove();
               break;
            }

            //else update availTable pointer to next node
            else
            {
               availTable = available.next();
            }
         }

         //if loop above isnt entered then party will not be updated through remove and will need to be updated
         if (waitParty == party)
         {
            party = waiting.next();
         }
      }
   }

   //map iterator is created and for each server it prints out first = name (string) second = total served (int)
   for (std :: map<string, int> :: iterator iter = servers.begin(); iter != servers.end(); ++iter)
   {
      std :: cout << iter->first << " served " << iter->second << std :: endl;
   }
}
