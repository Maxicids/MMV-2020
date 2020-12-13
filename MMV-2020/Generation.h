#pragma once
#include "Parm.h"
#include "LT.h"
#include "IT.h"
#include "LexAnalize.h"


#define HEAD *(log.stream) << "using System;" << endl << endl <<\
    "namespace CourseProject" << endl << "{" << endl <<"\t" << "class MMV2020" << endl << "\t" << "{" << endl << endl << "\t" << "\t";

#define FOOTER 	*(log.stream) << endl << "\t" << "}" << endl  << "}";

namespace CodeGeneration
{
	void Generation(LexAnalysis::Table table, Log::LOG log);
	void AddCodeSegm(LexAnalysis::Table table, Log::LOG log);
}

