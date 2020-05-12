#pragma once
#ifndef _UNEVEN_3D_ARRAY_H_
#define _UNEVEN_3D_ARRAY_H_


#include <cstdint>
#include "Uneven_2d_array_.h"
#include "Uneven_setup.h"

class Une3DArray
{
public:
	uint8_t PreInit(uint32_t ArraysCount);
	uint8_t Init();
	uint8_t SetLayerCount(uint32_t Array, uint32_t LayerCount);
	uint8_t SetLayerSize(uint32_t Array, uint32_t Layer, uint32_t Size);
	uint8_t wr(uint32_t Array, uint32_t Layer, uint32_t pos, TypeVar val);
	TypeVar rd(uint32_t Array, uint32_t Layer, uint32_t pos);
	uint8_t Create();
	uint8_t Delete();
private:
	uint32_t getPos(uint32_t Array, uint32_t Layer, uint32_t pos);
	TypeVar* Arrays;
	uint32_t Arrays_count = 1;
	uint32_t* Layers_count;
	uint32_t Size = 0;
	UneArray_ Layers_size;	//layer - Array; pos - layer, val - Size
	UneArray_ Shift;
	bool preinit = false;
	bool init = false;
	bool build = false;
};

#endif // !_UNEVEN_3D_ARRAY_H_