//
// Created by volodya on 12.12.2021.
//

#include "Record.h"

#include <utility>

const std::string &Record::getId() const {
    return _id;
}

Record::Record(std::string id, std::string name, std::string group, std::string birthday)
        : _id(std::move(id)), _name(std::move(name)), _group(std::move(group)), _birthday(std::move(birthday)) {}
