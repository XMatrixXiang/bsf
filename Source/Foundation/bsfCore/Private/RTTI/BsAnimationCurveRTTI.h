//************************************ bs::framework - Copyright 2018 Marko Pintera **************************************//
//*********** Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed. ***********//
#pragma once

#include "BsCorePrerequisites.h"
#include "Reflection/BsRTTIType.h"
#include "RTTI/BsFlagsRTTI.h"
#include "RTTI/BsStdRTTI.h"
#include "Animation/BsAnimationCurve.h"

namespace bs
{
	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Core
	 *  @{
	 */

	template<class T> struct RTTIPlainType<TKeyframe<T>>
	{
		enum { id = TID_KeyFrame }; enum { hasDynamicSize = 0 };

		/** @copydoc RTTIPlainType::toMemory */
		static uint32_t toMemory(const TKeyframe<T>& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			rtti_write(data.value, stream);
			rtti_write(data.inTangent, stream);
			rtti_write(data.outTangent, stream);
			rtti_write(data.time, stream);

			return sizeof(TKeyframe<T>);
		}

		/** @copydoc RTTIPlainType::fromMemory */
		static uint32_t fromMemory(TKeyframe<T>& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			rtti_read(data.value, stream);
			rtti_read(data.inTangent, stream);
			rtti_read(data.outTangent, stream);
			rtti_read(data.time, stream);
			
			return sizeof(TKeyframe<T>);
		}

		/** @copydoc RTTIPlainType::getDynamicSize */
		static uint32_t getDynamicSize(const TKeyframe<T>& data)
		{
			assert(false);
			return sizeof(TKeyframe<T>);
		}
	};

	template<class T> struct RTTIPlainType<TAnimationCurve<T>>
	{
		enum { id = TID_AnimationCurve }; enum { hasDynamicSize = 1 };

		/** @copydoc RTTIPlainType::toMemory */
		static uint32_t toMemory(const TAnimationCurve<T>& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			return rtti_write_with_size_header(stream, [&data, &stream]()
			{
				constexpr uint32_t VERSION = 0; // In case the data structure changes

				uint32_t size = 0;
				size += rtti_write(VERSION, stream);
				size += rtti_write(data.mStart, stream);
				size += rtti_write(data.mEnd, stream);
				size += rtti_write(data.mLength, stream);
				size += rtti_write(data.mKeyframes, stream);

				return size;
			});
		}

		/** @copydoc RTTIPlainType::fromMemory */
		static uint32_t fromMemory(TAnimationCurve<T>& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			uint32_t size = 0;
			rtti_read(size, stream);

			uint32_t version;
			rtti_read(version, stream);

			rtti_read(data.mStart, stream);
			rtti_read(data.mEnd, stream);
			rtti_read(data.mLength, stream);
			rtti_read(data.mKeyframes, stream);

			return size;
		}

		/** @copydoc RTTIPlainType::getDynamicSize */
		static uint32_t getDynamicSize(const TAnimationCurve<T>& data)
		{
			uint64_t dataSize = sizeof(uint32_t) + sizeof(uint32_t);
			dataSize += rtti_size(data.mStart);
			dataSize += rtti_size(data.mEnd);
			dataSize += rtti_size(data.mLength);
			dataSize += rtti_size(data.mKeyframes);

			assert(dataSize <= std::numeric_limits<uint32_t>::max());

			return (uint32_t)dataSize;
		}
	};

	template<class T> struct RTTIPlainType<TNamedAnimationCurve<T>>
	{
		enum { id = TID_NamedAnimationCurve }; enum { hasDynamicSize = 1 };

		/** @copydoc RTTIPlainType::toMemory */
		static uint32_t toMemory(const TNamedAnimationCurve<T>& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			return rtti_write_with_size_header(stream, [&data, &stream]()
			{
				uint32_t size = 0;
				size += rtti_write(data.name, stream);
				size += rtti_write(data.flags, stream);
				size += rtti_write(data.curve, stream);

				return size;
			});
		}

		/** @copydoc RTTIPlainType::fromMemory */
		static uint32_t fromMemory(TNamedAnimationCurve<T>& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			UINT32 size = 0;
			rtti_read(size, stream);

			rtti_read(data.name, stream);
			rtti_read(data.flags, stream);
			rtti_read(data.curve, stream);

			return size;
		}

		/** @copydoc RTTIPlainType::getDynamicSize */
		static uint32_t getDynamicSize(const TNamedAnimationCurve<T>& data)
		{
			uint64_t dataSize = sizeof(uint32_t);
			dataSize += rtti_size(data.name);
			dataSize += rtti_size(data.flags);
			dataSize += rtti_size(data.curve);

			assert(dataSize <= std::numeric_limits<uint32_t>::max());

			return (uint32_t)dataSize;
		}
	};
	
	/** @} */
	/** @endcond */
}
