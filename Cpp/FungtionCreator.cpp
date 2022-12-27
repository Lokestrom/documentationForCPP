#include "FungtionCreator.hpp"
#include "HTMLCreator.hpp"

#include <fstream>
#include <iostream>


void fungtionCreator(String fullFileName) {
	fileName = new Vector<String>(fullFileName.split('/'));
	String FungtionName = fileName->operator[](fileName->size() - 1);
	FungtionName = FungtionName.split('.')[0];
	ifile = new std::ifstream(toSTD(fullFileName));
	ofile = new std::ofstream("HTML\\" + toSTD(fileName->operator[](1)) + "\\" +toSTD(fileName->operator[](2)) + "\\" + toSTD(FungtionName) + ".html");
	String text;

	*ofile << "<!DOCTYPE html>\n"
		<< "<head>\n"
		<< "	<link rel=\"stylesheet\" href=\"../../documentationStyles/all.css\">\n"
		<< "	<link rel=\"stylesheet\" href=\"../../documentationStyles/fungtion.css\">\n"
		<< "</head>\n"
		<< "<header>\n"
		<< "	<a class=\"homeButton\" href=\"../../main.html\">Home</a>\n"
		<< "	<a class=\"libButton\" href=\"../" + toSTD(fileName->operator[](1)) + ".html\">" + toSTD(fileName->operator[](1)) + "</a>\n"
		<< "	<a class=\"toClassButton\" href=\"../classes/" + toSTD(fileName->operator[](2)) + ".html\">" + toSTD(fileName->operator[](2)) + "</a>\n"
		<< "	<h1 class=\"white underline\">" + toSTD(fileName->operator[](2)) + " documentation</h1>\n"
		<< "	<h2 class=\"white\">" + FungtionName + "</h2>\n"
		<< "</header>\n\n"
		<< "<body class=\"background white\">\n"
		<< "    <table class=\"declarationTable\">";

	while (getline(*ifile, text)) {
		text.lower();
		if (!text.contains("declerations"))
			continue;
		while (getline(*ifile, text) && !text.contains("}")) {
			if (!text.contains(":"))
				continue;
			*ofile << "<tr>\n<th>\n";
			fileWriter(text(text.linearSearch(':') + 1, text.length()), "span");
			*ofile << "</th>\n<th>"
				<< "<span>(" + text.split(':')[0] + ")</span>"
				<< "</th>"
				<< "</tr>";
		}
		break;
	}

	*ofile << "</table>\n"
		<< "<br><br>\n"
		<< "<table class=\"textTable\">\n";

	while (getline(*ifile, text)) {
		text.lower();
		if (!text.contains("description"))
			continue;
		while (getline(*ifile, text) && !text.contains("}")) {
			if (!text.contains(":"))
				continue;
			*ofile << "<tr>\n"
				<< "<th>\n"
				<< "<span>(" + text.split(':')[0] + ")</span>\n"
				<< "</th>\n"
				<< "<th>\n";
			fileWriter(text(text.linearSearch(':') + 1, text.length()), "span class=\"nb\"");
			*ofile << "<th>\n</tr>\n";
		}
		break;
	}

	*ofile << "</table>"
		<< "<h3 class=\"underline\">Complexity</h3>"
		<< "<table class = \"textTable\">";

	while (getline(*ifile, text)) {
		text.lower();
		if (!text.contains("complexity"))
			continue;
		while (getline(*ifile, text) && !text.contains("}")) {
			if (!text.contains(":"))
				continue;
			*ofile << "<tr>\n"
				<< "<th>\n"
				<< "<span>(" + text.split(':')[0] + ")</span>\n"
				<< "</th>\n"
				<< "<th>\n";
				fileWriter(text(text.linearSearch(':') + 1, text.length()), "span class=\"nb\"");
			*ofile << "<th>\n</tr>\n";
		}
		break;
	}
	*ofile << "</table>"
		<< "</body>";

	ofile->close();
	ifile->close();

	delete ifile;
	delete ofile;
	delete fileName;
}