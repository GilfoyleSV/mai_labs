#include <stdio.h>
#include "faq8.h"

int main(int argc, char *argv[]){
	if (argc < 3){
		fprintf(stderr, "gde??");
		return -52;
	}
	FILE* file1 = fopen(argv[1], "r");
	if (file1 == NULL){
		fprintf(stderr, "Unable to open first file");
		return -10;
	}
	FILE* file2 = fopen(argv[2], "wb");
	if (file2 == NULL){
		fprintf(stderr, "Unable to open second file");
		fclose(file1);
		return -20;
	}

	faq8_post row;
	faq8_header first_row;
	if (fscanf(file1, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]", first_row.theme, first_row.author, first_row.views, first_row.messages, first_row.timestamp, first_row.last_editor) == 6){
		fwrite(&first_row, sizeof(faq8_header), 1, file2);
	}
	while (6 == fscanf(file1, "%[^;];%[^;];%d;%d;%d;%s", row.theme, row.author, &row.views, &row.messages, &row.timestamp, row.last_editor)){
		fwrite(&row, sizeof(faq8_post), 1, file2);
	}
	fclose(file1);
	fclose(file2);
	printf("Complete\n");
	return 0;
}