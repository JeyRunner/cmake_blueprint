//
// Created by joshua on 27.12.16.
//
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#ifdef ANDROID
#include <jni.h>
#endif
using namespace std;

#define as(x) #x

int main(int argCount, char *args[])
{
  printf("program arguments (%i) of %s",
         argCount, args[0]);

  exit(42);
}


template<typename T>
std::string to_string(T value)
{
  std::ostringstream os;
  os << value;
  return os.str();
}

#ifdef ANDROID
extern "C"
jstring
Java_com_blueprint_cmake_main_stringFromJNI(
    JNIEnv* env,
    jobject /* this */, int howmuch) {

  string a = "";
  for (int i = 0; i < howmuch; ++i) {
    a+= to_string(i) + "_";
  }
  std::string hello = a;

  return env->NewStringUTF(hello.c_str());
}
#endif