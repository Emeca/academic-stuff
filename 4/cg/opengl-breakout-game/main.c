#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define ESC 27

#define FALSE 0
#define TRUE 1

#define WIDTH 800
#define HEIGHT 600
#define X_INI 0
#define X_END 1
#define Y_INI 2
#define Y_END 3
#define X_CENTER 4
#define Y_CENTER 5

#define YELLOW "\033[01;33m"
#define RED "\033[01;31m"
#define GREEN "\033[01;32m"
#define BLUE "\033[01;34m"
#define MAGENTA "\033[01;35m"
#define WHITE "\033[01;37m"
#define BLACK "\033[01;30m"
#define NEUTRAL "\033[00m"

#define DOWN 0
#define UP 1
#define RIGHT 10
#define LEFT 11

#define AMAX 90
#define AMIN 10
#define MAX 50

#define UNUSED(x) (void)(x)

struct string
{
	char *str;
};

struct color
{
	float r;
	float g;
	float b;
	float a;
};

struct point
{
	float x;
	float y;
	float z;
};

struct box
{
	struct point *pos;
	struct point *scale;
	struct color *color_border;
	struct color *color_fill;
	int size;
	int filled;
	int active;
};

struct sphere
{
	struct point *pos;
	struct point *scale;
	struct color *color_border;
	struct color *color_fill;
	int filled;
};

struct game
{
	int width;
	int height;
	int kills;
	int lives;
	struct string *name;
	int x;
	int y;
	int fullscreen;
	int ball_angulo;
	int ball_v_direction;
	int ball_h_direction;
	float ball_speed_up;
	float ball_speed;
	int n_blocks;
	int pause;
};

struct camera
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	float zoom;
};

static void ctrl_reshape(int width, int height);
float box_get(struct box *box, int opt);
void show_score();
void show_game_score();
void show_game_end();
void show_game_help();
void show_msg(char *str);

struct box *_player = NULL;
struct game *_game = NULL;
struct camera *_camera = NULL;
struct box *_border = NULL;
struct box *_score = NULL;
struct box *_block_1 = NULL;
struct box *_ball = NULL;
float x, y;
struct box *ga_blocks[MAX];
float ORTO;

void
show_msg(char *str)
{
	printf("%sUHETBALL:%s %s%s%s", BLUE, NEUTRAL, GREEN, str, NEUTRAL);
}

struct string *
string_new(char *str)
{
	struct string *string = NULL;
	char *s = (char *)malloc(sizeof(char[strlen(str) + 1]));

	string = malloc(sizeof(struct string));
	strcpy(s, str);
	string->str = s;
	return string;
}

void
camera_set(struct camera *camera)
{
	glRotatef(camera->x, 1.0, 0.0, 0.0);
	glRotatef(camera->y, 0.0, 1.0, 0.0);
	/* glRotatef(camera->z, 0.0, 0.0, 1.0); */
}

struct camera *
camera_new(void)
{
	struct camera *camera = NULL;

	camera = malloc(sizeof(struct camera));
	camera->x = 0;
	camera->y = 0;
	camera->z = 0;
	camera_set(camera);
	camera->zoom = 1.0;
	return camera;
}

void
camera_zoom(struct camera *camera)
{
	glScalef(camera->zoom, camera->zoom, camera->zoom);
}

struct color *
color_new(void)
{
	struct color *color = NULL;

	color = malloc(sizeof(struct color));
	color->r = 0;
	color->g = 0;
	color->b = 0;
	color->a = 0;
	return color;
}

void
color_print(struct color *color)
{
	show_msg("color: ");
	printf("[\"%f\",\"%f\",\"%f\"]\n", color->r, color->g, color->b);
}

void
color_set(struct color *color, float red, float green, float blue, float alfa)
{
	if (color == NULL)
		return;

	color->r = red;
	color->g = green;
	color->b = blue;
	color->a = alfa;
}

struct point *
point_new(void)
{
	struct point *pos = NULL;
	pos = malloc(sizeof(struct point));
	pos->x = 0;
	pos->y = 0;
	pos->z = 0;
	return pos;
}

void
point_print(struct point *pos)
{
	show_msg("point: ");
	printf("[\"%f\",\"%f\",\"%f\"]\n", pos->x, pos->y, pos->z);
}

void
point_set(struct point *pos, float x, float y, float z)
{
	if (pos == NULL)
		return;

	pos->x = x;
	pos->y = y;
	pos->z = z;
}

struct game *
game_new(void)
{
	struct game *game = NULL;
	game = malloc(sizeof(struct game));
	game->width = 800;
	game->height = 600;
	game->kills = 0;
	game->lives = 3;
	game->name = string_new("gl-breakout");
	game->x = 0;
	game->y = 0;
	game->fullscreen = FALSE;
	game->ball_v_direction = DOWN;	/* up, down */
	game->ball_h_direction = FALSE;	/* right, left, false */
	game->ball_speed = 0.1;
	game->ball_speed_up = 0;
	game->n_blocks = 0;
	game->pause = TRUE;
	return game;
}

void
game_print(struct game *game)
{
	show_msg("game:\n");
	printf("\twindow: %i x %i: \n", game->width, game->height);
	printf("\tkills: %i: \n", game->kills);
}

void
array_new(void)
{
	int i;
	for (i = 0; i < MAX; i++) {
		ga_blocks[i] = NULL;
	}
}

struct sphere *
sphere_new(void)
{
	struct sphere *e = NULL;
	e = malloc(sizeof(struct sphere));
	e->color_border = color_new();
	e->color_fill = color_new();
	e->pos = point_new();
	e->scale = point_new();
	e->filled = TRUE;
	return e;
}

struct box *
box_new(void)
{
	struct box *b = NULL;
	b = malloc(sizeof(struct box));
	b->color_border = color_new();
	b->color_fill = color_new();
	b->pos = point_new();
	b->scale = point_new();
	/* b->translate = point_new(); */
	b->size = 0;
	b->filled = FALSE;
	b->active = TRUE;
	return b;
}

void
box_print(struct box *b)
{
	/* show_msg("box:\n");
	   color_print(b->color_fill);
	   color_print(b->color_border); */

	show_msg("box: ");
	printf("[%.3f, ", box_get(b, X_INI));
	printf("%.3f, ", box_get(b, X_END));
	printf("%.3f, ", box_get(b, Y_INI));
	printf("%.3f] ", box_get(b, Y_END));
	printf("%s%s%s [%.3f, %.3f]\n", GREEN, "centro:", NEUTRAL,
		   box_get(b, X_CENTER), box_get(b, Y_CENTER));

	/* point_print(b->pos);
	   point_print(b->scale);
	   show_msg("size: ");
	   printf("%i\n", b->size); */
}

float
box_get(struct box *b, int opt)
{
	float r = 0;
	switch (opt) {
	case X_INI:
		r = (b->pos->x * b->scale->x) - (b->scale->x / 2);
		break;
	case X_END:
		r = (b->pos->x * b->scale->x) + (b->scale->x / 2);
		break;
	case Y_INI:
		r = (b->pos->y * b->scale->y) + (b->scale->y / 2);
		break;
	case Y_END:
		r = (b->pos->y * b->scale->y) - (b->scale->y / 2);
		break;
	case X_CENTER:
		r = b->pos->x * b->scale->x;
		break;
	case Y_CENTER:
		r = b->pos->y * b->scale->y;
		break;
	}
	return r;
}

static void
ctrl_keyboard(unsigned char key, int x, int y)
{
	UNUSED(x);
	UNUSED(y);

	switch (key) {
	case ESC:
		_game->n_blocks = 0;
		break;
	case '+':
		_camera->zoom += 0.02;
		break;
	case '-':
		_camera->zoom -= 0.02;
		break;
	case 'n':
		_camera->zoom = 1.0;
		break;
	case 'f':
		if (!_game->fullscreen) {
			glutFullScreen();
			glutPositionWindow(0, 0);
			_game->fullscreen = TRUE;
		} else {
			glutReshapeWindow(_game->width, _game->height);
			/* gambiarra */
			glutPositionWindow(_game->x - 1, _game->y - 17);
			_game->fullscreen = FALSE;
		}
		break;
	case '1':
		_player->color_fill->r += 0.1;
		_player->color_fill->g += 0.1;
		_player->color_fill->b += 0.1;
		break;
	case '2':
		_player->color_fill->r -= 0.1;
		_player->color_fill->g -= 0.1;
		_player->color_fill->b -= 0.1;
		break;
	case '3':
		_game->ball_speed_up += 0.1;
		break;
	case '4':
		_game->ball_speed_up -= 0.1;
		if (_game->ball_speed_up <= 0)
			_game->ball_speed_up = 0;
		break;
	case 'a':
		_camera->y -= 10;
		break;
	case 'd':
		_camera->y += 10;
		break;
	case 's':
		_camera->x -= 10;
		break;
	case 'w':
		_camera->x += 10;
		break;
	case 'j':
		box_print(_player);
		break;
	case 'b':
		box_print(_border);
		break;
	case 'h':
		if (_game->pause)
			_game->pause = FALSE;
		else
			_game->pause = TRUE;

		break;
	case 'v':
		box_print(_ball);
		break;
	case 'p':
		show_score();
		break;
	}
	glutPostRedisplay();
}

void
ctrl_key_left(float val)
{
	_player->pos->x -= val;
	if (box_get(_player, X_INI) > box_get(_border, X_INI))
		return;

	_player->pos->x =
		(box_get(_border, X_INI) + (_player->scale->x / 2)) / _player->scale->x;
}

void
ctrl_key_right(float val)
{
	_player->pos->x += val;
	if ((box_get(_player, X_END) * 1000) < (box_get(_border, X_END) * 1000))
		return;

	_player->pos->x =
		(box_get(_border, X_END) - (_player->scale->x / 2)) / _player->scale->x;
}

static void
ctrl_special(int key, int x, int y)
{
	UNUSED(x);
	UNUSED(y);

	switch (key) {
	case GLUT_KEY_LEFT:
		ctrl_key_left(0.25);
		break;
	case GLUT_KEY_RIGHT:
		ctrl_key_right(0.25);
		break;
	case GLUT_KEY_UP:
		ctrl_key_right(1);
		break;
	case GLUT_KEY_DOWN:
		ctrl_key_left(1);
		break;
	}

	glutPostRedisplay();
}

void
draw_box(struct box *box)
{
	if (box->active == FALSE)
		return;

	glPushMatrix();
	glScalef(box->scale->x, box->scale->y, box->scale->y);
	glTranslatef(box->pos->x, box->pos->y, box->pos->z);

	if (box->filled) {
		glColor3f(box->color_fill->r, box->color_fill->g, box->color_fill->b);
		glutSolidCube(box->size);	/* fill */
	}

	glColor3f(box->color_border->r, box->color_border->g, box->color_border->b);
	glutWireCube(box->size);	/* border */
	glPopMatrix();
}

static void
ctrl_display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glPushMatrix();
	camera_zoom(_camera);
	camera_set(_camera);
	int i = 0;
	while (ga_blocks[i]) {
		draw_box(ga_blocks[i]);
		i++;
	}
	draw_box(_ball);
	draw_box(_border);
	draw_box(_player);
	glPopMatrix();

	draw_box(_score);
	show_game_score();
	if (_game->pause)
		show_game_help();
	if (_game->n_blocks <= 0)
		show_game_end();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

static void
ctrl_reshape(int width, int height)
{
	if (_game->fullscreen == FALSE) {
		_game->x = glutGet(GLUT_WINDOW_X);
		_game->y = glutGet(GLUT_WINDOW_Y);
		_game->width = width;
		_game->height = height;
	}

	glViewport(0, 0, width, height);
}

static void
movement_ball(void)
{
	switch (_game->ball_v_direction) {
	case DOWN:
		_ball->pos->y -= _game->ball_speed + _game->ball_speed_up + y;
		break;
	case UP:
		_ball->pos->y += _game->ball_speed + _game->ball_speed_up + y;
		break;
	}

	switch (_game->ball_h_direction) {
	case RIGHT:
		_ball->pos->x += _game->ball_speed + _game->ball_speed_up + x;
		break;
	case LEFT:
		_ball->pos->x -= _game->ball_speed + _game->ball_speed_up + x;
		break;
	case FALSE:
		_ball->pos->x = 0;
		break;
	}
}

void
movement_collision_reflect(int percent_pos)
{
	if (_game->ball_h_direction == FALSE) {
		if (percent_pos < 50)
			_game->ball_h_direction = LEFT;
		else
			_game->ball_h_direction = RIGHT;
	}

	if (percent_pos > 50)
		percent_pos = 100 - percent_pos;

	x = 0;
	y = 0;
	if (percent_pos >= 0 && percent_pos < 10) {	//70
		x = 0.5;
		y = 1.5;
	} else if (percent_pos >= 10 && percent_pos < 20) {	//55
		x = 0.75;
		y = 1.25;
	} else if (percent_pos >= 20 && percent_pos < 30) {	//45
		x = 1;
		y = 1;
	} else if (percent_pos >= 30 && percent_pos < 40) {	//30
		x = 1.25;
		y = 0.75;
	} else if (percent_pos >= 40 && percent_pos <= 50) {	//15
		x = 1.5;
		y = 0.5;
	}
}

void
movement_collision_block(void)
{
	int i = 0;
	float pos_x_ball = box_get(_ball, X_CENTER);
	float pos_y_ball = box_get(_ball, Y_CENTER);

	while (ga_blocks[i]) {

		if (ga_blocks[i]->active == FALSE) {
			i++;
			continue;
		}

		float pos_xi_player = box_get(ga_blocks[i], X_INI);
		float pos_xf_player = box_get(ga_blocks[i], X_END);
		float pos_yi_player = box_get(ga_blocks[i], Y_INI);
		float pos_yf_player = box_get(ga_blocks[i], Y_END);

		/* collision with me! */
		if ((pos_x_ball >= pos_xi_player)
			&& ((pos_x_ball <= pos_xf_player))) {

			if ((pos_y_ball <= pos_yi_player)
				&& ((pos_y_ball >= pos_yf_player))) {

				ga_blocks[i]->active = FALSE;
				show_score();
				_game->kills++;
				_game->n_blocks--;
				if (_game->ball_v_direction == UP)
					_game->ball_v_direction = DOWN;
				else
					_game->ball_v_direction = UP;
			}
		}
		i++;
	}
}

void
show_score(void)
{
	printf("%s%s%s\n", BLUE, "_____________________", NEUTRAL);
	printf("%s%s%s", BLUE, "|", NEUTRAL);
	show_msg("[PLACAR]  ");
	printf("%s%s\n%s%s", BLUE, "|", "|", NEUTRAL);
	printf("%slives: %s%i%s kills: %s%3i", MAGENTA, NEUTRAL, _game->lives,
		   MAGENTA, NEUTRAL, _game->kills);
	printf("%s%s%s\n", BLUE, "|", NEUTRAL);
	printf("%s%s%s\n", BLUE, "|____________________|", NEUTRAL);
}

void
show_game(void *fonte, char *str)
{
	int i = 0;
	while (str[i])
		glutBitmapCharacter(fonte, str[i++]);
}

void
show_game_end(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);

	glPushMatrix();
	glRasterPos2f(0.0, 0.0);
	show_game(GLUT_BITMAP_8_BY_13, "GAME OVER\0");
	glPopMatrix();

	glPopMatrix();

	glutPostRedisplay();		/* update display */
	sleep(1);
	glutLeaveMainLoop();
}

void
show_game_help(void)
{
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);

	glPushMatrix();
	glRasterPos2f(-0.9, 0.0);
	show_game(GLUT_BITMAP_8_BY_13, "Help:\0");
	glRasterPos2f(-0.9, -0.05);
	show_game(GLUT_BITMAP_8_BY_13, "* h - help and pause\0");
	glRasterPos2f(-0.9, -0.10);
	show_game(GLUT_BITMAP_8_BY_13, "* lelt, down - move left\0");
	glRasterPos2f(-0.9, -0.15);
	show_game(GLUT_BITMAP_8_BY_13, "* right, up - move right\0");
	glRasterPos2f(-0.9, -0.20);
	show_game(GLUT_BITMAP_8_BY_13, "* esc - quit\0");
	glRasterPos2f(-0.9, -0.25);
	show_game(GLUT_BITMAP_8_BY_13, "* a,d,w,s - camera control\0");
	glRasterPos2f(-0.9, -0.30);
	show_game(GLUT_BITMAP_8_BY_13, "* -,+ - zoom control\0");
	glPopMatrix();

	glPopMatrix();
}

void
show_game_score(void)
{
	char str1[20];
	sprintf(str1, "Pontos: %i", _game->kills);
	char str2[20];
	sprintf(str2, "Vidas: %i", _game->lives);

	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2f(-0.95, -0.95);
	show_game(GLUT_BITMAP_8_BY_13, str1);
	glRasterPos2f(0.8, -0.95);
	show_game(GLUT_BITMAP_8_BY_13, str2);
	glPopMatrix();
}

void
movement_collision_death(void)
{
	_ball->pos->x = 0;
	_ball->pos->y = 0;
	x = 1;
	y = 1;
	_game->ball_v_direction = DOWN;
	_game->ball_h_direction = FALSE;
	_game->ball_speed_up = 0;
	_game->lives--;
	if (_game->lives <= 0)
		_game->n_blocks = 0;
	show_score();
}

/* look for where is the ball */
static void
movement_collision(void)
{
	float pos_x_ball = box_get(_ball, X_CENTER);
	float pos_y_ball = box_get(_ball, Y_CENTER);

	/* player's height */
	if (pos_y_ball < box_get(_player, Y_INI)) {

		/* player? */
		float pos_xi_player = box_get(_player, X_INI);
		float pos_xf_player = box_get(_player, X_END);
		if ((pos_x_ball >= pos_xi_player)
			&& ((pos_x_ball <= pos_xf_player))) {

			_game->ball_v_direction = UP;
			float pos_collision = pos_x_ball - pos_xi_player;
			int percent_pos =
				(int)floor(pos_collision * 100 /
						   (pos_xf_player - pos_xi_player));
			movement_collision_reflect(percent_pos);

			/* if not in the player, then die! */
		} else {
			movement_collision_death();
		}
		/* roof? */
	} else if (pos_y_ball >= box_get(_border, Y_INI)) {

		_game->ball_v_direction = DOWN;

		/* left wall? */
	} else if (pos_x_ball <= box_get(_border, X_INI)) {

		_game->ball_h_direction = RIGHT;

		/* right wall? */
	} else if (pos_x_ball >= box_get(_border, X_END)) {

		_game->ball_h_direction = LEFT;

		/* blocks? */
	} else
		movement_collision_block();
}

static void
ctrl_idle(void)
{
	if (_game->pause == TRUE)
		return;

	usleep(10000);
	movement_ball();
	movement_collision();
	glutPostRedisplay();
}

void
ctrl_end(void)
{
	show_score();
	show_msg("maravilha alberto!\n");
	show_game_end();
}

int
ctrl_gogo(void)
{
	_game = game_new();
	_game->x = rint(glutGet(GLUT_SCREEN_WIDTH) / 2) - (WIDTH / 2);
	_game->y = rint(glutGet(GLUT_SCREEN_HEIGHT) / 2) - (HEIGHT / 2);

	_camera = camera_new();

	_player = box_new();
	point_set(_player->pos, 0, -34.0, 0);
	point_set(_player->scale, 0.3, 0.025, 1);
	color_set(_player->color_fill, 0.2, 0.3, 0.2, 0.0);
	color_set(_player->color_border, 0.0, 1.0, 0.0, 0.0);
	_player->size = 1.0;
	_player->filled = TRUE;

	_border = box_new();
	point_set(_border->pos, 0, 0.035, 0.0);
	point_set(_border->scale, 1.97, 1.84, 0.0);
	color_set(_border->color_border, 0.0, 1.0, 0.0, 0.0);
	_border->size = 1.0;
	_border->filled = FALSE;

	_score = box_new();
	point_set(_score->pos, 0, -9.3, 0.0);
	point_set(_score->scale, 1.97, 0.1, 1.0);
	color_set(_score->color_fill, 0.2, 0.3, 0.2, 0.0);
	color_set(_score->color_border, 0.0, 1.0, 0.0, 0.0);
	_score->size = 1.0;
	_score->filled = TRUE;

	_ball = box_new();
	point_set(_ball->pos, 0.0, 0.0, 0.0);
	point_set(_ball->scale, 0.01, 0.01, 0.01);
	color_set(_ball->color_fill, 1.0, 0.0, 0, 0.0);
	color_set(_ball->color_border, 1.0, 0.0, 0, 0.0);
	_ball->size = 1.0;
	_ball->filled = TRUE;

	array_new();
	int i;
	for (i = 0; i < 10; i++) {
		ga_blocks[i] = box_new();
		point_set(ga_blocks[i]->pos, i - 5, 10, 0.0);
		point_set(ga_blocks[i]->scale, 0.125, 0.08, 1.0);
		color_set(ga_blocks[i]->color_border, 0.0, 1.0, 0.0, 0.0);
		ga_blocks[i]->size = 1.0;
		ga_blocks[i]->filled = FALSE;
		_game->n_blocks++;
	}

	x = 1;
	y = 1;
	ORTO = 1;
	return 0;
}

int
main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	ctrl_gogo();

	glutInitWindowSize(_game->width, _game->height);
	glutInitWindowPosition(_game->x, _game->y);
	glutCreateWindow(_game->name->str);

	glutDisplayFunc(ctrl_display);
	glutKeyboardFunc(ctrl_keyboard);
	glutSpecialFunc(ctrl_special);
	glutReshapeFunc(ctrl_reshape);
	glutIdleFunc(ctrl_idle);
	glutCloseFunc(ctrl_end);

	glutMainLoopEvent();
	glutMainLoop();

	return 0;
}
