#include "HTMLCreator.hpp"
#include <fstream>
#include <iostream>
#include "String.hpp"
#include <filesystem>

using namespace Database;
namespace fs = std::filesystem;

definitions::definitions() {
	for (int i = 48; i < 58; i++)
		fungtionCharList.pushBack(char(i));
	for (int i = 65; i < 91; i++)
		fungtionCharList.pushBack(char(i));
	fungtionCharList.pushBack(char(95));
	for (int i = 97; i < 123; i++)
		fungtionCharList.pushBack(char(i));
	fungtionCharList.pushBack(char(126));
	fungtionArgsCharList = { char(32), char(44) };
	fungtionArgsCharList += fungtionCharList;
	blueWords = { "class", "template", "typename", "char", "int", "double", "float", "long", "short", "unsigned", "signed", "auto" };
	greenWords = { "T" };
	String path = "documetasion\\classes";
	for (const auto& entry : fs::directory_iterator(toSTD(path)))
		greenWords.pushBack(String(entry.path().string()));
}

String findLocalFungtionFile(String& s) {
	if (green((*fileName)[fileName->size() - 2], 0))
		return "documentation/" + (*fileName)[fileName->size() - 2] + '/' + s + ".html";
	else if (green((*fileName)[fileName->size() - 1].split('.')[0], 0))
		return "documentation/" + (*fileName)[fileName->size() - 1].split('.')[0] + '/' + s + ".html";
	return "";
}

String findClassFile(String& s) {
	return "documentation/classes/" + s + ".html";
}

String findClassFungtionFile(String& className, String& s) {
	return "documentation/" + className + '/' + s + ".html";
}

bool manual(const String& s, int i) {
	if (s[i] == '<')
		for (; i < s.length(); i++)
			if (s[i] == '>')
				for (; i < s.length()-1; i++)
					if (s[i] == '<' && s[i + 1] == '>')
						return true;
	return false;
}

bool classFungtion(const String& s, int i) {
	if (s[i] == '.')
		return localFungtion(s, i);
	return false;
}

bool definitionFungtion(const String& s, int i) {
	if ((*fileName)[fileName->size() - 1].split('.')[0] == s(i, s.length()).split('(')[0]) {
		return true;
	}
	return false;
}

bool localFungtion(const String& s, int i) {
	definitions d;
	for (; i < s.length() - 1; i++) {
		if (s[i] == '(')
			for (; i < s.length(); i++) {
				if (s[i] == ')')
					return true;
				else if (d.fungtionArgsCharList.binarySerch(s[i]))
					return false;
			}

		else if (d.fungtionCharList.binarySerch(s[i]) == -1)
			return false;
	}
	return false;
}

bool string(const String& s, int i) {
	if (s[i] == '"')
		for (; i < s.length(); i++)
			if (s[i] == '"')
				return true;
	return false;
}

bool blue(const String& s, int i) {
	if (s[i] == ' ')
		return false;
	definitions d;
	String word = s(i, s.length());
	word = word.split(' ')[0];

	for (const String& j : d.blueWords)
		if (word == j)
			return true;
	return false;
}

bool green(const String& s, int i) {
	if (s[i] == ' ')
		return false;
	definitions d;
	String word = s(i, s.length());
	word = word.split(' ')[0];
	word = word.split('.')[0];

	for (const String& j : d.greenWords)
		if (word == j)
			return true;
	return false;
}

void fileWriter(const String& s, const String type) {
	*ofile << "<" << type << ">";
	String r = s;
	String sub;
	for (auto i = 0; i < s.length();) {
		if (manual(s, i)) {
			*ofile << '\n';
			i++;
			sub.clear();
			for (; s[i] != ',' && s[i] != '>'; i++)
				sub.pushBack(s[i]);
			if (sub != "")
				*ofile << "<a class=\"" << sub << "\"";

			if (s[i] == ',') {
				i++;
				sub.clear();
				for (; s[i] != '>'; i++)
					sub.pushBack(s[i]);
				*ofile << " href=\"" << sub << "\"";
			}
			*ofile << ">";
			sub.clear();
			for (; s[i] != '<' && s[i + 1] != '>'; i++)
				sub.pushBack(s[i]);
			*ofile << sub;
			i += 2;
			*ofile << "</a>\n";
			continue;
		}

		if (string(s, i)) {
			sub.clear();
			sub.pushBack(s[i]);
			i++;
			for (bool first = true; (s[i-1] != '"' && s[i-1] != '\'') || first; first = false, i++)
				sub.pushBack(s[i]);
			*ofile << "<a class=\"string\">" << sub << "</a>\n";
			continue;
		}

		if (classFungtion(s, i)) {
			*ofile << '\n';
			sub.clear();
			for (; s[i] != '('; i++)
				sub.pushBack(s[i]);

			*ofile << "<a class=\"fungtion\">" << sub << "</a>\n(";
			i++;
			continue;
		}

		if (localFungtion(s, i)) {
			*ofile << '\n';
			sub.clear();
			for (; s[i] != '('; i++)
				sub.pushBack(s[i]);

			String file = findLocalFungtionFile(sub);
			*ofile << "<a class=\"fungtion\"";
			if (file.length() != 0)
				*ofile << " href=\"" << file << "\"";
			*ofile << ">" << sub << "</a>\n(";
			continue;
		}

		if (green(s, i)) {
			*ofile << '\n';
			sub.clear();
			for (; s[i] != '.' || s[i] != ' '; i++)
				sub.pushBack(s[i]);

			String file = findClassFile(sub);
			*ofile << "<a class=\"classGreen\"";
			if (file.length() != 0)
				*ofile << " href=\"" << file << "\"";
			*ofile << ">" << sub << "</a>\n";

			if (classFungtion(s, i)) {
				String className = sub;
				sub.clear();
				i++;
				for (;s[i] != '('; i++)
					sub.pushBack(s[i]);
				file = findClassFungtionFile(className, sub);
				*ofile << ".\n";
				*ofile << "<a class=\"fungtion\" href=\"" << file << "\">" << sub << "</a>\n";
				*ofile << "(";
				i++;
			}
			continue;
		}

		if (blue(s, i)) {
			*ofile << '\n';
			sub.clear();
			for (; s[i] != ' '; i++)
				sub.pushBack(s[i]);
			*ofile << "<a class=\"blue\">" << sub << "</a>\n";
			continue;
		}

		*ofile << s[i];
		i++;
	}
	*ofile << "<" << type.split(' ')[0] << ">\n";
}

void FungtionList(String s) {
	Vector<String> v(s.split(':'));
	*ofile << "<tr>\n"
		<< "<th><a class = \"blue\" href = \"" + findLocalFungtionFile(v[0]) + "\">" + v[0] + "</a></th>\n"
		<< "<th>";
	fileWriter(v[1], "span");
	*ofile << "</th>\n"
		<< "</tr>\n";
}

void subList(String s) {
	s.popBack();
	*ofile << "<tr>\n"
		<< "<th>\n"
		<< "<h4 style=\"line-height: 0px;\">" + s + "</h4>\n"
		<< "</th>\n"
		<< "</tr>\n";
}