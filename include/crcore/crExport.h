#ifndef CRCORE_EXPORT
#define CRCORE_EXPORT 1

// define used to include in API which is being fazed out
// if you can compile your apps with this turned off you are
// well placed for compatablity with future versions.
#define USE_DEPRECATED_API

#if defined(WIN32) && !(defined(__CYGWIN__) || defined(__MINGW32__))
	#pragma warning( disable : 4244 )
	#pragma warning( disable : 4251 )
	#pragma warning( disable : 4267 )
	#pragma warning( disable : 4275 )
	#pragma warning( disable : 4290 )
	#pragma warning( disable : 4786 )
	#pragma warning( disable : 4305 )
	#pragma warning( disable : 4006 )
	#pragma warning( disable : 4312 )
	#pragma warning( disable : 4311 )
	#pragma warning( disable : 4018 )
    #pragma warning( disable : 4800 )
    #pragma warning( disable : 4996 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)

#  ifdef CR_LIBRARY
#    define CR_EXPORT   __declspec(dllexport)
#  else
#    define CR_EXPORT   __declspec(dllimport)
#  endif /* CR_LIBRARY */
#else
#  define CR_EXPORT
#endif  

// set up define for whether member templates are supported by VisualStudio compilers.
#ifdef _MSC_VER
# if (_MSC_VER >= 1300)
#  define __STL_MEMBER_TEMPLATES
# endif
#endif

/* Define NULL pointer value */

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

///define creature3d texture channels
//0��Basemap
//1��Normalmap
//2��Lightmap//��̬��shadowmap
//3��Shadowmap
//4��Envmap
//5��Emissivemap
//6��Specularmap//rgb��ʾspecular color,  a��ʾshiness
//7��Noisemap

#define TEXTURE_BASEMAP 0//��1����������ͼ
#define TEXTURE_BUMPMAP 2//��1�㷢����ͼ
#define TEXTURE_LIGHTMAP 1//3DMAX��Ӱ������ͼ
#define TEXTURE_SHADOWMAP 3//ʵʱ��Ӱ1
#define TEXTURE_SHADOWMAP2 13//ʵʱ��Ӱ2
#define TEXTURE_ENVMAP 1//������ͼCubeMap
#define TEXTURE_DIFFUSEMAP 5//��2����������ͼ
#define TEXTURE_SPECULARMAP 6//��1��߹���ͼ
#define TEXTURE_EMISSIVEMAP 7//��ѡͨ��1
//#define TEXTURE_NOISEMAP 1//

#define TEXTURE_NORMALMAP2 8//��2�㷢����ͼ
#define TEXTURE_DIFFUSEMAP2 9//��3����������ͼ
#define TEXTURE_SPECULARMAP2 10//��2��߹���ͼ
#define TEXTURE_EMISSIVEMAP2 11//��ѡͨ��2

#define TEXTURE_NORMALMAP3 12//������
//#define TEXTURE_DIFFUSEMAP3 13
#define TEXTURE_SPECULARMAP3 14//�߹���ͼ
#define TEXTURE_EMISSIVEMAP3 15//��ѡͨ��3

//#define TEXTURE_METALLICMAP 10
//#define TEXTURE_ROUGHNESSMAP 14

#define TEXTURE_UVSCRAMBLER 4//ExternTextureID
#define TEXTURE_COLORWEIGHT 4//ExternTextureID
#define TEXTURE_GIMAP 13
#define TEXTURE_SPOTLIGHTMAP 13//��Դ��ͼIES��
//#define TEXTURE_DETAILMAP 8
//#define TEXTURE_REFLECTMAP 9
//#define TEXTURE_REFRACTMAP 10
//
//#define TEXTURE_DETAILBUMPMAP 3

///define creature3d vertex attributes channels
//#define ATTRIBUTE_VERTEX 0
#define ATTRIBUTE_TANGENT 6   //tangent
#define ATTRIBUTE_BINORMAL 7 //binormal
//#define ATTRIBUTE_NORMAL 8 //normal

#endif
