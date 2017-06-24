#include <memory>
#include <fstream>
#include <string>
#include <iostream>


// Product
class Xml_file
{
public:
	Xml_file();
	void out_beginning(std::string text);
	void out_ending(std::string text);
	void out_headline(std::string&& text);
	void out_authors(std::string&& text);
	void out_text(std::string&& text);
	void out_hash(std::string&& text);
private:
	std::ofstream out_file;
};

// Builder
class Converter_to_xml
{
public:
	Converter_to_xml(std::string file_name);
	void attach_xml(std::unique_ptr<Xml_file>&& file);
	virtual bool check_hash() = 0;
	virtual void out_beginning() = 0;
	virtual void out_ending() = 0;
	virtual void out_headline() = 0;
	virtual void out_authors() = 0;
	virtual void out_text() = 0;
	virtual void out_hash() = 0;
	virtual ~Converter_to_xml() {};
protected:
	int count_number_of_lines();
	void return_to_file_beginning();
	void go_to_line(int line);

	std::ifstream in_file;
	std::unique_ptr<Xml_file>xml_file;
};

// Concrete Builder
class Txt_converter :public Converter_to_xml
{
public:
	Txt_converter(std::string file_name);
	bool check_hash()override;
	void out_beginning()override;
	void out_ending()override;
	void out_headline()override;
	void out_authors()override;
	void out_text()override;
	void out_hash()override;
};

//Director
class Director
{
public:
	void attach(Converter_to_xml* converter);
	void convert_to_xml();
private:
	void convert_to_xml_move();
	Converter_to_xml* converter;
};



Converter_to_xml::Converter_to_xml(std::string file_name) :in_file{ file_name }
{
	if (!in_file.is_open())throw std::string("Wrong file name");
}

void Converter_to_xml::attach_xml(std::unique_ptr<Xml_file>&& file)
{
	this->xml_file = std::move(file);
}

int Converter_to_xml::count_number_of_lines()
{
	int lines = 0;
	while (std::getline(in_file, std::string{}))++lines;
	return_to_file_beginning();
	return lines;
}

void Converter_to_xml::return_to_file_beginning()
{
	in_file.clear();
	in_file.seekg(0, std::ios::beg);
}

void Converter_to_xml::go_to_line(int line)
{
	return_to_file_beginning();
	for (int i = 1; i < line; ++i)
	{
		std::getline(in_file, std::string());
	}
}

Txt_converter::Txt_converter(std::string file_name)try : Converter_to_xml{ file_name }
{
}
catch (std::string error)
{
	std::cout << error << std::endl;
}

bool Txt_converter::check_hash()
{
	std::string line{};
	std::string hash{};
	int lines_counter = count_number_of_lines();
	for (int i = 1; i < lines_counter; ++i)
	{
		std::getline(in_file, line);
		hash += std::to_string(std::hash <std::string>()(line));
	}
	std::string real_hash{};
	std::getline(in_file, real_hash);
	return_to_file_beginning();
	return real_hash == hash ? true : false;
}

void Txt_converter::out_beginning()
{
	xml_file->out_beginning("<article>");
}

void Txt_converter::out_ending()
{
	xml_file->out_ending("</article>");
}

void Txt_converter::out_headline()
{
	std::string headline{};
	std::getline(in_file, headline);
	xml_file->out_headline(std::move(headline));
}

void Txt_converter::out_authors()
{
	std::string authors{};
	std::getline(in_file, authors);
	xml_file->out_authors(std::move(authors));
}

void Txt_converter::out_text()
{
	std::string text{};
	std::string out_text{};
	int lines_counter = count_number_of_lines();

	go_to_line(3);
	for (int i = 1; i < lines_counter; ++i)
	{
		std::getline(in_file, text);
		if (i < lines_counter - 1)
		{
			out_text += text + "\n";
		}
		else
		{
			out_text += text;
		}
	}
	xml_file->out_text(std::move(out_text));
}

void Txt_converter::out_hash()
{
	std::string hash{};
	std::getline(in_file, hash);
	xml_file->out_hash(std::move(hash));
}

Xml_file::Xml_file()try :out_file{ "Output.xml" }
{
	if (!out_file.is_open())throw "Can't open output file";
}
catch (std::string error)
{
	std::cout << error << std::endl;
}

void Xml_file::out_beginning(std::string text)
{
	out_file << text << "\n";
}

void Xml_file::out_ending(std::string text)
{
	out_file << text << "\n";
}

void Xml_file::out_headline(std::string && text)
{
	out_file << "<title>\t" << text << "\t</title>\n";
}

void Xml_file::out_authors(std::string && text)
{
	out_file << "<authors>\t" << text << "\t</authors>\n";
}

void Xml_file::out_text(std::string && text)
{
	out_file << "<body>\n" << text << "\n</body>\n";
}

void Xml_file::out_hash(std::string && text)
{
	out_file << "<hash>\t" << text << "\t</hash>\n";
}

void Director::attach(Converter_to_xml* converter)
{
	this->converter = converter;
}

void Director::convert_to_xml()
{
	try
	{
		convert_to_xml_move();
	}
	catch (std::string error)
	{
		std::cout << error << std::endl;
	}

}

void Director::convert_to_xml_move()
{
	if (converter->check_hash())
	{
		converter->out_beginning();
		converter->out_headline();
		converter->out_authors();
		converter->out_text();
		converter->out_hash();
		converter->out_ending();
	}
	else throw std::string("Hash in file is wrong");
}