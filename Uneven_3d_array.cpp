#include "Uneven_3d_array.h"
#include <cstdlib>

uint8_t Une3DArray::PreInit(uint32_t ArraysCount)
{
	#ifndef _FASTMODE_
	if (preinit == true)
		return 1;
	#endif; // ! _FASTMODE_

	Layers_size.Init(ArraysCount);

	Layers_count = (uint32_t*)malloc(ArraysCount*4);

	for (uint32_t i = 0; i < ArraysCount; i++)
	{
		Layers_count[i] = 1;
	}

	Arrays_count = ArraysCount;

	preinit = true;

	return 0;
}

uint8_t Une3DArray::Init()
{
	#ifndef _FASTMODE_
	if (preinit != true)
		return 1;

	if (init == true)
		return 1;
	#endif; // ! _FASTMODE_

	Layers_size.Create();

	init = true;
	return 0;
}

uint8_t Une3DArray::SetLayerCount(uint32_t Array, uint32_t LayerCount)
{
	#ifndef _FASTMODE_
	if (preinit != true)
		return 1;

	if (Array >= Arrays_count)
		return 2;
	#endif; // ! _FASTMODE_

	Layers_count[Array] = LayerCount;

	Layers_size.setLayerSize(Array,LayerCount);

	return 0;
}

uint8_t Une3DArray::SetLayerSize(uint32_t Array, uint32_t Layer, uint32_t Size)
{
	#ifndef _FASTMODE_
	if (init != true)
		return 1;
	#endif; // ! _FASTMODE_

	Layers_size.wr(Array, Layer, Size);

	return 0;
}

uint8_t Une3DArray::wr(uint32_t Array, uint32_t Layer, uint32_t pos, TypeVar val)
{
	#ifndef _FASTMODE_
	if (build != true)
		return 1;

	if (Array >= Arrays_count)
		return 2;

	if (Layer >= Layers_count[Array])
		return 3;

	if (pos >= Layers_size.rd(Array, Layer))
		return 4;
	#endif; // ! _FASTMODE_

	Arrays[getPos(Array, Layer, pos)] = val;

	return 0;
}

TypeVar Une3DArray::rd(uint32_t Array, uint32_t Layer, uint32_t pos)
{
	#ifndef _FASTMODE_
	if (build != true)
		return 1;

	if (Array >= Arrays_count)
		return 2;

	if (Layer >= Layers_count[Array])
		return 3;

	if (pos >= Layers_size.rd(Array, Layer))
		return 4;
	#endif; // ! _FASTMODE_

	return Arrays[getPos(Array, Layer, pos)];
}

uint8_t Une3DArray::Create()
{
	#ifndef _FASTMODE_
	if (init != true)
		return 1;

	if (build == true)
		return 2;
	#endif; // ! _FASTMODE_

	for (uint32_t Array = 0; Array < Arrays_count; Array++)	//Getting Arrays size
	{
		for (uint32_t Layer = 0; Layer < Layers_count[Array]; Layer++)
		{
			Size += Layers_size.rd(Array, Layer);
		}
	}
	Size = Size * sizeof(TypeVar);

	Arrays = (TypeVar*)malloc(Size);	//Create Array
	
	Shift.Init(Arrays_count);	//Init Shift array
	for (uint32_t Array = 0; Array < Arrays_count; Array++)
	{
		Shift.setLayerSize(Array, Layers_count[Array]);
	}
	Shift.Create();

	uint32_t pos = 0;			//Fulling Shift array
	for (uint32_t Array = 0; Array < Arrays_count; Array++)
	{
		for (uint32_t Layer = 0; Layer < Layers_count[Array]; Layer++)
		{
			Shift.wr(Array,Layer,pos);
			pos += Layers_size.rd(Array,Layer);
		}
	}

	build = true;
	return 0;
}

uint8_t Une3DArray::Delete()
{
	
	if (preinit == true)
	{
		Layers_size.Delete();
	}

	if (build == true)
	{
		Shift.Delete();
		free(Arrays);
	}

	if (init == true)
	{
		free(Layers_count);
	}

	preinit = false;
	init = false;
	build = false;

	return 0;
}

//=========================Private=============================

uint32_t Une3DArray::getPos(uint32_t Array, uint32_t Layer, uint32_t pos)
{
	return (pos + Shift.rd(Array, Layer));
}
