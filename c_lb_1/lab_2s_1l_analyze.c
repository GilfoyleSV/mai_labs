#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "faq8.h"
#include <stdbool.h>


int main(int argc, char *argv[]){
    if (argc < 2){
        printf("gde?");
        return -2;
    }
    FILE* file = fopen(argv[1], "rb");
    if (file == NULL){
        printf("Error with opening file");
        fclose(file);
        return -3;
    }
    faq8_post row;
    int count_post = 0;
    long long int count_views = 0;
    long int max_delta = 0;
    faq8_post first_post;
    faq8_post second_post;
    int count_read;
	while (fread(&row, sizeof(faq8_post), 1, file) == 1){
        count_views += row.views;
        count_post += 1;
        FILE* file2 = fopen(argv[1], "rb");
        if (file2 == NULL){
            printf("Error with opening file");
            fclose(file2);
            fclose(file);
            return -22;
        }

        faq8_post second_row;
        long current_pos = ftell(file);
        if (current_pos == -1L) {
            fprintf(stderr, "Error getting file position\n");
            fclose(file2);
            fclose(file);
            return -23;
        }

        if (fseek(file2, current_pos, SEEK_SET) != 0) {
            fprintf(stderr, "Error seeking in file\n");
            fclose(file2);
            fclose(file);
            return -24;
        } 
        while (fread(&second_row, sizeof(faq8_post), 1, file2) == 1){
            long int delta_views = abs(row.views - second_row.views);
            if (delta_views > max_delta){
                first_post = row;
                second_post = second_row;
                max_delta = delta_views;
            }
        }

        fclose(file2);
    }

    fclose(file);
    printf("Max delta views between 2 posts: %ld\n", max_delta);
    printf("First post\n------\nTitle %s\nViews %d\n------\n", first_post.theme, first_post.views);
    printf("Second post\n------\nTitle %s\nViews %d\n------\n", second_post.theme, second_post.views);
    printf("Total views of all posts: %lld\n", count_views);
    printf("Number of posts: %d\n", count_post);
}
