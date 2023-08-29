#include "phone_book.h"

using namespace std;

namespace {
    struct Comparator {
        bool operator()(const Contact& lhs, const Contact& rhs) const {
            return lhs.name < rhs.name;
        }

        bool operator()(const Contact& lhs, std::string_view rhs) const {
            return lhs.name < rhs;
        }

        bool operator()(std::string_view lhs, const Contact& rhs) const {
            auto [lp, rp] = std::mismatch(lhs.begin(), lhs.end(), rhs.name.begin(), rhs.name.end());
            return lp != lhs.end() && rp != rhs.name.end() && *lp < *rp;
        }
    };
}

PhoneBook::PhoneBook(std::vector<Contact> contacts): contacts_(std::move(contacts)){
    std::sort(contacts_.begin(), contacts_.end(), Comparator());
}

PhoneBook::ContactRange PhoneBook::FindByNamePrefix(std::string_view name_prefix) const{
    return std::equal_range(contacts_.cbegin(), contacts_.cend(), name_prefix, Comparator());
}

void PhoneBook::SaveTo(std::ostream& output) const{
    phone_book_serialize::ContactList list;
    for (const auto& contact : contacts_) {
        auto& person = *list.add_contact();
        person.set_name(contact.name);
        if (contact.birthday.has_value()) {
            auto& birthday = *person.mutable_birthday();
            birthday.set_year(contact.birthday->year);
            birthday.set_month(contact.birthday->month);
            birthday.set_day(contact.birthday->day);
        }
        *person.mutable_phone_number() = {contact.phones.begin(), contact.phones.end()};
    }
    list.SerializeToOstream(&output);
}

PhoneBook DeserializePhoneBook(std::istream& input){
    phone_book_serialize::ContactList list;
    list.ParseFromIstream(&input);

    auto get_birthday = [](phone_book_serialize::Contact& contact){
        if (contact.has_birthday()) {
            return std::optional<Date>({contact.birthday().year(), contact.birthday().month(), contact.birthday().day()});
        }
        return std::optional<Date>{std::nullopt};
    };

    vector<Contact> phone_book;
    phone_book.reserve(list.contact_size());
    for (auto& item : *list.mutable_contact()) {
        const auto& numbers =  *item.mutable_phone_number();
        phone_book.emplace_back(std::move(Contact{std::move(*item.mutable_name()), get_birthday(item), {numbers.begin(), numbers.end()} }));
    }

    return PhoneBook(std::move(phone_book));
}