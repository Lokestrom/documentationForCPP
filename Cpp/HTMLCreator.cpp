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
		functionCharList.pushBack(char(i));
	for (int i = 65; i < 91; i++)
		functionCharList.pushBack(char(i));
	functionCharList.pushBack(char(95));
	for (int i = 97; i < 123; i++)
		functionCharList.pushBack(char(i));
	functionCharList.pushBack(char(126));
	functionArgsCharList = { char(32), '&', char(44), '>', '<', ':', '*'};
	functionArgsCharList += functionCharList;
	functionArgsCharList.bubbleSort();
	blueWords = { "class", "template", "typename", "char", "int", "double", "float", "long", "short", "unsigned", "signed", "auto", "const", "noexcept", "constexpr"};
	greenWords = { "T", "sizeT, size_t"};
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

String returnencryptedFileName(String fileName) {
	Vector<char> invalidCharsInFileName = { '<', '>', '*', '/', '\\', '"', ':', '|', '?' };
	for (int i = 0; i < fileName.length(); i++) {
		if (invalidCharsInFileName.linearSearch(fileName[i]) != -1) {
			fileName.insert(i+1, "char(" + toS((int)fileName[i]) + ")");
			fileName.pop(i);
			i += 6;
		}
	}
	return fileName;
}

String returnDecryptedFileName(String fileName) {
	for (int i = 0; i < (int)fileName.length()-6; i++) {
		if (fileName(i, i + 5) == "char(") {
			String charNum;
			for (int j = i + 5; fileName[j] != ')' && j < fileName.length(); j++)
				charNum.pushBack(fileName[j]);
			fileName.pop(i, i+charNum.length()+6);
			fileName.insert(i, char(SToi(charNum)));
		}
	}
	return fileName;
}

String findLocalfunctionFile(String& s) {
	if ((*fileName)[3].split('.')[0] == s || (*fileName)[2] == s)
		return "";
	if((*fileName)[2] == "classes")
		return "../" + (*fileName)[3].split('.')[0] + "/" + returnencryptedFileName(s) + ".html";
	return "../" + (*fileName)[2] + "/" + returnencryptedFileName(s) + ".html";
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

String findClassfunctionFile(String& className, String& s) {
	return "../" + className + '/' + returnencryptedFileName(s) + ".html";
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

bool classfunction(const String& s, int i) {
	if (s[i] == '.')
		return localfunction(s, ++i);
	return false;
}

bool definitionfunction(const String& s, int i) {
	if ((*fileName)[fileName->size() - 1].split('.')[0] == s(i, s.length()).split('(')[0]) {
		return true;
	}
	return false;
}

bool localfunction(const String& s, int i) {
	definitions d;
	for (; i < s.length() - 1; i++) {
		if (s[i] == '(') {
			i++;
			for (; i < s.length(); i++) {
				if (s[i] == ')')
					return true;
				else if (s[i] == '<')
					for (; s[i] != '>' && i < s.length(); i++);
				else if (d.functionArgsCharList.binarySearch(s[i]) == -1) {
					return false;
				}
			}
		}
		else if (d.functionCharList.binarySearch(s[i]) == -1)
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

		if (localfunction(s, i)) {
			sub.clear();
			for (; s[i] != '('; i++)
				sub.pushBack(s[i]);

			String file = findLocalfunctionFile(sub);
			*ofile << "<a class=\"function\"";
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

			if (classfunction(s, i)) {
				String className = sub;
				sub.clear();
				i++;
				for (;s[i] != '('; i++)
					sub.pushBack(s[i]);
				file = findClassfunctionFile(className, sub);
				*ofile << ".";
				*ofile << "<a class=\"function\" href=\"" << file << "\">" << sub << "</a>";
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

void functionList(String s) {
	String text = s(s.linearSearch(':') + 1, s.length());
	*ofile << "<tr>\n"
		<< "<th><a class = \"blue\" href = \"" + findLocalfunctionFile(s.split(':')[0]) + "\">" + s.split(':')[0] + "</a></th>\n"
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