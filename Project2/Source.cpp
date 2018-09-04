#include <GL/glut.h>
#include <stdio.h>
int WindowPositionX = 100;  //生成するウィンドウ位置のX座標
int WindowPositionY = 100;  //生成するウィンドウ位置のY座標
int WINDOW_W = 800;    //生成するウィンドウの幅
int WINDOW_H = 800;    //生成するウィンドウの高さ
char WindowTitle[] = "世界の始まり";  //ウィンドウのタイトル

//----------------------------------------------------
// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
//----------------------------------------------------
void Initialize(void);
void Display(void);
void Ground(void);  //大地の描画

inline int scaler(int point, int base) {
	return (point - base);
}
void draw_koma() {
	glPushMatrix();
	glTranslated(0, 0, 10);
	glTranslated(9, 9, 0);
	glScaled(0.05, 0.05, 0.05);
	glColor3d(1, 0, 0);
	glRotated(180, 0, 0, 1);

	//下面
	glBegin(GL_POLYGON);
	glVertex3d(180, 0, 0);
	glVertex3d(300, 40, 0);
	glVertex3d(360, 385, 0);
	glVertex3d(0, 385, 0);
	glVertex3d(40, 40, 0);
	glEnd();

	//上面
	glBegin(GL_POLYGON);
	glVertex3d(180, 0, 30);
	glVertex3d(300, 40, 30);
	glVertex3d(360, 385, 30);
	glVertex3d(0, 385, 30);
	glVertex3d(40, 40, 30);
	glEnd();
	glPopMatrix();
}
void drawboard() {
	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0);//色の設定
	glLineWidth(3);
	glTranslated(0, 0, 5);
	glScaled(18, 18, 1);
	glutSolidCube(10.0);//引数：(一辺の長さ)
	glColor3d(0, 0, 0);//色の設定
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
// メイン関数
//----------------------------------------------------
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);//環境の初期化
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//ウィンドウの位置の指定
	glutInitWindowSize(WINDOW_W, WINDOW_H); //ウィンドウサイズの指定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定
	glutCreateWindow(WindowTitle);  //ウィンドウの作成
	glutDisplayFunc(Display); //描画時に呼び出される関数を指定する（関数名：Display）
	//glutReshapeFunc(resize);
	Initialize(); //初期設定の関数を呼び出す
	glutMainLoop();
	return 0;
}
//----------------------------------------------------
// 初期設定の関数
//----------------------------------------------------
void Initialize(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //背景色
	glEnable(GL_DEPTH_TEST);//デプスバッファを使用：glutInitDisplayMode() で GLUT_DEPTH を指定する

	gluPerspective(30.0, (double)WINDOW_W / (double)WINDOW_H, 0.1, 1000.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);

	gluLookAt(
		0.0, -200.0, 300.0, // 視点の位置x,y,z;
		0.0, 0.0, 0.0,   // 視界の中心位置の参照点座標x,y,z
		0.0, 0.0, 1.0);  //視界の上方向のベクトルx,y,z
}
//----------------------------------------------------
// 描画の関数
//----------------------------------------------------
void set_koma() {
	glPushMatrix();
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			glTranslated(20, 0, 0);
			draw_koma();
		}
		glTranslated(-20 * 9, 20 * 2, 0);
	}
	glPopMatrix();
}
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //バッファの消去
	Ground();
	drawboard();

	//コマを並べる
	//
	glPushMatrix();
	//左下に調整
	glTranslated(-20 * 5, -20 * 4, 0);
	set_koma();
	glPopMatrix();
	glPushMatrix();
	glRotated(180, 0, 0, 1);
	//左下に調整
	glTranslated(-20 * 5, -20 * 4, 0);
	set_koma();
	glPopMatrix();
	glutSwapBuffers(); //glutInitDisplayMode(GLUT_DOUBLE)でダブルバッファリングを利用可
}
//----------------------------------------------------
// 大地の描画
//----------------------------------------------------
void Ground(void)
{
	double ground_max_x = 300.0;
	double ground_max_y = 300.0;
	glColor3d(0.8, 0.8, 0.8);  // 大地の色
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
