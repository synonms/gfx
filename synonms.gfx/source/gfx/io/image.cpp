#include "image.h"

#include <FreeImage.h>

using namespace synonms::gfx::io;
using namespace synonms::gfx::api;

int GetOpenGlImageFormat(FREE_IMAGE_TYPE type, unsigned int bitsPerPixel)
{

    return 0;
}

Image::Image(const std::string& filePath)
{
    auto format = FreeImage_GetFileType(filePath.c_str(), 0);

    if (format == FIF_UNKNOWN) format = FreeImage_GetFIFFromFilename(filePath.c_str());

    if (format == FIF_UNKNOWN) 
    {
        auto message = "Unable to determine format of image " + filePath;
        throw new std::exception(message.c_str());
    }

    if (!FreeImage_FIFSupportsReading(format))
    {
        auto message = "Image format does not support reading - " + filePath;
        throw new std::exception(message.c_str());
    }

    _imageData = FreeImage_Load(format, filePath.c_str());
//    _imageData = FreeImage_ConvertTo32Bits(reinterpret_cast<FIBITMAP*>(tempImageData));
//    FreeImage_Unload(reinterpret_cast<FIBITMAP*>(tempImageData));

    if (_imageData == nullptr)
    {
        auto message = "Failed to load image " + filePath;
        throw new std::exception(message.c_str());
    }

    _imageType = FreeImage_GetImageType(reinterpret_cast<FIBITMAP*>(_imageData));
    _redMask = FreeImage_GetRedMask(reinterpret_cast<FIBITMAP*>(_imageData));
    _greenMask = FreeImage_GetGreenMask(reinterpret_cast<FIBITMAP*>(_imageData));
    _blueMask = FreeImage_GetBlueMask(reinterpret_cast<FIBITMAP*>(_imageData));

    _data = FreeImage_GetBits(reinterpret_cast<FIBITMAP*>(_imageData));
    _bitsPerPixel = FreeImage_GetBPP(reinterpret_cast<FIBITMAP*>(_imageData));
    _width = FreeImage_GetWidth(reinterpret_cast<FIBITMAP*>(_imageData));
    _height = FreeImage_GetHeight(reinterpret_cast<FIBITMAP*>(_imageData));

    if (_data == nullptr || _width == 0 || _height == 0)
    {
        auto message = "Image data or dimensions invalid after loading " + filePath;
        throw new std::exception(message.c_str());
    }

    // If true then format is BGR, otherwise RGB
    auto isLittleEndian = FreeImage_IsLittleEndian();

//	int iFormat = _bitsPerPixel == 24 ? GL_BGR : iBPP == 8 ? GL_LUMINANCE : 0;
//	int iInternalFormat = iBPP == 24 ? GL_RGB : GL_DEPTH_COMPONENT;

    //generate an OpenGL texture ID for this texture
//	glGenTextures(1, &gl_texID);
//	m_texID[texID] = gl_texID;
//	glBindTexture(GL_TEXTURE_2D, gl_texID);
//	glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height, border, image_format, GL_UNSIGNED_BYTE, bits);

    //Free FreeImage's copy of the data
}

Image::Image(Image&& other) noexcept
    : _imageData(std::exchange(other._imageData, nullptr))
    , _data(std::exchange(other._data, nullptr))
    , _width(std::exchange(other._width, 0))
    , _height(std::exchange(other._height, 0))
    , error(std::exchange(other.error, ""))
{
}

Image& Image::operator=(Image&& other) noexcept
{
    _imageData = std::exchange(other._imageData, nullptr);
    _data = std::exchange(other._data, nullptr);
    _width = std::exchange(other._width, 0);
    _height = std::exchange(other._height, 0);
    error = std::exchange(other.error, "");

    return *this;
}

Image::~Image()
{
    if (_imageData) {
        FreeImage_Unload(reinterpret_cast<FIBITMAP*>(_imageData));
    }
}

opengl::enumerators::DataType Image::GetDataType() const
{
    switch (GetTextureInternalFormat())
    {
    case opengl::enumerators::TextureInternalFormat::R8:
    case opengl::enumerators::TextureInternalFormat::R8UI:
    case opengl::enumerators::TextureInternalFormat::RGB8:
    case opengl::enumerators::TextureInternalFormat::RGB8UI:
    case opengl::enumerators::TextureInternalFormat::RGBA8:
    case opengl::enumerators::TextureInternalFormat::RGBA8UI:
        return opengl::enumerators::DataType::UnsignedByte;

    case opengl::enumerators::TextureInternalFormat::R16UI:
    case opengl::enumerators::TextureInternalFormat::RGB16UI:
    case opengl::enumerators::TextureInternalFormat::RGBA16UI:
        return opengl::enumerators::DataType::UnsignedShort;

    case opengl::enumerators::TextureInternalFormat::R32UI:
        return opengl::enumerators::DataType::UnsignedInt;

    case opengl::enumerators::TextureInternalFormat::R16I:
        return opengl::enumerators::DataType::Short;

    case opengl::enumerators::TextureInternalFormat::R32I:
        return opengl::enumerators::DataType::Int;

    case opengl::enumerators::TextureInternalFormat::R32F:
    case opengl::enumerators::TextureInternalFormat::RGB32F:
    case opengl::enumerators::TextureInternalFormat::RGBA32F:
        return opengl::enumerators::DataType::Float;

    case opengl::enumerators::TextureInternalFormat::RGB5_A1:
        return opengl::enumerators::DataType::UnsignedShort_5_5_5_1;

    case opengl::enumerators::TextureInternalFormat::RGB565:
        return opengl::enumerators::DataType::UnsignedShort_5_6_5;

    default:
        throw std::exception("Data Type is not supported for image.");
        break;
    }
}

opengl::enumerators::TextureFormat Image::GetTextureFormat() const
{
    switch (GetTextureInternalFormat())
    {
    case opengl::enumerators::TextureInternalFormat::R8:
    case opengl::enumerators::TextureInternalFormat::R8UI:
    case opengl::enumerators::TextureInternalFormat::R16I:
    case opengl::enumerators::TextureInternalFormat::R16UI:
    case opengl::enumerators::TextureInternalFormat::R32F:
    case opengl::enumerators::TextureInternalFormat::R32I:
    case opengl::enumerators::TextureInternalFormat::R32UI:
        return opengl::enumerators::TextureFormat::Red;

    case opengl::enumerators::TextureInternalFormat::RGB8:
    case opengl::enumerators::TextureInternalFormat::RGB5_A1:
    case opengl::enumerators::TextureInternalFormat::RGB565:
    case opengl::enumerators::TextureInternalFormat::RGB8UI:
    case opengl::enumerators::TextureInternalFormat::RGB16UI:
    case opengl::enumerators::TextureInternalFormat::RGB32F:
        if (FreeImage_IsLittleEndian() > 0)
            return opengl::enumerators::TextureFormat::BGR;
        return opengl::enumerators::TextureFormat::RGB;

    case opengl::enumerators::TextureInternalFormat::RGBA8:
    case opengl::enumerators::TextureInternalFormat::RGBA8UI:
    case opengl::enumerators::TextureInternalFormat::RGBA16UI:
    case opengl::enumerators::TextureInternalFormat::RGBA32F:
        if (FreeImage_IsLittleEndian() > 0)
            return opengl::enumerators::TextureFormat::BGRA;
        return opengl::enumerators::TextureFormat::RGBA;

    default:
        throw std::exception("Texture Format is not supported for image.");
        break;
    }
}

opengl::enumerators::TextureInternalFormat Image::GetTextureInternalFormat() const
{
    switch (_imageType)
    {
    case FIT_BITMAP:
        switch (_bitsPerPixel)
        {
        case 8u: 
            return opengl::enumerators::TextureInternalFormat::R8;
        case 16u:
            if (_redMask == FI16_555_RED_MASK && _greenMask == FI16_555_GREEN_MASK && _blueMask == FI16_555_BLUE_MASK)
            {
                return opengl::enumerators::TextureInternalFormat::RGB5_A1;
            }
            else if (_redMask == FI16_565_RED_MASK && _greenMask == FI16_565_GREEN_MASK && _blueMask == FI16_565_BLUE_MASK)
            {
                return opengl::enumerators::TextureInternalFormat::RGB565;
            }
            else
            {
                return opengl::enumerators::TextureInternalFormat::R16UI;
            }
            break;
        case 24u: 
            return opengl::enumerators::TextureInternalFormat::RGB8;
        case 32u: 
            return opengl::enumerators::TextureInternalFormat::RGBA8;
        default:
            throw std::exception("Color depth for FIT_BITMAP is not supported for image.");
            break;
        };
        break;
    case FIT_FLOAT: 
        return opengl::enumerators::TextureInternalFormat::R32F;
    case FIT_INT16: 
        return opengl::enumerators::TextureInternalFormat::R16I;
    case FIT_INT32: 
        return opengl::enumerators::TextureInternalFormat::R32I;
    case FIT_RGB16: 
        return opengl::enumerators::TextureInternalFormat::RGB16UI;
    case FIT_RGBA16: 
        return opengl::enumerators::TextureInternalFormat::RGBA16UI;
    case FIT_RGBAF: 
        return opengl::enumerators::TextureInternalFormat::RGBA32F;
    case FIT_RGBF: 
        return opengl::enumerators::TextureInternalFormat::RGB32F;
    case FIT_UINT16: 
        return opengl::enumerators::TextureInternalFormat::R16UI;
    case FIT_UINT32: 
        return opengl::enumerators::TextureInternalFormat::R32UI;
    case FIT_COMPLEX:
    case FIT_DOUBLE:
    case FIT_UNKNOWN:
    default:
        throw std::exception("Texture Internal Format is not supported for image.");
        break;
    };
}
