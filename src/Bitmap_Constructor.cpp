#include <Fantasy2C/Bitmap.hpp>

namespace F2C{

bool Bitmap::initil = false;

void Bitmap::initDevIL(){
    if(!Bitmap::initil){
        ilInit();
        iluInit();
        ilEnable(IL_FILE_OVERWRITE);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        Bitmap::initil = true;
    }
}

Bitmap::~Bitmap(){
    if (pixels)
        delete[] this->pixels;
}

Bitmap::Bitmap():
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();
}

Bitmap::Bitmap(uint _width,uint _height):
	filename(""),
	pixels(NULL),
	width(_width),
	height(_height),
	create_width(_width),
	create_height(_height),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();
    if(this->width > 0 && this->height > 0){
        this->bits = 32;
        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * 4;
        this->pixels = new ubyte[this->psize]();
    }
}

Bitmap::Bitmap(const ubyte* cpixels,uint width,uint height,uint bpp,Image::DataFormat format):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();

    if(width > 0 && height > 0 && bpp > 0 && cpixels){
        this->create_width = width;
        this->create_height = width;
        this->width = this->create_width;
        this->height = this->create_height;
        this->bits = bpp*8;
        this->data_format = format;

        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * this->getBytes();
        this->pixels = new ubyte[this->psize]();

        Bitmap::blt_image(cpixels,
                                0, 0,width,
                                bpp,
                                width,height,

                                this->pixels,
                                0, 0,this->po2_size,
                                this->getBytes(),
                                this->width,this->height,

                                this->create_width ,this->create_height,
                                false,255);
    }
}

Bitmap::Bitmap(const std::vector<ubyte>& cpixels,uint width,uint height,uint bpp,Image::DataFormat format):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();

    if(width > 0 && height > 0 && bpp > 0 && cpixels.size() >= bpp*sizeof(ubyte)){
            this->create_width = width;
            this->create_height = width;
            this->width = this->create_width;
            this->height = this->create_height;
            this->bits = bpp*8;
            this->data_format = format;

            this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
            this->psize = this->po2_size * this->po2_size * this->getBytes();
            this->pixels = new ubyte[this->psize]();

            Bitmap::blt_image(&(*cpixels.begin()),
                                0, 0,width,
                                bpp,
                                width,height,

                                this->pixels,
                                0, 0,this->po2_size,
                                this->getBytes(),
                                this->width,this->height,

                                this->create_width ,this->create_height,
                                false,255);
    }
}

Bitmap::Bitmap(std::string _filename):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();

    LogError error;

	std::fstream ffile (_filename.c_str(), std::fstream::in | std::fstream::out);
	if (ffile.is_open()){
		ffile.close();
	}else{
		std::ostringstream buffer;
		buffer << "No such file or directory: " << _filename.c_str() << std::endl;
		error.setError(buffer.str());
		throw error;
	}

	GLuint image = 0;
	this->make_image(&image,Image::RGBA);
	if(this->loadImageintoBitmap(image,_filename,Image::unknown,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

Bitmap::Bitmap(std::string _filename,Image::ImageType _type):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();

    LogError error;
	GLuint image = 0;
	this->make_image(&image,Image::RGBA);
	if(!this->loadImageintoBitmap(image,_filename,_type,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

Bitmap::Bitmap(FILE* stream):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();
    LogError error;

	if (!stream){
		error.setError("file-stream is NULL (possibly error by loading) \n");
		throw error;
	}

	GLuint image = 0;
	this->make_image(&image,Image::RGBA);
	if(!this->loadFileintoBitmap(image,stream,Image::unknown,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

Bitmap::Bitmap(FILE* stream,Image::ImageType _type):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();

    LogError error;
	GLuint image;
	this->make_image(&image,Image::RGBA);
	if(!this->loadFileintoBitmap(image,stream,_type,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

Bitmap::Bitmap(std::istream& stream):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();

    LogError error;
	GLuint image;
	this->make_image(&image,Image::RGBA);
	if(!this->loadFileintoBitmap(image,stream,Image::unknown,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

Bitmap::Bitmap(std::istream& stream,Image::ImageType _type):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();

    LogError error;
	GLuint image;
	this->make_image(&image,Image::RGBA);
	if(!this->loadFileintoBitmap(image,stream,_type,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

Bitmap::Bitmap(const Bitmap &cbitmap):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	is_changed(false),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    Bitmap::initDevIL();
	*this = cbitmap;
}

Bitmap& Bitmap::operator= (const Bitmap& cbitmap){
    if (this != &cbitmap){
        this->filename = cbitmap.filename;
        this->width = cbitmap.width;
        this->height = cbitmap.height;
        this->create_width = cbitmap.create_width;
        this->create_height = cbitmap.create_height;
        this->image_type = cbitmap.image_type;
        this->data_format = cbitmap.data_format;
        this->bits = cbitmap.bits;
        this->psize = cbitmap.psize;
        this->po2_size = cbitmap.po2_size;
        this->is_changed = cbitmap.is_changed;

        if(this->pixels)
            delete[] this->pixels;
        this->pixels = NULL;

        if(cbitmap.pixels){
            this->pixels = new ubyte[cbitmap.psize]();
            memcpy(this->pixels,cbitmap.pixels,cbitmap.psize*sizeof(ubyte));
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out,const F2C::Bitmap& cbitmap){
    int itype = static_cast<int>(cbitmap.image_type);
    int iformat = static_cast<int>(cbitmap.data_format);

    out << cbitmap.filename;
    out << cbitmap.width;
    out << cbitmap.height;
    out << cbitmap.create_width;
    out << cbitmap.create_height;
    out << itype;
    out << iformat;
    out << cbitmap.bits;
    out << cbitmap.psize;
    out << cbitmap.po2_size;
    out << cbitmap.is_changed;

    if(cbitmap.pixels){
        for(size_t i = 0;i < cbitmap.psize;++i){
            out << cbitmap.pixels[i];
        }
    }

    return out;
}

std::istream& operator>>(std::istream &in, F2C::Bitmap& cbitmap){
    int itype = 0;
    int iformat = 0;

    in >> cbitmap.filename;
    in >> cbitmap.width;
    in >> cbitmap.height;
    in >> cbitmap.create_width;
    in >> cbitmap.create_height;
    in >> itype;
    in >> iformat;
    in >> cbitmap.bits;
    in >> cbitmap.psize;
    in >> cbitmap.po2_size;
    in >> cbitmap.is_changed;

    cbitmap.image_type = static_cast<Image::ImageType>(itype);
    cbitmap.data_format = static_cast<Image::DataFormat>(iformat);

    if(cbitmap.pixels){
        for(size_t i = 0;i < cbitmap.psize;++i){
            in >> cbitmap.pixels[i];
        }
    }

    return in;
}

void Bitmap::loadFile(std::string _filename){
    this->filename = "";
    this->width = 0;
    this->height = 0;
    this->create_width = 0;
    this->create_height = 0;
    this->image_type = Image::unknown;
    this->data_format = Image::RGBA;
    this->bits = 0;
    this->po2_size = 0;
    this->psize = 0;
    this->is_changed = false;
    if(this->pixels)
        delete[] pixels;
    this->pixels = NULL;

    LogError error;
	GLuint image = 0;
	this->make_image(&image,Image::RGBA);
    if(!this->loadImageintoBitmap(image,_filename,Image::unknown,&error)){
        ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

void Bitmap::loadFile(std::string _filename,Image::ImageType _type){
    this->filename = "";
    this->width = 0;
    this->height = 0;
    this->create_width = 0;
    this->create_height = 0;
    this->image_type = Image::unknown;
    this->data_format = Image::RGBA;
    this->bits = 0;
    this->po2_size = 0;
    this->psize = 0;
    this->is_changed = false;
    if(this->pixels)
         delete[] pixels;
    this->pixels = NULL;

    LogError error;
    GLuint image;
    this->make_image(&image,Image::RGBA);
    if(!this->loadImageintoBitmap(image,_filename,_type,&error)){
        ilDeleteImages(1,&image);
        throw error;
    }
    ilDeleteImages(1,&image);
}

void Bitmap::loadFile(FILE* stream){
    this->filename = "";
    this->width = 0;
    this->height = 0;
    this->create_width = 0;
    this->create_height = 0;
    this->image_type = Image::unknown;
    this->data_format = Image::RGBA;
    this->bits = 0;
    this->po2_size = 0;
    this->psize = 0;
    this->is_changed = false;
    if(this->pixels)
         delete[] pixels;
    this->pixels = NULL;

    LogError error;
	GLuint image;
	this->make_image(&image,Image::RGBA);
	if(!this->loadFileintoBitmap(image,stream,Image::unknown,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

void Bitmap::loadFile(FILE* stream,Image::ImageType _type){
    this->filename = "";
    this->width = 0;
    this->height = 0;
    this->create_width = 0;
    this->create_height = 0;
    this->image_type = Image::unknown;
    this->data_format = Image::RGBA;
    this->bits = 0;
    this->po2_size = 0;
    this->psize = 0;
    this->is_changed = false;
    if(this->pixels)
         delete[] pixels;
    this->pixels = NULL;

    LogError error;
	GLuint image;
	this->make_image(&image,Image::RGBA);
	if(!this->loadFileintoBitmap(image,stream,_type,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}



void Bitmap::loadFile(std::istream& stream){
    this->filename = "";
    this->width = 0;
    this->height = 0;
    this->create_width = 0;
    this->create_height = 0;
    this->image_type = Image::unknown;
    this->data_format = Image::RGBA;
    this->bits = 0;
    this->po2_size = 0;
    this->psize = 0;
    this->is_changed = false;
    if(this->pixels)
         delete[] pixels;
    this->pixels = NULL;

    LogError error;
	GLuint image;
	this->make_image(&image,Image::RGBA);
	if(!this->loadFileintoBitmap(image,stream,Image::unknown,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

void Bitmap::loadFile(std::istream& stream,Image::ImageType _type){
    this->filename = "";
    this->width = 0;
    this->height = 0;
    this->create_width = 0;
    this->create_height = 0;
    this->image_type = Image::unknown;
    this->data_format = Image::RGBA;
    this->bits = 0;
    this->po2_size = 0;
    this->psize = 0;
    this->is_changed = false;
    if(this->pixels)
         delete[] pixels;
    this->pixels = NULL;

    LogError error;
	GLuint image;
	this->make_image(&image,Image::RGBA);
	if(!this->loadFileintoBitmap(image,stream,_type,&error)){
	    ilDeleteImages(1,&image);
        throw error;
	}
	ilDeleteImages(1,&image);
}

void Bitmap::newBitmap(uint _width,uint _height){
    this->filename = "";
	this->width = _width;
	this->height = _height;
	this->create_width = _width;
	this->create_height = _height;
	this->image_type = Image::unknown;
	this->data_format = Image::RGBA;
	this->po2_size = 0;
	this->bits = 0;
	this->psize = 0;
	this->is_changed = false;
    if(this->pixels)
         delete[] pixels;
    this->pixels = NULL;

    if(this->width > 0 && this->height > 0){
        this->bits = 32;
        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * 4;
        this->pixels = new ubyte[this->psize]();
    }
}


void Bitmap::loadPixelArray(const ubyte* cpixels,uint _width,uint _height,uint bpp,Image::DataFormat format){
	this->filename = "";
	this->width = 0;
	this->height = 0;
	this->create_width = 0;
	this->create_height = 0;
	this->image_type = Image::unknown;
	this->data_format = Image::RGBA;
	this->po2_size = 0;
	this->bits = 0;
	this->psize = 0;
	this->is_changed = false;
    if(this->pixels)
         delete[] pixels;
    this->pixels = NULL;

    if(width > 0 && height > 0 && bpp > 0 && pixels){
        this->create_width = width;
        this->create_height = width;
        this->width = this->create_width;
        this->height = this->create_height;
        this->bits = bpp*8;
        this->data_format = format;

        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * (this->getBytes());
        this->pixels = new ubyte[this->psize]();

        Bitmap::blt_image(cpixels,
                            0, 0,width,
                            bpp,
                            width,height,

                            this->pixels,
                            0, 0,this->po2_size,
                            this->getBytes(),
                            this->width,this->height,

                            width,height,
                            false,255);
    }
}

void Bitmap::loadPixelArray(const std::vector<ubyte>& cpixels,uint width,uint height,uint bpp,Image::DataFormat format){
    this->filename = "";
	this->width = 0;
	this->height = 0;
	this->create_width = 0;
	this->create_height = 0;
	this->image_type = Image::unknown;
	this->data_format = Image::RGBA;
	this->po2_size = 0;
	this->bits = 0;
	this->psize = 0;
	this->is_changed = false;
    if(this->pixels)
         delete[] pixels;
    this->pixels = NULL;

    if(width > 0 && height > 0 && bpp > 0 &&
       cpixels.size() <= width*height*bpp){
            this->create_width = width;
            this->create_height = width;
            this->width = this->create_width;
            this->height = this->create_height;
            this->bits = bpp << 3;
            this->data_format = format;

            this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
            this->psize = this->po2_size * this->po2_size * (this->getBytes());
            this->pixels = new ubyte[this->psize]();

            Bitmap::blt_image(&(*cpixels.begin()),
                            0, 0,width,
                            bpp,
                            width,height,

                            this->pixels,
                            0, 0,this->po2_size,
                            this->getBytes(),
                            this->width,this->height,

                            width,height,
                            false,255);
    }
}

}

