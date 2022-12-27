#include "HTMLCreator.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace Database;
namespace fs = std::filesystem;

Vector<String>* fileName;
std::ifstream* ifile;
std::ofstream* ofile;

definitions::definitions() {
	for (int i = 48; i < 58; i++)
		fungtionCharList.pushBack(char(i));
	for (int i = 65; i < 91; i++)
		fungtionCharList.pushBack(char(i));
	fungtionCharList.pushBack(char(95));
	for (int i = 97; i < 123; i++)
		fungtionCharList.pushBack(char(i));
	fungtionCharList.pushBack(char(126));
	fungtionArgsCharList = { char(32), '&', char(44), '>', '<', ':', '*'};
	fungtionArgsCharList += fungtionCharList;
	fungtionArgsCharList.bubbleSort();
	blueWords = { "class", "template", "typename", "char", "int", "double", "float", "long", "short", "unsigned", "signed", "auto", "const", "noexcept", "constexpr"};
	greenWords = { "T", "sizeT"};
	String path = "TXT/";
	String i;
	std::filesystem::path pathPath = toSTD(path);
	for (const auto& files : fs::directory_iterator(pathPath)) {
		libNames.pushBack(String(files.path().string()).split('/')[1]);
		for (const auto& entry : fs::directory_iterator(files.path().string())) {
			i = entry.path().string();
			if (i.split('\\')[1] != "classes")
				greenWords.pushBack(i.split('\\')[1]);
		}
	}
}

String findLocalFungtionFile(String& s) {
	if ((*fileName)[3].split('.')[0] == s || (*fileName)[2] == s)
		return "";
	if((*fileName)[2] == "classes")
		return "../" + (*fileName)[3].split('.')[0] + "/" + s + ".html";
	return "../" + (*fileName)[2] + "/" + s + ".html";
}

String findClassFile(String& s) {
	definitions d;
	if (s == (*fileName)[3].split('.')[0] || s == (*fileName)[2])
		return "";
	for (const auto& dir : fs::directory_iterator("HTML/")) {
		if (d.libNames.linearSearch(String(dir.path().string()).split('/')[1]) != -1) {
			for (const auto& entry : fs::directory_iterator(dir.path().string() + "/classes/")) {
				String file = entry.path().string();
				if (file.split('/')[3].split('.')[0] == s)
					return "../../../" + entry.path().string();
			}
		}
	}
	return "";
}

String findClassFungtionFile(String& className, String& s) {
	return "../" + className + '/' + s + ".html";
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
		return localFungtion(s, ++i);
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
		if (s[i] == '(') {
			i++;
			for (; i < s.length(); i++) {
				if (s[i] == ')')
					return true;
				else if (s[i] == '<')
					for (; s[i] != '>' && i < s.length(); i++);
				else if (d.fungtionArgsCharList.binarySearch(s[i]) == -1) {
					return false;
				}
			}
		}
		else if (d.fungtionCharList.binarySearch(s[i]) == -1)
			return false;
	}
	return false;
}

bool string(const String& s, int i) {
	if (s[i] == '"' || s[i] == char(39))
		for (; i < s.length(); i++)
			if (s[i] == '"' || s[i] == char(39))
				return true;
	return false;
}

bool blue(const String& s, int i) {
	if ((s[i] == ' ') || (s[i] == '>') || (s[i] == '<') || (s[i] == ';') || (s[i] == '&') || (s[i] == '*'))
		return false;
	definitions d;
	String word = s(i, s.length());
	word = word.split(' ')[0];
	word = word.split('>')[0];
	word = word.split('<')[0];
	word = word.split(';')[0];
	word = word.split('&')[0];
	word = word.split('*')[0];

	for (const String& j : d.blueWords)
		if (word == j)
			return true;
	return false;
}

bool green(const String& s, int i) {
	if ((s[i] == '.') || (s[i] == ' ') || (s[i] == ';') || (s[i] == '>') || (s[i] == '<') || (s[i] == ')') || (s[i] == '&'))
		return false;
	definitions d;
	String word = s(i, s.length());
	word = word.split(' ')[0];
	word = word.split('.')[0];
	word = word.split(';')[0];
	word = word.split('>')[0];
	word = word.split('<')[0];
	word = word.split(')')[0];
	word = word.split('&')[0];
	
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
			sub.clear();
			for (; s[i] != '<' && s[i + 1] != '>'; i++)
				sub.pushBack(s[i]);
			*ofile << sub;
			i += 2;
			*ofile << "</a>";
			continue;
		}

		if (string(s, i)) {
			sub.clear();
			sub.pushBack(s[i]);
			i++;
			for (bool first = true; (s[i-1] != '"' && s[i-1] != '\'') || first; first = false, i++)
				sub.pushBack(s[i]);
			*ofile << "<a class=\"string\">" << sub << "</a>";
			continue;
		}

		if (localFungtion(s, i)) {
			sub.clear();
			for (; s[i] != '('; i++)
				sub.pushBack(s[i]);

			String file = findLocalFungtionFile(sub);
			*ofile << "<a class=\"fungtion\"";
			if (file.length() != 0)
				*ofile << " href=\"" << file << "\"";
			*ofile << ">" << sub << "</a>(";
			i++;
			continue;
		}

		if (green(s, i)) {
			sub.clear();
			for (; (s[i] != '.') && (s[i] != ' ') && (s[i] != ';') && (s[i] != '>') && (s[i] != '<') && (s[i] != ')') && (s[i] != '&') && i < s.length(); i++)
				sub.pushBack(s[i]);

			String file = findClassFile(sub);
			*ofile << "<a class=\"classGreen\"";
			if (file.length() != 0)
				*ofile << " href=\"" << file << "\"";
			*ofile << ">" << sub << "</a>";

			if (classFungtion(s, i)) {
				String className = sub;
				sub.clear();
				i++;
				for (;s[i] != '('; i++)
					sub.pushBack(s[i]);
				file = findClassFungtionFile(className, sub);
				*ofile << ".";
				*ofile << "<a class=\"fungtion\" href=\"" << file << "\">" << sub << "</a>";
				*ofile << "(";
				i++;
			}
			continue;
		}

		if (blue(s, i)) {
			sub.clear();
			for (; s[i] != ' ' && (s[i] != '>') && (s[i] != '<') && (s[i] != ';') && (s[i] != '&') && (s[i] != '*'); i++)
				sub.pushBack(s[i]);
			*ofile << "<a class=\"blue\">" << sub << "</a>";
			continue;
		}
		if (s[i] == '<')
			if (s(i, i + 4) == "<br>") {
				*ofile << "<br>";
				i += 3;
			}
			else
				*ofile << "&lt;";
		else if(s[i] == '>')
			*ofile << "&gt;";
		else
			*ofile << s[i];
		i++;
	}
	*ofile << "</" << type.split(' ')[0] << ">\n";
}

void FungtionList(String s) {
	String text = s(s.linearSearch(':') + 1, s.length());
	*ofile << "<tr>\n"
		<< "<th><a class = \"blue\" href = \"" + findLocalFungtionFile(s.split(':')[0]) + "\">" + s.split(':')[0] + "</a></th>\n"
		<< "<th>";
	fileWriter(text, "span");
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