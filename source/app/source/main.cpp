//
// Created by joshua on 27.12.16.
//
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <SDL.h>
#ifdef ANDROID
#include <jni.h>
#endif
using namespace std;

#define as(x) #x

int main(int argCount, char *args[])
{
  SDL_Log("program arguments (%i) of %s \n",
         argCount, args[0]);


  int error = 0;
  SDL_Surface *surface = NULL;

  // init sdl -----------------------------
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    string e = "\nUnable to initialize SDL:  " + string(SDL_GetError());
    SDL_Log(e.c_str());
    return 1;
  }

  SDL_Log("init SDL ok!");

  // activate doublebuffering

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // 8bit per pixel stacil buffer


  // open window - init projection matrix ...
  SDL_Window* window = SDL_CreateWindow("test",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            100, 100,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if (window == NULL)
  {
    string e = "\nerror create window:  " + string(SDL_GetError());
    SDL_Log(e.c_str());
  } else
  {
    string e = "\ncreate window ok!  " + string(SDL_GetError());
    SDL_Log(e.c_str());
  }
  // create context
  SDL_GL_CreateContext(window);



  // print open gl info
  //cout << ("Open Gl version: '" + to_string(glGetString(GL_VERSION)) + "'");


  while (true);
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