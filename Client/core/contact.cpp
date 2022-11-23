#include "contact.h"
//Constructor of contact's frame
Contact::Contact(QWidget *page, QVBoxLayout *layout, QLabel *name_label, QLabel *status_label)
{
    this->page = page;
    this->layout = layout;
    this->name_label = name_label;
    this->status_label = status_label;
}
//Destructor
Contact::~Contact()
{
}
