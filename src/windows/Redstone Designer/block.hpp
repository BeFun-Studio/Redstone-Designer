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
	Position position;
public:
	Block()
	{
		this->transparent = false;
		this->position = { 0,0 };
		this->type = COMPLETE_BLOCK;
	}
	Block(bool is_transparent, BlockType block_type, Position _position)
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
		this->position = _position;
	}
	Block(bool is_transparent, BlockType block_type, int position_x, int position_y)
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
		this->position.x = position_x;
		this->position.y = position_y;
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
	void SetPosition(Position _position)
	{
		this->position = _position;
	}
	void SetPosition(int position_x, int position_y)
	{
		this->position.x = position_x;
		this->position.y = position_y;
	}
	BlockType GetBlockType()
	{
		return this->type;
	}
	Position GetPosition()
	{
		return this->position;
	}
	bool operator ==(Block& target)
	{
		if (target.GetBlockType() == this->type && target.GetPosition() == this->position && target.IsTransparent() == this->transparent)
			return true;
		return false;
	}
	bool operator ==(Block* target)
	{
		if (target->GetBlockType() == this->type && target->GetPosition() == this->position && target->IsTransparent() == this->transparent)
			return true;
		return false;
	}
};