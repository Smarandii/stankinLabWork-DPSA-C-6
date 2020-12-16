// Внешние сортировки  работают с файлами
//
// Серия - отсортированная подпоследовательность элементов.
// Сортировки слиянием объединяют две или более последовательности в одну серию:
//
// Двух-фазная сортировка прямым слиянием.  
// 3 файла: f, g, t
// из f формируются файлы g, t (исходный файл f скопировать для сохранности)
// из g, t формируется f 
// f - 279 58 -1 7 29 45 8
// g - 279 | -1 | 29 | 8
// t - 58 | 7 | 45 |
// фаза слияния:
// сравниваем числа из t и g, меньшее записываем в f
// f - 58 279 | -1 7 | 29 45 | 8
// повторяем цикл сначала, пока в файле f не останется 1 серия.
//
// g - 58 279 | 29 45 |
// t - -1 7 | 8
// --------------------
// f - -1 7 58 279 | 8 29 45 |
// --------------------
// g - -1 7 58 279 |
// t - 8 29 45 |
// --------------------
// f - -1 7 8 29 45 58 279
//
// Однофазная сортировка прямым слиянием:
// получена слиянием двух фаз двузфазной сортировки
// 5 файлов: f, f1, f2, g1, g2,
// 1. читаем по 1 серии из f1 и f2
// 2. сливаем эти серии
// 3. присоединяем результирующую серию к одному из файлов g1 и g2 (они организованны в виде серий длинной в 2k) при этом переключаемся поочередно между g1 g2. хвост сливается с последней из созданных серий
// 4. опустошаем f1 f2
// 5. выполняем шаги 1-4 меняя файлы f1 на g1 f2 на g2 пока не получим файл из одной серии
//
// f - 279 58 -1 7 29 45 8
// ------------------
// f1 - 279 | -1 | 29 | 8
// f2 - 58 | 7 | 45
// g1 - 58 279 | 29 45
// g2 - -1 7 | 8
// ------------------
// f1 -1 7 58 279 | 
// f2 - 8 29 45 |
// g1 - -1 7 8 29 45 58 279
// g2 - ...
//
// при прямом слиянии мы теряем преимущество от изначально отсортированых данных, так как разделяем а потом вновь сливаем их
//
// Сортировка естественным слиянием:
// Сортировка при которой сливаются две самые длинные серии
// 3 файла: f, g, t
//
// 1. из f серии попеременно распределяются в файл g и t
// 2. из g и t серии сливаются в f
// процесс заканчивается как только в файле f останется 1 серия
//
// f - 279 58 -1 7 29 45 8
// --------------------
// g - 279 | -1 7 29 45 
// t - 58 | 8 
// f - 58 279 | -1 7 8 29 45
// --------------------
// g - 58 279 |
// t - -1 7 8 29 45 |
// f - -1 7 8 29 45 58 279 
//
// ускорение сортировок прямым слиянием:
// для ускорения считываем группы из k записей, сортируем их в оперативной памяти, отсортированные записи записать в файлы в виде серии длинны k 
// временные затраты пропорциональны числу требуемых проходов по файлам, следовательно надо стремиться сократить кол-во обращений к файлам
//
// Задание по лабе:
// знать теорию по 3 методам сортировки
// на оценку 4 два метода внешней сортировки

#include <iostream>
#include <fstream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <iostream>

void check_file(FILE* f) {
	if (f == NULL) { printf("\n[!]Can't open the file[!]\n"); exit(1); }
}

void make_file_copy(const char* file_name) {
	// перед сортировкой делаем копию, чтобы случайно не попортить данные 
	FILE* f, *copy;
	const char* copy_file_name = "1.txt";
	char tmp[] = "1";
	char c = 't';
	f = fopen(file_name, "r");
	copy = fopen(copy_file_name, "w");
	check_file(f);
	check_file(copy);

	while (c != EOF) {
		c = fgetc(f);
		if (c != ' ' && c != EOF) {
			tmp[0] = c;
			fprintf(copy, tmp);
		}
		if (c == ' ') fprintf(copy, " ");
	}
	fclose(f);
	fclose(copy);
}

int print_file(const char* file_name) {
	FILE* f;
	int file_length = 0;
	char c = '1';
	f = fopen(file_name, "r");
	check_file(f);
	printf(file_name);
	printf(": ");
	while (c != EOF) {
		while (c != ' ' && c != EOF) {
			c = fgetc(f);
			printf("%c", c);
		}
		file_length++;
		while (c == ' ')
			c = fgetc(f);
		printf("%c", c);
	}
	fclose(f);
	return file_length;
}

void _2phase_sort(int length_1_file) {
	FILE* f, * g, * t;
	char g_file[100], t_file[100], c = '1';
	int series_length = 1, series_length_1_file, series_length_2_file;
	int x2, x3;
	int length_2_file = 0, length_3_file = 0;
	int remaining_length, remaining_length_2;
	while (series_length < length_1_file) {
		
		printf("\niteration\n");
		f = fopen("1.txt", "r");
		check_file(f);

		g = fopen("2.txt", "w");
		check_file(g);

		t = fopen("3.txt", "w");
		check_file(t);


		// фаза разделения
		remaining_length = length_1_file;
		while (remaining_length > 0) {
			series_length_1_file = series_length;
			series_length_2_file = series_length;
			if (remaining_length > 0) {
				while (series_length_1_file > 0 && remaining_length > 0) {
					fscanf(f, "%s", g_file);
					fprintf(g, "%s", g_file);
					fprintf(g, " ");
					remaining_length--;
					series_length_1_file--;
				}
			}
			if (remaining_length > 0) {
				while (series_length_2_file > 0 && remaining_length > 0) {
					fscanf(f, "%s", t_file);
					fprintf(t, "%s", t_file);
					fprintf(t, " ");
					remaining_length--;
					series_length_2_file--;
				}
			}
		}
		fclose(g);
		fclose(t);
		fclose(f);

		// вывод файла g.txt
		printf("\n");
		g = fopen("2.txt", "r");
		check_file(g);
		remaining_length_2 = 0;
		printf("g: ");
		while ((c = fgetc(g)) != EOF) {
			while (c != ' ' && c != EOF) {
				printf("%c", c);
				c = fgetc(g);

			}
			length_2_file++;
			remaining_length_2++;
			if (remaining_length_2 == series_length) {
				printf("|");
				remaining_length_2 = 0;
			}
			printf("%c", c);
			c = fgetc(g);
			if (c == EOF && remaining_length_2 != 0)
				printf("|");
			printf("%c", c);
		}
		fclose(g);

		// вывод файла t.txt
		printf("\n");
		t = fopen("3.txt", "r");
		check_file(t);
		printf("t: ");
		remaining_length_2 = 0;
		while ((c = fgetc(t)) != EOF) {
			while (c != ' ' && c != EOF) {
				printf("%c", c);
				c = fgetc(t);

			}
			length_3_file++;
			remaining_length_2++;
			if (remaining_length_2 == series_length) {
				printf("|");
				remaining_length_2 = 0;
			}
			printf("%c", c);
			c = fgetc(t);
			if (c == EOF && remaining_length_2 != 0)
				printf("|");
			printf("%c", c);

		}
		printf("\n");
		fclose(t);

		f = fopen("1.txt", "w");
		check_file(f);
		g = fopen("2.txt", "r");
		check_file(g);
		t = fopen("3.txt", "r");
		check_file(t);

		remaining_length = length_1_file;
		fscanf(g, "%s", g_file);
		fscanf(t, "%s", t_file);
		x2 = atoi(g_file);
		x3 = atoi(t_file);

		// фаза слияния
		printf("f: ");
		while (remaining_length > 0) {
			series_length_1_file = series_length;
			series_length_2_file = series_length;
			while (series_length_1_file > 0 && series_length_2_file > 0 && remaining_length > 0 && length_2_file > 0 && length_3_file > 0) {
				if (x2 >= x3) {
					fprintf(f, "%s", t_file);
					fprintf(f, " ");
					printf("%s ", t_file);
					fscanf(t, "%s", t_file);
					x3 = atoi(t_file);
					remaining_length--;
					series_length_2_file--;
					length_3_file--;
				}
				else {
					fprintf(f, "%s", g_file);
					fprintf(f, " ");
					printf("%s ", g_file);
					fscanf(g, "%s", g_file);
					x2 = atoi(g_file);
					remaining_length--;
					series_length_1_file--;
					length_2_file--;
				}
			}
			if (series_length_1_file != 0 && length_2_file != 0)
				while (series_length_1_file > 0 && remaining_length > 0) {
					fprintf(f, "%s", g_file);
					fprintf(f, " ");
					printf("%s ", g_file);
					fscanf(g, "%s", g_file);
					x2 = atoi(g_file);
					remaining_length--;
					series_length_1_file--;
					if ((series_length_2_file == 0 && series_length_1_file == 0) || remaining_length == 0)
						printf("|");
					length_2_file--;
				}
			else
				if (series_length_2_file != 0 && remaining_length > 0 && length_3_file != 0)
					while (series_length_2_file > 0 && remaining_length > 0) {
						fprintf(f, "%s", t_file);
						fprintf(f, " ");
						printf("%s ", t_file);
						fscanf(t, "%s", t_file);
						x3 = atoi(t_file);
						remaining_length--;
						series_length_2_file--;
						if ((series_length_2_file == 0 && series_length_1_file == 0) || remaining_length == 0)
							printf("|");
						length_3_file--;
					}
		}

		length_2_file = 0;
		length_3_file = 0;
		printf("\n");
		series_length *= 2;
		fclose(f);
		fclose(g);
		fclose(t);
	}
}

void main() {

	// двухфазная сортировка слиянием (списана у Фадеева Максима) рефакторинг @Smarandii

	FILE* f;
	int f_length = 0;
	
	make_file_copy("f.txt");
	f_length = print_file("f.txt");

	_2phase_sort(f_length);

}