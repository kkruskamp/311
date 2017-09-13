/**
 * @file table.cc
 *
 * @brief
 *    Definition of class functions in table.h
 *
 * @author Kyle Kruskamp
 * @date 2/10/16
 */


#include "table.h"

//We use this because tableID and tableID have the same name therefore we have to specify which is the private and public variables
//TableID and serverName must be wrapped in a new string because const type had issues compiling
Table :: Table(const string& tableID, int numSeats, const string& serverName)
{
   this->tableID = new string(tableID);
   this->numSeats = numSeats;
   this->serverName = new string(serverName);
}

Table :: ~Table()
{

}

//Sets a party to newParty to hold it for use in seating parties
void Table :: seatParty(const Party *newParty)
{
   this->party = newParty;
}
