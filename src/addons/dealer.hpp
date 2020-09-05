// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef DEALER_HPP_INCLUDED
#define DEALER_HPP_INCLUDED

#include "..\libs.hpp"
#include "..\var.hpp"
#include "..\proc.hpp"
#include "..\config.hpp"

bool genDealerDatabase(std::string file = "cars.txt");

void databaseCheckout();

void dealerInfo(bool isBuy);

void printDatabase(bool showDiff = false);

void dealer();



#endif