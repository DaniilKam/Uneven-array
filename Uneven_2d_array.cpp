#include "Uneven_2d_array.h"
#include <stdlib.h>

uint8_t UneArray::Init(uint32_t Layers)
{
	#ifndef _FASTMODE_
	if (init == true)
		return 1;
	#endif

	Layers_count = Layers;
	Layers_size = (uint32_t*)malloc(Layers * 4);
	Shift = (uint32_t*)malloc(Layers * 4);
	init = true;

	for (uint32_t i = 0; i < Layers; i++)
	{
		Layers_size[i] = 1;
		Shift[i] = 0;
	}

	return 0;
}

uint8_t UneArray::setLayerSize(uint32_t Layer, uint32_t Size)
{
	#ifndef _FASTMODE_
	if (init != true)
		return 1;

	if (build == true)
		return 2;

	if (Layer >= Layers_count)
		return 3;
	#endif

	Layers_size[Layer] = Size;

	return 0;
}

uint8_t UneArray::setLayerSize(uint32_t Sizes[])
{
	#ifndef _FASTMODE_
	if (init != true)
		return 1;

	if (build == true)
		return 2;
	#endif

	for (uint32_t i = 0; i < Layers_count; i++)
	{
		Layers_size[i] = Sizes[i];
	}

	return 0;
}

uint8_t UneArray::Create()
{
	#ifndef _FASTMODE_
	if (init != true)
		return 1;

	if (build == true)
		return 2;
	#endif
	
	uint32_t Array_size = 0;
	for (uint32_t i = 0; i < Layers_count; i++)
	{
		Array_size += Layers_size[i];
		for (uint32_t i2 = 0; i2 < i; i2++)
		{
			Shift[i] += Layers_size[i2];
		}
	}

	Size = Array_size * sizeof(TypeVar);

	Array = (TypeVar*)malloc(Size);

	build = true;

	return 0;
}

uint8_t UneArray::wr(uint32_t Layer, uint32_t pos, TypeVar val)
{
	#ifndef _FASTMODE_
	if(build!= true)
		return 1;

	if (Layer >= Layers_count)
		return 2;

	if (pos >= Layers_size[Layer])
		return 3;
	#endif

	Array[getPos(Layer,pos)] = val;

	return 0;
}

TypeVar UneArray::rd(uint32_t Layer, uint32_t pos)
{
	#ifndef _FASTMODE_
	if (build != true)
		return 1;

	if (Layer >= Layers_count)
		return 2;

	if (pos >= Layers_size[Layer])
		return 3;
	#endif

	return Array[getPos(Layer,pos)];
}

uint32_t UneArray::getLayersCount()
{
	return Layers_count;
}

uint32_t UneArray::getLayerSize(uint32_t Layer)
{
	#ifndef _FASTMODE_
	if (build != true)
		return 1;
	
	if (Layer >= Layers_count)
		return 2;
	#endif

	return Layers_size[Layer];
}

uint32_t UneArray::getSize()
{
	return Size;
}

uint8_t UneArray::Delete()
{
	if (init == true)
	{
		free(Layers_size);
	}

	if (build == true)
	{
		free(Array);
	}
	init = false;
	build = false;
	return 0;
}

//=========================Private================================

uint32_t UneArray::getPos(uint32_t Layer, uint32_t pos)
{
	uint32_t res = pos + Shift[Layer];

	return res;
}
