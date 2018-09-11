#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <math.h>
#include "color.h"
#include "material.h"
#include "image.h"

int WindowPositionX = 100;  //��������E�B���h�E�ʒu��X���W
int WindowPositionY = 100;  //��������E�B���h�E�ʒu��Y���W
int WINDOW_W = 800;    //��������E�B���h�E�̕�
int WINDOW_H = 800;    //��������E�B���h�E�̍���
char WindowTitle[] = "���E�̎n�܂�";  //�E�B���h�E�̃^�C�g��
color_image4_t texture;
GLuint texture_id[8];
const char * texture_path[] =
{
	"img/kyousha.data",
	"img/keima.data",
	"img/gin.data",
	"img/kin.data",
	"img/ou.data",
	"img/hu.data",
	"img/kaku.data",
	"img/hisha.data"
};
//----------------------------------------------------
// �֐��v���g�^�C�v�i��ɌĂяo���֐����ƈ����̐錾�j
//----------------------------------------------------
void Initialize(void);
void Display(void);
void Ground(void);  //��n�̕`��
void initTexMode(GLenum tex_mode, GLint filter_mode, GLint wrap_mode, GLint env_mode)
{
	glTexParameteri(tex_mode, GL_TEXTURE_MAG_FILTER, filter_mode);
	glTexParameteri(tex_mode, GL_TEXTURE_MIN_FILTER, filter_mode);
	glTexParameteri(tex_mode, GL_TEXTURE_WRAP_S, wrap_mode);
	glTexParameteri(tex_mode, GL_TEXTURE_WRAP_T, wrap_mode);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, env_mode);
}
inline double scaler(int point, double base) {
	return (point - base);
}

void draw_koma() {
	glPushMatrix();

	glTranslated(0, 0, 10);
	glTranslated(9, 9, 0);
	glScaled(0.05, 0.05, 0.05);
	glColor3d(253/255.0 , 251/255.0 ,70/255.0);
	glRotated(180, 0, 0, 1);

	//����
	glBegin(GL_POLYGON);
	glVertex3d(180, 0, 0);
	glVertex3d(300, 40, 0);
	glVertex3d(360, 385, 0);
	glVertex3d(0, 385, 0);
	glVertex3d(40, 40, 0);
	glEnd();
	//���
	glBegin(GL_POLYGON);
	glVertex3d(180, 0, 30);
	glVertex3d(300, 40, 30);
	glVertex3d(360, 385, 30);
	glVertex3d(0, 385, 30);
	glVertex3d(40, 40, 30);
	glEnd();
	//�e�N�X�`��
	glTranslated(0, 0, 1);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(360, 40, 30);
	glTexCoord2d(0, 1);
	glVertex3d(360, 385, 30);
	glTexCoord2d(1, 1);
	glVertex3d(0, 385, 30);
	glTexCoord2d(1, 0);
	glVertex3d(0, 40, 30);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawboard() {
	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0);//�F�̐ݒ�
	glLineWidth(3);
	glTranslated(0, 0, 5);
	glScaled(18, 18, 1);
	glutSolidCube(10.0);//�����F(��ӂ̒���)
	glColor3d(0, 0, 0);//�F�̐ݒ�
	glutWireCube(10.01);
	double ground_max_x = 5.0;
	double ground_max_y = 5.0;
	glPushMatrix();
	glBegin(GL_LINES);
	for (int ly = 0; ly < 9; ly++) {
		glVertex3d(-ground_max_x, scaler(ly, ground_max_x)*1.11 + 0.5, 5.5);
		glVertex3d(ground_max_x, scaler(ly, ground_max_x)*1.11 + 0.5, 5.5);
	}
	for (int lx = 0; lx < 9; lx++) {
		glVertex3d(scaler(lx, ground_max_y)*1.11111 + 0.55, ground_max_y, 5.5);
		glVertex3d(scaler(lx, ground_max_y)*1.11111 + 0.55, -ground_max_y, 5.5);
	}
	glEnd();
	glLineWidth(1);
	glPopMatrix();
	glPopMatrix();
}
//----------------------------------------------------
// ���C���֐�
//----------------------------------------------------
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);//���̏�����
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//�E�B���h�E�̈ʒu�̎w��
	glutInitWindowSize(WINDOW_W, WINDOW_H); //�E�B���h�E�T�C�Y�̎w��
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//�f�B�X�v���C���[�h�̎w��
	glutCreateWindow(WindowTitle);  //�E�B���h�E�̍쐬
	glutDisplayFunc(Display); //�`�掞�ɌĂяo�����֐����w�肷��i�֐����FDisplay�j
	//glutReshapeFunc(resize);
	Initialize(); //�����ݒ�̊֐����Ăяo��
	glutMainLoop();
	return 0;
}
//----------------------------------------------------
// �����ݒ�̊֐�
//----------------------------------------------------
void Initialize(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// �B�ʏ����̗L��
	glEnable(GL_DEPTH_TEST);
	// �e�N�X�`���̓ǂݍ���
	glGenTextures(8, texture_id);
	for (int i = 0; i < 8; i++)
	{
		load_raw_image(&texture, texture_path[i]);
		glBindTexture(GL_TEXTURE_2D, texture_id[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.image);

		// �e�N�X�`���̊e��ݒ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	/* �e�N�X�`�����g��E�k��������@�̎w�� */
	glAlphaFunc(GL_GREATER, 0.7);
	gluPerspective(30.0, (double)WINDOW_W / (double)WINDOW_H, 0.1, 1000.0); //�������e�@�̎��̐�gluPerspactive(th, w/h, near, far);
	//initTexMode(GL_TEXTURE_2D, GL_LINEAR, GL_CLAMP, GL_MODULATE);
	gluLookAt(
		0.0, -200.0, 300.0, // ���_�̈ʒux,y,z;
		0.0, 0.0, 0.0,   // ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
		0.0, 0.0, 1.0);  //���E�̏�����̃x�N�g��x,y,z
}
//----------------------------------------------------
// �`��̊֐�
//----------------------------------------------------
void changescale(int index) {
	if (index == 4)return;
	if (index > 4)index = 8 - index;
	glScaled(0.7 + index * 0.05, 0.85 + index * 0.05, 1);
}
void set_koma() {
	glPushMatrix();
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			glTranslated(20, 0, 0);
			glPushMatrix();
			if (j == 0)
				//���̑�
				changescale(i);
			else
				//���p�̃p�����[�^
				glScaled(0.67, 0.8, 1);
			int index = i;
			if (index > 4)
				index = 8 - index;
			if (j != 0)
				index = 5;
			glBindTexture(GL_TEXTURE_2D, texture_id[index]);
			draw_koma();
			glPopMatrix();
		}
		glTranslated(-20 * 9, 20 * 2, 0);
	}
	glPopMatrix();
	glPushMatrix();
	//��Ԋp
	glTranslated(20 * 2, 20, 0);
	glBindTexture(GL_TEXTURE_2D, texture_id[6]);
	draw_koma();
	glTranslated(20 * 6, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture_id[7]);
	draw_koma();
	glPopMatrix();
}
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�o�b�t�@�̏���
	Ground();
	drawboard();

	//�R�}����ׂ� 
	glPushMatrix();
	//�����ɒ���
	glTranslated(-20 * 5, -20 * 4, 0);
	set_koma();
	glPopMatrix();
	glPushMatrix();
	glRotated(180, 0, 0, 1);
	//�����ɒ���
	glTranslated(-20 * 5, -20 * 4, 0);
	set_koma();

	glPopMatrix();
	glutSwapBuffers(); //glutInitDisplayMode(GLUT_DOUBLE)�Ń_�u���o�b�t�@�����O�𗘗p��
}
//----------------------------------------------------
// ��n�̕`��
//----------------------------------------------------
void Ground(void)
{
	double ground_max_x = 300.0;
	double ground_max_y = 300.0;
	glColor3d(0.8, 0.8, 0.8);  // ��n�̐F
	glBegin(GL_LINES);
	for (double ly = -ground_max_y; ly <= ground_max_y; ly += 10.0) {
		glVertex3d(-ground_max_x, ly, 0);
		glVertex3d(ground_max_x, ly, 0);
	}
	for (double lx = -ground_max_x; lx <= ground_max_x; lx += 10.0) {
		glVertex3d(lx, ground_max_y, 0);
		glVertex3d(lx, -ground_max_y, 0);
	}
	glEnd();
}