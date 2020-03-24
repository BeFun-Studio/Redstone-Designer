#pragma once
#include "components.hpp"
#include "block.hpp"
#include <list>
#include <sstream>
enum CircuitFileImportErrorCode
{
	FILE_DOES_NOT_EXISTING=1,
	FILE_STRUCTURE_DAMAGED
};
enum SegmentType
{
	NOT_SPECIFIED=0,
	WIRES,
	REDSTONE_BLOCKS,
	REDSTONE_TORCHES,
	COMMAND_BLOCKS,
	TRAP_DOORS,
	BLOCKS
};
struct CircuitLayer
{
	list<RedstoneWire>wires;
	list<RedstoneBlock>redstone_blocks;
	list<RedstoneTorch>redstone_torches;
	list<CommandBlock>command_blocks;
	list<TrapDoor>trap_doors;
	list<Block>blocks;
	list<Chest>chests;
	list<TrapChest>trap_chests;
};
struct ImporterGenericSegment
{
	wstring position_x;
	wstring position_y;
};

struct ImporterRedstoneTorchSegment :public ImporterGenericSegment
{
	wstring direction;
};
struct ImporterCommandBlockSegment :public ImporterGenericSegment
{
	wstring conditional;
	wstring keep_active;
	wstring block_type;
	wstring custom_name;
	wstring command;
	wstring direction;
};
struct ImporterTrapDoorSegment :public ImporterGenericSegment
{
	wstring direction;
};
struct ImporterBlockSegment :public ImporterGenericSegment
{
	wstring block_type;
	wstring transparent;
};

list<CircuitLayer>CircuitLayers;

bool ExportCircuitFile(LPCWSTR export_path)
{
	FILE* fp=_wfopen(export_path,L"w");
	if (fp == NULL)
	{
		fclose(fp);
		return false;
	}
	fwprintf(fp, L"redstonedesigner;");
	for (int i = 0; i < CircuitLayers.size(); i++)
	{
		fprintf(fp, "<");
		for (list<CircuitLayer>::iterator itor = CircuitLayers.begin(); itor != CircuitLayers.end(); i++)
		{
			fwprintf(fp, L"wires");
			for (list<RedstoneWire>::iterator itor_redstone_wire = itor->wires.begin(); itor_redstone_wire != itor->wires.end(); itor_redstone_wire++)
				fwprintf(fp, L",%d,%d", itor_redstone_wire->GetPosition().x, itor_redstone_wire->GetPosition().y);
			fwprintf(fp, L";redstone_blocks");
			for (list<RedstoneBlock>::iterator itor_redstone_block = itor->redstone_blocks.begin(); itor_redstone_block != itor->redstone_blocks.end(); itor_redstone_block++)
				fwprintf(fp, L",%d,%d", itor_redstone_block->GetPosition().x, itor_redstone_block->GetPosition().y);
			fwprintf(fp, L";redstone_torches");
			for (list<RedstoneTorch>::iterator itor_redstone_torch = itor->redstone_torches.begin(); itor_redstone_torch != itor->redstone_torches.end(); itor_redstone_torch++)
				fwprintf(fp, L",%d,%d,%d", itor_redstone_torch->GetPosition().x, itor_redstone_torch->GetPosition().y,itor_redstone_torch->GetDirection());
			fwprintf(fp, L";command_blocks");
			for (list<CommandBlock>::iterator itor_command_block = itor->command_blocks.begin(); itor_command_block != itor->command_blocks.end(); itor_command_block++)
				fwprintf(fp, L",%d,%d,%d,%d,%d,%ls,'%ls',%d", itor_command_block->GetPosition().x, itor_command_block->GetPosition().y,itor_command_block->IsConditional(),itor_command_block->IsKeepActive(),itor_command_block->GetCommandBlockType(),itor_command_block->GetCustomName(),itor_command_block->GetCommand(),itor_command_block->GetDirection());
			fwprintf(fp, L";trap_doors");
			for (list<TrapDoor>::iterator itor_trap_door = itor->trap_doors.begin(); itor_trap_door != itor->trap_doors.end(); itor_trap_door++)
				fwprintf(fp, L",%d,%d,%d", itor_trap_door->GetPosition().x,itor_trap_door->GetPosition().y,itor_trap_door->GetDirection());
			fwprintf(fp, L"blocks");
			for (list<Block>::iterator itor_block = itor->blocks.begin(); itor_block != itor->blocks.end(); itor_block++)
				fwprintf(fp, L",%d,%d,%d,%d", itor_block->GetPosition().x, itor_block->GetPosition().y, itor_block->GetBlockType(), itor_block->IsTransparent());
		}
		fprintf(fp, ">");
	}
	fclose(fp);
	return true;
}

int ImportCircuitFile(LPCWSTR import_path)
{
	FILE* fp = _wfopen(import_path, L"r");
	if (fp == NULL)
	{
		fclose(fp);
		return FILE_DOES_NOT_EXISTING;
	}
	int current_char;
	wstring current_string;
	while (true)
	{
		current_char = fgetwc(fp);
		if (current_char != EOF && current_char != L';')
			current_string += current_char;
		else
			break;
	}
	if (current_string != L"redstonedesigner")
		return FILE_STRUCTURE_DAMAGED;
	if (current_char = fgetwc(fp) != L'<')
		return FILE_STRUCTURE_DAMAGED;
	bool first_read = false;
	while (1)
	{
		while (1)
		{
			current_char = fgetwc(fp);
			if (current_char == L'>')
				break;
			else if (current_char == EOF && !first_read)
				return FILE_STRUCTURE_DAMAGED;
			else
				goto end_import;
			current_string += current_char;
			first_read = false;
		}
		wstring current_arg;
		vector<wstring>args;
		for (int i = 0; i < current_string.length(); i++)
			if (current_string[i] == L',')
			{
				if (current_arg.length() == 0)
					continue;
				else
				{
					args.push_back(current_arg);
					current_arg = L"";
				}
			}
			else if (current_string[i] == L'\'')
			{
				if (current_arg.length() != 0)
				{
					args.push_back(current_arg);
					current_arg = L"";
				}
				for (; current_string[i] != L'\''; i++)
					if (i + 1 == current_string.length())
						return FILE_STRUCTURE_DAMAGED;
					else
						current_arg += current_string[i];
				args.push_back(current_arg);
				current_arg = L"";
			}
		bool read_complete_segment=false;
		unsigned char read_arguments = 0;
		SegmentType current_segment_type;
		vector<ImporterGenericSegment>wire_segments;
		vector<ImporterGenericSegment>redstone_block_segments;
		vector<ImporterRedstoneTorchSegment>redstone_torch_segments;
		vector<ImporterCommandBlockSegment>command_block_segments;
		vector<ImporterTrapDoorSegment>trap_door_segments;
		vector<ImporterBlockSegment>block_segments;
		for (int i = 0; i < args.size(); i++)
			if (args[i] == L"wires")
				if (!read_complete_segment && current_segment_type != NOT_SPECIFIED)
					return FILE_STRUCTURE_DAMAGED;
				else
				{
					read_complete_segment = false;
					current_segment_type = WIRES;
				}
			else if(args[i]==L"redstone_blocks")
				if (!read_complete_segment && current_segment_type != NOT_SPECIFIED)
					return FILE_STRUCTURE_DAMAGED;
				else
				{
					read_complete_segment = false;
					current_segment_type = REDSTONE_BLOCKS;
				}
			else if (args[i] == L"redstone_torches")
				if (!read_complete_segment && current_segment_type != NOT_SPECIFIED)
					return FILE_STRUCTURE_DAMAGED;
				else
				{
					read_complete_segment = false;
					current_segment_type = REDSTONE_TORCHES;
				}
			else if (args[i] == L"command_blocks")
				if (!read_complete_segment && current_segment_type != NOT_SPECIFIED)
					return FILE_STRUCTURE_DAMAGED;
				else
				{
					read_complete_segment = false;
					current_segment_type = COMMAND_BLOCKS;
				}
			else if (args[i] == L"trap_doors")
				if (!read_complete_segment && current_segment_type != NOT_SPECIFIED)
					return FILE_STRUCTURE_DAMAGED;
				else
				{
					read_complete_segment = false;
					current_segment_type = TRAP_DOORS;
				}
			else if (args[i] == L"blocks")
				if (!read_complete_segment && current_segment_type != NOT_SPECIFIED)
					return FILE_STRUCTURE_DAMAGED;
				else
				{
					read_complete_segment = false;
					current_segment_type = BLOCKS;
				}
			else
			{
				switch (current_segment_type)
				{
				case WIRES:
					if (read_arguments == 0)
					{
						ImporterGenericSegment new_segment;
						new_segment.position_x = args[i];
						wire_segments.push_back(new_segment);
						read_arguments++;
					}
					else
					{
						vector<ImporterGenericSegment>::iterator itor = wire_segments.end() - 1;
						itor->position_y = args[i];
						read_arguments--;
						read_complete_segment = true;
					}
				case REDSTONE_BLOCKS:
					if (read_arguments == 0)
					{
						ImporterGenericSegment new_segment;
						new_segment.position_x = args[i];
						redstone_block_segments.push_back(new_segment);
						read_arguments++;
					}
					else
					{
						vector<ImporterGenericSegment>::iterator itor = redstone_block_segments.end() - 1;
						itor->position_y = args[i];
						read_arguments--;
						read_complete_segment = true;
					}
				case REDSTONE_TORCHES:
					switch (read_arguments)
					{
					case 0:
					{
						ImporterRedstoneTorchSegment new_segment;
						new_segment.position_x = args[i];
						redstone_torch_segments.push_back(new_segment);
						read_arguments++;
						break;
					}
					case 1:
					{
						vector<ImporterRedstoneTorchSegment>::iterator itor = redstone_torch_segments.end() - 1;
						itor->position_y = args[i];
						read_arguments++;
						break;
					}
					case 2:
					{
						vector<ImporterRedstoneTorchSegment>::iterator itor = redstone_torch_segments.end() - 1;
						itor->direction = args[i];
						read_arguments = 0;
						read_complete_segment = true;
						break;
					}
					}
				case COMMAND_BLOCKS:
					switch (read_arguments)
					{
					case 0:
					{
						ImporterCommandBlockSegment new_segment;
						new_segment.position_x = args[i];
						command_block_segments.push_back(new_segment);
						read_arguments++;
						break;
					}
					case 1:
					{
						vector<ImporterCommandBlockSegment>::iterator itor = command_block_segments.end() - 1;
						itor->position_y = args[i];
						read_arguments++;
						break;
					}
					case 2:
					{
						vector<ImporterCommandBlockSegment>::iterator itor = command_block_segments.end() - 1;
						itor->conditional = args[i];
						read_arguments++;
						break;
					}
					case 3:
					{
						vector<ImporterCommandBlockSegment>::iterator itor = command_block_segments.end() - 1;
						itor->keep_active = args[i];
						read_arguments++;
						break;
					}
					case 4:
					{
						vector<ImporterCommandBlockSegment>::iterator itor = command_block_segments.end() - 1;
						itor->block_type = args[i];
						read_arguments++;
						break;
					}
					case 5:
					{
						vector<ImporterCommandBlockSegment>::iterator itor = command_block_segments.end() - 1;
						itor->custom_name = args[i];
						read_arguments++;
						break;
					}
					case 6:
					{
						vector<ImporterCommandBlockSegment>::iterator itor = command_block_segments.end() - 1;
						itor->command = args[i];
						read_arguments++;
						break;
					}
					case 7:
					{
						vector<ImporterCommandBlockSegment>::iterator itor = command_block_segments.end() - 1;
						itor->direction = args[i];
						read_arguments=0;
						break;
					}
					}
				case TRAP_DOORS:
					switch (read_arguments)
					{
					case 0:
					{
						ImporterTrapDoorSegment new_segment;
						new_segment.position_x = args[i];
						trap_door_segments.push_back(new_segment);
						read_arguments++;
						break;
					}
					case 1:
					{
						vector<ImporterTrapDoorSegment>::iterator itor = trap_door_segments.end() - 1;
						itor->position_y = args[i];
						read_arguments++;
						break;
					}
					case 2:
					{
						vector<ImporterTrapDoorSegment>::iterator itor = trap_door_segments.end() - 1;
						itor->direction = args[i];
						read_arguments=0;
						break;
					}
					}
					break;
				case BLOCKS:
					switch (read_arguments)
					{
					case 0:
					{
						ImporterBlockSegment new_segment;
						new_segment.position_x = args[i];
						block_segments.push_back(new_segment);
						read_arguments++;
						break;
					}
					case 1:
					{
						vector<ImporterBlockSegment>::iterator itor=block_segments.end()-1;
						itor->position_y = args[i];
						read_arguments++;
						break;
					}
					case 2:
					{
						vector<ImporterBlockSegment>::iterator itor = block_segments.end() - 1;
						itor->block_type = args[i];
						read_arguments++;
						break;
					}
					case 3:
					{
						vector<ImporterBlockSegment>::iterator itor = block_segments.end() - 1;
						itor->transparent = args[i];
						read_arguments=0;
						break;
					}
					}
				}
			}
		first_read = true;
		CircuitLayer current_layer;
		for (int i = 0; i < wire_segments.size(); i++)
		{
			RedstoneWire wire;
			wstringstream ss;
			int x, y;
			ss << wire_segments[i].position_x.c_str();
			ss >> x;
			ss << wire_segments[i].position_y.c_str();
			ss >> y;
			Position position = { x,y };
			wire.SetPosition(position);
			current_layer.wires.push_back(wire);
		}
		for (int i = 0; i < redstone_block_segments.size(); i++)
		{
			RedstoneBlock redstone_block;
			wstringstream ss;
			int x, y;
			ss << wire_segments[i].position_x.c_str();
			ss >> x;
			ss << wire_segments[i].position_y.c_str();
			ss >> y;
			Position position = { x,y };
			redstone_block.SetPosition(position);
			current_layer.redstone_blocks.push_back(redstone_block);
		}
		for (int i = 0; i < redstone_torch_segments.size(); i++)
		{
			RedstoneTorch redstone_torch;
			wstringstream ss;
			int x, y;
			int direction;
			ss << redstone_torch_segments[i].position_x.c_str();
			ss >> x;
			ss << redstone_torch_segments[i].position_y;
			ss >> y;
			ss << redstone_torch_segments[i].direction;
			ss >> direction;
			Position position = { x,y };
			redstone_torch.SetPosition(position);
			redstone_torch.SetDirection((Direction)direction);
			current_layer.redstone_torches.push_back(redstone_torch);
		}
		for (int i = 0; i < command_block_segments.size(); i++)
		{
			CommandBlock command_block;
			wstringstream ss;
			int x, y, command_block_type,direction;
			bool conditional, keep_active;
			LPCWSTR custom_name, command;
			ss << command_block_segments[i].position_x.c_str();
			ss >> x;
			ss << command_block_segments[i].position_y.c_str();
			ss >> y;
			ss << command_block_segments[i].block_type.c_str();
			ss >> command_block_type;
			ss << command_block_segments[i].conditional.c_str();
			ss >> conditional;
			ss << command_block_segments[i].keep_active.c_str();
			ss >> keep_active;
			custom_name = command_block_segments[i].custom_name.c_str();
			command = command_block_segments[i].command.c_str();
			ss << command_block_segments[i].direction.c_str();
			ss >> direction;
			Position position = { x,y };
			command_block.SetPosition(position);
			command_block.SetCommandBlockType((CommandBlockType)command_block_type);
			command_block.SetConditional(conditional);
			command_block.SetDirection((Direction)direction);
			command_block.SetKeepActive(keep_active);
			command_block.SetCustomName(custom_name);
			command_block.SetCommand(command);
			current_layer.command_blocks.push_back(command_block);
		}
		for (int i = 0; i < trap_door_segments.size(); i++)
		{
			TrapDoor trap_door;
			wstringstream ss;
			int x, y, direction;
			ss << trap_door_segments[i].position_x.c_str();
			ss >> x;
			ss << trap_door_segments[i].position_y.c_str();
			ss >> y;
			ss << trap_door_segments[i].direction.c_str();
			ss >> direction;
			Position position={ x,y };
			trap_door.SetPosition(position);
			trap_door.SetDirection((Direction)direction);
			current_layer.trap_doors.push_back(trap_door);
		}
		for (int i = 0; i < block_segments.size(); i++)
		{
			Block block;
			wstringstream ss;
			int x, y, block_type;
			bool transparent;
			ss << block_segments[i].position_x.c_str();
			ss >> x;
			ss << block_segments[i].position_y.c_str();
			ss >> y;
			ss << block_segments[i].block_type;
			ss >> block_type;
			ss << block_segments[i].transparent;
			ss >> transparent;
			Position position = { x,y };
			block.SetPosition(position);
			block.SetBlockType((BlockType)block_type);
			block.SetTransparent(transparent);
			current_layer.blocks.push_back(block);
		}
		CircuitLayers.push_back(current_layer);
	}
	end_import:
	return 0;
}