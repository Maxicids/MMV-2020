#pragma once
#include "In.h"
#include "Error.h"
#include "Log.h"
#include "IT.h"
#include "LT.h"
#include "FST.h"
#include "PredifinedWords.h"



namespace LexAnalysis
{
	struct Table
	{
		IT::IdTable idtable;;
		LT::LexTable lextable;
	};
	Table LexAnalysis(In::IN in, Log::LOG log);
	void ClearSpaces(unsigned char source[], int size, Log::LOG log);
	unsigned char** GetWord(unsigned char source[], int size);
}