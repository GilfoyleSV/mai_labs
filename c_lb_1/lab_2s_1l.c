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
    char header_line[256];
    if (!fgets(header_line, sizeof(header_line), file1)) {
        fprintf(stderr, "Empty file\n");
        fclose(file1);
        fclose(file2);
        return -4;
    }
	// while (6 == fscanf(file1, "%190[^;];%21[^;];%d;%d;%lld;%20s\n", row.theme, row.author, &row.views, &row.messages, &row.timestamp, row.last_editor)){
	// 	fwrite(&row, sizeof(faq8_post), 1, file2);
	//        printf("%s %s %d %d %lld %s", row.theme, row.author, row.views, row.messages, row.timestamp, row.last_editor);
	//        printf("1\n");
	// }
    while (1== 1){
        int read_fields = fscanf(file1, "%190[^;];%21[^;];%d;%d;%lld;%20s\n",
                            row.theme, row.author, &row.views, &row.messages, 
                            &row.timestamp, row.last_editor);

        if (read_fields != 6) {
            // Выводим информацию о том, что удалось считать
            printf("Ошибка чтения! Считано %d/6 полей:\n", read_fields);
            
            if (read_fields >= 1) printf("  theme: '%s'\n", row.theme);
            else printf("  theme: НЕ СЧИТАНО\n");
            
            if (read_fields >= 2) printf("  author: '%s'\n", row.author);
            else printf("  author: НЕ СЧИТАНО\n");
            
            if (read_fields >= 3) printf("  views: %d\n", row.views);
            else printf("  views: НЕ СЧИТАНО\n");
            
            if (read_fields >= 4) printf("  messages: %d\n", row.messages);
            else printf("  messages: НЕ СЧИТАНО\n");
            
            if (read_fields >= 5) printf("  timestamp: %lld\n", row.timestamp);
            else printf("  timestamp: НЕ СЧИТАНО\n");
            
            if (read_fields >= 6) printf("  last_editor: '%s'\n", row.last_editor);
            else printf("  last_editor: НЕ СЧИТАНО\n");
            break;}
        printf("%s %s %d %d %lld %s\n", row.theme, row.author, row.views, row.messages, row.timestamp, row.last_editor);

    }
	fclose(file1);
	fclose(file2);
	printf("Complete\n");
	return 0;
}
