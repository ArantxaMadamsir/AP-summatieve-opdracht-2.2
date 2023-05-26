#include "include/employee.hpp"


Employee::Employee(std::string name, bool forkliftCertificate): name(name), forkliftCertificate(forkliftCertificate) {}

std::string Employee::getName() {
    return name;
}

bool Employee::getBusy() {
    return busy;
}

void Employee::setBusy(bool busy) {
    this->busy = busy;
}

bool Employee::getForkliftCertificate() {
    return forkliftCertificate;
}

void Employee::setForkliftCertificate(bool forkliftCertificate) {
    this->forkliftCertificate = forkliftCertificate;
}

std::ostream& operator<<(std::ostream& output, Employee& employee) {
    output << "Name: " << employee.getName() << "\n"
           << "Busy: " << employee.getBusy() << "\n"
           << "Forklift Certificate: " << employee.getForkliftCertificate() << "\n";
    return output;
}
