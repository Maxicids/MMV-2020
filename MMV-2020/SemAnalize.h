#pragma once

#include "Log.h"
#include "LexAnalize.h"

namespace Semantics
{
	void Analize(LexAnalysis::Table lex, Log::LOG log);
	void ToPolish(LexAnalysis::Table lex, Log::LOG log);
}