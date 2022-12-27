#include "LibraryAndProjectPageCreator.hpp"
#include "HTMLCreator.hpp"

#include <fstream>
#include <filesystem>

using namespace Database;
namespace fs = std::filesystem;

void libProjecktCreator()
{
    definitions d;
    for (auto& libProjectName : d.libNames) {
        ofile = new std::ofstream("HTML\\" + toSTD(libProjectName) + "\\" + toSTD(libProjectName) + ".html");
        String text;

        *ofile << "<!DOCTYPE html>\n"
            << "<head>\n"
            << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>\n"
            << "<link rel=\"stylesheet\" href = \"../documentationStyles/all.css\">\n"
            << "<link rel=\"stylesheet\" href=\"../documentationStyles/libProject.css\">\n"
            << "</head>\n"
            << "<header>\n"
            << "<br>\n"
            << "<a class=\"homeButton\" href=\"../main.html\">Home</a>\n"
            << "<h1 class=\"white underline\">" + libProjectName + " documentation</h1>\n"
            << "</header>\n"
            << "<body class=\"background\">\n"
            << "<p class=\"GitHub\">\n"
            << "<span class=\"white\">GitHub:</span>\n"
            << "<br>\n"
            << "<a href=\"https://github.com/Lokestrom/" + libProjectName + "\">" + libProjectName + "</a>\n"
            << "</p>\n"
            << "<ul class=\"list\">\n";
        std::filesystem::path path = toSTD("HTML/" + toSTD(libProjectName) + "/classes");
        for (const auto& className : fs::directory_iterator(path))
            *ofile << "<li><a href=\"../../" + className.path().string() + "\">" + String(className.path().string()).split('.')[0].split('\\')[1] + "</a></li>\n";
        *ofile << "</ul>\n</body>";
    }
}