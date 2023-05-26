#pragma once
#include <iostream>
#include <string>


class Employee {
   private:
      const std::string name;

      bool busy;
      
      bool forkliftCertificate;

   public:
      Employee(std::string name, bool forkliftCertificate);

      std::string getName();

      bool getBusy();

      void setBusy(bool busy);

      bool getForkliftCertificate();

      void setForkliftCertificate(bool forkliftCertificate);

      friend std::ostream& operator<<(std::ostream& output, Employee& employee);

};
