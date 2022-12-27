#include "MainCreator.hpp"
#include "HTMLCreator.hpp"

#include <fstream>

using namespace Database;

void mainCreator()
{
    definitions d;
    ofile = new std::ofstream("HTML\\main.html");

    *ofile << "<!DOCTYPE html>\n"
        << "<head>\n"
        << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>\n"
        << "<link rel=\"stylesheet\" href = \"documentationStyles/all.css\">\n"
        << "<link rel=\"stylesheet\" href=\"documentationStyles/libProject.css\">\n"
        << "</head>\n"
        << "<header>\n"
        << "<h1 class=\"white underline\">Documentation</h1>\n"
        << "</header>\n"
        << "<body class=\"background\">\n"
        << "<ul class=\"list\">\n";
    for (const auto& libProjectName : d.libNames)
        *ofile << "<li><a href=\"" + libProjectName + "\\" + libProjectName + ".html\">" + libProjectName + "</a></li>\n";
    *ofile << "</ul>\n</body>";
}