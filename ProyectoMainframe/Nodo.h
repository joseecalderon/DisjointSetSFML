#ifndef __NODO_H__
#define __NODO_H__
#include "Algoritmo.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <queue>

using namespace std;

class Nodo {
public:
	int alto = 0;
	int ancho = 0;
	float x = 0;
	float y = 0;
	string num = "";
	sf::Font fuente;


public:
	Nodo() {}
	Nodo(int size, float x, float y, string num, sf::Font fuente) {
		this->alto = size;
		this->ancho = size;
		this->x = x;
		this->y = y;
		this->num = num;
		this->fuente = fuente;
	}
	void paint(sf::RenderWindow* window);
};
void Nodo::paint(sf::RenderWindow* window){
	alto = 100;
	ancho = 150;
	sf::Text numCirculo;
	sf::String cadenaNum;

	sf::CircleShape shape(25);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(this->x, this->y);
	window->draw(shape);
	// Damos un valor a la cadena
	cadenaNum = num;
	// Asignamos la cadena al texto
	numCirculo.setString(cadenaNum);
	// Asignamos la fuente que hemos cargado al texto
	numCirculo.setFont(fuente);
	// Tamaño de la fuente
	numCirculo.setCharacterSize(20);
	// Color al texto
	numCirculo.setFillColor(sf::Color::Black);
	// Posicion del texto
	numCirculo.setPosition(ancho - 45, alto + 18);
	//MANDAS A LA VENTANA EL NUMERO
	window->draw(numCirculo);

};

struct Move {
	float x = 0;
	float y = 0;
	float vx = 0;
	float vy = 0;
	Nodo * nodo;
	sf::Clock clock;
	boolean isMoving;
	Move(float x, float y, float vx, float vy, Nodo * nodo) {
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;
		this->nodo = nodo;
		this->isMoving = false;
		if (nodo->x > x) {
			this->vx = vx * -1;
		}
		if (nodo->y > y) {
			this->vy = vy * -1;
		}

	}
	void start() {
		this->isMoving = true;
		clock.restart();
	};
	void move() {
		if (!isMoving) return;
		sf::Time elapsed = clock.restart();
		float nuevo_x = this->nodo->x + vx*elapsed.asMilliseconds();
		float nuevo_y = this->nodo->y + vy*elapsed.asMilliseconds();
		if ((this->nodo->x <= nuevo_x && nuevo_x <= x) || (this->nodo->x >= nuevo_x && nuevo_x >= x)) {
			// si no esta fuera del rango
			this->nodo->x = nuevo_x;
		}
		else {
			this->nodo->x = x;
		}
		if ((this->nodo->y <= nuevo_y && nuevo_y <= y) || (this->nodo->y >= nuevo_y && nuevo_y >= y)) {
			this->nodo->y = nuevo_y;
		}
		else {
			this->nodo->y = y;
		}

		if (nodo->x == x && nodo->y == y) {
			this->isMoving = false;
		}
	}
};

void mover(queue<Move*> * movimientos) {
	while (true) {
		while (!movimientos->empty())
		{
			Move * movimiento = movimientos->front();
			if (!movimiento->isMoving) {
				movimientos->front()->start();
			}
			movimiento->move();
			if (!movimiento->isMoving) { // si dejo de moverse, chau
				delete movimiento;
				movimientos->pop();
			}
			Sleep(10);
		}
		Sleep(10);
	}
}
#endif