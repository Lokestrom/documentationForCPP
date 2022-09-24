#include <fstream>
#include <iostream>
#include "String.hpp"
#include <filesystem>

#include "HTMLCreator.hpp"

using namespace Database;

int main(const int argc, const char* file)
{
	String s(file[1]);
	fileName = new Vector<String>(s.split('/'));
	String className = fileName[fileName->size()-1].split('.')[0];
	ifile = new std::ifstream(toSTD(s));
	ofile = new std::ofstream(toSTD(className) + ".html");
	String text;

	*ofile << "<!DOCTYPE html>\n"
		<< "<head>\n"
		<< "	<link rel = \"stylesheet\" href=\"../documentationStyles/all.css\">\n"
		<< "	<link rel=\"stylesheet\" href=\"../documentationStyles/class.css\">\n"
		<< "</head>\n\n"
		<< "<header>\n"
		<< "	<a class = \"homeButton\" href=\"../main.html\">Home</a>\n"
		<< "    <h1 class = \"white underline\">" << className << "</h1>\n"
		<< "</header>\n\n"
		<< "<body class=\"background white\">\n"
		<< "	<div>\n"
		<< "		<p class=\"header\">\n"
		<< "			<span>Defined in header</span>\n"
		<< "			<a href=\"https://github.com/Lokestrom/database/blob/main/database/" << className << ".hpp\">" << "\"" << className << ".hpp\"" << "</a>\n"
		<< "			<br>\n"
		<< "			<span>Code in</span>\n";

	getline(ifile, text);
	text.lower();
	if (text.contains("github")) {
		if (text.contains("cpp"))
			*ofile << "			<a href=\"https://github.com/Lokestrom/database/blob/main/database/" << className << ".cpp\">" << "\"" << className << ".cpp\"" << "</a>\n";
		if (text.contains("cpp") && text.contains("tpp"))
			*ofile << "<span> and </span>\n";
		if (text.contains("tpp"))
			*ofile << "			<a href=\"https://github.com/Lokestrom/database/blob/main/database/" << className << ".tpp\">" << "\"" << className << ".tpp\"" << "</a>\n";
	}
	
	*ofile << "		</p>\n"
		<< "		<p class=\"definition\">\n";
	while(getline(ifile, text)){
		text.lower();
		if (text.contains("class defintition")) {
			getline(ifile, text);
			String definition = text;
			getline(ifile, text);
			if(text != "}")
				definition += "<br>" + text;
			fileWriter(definition, "p class=\"definition\"");
		}
	}

	while (getline(ifile, text)) {
		text.lower();
		if (!text.contains("class description"))
			continue;
		String description = "";
		for (; text != "}"; getline(ifile, text))
			description += text + "\n<br>\n";
		description.pop(description.length() - 7, description.length());
		fileWriter(description, "span class=\"description\"");
	}

	*ofile << "    <br><br> \n <h2 style=\"line-height: 0px;\"> Member fungtions </h2>\n\n <table class=\"linkToFungtionsTable\">";

	while (getline(ifile, text)) {
		text.lower();
		if (!text.contains("member fungtions"))
			continue;
		for (; text != "}"; getline(ifile, text)) {
			if (text.contains(":")) 
				FungtionList(text);

			else if (text.contains("{")) {
				subList(text(0, text.length()));
				for (; text != "}"; getline(ifile, text))
					if (text.contains(":"))
						FungtionList(text);
			}
		}
		*ofile << "</table>\n";
	}

	while (getline(ifile, text)) {
		text.lower();
		if (text.contains("non-member fungtions")) {
			*ofile <<  "<br>\n<h2 style = \"line-height: 0px;\">Non - Member fungtions< / h2>\n<table class = \"linkToFungtionsTable\">";
			for (; text != "}"; getline(ifile, text)) {
				if (text.contains(":"))
					FungtionList(text);

				else if (text.contains("{")) {
					subList(text(0, text.length()));
					for (; text != "}"; getline(ifile, text))
						if (text.contains(":"))
							FungtionList(text);
				}
			}
		}
		*ofile << "</table>";
	}
	
	*ofile << "<br><br><br><br><br><br><br><br><br>\n</body>";

	delete ifile;
	delete ofile;
	delete fileName;
}