#include <Fantasy2C/Bitmap.hpp>

namespace F2C{

void Bitmap::blt_image(const ubyte* src_data,
                            int src_xstart, int src_ystart, uint src_width,
                            uint src_bytepp,
                            uint src_bitmapwidth,uint src_bitmapheight,

                            ubyte* dst_data,
                            int dst_xstart, int dst_ystart,uint dst_width,
                            uint dst_bytepp,
                            uint dst_bitmapwidth,uint dst_bitmapheight,

                            uint width, uint height,
                            bool blend, uint8 alpha)
{
    if(blend && alpha < 1)
        return;
    if(!src_data || !dst_data)
        return;

    //outside of Bitmap
    if(src_xstart > static_cast<int>(src_bitmapwidth) || src_ystart > static_cast<int>(src_bitmapheight))
        return;
    if(dst_xstart > static_cast<int>(dst_bitmapwidth) || dst_ystart > static_cast<int>(dst_bitmapheight))
        return;

    //limit to the smallest width/height
    uint dstartx = std::max<int>(dst_xstart, 0);
    uint dstarty  = std::max<int>(dst_ystart, 0);
    uint dendx = std::min<int>(dst_xstart+width,dst_bitmapwidth);
    uint dendy = std::min<int>(dst_ystart+height,dst_bitmapheight);

    uint sstartx = std::max<int>(src_xstart, 0);
    uint sstarty = std::max<int>(src_ystart, 0);
    uint sendx = std::min<int>(src_xstart+width,src_bitmapwidth);
    uint sendy = std::min<int>(src_ystart+height,src_bitmapheight);

    //start is greater than end
    if(sstarty > sendy || dstarty > dendy)
        return;

    //Alpha Blending
    //((srccolor * alpha) + (dstalpha * (256-alpha)) / 255 (src/dst/alpha value range: 0-255)
    //((srccolor+1 * alpha+1) + (dstalpha+1 * (256-alpha+1)) / 256 (src/dst/alpha value range: 1-256)

    //x >> 8 = x / 256
    //=>  ((srccolor+1 * alpha+1) + (dstalpha+1 * (256 - alpha+1)) >> 8 = 1..256
    //=> (((srccolor+1 * alpha+1) + (dstalpha+1 * (256 - alpha+1)) >> 8) - 1 = 0..255

    //start coord.
    uint dx = dstartx;
    uint sx = sstartx;
    uint dy = dstarty;
    uint sy = sstarty;

    //whole width/height
    size_t wholewidth = std::min(sendx-sstartx,dendx-dstartx);
    size_t wholeheight = std::min(sendy-sstarty,dendy-dstarty);

    //Value is over 255 (convert to int)
    int intAlpha = alpha+1;

    //not blendeffect and have same bytepp
    if(!blend && (src_bytepp == dst_bytepp)){
        while(wholeheight-- > 0){
            //Source Pixel index
            size_t spi = (sstartx + sy * src_width)*src_bytepp;
            //Destination Pixel index
            size_t dpi = (dstartx + dy * dst_width)*dst_bytepp;

            //copy the whole width
            memcpy(dst_data+dpi,src_data+spi,wholewidth*src_bytepp*sizeof(ubyte));

            sy++;
            dy++;
        }
    }
    else if(src_bytepp == dst_bytepp){ //have same bytepp
        //copy the whole width with alphablending
        size_t resetcopyw = wholewidth*src_bytepp;
        while(wholeheight-- > 0){
            //Source Pixel index
            size_t spi = (sstartx + sy * src_width)*src_bytepp;
            //Destination Pixel index
            size_t dpi = (dstartx + dy * dst_width)*dst_bytepp;

            ubyte *dest = dst_data+dpi;
            ubyte const *src = src_data+spi;

            //copy the whole width with alphablending
            size_t copyw = resetcopyw;
            while(copyw-- > 0){
                //alpha blending color
                *dest = (((*src+1) * intAlpha) + ((*dest+1) * (256-intAlpha))) >> 8;
                (*dest)--;

                dest++;
                src++;
            }

            sy++;
            dy++;
        }
    }
    else{
        //copy as RGB/RGBA
        size_t bpp = std::min(src_bytepp,dst_bytepp);

        while(wholeheight-- > 0){
            size_t copyw = wholewidth;
            while(copyw-- > 0){
                //Source Pixel index
                size_t spi = (sx + sy * src_width)*src_bytepp;
                //Destination Pixel index
                size_t dpi = (dx + dy * dst_width)*dst_bytepp;

                ubyte *dest = dst_data+dpi;
                ubyte const *src = src_data+spi;

                if(src_bytepp <= 3){ //is RGB (without alpha)
                    uint len = bpp;

                    //without alphablending
                    while(len-- > 0){
                        *dest++ = *src++;
                    }

                    //set alpha to 255
                    if(dst_bytepp > 3){
                        *dest = 255;
                    }
                }else{
                    size_t len = bpp;

                    //copy as RGB/RGBA
                    while(len-- > 0){
                        *dest = ((((*src)+1) * intAlpha) + (((*dest)+1) * (256-intAlpha))) >> 8;
                        (*dest)--;

                        dest++;
                        src++;
                    }
                }

                sx++;
                dx++;
            }
            sy++;
            dy++;
        }
    }
}

void Bitmap::bltPixels(const ubyte* src_data,
                            int src_xstart, int src_ystart,
                            uint src_bitmapwidth,uint src_bitmapheight,
                            uint src_bytepp,

                            ubyte* dst_data,
                            int dst_xstart, int dst_ystart,
                            uint dst_bitmapwidth,uint dst_bitmapheight,
                            uint dst_bytepp,

                            uint width, uint height,
                            bool blend, uint8 alpha){
    Bitmap::blt_image(src_data,
                        src_xstart,src_ystart, src_bitmapwidth,
                        src_bytepp,
                        src_bitmapwidth,src_bitmapheight,

                        dst_data,
                        dst_xstart,dst_ystart,dst_bitmapwidth,
                        dst_bytepp,
                        dst_bitmapwidth,dst_bitmapheight,

                        width,height,
                        blend,alpha);

}

void Bitmap::make_image(GLuint* image_id,F2C::Image::DataFormat dataformat){
    if(!image_id)
        return;

	GLubyte pixels[4] = {0};

	ilGenImages(1,image_id);
	ilBindImage(*image_id);
	ilTexImage(1,1,1,4,static_cast<ILenum>(dataformat),IL_UNSIGNED_BYTE,pixels);
}

void Bitmap::make_image(GLuint* image_id,F2C::Image::DataFormat dataformat,uint width,uint height){
    if(!image_id)
        return;

	GLubyte pixels[4] = {0};

	ilGenImages(1,image_id);
	ilBindImage(*image_id);
	ilTexImage(1,1,1,4,static_cast<ILenum>(dataformat),IL_UNSIGNED_BYTE,pixels);
	iluScale(width, height, 1);
}

void Bitmap::make_image(GLuint* image_id,F2C::Image::DataFormat dataformat,uint width,uint height,uint8 r,uint8 g,uint8 b,uint8 a){
	if(!image_id)
        return;

	GLubyte pixels[4] = {r,g,b,a};

	ilGenImages(1,image_id);
	ilBindImage(*image_id);
	ilTexImage(1,1,1,4,static_cast<ILenum>(dataformat),IL_UNSIGNED_BYTE,pixels);
	iluScale(width, height, 1);
}

bool Bitmap::loadFileintoBitmap(GLuint image_id,std::istream& file,F2C::Image::ImageType type,LogError* error){
    ilBindImage(image_id);
    bool isError = false;
    ILenum loadedFormat = 0;

    file.seekg(0, std::ios_base::end);
    size_t sizef = file.tellg();

    ubyte* lump = new ubyte[sizef]();

    file.seekg(0, std::ios_base::beg);
    file.read((char*)lump,sizef);

	if (!ilLoadL(static_cast<ILenum>(type), lump, sizef)){
	    if(error)
            error->setError(iluErrorString(ilGetError()));
		isError = true;
	}
	delete[] lump;

    if(!isError){
        loadedFormat = static_cast<ILenum>(ilGetInteger(IL_IMAGE_FORMAT));
        if(loadedFormat != IL_RGB || loadedFormat != IL_RGBA){
            if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
                if(error)
                    error->setError(iluErrorString(ilGetError()));
                isError = true;
            }
        }
    }

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

    ubyte* copydata = ilGetData();
    if(!isError && copydata){
            this->filename = filename;
            this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
            this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
            this->width = this->create_width;
            this->height = this->create_height;
            this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
            this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));
            this->data_format = static_cast<Image::DataFormat>(ilGetInteger(IL_IMAGE_FORMAT));
            uint bpp = this->getBytes();

            this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
            this->psize = this->po2_size * this->po2_size * bpp;
            if(this->pixels)
                delete[] this->pixels;
            this->pixels = new ubyte[this->psize]();

            Bitmap::blt_image(copydata,
                                0, 0,ilGetInteger(IL_IMAGE_WIDTH),
                                ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL),
                                ilGetInteger(IL_IMAGE_WIDTH),ilGetInteger(IL_IMAGE_HEIGHT),

                                this->pixels,
                                0, 0,this->po2_size,
                                bpp,
                                this->width,this->height,

                                ilGetInteger(IL_IMAGE_WIDTH),ilGetInteger(IL_IMAGE_HEIGHT),
                                false,255);
    }

    return !isError;
}

bool Bitmap::loadFileintoBitmap(GLuint image_id,FILE* file,F2C::Image::ImageType type,LogError* error){
    ilBindImage(image_id);
    bool isError = false;
    ILenum loadedFormat = 0;

    fseek(file, 0, SEEK_END);
    size_t sizef = ftell(file);

    ubyte* lump = new ubyte[sizef]();

    fseek(file, 0, SEEK_SET);
    fread(lump, 1, sizef,file);

	if (!ilLoadL(static_cast<ILenum>(type), lump, sizef)){
	    if(error)
            error->setError(iluErrorString(ilGetError()));
		isError = true;
	}
	delete[] lump;

    if(!isError){
        loadedFormat = static_cast<ILenum>(ilGetInteger(IL_IMAGE_FORMAT));
        if(loadedFormat != IL_RGB || loadedFormat != IL_RGBA){
            if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
                if(error)
                    error->setError(iluErrorString(ilGetError()));
                isError = true;
            }
        }
    }

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

    ubyte* copydata = ilGetData();
    if(!isError && copydata){
            this->filename = filename;
            this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
            this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
            this->width = this->create_width;
            this->height = this->create_height;
            this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
            this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));
            this->data_format = static_cast<Image::DataFormat>(ilGetInteger(IL_IMAGE_FORMAT));
            uint bpp = this->getBytes();

            this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
            this->psize = this->po2_size * this->po2_size * bpp;
            if(this->pixels)
                delete[] this->pixels;
            this->pixels = new ubyte[this->psize]();

            Bitmap::blt_image(copydata,
                                0, 0,ilGetInteger(IL_IMAGE_WIDTH),
                                ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL),
                                ilGetInteger(IL_IMAGE_WIDTH),ilGetInteger(IL_IMAGE_HEIGHT),

                                this->pixels,
                                0, 0,this->po2_size,
                                bpp,
                                this->width,this->height,

                                ilGetInteger(IL_IMAGE_WIDTH),ilGetInteger(IL_IMAGE_HEIGHT),
                                false,255);
    }

    return !isError;
}

bool Bitmap::loadImageintoBitmap(GLuint image_id,std::string filename,F2C::Image::ImageType type,LogError* error){
    ilBindImage(image_id);
    bool isError = false;
    ILenum loadedFormat = 0;

	if (!ilLoad(static_cast<ILenum>(type),filename.c_str())){
		if(error)
            error->setError(iluErrorString(ilGetError()));
		isError = true;
	}

    if(!isError){
        loadedFormat = static_cast<ILenum>(ilGetInteger(IL_IMAGE_FORMAT));
        if(loadedFormat != IL_RGB || loadedFormat != IL_RGBA){
            if (!ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE)){
                if(error)
                    error->setError(iluErrorString(ilGetError()));
                isError = true;
            }
        }
    }

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

    ubyte* copydata = ilGetData();
    if(!isError && copydata){
            this->filename = filename;
            this->create_width = ilGetInteger(IL_IMAGE_WIDTH);
            this->create_height = ilGetInteger(IL_IMAGE_HEIGHT);
            this->width = this->create_width;
            this->height = this->create_height;
            this->bits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
            this->image_type = static_cast<Image::ImageType>(ilGetInteger(IL_IMAGE_TYPE));
            this->data_format = static_cast<Image::DataFormat>(ilGetInteger(IL_IMAGE_FORMAT));
            uint bpp = this->getBytes();

            this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
            this->psize = this->po2_size * this->po2_size * bpp;
            if(this->pixels)
                delete[] this->pixels;
            this->pixels = new ubyte[this->psize]();

            Bitmap::blt_image(copydata,
                                0, 0,ilGetInteger(IL_IMAGE_WIDTH),
                                ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL),
                                ilGetInteger(IL_IMAGE_WIDTH),ilGetInteger(IL_IMAGE_HEIGHT),

                                this->pixels,
                                0, 0,this->po2_size,
                                bpp,
                                this->width,this->height,

                                ilGetInteger(IL_IMAGE_WIDTH),ilGetInteger(IL_IMAGE_HEIGHT),
                                false,255);
    }

    return !isError;
}

void Bitmap::BuildFont(Rect* outarray,size_t outarraysize,
                       const Bitmap& bitmapfont,
                       uint charpw,uint charph,uint8 alphatolerance){
    if(!outarray || outarraysize < 1)
        return;
    if(bitmapfont.getWidth() <= 0 || bitmapfont.getHeight() <= 0 || charpw <= 0 || charph <= 0)
		return;
	uint cx = 0;
	uint cy = 0;
	uint pcw = bitmapfont.getWidth()/charpw;
	uint pch = bitmapfont.getHeight()/charph;
	uint biggestCharWidth = 0;
    uint biggestCharHeight = 0;
    F2C::uint bytepp = bitmapfont.getBytes();
    const ubyte* bitmap = bitmapfont.getPixels();
    size_t bitmapsize = bitmapfont.getWidth()*bitmapfont.getHeight()*bytepp;

	for (size_t i = 0;i < outarraysize && i < 256; ++i){
	    if (cy >= bitmapfont.getHeight())
			break;
        uint sx = cx;
	    uint sy = cy;
	    uint sw = cx+pcw;
	    uint sh = cy+pch;
        if(i == static_cast<size_t>(' ')){ //space
            outarray[i].set(sx,cy,sw-pcw/4,pch);
            cx += pcw;
            if (cx >= bitmapfont.getWidth()){
                cx = 0;
                cy += pch;
            }
            continue;
        }

        //|->|A | Determines the distance from start to the letter
        uint countx = 0;
        while(sx <= sw){
            if(i == 0 || bytepp < 4)
                break;
            size_t alphai = bytepp*(sx + sy * bitmapfont.getPixelsWidth())+3;
            if(alphai >= bitmapsize)
                break;
            if(bitmap[alphai] >= alphatolerance)
                break;
            sy++;
            if(sy >= sh){
                sy = cy;
                sx++;
                countx++;
            }
        }
        uint sx2 = cx+pcw;
	    uint sy2 = cy+pch;
	    uint sw2 = cx;
	    uint sh2 = cy;
	    uint countw = 0;
	    //| A|<-| Determines the distance from end to the letter
        while(sx2 >= sw2){
            if(i == 0 || bytepp < 4)
                break;
            size_t alphai = bytepp*(sx2 + sy2 * bitmapfont.getPixelsWidth())+3;
            if(alphai >= bitmapsize)
                break;
            if(bitmap[alphai] >= alphatolerance)
                break;
            sy2--;
            if(sy2 <= sh2){
                sy2 = cy+pch;
                sx2--;
                countw++;
            }
        }
        /*
        * (cx,cy)                                             (pcw,cy)
        *    |----------------------------------------------------|
        *    |                (sx,sy)     (sw,sy)                 |
        *    |--------|----------|-----------|-----------|--------|
        *    |        |first half|           |second half|        |
        *    |        |char      |   CHAR    |char       |        |
        *    |        |distance  |           |distance   |        |
        *    |-------countx------|-----------|-------countw-------|
        *    |                (sx,sh)     (sw,sh)                 |
        *    |--------|---------------crw----------------|--------|
        *    |----------------------------------------------------|
        * (cx,pch)                                            (pcw,pch)
        *
        *
        * (cx,cy)                                             (pcw,cy)
        *    |----------------------------------------------------|
        *    |   (cr.x,cr.y)                        (cr.w,cr.y)   |
        *    |--------|----------------------------------|--------|
        *    |        |                                  |        |
        *    |        |                                  |        |
        *    |        |                                  |        |
        *    |--------|----------------------------------|--------|
        *    |   (cr.x,cr.w)                        (cr.w,cr.h)   |
        *    |----------------------------------------------------|
        * (cx,pch)                                            (pcw,pch)
        *
        *cr = outarray[i]
        */

        uint chardistance = (static_cast<int>(pcw/charpw))/4;  //additional distance
        uint crw = static_cast<uint>(std::max<int>(0,(pcw-countx-countw) + chardistance));
		outarray[i].set(sx - static_cast<int>(chardistance/2),cy,crw,pch);
        biggestCharWidth = std::max<uint>(biggestCharWidth,crw);
        biggestCharHeight = std::max<uint>(biggestCharHeight,outarray[i].height);

		cx += pcw;
		if (cx >= bitmapfont.getWidth()){
			cx = 0;
			cy += pch;
		}
	}

	if(biggestCharWidth > 0 && outarraysize > static_cast<size_t>(' '))
        outarray[static_cast<size_t>(' ')].width = static_cast<uint>(static_cast<float>(biggestCharWidth)/3.0f);
}

};
