#include <Fantasy2C/Sprite.hpp>

namespace F2C{

GLhandleARB Sprite::ShaderProgramObj = 0;
TexParam::Tex_Param Sprite::filter = TexParam::Linear;
bool Sprite::VertexArray = false;
bool Sprite::checkVertexArray = false;

void Sprite::enableGLDrawArray(bool enable){
    Sprite::VertexArray = enable;
    Sprite::checkVertexArray = true;
}
bool Sprite::isEnableGLDrawArray(){
    return Sprite::VertexArray;
}

Sprite::Sprite(const Sprite& copy):
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Sprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        Sprite::enableGLDrawArray(true);
    }


	*this = copy;
}

Sprite& Sprite::operator= (const Sprite& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;

        this->SpriteBase::operator = (copy);
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out,const Sprite& copy){
    out << copy.tone;

    out << dynamic_cast<const SpriteBase&>(copy);

    return out;
}

std::istream& operator>>(std::istream &in, Sprite& copy){
    in >> copy.tone;

    in >> dynamic_cast<SpriteBase&>(copy);

    return in;
}

void Sprite::copyProperties(const Sprite& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;

        this->SpriteBase::copyProperties(copy);
    }
}

Sprite::Sprite():
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Sprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        Sprite::enableGLDrawArray(true);
    }
}

Sprite::Sprite(const Bitmap* bitmap):
    SpriteBase(bitmap),
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Sprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        Sprite::enableGLDrawArray(true);
    }
}

Sprite::Sprite(Viewport* viewport):
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Sprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        Sprite::enableGLDrawArray(true);
    }

   this->setViewport(viewport);
}

void Sprite::setViewport(Viewport* viewport){
    this->viewport = viewport;
    if(!this->viewport){
        this->clip_rect = NULL;
    }else if(this->viewport->clip_rect.x != 0 || this->viewport->clip_rect.y != 0 ||
                this->viewport->clip_rect.height != 0  || this->viewport->clip_rect.width != 0 ){
                    this->clip_rect = &this->viewport->clip_rect;
    }else{
        this->clip_rect = NULL;
    }
}

};

