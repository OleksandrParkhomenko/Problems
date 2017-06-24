#include "stdafx.h"
#include "catch.hpp"
#include"../Task 14 (Abstract Factory)/AbstractFactory.h"


namespace UnitTest1
{		
	TEST_CASE("Ukranian film")
	{
		FilmDestribution destributor;
		UkrainianFactory ukr;
		Film* ukrFilm = destributor.createFilm(ukr, "Inception");
		string str = "Inception";
		REQUIRE(str == ukrFilm->name);
		str = "ukrainian subtitles";
		REQUIRE(str == ukrFilm->subt->getSubtitLang());
		str = "ukrainian voice";
		REQUIRE(str == ukrFilm->voice->getFilmLang());
	}
	TEST_CASE("English film")
	{
		FilmDestribution destributor;
		EnglishFactory eng;
		Film* engFilm = destributor.createFilm(eng, "Harry Potter and the Philosopher's Stone");
		string str = "Harry Potter and the Philosopher's Stone";
		REQUIRE(str == engFilm->name);
		str = "english subtitles";
		REQUIRE(str == engFilm->subt->getSubtitLang());
		str = "english voice";
		REQUIRE(str == engFilm->voice->getFilmLang());
	}
	TEST_CASE("German film")
	{
		FilmDestribution destributor;
		GermanFactory ger;
		Film* gerFilm = destributor.createFilm(ger, "Untouchables");
		string str = "Untouchables";
		REQUIRE(str == gerFilm->name);
		str = "german subtitles";
		REQUIRE(str == gerFilm->subt->getSubtitLang());
		str = "german voice";
		REQUIRE(str == gerFilm->voice->getFilmLang());
	}
}