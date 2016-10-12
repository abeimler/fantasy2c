#include "Window.hpp"

namespace F2C{

#if defined(WIN32_OR_X11)
void Window::setupExtensionsShader(){

    if( uglExtensionSupported("GL_ARB_shader_objects") &&
      uglExtensionSupported("GL_ARB_shading_language_100") &&
      uglExtensionSupported("GL_ARB_vertex_shader") &&
      uglExtensionSupported("GL_ARB_fragment_shader") )
    {
        glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)
          uglGetProcAddress("glCreateProgramObjectARB");
        glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)
          uglGetProcAddress("glDeleteObjectARB");
        glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)
          uglGetProcAddress("glCreateShaderObjectARB");
        glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)
          uglGetProcAddress("glShaderSourceARB");
        glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)
          uglGetProcAddress("glCompileShaderARB");
        glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)
          uglGetProcAddress("glGetObjectParameterivARB");
        glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)
          uglGetProcAddress("glAttachObjectARB");
        glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)
          uglGetProcAddress("glGetInfoLogARB");
        glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)
          uglGetProcAddress("glLinkProgramARB");
        glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)
          uglGetProcAddress("glUseProgramObjectARB");
        glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)
          uglGetProcAddress("glGetUniformLocationARB");
        glUniform1fARB = (PFNGLUNIFORM1FARBPROC)
          uglGetProcAddress("glUniform1fARB");
        glUniform1iARB = (PFNGLUNIFORM1IARBPROC)
          uglGetProcAddress("glUniform1iARB");

        if( false
         || glCreateProgramObjectARB == NULL
         || glDeleteObjectARB == NULL
         || glCreateShaderObjectARB == NULL
         || glShaderSourceARB == NULL
         || glCompileShaderARB == NULL
         || glGetObjectParameterivARB == NULL
         || glAttachObjectARB == NULL
         || glGetInfoLogARB == NULL
         || glLinkProgramARB == NULL
         || glUseProgramObjectARB == NULL
         || glGetUniformLocationARB == NULL
         || glUniform1fARB == NULL
         || glUniform1iARB == NULL
          )
          this->shading_enabled = false;

        else
          this->shading_enabled = true;
    } else
          this->shading_enabled = false;

}

void Window::setupExtensionsVBO(){

  if( uglExtensionSupported("GL_ARB_vertex_buffer_object"))
  {
    glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)
        uglGetProcAddress("glGenBuffersARB");
    glBindBufferARB = (PFNGLBINDBUFFERARBPROC)
        uglGetProcAddress("glBindBufferARB");
    glBufferDataARB = (PFNGLBUFFERDATAARBPROC)
        uglGetProcAddress("glBufferDataARB");
    glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)
        uglGetProcAddress("glDeleteBuffersARB");

    if( false
     || glGenBuffersARB == NULL
     || glBindBufferARB == NULL
     || glBufferDataARB == NULL
     || glDeleteBuffersARB == NULL
      )
      this->vbo_enabled = false;

    else
      this->vbo_enabled = true;
  } else
      this->vbo_enabled = false;

}

void Window::setupExtensionsMultiTexel(){

  if( uglExtensionSupported("GL_ARB_multitexture") &&
      uglExtensionSupported("GL_EXT_texture_env_combine") )
  {
    #if defined(WIN32) || defined(_Windows)
        glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)
            uglGetProcAddress("glMultiTexCoord1fARB");
        glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)
            uglGetProcAddress("glMultiTexCoord2fARB");
        glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)
            uglGetProcAddress("glMultiTexCoord3fARB");
        glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)
            uglGetProcAddress("glMultiTexCoord4fARB");
        glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)
            uglGetProcAddress("glActiveTextureARB");
        glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)
            uglGetProcAddress("glClientActiveTextureARB");

        if( false
             || glMultiTexCoord1fARB == NULL
             || glMultiTexCoord2fARB == NULL
             || glMultiTexCoord3fARB == NULL
             || glMultiTexCoord4fARB == NULL
             || glActiveTextureARB == NULL
             || glClientActiveTextureARB == NULL)
                this->multitexel_enabled = false;
        else
            this->multitexel_enabled = true;
    #else
            this->multitexel_enabled = true;
    #endif
  } else
      this->multitexel_enabled = false;

}

#else
      void Window::setupExtensionsShader(){
          if( uglExtensionSupported("GL_ARB_shader_objects") &&
                uglExtensionSupported("GL_ARB_shading_language_100") &&
                uglExtensionSupported("GL_ARB_vertex_shader") &&
                uglExtensionSupported("GL_ARB_fragment_shader"))
                    this->shading_enabled = true;
            else
                this->shading_enabled = false;
        }
        void Window::setupExtensionsVBO(){
          if(uglExtensionSupported("GL_ARB_vertex_buffer_object"))
                this->vbo_enabled = true;
            else
                this->vbo_enabled = false;
        }
        void Window::setupExtensionsMultiTexel(){
          if( uglExtensionSupported("GL_ARB_multitexture") &&
                uglExtensionSupported("GL_EXT_texture_env_combine"))
                    this->multitexel_enabled = true;
            else
                this->multitexel_enabled = false;
        }
#endif

Window* Window::_instance = NULL;

Window* Window::getInstance(){
   if (!Window::_instance)
      Window::_instance = new Window;
   return Window::_instance;
}

Window::Window():
    FPS(0.0f),
	startTime(0.0f),
	startTick(0.0f),
	activTime(0.0f),
	frames(0),
	shading_enabled(false),
	vbo_enabled(false),
	multitexel_enabled(false),
    maxTexelUnits(1),
	showmouse(false),
	programObj(0),
    fragmentShader(0),
    vertexShader(0)
{}

void Window::UpdateGLScreen(){
   this->frames++;
   glfwSwapBuffers();
   this->activTime = glfwGetTime();
   if( (this->activTime-this->startTime) > 1.0 || this->frames == 0 ){
      this->FPS = static_cast<double>(this->frames) / (this->activTime-this->startTime);
      this->startTime = this->activTime;
      this->frames = 0;
   }
}

void Window::ReSize(uint wndwidth, uint wndheight,uint screenwidth,uint screenheight){
	if(wndheight < 1)
		wndheight = 1;
    if(screenheight < 1)
         screenheight = 1;

    glfwSetWindowSize(wndwidth,wndheight);
	glViewport(0,wndheight-screenheight,screenwidth,screenheight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,screenwidth,screenheight,0,INT_MIN+1,INT_MAX-1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Window::InitGL(){
	glAlphaFunc(GL_GREATER, 0.000f);
	glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

    this->setupExtensionsShader();
    this->setupExtensionsVBO();
    this->setupExtensionsMultiTexel();
}

int Window::loadshader(std::string filename, std::string& ShaderSource){
   std::ifstream file;
   file.open(filename.c_str(), std::ios::in); // opens as ASCII!
   if(!file)
    return -1;

   uint32 len;
   if(!file.good())
      len = 0;
   else{
      file.seekg (0, std::ios::end);
      len = file.tellg();
      file.seekg(0,std::ios::beg);
   }

   if (len == 0)
      return -2;   // Error: Empty File

   while (!file.eof()){
     ShaderSource.push_back(file.get());
   }

   file.close();

   return 1; // No Error
}

int Window::InitGLShader(){
    if(! glfwExtensionSupported("GL_ARB_shading_language_100") )
        return -1;

    if(! glfwExtensionSupported("GL_ARB_shader_objects"))
        return -2;

    if(!this->shading_enabled)
      return -3;


	//
	// Create our fragment and vertex shader...
	//

	if (this->fragmentShader)
		glDeleteObjectARB( this->fragmentShader );
	if (this->vertexShader)
		glDeleteObjectARB( this->vertexShader );
	if (this->programObj)
		glDeleteObjectARB( this->programObj );

    this->programObj = 0;
    this->fragmentShader = 0;
    this->vertexShader = 0;

    return 1;
}

void Window::printLog(uint obj,std::string* error){
    if(!error)
        return;
    int infologLength = 0;
    char infoLog[1024];

    glGetInfoLogARB(obj, 1024, &infologLength, infoLog);

    if (infologLength > 0){
		std::string tmp (infoLog,infologLength);
		*error += tmp;
		*error += '\n';
    }
}

int Window::LoadGLVertexShader(std::string shaderfilename,std::string* error){
    /* The vertex shader */
	std::string vsSource;
	int status = this->loadshader(shaderfilename.c_str(),vsSource);
	if(status < 0)
	    return status;

	/* Compile and load the program */
	if (this->vertexShader)
		glDeleteObjectARB( this->vertexShader );

    const GLcharARB* vsSrc = vsSource.c_str();
	this->vertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER);
	glShaderSourceARB(this->vertexShader, 1,&vsSrc,NULL);
	glCompileShaderARB(this->vertexShader);
	this->printLog(this->vertexShader,error);

	return 1;
}

int Window::LoadGLFragmentShader(std::string shaderfilename,std::string* error){
	/* The fragment shader */
	std::string fsSource;
	int status = this->loadshader(shaderfilename,fsSource);
	if(status < 0)
	    return status;

	/* Compile and load the program */
     if (this->fragmentShader)
            glDeleteObjectARB( this->fragmentShader );

    const GLcharARB* fsSrc = fsSource.c_str();
	this->fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
	glShaderSourceARB(this->fragmentShader, 1,&fsSrc, NULL);
	glCompileShaderARB(this->fragmentShader);
	this->printLog(this->fragmentShader,error);

	return 1;
}

void Window::CreateShaderProgram(std::string* error){
    if (this->programObj)
		glDeleteObjectARB( this->programObj );

	this->programObj = glCreateProgramObjectARB();
    glAttachObjectARB(this->programObj, this->fragmentShader);
    glAttachObjectARB(this->programObj, this->vertexShader);
    glLinkProgramARB(this->programObj);
	this->printLog(this->programObj,error);
}

void Window::ClearGLScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
}

void Window::ShutdownGLWindow(){
	glfwTerminate();
	if (this->fragmentShader)
		glDeleteObjectARB( this->fragmentShader );
	if (this->vertexShader)
		glDeleteObjectARB( this->vertexShader );
	if (this->programObj)
		glDeleteObjectARB( this->programObj );
}


bool Window::CreateGLWindow(std::string title,uint width,uint height, int bits, bool fullscreen){
   if(! (glfwInit()))
      return false;

   if (height == 0) height = 1;

	this->frames = 0;
	this->FPS = 0.0f;
	this->activTime = 0.0f;
	this->startTime = glfwGetTime();
	this->startTick = 0.0f;
	this->shading_enabled = false;
	this->vbo_enabled = false;
	this->multitexel_enabled = false;

    this->programObj = 0;
    this->fragmentShader = 0;
    this->vertexShader = 0;
    this->maxTexelUnits = 1;
    this->showmouse = false;

	int rgba[4] = {0,0,0,0};
	if(bits == 8){
	   rgba[0] = 3;
	   rgba[1] = 3;
	   rgba[2] = 2;
   }else if(bits == 12){
	   rgba[0] = 4;
	   rgba[1] = 4;
	   rgba[2] = 4;
   }else if(bits == 16){
	   rgba[0] = 5;
	   rgba[1] = 6;
	   rgba[2] = 5;
   }else if(bits == 24){
      rgba[0] = 8;
      rgba[1] = 8;
      rgba[2] = 8;
   }else if(bits == 36){
      rgba[0] = 12;
      rgba[1] = 12;
      rgba[2] = 12;
   }else if(bits == 42){
      rgba[0] = 14;
      rgba[1] = 14;
      rgba[2] = 14;
   }else if(bits == 48){
      rgba[0] = 16;
      rgba[1] = 16;
      rgba[2] = 16;
   }else{
      rgba[0] = 8;
      rgba[1] = 8;
      rgba[2] = 8;
      rgba[3] = 8;
   }

	int mode = (fullscreen)? GLFW_FULLSCREEN : GLFW_WINDOW;
	this->showmouse = (fullscreen)? false : true;

   if(! (glfwOpenWindow(
           width, height,     // Width and height of window
           rgba[0], rgba[1], rgba[2],           // Number of red, green, and blue bits for color buffer
           rgba[3],                 // Number of bits for alpha buffer
           bits-8,              // Number of bits for depth buffer (Z-buffer)
           bits-8,              // Number of bits for stencil buffer
           mode        // Window or Fullscreen mode
         )
   )){
      glfwTerminate();
      return false;
   }

   glfwSetWindowTitle(title.c_str());

   this->ReSize(width,height,width,height);

	return true;
}

void Window::setWindowPosition(int x,int y){glfwSetWindowPos(x,y);}
void Window::setWindowSize(uint wndwidth, uint wndheight){glfwSetWindowSize(wndwidth,wndheight);}
void Window::setWindowTitle(std::string title){glfwSetWindowTitle(title.c_str());}

void Window::setWindowHint(WindowProperty::ParamWindow paramwindow,int value){
   glfwOpenWindowHint(paramwindow,value);
}

int Window::getWindowParam(WindowProperty::ParamWindow param){
   return glfwGetWindowParam(param);
}

void Window::getWindowSize(int* width,int* height){glfwGetWindowSize( width, height );}

void Window::setTime(double time){glfwSetTime(time);}
double Window::getTime(){return glfwGetTime();}
void Window::Sleep(double time){glfwSleep(time);}

void Window::startTicks(){this->startTick = glfwGetTime();}
double Window::getTicks(){return glfwGetTime()-this->startTick;}

void Window::getSize(int* wndwidth, int* wndheight,uint* screenwidth,uint* screenheight){
   int params[4];
   glGetIntegerv(GL_VIEWPORT,params);
   if(screenwidth)
        *screenwidth = params[2];
   if(screenheight)
        *screenheight = params[3];
   glfwGetWindowSize(wndwidth,wndheight);
}

void Window::getScreenSize(uint* screenwidth,uint* screenheight){
   int* params = new int[4];
   glGetIntegerv(GL_VIEWPORT,params);
   if(screenwidth)
        *screenwidth = params[2];
   if(screenheight)
        *screenheight = params[3];
   delete[] params;
}

double Window::getFPS(){return this->FPS;}
bool Window::getSupportedShader(){return this->shading_enabled;}
bool Window::getSupportedVBO(){return this->vbo_enabled;}
bool Window::getSupportedMultiTexel(){return this->multitexel_enabled;}
uint Window::getFrame(){return this->frames;}
int Window::getMaxTexelUnits(){glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB,&this->maxTexelUnits);return this->maxTexelUnits;}

void Window::showMouseCursor(bool show){
    if(show)
        glfwEnable(GLFW_MOUSE_CURSOR);
    else
        glfwDisable(GLFW_MOUSE_CURSOR);
    this->showmouse = show;
}

bool Window::getShowMouseCursor(){
    return this->showmouse;
}

};


