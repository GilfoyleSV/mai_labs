#ifndef FAQ8_H
#define FAQ8_H

#define MAX_LENGHT_THEME 98
#define MAX_LENGHT_AUTHOR 21
#define MAX_LENGHT_LAST_EDITOR 7

typedef struct {
	char theme[MAX_LENGHT_THEME];
	char author[MAX_LENGHT_AUTHOR];
	int views;
	int messages;
	unsigned long long timestamp;
	char last_editor[MAX_LENGHT_LAST_EDITOR];
} faq8_post;

typedef struct {
	char theme[5];
	char author[6];
	char views[5];
	char messages[8];
	char timestamp[9];
	char last_editor[11];
} faq8_header;

#endif