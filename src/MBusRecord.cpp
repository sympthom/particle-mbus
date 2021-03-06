#include <MBusRecord.h>
#include <string.h>

MBusString::MBusString() {
  this->value = NULL;
  this->size = 0;
};

MBusString::MBusString(char *str, unsigned int size) {
  this->value = NULL;
  this->size = 0;
  this->set(str, size);
};

MBusString::~MBusString() {
  if (this->value) {
    delete [] this->value;
  };
};

void MBusString::set(char *str, unsigned int size) {
  if (this->value) {
    delete [] this->value;
  };

  this->value = new char[size + 1]; // +1 for NULL termination
  this->size = size;
  bcopy(str, this->value, size);
  this->value[size] = '\0'; // terminate string
};

MBusValue::MBusValue() {
  this->real_val = 0;
};

MBusValue::~MBusValue() {

};

MBusRecord::MBusRecord() {
  this->value = new MBusValue();
  this->isNumeric = false;
  this->unit = NULL;
  this->function_medium = NULL;
  this->quantity = NULL;
  this->device = 0;
  this->tariff = 0;
  this->storage_number = 0;
};

MBusRecord::~MBusRecord() {
  if (this->value != NULL) {
    delete this->value;
  }
};

int MBusRecord::setValue(double val) {
  this->value->real_val = val;
  this->isNumeric = true;

  return 0;
};

int MBusRecord::setValue(char *str, unsigned int size) {
  this->value->str_val.set(str, size);
  this->isNumeric = false;

  return 0;
};

double MBusRecord::getValue() {
  if(this->isNumeric) {
    return this->value->real_val;
  }

  return -1;
};

char *MBusRecord::getString() {
  if(this->isNumeric == false) {
    return this->value->str_val.value;
  }

  return NULL;
};
