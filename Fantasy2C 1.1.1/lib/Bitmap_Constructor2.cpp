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
                            bool blend, uint8 alpha) const
{
    if(alpha < 1)
        return;
    if(!src_data || !dst_data)
        return;

    //outside of Rect
    if(src_xstart > static_cast<int>(src_bitmapwidth) || src_ystart > static_cast<int>(src_bitmapheight))
        return;
    if(dst_xstart > static_cast<int>(dst_bitmapwidth) || dst_ystart > static_cast<int>(dst_bitmapheight))
        return;

    uint dstartx = std::max<int>(dst_xstart, 0);
    uint dstarty  = std::max<int>(dst_ystart, 0);
    uint dendx = std::min<int>(dst_xstart+width,dst_bitmapwidth);
    uint dendy = std::min<int>(dst_ystart+height,dst_bitmapheight);

    uint sstartx = std::max<int>(src_xstart, 0);
    uint sstarty = std::max<int>(src_ystart, 0);
    uint sendx = std::min<int>(src_xstart+width,src_bitmapwidth);
    uint sendy = std::min<int>(src_ystart+height,src_bitmapheight);

    size_t bpp = std::min(src_bytepp,dst_bytepp);

    for (uint dy = dstarty, sy = sstarty; dy < dendy || sy < sendy; dy++, sy++){
        for (uint dx = dstartx, sx = sstartx; dx < dendx  || sx < sendx; dx++, sx++) {
            //Source Pixel index
            uint32 spi = (sx + sy * src_width)*src_bytepp;
            //Destination Pixel index
            uint32 dpi = (dx + dy * dst_width)*dst_bytepp;

            //Alpha Blending
            //((srccolor * alpha) + (dstalpha * (255-alpha)) / 255

            //x >> 8 = x / 256
            //=>  (((srccolor+1) * (alpha+1)) + ((dstalpha+1) * (256 - (alpha+1))) >> 8 = 1..256
            //=> ((((srccolor+1) * (alpha+1)) + ((dstalpha+1) * (256 - (alpha+1))) >> 8) - 1 = 0..255
            if(blend){
                for(size_t i = 0;i < bpp;i++){
                    int32 color = dst_data[dpi+i];
                    color = ((src_data[spi+i]+1) * static_cast<int>(alpha+1)) + (dst_data[dpi+i] * static_cast<int>(257-alpha));
                    color = (color >> 8) - 1;
                    dst_data[dpi+i] = static_cast<uint8>(color);
                }
            }else{
                memcpy(&dst_data[dpi],&src_data[spi],bpp*sizeof(ubyte));
            }
        }
    }
}

void Bitmap::make_image(uint& image_id) const{
	GLubyte pixels[4];
	memset(pixels,0,4);

	ilGenImages(1,&image_id);
	ilBindImage(image_id);
	ilTexImage(1,1,1,4,static_cast<ILenum>(this->data_format),IL_UNSIGNED_BYTE,pixels);
}

void Bitmap::make_image(uint& image_id,uint width,uint height) const{
	GLubyte pixels[4];
	memset(pixels,0,4);

	ilGenImages(1,&image_id);
	ilBindImage(image_id);
	ilTexImage(1,1,1,4,static_cast<ILenum>(this->data_format),IL_UNSIGNED_BYTE,pixels);
	iluScale(width, height, 1);
}

void Bitmap::make_image(uint& image_id,uint width,uint height,uint8 r,uint8 g,uint8 b,uint8 a) const{
	GLubyte pixels[4] = {r,g,b,a};

	ilGenImages(1,&image_id);
	ilBindImage(image_id);
	ilTexImage(1,1,1,4,static_cast<ILenum>(this->data_format),IL_UNSIGNED_BYTE,pixels);
	iluScale(width, height, 1);
}

};
