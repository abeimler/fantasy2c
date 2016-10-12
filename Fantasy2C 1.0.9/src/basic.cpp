#include "Basic.hpp"


#if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
    PFNGLCREATEPROGRAMOBJECTARBPROC     glCreateProgramObjectARB;
    PFNGLDELETEOBJECTARBPROC            glDeleteObjectARB;
    PFNGLCREATESHADEROBJECTARBPROC      glCreateShaderObjectARB;
    PFNGLSHADERSOURCEARBPROC            glShaderSourceARB;
    PFNGLCOMPILESHADERARBPROC           glCompileShaderARB;
    PFNGLGETOBJECTPARAMETERIVARBPROC    glGetObjectParameterivARB;
    PFNGLATTACHOBJECTARBPROC            glAttachObjectARB;
    PFNGLGETINFOLOGARBPROC              glGetInfoLogARB;
    PFNGLLINKPROGRAMARBPROC             glLinkProgramARB;
    PFNGLUSEPROGRAMOBJECTARBPROC        glUseProgramObjectARB;
    PFNGLGETUNIFORMLOCATIONARBPROC      glGetUniformLocationARB;
    PFNGLUNIFORM1FARBPROC               glUniform1fARB;
    PFNGLUNIFORM1IARBPROC               glUniform1iARB;

    PFNGLGENBUFFERSARBPROC glGenBuffersARB;
    PFNGLBINDBUFFERARBPROC glBindBufferARB;
    PFNGLBUFFERDATAARBPROC glBufferDataARB;
    PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;

    PFNGLMULTITEXCOORD1FARBPROC glMultiTexCoord1fARB;
    PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
    PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB;
    PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB;
    PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
    PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
#endif


/*
namespace F2C{

#if defined(__cplusplus)
extern "C" {
#endif

bool glExtensionSupported(const char *extName ){
     //
     // Search for extName in the extensions string.  Use of strstr()
     // is not sufficient because extension names can be prefixes of
     // other extension names.  Could use strtok() but the constant
     // string returned by glGetString can be in read-only memory.
     //
     if(extName == NULL)
        return false;

    char* list = (char *) glGetString(GL_EXTENSIONS);
    if(list == NULL)
        return false;

    const char* end = list + strlen(list);
    size_t extNameLen = strlen(extName);

    while (list < end || list != '\0'){
        size_t n = strcspn(list, " ");
        if ((extNameLen == n) && (strncmp(extName, list, n) == 0)){
            return true;
        }
        list += (n + 1);
    }
    return false;
}

#if defined(__cplusplus)
}
#endif

}
*/
