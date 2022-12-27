#include "ClassCreator.hpp"
#include "HTMLCreator.hpp"

#include <fstream>

using namespace Database;

//name = TXT/"LibName"/classes/"className".txt
void classCreator(String fullFileName)
{
	fileName = new Vector<String>(fullFileName.split('/'));
	String className = fileName->operator[](fileName->size()-1);
	className = className.split('.')[0];
	ifile = new std::ifstream(toSTD(fullFileName));
	ofile = new std::ofstream("HTML\\" + toSTD(fileName->operator[](1)) + "\\classes\\" + toSTD(className) + ".html");
	String text;
	while (!text.contains("github")) {
		getline(*ifile, text);
	}
	getline(*ifile, text);

	*ofile << "<!DOCTYPE html>\n"
		<< "<head>\n"
		<< "	<link rel = \"stylesheet\" href=\"../../documentationStyles/all.css\">\n"
		<< "	<link rel=\"stylesheet\" href=\"../../documentationStyles/class.css\">\n"
		<< "</head>\n\n"
		<< "<header>\n"
		<< "	<a class = \"homeButton\" href=\"../../main.html\">Home</a>\n"
		<< "	<a class = \"libButton\" href=\"../" + fileName->operator[](1) + ".html\">" + fileName->operator[](1) + "</a>\n"
		<< "    <h1 class = \"white underline\">" << className << "</h1>\n"
		<< "</header>\n\n"
		<< "<body class=\"background white\">\n"
		<< "	<div>\n"
		<< "		<p class=\"header\">\n"
		<< "			<span>Defined in header</span>\n"
		<< "			<a href=\"" + text + "\">" << "\"" << className << ".hpp\"" << "</a>\n"
		<< "			<br>\n"
		<< "			<span>Code in</span>\n";

	getline(*ifile, text);
	if (text.split(':')[0] == "cpp") {
		*ofile << "			<a href=\"" + text(4,text.length()) + "\">" << "\"" << className << ".cpp\"" << "</a>\n";
		getline(*ifile, text);
		if (text.split(':')[0] == "tpp")
			*ofile << "<span> and </span>\n";
	}
	if (text.split(':')[0] == "tpp")
		*ofile << "			<a href=\"" + text(4, text.length()) + "\">" << "\"" << className << ".tpp\"" << "</a>\n";
	
	*ofile << "		</p>\n";
	while(getline(*ifile, text)){
		text.lower();
		if (text.contains("class declaration")) {
			getline(*ifile, text);
			String definition = text;
			getline(*ifile, text);
			if(text != "}")
				definition += "<br>" + text;
			fileWriter(definition, "p class=\"declaration\"");
			break;
		}
	}
	*ofile << "</div>\n";

	while (getline(*ifile, text)) {
		text.lower();
		if (!text.contains("class description"))
			continue;
		String description = "Class description:\n<br>\n";
		getline(*ifile, text);
		for (; text != "}"; getline(*ifile, text))
			description += text + "\n<br>\n";
		description.pop(description.length() - 6, description.length());
		fileWriter(description, "span class=\"description\"");
		break;
	}

	while (getline(*ifile, text)) {
		text.lower();
		if (!text.contains("member fungtions"))
			continue;
		*ofile << "    <br><br> \n <h2 style=\"line-height: 0px;\"> Member fungtions </h2>\n\n <table class=\"linkToFungtionsTable\">";
		getline(*ifile, text);
		for (; text != "}"; getline(*ifile, text)) {
			if (text.contains(":")) 
				FungtionList(text);

			else if (text.contains("{")) {
				subList(text(0, text.length()));
				for (; text != "}"; getline(*ifile, text))
					if (text.contains(":"))
						FungtionList(text);
			}
		}
		*ofile << "</table>\n";
		break;
	}

	while (getline(*ifile, text)) {
		text.lower();
		if (!text.contains("non-member fungtions"))
			continue;
		*ofile <<  "<br>\n<h2 style = \"line-height: 0px;\">Non-Member fungtions</h2>\n<table class = \"linkToFungtionsTable\">";
		getline(*ifile, text);
		for (; text != "}"; getline(*ifile, text)) {
			if (text.contains(":"))
				FungtionList(text);

			else if (text.contains("{")) {
				subList(text(0, text.length()));
				for (; text != "}"; getline(*ifile, text))
					if (text.contains(":"))
						FungtionList(text);
			}
		}
		*ofile << "</table>";
		break;
	}
	
	*ofile << "<br><br><br><br><br><br><br><br><br>\n</body>";

	ifile->close();
	ofile->close();

	delete ifile;
	delete ofile;
	delete fileName;
}