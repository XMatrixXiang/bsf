//************************************ bs::framework - Copyright 2018 Marko Pintera **************************************//
//*********** Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed. ***********//
#pragma once

#include "BsCorePrerequisites.h"
#include "Reflection/BsRTTIType.h"
#include "Reflection/BsRTTIPlain.h"
#include "Image/BsSpriteTexture.h"

namespace bs
{
	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Engine
	 *  @{
	 */

	class BS_CORE_EXPORT SpriteTextureRTTI : public RTTIType<SpriteTexture, Resource, SpriteTextureRTTI>
	{
	private:
		BS_BEGIN_RTTI_MEMBERS
			BS_RTTI_MEMBER_REFL(mAtlasTexture, 0)
			BS_RTTI_MEMBER_PLAIN(mUVOffset, 1)
			BS_RTTI_MEMBER_PLAIN(mUVScale, 2)
			BS_RTTI_MEMBER_PLAIN(mAnimation, 3)
			BS_RTTI_MEMBER_PLAIN(mPlayback, 4)
		BS_END_RTTI_MEMBERS

	public:
		const String& getRTTIName() override
		{
			static String name = "SpriteTexture";
			return name;
		}

		UINT32 getRTTIId() override
		{
			return TID_SpriteTexture;
		}

		SPtr<IReflectable> newRTTIObject() override
		{
			return SpriteTexture::createEmpty();
		}

	private:
		void onDeserializationEnded(IReflectable* obj, SerializationContext* context) override
		{
			SpriteTexture* texture = static_cast<SpriteTexture*>(obj);
			texture->initialize();
		}
	};

	template<> struct RTTIPlainType<SpriteSheetGridAnimation>
	{	
		enum { id = TID_SpriteSheetGridAnimation }; enum { hasDynamicSize = 1 };

		static uint32_t toMemory(const SpriteSheetGridAnimation& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			static constexpr uint32_t VERSION = 0;

			return rtti_write_with_size_header(stream, [&data, &stream]()
			{
				uint32_t size = 0;
				size += rtti_write(VERSION, stream);
				size += rtti_write(data.numRows, stream);
				size += rtti_write(data.numColumns, stream);
				size += rtti_write(data.count, stream);
				size += rtti_write(data.fps, stream);

				return size;
			});
		}

		static uint32_t fromMemory(SpriteSheetGridAnimation& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			uint32_t size = 0;
			rtti_read(size, stream);

			uint32_t version = 0;
			rtti_read(version, stream);

			switch(version)
			{
			case 0:
			{
				rtti_read(data.numRows, stream);
				rtti_read(data.numColumns, stream);
				rtti_read(data.count, stream);
				rtti_read(data.fps, stream);
			}
				break;
			default:
				BS_LOG(Error, RTTI, "Unknown version. Unable to deserialize.");
				break;
			}

			return size;
		}

		static uint32_t getDynamicSize(const SpriteSheetGridAnimation& data)
		{
			uint32_t size = sizeof(uint32_t) * 2 + rtti_size(data.numRows) + rtti_size(data.numColumns) +
				rtti_size(data.count) + rtti_size(data.fps);
			return size;
		}	
	};

	/** @} */
	/** @endcond */
}
