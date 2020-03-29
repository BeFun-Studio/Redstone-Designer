#pragma once
#include <string>
#include <Windows.h>
#include "def.hpp"
using namespace std;
enum CommandBlockType
{
	COMMON_COMMAND_BLOCK=0,
	CHAIN_COMMAND_BLOCK,
	REPEAT_COMMAND_BLOCK
};

class Component
{
protected:
	Position position;
	wstring comment;
public:
	Position GetPosition()
	{
		return this->position;
	}
	void SetPosition(Position position)
	{
		this->position = position;
	}
	void SetPosition(int x, int y)
	{
		this->position.x = x;
		this->position.y = y;
	}
	void SetComment(LPCWSTR comment)
	{
		this->comment = comment;
	}
	LPCWSTR GetComment()
	{
		return this->comment.c_str();
	}
};

class CommandBlock :public Component
{
private:
	wstring storaged_command;
	CommandBlockType type;
	bool conditional;
	Direction direction;
	bool keep_active;
	wstring custom_name;
public:
	CommandBlock()
	{
		this->storaged_command = L"";
		this->type = COMMON_COMMAND_BLOCK;
		this->conditional = false;
		this->direction = UP;
		this->keep_active = false;
		this->custom_name = L"";
	}
	CommandBlock(LPCWSTR initial_command, CommandBlockType command_block_type, bool _conditional, bool _keep_active, LPCWSTR _custom_name, Position _position)
	{
		this->storaged_command = initial_command;
		this->type = command_block_type;
		this->conditional = _conditional;
		this->keep_active = _keep_active;
		this->custom_name = _custom_name;
		this->position = _position;
	}
	CommandBlock(LPCWSTR initial_command, CommandBlockType command_block_type, bool _conditional, bool _keep_active, LPCWSTR _custom_name, int position_x, int position_y)
	{
		this->storaged_command = initial_command;
		this->type = command_block_type;
		this->conditional = _conditional;
		this->keep_active = _keep_active;
		this->custom_name = _custom_name;
		this->position.x = position_x;
		this->position.y = position_y;
	}
	LPCWSTR GetCommand()
	{
		return this->storaged_command.c_str();
	}
	CommandBlockType GetCommandBlockType()
	{
		return this->type;
	}
	bool IsConditional()
	{
		return this->conditional;
	}
	bool IsKeepActive()
	{
		return this->keep_active;
	}
	LPCWSTR GetCustomName()
	{
		return this->custom_name.c_str();
	}
	void SetCommand(LPCWSTR command)
	{
		this->storaged_command = command;
	}
	void SetCommandBlockType(CommandBlockType cmd_block_type)
	{
		this->type = cmd_block_type;
	}
	void SetConditional(bool is_conditional)
	{
		this->conditional = is_conditional;
	}
	void SetKeepActive(bool is_keep_active)
	{
		this->keep_active = is_keep_active;
	}
	void SetCustomName(LPCWSTR _custom_name)
	{
		this->custom_name = _custom_name;
	}
	void SetDirection(Direction _direction)
	{
		this->direction = _direction;
	}
	Direction GetDirection()
	{
		return this->direction;
	}
	bool operator ==(CommandBlock target)
	{
		if (this->comment == target.GetComment() && this->conditional == target.IsConditional() && this->custom_name == target.GetCustomName() && this->direction == target.GetDirection() && this->keep_active == target.IsKeepActive() && this->position == target.GetPosition() && this->storaged_command == target.GetCommand() && this->type == target.GetCommandBlockType())
			return true;
		return false;
	}
	bool operator ==(CommandBlock& target)
	{
		if (this->comment == target.GetComment() && this->conditional == target.IsConditional() && this->custom_name == target.GetCustomName() && this->direction == target.GetDirection() && this->keep_active == target.IsKeepActive() && this->position == target.GetPosition() && this->storaged_command == target.GetCommand() && this->type == target.GetCommandBlockType())
			return true;
		return false;
	}
	bool operator ==(CommandBlock* target)
	{
		if (this->comment == target->GetComment() && this->conditional == target->IsConditional() && this->custom_name == target->GetCustomName() && this->direction == target->GetDirection() && this->keep_active == target->IsKeepActive() && this->position == target->GetPosition() && this->storaged_command == target->GetCommand() && this->type == target->GetCommandBlockType())
			return true;
		return false;
	}
};
class RedstoneWire :public Component
{
public:
	RedstoneWire()
	{
		this->position = { 0,0 };
	}
	RedstoneWire(Position _position)
	{
		this->position = _position;
	}
	bool operator ==(RedstoneWire* target)
	{
		if (this->GetPosition() == target->GetPosition())
			return true;
	}
	bool operator ==(RedstoneWire& target)
	{
		if (this->GetPosition() == target.GetPosition())
			return true;
	}
};
class RedstoneBlock :public RedstoneWire
{
	bool operator ==(RedstoneBlock* target)
	{
		if (this->GetPosition() == target->GetPosition())
			return true;
	}
	bool operator ==(RedstoneBlock& target)
	{
		if (this->GetPosition() == target.GetPosition())
			return true;
	}
	bool operator ==(RedstoneBlock target)
	{
		if (this->GetPosition() == target.GetPosition())
			return true;
	}
};

class RedstoneTorch :public Component
{
private:
	Direction direction;
public:
	RedstoneTorch()
	{
		this->position = { 0,0 };
		this->direction = UP;
	}
	RedstoneTorch(Position _position, Direction _direction)
	{
		this->position = _position;
		this->direction = _direction;
	}
	bool SetDirection(Direction _direction)
	{
		if (_direction == DOWN)
			return false;
		this->direction = _direction;
		return true;
	}
	Direction GetDirection()
	{
		return this->direction;
	}
	bool operator ==(RedstoneTorch& target)
	{
		if (this->comment == target.GetComment() && this->direction == target.GetDirection() && this->position == target.GetPosition())
			return true;
		return false;
	}
	bool operator ==(RedstoneTorch* target)
	{
		if (this->comment == target->GetComment() && this->direction == target->GetDirection() && this->position == target->GetPosition())
			return true;
		return false;
	}
};

class TrapDoor :public Component
{
private:
	Direction direction;
public:
	TrapDoor()
	{
		this->position = { 0,0 };
		this->direction = NORTH;
	}
	TrapDoor(Position _position, Direction _direction)
	{
		this->position = _position;
		if (direction == UP || direction == DOWN)
		{
			throw InvalidDirection();
			this->direction = NORTH;
		}
		this->direction = _direction;
	}
	TrapDoor(int position_x, int position_y, Direction _direction)
	{
		this->position.x = position_x;
		this->position.y = position_y;
		if (direction == UP || direction == DOWN)
		{
			throw InvalidDirection();
			this->direction = NORTH;
		}
		this->direction = _direction;
	}
	bool SetDirection(Direction _direction)
	{
		if (_direction == UP || _direction == DOWN)
			return false;
		this->direction = _direction;
	}
	Direction GetDirection()
	{
		return this->direction;
	}
	bool operator ==(TrapDoor& target)
	{
		if (this->comment == target.GetComment() && this->direction == target.GetDirection() && this->position == target.GetPosition())
			return true;
		return false;
	}
	bool operator ==(TrapDoor* target)
	{
		if (this->comment == target->GetComment() && this->direction == target->GetDirection() && this->position == target->GetPosition())
			return true;
		return false;
	}
};

class Chest :public Component
{
protected:
	Direction direction;
public:
	Chest()
	{
		this->position = { 0,0 };
		this->direction = NORTH;
	}
	Chest(Position _position, Direction _direction)
	{
		this->position = _position;
		this->direction = _direction;
	}
	Chest(int position_x, int position_y, Direction _direction)
	{
		this->position.x = position_x;
		this->position.y = position_y;
		this->direction = _direction;
	}
	bool SetDirection(Direction _direction)
	{
		if (_direction == UP || _direction == DOWN)
			return false;
		this->direction = _direction;
	}
	Direction GetDirection()
	{
		return this->direction;
	}
	bool operator ==(Chest& target)
	{
		if (this->comment == target.GetComment() && this->direction == target.GetDirection() && this->position == target.GetPosition())
			return true;
		return false;
	}
	bool operator ==(Chest* target)
	{
		if (this->comment == target->GetComment() && this->direction == target->GetDirection() && this->position == target->GetPosition())
			return true;
		return false;
	}
};

class TrapChest :public Chest
{
public:
	bool operator ==(TrapChest& target)
	{
		if (this->comment == target.GetComment() && this->direction == target.GetDirection() && this->position == target.GetPosition())
			return true;
		return false;
	}
	bool operator ==(TrapChest* target)
	{
		if (this->comment == target->GetComment() && this->direction == target->GetDirection() && this->position == target->GetPosition())
			return true;
		return false;
	}
};