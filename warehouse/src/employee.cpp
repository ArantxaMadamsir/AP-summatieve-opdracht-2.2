#include "include/employee.hpp"

Employee::Employee(std::string name, bool forkliftCertificate): name(name), forkliftCertificate(forkliftCertificate) {}


std::string Employee::getName()
{
    return name;
}

bool Employee::getBusy()
{
    return busy;
}

void Employee::setBusy(bool busy)
{
    this->busy = busy;
}

bool Employee::getForkliftCertificate()
{
    return getForkliftCertificate;
}

void Employee::setForkliftCertificate(bool forkliftCertificate)
{
    this->forkliftCertificate = forkliftCertificate;
}

