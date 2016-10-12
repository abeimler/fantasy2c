#include <Fantasy2C/Plane.hpp>

namespace F2C{

GLhandleARB Plane::ShaderProgramObj = 0;
TexParam::Tex_Param Plane::filter = TexParam::Linear;
bool Plane::VertexArray = false;
bool Plane::checkVertexArray = false;

void Plane::enableGLDrawArray(bool enable){
    Plane::VertexArray = enable;
    Plane::checkVertexArray = true;
}
bool Plane::isEnableGLDrawArray(){
    return Plane::VertexArray;
}


Plane::Plane(const Plane& copy):
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Plane::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        Plane::enableGLDrawArray(true);
    }

	*this = copy;
}

Plane& Plane::operator= (const Plane& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;

        this->SpriteBase::operator = (copy);
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out,const Plane& copy){
    out << copy.tone;

    out << dynamic_cast<const SpriteBase&>(copy);

    return out;
}

std::istream& operator>>(std::istream &in, Plane& copy){
    in >> copy.tone;

    in >> dynamic_cast<SpriteBase&>(copy);

    return in;
}

void Plane::copyProperties(const Plane& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;

        this->SpriteBase::copyProperties(copy);
    }
}

Plane::Plane():
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Plane::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        Plane::enableGLDrawArray(true);
    }
}

Plane::Plane(const Bitmap* bitmap):
    SpriteBase(bitmap),
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Plane::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        Plane::enableGLDrawArray(true);
    }
}

Plane::Plane(Viewport* viewport):
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Plane::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        Plane::enableGLDrawArray(true);
    }

   this->setViewport(viewport);

}

void Plane::setViewport(Viewport* viewport){
    this->viewport = viewport;
    if(!this->viewport){
        this->clip_rect = NULL;
        return;
    }

    if(this->viewport->clip_rect.x != 0 || this->viewport->clip_rect.y != 0 ||
                this->viewport->clip_rect.height != 0  || this->viewport->clip_rect.width != 0 ){
                    this->clip_rect = &this->viewport->clip_rect;
    }
}


};

