#pragma once
#define MAX_IMAGE_SIZE 512

//typedef struct {
//	unsigned char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE][3];
//	int width;
//	int height;
//} color_image3_t;

typedef struct {
	unsigned char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE][4];
	//unsigned char subimages[6][MAX_IMAGE_SIZE][MAX_IMAGE_SIZE][4];
	int width;
	int height;
	//int subwidth;
	//int subheight;
} color_image4_t;

//void load_ppm_image(color_image3_t *img, char filepath[]) {
//	FILE *fp = fopen(filepath, "rb");
//	if (fp == NULL) {
//		printf("file read error!\n");
//		exit(-1);
//	}
//	char buf[MAX_IMAGE_SIZE];
//	fgets(buf, MAX_IMAGE_SIZE, fp);
//	if (buf[0] != 'P' || buf[1] != '6') {
//		printf("file format error!\n");
//		exit(-1);
//	}
//	int width, height;
//	while (true) {
//		fgets(buf, MAX_IMAGE_SIZE, fp);
//		if (buf[0] == '#') continue;
//		sscanf(buf, "%d %d", &width, &height);
//		break;
//	}
//	while (true) {
//		fgets(buf, MAX_IMAGE_SIZE, fp);
//		if (buf[0] == '#') continue;
//		if (buf[0] != '2' || buf[1] != '5' || buf[2] != '5') {
//			printf("file format error!\n");
//			exit(-1);
//		}
//		break;
//	}
//	if (width > MAX_IMAGE_SIZE || height > MAX_IMAGE_SIZE) {
//		printf("file size error!\n");
//		exit(-1);
//	}
//	img->width = width;
//	img->height = height;
//	for (int y = 0; y < height; y++) {
//		for (int x = 0; x < width; x++) {
//			for (int c = 0; c < 3; c++) {
//				img->image[y][x][c] = (unsigned char)fgetc(fp);
//			}
//		}
//	}
//	fclose(fp);
//}

void load_raw_image(color_image4_t *img,const char filepath[]) {
	FILE *fp;
	fopen_s(&fp,filepath, "rb");
	if (fp == NULL) {
		printf("file read error!\n");
		exit(-1);
	}
	int size = fread(img->image, 1, sizeof img->image, fp);
	img->width = (int)sqrt(size/4.0);
	img->height = (int)sqrt(size/4.0);
	fclose(fp);
}
