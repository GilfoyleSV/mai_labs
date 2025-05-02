#include <stdio.h>
#include "faq8.h"

int main(int argc, char *argv[]){
	if (argc < 3){
		fprintf(stderr, "gde??");
		return -52;
	}
	FILE* file1 = fopen(argv[1], "rb");
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
    char header_line[256];
    if (!fgets(header_line, sizeof(header_line), file1)) {
        fprintf(stderr, "Empty file\n");
        fclose(file1);
        fclose(file2);
        return -4;
    }
    int count_read;
	while ((count_read = fscanf(file1, "%[^;];%[^;];%d;%d;%lld;%s\n", row.theme, row.author, &row.views, &row.messages, &row.timestamp, row.last_editor)) != EOF){
        if (count_read < 6){
            fprintf(stderr, "not all columns of the row are read\n");
            printf("%s\n", row.theme);
            fclose(file1);
            fclose(file2);
            return -5;
        }
		if (!fwrite(&row, sizeof(faq8_post), 1, file2)){
            fprintf(stderr, "not all columns of the row are write\n");
            fclose(file1);
            fclose(file2);
            return -6;
        }
	}

	fclose(file1);
	fclose(file2);
	printf("Complete\n");
	return 0;
}
