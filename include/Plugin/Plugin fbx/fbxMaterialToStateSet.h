#ifndef FBXMATERIALTOOSGSTATESET_H
#define FBXMATERIALTOOSGSTATESET_H

#include <map>
#include <memory>
#include <CRCore/crMaterial.h>
#include <CRCore/crStateSet.h>
#include <CRIOManager/crReaderWriter.h>
#include <CRCore/crTexture2D.h>

#if defined(_MSC_VER)
#pragma warning( disable : 4505 )
#pragma warning( default : 4996 )
#endif
#include <fbxsdk.h>

//The only things we need to create a new crStateSet are texture and materials. So we store that in a pair.
//We Don't store directly in stateSet because getOrCreateStateSet function set some parameters.

struct StateSetContent
{
    StateSetContent()
        : diffuseFactor(1.0),
        reflectionFactor(1.0),
        emissiveFactor(1.0)
    {
    }

    CRCore::ref_ptr<CRCore::crMaterial> material;

    // textures objects...
    CRCore::ref_ptr<CRCore::crTexture2D> diffuseTexture;
    CRCore::ref_ptr<CRCore::crTexture2D> opacityTexture;
    CRCore::ref_ptr<CRCore::crTexture2D> reflectionTexture;
    CRCore::ref_ptr<CRCore::crTexture2D> emissiveTexture;
    // more textures types here...

    // textures maps channels names...
    std::string diffuseChannel;
    std::string opacityChannel;
    std::string reflectionChannel;
    std::string emissiveChannel;
    // more channels names here...

    // combining factors...
    double diffuseFactor;
    double reflectionFactor;
    double emissiveFactor;
    // more combining factors here...

    double diffuseScaleU;
    double diffuseScaleV;
    double opacityScaleU;
    double opacityScaleV;
    double emissiveScaleU;
    double emissiveScaleV;

    // texture units (eventually used for each texture map)...
    enum TextureUnit
    {
        DIFFUSE_TEXTURE_UNIT = 0,
        OPACITY_TEXTURE_UNIT,
        REFLECTION_TEXTURE_UNIT,
        EMISSIVE_TEXTURE_UNIT
        // more texture units here...
    };
};

//We use the pointers set by the importer to not duplicate materials and textures.
typedef std::map<const FbxSurfaceMaterial *, StateSetContent> FbxMaterialMap;

//This map is used to not load the same image more than 1 time.
typedef std::map<std::string, CRCore::crTexture2D *> ImageMap;

class FbxMaterialToOsgStateSet
{
public:
    //Convert a FbxSurfaceMaterial to a osgMaterial and an osgTexture.
    StateSetContent convert(const FbxSurfaceMaterial* pFbxMat);

    //dir is the directory where fbx is stored (for relative path).
    FbxMaterialToOsgStateSet(const std::string& dir, const CRIOManager::Options* options, bool lightmapTextures) :
        _options(options),
        _dir(dir),
        _lightmapTextures(lightmapTextures){}

    void checkInvertTransparency();
private:
    //Convert a texture fbx to an CRCore texture.
    CRCore::ref_ptr<CRCore::crTexture2D>
    fbxTextureToOsgTexture(const FbxFileTexture* pOsgTex);
    FbxMaterialMap       _fbxMaterialMap;
    ImageMap              _imageMap;
    const CRIOManager::crReaderWriter::Options* _options;
    const std::string     _dir;
    bool                  _lightmapTextures;
};


#endif //FBXMATERIALTOOSGSTATESET_H
