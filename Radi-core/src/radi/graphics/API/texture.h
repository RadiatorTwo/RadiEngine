#pragma once

#include "radi/radi_types.h"
#include "radi/radi_string.h"

namespace radi {
	namespace graphics {
		namespace API {

			enum class RD_API TextureWrap
			{
				NONE = 0,
				REPEAT,
				CLAMP,
				MIRRORED_REPEAT,
				CLAMP_TO_EDGE,
				CLAMP_TO_BORDER
			};

			enum class RD_API TextureFilter
			{
				NONE = 0,
				LINEAR,
				NEAREST
			};

			enum class RD_API TextureFormat
			{
				NONE = 0,
				RGB,
				RGBA,
				LUMINANCE,
				LUMINANCE_ALPHA
			};

			struct RD_API TextureParameters
			{
				TextureFormat format;
				TextureFilter filter;
				TextureWrap wrap;

				TextureParameters()
				{
					format = TextureFormat::RGBA;
					filter = TextureFilter::LINEAR;
					wrap = TextureWrap::CLAMP;
				}

				TextureParameters(TextureFormat format, TextureFilter filter, TextureWrap wrap)
					: format(format), filter(filter), wrap(wrap)
				{
				}

				TextureParameters(TextureFilter filter)
					: format(TextureFormat::RGBA), filter(filter), wrap(TextureWrap::CLAMP)
				{
				}

				TextureParameters(TextureFilter filter, TextureWrap wrap)
					: format(TextureFormat::RGBA), filter(filter), wrap(wrap)
				{
				}
			};

			struct RD_API TextureLoadOptions
			{
				bool flipX;
				bool flipY;

				TextureLoadOptions()
				{
					flipX = false;
					flipY = false;
				}

				TextureLoadOptions(bool flipX, bool flipY)
					: flipX(flipX), flipY(flipY)
				{
				}
			};

			class RD_API Texture
			{
			protected:
				static TextureWrap s_WrapMode;
				static TextureFilter s_FilterMode;
			public:
				virtual ~Texture() {}

				virtual void Bind(uint slot = 0) const = 0;
				virtual void Unbind(uint slot = 0) const = 0;

				virtual const String& GetName() const = 0;
				virtual const String& GetFilepath() const = 0;
			public:
				inline static void SetWrap(TextureWrap mode) { s_WrapMode = mode; }
				inline static void SetFilter(TextureFilter mode) { s_FilterMode = mode; }
			public:
				static byte GetStrideFromFormat(TextureFormat format);
			};

		}
	}
}