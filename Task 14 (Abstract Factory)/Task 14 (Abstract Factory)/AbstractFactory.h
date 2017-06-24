#include <string>
#include <iostream>
using namespace std;


class Subtitles;
class VoiceLang;
class EnglishFactory;
class VoiceFactory;
class Factory;


class Subtitles
{
public:
	virtual string getSubtitLang() = 0;
	void showSubtitlLang()
	{
		cout << getSubtitLang();
	};
	~Subtitles();
};

class VoiceLang
{
public:
	virtual string getFilmLang() = 0;
	virtual void showFilmLang()
	{
		cout << getFilmLang();
	}
	~VoiceLang();
};

class UkrainianSubtit :public Subtitles
{
	virtual string getSubtitLang()
	{
		return  "ukrainian subtitles";
	}
};

class GermanSubtitl : public Subtitles
{
	virtual string getSubtitLang()
	{
		return  "german subtitles";
	}
};

class EnglishSubtitl : public Subtitles
{
	virtual string getSubtitLang()
	{
		return  "english subtitles";
	}
};

class UkrainianLanguage :public VoiceLang
{
	virtual string getFilmLang()
	{
		return  "ukrainian voice";
	}
};

class GermanLanguage : public VoiceLang
{
	virtual string getFilmLang()
	{
		return  "german voice";
	}
};

class EnglishLanguage : public VoiceLang
{
	virtual string getFilmLang()
	{
		return  "english voice";
	}
};

class Film
{
public:
	VoiceLang * voice;
	Subtitles* subt;
	string name;
	Film(string filmName)
	{
		name = filmName;
	}
	string stringFilmInfo()
	{
		return name + " with " + voice->getFilmLang() +
			" and " + subt->getSubtitLang();
	}
	void showFilmInfo()
	{
		cout << stringFilmInfo();
	}
};

class Factory
{
public:
	virtual Subtitles* createSubtit() = 0;
	virtual VoiceLang* createVoiceLang() = 0;
};

class EnglishFactory : public Factory
{
	virtual Subtitles* createSubtit()
	{
		return new EnglishSubtitl;
	};
	virtual VoiceLang* createVoiceLang()
	{
		return new EnglishLanguage;
	};
};

class UkrainianFactory : public Factory
{
	virtual Subtitles* createSubtit()
	{
		return new UkrainianSubtit;
	};
	virtual VoiceLang* createVoiceLang()
	{
		return new UkrainianLanguage;
	};
};

class GermanFactory : public Factory
{
	virtual Subtitles* createSubtit()
	{
		return new GermanSubtitl;
	};
	virtual VoiceLang* createVoiceLang()
	{
		return new GermanLanguage;
	};
};


class FilmDestribution
{
public:
	Film* createFilm(Factory& factory, string filmName)
	{
		Film * film = new Film(filmName);
		film->voice = factory.createVoiceLang();
		film->subt = factory.createSubtit();
		return film;
	}
};