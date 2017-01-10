/* -- INCLUDE ------------------------------------------------ */
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <version.h>
//#include <>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp> // gl Math matix transform
using namespace std;

/* -- includes depinding on platform */
#ifdef ANDROID
#include <jni.h>
#include <GLES2/gl2.h>

#elif  __gnu_linux__
#include <GL/glew.h>
#include <GL/glu.h>
//#include <SDL/SDL_opengl.h>


#elif defined   __APPLE__     
#elif defined   __WINDOWS__
#else
#endif

#include <SDL.h>
#include <ctime>
#include <unistd.h>


// -- VAR
SDL_Window *window;
SDL_GLContext context;

GLint HANDEL_SHADER,
    HANDEL_SHADER_ATTR_VERTEX,
    HANDEL_SHADER_UNI_TRANSFORM,
    HANDEL_SHADER_UNI_COLOR;

int windowWidth = 1500;
int windowHeight = 400;
GLfloat fps = 0;


/* -- PRE DEFINED FUNC ---------------------------------------- */
void renderLoop();
void renderScene();
void createShader();
void setViewport(float w, float h);
void checkShaderError(GLuint shader, bool isProgram, GLint flag, string message);


/* -- HELPER ---------------------------------------------------*/
template<typename T>
std::string to_string(T value)
{
  std::ostringstream os;
  os << value;
  return os.str();
}


void log(string text)
{
  SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, text.c_str());
}

void checkSDLError()
{
  const char *error = SDL_GetError();
  if (*error != '\0')
  {
    log("SDL Error: " + string(error));
    SDL_ClearError();
  }
}




/* -- CREATE OPENGL WINDOW ------------------------------------ */
// -- Linux - Ubuntu 
bool createWindow()
{
  int error = 0;
  log("[....] creating Window");

  // init sdl -----------------------------
  error = SDL_Init(SDL_INIT_VIDEO);
  checkSDLError();
  if (error != 0)
  {
    log("[ERR ] SDL_Init");
    return false;
  }
  else
  {
    log("[ OK ] SDL_Init");
  }

  // set window title
  //SDL_WM_SetCaption("OpenGl Window", "");

  // activate doublebuffering
  // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);



  // open window
  //SDL_SetVideoMode(windowWith, windowHight, 32, SDL_OPENGL | SDL_RESIZABLE | SDL_DOUBLEBUF);
  window = SDL_CreateWindow("OpenGl Window with SDL2",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            windowWidth, windowHeight,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  checkSDLError();

  SDL_GetWindowSize(window, &windowWidth, &windowHeight);
  log("[DISP] get SDL window size, height: " + to_string(windowHeight) + ", windowWidth: " + to_string(windowWidth));


  // create context
  context = SDL_GL_CreateContext(window);
  checkSDLError();
  SDL_GL_MakeCurrent(window, context);
  checkSDLError();
  log("context: " + to_string(context));


  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // 8bit per pixel stacil buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 10);
  checkSDLError();

  // use vsync
  SDL_GL_SetSwapInterval(1);
  checkSDLError();

  // init glew
  // not in android
#ifndef ANDROID
  glewInit();
#endif

  // ouput ok
  log("[DONE] created Window ");
}


/* -- MAIN PROGRAM ------------------------------------------- */
int main(int argc, char *argv[])
{
  // output
  log("[ OK ] program start");
  log("[ OK ] blueprintcmake version " + CMAKE_VERSION);
  createWindow();


  // output of openGl versions
  log("[INFO] openGl version: " + to_string(glGetString(GL_VERSION)));
  log("[INFO] openGl SL version: " + to_string(glGetString(GL_SHADING_LANGUAGE_VERSION)));


  // start render loop
  renderLoop();


  // Delete our OpengL context
  SDL_GL_DeleteContext(context);

  // Destroy our window
  SDL_DestroyWindow(window);

  // Shutdown SDL 2
  SDL_Quit();
}


double starttime = 0;
double endtime = 0;
double timeTemp = 0;
float timeGone = 0;
int frame = 0;
// transform matrix
glm::mat4 transformMatrix;


bool run = true;
bool render = true;

/* -- HANDLE EVENT --------------------------------------------- */
void handleEvent(SDL_Event *event)
{
  //log("event: " + event.type);
  // check for SDL event
  switch (event->type)
  {
    case SDL_QUIT:
      log("[END ] close program ");
      run = false;
      break;

      // event from window
    case SDL_WINDOWEVENT:
      switch (event->window.event)
      {
        case SDL_WINDOWEVENT_RESIZED:
          windowWidth = event->window.data1;
          windowHeight = event->window.data2;
          //SDL_SetWindowSize(window, w, h);
          setViewport(windowWidth, windowHeight);
          break;


        case SDL_WINDOWEVENT_MINIMIZED:
          log("SDL_WINDOWEVENT_MINIMIZED");
          render = false;
          break;

        case SDL_WINDOWEVENT_RESTORED:
          log("SDL_WINDOWEVENT_RESTORED");
          render = true;
          break;


      }
      break;

    case SDL_APP_WILLENTERBACKGROUND:
      render = false;
      log("SDL_APP_WILLENTERBACKGROUND");
      break;


    case SDL_APP_DIDENTERFOREGROUND:
      render = true;
      context = SDL_GL_CreateContext(window);
      checkSDLError();
      SDL_GL_MakeCurrent(window, context);
      checkSDLError();
      log("SDL_APP_DIDENTERFOREGROUND");
      setViewport(windowWidth, windowHeight);
      //setViewport(windowWidth, windowHeight);
      createShader();
      break;


    case SDL_APP_TERMINATING:
      run = false;
      log("SDL_APP_TERMINATING");
      break;

    case SDL_APP_LOWMEMORY:
      log("SDL_APP_LOWMEMORY");
      break;
  }
}


/* -- RENDER LOOP ---------------------------------------------- */
void renderLoop()
{
  // resize ortho
  setViewport(windowWidth, windowHeight);

  // sdl event
  SDL_Event *event = new SDL_Event;

  // output
  log("[....] start render loop");

  // create shader
  createShader();


  SDL_StartTextInput();
  SDL_Rect rect;
  rect.x = 10;
  rect.y = 10;
  rect.h = 50;
  rect.w = 100;
  SDL_SetTextInputRect(&rect);



  // render loop
  while (run)
  {
    // lock till next event when not need render
    // example: app is in background
    if (!render)
    {
      if (SDL_WaitEvent(event) > 0)
      {
        log("end locking");
        handleEvent(event);
      }
      else
      {
        checkSDLError();
      }
    }

    // get all events
    while (SDL_PollEvent(event))
    {
      //log("event" + to_string(event->type));
      handleEvent(event);
    }


    if (render)
    {
      // render
      renderScene();
    }
  }
}

/* -- RENDER ------------------------------------ */
void renderScene()
{
  starttime = clock();

  // vertices
  GLfloat vertices[12] = {
      -100, -100, 0,
      -100, 100, 0,
      100, -100, 0,
      100, 100, 0
  };


  /* clear framebuffer
   * -> red               */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);



  // draw some stuff -------------------------------------------------
  // aktivate shader program
  glUseProgram(HANDEL_SHADER);

  // set attribute to recive vertex data
  glEnableVertexAttribArray(HANDEL_SHADER_ATTR_VERTEX);


  for (float i = -1; i <= 1.0; i += 0.25)
  {
    // remove
    float value = (0.3 * glm::sin(timeGone * 0.3) + i);
    float value2 = (0.3 * glm::cos((timeGone * 0.3) + i));
    float value3 = (0.9 * glm::cos((timeGone * 0.6) + i));

    glm::vec3 move = glm::vec3(value, value2, 0);
    glm::vec3 rot = glm::vec3(0, 0, 1);


    glm::mat4 moveMatrix = glm::translate(glm::mat4(1.0f), move);
    glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), value * 100, rot);
    glm::mat4 matrixFinal = moveMatrix * transformMatrix * rotMatrix;



    // set transform/projecttion matrix
    glUniformMatrix4fv(HANDEL_SHADER_UNI_TRANSFORM,
                       1                /* amount of matrix */,
                       GL_FALSE         /* convert format -> NO */,
                       &matrixFinal[0][0]);

    // set color
    glUniform4f(HANDEL_SHADER_UNI_COLOR,
                value3,
                value,
                value2,
                1.0);

    // give gl the Vertices via array
    glVertexAttribPointer(
        HANDEL_SHADER_ATTR_VERTEX                       /* pass vertices to vertex Pos attribute of vertexShader */,
        3                                               /* 3 Aruments: x,y,z */,
        GL_FLOAT                                        /* Format: float     */,
        GL_FALSE                                        /* take values as-is */,
        0                                               /* Entry lenght ?    */,
        vertices                       /* vertices Array    */ );

    // draw with the vertices form the given Array
    // make two connected triangle to create a rectangle
    glDrawArrays(
        GL_TRIANGLE_STRIP,
        0 /* Array start pos   */,
        4 /* how much vertices */);

  }



  // -- FPS -----------------------------------------------
  // vertices
  GLfloat verticesFps[12] = {
      -0, -10, 0,
      -0, 0, 0,
      (fps / 4), -10, 0,
      (fps / 4), 0, 0
  };

  // remove
  glm::vec3 move = glm::vec3(-1, +1, 0);
  glm::vec3 rot = glm::vec3(0, 0, 0);


  glm::mat4 moveMatrix = glm::translate(glm::mat4(1.0f), move);
  glm::mat4 matrixFinal = moveMatrix * transformMatrix;


  // set transform/projecttion matrix
  glUniformMatrix4fv(HANDEL_SHADER_UNI_TRANSFORM,
                     1                /* amount of matrix */,
                     GL_FALSE         /* convert format -> NO */,
                     &matrixFinal[0][0]);

  // set color
  glUniform4f(HANDEL_SHADER_UNI_COLOR,
              0.0,
              1.0,
              0.2,
              1.0);

  // give gl the Vertices via array
  glVertexAttribPointer(
      HANDEL_SHADER_ATTR_VERTEX                       /* pass vertices to vertex Pos attribute of vertexShader */,
      3                                               /* 3 Aruments: x,y,z */,
      GL_FLOAT                                        /* Format: float     */,
      GL_FALSE                                        /* take values as-is */,
      0                                               /* Entry lenght ?    */,
      verticesFps                       /* vertices Array    */ );

  // draw with the vertices form the given Array
  // make two connected triangle to create a rectangle
  glDrawArrays(
      GL_TRIANGLE_STRIP,
      0 /* Array start pos   */,
      4 /* how much vertices */);
  // -- End FPS -------------------------------------------






  // deactivate vertex Array mode
  // => end of operation
  glDisableVertexAttribArray(HANDEL_SHADER_ATTR_VERTEX);

  // unbind shader
  glUseProgram(0);

  // end draw --------------------------------------------------


  // swarp buffer
  //SDL_GL_SwapBuffers();
  SDL_GL_SwapWindow(window);

  timeGone += 0.009;
  frame++;


  //sleep(3);

  // calc fps
  endtime = clock();
  double timeDiff = (endtime - starttime) / (double) CLOCKS_PER_SEC;
  timeTemp += timeDiff;
  starttime = endtime;


  if (frame >= 60)
  {
    fps = 1 / (timeTemp / frame);

    // set window titel
//            ostringstream stream;
//            stream << "OpenGl Window - Fps " << fps;
//            const char* streamO = stream.str().c_str();
//            SDL_WM_SetCaption(streamO, "");
    log("FPS: " + to_string(fps));

    timeTemp = 0;
    frame = 0;
  }
}


void setViewport(float w, float h)
{
  //log("set glViewport: height: " + to_string(h) + ", width: " + to_string(w));
  //SDL_GetWindowSize(window, &w, &h);
  // out
  //cout << "[INFO] window height: " << h << "  width: " << w << endl;
  //cout << "[INEV] window height: " <<  << "  width: " << w << endl;
  // reset screen
  //SDL_SetVideoMode(w, h, 32, SDL_OPENGL | SDL_RESIZABLE | SDL_DOUBLEBUF);
  //SDL_SetWindowSize(window, w, h);
  glViewport(0, 0, w, h);

  // resize ortho
  transformMatrix = glm::ortho(-(float) w / 2  /* left */,
                               (float) w / 2  /* right */,
                               -(float) h / 2 /* bottom */,
                               (float) h / 2 /* top */,

                               1.0f                     /* zNear */,
                               -1.0f                     /* zFar */);
}


/* -- CREATE SHADER ----------------------------- */
void createShader()
{
  // shader src
  const GLchar *vertexShader =
      "#version 100                             \n"
          "attribute vec3 vertexPos;                                \n"
          "uniform   mat4 transformMatrix;                          \n" // uniform can be set by cpu
          "                                                         \n"
          "void main() {                                            \n"
          "                                                         \n"
          "    gl_Position = transformMatrix * vec4(vertexPos, 1.0);\n"
          "}                                                        \n";

  const GLchar *fragmentShader =
      "#version 100                             \n"
          "precision highp float;                   \n"
          "uniform vec4 color;                      \n" // uniform can be set by cpu
          "                                         \n"
          "void main() {                            \n"
          "                                         \n"
          "   gl_FragColor =  color;                \n"
          "}                                        \n";


  GLint shaderVertex, shaderFragment;

  // create shader programm
  HANDEL_SHADER = glCreateProgram();
  if (HANDEL_SHADER == 0)
  {
    log("[ GL ] create shader program [ERR]");
  }
  else
  {
    log("[ GL ] create shader program [OK]");
  }


  // create shader container --------
  shaderVertex = glCreateShader(GL_VERTEX_SHADER);   // for vertext-shader
  shaderFragment = glCreateShader(GL_FRAGMENT_SHADER); // for fragment-shader
  if (shaderVertex == 0 || shaderFragment == 0)
  {
    log("[ GL ] create shader [ERR]");
  }
  else
  {
    log("[ GL ] create shader [OK]");
  }


  // load shaders into char vars
  // => not necessary


  // load shader into container
  glShaderSource(shaderVertex, 1, &vertexShader, NULL);
  glShaderSource(shaderFragment, 1, &fragmentShader, NULL);


  // compile shader
  glCompileShader(shaderVertex);
  glCompileShader(shaderFragment);
  checkShaderError(shaderVertex, false, GL_COMPILE_STATUS, "compile vertex shader");
  checkShaderError(shaderFragment, false, GL_COMPILE_STATUS, "compile fragment shader");


  // add shader to programm
  glAttachShader(HANDEL_SHADER, shaderVertex);
  glAttachShader(HANDEL_SHADER, shaderFragment);


  // bind shader programm to openGl
  glLinkProgram(HANDEL_SHADER);
  checkShaderError(HANDEL_SHADER, true, GL_LINK_STATUS, "link shader program");

  glValidateProgram(HANDEL_SHADER);
  checkShaderError(HANDEL_SHADER, true, GL_VALIDATE_STATUS, "validate shader program");


  // get attributes / uniformes
  HANDEL_SHADER_ATTR_VERTEX = glGetAttribLocation(HANDEL_SHADER, "vertexPos");
  HANDEL_SHADER_UNI_TRANSFORM = glGetUniformLocation(HANDEL_SHADER, "transformMatrix");
  HANDEL_SHADER_UNI_COLOR = glGetUniformLocation(HANDEL_SHADER, "color");

  if (HANDEL_SHADER_ATTR_VERTEX == -1
      || HANDEL_SHADER_UNI_TRANSFORM == -1
      || HANDEL_SHADER_UNI_COLOR == -1)
  {
    log("[ GL ] get Attribute/Uniform [ERR]");
  }
  else
  {
    log("[ GL ] get Attribute/Uniform [OK]");
  }

}


// -- CHECK SHADER ERROR ----------------------
void checkShaderError(GLuint shader, bool isProgram, GLint flag, string message)
{
  // error var
  GLint success = GL_FALSE;
  GLchar errorText[1024] = {0};


  // is there an error
  if (isProgram)
  {
    glGetProgramiv(shader, flag, &success);
  }
  else
  {
    glGetShaderiv(shader, flag, &success);
  }


  // if there is error
  if (success == GL_FALSE)
  {
    if (isProgram)
      glGetProgramInfoLog(shader, sizeof(errorText), NULL, errorText);
    else
      glGetShaderInfoLog(shader, sizeof(errorText), NULL, errorText);
  }

  // out
  if (success == GL_FALSE)
  {
    log("[ GL ] " + message + " [ERR] '" + errorText + "'");
  }
  else
  {
    log("[ GL ] " + message + " [OK]");
  }
}