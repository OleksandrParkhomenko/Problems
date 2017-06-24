#include "AbstractFactory.h"

void main() {
	FilmDestribution destributor;
	EnglishFactory eng;
	UkrainianFactory ukr;
	GermanFactory grm;

	Film* engFilm = destributor.createFilm(eng, "Harry Potter and the Philosopher's Stone");
	Film* ukrFilm = destributor.createFilm(ukr, "Inception");
	Film* grmFilm = destributor.createFilm(grm, "Untouchables");

	engFilm->showFilmInfo();
	cout << endl;
	system("pause");
}