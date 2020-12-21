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

int print_file(const char* file_name, int series_length) {
	FILE* f;
	char c = '1';
	int length_f = 0;
	printf("\n");
	f = fopen(file_name, "r");
	check_file(f);
	int remaining_length_2 = 0;
	printf(file_name);
	printf(": ");
	while ((c = fgetc(f)) != EOF) {
		while (c != ' ' && c != EOF) {
			printf("%c", c);
			c = fgetc(f);

		}
		length_f++;
		remaining_length_2++;
		if (remaining_length_2 == series_length) {
			printf("|");
			remaining_length_2 = 0;
		}
		printf("%c", c);
		c = fgetc(f);
		if (c == EOF && remaining_length_2 != 0)
			printf("|");
		printf("%c", c);
	}
	fclose(f);
	return length_f;
	
}



void _2phase_sort() {
	FILE* f, * g, * t;
	char g_file[100], t_file[100], c = '1';
	int series_length = 1, series_length_1_file, series_length_2_file;
	int x2, x3;
	int length_2_file = 0, length_3_file = 0, length_1_file = 2;
	int remaining_length, remaining_length_2;
	int flag_2 = 1, flag_3 = 1;
	while (series_length < length_1_file) {
		
		f = fopen("1.txt", "r");
		check_file(f);
		g = fopen("2.txt", "w");
		check_file(g);
		t = fopen("3.txt", "w");
		check_file(t);

		// фаза разделения
		while (flag_2 != -1 && flag_3 != -1) {
			series_length_1_file = series_length;
			series_length_2_file = series_length;
			while (series_length_1_file > 0 && flag_2 != -1) {
				flag_2 = fscanf(f, "%s", g_file);
				fprintf(g, "%s ", g_file);
				series_length_1_file--;
				length_2_file++;
			}
			while (series_length_2_file > 0 && flag_3 != -1) {
				flag_3 = fscanf(f, "%s", t_file);
				if (flag_3 == -1) break;
				fprintf(t, "%s ", t_file);
				series_length_2_file--;
				length_3_file++;
			}
		}
		fclose(g);
		fclose(t);
		fclose(f);

		length_1_file = (length_2_file + length_3_file);
		print_file("2.txt", series_length);
		print_file("3.txt", series_length);
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


		printf("\nf: ");
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
		flag_2 = 1;
		flag_3 = 1;
	}
}

void main() {

	// двухфазная сортировка слиянием (списана у Фадеева Максима) рефакторинг @Smarandii

	FILE* f;
	int f_length = 0;
	
	make_file_copy("f.txt");
	f_length = print_file("f.txt");

	_2phase_sort();

}