#ifndef TRAIN_SYSTEM_H
#define TRAIN_SYSTEM_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

enum class Command {
    CREATE_TRAIN,
    TRAINS_FOR_TOWN,
    TOWNS_FOR_TRAIN,
    TRAINS,
    EXIT,
    UNKNOWN
};

Command parse_command(const std::string& input);
void create_train(const std::string& train, const std::vector<std::string>& towns);
void trains_for_town(const std::string& town);
void towns_for_train(const std::string& train);
void trains();

#endif
