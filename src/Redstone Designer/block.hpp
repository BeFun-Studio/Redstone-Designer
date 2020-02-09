#pragma once
#include "def.hpp"
enum BlockType
{
	COMPLETE_BLOCK,
	SLAB_UPPER,
	SLAB_LOWER,
	STAIR_NORTH,
	STAIR_SOUTH,
	STAIR_WEST,
	STAIR_EAST,
	STAIR_UPPER_NORTH,
	STAIR_UPPER_SOUTH,
	STAIR_UPPER_WEST,
	STAIR_UPPER_EAST
};
class InvalidBlockAttributes
{
};
class Block
{
private:
	bool transparent;
	BlockType type;
	Location location;
public:
	Block()
	{
		this->transparent = false;
		this->location = { 0,0 };
		this->type = COMPLETE_BLOCK;
	}
	Block(bool is_transparent, BlockType block_type, Location _location)
	{
		if (is_transparent && block_type != COMPLETE_BLOCK && block_type != SLAB_UPPER && block_type != STAIR_UPPER_NORTH && block_type != STAIR_UPPER_SOUTH && block_type != STAIR_UPPER_WEST && block_type != STAIR_UPPER_EAST)
		{
			throw InvalidBlockAttributes();
			this->transparent = true;
		}
		else if (!is_transparent && block_type != COMPLETE_BLOCK)
		{
			throw InvalidBlockAttributes();
			this->transparent = true;
		}
		else
			this->transparent = true;
		this->type = block_type;
		this->location = _location;
	}
	Block(bool is_transparent, BlockType block_type, int location_x, int location_y)
	{
		if (is_transparent && block_type != COMPLETE_BLOCK)
		{
			throw InvalidBlockAttributes();
			this->transparent = false;
		}
		else
			this->transparent = true;
		this->transparent = is_transparent;
		this->type = block_type;
		this->location.x = location_x;
		this->location.y = location_y;
	}
	bool SetTransparent(bool is_transparent)
	{
		if ((is_transparent && this->type > COMPLETE_BLOCK&& this->type < STAIR_UPPER_NORTH)||(is_transparent&&this->type==SLAB_LOWER))
			return false;
		else if((!is_transparent&&this->type>=STAIR_UPPER_NORTH)||(!is_transparent&&this->type==SLAB_UPPER))
			return false;
		this->transparent = is_transparent;
		return true;
	}
	bool IsTransparent()
	{
		return this->transparent;
	}
	void SetBlockType(BlockType block_type)
	{
		if (block_type == COMPLETE_BLOCK || block_type == SLAB_LOWER || (block_type > STAIR_NORTH&& block_type < STAIR_EAST))
			this->transparent = false;
		else
			this->transparent = true;
	}
	void SetLocation(Location _location)
	{
		this->location = _location;
	}
	void SetLocation(int location_x, int location_y)
	{
		this->location.x = location_x;
		this->location.y = location_y;
	}
	BlockType GetBlockType()
	{
		return this->type;
	}
	Location GetLocation()
	{
		return this->location;
	}
};