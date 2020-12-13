#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#include "LexAnalize.h"

namespace Converter
{
    void ToPolish(LexAnalysis::Table table);
    void Show(LexAnalysis::Table table);
    int GetPriority(char c);
    bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
}