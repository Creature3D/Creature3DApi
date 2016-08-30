/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
* Copyright (C) 2003-2005 3Dlabs Inc. Ltd.
* Copyright (C) 2004-2005 Nathan Cournia
* Copyright (C) 2007 Art Tevs
* Copyright (C) 2008 Zebra Imaging
* Copyright (C) 2010 VIRES Simulationstechnologie GmbH
* Copyright (C) 2012 David Callu
*
* This application is open source and may be redistributed and/or modified
* freely and without restriction, both in commercial and non commercial
* applications, as long as this copyright notice is maintained.
*
* This application is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
#ifndef CRCORE_GL2EXTENSIONS_H
#define CRCORE_GL2EXTENSIONS_H 1

#include <CRCore/crExport.h>
#include <CRCore/Referenced.h>
#include <CRCore/ref_ptr.h>
#include <crgl/GL.h>

#include <string>

#ifndef GL_SAMPLER_2D_ARRAY_EXT
    #define GL_SAMPLER_1D_ARRAY_EXT           0x8DC0
    #define GL_SAMPLER_2D_ARRAY_EXT           0x8DC1
    #define GL_SAMPLER_1D_ARRAY_SHADOW_EXT    0x8DC3
    #define GL_SAMPLER_2D_ARRAY_SHADOW_EXT    0x8DC4
#endif

#ifndef GL_VERSION_2_0
#define GL_VERSION_2_0 1
typedef char GLchar;
#define GL_BLEND_EQUATION_RGB             GL_BLEND_EQUATION
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE       0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#define GL_CURRENT_VERTEX_ATTRIB          0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE      0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE        0x8643
#define GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_MAX_DRAW_BUFFERS               0x8824
#define GL_DRAW_BUFFER0                   0x8825
#define GL_DRAW_BUFFER1                   0x8826
#define GL_DRAW_BUFFER2                   0x8827
#define GL_DRAW_BUFFER3                   0x8828
#define GL_DRAW_BUFFER4                   0x8829
#define GL_DRAW_BUFFER5                   0x882A
#define GL_DRAW_BUFFER6                   0x882B
#define GL_DRAW_BUFFER7                   0x882C
#define GL_DRAW_BUFFER8                   0x882D
#define GL_DRAW_BUFFER9                   0x882E
#define GL_DRAW_BUFFER10                  0x882F
#define GL_DRAW_BUFFER11                  0x8830
#define GL_DRAW_BUFFER12                  0x8831
#define GL_DRAW_BUFFER13                  0x8832
#define GL_DRAW_BUFFER14                  0x8833
#define GL_DRAW_BUFFER15                  0x8834
#define GL_BLEND_EQUATION_ALPHA           0x883D
#define GL_POINT_SPRITE                   0x8861
#define GL_COORD_REPLACE                  0x8862
#define GL_MAX_VERTEX_ATTRIBS             0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_MAX_TEXTURE_COORDS             0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#define GL_MAX_VARYING_FLOATS             0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE                    0x8B4F
#define GL_FLOAT_VEC2                     0x8B50
#define GL_FLOAT_VEC3                     0x8B51
#define GL_FLOAT_VEC4                     0x8B52
#define GL_INT_VEC2                       0x8B53
#define GL_INT_VEC3                       0x8B54
#define GL_INT_VEC4                       0x8B55
#define GL_BOOL                           0x8B56
#define GL_BOOL_VEC2                      0x8B57
#define GL_BOOL_VEC3                      0x8B58
#define GL_BOOL_VEC4                      0x8B59
#define GL_FLOAT_MAT2                     0x8B5A
#define GL_FLOAT_MAT3                     0x8B5B
#define GL_FLOAT_MAT4                     0x8B5C
#define GL_SAMPLER_1D                     0x8B5D
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_3D                     0x8B5F
#define GL_SAMPLER_CUBE                   0x8B60
#define GL_SAMPLER_1D_SHADOW              0x8B61
#define GL_SAMPLER_2D_SHADOW              0x8B62
#define GL_DELETE_STATUS                  0x8B80
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ACTIVE_UNIFORMS                0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH      0x8B87
#define GL_SHADER_SOURCE_LENGTH           0x8B88
#define GL_ACTIVE_ATTRIBUTES              0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN      0x8CA0
#define GL_LOWER_LEFT                     0x8CA1
#define GL_UPPER_LEFT                     0x8CA2
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
#endif

#ifndef GL_VERSION_2_1
#define GL_VERSION_2_1 1
#define GL_CURRENT_RASTER_SECONDARY_COLOR 0x845F
#define GL_PIXEL_PACK_BUFFER              0x88EB
#define GL_PIXEL_UNPACK_BUFFER            0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING      0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING    0x88EF
#define GL_FLOAT_MAT2x3                   0x8B65
#define GL_FLOAT_MAT2x4                   0x8B66
#define GL_FLOAT_MAT3x2                   0x8B67
#define GL_FLOAT_MAT3x4                   0x8B68
#define GL_FLOAT_MAT4x2                   0x8B69
#define GL_FLOAT_MAT4x3                   0x8B6A
#define GL_SRGB                           0x8C40
#define GL_SRGB8                          0x8C41
#define GL_SRGB_ALPHA                     0x8C42
#define GL_SRGB8_ALPHA8                   0x8C43
#define GL_SLUMINANCE_ALPHA               0x8C44
#define GL_SLUMINANCE8_ALPHA8             0x8C45
#define GL_SLUMINANCE                     0x8C46
#define GL_SLUMINANCE8                    0x8C47
#define GL_COMPRESSED_SRGB                0x8C48
#define GL_COMPRESSED_SRGB_ALPHA          0x8C49
#define GL_COMPRESSED_SLUMINANCE          0x8C4A
#define GL_COMPRESSED_SLUMINANCE_ALPHA    0x8C4B
#endif

// EXT_geometry_shader4
#ifndef GL_GEOMETRY_SHADER_EXT
#define GL_GEOMETRY_SHADER_EXT                       0x8DD9
#define GL_GEOMETRY_VERTICES_OUT_EXT                 0x8DDA
#define GL_GEOMETRY_INPUT_TYPE_EXT                   0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_EXT                  0x8DDC
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT      0x8C29
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_EXT       0x8DDD
#define GL_MAX_VERTEX_VARYING_COMPONENTS_EXT         0x8DDE
#define GL_MAX_VARYING_COMPONENTS_EXT                0x8B4B
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT       0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT          0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT  0x8DE1
#define GL_LINES_ADJACENCY_EXT                       0x000A
#define GL_LINE_STRIP_ADJACENCY_EXT                  0x000B
#define GL_TRIANGLES_ADJACENCY_EXT                   0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY_EXT              0x000D
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT  0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_EXT    0x8DA9
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT        0x8DA7
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT  0x8CD4
#define GL_PROGRAM_POINT_SIZE_EXT                    0x8642
#endif

// EXT_gpu_shader4
#ifndef GL_INT_SAMPLER_2D_EXT
#define GL_SAMPLER_1D_ARRAY_EXT               0x8DC0
#define GL_SAMPLER_2D_ARRAY_EXT               0x8DC1
#define GL_SAMPLER_BUFFER_EXT                 0x8DC2
#define GL_SAMPLER_1D_ARRAY_SHADOW_EXT        0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW_EXT        0x8DC4
#define GL_SAMPLER_CUBE_SHADOW_EXT            0x8DC5
#define GL_UNSIGNED_INT_VEC2_EXT              0x8DC6
#define GL_UNSIGNED_INT_VEC3_EXT              0x8DC7
#define GL_UNSIGNED_INT_VEC4_EXT              0x8DC8
#define GL_INT_SAMPLER_1D_EXT                 0x8DC9
#define GL_INT_SAMPLER_2D_EXT                 0x8DCA
#define GL_INT_SAMPLER_3D_EXT                 0x8DCB
#define GL_INT_SAMPLER_CUBE_EXT               0x8DCC
#define GL_INT_SAMPLER_2D_RECT_EXT            0x8DCD
#define GL_INT_SAMPLER_1D_ARRAY_EXT           0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY_EXT           0x8DCF
#define GL_INT_SAMPLER_BUFFER_EXT             0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_1D_EXT        0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D_EXT        0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D_EXT        0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE_EXT      0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT_EXT   0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY_EXT  0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY_EXT  0x8DD7
#define GL_UNSIGNED_INT_SAMPLER_BUFFER_EXT    0x8DD8
#define GL_MIN_PROGRAM_TEXEL_OFFSET_EXT       0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET_EXT       0x8905
#endif


namespace CRCore {

class CR_EXPORT GL2Extensions : public CRCore::Referenced
{
    public:
        GL2Extensions(unsigned int contextID);
        GL2Extensions(const GL2Extensions& rhs);

        void lowestCommonDenominator(const GL2Extensions& rhs);

        void setupGL2Extensions(unsigned int contextID);

        /** Does the GL driver support OpenGL Shading Language? */
        bool isGlslSupported() const;

        float getGlVersion() const { return m_glVersion; }
        float getLanguageVersion() const { return m_glslLanguageVersion; }

        void setShaderObjectsSupported(bool flag) { m_isShaderObjectsSupported = flag; }
        bool isShaderObjectsSupported() const { return m_isShaderObjectsSupported; }

        void setVertexShaderSupported(bool flag) { m_isVertexShaderSupported = flag; }
        bool isVertexShaderSupported() const { return m_isVertexShaderSupported; }

        void setFragmentShaderSupported(bool flag) { m_isFragmentShaderSupported = flag; }
        bool isFragmentShaderSupported() const { return m_isFragmentShaderSupported; }

        void setLanguage100Supported(bool flag) { m_isLanguage100Supported = flag; }
        bool isLanguage100Supported() const { return m_isLanguage100Supported; }

        void setGeometryShader4Supported(bool flag) { m_isGeometryShader4Supported = flag; }
        bool isGeometryShader4Supported() const { return m_isGeometryShader4Supported; }

        void setGpuShader4Supported(bool flag) { m_isGpuShader4Supported = flag; }
        bool isGpuShader4Supported() const { return m_isGpuShader4Supported; }

        /** Function to call to get the extension of a specified context.
          * If the Exentsion object for that context has not yet been created then
          * and the 'createIfNotInitalized' flag been set to false then returns NULL.
          * If 'createIfNotInitalized' is true then the Extensions object is
          * automatically created.  However, in this case the extension object
          * only be created with the graphics context associated with ContextID..*/
        static GL2Extensions* Get(unsigned int contextID,bool createIfNotInitalized);

        /** allows users to override the extensions across graphics contexts.
          * typically used when you have different extensions supported across graphics pipes
          * but need to ensure that they all use the same low common denominator extensions.*/
        static void Set(unsigned int contextID, GL2Extensions* extensions);
        //static void Clear();
		static void clearExtensions();

        void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) const;
        void glDrawBuffers(GLsizei n, const GLenum *bufs) const;
        void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) const;
        void glStencilFuncSeparate(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask) const;
        void glStencilMaskSeparate(GLenum face, GLuint mask) const;
        void glAttachShader(GLuint program, GLuint shader) const;
        void glBindAttribLocation(GLuint program, GLuint index, const GLchar *name) const;
        void glCompileShader(GLuint shader) const;
        GLuint glCreateProgram(void) const;
        GLuint glCreateShader(GLenum type) const;
        void glDeleteProgram(GLuint program) const;
        void glDeleteShader(GLuint shader) const;
        void glDetachShader(GLuint program, GLuint shader) const;
        void glDisableVertexAttribArray(GLuint index) const;
        void glEnableVertexAttribArray(GLuint index) const;
        void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) const;
        void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) const;
        void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *obj) const;
        GLint glGetAttribLocation(GLuint program, const GLchar *name) const;
        void glGetProgramiv(GLuint program, GLenum pname, GLint *params) const;
        void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) const;
        void glGetShaderiv(GLuint shader, GLenum pname, GLint *params) const;
        void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) const;
        void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source) const;
        GLint glGetUniformLocation(GLuint program, const GLchar *name) const;
        void glGetUniformfv(GLuint program, GLint location, GLfloat *params) const;
        void glGetUniformiv(GLuint program, GLint location, GLint *params) const;
        void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params) const;
        void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params) const;
        void glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params) const;
        void glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid* *pointer) const;
        GLboolean glIsProgram(GLuint program) const;
        GLboolean glIsShader(GLuint shader) const;
        void glLinkProgram(GLuint program) const;
        void glShaderSource(GLuint shader, GLsizei count, const GLchar* *string, const GLint *length) const;
        void glUseProgram(GLuint program) const;
        void glUniform1f(GLint location, GLfloat v0) const;
        void glUniform2f(GLint location, GLfloat v0, GLfloat v1) const;
        void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) const;
        void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
        void glUniform1i(GLint location, GLint v0) const;
        void glUniform2i(GLint location, GLint v0, GLint v1) const;
        void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) const;
        void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) const;
        void glUniform1fv(GLint location, GLsizei count, const GLfloat *value) const;
        void glUniform2fv(GLint location, GLsizei count, const GLfloat *value) const;
        void glUniform3fv(GLint location, GLsizei count, const GLfloat *value) const;
        void glUniform4fv(GLint location, GLsizei count, const GLfloat *value) const;
        void glUniform1iv(GLint location, GLsizei count, const GLint *value) const;
        void glUniform2iv(GLint location, GLsizei count, const GLint *value) const;
        void glUniform3iv(GLint location, GLsizei count, const GLint *value) const;
        void glUniform4iv(GLint location, GLsizei count, const GLint *value) const;
        void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) const;
        void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) const;
        void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) const;
        void glValidateProgram(GLuint program) const;
        void glVertexAttrib1d(GLuint index, GLdouble x) const;
        void glVertexAttrib1dv(GLuint index, const GLdouble *v) const;
        void glVertexAttrib1f(GLuint index, GLfloat x) const;
        void glVertexAttrib1fv(GLuint index, const GLfloat *v) const;
        void glVertexAttrib1s(GLuint index, GLshort x) const;
        void glVertexAttrib1sv(GLuint index, const GLshort *v) const;
        void glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y) const;
        void glVertexAttrib2dv(GLuint index, const GLdouble *v) const;
        void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) const;
        void glVertexAttrib2fv(GLuint index, const GLfloat *v) const;
        void glVertexAttrib2s(GLuint index, GLshort x, GLshort y) const;
        void glVertexAttrib2sv(GLuint index, const GLshort *v) const;
        void glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) const;
        void glVertexAttrib3dv(GLuint index, const GLdouble *v) const;
        void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) const;
        void glVertexAttrib3fv(GLuint index, const GLfloat *v) const;
        void glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) const;
        void glVertexAttrib3sv(GLuint index, const GLshort *v) const;
        void glVertexAttrib4Nbv(GLuint index, const GLbyte *v) const;
        void glVertexAttrib4Niv(GLuint index, const GLint *v) const;
        void glVertexAttrib4Nsv(GLuint index, const GLshort *v) const;
        void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) const;
        void glVertexAttrib4Nubv(GLuint index, const GLubyte *v) const;
        void glVertexAttrib4Nuiv(GLuint index, const GLuint *v) const;
        void glVertexAttrib4Nusv(GLuint index, const GLushort *v) const;
        void glVertexAttrib4bv(GLuint index, const GLbyte *v) const;
        void glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) const;
        void glVertexAttrib4dv(GLuint index, const GLdouble *v) const;
        void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
        void glVertexAttrib4fv(GLuint index, const GLfloat *v) const;
        void glVertexAttrib4iv(GLuint index, const GLint *v) const;
        void glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) const;
        void glVertexAttrib4sv(GLuint index, const GLshort *v) const;
        void glVertexAttrib4ubv(GLuint index, const GLubyte *v) const;
        void glVertexAttrib4uiv(GLuint index, const GLuint *v) const;
        void glVertexAttrib4usv(GLuint index, const GLushort *v) const;
        void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) const;

        // C++-friendly convenience wrapper methods
        GLuint getCurrentProgram() const;
        bool getProgramInfoLog( GLuint program, std::string& result ) const;
        bool getShaderInfoLog( GLuint shader, std::string& result ) const;
        bool getAttribLocation( const char* attribName, GLuint& slot ) const;
        bool getFragDataLocation( const char* fragDataName, GLuint& slot) const;

        // GL 2.1
        void glUniformMatrix2x3fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value ) const;
        void glUniformMatrix3x2fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value ) const;
        void glUniformMatrix2x4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value ) const;
        void glUniformMatrix4x2fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value ) const;
        void glUniformMatrix3x4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value ) const;
        void glUniformMatrix4x3fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value ) const;

        // EXT_geometry_shader4
        void glProgramParameteri( GLuint program, GLenum pname, GLint value ) const;
        void glFramebufferTexture( GLenum target, GLenum attachment, GLuint texture, GLint level ) const;
        void glFramebufferTextureLayer( GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer ) const;
        void glFramebufferTextureFace( GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face ) const;

        // EXT_gpu_shader4
        void glGetUniformuiv( GLuint program, GLint location, GLuint *params ) const;
        void glBindFragDataLocation( GLuint program, GLuint color, const GLchar *name ) const;
        GLint glGetFragDataLocation( GLuint program, const GLchar *name ) const;
        void glUniform1ui( GLint location, GLuint v0 ) const;
        void glUniform2ui( GLint location, GLuint v0, GLuint v1 ) const;
        void glUniform3ui( GLint location, GLuint v0, GLuint v1, GLuint v2 ) const;
        void glUniform4ui( GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 ) const;
        void glUniform1uiv( GLint location, GLsizei count, const GLuint *value ) const;
        void glUniform2uiv( GLint location, GLsizei count, const GLuint *value ) const;
        void glUniform3uiv( GLint location, GLsizei count, const GLuint *value ) const;
        void glUniform4uiv( GLint location, GLsizei count, const GLuint *value ) const;

		//////////////////////////////
		void glDeleteBuffers(GLsizei n, const GLuint *buffers) const;
    protected:
        ~GL2Extensions() {}

        float m_glVersion;
        float m_glslLanguageVersion;

        bool m_isShaderObjectsSupported;
        bool m_isVertexShaderSupported;
        bool m_isFragmentShaderSupported;
        bool m_isLanguage100Supported;
        bool m_isGeometryShader4Supported;
        bool m_isGpuShader4Supported;
		static bool s_isShaderEnabled;

        void* m_glBlendEquationSeparate;
        void* m_glDrawBuffers;
        void* m_glStencilOpSeparate;
        void* m_glStencilFuncSeparate;
        void* m_glStencilMaskSeparate;
        void* m_glAttachShader;
        void* m_glBindAttribLocation;
        void* m_glCompileShader;
        void* m_glCreateProgram;
        void* m_glCreateShader;
        void* m_glDeleteProgram;
        void* m_glDeleteShader;
        void* m_glDetachShader;
        void* m_glDisableVertexAttribArray;
        void* m_glEnableVertexAttribArray;
        void* m_glGetActiveAttrib;
        void* m_glGetActiveUniform;
        void* m_glGetAttachedShaders;
        void* m_glGetAttribLocation;
        void* m_glGetProgramiv;
        void* m_glGetProgramInfoLog;
        void* m_glGetShaderiv;
        void* m_glGetShaderInfoLog;
        void* m_glGetShaderSource;
        void* m_glGetUniformLocation;
        void* m_glGetUniformfv;
        void* m_glGetUniformiv;
        void* m_glGetVertexAttribdv;
        void* m_glGetVertexAttribfv;
        void* m_glGetVertexAttribiv;
        void* m_glGetVertexAttribPointerv;
        void* m_glIsProgram;
        void* m_glIsShader;
        void* m_glLinkProgram;
        void* m_glShaderSource;
        void* m_glUseProgram;
        void* m_glUniform1f;
        void* m_glUniform2f;
        void* m_glUniform3f;
        void* m_glUniform4f;
        void* m_glUniform1i;
        void* m_glUniform2i;
        void* m_glUniform3i;
        void* m_glUniform4i;
        void* m_glUniform1fv;
        void* m_glUniform2fv;
        void* m_glUniform3fv;
        void* m_glUniform4fv;
        void* m_glUniform1iv;
        void* m_glUniform2iv;
        void* m_glUniform3iv;
        void* m_glUniform4iv;
        void* m_glUniformMatrix2fv;
        void* m_glUniformMatrix3fv;
        void* m_glUniformMatrix4fv;
        void* m_glValidateProgram;
        void* m_glVertexAttrib1d;
        void* m_glVertexAttrib1dv;
        void* m_glVertexAttrib1f;
        void* m_glVertexAttrib1fv;
        void* m_glVertexAttrib1s;
        void* m_glVertexAttrib1sv;
        void* m_glVertexAttrib2d;
        void* m_glVertexAttrib2dv;
        void* m_glVertexAttrib2f;
        void* m_glVertexAttrib2fv;
        void* m_glVertexAttrib2s;
        void* m_glVertexAttrib2sv;
        void* m_glVertexAttrib3d;
        void* m_glVertexAttrib3dv;
        void* m_glVertexAttrib3f;
        void* m_glVertexAttrib3fv;
        void* m_glVertexAttrib3s;
        void* m_glVertexAttrib3sv;
        void* m_glVertexAttrib4Nbv;
        void* m_glVertexAttrib4Niv;
        void* m_glVertexAttrib4Nsv;
        void* m_glVertexAttrib4Nub;
        void* m_glVertexAttrib4Nubv;
        void* m_glVertexAttrib4Nuiv;
        void* m_glVertexAttrib4Nusv;
        void* m_glVertexAttrib4bv;
        void* m_glVertexAttrib4d;
        void* m_glVertexAttrib4dv;
        void* m_glVertexAttrib4f;
        void* m_glVertexAttrib4fv;
        void* m_glVertexAttrib4iv;
        void* m_glVertexAttrib4s;
        void* m_glVertexAttrib4sv;
        void* m_glVertexAttrib4ubv;
        void* m_glVertexAttrib4uiv;
        void* m_glVertexAttrib4usv;
        void* m_glVertexAttribPointer;

        void* m_glGetInfoLogARB;
        void* m_glGetObjectParameterivARB;
        void* m_glDeleteObjectARB;
        void* m_glGetHandleARB;

        // GL 2.1
        void* m_glUniformMatrix2x3fv;
        void* m_glUniformMatrix3x2fv;
        void* m_glUniformMatrix2x4fv;
        void* m_glUniformMatrix4x2fv;
        void* m_glUniformMatrix3x4fv;
        void* m_glUniformMatrix4x3fv;

        // EXT_geometry_shader4
        void* m_glProgramParameteri;
        void* m_glFramebufferTexture;
        void* m_glFramebufferTextureLayer;
        void* m_glFramebufferTextureFace;

        // EXT_gpu_shader4
        void* m_glGetUniformuiv;
        void* m_glBindFragDataLocation;
        void* m_glGetFragDataLocation;
        void* m_glUniform1ui;
        void* m_glUniform2ui;
        void* m_glUniform3ui;
        void* m_glUniform4ui;
        void* m_glUniform1uiv;
        void* m_glUniform2uiv;
        void* m_glUniform3uiv;
        void* m_glUniform4uiv;
		///////////////////////////
		void* m_glDeleteBuffers;
};
}

#endif
