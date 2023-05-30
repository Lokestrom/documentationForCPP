#include <Vector.hpp>
#include <String.hpp>
using namespace Database;

extern Vector<String>* fileName;
extern std::ifstream* ifile;
extern std::ofstream* ofile;

class definitions {
public:
	Vector<String> libNames;
	Vector<char> functionCharList;
	Vector<char> functionArgsCharList;
	Vector<String> blueWords;
	Vector<String> greenWords;
	definitions();
};

String returnencryptedFileName(String fileName);
String returnDecryptedFileName(String fileName);

String findLocalfunctionFile(String& s);
String findClassFile(String& s);
String findClassfunctionFile(String& className, String& s);

bool manual(const String& s, int i);
bool classfunction(const String& s, int i);
bool definitionfunction(const String& s, int i);
bool localfunction(const String& s, int i);
bool string(const String& s, int i);
bool blue(const String& s, int i);
bool green(const String& s, int i);

void fileWriter(const String& s, const String type);
void functionList(String s);
void subList(String s);