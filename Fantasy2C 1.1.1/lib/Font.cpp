#include <Fantasy2C/Font.hpp>

namespace F2C{

#if defined(_WIN32) || defined(_Windows) || defined(__WIN32__)
    std::string TTFFont::defaultdir = "C:/WINDOWS/Fonts/";
    std::string TTFFont::defaultName = "Arial.ttf";
#elif defined(__X11__) || defined(__linux)
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

TTFFont::TTFLibrary::TTFLibrary(){
    if (FT_Init_FreeType(&library_) != 0){
        LogError error;
		error.setError("Could not initialize FreeType2 library.\n");
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
		buffer << "No such file or directory: " << _filename.c_str() << '\n';
		error.setError(buffer.str());
		throw error;
	}

    if(FT_New_Face(TTFFont::library.getLibrary(), _filename.c_str(), 0, &face) != 0){
		std::ostringstream buffer;
		LogError error;
		buffer << "Could not load font file: " << _filename.c_str() << '\n';
		error.setError(buffer.str());
		throw error;
    }

    if(!(face->face_flags & FT_FACE_FLAG_SCALABLE) ||
        !(face->face_flags & FT_FACE_FLAG_HORIZONTAL)){
			std::ostringstream buffer;
			LogError error;
			buffer << "Invalid font: Error setting font size: " << _filename.c_str() << '\n';
			error.setError(buffer.str());
			throw error;
    }

    FT_Set_Char_Size( face, _size << 6, _size << 6, 0, 0);

    uint charSize = 0;
    uint charWidth = 0;
    uint charHeight = 0;
    uint charTop = 0;
    uint charIndex = 0;

    for(size_t ch = 0; ch < this->widths.size(); ++ch){
        charIndex = FT_Get_Char_Index(face, ch);

        FT_Load_Glyph(face, charIndex, FT_LOAD_DEFAULT);
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

        FT_Glyph glyph;
        FT_Get_Glyph( face->glyph, &glyph );

        FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
        FT_Bitmap& bitmap = bitmap_glyph->bitmap;

        this->widths[ch] = bitmap.width;
        this->heights[ch] = bitmap.rows;
        charHeight = std::max<uint>(this->heights[ch],charHeight);
        charTop = std::max<uint>(bitmap_glyph->top,charTop);
        charWidth = std::max<uint>(this->widths[ch],charWidth);
    }
    charSize = std::max<uint>(charHeight+static_cast<uint>(charHeight*0.75f),charWidth);

    _bitmap.newBitmap(charSize*_charsperwidth,charSize*_charsperheight);

    uint x = 0;
    uint y = 0;

    for(uint ch = 0; ch < this->widths.size(); ++ch){
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

        ubyte* pixels = _bitmap.getPixels();
        for(int j = 0; j < bitmap.rows; ++j){
            if(y+j+addy > _bitmap.getHeight())
                    break;
            for(int i = 0; i < bitmap.width; ++i){
                if(x+i+addx > _bitmap.getWidth())
                    break;
                if(bitmap.buffer[i + j * bitmap.width] > 0){
                    uint pxi = (_bitmap.getBits()/8) *
                                ((x+i+addx) +
                                ((y+j+addy) * _bitmap.getPixelsWidth()));
                    if(bitmap.buffer[i + j * bitmap.width] > 0){
                        pixels[pxi] = _color.red;
                        pixels[pxi+1] = _color.blue;
                        pixels[pxi+2] = _color.green;
                    }else{
                        pixels[pxi] = 0;
                        pixels[pxi+1] = 0;
                        pixels[pxi+2] = 0;
                    }
                    pixels[pxi+3] = std::min<ubyte>(_color.alpha,bitmap.buffer[i + j * bitmap.width]);
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
	heights(256),
	widths(256)
{}

TTFFont::TTFFont(std::string _filename,uint _size,const Color& _color,uint _charsperwidth,uint _charsperheight,bool usesystemdir):
	filename(""),
	size(0),
	heights(256),
	widths(256)
{
    this->loadFile(_filename,_size,_color,_charsperwidth,_charsperheight,usesystemdir);
}

void TTFFont::loadFile(bool usesystemdir,std::string _filename,uint _size){
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
    }catch (LogError& err){
        throw err;
    }
    this->filename = _filename;
    this->size = _size;
    this->color = _color;
}

std::string TTFFont::getFilename() const {return this->filename;}
uint TTFFont::getSize() const {return this->size;}
Color TTFFont::getColor() const {return this->color;}
const Bitmap& TTFFont::getBitmap() const {return this->bitmap;}
Rect TTFFont::getCharSize(uint8 c) const {return Rect (0,0,this->widths[c],this->heights[c]);}
void TTFFont::copyBitmap(Bitmap& cbitmap) const {cbitmap = this->bitmap;}

};
