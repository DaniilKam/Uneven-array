#pragma once
#ifndef _UNEVEN_2D_ARRAY_H__
#define _UNEVEN_2D_ARRAY_H__

#include <cstdint>
#include "Uneven_setup.h"

class UneArray_
{
public:
	uint8_t Init(uint32_t Layers);	//Initing and set Layers count.
	uint8_t setLayerSize(uint32_t Layer, uint32_t Size);	//Set Layer's size.
	uint8_t setLayerSize(uint32_t Sizes[]);	//Set all Layers' sizes.
	uint8_t Create();	//Creating array.
	uint8_t wr(uint32_t Layer, uint32_t pos, uint32_t val);	//Writing val on layer in pos.
	uint32_t rd(uint32_t Layer, uint32_t pos);	//Reading val on layer in pos.
	uint32_t getLayersCount();	//Return layers count
	uint32_t getLayerSize(uint32_t Layer);	//Return layer's size
	uint32_t getSize();	//Return array size in byte
	uint8_t Delete();	//Delete array
private:
	uint32_t getPos(uint32_t Layer, uint32_t pos);
	uint32_t Size = 0;
	uint32_t* Array;
	uint32_t* Shift;
	uint32_t Layers_count;
	uint32_t* Layers_size;
	bool init = false;
	bool build = false;
};

#endif // ! _UNEVEN_ARRAY_H__