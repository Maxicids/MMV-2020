#include <iomanip>
#include "LT.h"
#include <cstddef>
#include <iostream>

using namespace std;

namespace LT
{
	LexTable Create(int size)
	{
		if (size > LT_MAXSIZE)
			throw ERROR_THROW(201);
		LexTable lexTable;
		lexTable.maxsize = size;
		lexTable.size = NULL;
		lexTable.table = new Entry[size];
		return lexTable;
	}

	void Add(LexTable& lexTable, Entry entry)
	{
		if (lexTable.size >= lexTable.maxsize)
			throw ERROR_THROW(202);
		lexTable.table[lexTable.size++] = entry;
	}

	Entry GetEntry(LexTable& lexTable, int n)
	{
		return lexTable.table[n];
	}

	void Delete(LexTable& lexTable)
	{
		delete[] lexTable.table;
	}

	void WriteLexTable(LT::LexTable& lextable)
	{
		cout << endl << setw(32) << '~' << " Таблица лексем " << setw(43) << '~' << endl;
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].line != lextable.table[i - 1].line)
			{
				cout << endl;
				cout << lextable.table[i].line + 1 << " ";
			}
			cout << lextable.table[i].lexema;
		}
		cout << "\n";
	}
}