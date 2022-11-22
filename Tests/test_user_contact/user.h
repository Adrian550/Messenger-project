#include <string>
#include <vector>

class User
{
public:
    User();

public:
    std::string username, user_id, password;
    std::vector<std::string> current_contacts;

public:
    void add_contact(std::string);
    void remove_contact(std::string);
    bool find_contact(std::string);
    void clear_contacts();
    void set_user_id(std::string);
    void set_username(std::string);
    void set_password(std::string);
    std::string get_username();
    std::string get_user_id();
    std::string get_password();
};

