#include "Bitmap.hpp"

namespace F2C{

void Bitmap::blt_image(const ubyte* src_data,
                            int src_xstart, int src_ystart, uint src_width,uint src_height,
                            uint src_bytepp,

                            ubyte* dst_data,
                            int dst_xstart, int dst_ystart,uint dst_width,uint dst_height,
                            uint dst_bytepp,

                            uint width, uint height,
                            bool blend, uint8 alpha) const
{
    if(!src_data || !dst_data)
        return;

    //outside of Rect
    if(src_xstart >= static_cast<int>(src_width) || src_ystart >= static_cast<int>(src_height))
        return;
    if(dst_xstart >= static_cast<int>(src_width) || dst_ystart >= static_cast<int>(dst_height))
        return;

    uint dleft = std::max<uint>(dst_xstart, 0);
    uint dtop  = std::max<uint>(dst_ystart, 0);
    uint dright = std::min<uint>(dst_xstart+width,dst_width);
    uint dbottom = std::min<uint>(dst_ystart+height,dst_height);

    uint sleft = std::max<uint>(src_xstart, 0);
    uint stop = std::max<uint>(src_ystart, 0);
    uint sright = std::min<uint>(src_xstart+width,src_width);
    uint sbottom = std::min<uint>(src_ystart+height,src_height);

	for (size_t dy = dleft, sy = sleft; dy < dright || sy < sright; ++dy, ++sy){
        for (size_t dx = dtop, sx = stop; dx < dbottom  || sx < sbottom; ++dx, ++sx) {
            //Source Pixel index
            size_t spi = (sx + sy * src_width)*src_bytepp;
            //Destination Pixel index
            size_t dpi = (dx + dy * dst_width)*dst_bytepp;
            size_t bpp = std::min(src_bytepp,dst_bytepp);
            //Alpha Blending
            //src_color * alpha + dst_color * (255-alpha)
            //... >> 8 ,Keep in 0-255 Range
            if(blend)
                for(size_t i = 0;i < bpp;i++){
                    dst_data[dpi+i] = ((src_data[spi+i] * (alpha+1)) + (dst_data[dpi+i] * (256-alpha))) >> 8;
                }
            else
                memcpy(&dst_data[dpi],&src_data[spi],bpp*sizeof(ubyte));
        }
    }
}

void Bitmap::make_image(uint& image_id) const{
	GLubyte pixels[4];
	memset(pixels,0,4);

	ilGenImages(1,&image_id);
	ilBindImage(image_id);
	ilTexImage(1,1,1,4,this->data_format,IL_UNSIGNED_BYTE,pixels);
}

void Bitmap::make_image(uint& image_id,uint width,uint height) const{
	GLubyte pixels[4];
	memset(pixels,0,4);

	ilGenImages(1,&image_id);
	ilBindImage(image_id);
	ilTexImage(1,1,1,4,this->data_format,IL_UNSIGNED_BYTE,pixels);
	iluScale(width, height, 1);
}

void Bitmap::make_image(uint& image_id,uint width,uint height,uint8 r,uint8 g,uint8 b,uint8 a) const{
	GLubyte pixels[4] = {r,g,b,a};

	ilGenImages(1,&image_id);
	ilBindImage(image_id);
	ilTexImage(1,1,1,4,this->data_format,IL_UNSIGNED_BYTE,pixels);
	iluScale(width, height, 1);
}

};
