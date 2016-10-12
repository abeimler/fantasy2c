#include <Fantasy2C/RenderManager.hpp>

namespace F2C{

void RenderManager::enable2DTexture(bool enable){
    if(enable)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
}


void RenderManager::bindTexture(GLuint texture){
    int active_texture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D,&active_texture);
    if(static_cast<uint>(active_texture) != texture){
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

void RenderManager::enableScissor(bool enable){
    if(enable)
        glEnable(GL_SCISSOR_TEST);
    else
        glDisable(GL_SCISSOR_TEST);
}

void RenderManager::enableStencil(bool enable){
    if(enable)
        glEnable(GL_STENCIL_TEST);
    else
        glDisable(GL_STENCIL_TEST);
}

void RenderManager::startStencil(){
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS,1,1);
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE );
}

void RenderManager::clearStencil(){
    glClear(GL_STENCIL_BUFFER_BIT);
}

void RenderManager::endStencil(){
    glStencilFunc(GL_GEQUAL, 1, 1);
    glStencilOp(GL_KEEP,GL_KEEP, GL_KEEP);
}

void RenderManager::setTexParam(TexParam::Tex_Param param){
    if(param == TexParam::Nearest){
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    }else if(param == TexParam::Linear){
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


void RenderManager::setBlendFunc(BlendType::Blend_Type type){
    if(type == BlendType::additives)
        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    else if(type == BlendType::normal)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    else if(type == BlendType::multiplicative)
        glBlendFunc(GL_DST_COLOR,GL_ZERO);
    else if(type == BlendType::light)
        glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR);
    else if(type == BlendType::mask)
        glBlendFunc(GL_DST_COLOR,GL_ZERO);
}


void RenderManager::setCoord(GLdouble x,GLdouble y,GLdouble z,
                                GLuint width,GLuint height,
                                GLdouble angle_x,GLdouble angle_y,GLdouble angle_z,
                                GLdouble zoom_x,GLdouble zoom_y){
    glLoadIdentity();
    //move to x,y and z Coord.
    //move to middle
    glTranslated(x + width/2.0f,
                  y + height/2.0f,
                  z);
    //rotate in middle
    glRotated(angle_x,1.0f,0.0f,0.0f);
    glRotated(angle_y,0.0f,1.0f,0.0f);
    glRotated(angle_z,0.0f,0.0f,1.0f);
    //move back
    glTranslated(width/-2.0f,
                  height/-2.0f,
                  0.0f);
    if(zoom_x != 0.0f && zoom_y != 0.0f)
        glScaled(zoom_x,zoom_y,1.0f);
}


void RenderManager::getTexCoordArray8(GLdouble* texcoords,GLdouble tcx,
                                        GLdouble tcy,GLdouble tcwidth,GLdouble tcheight,
                                        GLdouble texturewidth,GLdouble textureheight){

    //set texcoord of Texture
    //texcoord: top
    GLdouble cx = tcx/texturewidth;

    //texcoord: left
    GLdouble cy = tcy/texturewidth;

    //texcoord: right
    GLdouble cwidth = (tcx+tcwidth)/texturewidth;

    //texcoord: bottom
    GLdouble cheight = (tcy+tcheight)/texturewidth;

    cx = (cx > cwidth)? cwidth : cx;
    cy = (cy > cheight)? cheight : cy;

    *texcoords = cx;
    *(texcoords+1) = cy;

    *(texcoords+2) = cwidth;
    *(texcoords+3) = cy;

    *(texcoords+4) = cwidth;
    *(texcoords+5) = cheight;

    *(texcoords+6) = cx;
    *(texcoords+7) = cheight;
}

void RenderManager::getTexCoordArray8(GLdouble* texcoords,Rect coord,
                                        GLdouble texturewidth,GLdouble textureheight){
    RenderManager::getTexCoordArray8(texcoords,coord.x,coord.y,coord.width,coord.height,texturewidth,textureheight);
}


void RenderManager::getVerticesArray8(GLdouble* vertices,GLdouble x,GLdouble y,GLdouble width,GLdouble height){
    *vertices = x;
    *(vertices+1) = y;

    *(vertices+2) = x+width;
    *(vertices+3) = y;

    *(vertices+4) = x+width;
    *(vertices+5) = y+height;

    *(vertices+6) = x;
    *(vertices+7) = y+height;
}


void RenderManager::getVerticesArray8(GLdouble* vertices,Rect vertex){
    RenderManager::getVerticesArray8(vertices,vertex.x,vertex.y,vertex.width,vertex.height);
}


void RenderManager::getVerticesArray12(GLdouble* vertices,GLdouble x,GLdouble y,GLdouble z,GLdouble width,GLdouble height){
    *vertices = x;
    *(vertices+1) = y;
    *(vertices+2) = z;

    *(vertices+3) = x+width;
    *(vertices+4) = y;
    *(vertices+5) = z;

    *(vertices+6) = x+width;
    *(vertices+7) = y+height;
    *(vertices+8) = z;

    *(vertices+9) = x;
    *(vertices+10) = y+height;
    *(vertices+11) = z;
}


void RenderManager::flippedHTexCoord8(GLdouble* texcoords){
    std::swap(*texcoords    ,*(texcoords+2));
    std::swap(*(texcoords+4),*(texcoords+6));
}


void RenderManager::flippedVTexCoord8(GLdouble* texcoords){
    std::swap(*(texcoords+1),*(texcoords+7));
    std::swap(*(texcoords+3),*(texcoords+5));
}


void RenderManager::getColorArray3(GLubyte* colors,const Color* srccolors,size_t colorsize,size_t srccolorsize){
    size_t j = 0;
    for(size_t i = 0;i < colorsize*4;i+=4){
        *(colors+(i)) = (srccolors+j)->red;
        *(colors+(i+1)) = (srccolors+j)->green;
        *(colors+(i+2)) = (srccolors+j)->blue;

        j++;
        if(j >= srccolorsize)
            j = 0;
    }
}


void RenderManager::getColorArray4(GLubyte* colors,const Color* srccolors,size_t colorsize,size_t srccolorsize){
    size_t j = 0;
    for(size_t i = 0;i < colorsize*4;i+=4){
        *(colors+(i)) = (srccolors+j)->red;
        *(colors+(i+1)) = (srccolors+j)->green;
        *(colors+(i+2)) = (srccolors+j)->blue;
        *(colors+(i+3)) = (srccolors+j)->alpha;

        j++;
        if(j >= srccolorsize)
            j = 0;
    }
}

void RenderManager::getColorArrayQuad3(GLubyte* colors,const Color* srccolors,size_t quadnumbers,size_t srccolorsize){
    size_t j = 0;

    //quadnumbers*3*4 = quadnumbers * RGB * 4(for Quad (4 Vertices))
    for(size_t i = 0;i < quadnumbers*12;i+=3){
        *(colors+i) = (srccolors+j)->red;
        *(colors+(i+1)) = (srccolors+j)->green;
        *(colors+(i+2)) = (srccolors+j)->blue;

        j++;
        if(j >= srccolorsize)
            j = 0;
    }
}

void RenderManager::getColorArrayQuad4(GLubyte* colors,const Color* srccolors,size_t quadnumbers,size_t srccolorsize){
    size_t j = 0;

    //quadnumbers*4*4 = quadnumbers * RGBA * 4(for Quad (4 Vertices))
    for(size_t i = 0;i < quadnumbers*16;i+=4){
        *(colors+i) = (srccolors+j)->red;
        *(colors+(i+1)) = (srccolors+j)->green;
        *(colors+(i+2)) = (srccolors+j)->blue;
        *(colors+(i+3)) = (srccolors+j)->alpha;

        j++;
        if(j >= srccolorsize)
            j = 0;
    }
}

void RenderManager::setScissorInTopLeftMode(GLint x,GLint y,GLuint width,GLuint height){
    GLint viewport[4] = {0};
    glGetIntegerv(GL_VIEWPORT, viewport);

//    GLint clippedLeft = x;
//    GLint clippedTop = y;
//    GLint clippedRight = x+width;
    GLint clippedBottom = y+height;

    // translate from top left to bottom left coordinate system
    glScissor(x, viewport[3] - clippedBottom, width, height);
}

bool RenderManager::isInViewportRange(GLint x,GLint y,GLuint width,GLuint height){
    GLint viewport[4] = {0};
    glGetIntegerv(GL_VIEWPORT, viewport);

    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1 = x;
    left2 = viewport[0];
    right1 = x + width;
    right2 = viewport[0] + viewport[2];
    top1 = y;
    top2 = viewport[1];
    bottom1 = y + height;
    bottom2 = viewport[1] + viewport[3];

    if(bottom1 < top2) return false;
	if(top1 > bottom2) return false;
	if(right1 < left2) return false;
	if(left1 > right2) return false;

	return true;
}

void RenderManager::setScissorInTopLeftMode(Rect rect){
    RenderManager::setScissorInTopLeftMode(rect.x,rect.y,rect.width,rect.height);
}

bool RenderManager::isInViewportRange(Rect rect){
    return RenderManager::isInViewportRange(rect.x,rect.y,rect.width,rect.height);
}

bool RenderManager::iscollisionRect(GLint x1,GLint y1,GLuint width1,GLuint height1,
                                        GLint x2,GLint y2,GLuint width2,GLuint height2){
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1 = x1;
    left2 = x2;
    right1 = x1 + static_cast<int>(width1);
    right2 = x2 + static_cast<int>(width2);
    top1 = y1;
    top2 = y2;
    bottom1 = y1 + static_cast<int>(height1);
    bottom2 = y2 + static_cast<int>(height2);

    if(bottom1 < top2) return false;
	if(top1 > bottom2) return false;
	if(right1 < left2) return false;
	if(left1 > right2) return false;

	return true;
}

bool RenderManager::iscollisionRect(Rect rect1,Rect rect2){
    return RenderManager::iscollisionRect(rect1.x,rect1.y,rect1.width,rect1.height,rect2.x,rect2.y,rect2.width,rect2.height);
}

void RenderManager::renderingQuad(GLdouble* texcoords,GLdouble* vertices,GLubyte* colors,
                                    GLint tcsize,GLint vexsize,GLint colsize,
                                    GLuint numbersofquads,bool usedrawarray){

    if(numbersofquads < 1)
        return;
    if(!texcoords && !vertices && !colors)
        return;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    if(numbersofquads < 2){
        bool allcolorsequal = false;
        for(size_t i = 1;i < colsize*numbersofquads*4;i+=colsize){
            allcolorsequal = *(colors+i) == *(colors+i-1);
        }
        if(allcolorsequal)
            glShadeModel(GL_FLAT);
        else
            glShadeModel(GL_SMOOTH);
    }else
        glShadeModel(GL_SMOOTH);

    if(usedrawarray && numbersofquads > 1){
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        if(texcoords)
            glTexCoordPointer(tcsize, GL_DOUBLE, 0, texcoords);
        if(vertices)
            glVertexPointer(vexsize, GL_DOUBLE, 0, vertices);
        if(colors)
            glColorPointer(colsize,GL_UNSIGNED_BYTE, 0, colors);

        glDrawArrays(GL_QUADS, 0, numbersofquads*4);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }else{
        size_t i = 0;
        size_t j = 0;
        size_t k = 0;
        glBegin(GL_QUADS);
        for(;i < tcsize*numbersofquads*4 || j < vexsize*numbersofquads*4 || k < colsize*numbersofquads*4;
            i+=tcsize,j+=vexsize,k+=colsize){
                if(colors){
                    switch(colsize){
                        case 3:
                            glColor3ubv(colors+k);
                        break;
                        case 4:
                            glColor4ubv(colors+k);
                        break;
                    }
                }
                if(texcoords){
                    switch(tcsize){
                        case 1:
                            glTexCoord1dv(texcoords+i);
                        break;
                        case 2:
                            glTexCoord2dv(texcoords+i);
                        break;
                        case 3:
                            glTexCoord3dv(texcoords+i);
                        break;
                        case 4:
                            glTexCoord4dv(texcoords+i);
                        break;
                    }
                }
                if(vertices){
                    switch(vexsize){
                        case 2:
                            glVertex2dv(vertices+j);
                        break;
                        case 3:
                            glVertex3dv(vertices+j);
                        break;
                        case 4:
                            glVertex4dv(vertices+j);
                        break;
                    }
                }
        }
        glEnd();
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
}

}
