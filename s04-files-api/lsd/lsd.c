#include <stdio.h>

int parseChar(FILE* f, int c) {
	int x = fgetc(f);
	if (x == EOF)
		return -1;
	if (x != c)
		return -1;
	return 0;
}

int parseChars(FILE* f, const char* str) {
	for (const char* c = str; *c != 0; c++) {
		if (parseChar(f, *c) != 0)
			return -1;
	}
	return 0;
}

int parseInt(FILE* f, int* r) {
	int c0 = fgetc(f);
	if (c0 == EOF)
		return -1;
	int c1 = fgetc(f);
	if (c1 == EOF)
		return -1;
	int c2 = fgetc(f);
	if (c2 == EOF)
		return -1;
	int c3 = fgetc(f);
	if (c3 == EOF)
		return -1;
	*r = (c0 << 24) | (c1 << 16) | (c2 << 8) | c3;
	return 0;
}
	

int parsePNG(FILE* f, int* width, int* height) {
	if (parseChar(f, 137) != 0)
		return -1;
	if (parseChars(f, "PNG\r\n") != 0)
		return -2;
	if (parseChar(f, 26) != 0)
		return -3;
	if (parseChar(f, '\n') != 0)
		return -4;
	int len;
	if (parseInt(f, &len) != 0)
		return -5;
	if (len < 12)
		return -6;
	if (parseChars(f, "IHDR") != 0)
		return -7;
	if (parseInt(f, width) != 0)
		return -8;
	if (parseInt(f, height) != 0)
		return -9;
	return 0;
}

int main(int argc, const char* argv[]) {
	for (int i = 1; i < argc; i++) {
		const char* filename = argv[i];
		FILE* f = fopen(filename, "r");
		if (f == NULL) {
			fprintf(stderr, "eroare deschiderea fisierului %s\n", filename);
			return -1;
		}
		int w = 0, h = 0;
		int r = parsePNG(f, &w, &h);
		if (r != 0)
			fprintf(stderr, "%s error=%d\n", filename, r);
		else
			printf("%s %dx%d\n", filename, w, h); 
		fclose(f);
	}
	return 0;
}
