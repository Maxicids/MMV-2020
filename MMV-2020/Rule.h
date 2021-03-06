#pragma once

#include "Greibach.h"

#define GRB_ERROR_SERIES 600

#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(
		NS('S'), TS('$'),                     // ��������� ������, ��� �����
		13,									  // ���������� ������
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,    // �������� ��������� ���������
			3,
			Rule::Chain(6, TS('f'), TS('t'), TS('i'), NS('F'), NS('B'), NS('S')),
			Rule::Chain(4, TS('h'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(5, TS('f'), TS('t'), TS('i'), NS('F'), NS('B'))
		),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 1,    // ����������� ������ ���������� �������
			2,
			Rule::Chain(3, TS('['), NS('P'), TS(']')),
			Rule::Chain(2, TS('['), TS(']'))
		),
		Rule(
			NS('P'), GRB_ERROR_SERIES + 2,    // ������ � ���������� ������� ��� � ����������
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS('&'), NS('P'))
		),
		Rule(
			NS('B'), GRB_ERROR_SERIES + 3,    // ����������� ���� �������
			2,
			Rule::Chain(8, TS('{'), NS('N'), TS('r'), TS('['), NS('I'), TS(']'), TS('.'), TS('}')),
			Rule::Chain(7, TS('{'), TS('r'), TS('['), NS('I'), TS(']'), TS('.'), TS('}'))
		),
		Rule(
			NS('I'), GRB_ERROR_SERIES + 4,    // ������������ ���������. ��������� ������ �������� � ��������������
			2,
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 5,    // �������� ����������� � ���� �������
			20,
			Rule::Chain(5, TS('v'), TS('t'), TS('i'), TS('.'), NS('N')),//
			Rule::Chain(7, TS('v'), TS('t'), TS('i'), TS('='), NS('E'), TS('.'), NS('N')),//
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS('.'), NS('N')),//
			Rule::Chain(8, TS('c'), TS('['), NS('R'), TS(']'), TS('{'), NS('X'), TS('}'), NS('N')),//if
			Rule::Chain(12, TS('c'), TS('['), NS('R'), TS(']'), TS('{'), NS('X'), TS('}'), TS('u'), TS('{'), NS('X'), TS('}'), NS('N')),
			Rule::Chain(6, TS('P'), NS('K'), TS('.'), NS('N')),//
			Rule::Chain(6, TS('S'), NS('K'), TS('.'), NS('N')),//
			Rule::Chain(6, TS('o'), TS('['), NS('I'), TS(']'), TS('.'), NS('N')),//
			Rule::Chain(3, TS('n'), TS('.'), NS('N')),//
			Rule::Chain(4, TS('i'), NS('K'), TS('.'), NS('N')),

			Rule::Chain(4, TS('v'), TS('t'), TS('i'), TS('.')),
			Rule::Chain(6, TS('v'), TS('t'), TS('i'), TS('='), NS('E'), TS('.')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS('.')),
			Rule::Chain(7, TS('c'), TS('['), NS('R'), TS(']'), TS('{'), NS('X'), TS('}')),
			Rule::Chain(11, TS('c'), TS('['), NS('R'), TS(']'), TS('{'), NS('X'), TS('}'), TS('u'), TS('{'), NS('X'), TS('}')),
			Rule::Chain(3, TS('P'), NS('K'), TS('.')),
			Rule::Chain(3, TS('S'), NS('K'), TS('.')),
			Rule::Chain(5, TS('o'), TS('['), NS('I'), TS(']'), TS('.')),//
			Rule::Chain(2, TS('n'), TS('.')),
			Rule::Chain(3, TS('i'), NS('K'), TS('.'))
		),
		Rule(
			NS('R'), GRB_ERROR_SERIES + 6,    // ������ � �������� ���������
			4,
			Rule::Chain(3, TS('i'), TS('b'), TS('i')),
			Rule::Chain(3, TS('i'), TS('b'), TS('l')),
			Rule::Chain(3, TS('l'), TS('b'), TS('i')),
			Rule::Chain(3, TS('l'), TS('b'), TS('l'))
		),
		Rule(
			NS('K'), GRB_ERROR_SERIES + 7,    // ������ � ������ �������
			2,
			Rule::Chain(3, TS('['), NS('W'), TS(']')),
			Rule::Chain(2, TS('['), TS(']'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 8,    // ������ � �������������� ���������
			12,
			Rule::Chain(2, TS('i'), NS('K')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('P'), NS('K')),
			Rule::Chain(2, TS('S'), NS('K')),

			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('i'), NS('K'), NS('M')),
			Rule::Chain(3, TS('P'), NS('K'), NS('M')),
			Rule::Chain(3, TS('S'), NS('K'), NS('M'))
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 9,    // ������ � ���������� ���������� ������� 
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS('&'), NS('W')),
			Rule::Chain(3, TS('l'), TS('&'), NS('W'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 8,    // ������ � �������������� ���������
			2,
			Rule::Chain(2, TS('s'), NS('E')),
			Rule::Chain(3, TS('s'), NS('E'), NS('M'))
		),
		Rule(
			NS('X'), GRB_ERROR_SERIES + 11,    // �������� ����������� � ���� �����/��������� ���������
			12,
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS('.'), NS('X')),
			Rule::Chain(6, TS('P'), NS('K'), TS('.'), NS('X')),
			Rule::Chain(6, TS('S'), NS('K'), TS('.'), NS('X')),
			Rule::Chain(6, TS('o'), TS('['), NS('I'), TS(']'), TS('.'), NS('X')),
			Rule::Chain(3, TS('c'), TS('.'), NS('N')),
			Rule::Chain(4, TS('i'), NS('K'), TS('.'), NS('X')),

			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS('.')),
			Rule::Chain(3, TS('P'), NS('K'), TS('.')),
			Rule::Chain(3, TS('S'), NS('K'), TS('.')),
			Rule::Chain(3, TS('o'), NS('K'), TS('.')),
			Rule::Chain(2, TS('c'), TS('.')),
			Rule::Chain(3, TS('i'), NS('K'), TS('.'))
		)
	);
}