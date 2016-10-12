#include <Fantasy2C/SimpleSprite.hpp>

namespace F2C{

GLhandleARB SimpleSprite::ShaderProgramObj = 0;
TexParam::Tex_Param SimpleSprite::filter = TexParam::Linear;
bool SimpleSprite::VertexArray = false;
bool SimpleSprite::checkVertexArray = false;

void SimpleSprite::enableGLDrawArray(bool enable){
    SimpleSprite::VertexArray = enable;
    SimpleSprite::checkVertexArray = true;
}
bool SimpleSprite::isEnableGLDrawArray(){
    return SimpleSprite::VertexArray;
}

SimpleSprite::SimpleSprite(const SimpleSprite& copy){
    if(!SimpleSprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        SimpleSprite::enableGLDrawArray(true);
    }

    *this = copy;
}

SimpleSprite& SimpleSprite::operator= (const SimpleSprite& copy){
    if(this != &copy){
        this->grayscale = copy.grayscale;

        this->SpriteBase::operator = (copy);
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out,const SimpleSprite& copy){
    out << copy.grayscale;

    out << dynamic_cast<const SpriteBase&>(copy);

    return out;
}

std::istream& operator>>(std::istream &in, SimpleSprite& copy){
    in >> copy.grayscale;

    in >> dynamic_cast<SpriteBase&>(copy);

    return in;
}

SimpleSprite::SimpleSprite():
    grayscale(0)
{
    if(!SimpleSprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        SimpleSprite::enableGLDrawArray(true);
    }
}

SimpleSprite::SimpleSprite(const Bitmap* bitmap):
    SpriteBase(bitmap),
    grayscale(0)
{
    if(!SimpleSprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        SimpleSprite::enableGLDrawArray(true);
    }
}

void SimpleSprite::copyProperties(const SimpleSprite& copy){
    if(this != &copy){
        this->grayscale = copy.grayscale;

        this->SpriteBase::copyProperties(copy);
    }
}

};

