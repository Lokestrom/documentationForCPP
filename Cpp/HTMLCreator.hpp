#include <Vector.hpp>
#include <String.hpp>
using namespace Database;

extern Vector<String>* fileName;
extern std::ifstream* ifile;
extern std::ofstream* ofile;

class definitions {
public:
	Vector<String> libNames;
	Vector<char> fungtionCharList;
	Vector<char> fungtionArgsCharList;
	Vector<String> blueWords;
	Vector<String> greenWords;
	definitions();
};

String findLocalFungtionFile(String& s);
String findClassFile(String& s);
String findClassFungtionFile(String& className, String& s);

bool manual(const String& s, int i);
bool classFungtion(const String& s, int i);
bool definitionFungtion(const String& s, int i);
bool localFungtion(const String& s, int i);
bool string(const String& s, int i);
bool blue(const String& s, int i);
bool green(const String& s, int i);

void fileWriter(const String& s, const String type);
void FungtionList(String s);
void subList(String s);