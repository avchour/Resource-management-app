#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
void rtrim(char *str);
int getIntInput(const char *prompt);
float getFloatInput(const char *prompt);
bool askAgain(const char *message);
#endif