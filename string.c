#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "string.h"

String NewString(const char *p) {
	if(!p)
		return (String){ .data = (char *)malloc(1), .idx = 0 };

	String s = {
		.data 			= (!p ? NULL : strdup(p)),
		.idx 			= (!p ? 0 : strlen(p)),

		.FindChar		= String__FindChar,
		.FindCharAt		= String__FindCharAt,
		.CountChar		= String__CountChar,
		.Trim			= String__Trim,
		.Strip			= String__Strip,

		.AppendString	= String__AppendString
	};

	return s;
}

int String__FindChar(String *s, const char ch) {
	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch)
			return i;
	}

	return -1;
}

int String__FindCharAt(String *s, const char ch, int match_count) {
	int count = 0;
	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch)
			count++;

		if(s->data[i] == ch && match_count == i)
			return i;
	}

	return -1;
}

int String__CountChar(String *s, const char ch) {
	int count = 0;
	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch)
			count++;

	}

	return count;
}

int String__Trim(String *s, const char ch) {
	if(!s)
		return 0;

	int found = 0, idx = 0;
	char *new = (char *)malloc(1);

	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch) {
			found = 1;
			continue;
		}

		new[idx] = s->data[i];
		idx++;
		new = (char *)realloc(new, idx + 1);
	}

	new[idx] = '\0';
	free(s->data);
	s->data = new;
	s->idx = strlen(new);

	return found;
}

int String__Strip(String *s) {
	if(!s || !s->data) return 0;

	int start = 0;
	while(isspace(s->data[start])) start++;

	int end = strlen(s->data) - 1;
	while(isspace(s->data[end])) end--;

	int new_len = end - start + 2;
	char *new = (char *)malloc(new_len);
	if(!new)
		return 0;

	memset(new, '\0', new_len);
	for(int i = 0; i < new_len; i++)
		new[i] = s->data[start + i];


	new[strlen(new) - 1] = '\0';
	free(s->data);
	s->data = strdup(new);
	s->idx = strlen(new);

	return 1;
}

void String__ReplaceChar(String *s, const char ch, const char *data) {
	char *new = (char *)malloc(s->idx);
	int idx = 0;

	for(int i = 0; i < s->idx; i++) {
		if(!s->data[i])
			break;

		if(s->data[i] == ch) {
			for(int chr = 0; chr < (int)strlen(data); chr++) {
				new[idx] = data[chr];
				idx++;
				if((i + chr) > s->idx)
					new = (char *)realloc(new, idx + 1);
			}
		}

		new[idx] = s->data[i];
		idx++;
		if(i > s->idx)
			new = (char *)realloc(new, idx + 1);
	}

	new[idx] = '\0';
	free(s->data);
	s->data = new;
	s->idx = strlen(new);
}

int String__AppendString(String *s, const char *data) {
	if(!s)
		return 0;

	if(!data)
		return 0;

	for(int i = 0; i < strlen(data); i++) {
		s->data[s->idx] = data[i];
		s->idx++;
		s->data = (char *)realloc(s->data, s->idx + 1);
	}
	return 1;
}
