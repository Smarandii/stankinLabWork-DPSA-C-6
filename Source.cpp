#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>


void check_file_errors(FILE* f) {
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
	check_file_errors(f);
	check_file_errors(copy);

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
	check_file_errors(f);
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
	check_file_errors(f);
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
	char g_digit[100], t_digit[100];
	int series_length = 1, series_length_2_file, series_length_3_file;
	int x2, x3;
	int series_counter = 0;
	int flag_2 = 1;
	int flag_3 = 1;
	while (series_counter != 1) {

		series_counter = 0;
		f = fopen("1.txt", "r");
		check_file_errors(f);
		g = fopen("2.txt", "w");
		check_file_errors(g);
		t = fopen("3.txt", "w");
		check_file_errors(t);

		while (flag_2 != -1 && flag_3 != -1) {
			series_length_2_file = series_length;
			series_length_3_file = series_length;
			while (series_length_2_file > 0 && flag_2 != -1) {
				flag_2 = fscanf(f, "%s", g_digit);
				if (flag_2 != -1) fprintf(g, "%s ", g_digit);
				series_length_2_file--;
			}

			while (series_length_3_file > 0 && flag_3 != -1) {
				flag_3 = fscanf(f, "%s", t_digit);
				if (flag_3 != -1) fprintf(t, "%s ", t_digit);
				series_length_3_file--;
			}
			printf("\n%s %s", g_digit, t_digit);
			
		}

		fclose(g);
		fclose(t);
		fclose(f);


		print_file("2.txt", series_length);
		print_file("3.txt", series_length);

		f = fopen("1.txt", "w");
		check_file_errors(f);
		g = fopen("2.txt", "r");
		check_file_errors(g);
		t = fopen("3.txt", "r");
		check_file_errors(t);

		
		flag_2 = fscanf(g, "%s", g_digit);
		flag_3 = fscanf(t, "%s", t_digit);
		
		x2 = atoi(g_digit);
		x3 = atoi(t_digit);

		printf("\nf: ");
		while (flag_2 != -1 && flag_3 != -1)
		{
			series_length_2_file = series_length;
			series_length_3_file = series_length;
			while (series_length_2_file > 0 && series_length_3_file > 0) {
				if (x2 >= x3) 
				{
					fprintf(f, "%s ", t_digit);
					printf("%s ", t_digit);
					flag_3 = fscanf(t, "%s", t_digit);
					x3 = atoi(t_digit);
					series_length_3_file--;
				}
				else 
				{
					fprintf(f, "%s ", g_digit);
					printf("%s ", g_digit);
					flag_2 = fscanf(g, "%s", g_digit);
					x2 = atoi(g_digit);
					series_length_2_file--;
				}
			}
			if (series_length_2_file != 0 && flag_2 != -1)
				while (series_length_2_file > 0 && flag_2 != -1) {
					fprintf(f, "%s ", g_digit);
					printf("%s ", g_digit);
					flag_2 = fscanf(g, "%s", g_digit);
					x2 = atoi(g_digit);
					series_length_2_file--;
					if ((series_length_3_file == 0 && series_length_2_file == 0) || flag_2 == -1 || flag_3 == -1) {
						printf("|");
						series_counter++;
					}
				}
			else if (series_length_3_file != 0 && flag_3 != -1)
				while (series_length_3_file > 0 && flag_3 != -1) 
				{
					fprintf(f, "%s ", t_digit);
					printf("%s ", t_digit);
					flag_3 = fscanf(t, "%s", t_digit);
					x3 = atoi(t_digit);
					series_length_3_file--;
					if ((series_length_3_file == 0 && series_length_2_file == 0) || flag_2 == -1 || flag_3 == -1) {
						printf("|");
						series_counter++;
					}
				}

			if (flag_2 == -1 && flag_3 == 1) { flag_3 = fscanf(t, "%s", t_digit); fprintf(f, "%s ", t_digit); printf("%s ", t_digit); printf("|"); series_counter++; }
			else if (flag_2 == 1 && flag_3 == -1) { flag_2 = fscanf(g, "%s", g_digit); fprintf(f, "%s ", g_digit); printf("%s ", g_digit); printf("|"); series_counter++; }
	
		}
		printf("\n");
		series_length *= 2;
		printf("\n%d\n", series_length);
		printf("\n%d\n", series_counter);
		fclose(f);
		fclose(g);
		fclose(t);
		flag_2 = 1;
		flag_3 = 1;
	}
}

void main() {
	FILE* f;
	int f_length = 0;
	
	make_file_copy("f.txt");
	f_length = print_file("f.txt");

	_2phase_sort();

}