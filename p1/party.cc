/**
 * @file party.cc
 *
 * @brief
 *    Definition of class functions in party.h.
 *
 * @author Kyle Kruskamp
 * @date 2/10/16
 */

#include "party.h"

Party :: Party(const string& reservationName, int numDiners, int timeRequired)
{
   this->reservationName = new string (reservationName);
   this->numDiners = numDiners;
   this->timeRequired = timeRequired;
}

Party :: ~Party()
{
}
