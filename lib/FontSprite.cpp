#include <Fantasy2C/FontSprite.hpp>

namespace F2C{

GLhandleARB FontSprite::ShaderProgramObj = 0;
TexParam::Tex_Param FontSprite::filter = TexParam::Linear;
bool FontSprite::VertexArray = false;
bool FontSprite::checkVertexArray = false;
uint8 FontSprite::AlphaTolerance = 5;

uint FontSprite::defaultCharsperW = 16;
uint FontSprite::defaultCharsperH = 16;

void FontSprite::enableGLDrawArray(bool enable){
    FontSprite::VertexArray = enable;
    FontSprite::checkVertexArray = true;
}
bool FontSprite::isEnableGLDrawArray(){
    return FontSprite::VertexArray;
}

FontSprite::FontSprite(const FontSprite& copy) :
    SpriteBase(copy),
    clip_rect(NULL),
	viewport(NULL),
    charsperwidth(FontSprite::defaultCharsperW),
    charsperheight(FontSprite::defaultCharsperH),
    biggestCharWidth(0),
    biggestCharHeight(0),
    italic(false)
{
    if(!FontSprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        FontSprite::enableGLDrawArray(true);
    }

//	memset(this->char_rect,0,sizeof(this->char_rect[0])*256);

    *this = copy;
}

FontSprite& FontSprite::operator= (const FontSprite& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;
        this->charsperwidth = copy.charsperwidth;
        this->charsperheight = copy.charsperheight;
        this->biggestCharWidth = copy.biggestCharWidth;
        this->biggestCharHeight = copy.biggestCharHeight;
        this->strings = copy.strings;
        this->rect_strings = copy.rect_strings;
        this->italic = copy.italic;
        this->bitmapfont = copy.bitmapfont;

        memcpy(this->char_rect,copy.char_rect,sizeof(this->char_rect[0])*256);

        this->SpriteBase::operator = (copy);
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out,const FontSprite& copy){
    out << copy.tone;
    out << copy.charsperwidth;
    out << copy.charsperheight;
    out << copy.biggestCharWidth;
    out << copy.biggestCharHeight;
    out << copy.strings;
    out << copy.rect_strings;
    out << copy.italic;
    out << copy.bitmapfont;
    for(size_t i = 0;i < 256;++i)
        out << copy.char_rect[i];

    out << dynamic_cast<const SpriteBase&>(copy);

    return out;
}

std::istream& operator>>(std::istream &in, FontSprite& copy){
    in >> copy.tone;
    in >> copy.charsperwidth;
    in >> copy.charsperheight;
    in >> copy.biggestCharWidth;
    in >> copy.biggestCharHeight;
    in >> copy.strings;
    in >> copy.rect_strings;
    in >> copy.italic;
    in >> copy.bitmapfont;
    for(size_t i = 0;i < 256;++i)
        in >> copy.char_rect[i];

    in >> dynamic_cast<SpriteBase&>(copy);

    return in;
}

void FontSprite::copyProperties(const FontSprite& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;
        this->strings = copy.strings;
        this->rect_strings = copy.rect_strings;
        this->italic = copy.italic;

        this->SpriteBase::copyProperties(copy);
    }
}

FontSprite::FontSprite():
    clip_rect(NULL),
	viewport(NULL),
    charsperwidth(FontSprite::defaultCharsperW),
    charsperheight(FontSprite::defaultCharsperH),
    biggestCharWidth(0),
    biggestCharHeight(0),
    italic(false)
{
    if(!FontSprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        FontSprite::enableGLDrawArray(true);
    }
}

FontSprite::FontSprite(Viewport* viewport):
    clip_rect(NULL),
	viewport(NULL),
	charsperwidth(FontSprite::defaultCharsperW),
    charsperheight(FontSprite::defaultCharsperH),
    biggestCharWidth(0),
    biggestCharHeight(0),
	italic(false)
{
    if(!FontSprite::checkVertexArray){
        FontSprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        FontSprite::checkVertexArray = true;
    }

   this->setViewport(viewport);
}

FontSprite::FontSprite(const Bitmap* bitmap,uint charsperwidth,uint charsperheight) :
    clip_rect(NULL),
	viewport(NULL),
	charsperwidth(charsperwidth),
    charsperheight(charsperheight),
    biggestCharWidth(0),
    biggestCharHeight(0),
    italic(false)
{
    if(!FontSprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        FontSprite::enableGLDrawArray(true);
    }

    this->setBitmap(bitmap,charsperwidth,charsperheight);
}


void FontSprite::setBitmap(const Bitmap* bitmap,uint charsperwidth,uint charsperheight){
	if (bitmap){
        this->bitmapfont.loadBitmap(*bitmap,charsperwidth,charsperheight);
        this->setBitmap(&this->bitmapfont);
    }else{
        this->bitmapfont = TTFFont();
        this->setBitmap(&this->bitmapfont);
    }
}

void FontSprite::setBitmap(const TTFFont* font){
    if(font){
        this->charsperwidth = font->getCharsperWidth();
        this->charsperheight = font->getCharsperHeight();

        this->SpriteBase::setBitmap(&font->getBitmap());

        const Rect* charrects = font->getCharsSize();
        for(size_t i = 0;i < 256;++i)
            this->char_rect[i] = charrects[i];
    }else{
        this->charsperwidth = 0;
        this->charsperheight = 0;

        this->SpriteBase::setBitmap(NULL);

        for(size_t i = 0;i < 256;++i)
            this->char_rect[i].set(0,0,0,0);
    }
}

void FontSprite::addText(int x,int y,uint width,uint height,std::string text){
	this->strings.push_back(text);
	this->rect_strings.push_back(Rect (x,y,width,height));
}

void FontSprite::addText(const Rect& rect,std::string text){
	this->strings.push_back(text);
	this->rect_strings.push_back(rect);
}

void FontSprite::addText(int x,int y,std::string text){
    Rect rect = this->getStringSize(text);
    rect.x = x;
    rect.y = y;
	this->strings.push_back(text);
	this->rect_strings.push_back(rect);
}

void FontSprite::clearTexts(){
	this->strings.clear();
	this->rect_strings.clear();
}

F2C::Rect FontSprite::getStringSize(std::string str) const {
    if(this->getTexWidth() < 1 || this->getTexHeight() < 1 || str.empty())
        return F2C::Rect (0,0,0,0);

    F2C::uint x = 0; //current x-pos

    //current width
    F2C::uint w = this->char_rect[static_cast<size_t>(str[0])].width; //first letter
    //current height
    F2C::uint h = this->char_rect[static_cast<size_t>(str[0])].height; //first letter

    for(size_t i = 0;i < str.length();++i){
        if(str[i] == '\n'){
            h += this->char_rect[static_cast<size_t>(str[i])].height;
            x = 0;
            continue;
        }
        x += this->char_rect[static_cast<size_t>(str[i])].width;
        w = (x > w)? x : w; //longest/biggers Line
    }
    return F2C::Rect (0,0,w,h);
}

void FontSprite::setViewport(Viewport* viewport){
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

uint FontSprite::getCharsperWidth() const {return this->charsperwidth;}
uint FontSprite::getCharsperHeight() const {return this->charsperheight;}
const std::vector<std::string>& FontSprite::getTexts() const {return this->strings;}
const std::vector<Rect>& FontSprite::getTextsRect() const {return this->rect_strings;}
const Rect* FontSprite::getCharsRect() const {return this->char_rect;}

};

