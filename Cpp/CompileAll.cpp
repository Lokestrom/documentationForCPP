#include "classCreator.hpp"
#include "FungtionCreator.hpp"
#include "LibraryAndProjectPageCreator.hpp"
#include "MainCreator.hpp"
#include "HTMLCreator.hpp"
#include "String.hpp"
#include "Vector.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace Database;
namespace fs = std::filesystem;


int main() {
	definitions d;
	for(const auto& libProject : d.libNames)
		for (const auto& className : fs::directory_iterator(toSTD("TXT/" + libProject + "/classes/"))) {
			classCreator(className.path().string());
			for (const auto& fungtionName : fs::directory_iterator(toSTD("TXT/" + libProject + "/" + String(className.path().string()).split('.')[0].split('/')[3] + "/"))) {
				fungtionCreator(fungtionName.path().string());
			}
		}

	libProjecktCreator();
	mainCreator();
}