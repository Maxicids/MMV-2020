#include "IT.h"
#include "stdafx.h"
namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE)
			throw ERROR_THROW(203);
		IdTable idTable;
		idTable.maxsize = size;
		idTable.size = NULL;
		idTable.table = new Entry[size];
		return idTable;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size >= idtable.maxsize)
			throw ERROR_THROW(204);
		idtable.table[idtable.size++] = entry;
	}

	Entry GetEntry(IdTable & idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, unsigned char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp((const char*)idtable.table[i].id, (const char*)id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
	}
}