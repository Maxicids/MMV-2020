#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Системная ошибка -> Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системная ошибка -> Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Системная ошибка -> Параметр -in должен быть задан"),
		ERROR_ENTRY(101, "Системная ошибка -> Превышена длина входного параметра"),
		ERROR_ENTRY(102, "Системная ошибка -> Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(103, "Системная ошибка -> Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(104, "Системная ошибка -> Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF(200),
		ERROR_ENTRY(201, "Лексическая ошибка -> Превышен размер таблицы лексем"),
		ERROR_ENTRY(202, "Лексическая ошибка -> Переполнение таблицы лексем"),
		ERROR_ENTRY(203, "Лексическая ошибка -> Превышен размер таблицы идентификаторов"),
		ERROR_ENTRY(204, "Лексическая ошибка -> Переполнение таблицы идентификаторов"),
		ERROR_ENTRY(205, "Лексическая ошибка -> Неизвестная последовательность символов"),
		ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250),
		ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "Семантическая ошибка -> Не закрыт строковый литерал"),//
		ERROR_ENTRY(301, "Семантическая ошибка -> Попытка использовать необьявленный идентификатор"),//lex
		ERROR_ENTRY(302, "Семантическая ошибка -> Отсутствует точка входа Head"),//
		ERROR_ENTRY(303, "Семантическая ошибка -> Обнаружено несколько точек входа Head"),//
		ERROR_ENTRY(304, "Семантическая ошибка -> Превышен размер строкового литерала"),//255
		ERROR_ENTRY(305, "Семантическая ошибка -> Объявление переменной без ключевого слова var недопустимо"),//need
		ERROR_ENTRY(306, "Семантическая ошибка -> Необъявленный идентификатор"),//need
		ERROR_ENTRY(307, "Семантическая ошибка -> Недопустимо объявление переменной без указания типа"),//need
		ERROR_ENTRY(308, "Семантическая ошибка -> Попытка реализовать уже существующую функцию"),//need
		ERROR_ENTRY(309, "Семантическая ошибка -> Попытка переопределить параметр или ошибка области видимости"),//need
		ERROR_ENTRY(310, "Семантическая ошибка -> Попытка переопределить переменную или ошибка области видимости"),//need
		ERROR_ENTRY(311, "Семантическая ошибка -> Не указан тип функции"),//need
		ERROR_ENTRY(312, "Семантическая ошибка -> Использование пустого строкового литерала недопустимо"),//
		ERROR_ENTRY(313, "Семантическая ошибка -> Тип функции и тип возвращаемого значения должны совпадать"),//need Sem
		ERROR_ENTRY(314, "Семантическая ошибка -> Превышено максимально допустимое (2) количество параметров функции"),//
		ERROR_ENTRY(315, "Семантическая ошибка -> Несовпадение типов передаваемых параметров"),//
		ERROR_ENTRY(316, "Семантическая ошибка -> Слишком много аргументов в вызове функции"),//
		ERROR_ENTRY(317, "Семантическая ошибка -> Слишком мало аргументов в вызове функции"),//
		ERROR_ENTRY(318, "Семантическая ошибка -> Несовместимые типы при присваивании"),//
		ERROR_ENTRY(319, "Семантическая ошибка -> Недопустимый целочисленный литерал"),//lex
		ERROR_ENTRY(320, "Семантическая ошибка -> Типы данных в выражении не совпадают"),//
		ERROR_ENTRY(321, "Семантическая ошибка -> Арифметические операторы могут применяться только к целочисленными типам"),//
		ERROR_ENTRY(322, "Семантическая ошибка -> Логические операторы могут применяться только к целочисленному и логическому типами(типы должны совпадать)"),//
		ERROR_ENTRY(323, "Семантическая ошибка -> К строкам можно применять только оператор \"+\""),//
		ERROR_ENTRY(324, "Семантическая ошибка -> К bool можно применять только логическое равно/неравно"),//
		ERROR_ENTRY_NODEF(325), ERROR_ENTRY_NODEF(326),
		ERROR_ENTRY_NODEF(327), ERROR_ENTRY_NODEF(328), ERROR_ENTRY_NODEF(329),
		ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),
		ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF10(500), ERROR_ENTRY_NODEF10(510), ERROR_ENTRY_NODEF10(520), ERROR_ENTRY_NODEF10(530), ERROR_ENTRY_NODEF10(540),
		ERROR_ENTRY_NODEF10(550), ERROR_ENTRY_NODEF10(560), ERROR_ENTRY_NODEF10(570), ERROR_ENTRY_NODEF10(580), ERROR_ENTRY_NODEF10(590),
		ERROR_ENTRY(600, "Синтаксическая ошибка -> Неверная структура программы"),
		ERROR_ENTRY(601, "Синтаксическая ошибка -> Отсутствует список параметров функции при её объявлении"),
		ERROR_ENTRY(602, "Синтаксическая ошибка -> Ошибка в параметрах функции при её объявлении"),
		ERROR_ENTRY(603, "Синтаксическая ошибка -> Возможно отсутствует тело функции"),
		ERROR_ENTRY(604, "Синтаксическая ошибка -> Недопустимое выражение. Ожидаются только литералы и идентификаторы"),
		ERROR_ENTRY(605, "Синтаксическая ошибка -> Неверная конструкция в теле функции"),
		ERROR_ENTRY(606, "Синтаксическая ошибка -> Ошибка в условном выражении"),
		ERROR_ENTRY(607, "Синтаксическая ошибка -> Ошибка в вызове функции"),
		ERROR_ENTRY(608, "Синтаксическая ошибка -> Ошибка в арифметическом выражении"),
		ERROR_ENTRY(609, "Синтаксическая ошибка -> Ошибка в списке параметров при вызове функции"),
		ERROR_ENTRY(610, "Синтаксическая ошибка -> Неверная конструкция в условном выражении"),
		ERROR_ENTRY(611, "Синтаксическая ошибка -> Требуется закрывающаяся фигурная скобка"),
		ERROR_ENTRY(612, "Синтаксическая ошибка -> Требуется открывающаяся фигурная скобка"),
		ERROR_ENTRY_NODEF(613), ERROR_ENTRY_NODEF(614), ERROR_ENTRY_NODEF(615), ERROR_ENTRY_NODEF(616), ERROR_ENTRY_NODEF(617), ERROR_ENTRY_NODEF(618), ERROR_ENTRY_NODEF(619),
		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		if (id > 0 && id < ERROR_MAX_ENTRY)
			return errors[id];
		else
			return errors[0];
	}

	ERROR geterrorin(int id, int line, int position)
	{
		ERROR error = geterror(id);
		error.inext.position = position;
		error.inext.line = line;
		return error;
	}
}