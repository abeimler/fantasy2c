#include <Fantasy2C/Font.hpp>

namespace F2C{

#if defined(_ISWINDOWS)
    std::string TTFFont::defaultdir = "C:/WINDOWS/Fonts/";
    std::string TTFFont::defaultName = "Arial.ttf";
#elif defined(_ISLINUX)
    std::string TTFFont::defaultdir = "/usr/share/fonts/truetype/";
    std::string TTFFont::defaultName = "arial.ttf";
#elif defined(macintosh) || (defined(__APPLE__) && defined(__MACH__))
    std::string TTFFont::defaultdir = "/Library/Fonts/";
    std::string TTFFont::defaultName = "Arial";
#else
    std::string TTFFont::defaultdir;
    std::string TTFFont::defaultName = "Arial.ttf";
#endif

uint TTFFont::defaultSize = 16;
TTFFont::TTFLibrary TTFFont::library;
FT_Library TTFFont::TTFLibrary::library_;
Color TTFFont::defaultColor (255,255,255,255);
uint TTFFont::defaultCharsperW = 16;
uint TTFFont::defaultCharsperH = 16;
uint8 TTFFont::defaultAlphaTolerance = 5;

TTFFont::TTFLibrary::TTFLibrary(){
    if (FT_Init_FreeType(&library_) != 0){
        LogError error;
		error.setError("Could not initialize FreeType2 library.\n");
		error.setErrorCode(ErrorCode::FREETYPE_ERROR);
		throw error;
    }
}

TTFFont::TTFLibrary::~TTFLibrary(){
    FT_Done_FreeType(library_);
}

FT_Library& TTFFont::TTFLibrary::getLibrary(){
    return library_;
}

void TTFFont::open(Bitmap& _bitmap,std::string _filename, unsigned int _size,Color _color,uint _charsperwidth,uint _charsperheight){
    FT_Face face;

	std::fstream ffile (_filename.c_str(), std::fstream::in | std::fstream::out);
	if (ffile.is_open()){
		ffile.close();
	}else{
		std::ostringstream buffer;
		LogError error;
		buffer << "No such file or directory: " << _filename.c_str() << std::endl;
		error.setError(buffer.str());
		error.setErrorCode(ErrorCode::NO_SUCH_FILE_OR_DIR);
		throw error;
	}

    if(FT_New_Face(TTFFont::library.getLibrary(), _filename.c_str(), 0, &face) != 0){
		std::ostringstream buffer;
		LogError error;
		buffer << "Could not load font file: " << _filename.c_str() << std::endl;
		error.setError(buffer.str());
		error.setErrorCode(ErrorCode::FREETYPE_ERROR);
		throw error;
    }

    if(!(face->face_flags & FT_FACE_FLAG_SCALABLE) ||
        !(face->face_flags & FT_FACE_FLAG_HORIZONTAL)){
			std::ostringstream buffer;
			LogError error;
			buffer << "Invalid font: Error setting font size: " << _filename.c_str() << std::endl;
            error.setErrorCode(ErrorCode::FREETYPE_ERROR);
			error.setError(buffer.str());
			throw error;
    }

    FT_Set_Char_Size( face, _size << 6, _size << 6, 0, 0);

    uint charSize = 0;
    uint charWidth = 0;
    uint charHeight = 0;
    uint charTop = 0;
    uint charIndex = 0;

    for(size_t ch = 0; ch < 256; ++ch){
        charIndex = FT_Get_Char_Index(face, ch);

        FT_Load_Glyph(face, charIndex, FT_LOAD_DEFAULT);
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

        FT_Glyph glyph;
        FT_Get_Glyph( face->glyph, &glyph );

        FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
        FT_Bitmap& bitmap = bitmap_glyph->bitmap;

        this->char_rect[ch].width = bitmap.width;
        this->char_rect[ch].height = bitmap.rows;
        charHeight = std::max<uint>(this->char_rect[ch].height,charHeight);
        charTop = std::max<uint>(bitmap_glyph->top,charTop);
        charWidth = std::max<uint>(this->char_rect[ch].width ,charWidth);
    }
    charSize = std::max<uint>(charHeight+static_cast<uint>(charHeight*0.75f),charWidth);

    _bitmap.newBitmap(charSize*_charsperwidth,charSize*_charsperheight);

    uint x = 0;
    uint y = 0;

    for(uint ch = 0; ch < 256; ++ch){
        uint charIndex = FT_Get_Char_Index(face, ch);

        FT_Load_Glyph(face, charIndex, FT_LOAD_DEFAULT);
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

        FT_Glyph glyph;
        FT_Get_Glyph( face->glyph, &glyph );

        FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
        FT_Bitmap& bitmap = bitmap_glyph->bitmap;

        uint addx = charSize/2-bitmap.width/2;
        uint addy = (charSize-bitmap_glyph->top)-charHeight/2;

        this->char_rect[ch].x = x;
        this->char_rect[ch].y = y;

        ubyte* pixels = _bitmap.getPixels();
        for(int bity = 0; bity < bitmap.rows; bity++){
            int dsty = y+bity+addy;
            if(dsty > _bitmap.getHeight())
                    break;
            for(int bitx = 0; bitx < bitmap.width; bitx++){
                int dstx = x+bitx+addx;
                size_t biti = bitx + bity * bitmap.width;

                if(dstx > _bitmap.getWidth())
                    break;
                size_t pxi = (dstx + dsty * _bitmap.getPixelsWidth())*_bitmap.getBytes();

                if(bitmap.buffer[biti] > 0){
                    pixels[pxi] = _color.red;
                    pixels[pxi+1] = _color.blue;
                    pixels[pxi+2] = _color.green;
                    pixels[pxi+3] = std::min(bitmap.buffer[biti],_color.alpha);
                }else{
                    memset(pixels+pxi,0,sizeof(ubyte)*4);
                }
            }
        }
        x += charSize;
        if(x >= _bitmap.getWidth()){
            x = 0;
            y += charSize;
        }
        if(y >= _bitmap.getHeight())
            break;
    }

    FT_Done_Face(face);
}

TTFFont::TTFFont():
	filename(""),
	size(0),
	charsperwidth(0),
	charsperheight(0),
	alphaTolerance(defaultAlphaTolerance)
{}

TTFFont::TTFFont(std::string _filename,uint _size,const Color& _color,uint _charsperwidth,uint _charsperheight,bool usesystemdir):
	filename(""),
	size(0),
	charsperwidth(_charsperwidth),
	charsperheight(_charsperheight),
	alphaTolerance(TTFFont::defaultAlphaTolerance)
{
    this->loadFile(_filename,_size,_color,_charsperwidth,_charsperheight,usesystemdir);
}

std::ostream& operator<<(std::ostream &out,const TTFFont& obj){
    out << obj.filename;
    out << obj.size;
    out << obj.color;
    out << obj.bitmap;
    for(size_t i = 0;i < 256;++i)
        out << obj.char_rect[i];
    out << obj.charsperwidth;
    out << obj.charsperheight;
    out << obj.alphaTolerance;

    return out;
}
std::istream& operator>>(std::istream &in, TTFFont& obj){
    in >> obj.filename;
    in >> obj.size;
    in >> obj.color;
    in >> obj.bitmap;
    for(size_t i = 0;i < 256;++i)
        in >> obj.char_rect[i];
    in >> obj.charsperwidth;
    in >> obj.charsperheight;
    in >> obj.alphaTolerance;

    return in;
}

void TTFFont::loadFile(std::string _filename,uint _size,bool usesystemdir){
    this->loadFile(_filename,_size,TTFFont::defaultColor,TTFFont::defaultCharsperW,TTFFont::defaultCharsperH,usesystemdir);
}

void TTFFont::loadFile(std::string _filename ,uint _size,const Color& _color,uint _charsperwidth,uint _charsperheight,bool usesystemdir){
    this->filename = "";
	this->size = 0;

	std::string loadfilename = _filename;
    if(usesystemdir)
        loadfilename = TTFFont::defaultdir+_filename;

    try{
        this->open(this->bitmap,loadfilename.c_str(),_size,_color,_charsperwidth,_charsperheight);
        this->BuildFont(this->char_rect,256,this->bitmap,_charsperwidth,_charsperheight,this->alphaTolerance);
    }catch (LogError& err){
        throw err;
    }
    this->filename = _filename;
    this->size = _size;
    this->color = _color;
    this->charsperwidth = _charsperwidth;
	this->charsperheight = _charsperheight;
}

void TTFFont::loadBitmap(const Bitmap& bitmap,uint charsperwidth,uint charsperheight){
    this->charsperwidth = charsperwidth;
	this->charsperheight = charsperheight;
	this->bitmap = bitmap;
    this->BuildFont(this->char_rect,256,this->bitmap,charsperwidth,charsperheight,this->alphaTolerance);
}

void TTFFont::BuildFont(Rect* outarray,size_t outarraysize,
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
    size_t bitmapsize = bitmapfont.getPixelsSize();

	for (size_t i = 0;i < outarraysize && i < 256; ++i){
	    if (cy >= bitmapfont.getHeight())
			break;

        //|->|A | Determines the distance from start to the letter
        uint startx = cx;
	    uint starty = cy;
	    uint endx = cx+pcw;
	    uint endy = cy+pch;
        uint leftDestance = 0;
        while(startx <= endx){
            if(i == 0 || bytepp < 4)
                break;
            size_t alphai = bytepp*(startx + starty * bitmapfont.getPixelsWidth())+3;
            if(alphai >= bitmapsize) //out of range(pixel array)
                break;
            if(bitmap[alphai] >= alphatolerance) //found character
                break;

            starty++;
            if(starty >= endy){
                starty = cy;
                startx++;
                leftDestance++;
            }
        }

        uint endx2 = cx+pcw;
	    uint endy2 = cy+pch;
	    uint startx2 = cx;
	    uint starty2 = cy;
	    uint rightDestance = 0;
	    //| A|<-| Determines the distance from end to the letter
        while(endx2 >= startx2){
            if(i == 0 || bytepp < 4)
                break;
            size_t alphai = bytepp*(endx2 + endy2 * bitmapfont.getPixelsWidth())+3;
            if(alphai >= bitmapsize) //out of range(pixel array)
                break;
            if(bitmap[alphai] >= alphatolerance) //found character
                break;

            endy2--;
            if(endy2 <= starty2){
                endy2 = cy+pch;
                endx2--;
                rightDestance++;
            }
        }
        /*
        * (cx,cy)                                             (pcw,cy)
        *    |----------------------------------------------------|
        *    |           (startx,starty)(startx,endy)             |
        *    |--------|----------|-----------|-----------|--------|
        *    |        |first half|           |second half|        |
        *    |        |char      |   CHAR    |char       |        |
        *    |        |distance  |           |distance   |        |
        *    |---leftDestance----|-----------|----rightDestance---|
        *    |            (startx,endy) (endx,endy)               |
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

        uint chardistance = (charpw/10)+1;  //additional distance
        uint crw = static_cast<uint>(std::max<int>(0,(pcw-leftDestance-rightDestance) + chardistance));
		outarray[i].set(startx - static_cast<int>(chardistance/2),cy,crw,pch);
        biggestCharWidth = std::max<uint>(biggestCharWidth,crw);
        biggestCharHeight = std::max<uint>(biggestCharHeight,outarray[i].height);

		cx += pcw;
		if (cx >= bitmapfont.getWidth()){
			cx = 0;
			cy += pch;
		}
	}

	//set size of newline
	if(outarraysize > static_cast<size_t>('\n')){
        outarray[static_cast<size_t>('\n')].height = biggestCharHeight;
	}

    //set size of space
	if(outarraysize > static_cast<size_t>(' ')){
        outarray[static_cast<size_t>(' ')].width = static_cast<uint>(static_cast<float>(biggestCharWidth)/3.5f)+1;
        outarray[static_cast<size_t>(' ')].height = biggestCharHeight;
	}
}

uint TTFFont::getCharsperWidth() const {return this->charsperwidth;}
uint TTFFont::getCharsperHeight() const {return this->charsperheight;}

std::string TTFFont::getFilename() const {return this->filename;}
uint TTFFont::getSize() const {return this->size;}
Color TTFFont::getColor() const {return this->color;}
const Bitmap& TTFFont::getBitmap() const {return this->bitmap;}
Rect TTFFont::getCharSize(uint8 c) const {return this->char_rect[c];}
const Rect* TTFFont::getCharsSize() const {return this->char_rect;}
void TTFFont::copyBitmap(Bitmap& cbitmap) const {cbitmap = this->bitmap;}

};
