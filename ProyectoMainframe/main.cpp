#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include "Algoritmo.h"
#include <queue>
#include "Nodo.h"

using namespace std;

struct Contexto {
	UnionFind* us;
	std::queue<Move*> * movimientos;
	std::vector<Nodo*> * nodos;
	int width, height;
};

//Método para crear el título
void newTitulo(sf::Font fuente, sf::RenderWindow * window, int width) {
	//Crear el título para el window
	sf::Text Title;
	sf::String nameTitle = "Union Find - Disjoint Set";

	//Seteando valores al título
	Title.setString(nameTitle);
	Title.setFont(fuente);
	Title.setCharacterSize(20);
	Title.setPosition((width / 2) - 200, 0);
	Title.setFillColor(sf::Color::Blue);
	window->draw(Title);
}

//función recursiva para crear el "árbol"
void dibujarPosicion(int padre, float x, float y, float ancho, Contexto cx) {
	vector <int> nodos;
	if (padre == -1) {
		nodos=cx.us->getPadres();
	}
	else {

	}
	
	
}

void actualizarGrafo(Contexto cx) {
	for (int i = 0; i < cx.us->p.size(); i++) {
		
	}
}

void mi_algoritmo(Contexto cx) {
	/*cx.movimientos->push(new Move(100, 100, 0.5, 2, cx.nodos->at(0)));
	cx.movimientos->push(new Move(220, 100, 0.5, 2, cx.nodos->at(1)));
	cx.movimientos->push(new Move(300, 100, 0.5, 2, cx.nodos->at(2)));*/
	dibujarPosicion(-1, 0, 0, cx.width, cx);

}


int main() {
	//Creando un objeto para realizar el algoritmo
	UnionFind us;
	int width, height;

	//Creando los nodos y seteando los valores necesarios
	us.makeSet(9);

	us.unionSet(1, 2);
	us.unionSet(3, 5);
	us.unionSet(5, 2);
	us.unionSet(8, 0);
	us.unionSet(7, 3);
	us.unionSet(4, 6);
	/*
	cout << us.findSet(7);
	cout << us.findSet(2);
	std::cout << us.findSet(3);
	cout << us.numDisjointSets();
	*/
	//Largo y ancho de la pantalla

	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	sf::RenderWindow window(sf::VideoMode(width, height), "Proyecto Mainframe: Union Find - DS");

	//CREAMOS UN OBJETO FUENTE
	sf::Font fuente;
	// Intentamos cargarla
	if (!fuente.loadFromFile("DroidSans.ttf"))
	{
		return EXIT_FAILURE;
	}

	std::vector<Nodo*> nodos;
	std::queue<Move*> movimientos;
	sf::Clock clock;
	
	for (int i = 0; i < us.p.size(); i++) {
		Nodo* nodo = new Nodo(50, 0, i*50, std::to_string(us.p[i]), fuente);
		nodos.push_back(nodo);
	}
	Contexto cxt;
	cxt.us = &us;
	cxt.movimientos = &movimientos;
	cxt.nodos = &nodos;
	cxt.height = height;
	cxt.width = width;
	std::thread moving(mover, &movimientos);
	std::thread run_algoritmo(mi_algoritmo, &cxt);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time elapsed = clock.restart();
		window.clear();
		for (int i = 0; i < nodos.size(); i++) {
			nodos[i]->paint(&window);
		}
		newTitulo(fuente, &window, width);
		window.display();

		
	}
	moving.detach();
	run_algoritmo.detach();

	return 0;
}