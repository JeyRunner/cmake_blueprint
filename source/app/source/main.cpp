//
// Created by joshua on 27.12.16.
//
#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argCount, char *args[])
{
  printf("program arguments (%i) of %s",
         argCount, args[0]);

  exit(42);
}