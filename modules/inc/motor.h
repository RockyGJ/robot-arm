
#ifndef I2C_CONSOLE_H
#define I2C_CONSOLE_H



class Date {

public:
	Date(int, int, int);
  void set(int, int, int);
  void print();
  int test;

private:
  int year;
  int month;
  int day;
};
#endif
