#include "basic.h"

void getStringsSeparatedByLetter(std::vector<std::string>& words,std::string wordlist,std::string letter){
    if(wordlist.empty() || letter.empty())
        return;

    std::string::size_type a = 0;
    a = wordlist.find_first_not_of(letter,a);
    words.clear();
    while(a != std::string::npos){
        std::string::size_type e = wordlist.find_first_of(letter, a);
        if (e != std::string::npos) {
            words.push_back( wordlist.substr(a,e-a));
            a = e +1;
        }else{
            words.push_back( wordlist.substr(a));
            break;
        }

        a = wordlist.find_first_not_of(letter, a);
    }
}

int random(int lowest_number, int highest_number){
    if(lowest_number == highest_number)
        return lowest_number;

    int range = highest_number - lowest_number + 1;
    if(range == 0)
        return 0;

    //random srand
    static bool isInitRand = false;
    if(!isInitRand){
        time_t now = time(NULL);
        F2C::uint8* p = (F2C::uint8*)&now;
        F2C::uint seed = 0;

        for (size_t i = 0; i < sizeof(now); ++i)
            seed = seed * 255 + p[i];

        srand(seed);
        isInitRand = true;
    }

    int randn = 0;
    size_t cross = rand()%10+1;
    for(size_t i = 0;i < cross;++i){
        randn = (rand() % range) + lowest_number;
    }

    return randn;
}


namespace F2C{

void loadShader(F2C::ShaderGL& shader,std::string frag,std::string vertex){
   int shader_status = F2C::ShaderGL::InitGLShader();  //init Shader, get error
   if(shader_status > 0){
      std::string error_string;
      shader_status = shader.LoadGLFragmentShader(frag,&error_string);
      shader_status = shader.LoadGLVertexShader(vertex,&error_string);
      shader.CreateShaderProgram(&error_string);
      if(shader_status > 0){
         if(! error_string.empty()){  //write Shader compiler&linker Log
            F2C::LogError error;
            SETLOGERROR(error,error_string.c_str());
            error.writeError();
         }
         if(shader.getProgramObj() != 0){
            //Shader success
            F2C::Sprite::ShaderProgramObj = shader.getProgramObj();  //set Sprite Shader Program Object
            F2C::FontSprite::ShaderProgramObj = shader.getProgramObj();  //set FontSprite Shader Program Object
            F2C::Plane::ShaderProgramObj = shader.getProgramObj();  //set Plane Shader Program Object
            F2C::ArraySprite::ShaderProgramObj = shader.getProgramObj();  //set Array Sprite Shader Program Object
         }
      }else{  //load Shaderfile failure
         F2C::LogError error;
         switch(shader_status){
               case -1:
                  SETLOGERROR(error,"Can't open the Shaderfile");
                  error.writeError();
               break;
               case -2:
                  SETLOGERROR(error,"The Shaderfile is empty");
                  error.writeError();
         }
      }
   }else{  //init Shader failure
      F2C::LogError error;
      switch(shader_status){
            case -1:
               SETLOGERROR(error,"This extension string indicates that the OpenGL Shading Language, version 1.00, is supported.");
               error.writeError();
            break;
            case -2:
               SETLOGERROR(error,"GL_ARB_shader_objects extension was not found");
               error.writeError();
            break;
            case -3:
               SETLOGERROR(error,"shading not enabled");
               error.writeError();
      }
   }
}

void loadFragmentShader(F2C::ShaderGL& shader,std::string filename){
   int shader_status = F2C::ShaderGL::InitGLShader();  //init Shader
   if(shader_status > 0){
      std::string error_string;
      shader_status = shader.LoadGLFragmentShader(filename,&error_string);
      shader.CreateShaderProgram(&error_string);
      if(shader_status > 0){
         if(! error_string.empty()){  //write Shader compiler&linker Log
            F2C::LogError error;
            SETLOGERROR(error,error_string.c_str());
            error.writeError();
         }
         if(shader.getProgramObj() != 0){
            //Shader success
            F2C::Sprite::ShaderProgramObj = shader.getProgramObj();  //set Sprite Shader Program Object
            F2C::FontSprite::ShaderProgramObj = shader.getProgramObj();  //set FontSprite Shader Program Object
            F2C::Plane::ShaderProgramObj = shader.getProgramObj();  //set Plane Shader Program Object
            F2C::ArraySprite::ShaderProgramObj = shader.getProgramObj();  //set Array Sprite Shader Program Object
         }
      }else{  //load Shaderfile failure
         F2C::LogError error;
         switch(shader_status){
               case -1:
                  SETLOGERROR(error,"Can't open the Shaderfile");
                  error.writeError();
               break;
               case -2:
                  SETLOGERROR(error,"The Shaderfile is empty");
                  error.writeError();
         }
      }
   }else{  //init Shader failure
      F2C::LogError error;
      switch(shader_status){
            case -1:
               SETLOGERROR(error,"This extension string indicates that the OpenGL Shading Language, version 1.00, is supported.");
               error.writeError();
            break;
            case -2:
               SETLOGERROR(error,"GL_ARB_shader_objects extension was not found");
               error.writeError();
            break;
            case -3:
               SETLOGERROR(error,"shading not enabled");
               error.writeError();
      }
   }
}

void loadVertexShader(F2C::ShaderGL& shader,std::string filename){
   int shader_status = F2C::ShaderGL::InitGLShader();  //init Shader
   if(shader_status > 0){
      std::string error_string;
      shader_status = shader.LoadGLVertexShader(filename,&error_string);
      shader.CreateShaderProgram(&error_string);
      if(shader_status > 0){
         if(! error_string.empty()){  //write Shader compiler&linker Log
            F2C::LogError error;
            SETLOGERROR(error,error_string.c_str());
            error.writeError();
         }
         if(shader.getProgramObj() != 0){
            //Shader success
            F2C::Sprite::ShaderProgramObj = shader.getProgramObj();  //set Sprite Shader Program Object
            F2C::FontSprite::ShaderProgramObj = shader.getProgramObj();  //set FontSprite Shader Program Object
            F2C::Plane::ShaderProgramObj = shader.getProgramObj();  //set Plane Shader Program Object
            F2C::ArraySprite::ShaderProgramObj = shader.getProgramObj();  //set Array Sprite Shader Program Object
         }
      }else{  //load Shaderfile failure
         F2C::LogError error;
         switch(shader_status){
               case -1:
                  SETLOGERROR(error,"Can't open the Shaderfile");
                  error.writeError();
               break;
               case -2:
                  SETLOGERROR(error,"The Shaderfile is empty");
                  error.writeError();
         }
      }
   }else{  //init Shader failure
      F2C::LogError error;
      switch(shader_status){
            case -1:
               SETLOGERROR(error,"This extension string indicates that the OpenGL Shading Language, version 1.00, is supported.");
               error.writeError();
            break;
            case -2:
               SETLOGERROR(error,"GL_ARB_shader_objects extension was not found");
               error.writeError();
            break;
            case -3:
               SETLOGERROR(error,"shading not enabled");
               error.writeError();
      }
   }
}

}
