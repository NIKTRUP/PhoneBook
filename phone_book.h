#pragma once

#include "iterator_range.h"
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <contact.pb.h>

struct Date {
    int year, month, day;
};

struct Contact {
    std::string name;
    std::optional<Date> birthday;
    std::vector<std::string> phones;
};


class PhoneBook {
public:
    explicit PhoneBook(std::vector<Contact> contacts);

    using ConstIterator = std::vector<Contact>::const_iterator;

    using ContactRange = IteratorRange<ConstIterator>;

    ContactRange FindByNamePrefix(std::string_view name_prefix) const;

    void SaveTo(std::ostream& output) const;
private:
    std::vector<Contact> contacts_;
};

PhoneBook DeserializePhoneBook(std::istream& input);