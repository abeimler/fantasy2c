#include <Fantasy2C/Bitmap.hpp>

namespace F2C{

bool Bitmap::initil = false;

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
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    if(!Bitmap::initil){
        ilInit();
        iluInit();
        ilEnable(IL_FILE_OVERWRITE);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        Bitmap::initil = true;
    }
}

Bitmap::Bitmap(uint _width,uint _height):
	filename(""),
	pixels(NULL),
	width(_width),
	height(_height),
	create_width(_width),
	create_height(_height),
	po2_size(0),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(32),
	psize(0)
{
    if(!Bitmap::initil){
        ilInit();
        iluInit();
        ilEnable(IL_FILE_OVERWRITE);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        Bitmap::initil = true;
    }
    if(this->width > 0 && this->height > 0){
        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * (this->bits >> 3);
        this->pixels = new ubyte[this->psize];
        memset(this->pixels,0,this->psize*sizeof(ubyte));
    }
}

Bitmap::Bitmap(const ubyte* pixels,uint width,uint height,uint bpp,Image::DataFormat format):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    if(!Bitmap::initil){
        ilInit();
        iluInit();
        ilEnable(IL_FILE_OVERWRITE);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        Bitmap::initil = true;
    }
    if(width > 0 && height > 0 && bpp > 0 && pixels){
        this->create_width = width;
        this->create_height = width;
        this->width = this->create_width;
        this->height = this->create_height;
        this->bits = bpp << 3;
        this->data_format = format;

        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * this->bits;
        this->pixels = new ubyte[this->psize];
        for(size_t x = 0;x < this->width;x++){
            for(size_t y = 0;y < this->height;y++){
                memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                        &pixels[bpp*(x + y * this->width)],
                        bpp*sizeof(ubyte));
            }
        }
    }
}

Bitmap::Bitmap(const std::vector<ubyte>& pixels,uint width,uint height,uint bpp,Image::DataFormat format):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    if(!Bitmap::initil){
        ilInit();
        iluInit();
        ilEnable(IL_FILE_OVERWRITE);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        Bitmap::initil = true;
    }
    if(width > 0 && height > 0 && bpp > 0 && pixels.size() >= bpp*sizeof(ubyte)){
            this->create_width = width;
            this->create_height = width;
            this->width = this->create_width;
            this->height = this->create_height;
            this->bits = bpp << 3;
            this->data_format = format;

            this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
            this->psize = this->po2_size * this->po2_size * this->bits;
            this->pixels = new ubyte[this->psize];
            for(size_t x = 0;x < this->width;x++){
                for(size_t y = 0;y < this->height;y++){
                    if(x*y*this->bits > pixels.size())
                        break;
                    memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                            &pixels[bpp*(x + y * this->width)],
                            bpp*sizeof(ubyte));
                }
            }
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
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    if(!Bitmap::initil){
        ilInit();
        iluInit();
        ilEnable(IL_FILE_OVERWRITE);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        Bitmap::initil = true;
    }

	std::fstream ffile (_filename.c_str(), std::fstream::in | std::fstream::out);
	if (ffile.is_open()){
		ffile.close();
	}else{
		std::ostringstream buffer;
		LogError error;
		buffer << "No such file or directory: " << _filename.c_str() << '\n';
		error.setError(buffer.str());
		throw error;
	}

	GLuint image;
	this->make_image(image);
	ilBindImage(image);

	if (!ilLoadImage(_filename.c_str())){
	    ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}
	if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
	    ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}
    this->filename = _filename;
	this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
	this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
	this->width = this->create_width;
	this->height = this->create_height;
	this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));

    this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
    this->psize = this->po2_size * this->po2_size * ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    this->pixels = new ubyte[this->psize]();
    memset(this->pixels,0,this->psize*sizeof(ubyte));

	ubyte* copydata = ilGetData();
	uint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	if (copydata){
	    for(size_t x = 0;x < this->width;x++){
            for(size_t y = 0;y < this->height;y++){
                memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                        &copydata[bpp*(x + y * this->width)],
                        bpp*sizeof(ubyte));
            }
        }
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
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    if(!Bitmap::initil){
        ilInit();
        iluInit();
        ilEnable(IL_FILE_OVERWRITE);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        Bitmap::initil = true;
    }

	std::fstream ffile (_filename.c_str(), std::fstream::in | std::fstream::out);
	if (ffile.is_open()){
		ffile.close();
	}else{
		std::ostringstream buffer;
		LogError error;
		buffer << "No such file or directory: " << _filename.c_str() << '\n';
		error.setError(buffer.str());
		throw error;
	}

	GLuint image;
	this->make_image(image);
	ilBindImage(image);

	if (!ilLoad(static_cast<ILenum>(_type),_filename.c_str())){
	    ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}
	if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
	    ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}

    this->filename = _filename;
	this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
	this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
	this->width = this->create_width;
	this->height = this->create_height;
	this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));

    this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
    this->psize = this->po2_size * this->po2_size * ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    this->pixels = new ubyte[this->psize]();
    memset(this->pixels,0,this->psize*sizeof(ubyte));

	ubyte* copydata = ilGetData();
	uint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	if (copydata){
	    for(size_t x = 0;x < this->width;x++){
            for(size_t y = 0;y < this->height;y++){
                memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                        &copydata[bpp*(x + y * this->width)],
                        bpp*sizeof(ubyte));
            }
        }
	}

	ilDeleteImages(1,&image);
}

Bitmap::Bitmap(const FILE* stream):
	filename(""),
	pixels(NULL),
	width(0),
	height(0),
	create_width(0),
	create_height(0),
	po2_size(0),
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    if(!Bitmap::initil){
        ilInit();
        iluInit();
        ilEnable(IL_FILE_OVERWRITE);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        Bitmap::initil = true;
    }

	bool status = true;

	if (!status){
		LogError error;
		error.setError("No such stream or directory");
		throw error;
	}

	GLuint image;
	this->make_image(image);
	ilBindImage(image);

	if (!ilLoadF(IL_TYPE_UNKNOWN,(char *)stream)){
	   ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}
	if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
	   ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}

	if (status){
		this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
		this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
		this->width = this->create_width;
		this->height = this->create_height;
		this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
		this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));

        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
        this->pixels = new ubyte[this->psize]();
        memset(this->pixels,0,this->psize*sizeof(ubyte));

		ubyte* copydata = ilGetData();
		uint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		if (copydata){
		    for(size_t x = 0;x < this->width;x++){
                for(size_t y = 0;y < this->height;y++){
                    memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                            &copydata[bpp*(x + y * this->width)],
                            bpp*sizeof(ubyte));
                }
            }
		}

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
	image_type(Image::unknown),
	data_format(Image::RGBA),
	bits(0),
	psize(0)
{
    if(!Bitmap::initil){
        ilInit();
        iluInit();
        ilEnable(IL_FILE_OVERWRITE);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        Bitmap::initil = true;
    }

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
	if(this->pixels)
         delete[] pixels;

    std::fstream ffile (_filename.c_str(), std::fstream::in | std::fstream::out);
	if (ffile.is_open()){
		ffile.close();
	}else{
		std::ostringstream buffer;
		LogError error;
		buffer << "No such file or directory: " << _filename.c_str() << '\n';
		error.setError(buffer.str());
		throw error;
	}

	GLuint image;
	this->make_image(image);
	ilBindImage(image);

	if (!ilLoadImage(_filename.c_str())){
	    ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}
	if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
	   ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}

    this->filename = _filename;
	this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
	this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
	this->width = this->create_width;
	this->height = this->create_height;
	this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));

    this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
    this->psize = this->po2_size * this->po2_size * ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    this->pixels = new ubyte[this->psize]();
    memset(this->pixels,0,this->psize*sizeof(ubyte));

	ubyte* copydata = ilGetData();
	uint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	if (copydata){
	    for(size_t x = 0;x < this->width;x++){
            for(size_t y = 0;y < this->height;y++){
                memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                        &copydata[bpp*(x + y * this->width)],
                        bpp*sizeof(ubyte));
            }
        }
	}

	ilDeleteImages(1,&image);
}

void Bitmap::loadFile(std::string _filename,Image::ImageType _type){
   this->filename = "";
	this->width = 0;
	this->height = 0;
	this->create_width = 0;
	this->create_height = 0;
	this->image_type = _type;
	this->data_format = Image::RGBA;
	this->bits = 0;
	this->po2_size = 0;
	this->psize = 0;
	if(this->pixels)
         delete[] pixels;

    std::fstream ffile (_filename.c_str(), std::fstream::in | std::fstream::out);
	if (ffile.is_open()){
		ffile.close();
	}else{
		std::ostringstream buffer;
		LogError error;
		buffer << "No such file or directory: " << _filename.c_str() << '\n';
		error.setError(buffer.str());
		throw error;
	}

	GLuint image;
	this->make_image(image);
	ilBindImage(image);

	if (!ilLoad(_type,_filename.c_str())){
	    ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}
	if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
	    ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
	}

    this->filename = _filename;
	this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
	this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
	this->width = this->create_width;
	this->height = this->create_height;
	this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));

    this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
    this->psize = this->po2_size * this->po2_size * ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    this->pixels = new ubyte[this->psize]();
    memset(this->pixels,0,this->psize*sizeof(ubyte));

	ubyte* copydata = ilGetData();
	uint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	if (copydata){
	    for(size_t x = 0;x < this->width;x++){
            for(size_t y = 0;y < this->height;y++){
                memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                        &copydata[bpp*(x + y * this->width)],
                        bpp*sizeof(ubyte));
            }
        }
	}
	ilDeleteImages(1,&image);
}

void Bitmap::loadFile(const FILE* stream){
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
	if(this->pixels)
         delete[] pixels;

    bool status = true;
	if (!stream){
		LogError error;
		error.setError("No such stream");
		throw error;
		status = false;
	}

	GLuint image;
	this->make_image(image);
	ilBindImage(image);

	if (!ilLoadF(IL_TYPE_UNKNOWN,(char *)stream)){
	   ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
		status = false;
	}
	if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
	   ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
		status = false;
	}

	if (status){
		this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
		this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
		this->width = this->create_width;
		this->height = this->create_height;
		this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
		this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));

        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
        this->pixels = new ubyte[this->psize]();
        memset(this->pixels,0,this->psize*sizeof(ubyte));

		ubyte* copydata = ilGetData();
		uint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		if (copydata){
		    for(size_t x = 0;x < this->width;x++){
                for(size_t y = 0;y < this->height;y++){
                    memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                            &copydata[bpp*(x + y * this->width)],
                            bpp*sizeof(ubyte));
                }
            }
		}

	}
	ilDeleteImages(1,&image);
}

void Bitmap::loadFile(const FILE* stream,Image::ImageType _type){
    this->filename = "";
	this->width = 0;
	this->height = 0;
	this->create_width = 0;
	this->create_height = 0;
	this->image_type = _type;
	this->data_format = Image::RGBA;
	this->po2_size = 0;
	this->bits = 0;
	this->psize = 0;
	if(this->pixels)
         delete[] pixels;

    bool status = true;
	if (!stream){
		LogError error;
		error.setError("No such stream");
		throw error;
		status = false;
	}

	GLuint image;
	this->make_image(image);
	ilBindImage(image);

	if (!ilLoadF(static_cast<ILenum>(_type),(char*)stream)){
	   ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
		status = false;
	}
	if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
	   ilDeleteImages(1,&image);
		LogError error;
		error.setError(iluErrorString(ilGetError()));
		throw error;
		status = false;
	}

	if (status){
		this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
		this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
		this->width = this->create_width;
		this->height = this->create_height;
		this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
		this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));

        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
        this->pixels = new ubyte[this->psize]();
        memset(this->pixels,0,this->psize*sizeof(ubyte));

		ubyte* copydata = ilGetData();
		uint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		if (copydata){
		    for(size_t x = 0;x < this->width;x++){
                for(size_t y = 0;y < this->height;y++){
                    memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                            &copydata[bpp*(x + y * this->width)],
                            bpp*sizeof(ubyte));
                }
            }
		}

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
	this->bits = 32;
	this->psize = 0;
    if(this->pixels)
         delete[] pixels;
    this->pixels = NULL;

    if(this->width > 0 && this->height > 0){
        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * (this->bits >> 3);
        this->pixels = new ubyte[this->psize]();
        memset(this->pixels,0,this->psize*sizeof(ubyte));
    }
}


void Bitmap::loadPixelArray(const ubyte* pixels,uint width,uint height,uint bpp,Image::DataFormat format){
	this->filename = "";
    this->width = 0;
    this->height = 0;
    this->bits = 0;
    this-> image_type = Image::unknown;
    this->po2_size = 0;
    this->psize = 0;
    if(this->pixels)
        delete[] this->pixels;

    if(width > 0 && height > 0 && bpp > 0 && pixels){
        this->create_width = width;
        this->create_height = width;
        this->width = this->create_width;
        this->height = this->create_height;
        this->bits = bpp >> 3;
        this->data_format = format;

        this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
        this->psize = this->po2_size * this->po2_size * this->bits;
        this->pixels = new ubyte[this->psize]();

        for(size_t x = 0;x < this->width;x++){
            for(size_t y = 0;y < this->height;y++){
                memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                        &pixels[bpp*(x + y * this->width)],
                        bpp*sizeof(ubyte));
            }
        }
    }
}

void Bitmap::loadPixelArray(const std::vector<ubyte>& pixels,uint width,uint height,uint bpp,Image::DataFormat format){
    this->filename = "";
    this->width = 0;
    this->height = 0;
    this->bits = 0;
    this-> image_type = Image::unknown;
    this->po2_size = 0;
    this->psize = 0;
    if(this->pixels)
        delete[] this->pixels;

    if(width > 0 && height > 0 && bpp > 0 && pixels.size() >= bpp*sizeof(ubyte)){
            this->create_width = width;
            this->create_height = width;
            this->width = this->create_width;
            this->height = this->create_height;
            this->bits = bpp >> 3;
            this->data_format = format;

            this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
            this->psize = this->po2_size * this->po2_size * this->bits;
            this->pixels = new ubyte[this->psize]();

            for(size_t x = 0;x < this->width;x++){
                for(size_t y = 0;y < this->height;y++){
                    if(x*y*this->bits > pixels.size())
                        break;
                    memcpy(&this->pixels[bpp*(x + y * this->po2_size)],
                            &pixels[bpp*(x + y * this->width)],
                            bpp*sizeof(ubyte));
                }
            }
    }
}

};

