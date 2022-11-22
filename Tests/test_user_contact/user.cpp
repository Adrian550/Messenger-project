#include "user.h"

User::User()
{
}

// contacts
void User::add_contact(std::string contact)
{
    current_contacts.push_back(contact);
}

void User::remove_contact(std::string contact)
{
    for (auto i = current_contacts.begin(); i != current_contacts.end(); i++)
    {
        if (*i == contact)
            current_contacts.erase(i);
    }
}

bool User::find_contact(std::string contact)
{
    for (int i = 0; i < current_contacts.size(); i++)
    {
        if (current_contacts[i] == contact)
            return 1;
    }

    return 0;
}

void User::clear_contacts()
{
    current_contacts.clear();
}

// setters, getters
void User::set_username(std::string username)
{
    this->username = username;
}

void User::set_user_id(std::string user_id)
{
    this->user_id = user_id;
}

void User::set_password(std::string password)
{
    this->password = password;
}

std::string User::get_username()
{
    return username;
}

std::string User::get_user_id()
{
    return user_id;
}

std::string User::get_password()
{
    return password;
}
