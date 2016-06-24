#include <iostream>
#include <string>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <time.h>  
#include "GameManager.h"
#include "Roadside.h"
#include "Orange.h"
#include "Butter.h"
#include "Car.h"
#include "Table.h"
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"
#include "LightSource.h"
#include "Candle.h"
#include "PauseScreen.h"
#include "GameOverScreen.h"

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* set cursor macro */
#define setCursor(crd)	SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), crd )

using namespace std;

GLuint texture;
vector<GameObject*> _gameObjects;
vector<Camera*> cameras;
Car* _player;
Roadside* _roadside;
Camera* currentCamera;
Table* _table;
vector<Orange*> _oranges;
vector<Butter*> _butters;
vector<Candle*> _candles;
LightSource* _directionalLight;
vector<GLenum> lightVector;
vector<Vector3> pos;
vector<Car*> _livesVector;

Camera* pauseCam;
Camera* cam1;
Camera* cam2;
Camera* cam3;
Camera* carCam;

bool _toggleMode = true; // wired/solid
bool _lightMode = true; //key L
bool _day = false;//key N
bool _dead = false;
bool _constantShading = false; //key G
bool _lightSource = true; //key C
bool _pause = false; //key S
bool _carLight = true;
int _lives;
void update(int value);
double pausetime;
double cam_angle;
double window_w = 100;
double window_h = 100;




GameManager::GameManager()
{
}
GameManager::~GameManager()
{
}

void orangeRespawn(int orange) {
	if (_oranges[orange]->disabled) //when orange disappears
		_oranges[orange]->respawn();
}

void orangeLevel(int orange) {
	_oranges[orange]->nextLevel(); //increase orange speed
	glutTimerFunc(rand() % (MAX_LEVEL - MIN_LEVEL) + MIN_LEVEL, orangeLevel, orange);
}

void respawn() {
	//put game objects in vector
	cam_angle = 180;
	_gameObjects = vector<GameObject*>();
	_player = new Car(Vector3(-18, -12, 0));
	_roadside = new Roadside();
	_table = new Table();
	_oranges = vector<Orange*>();
	_butters = vector<Butter*>();
	_candles = vector<Candle*>();
	_livesVector = vector<Car*>();
	pos = { Vector3(-17, 10, 0), Vector3(-17, -10, 0), Vector3(17, -10, 0), Vector3(17, 10, 0), Vector3(0, -5, 0), Vector3(0, 5, 0) };
	lightVector = { GL_LIGHT1, GL_LIGHT2,GL_LIGHT3, GL_LIGHT4, GL_LIGHT5 };

	int x;
	int y;
	float posX = TABLE_XMIN;
	float posY = TABLE_YMIN / 2;
	srand(time(NULL));

	for (int i = 0; i < 3; i++) { //set random orange position -> just first time
		x = rand() % 6 + 20;
		y = rand() % 16;
		_oranges.push_back(new Orange(Vector3(x, y, 0)));
		glutTimerFunc(rand() % (MAX_LEVEL - MIN_LEVEL) + MIN_LEVEL, orangeLevel, i);
	}

	// creates 6 point lights
	for (int i = 0; i < 5; i++) {
		_candles.push_back(new Candle(pos[i]));
		_candles[i]->setLight(new LightSource(pos[i], lightVector[i]));
	}

	for (int i = 0; i < _lives;i++) {
		_livesVector.push_back(new Car(Vector3(i*-1, 0, 0)));
	}

	//butters position
	_butters.push_back(new Butter(Vector3(22, -0.5, 0)));
	_butters.push_back(new Butter(Vector3(-20.8, 7.8, 0)));
	_butters.push_back(new Butter(Vector3(-22.3, -0.2, 0)));
	_butters.push_back(new Butter(Vector3(-20.8, -8.2, 0)));
	_butters.push_back(new Butter(Vector3(17, 0, 0)));

	_gameObjects.push_back(_roadside);
	_gameObjects.push_back(_player);

	_gameObjects.insert(_gameObjects.end(), _candles.begin(), _candles.end());
	_gameObjects.insert(_gameObjects.end(), _oranges.begin(), _oranges.end());
	_gameObjects.insert(_gameObjects.end(), _butters.begin(), _butters.end());
}
void init()
{
	_lives = INITIAL_LIVES;
	respawn();
	cameras = vector<Camera*>();
	//orthogonal camera - PAUSE
	pauseCam = new OrthogonalCamera(0, 30, 0, 20, -15, 15);
	//orthogonal camera - see the whole table
	cam1 = new OrthogonalCamera(TABLE_XMIN, TABLE_XMAX, TABLE_YMIN, TABLE_YMAX, -15, 15);
	//perspective camera  (eye, at, up, fovy, aspect, near, far)
	cam2 = new PerspectiveCamera(Vector3(0, -25, 25), Vector3(0, 0, 0), Vector3(0, 0, 1), 90, 18 / 18, 1, 100);
	//perspective camera - follows car
	cam3 = new PerspectiveCamera(Vector3(), Vector3(), Vector3(0, 0, 1), 90, 18 / 18, 1, 20);
	//create direcional light
	_directionalLight = new LightSource(Vector3(1.0f, 0.0f, 1.5f), GL_LIGHT6); // creates directional light
	_directionalLight->setSpecular(Vector3(1.0f, 0.3f, 0.3f));
	_directionalLight->directionalLight();
	//create car camera for lives
	carCam = new OrthogonalCamera(-10, 10, -5, 5, 0, 0);

	//glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 0.0);

	cameras.push_back(cam1);
	cameras.push_back(cam2);
	cameras.push_back(cam3);
	cameras.push_back(pauseCam);

	currentCamera = cam1;

	glEnable(GL_DEPTH_TEST); //Enable Z-Buffer
	glDepthFunc(GL_LESS); //Passes if the incoming depth value is less than the stored depth value
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	glutTimerFunc(16, update, 0); //call update

}



void update(int value) {

	int thisTime = glutGet(GLUT_ELAPSED_TIME); // get elapsed time since beginning

	for (GameObject* obj : _gameObjects) {
		obj->update(thisTime - value); //update all objects
	}
	for (Butter* obj : _butters) {
		if (obj->hasCollided(_player)) {
		_player->processCollision(obj); //collision case with butters
		obj->collide(_player);
		}
	}

	for (int i = 0; i < _oranges.size(); i++) {
		Orange* obj = _oranges[i];
		if (obj->hasCollided(_player)) {
			obj->collide(_player); //collision case with orange
			_lives--;
		}
		if ((obj->disabled == false) && (abs(obj->_position.getX()) > TABLE_XMAX || abs(obj->_position.getY()) > TABLE_YMAX)) {
			glutTimerFunc(rand() % (MAX_RESPAWN - MIN_RESPAWN) + MIN_RESPAWN, orangeRespawn, i);
			obj->disabled = true; //when orange get out the table
		}
	}

	/*for (Cheerio &obj : _roadside->_cheerios) {
	if (obj.hasCollided(_player)) {
	_player->processCollision(&obj); //collision case with cheerio
	obj.collide(_player);
	}
	}

	//Candle collide
	for (Candle* obj : _candles) {
	if (obj->hasCollided(_player)) {
	_player->processCollision(obj); //collision case with candles
	obj->collide(_player);
	}
	}*/

	//check table limits
	if (_player->tableEnd(TABLE_XMIN, TABLE_XMAX, TABLE_YMIN, TABLE_YMAX)) {
		_lives--;
		respawn();
	}
	//update moving camera
	cameras[2]->setAt(_player->getPosition());
	double camX = cos(cam_angle)*_player->_direction.getX() + sin(cam_angle)*_player->_direction.getY();
	double camY = -sin(cam_angle)*_player->_direction.getX() + cos(cam_angle)*_player->_direction.getY();
	cameras[2]->setPosition(_player->getPosition() + Vector3(PROXIMITY*camX, PROXIMITY*camY, -PROXIMITY / 2));
	if (_lives == 0) {
		_dead = true;
	}
	if (!_pause && !_dead) {
		glutTimerFunc(16, update, thisTime); // 60fps
		pausetime = thisTime;
	}



	glutPostRedisplay();

}


void display(void)
{

	static float i = -10;
	i = i + .1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (!_toggleMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //select wired polygon rasterization mode
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //select solid polygon rasterization mode
	glViewport(0, 0, window_w, window_h);											   //draw table
	glPushMatrix();
	glMatrixMode(GL_PROJECTION); //get stack of projection matrix
	glLoadIdentity();
	currentCamera->computeProjectionMatrix(); //compute projection matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	currentCamera->computeVisualizationMatrix(); //compute visualization matrix


												 // Draw candles
	for (Candle* candle : _candles) {
		candle->draw();
	}

	// Draw directional light
	if (glIsEnabled(GL_LIGHT6))
		_directionalLight->draw();

	_table->draw();

	glPushMatrix();
	_roadside->draw(); // draw track

					   //draw all obstacles
	for (Butter* butter : _butters) {
		butter->draw();
	}

	for (Orange* orange : _oranges) {
		orange->draw();
	}

	//draw car
	_player->draw();

	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glViewport(0, 350, 1000, 150);
	glMatrixMode(GL_PROJECTION); //get stack of projection matrix
	glLoadIdentity();
	carCam->computeProjectionMatrix(); //compute projection matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	carCam->computeVisualizationMatrix(); //compute visualization matrix
	for (Car* c : _livesVector) {
		c->setMaterial(new Material(Vector3(0.5, 0.5, 0.5), Vector3(0, 0, 0), Vector3(0, 0, 0), 0));
		glPushMatrix();
		glScalef(0.1, 1, 0.5);
		glRotatef(-90, 1, 0, 0);
		c->draw();
		glPopMatrix();

	}

	glPopMatrix();


	if (_pause) {
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glViewport(window_w/4, window_h/4, window_w/2, window_h/2);
		glMatrixMode(GL_PROJECTION); //get stack of projection matrix
		glLoadIdentity();
		pauseCam->computeProjectionMatrix(); //compute projection matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		pauseCam->computeVisualizationMatrix(); //compute visualization matrix
		PauseScreen pauseScreen = PauseScreen();
		pauseScreen.draw();
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	if (_dead) {
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glViewport(window_w / 4, window_h / 4, window_w / 2, window_h / 2);
		glMatrixMode(GL_PROJECTION); //get stack of projection matrix
		glLoadIdentity();
		pauseCam->computeProjectionMatrix(); //compute projection matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		pauseCam->computeVisualizationMatrix(); //compute visualization matrix
		GameOverScreen gameOverScreen = GameOverScreen();
		gameOverScreen.draw();
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}

	glFlush();

}

void reshape(GLsizei w, GLsizei h)
{
	float aspect = (float)w / h;
	glMatrixMode(GL_PROJECTION); //get stack of projection matrix
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); //get stack of modelview matrix
	glLoadIdentity();
	window_w = w;
	window_h = h;
	for (Camera* cam : cameras) {
		cam->reshape(w, h);
	}
	currentCamera->computeProjectionMatrix();
}

void keyPressed(unsigned char key, int x, int y) { // different key commands
	if (key == 'A' || key == 'a') {
		if (_toggleMode) { // wired
			_toggleMode = false;
		}
		else { // solid
			_toggleMode = true;
		}
	}
	else if (key == '1') { //camera 1 - orthogonal
		currentCamera = cam1;
	}
	else if (key == '2') { //camera 2 - perspective
		currentCamera = cam2;
	}
	else if (key == '3') { //camera 2 - perspective
		currentCamera = cam3;
	}
	else if (key == 'n' || key == 'N') { // direccional light (day/night mode)
		_day = !_day;
		//key N
		if (_day) { glEnable(GL_LIGHT6); }
		else { glDisable(GL_LIGHT6); }
	}
	else if (key == 'l' || key == 'L') { // lighting calculation (day/night mode)
		_lightMode = !_lightMode;
		//key L
		if (_lightMode) { glEnable(GL_LIGHTING); }
		else { glDisable(GL_LIGHTING); }
	}
	else if (key == 'g' || key == 'G') { //type of shading (Constant/Gourand)
		_constantShading = !_constantShading;
		//key G 
		if (_constantShading) { glShadeModel(GL_FLAT); }
		else { glShadeModel(GL_SMOOTH); }
	}
	else if (key == 'c' || key == 'C') { // light sources
		_lightSource = !_lightSource;
		//key C
		if (_lightSource) {
			for (Candle* candle : _candles) { candle->candleEnable(); }
		}
		else {
			for (Candle* candle : _candles) { candle->candleDisable(); }
		}
	}
	//pause
	else if (key == 's' || key == 'S') {
		_pause = !_pause;
		if (!_pause) {
			glutTimerFunc(16, update, glutGet(GLUT_ELAPSED_TIME)); // 60fps
		}

	}
	else if (key == 'h' || key == 'H') {
		_carLight = !_carLight;
		if (_carLight) { _player->enableHeadlights(); }
		else { _player->disableHeadlights(); }
	}
	//rotate camera
	else if (key == 'o' || key == 'O') {
		cam_angle += 3.1415 / 180;
	}
	else if (key == 'P' || key == 'p') {
		cam_angle -= 3.1415 / 180;
	}
	//key R - restart
	else if (key == 'R' || key == 'r') {
		if (_dead) {
			glutTimerFunc(16, update, glutGet(GLUT_ELAPSED_TIME)); // 60fps
			_dead = false;
		}
			
	}

}


void keyBoardUp(int key, int x, int y) { // key up detection

	switch (key) {
	case(GLUT_KEY_UP) :
		_player->setAcceleration(0);
		break;
	case(GLUT_KEY_DOWN) :
		_player->setAcceleration(0);
		break;
	case(GLUT_KEY_LEFT) :
		_player->stopSteering();
		break;
	case(GLUT_KEY_RIGHT) :
		_player->stopSteering();
		break;
	}
}

void keyBoardDown(int key, int x, int y) { // key down detection

	switch (key) {
	case(GLUT_KEY_UP) :
		_player->gas();
		break;
	case(GLUT_KEY_DOWN) :
		_player->reverse();
		break;
	case(GLUT_KEY_LEFT) :
		_player->steerLeft();
		break;
	case(GLUT_KEY_RIGHT) :
		_player->steerRight();
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(-1, -1); //OS decide inicial window position
	glutCreateWindow(argv[0]);
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);
	glutSpecialUpFunc(keyBoardUp);
	glutSpecialFunc(keyBoardDown);

	glutMainLoop();

	return 0;
}
