Editing of the content happens in the .txt files found in the TXT folder.

the TXT folder contains folder for all the libraryes and projects.
In the library folders there is a classes folder containing the .txt files for the classes.
And a folder for each of the classes containing the fungtions that involve the class.

Before pushing to the repo run the CompileAll.cpp file in the Cpp folder.
Check that the .html file it looks like it should in the browser.

classes are colored green
fungtions are colored yellow
keywords are colored blue
strings are colored brown

to get costum color, other classes and links the syntax is so:
costum color, other classes og link: <color or other classes, link>text<>
costum color, other classes: <color or other classes>text<>
costum link <,link>text<>
make sure that the color or other class that you use are defined in "HTML\documentationStyles\all.css"
the color and other classes are separated by a space.

The class folders are structured like this:

GitHub{
link to the .hpp file on github
cpp:link to the .cpp file on github
tpp:link to the .tpp file on github
}

class decleration{
class decleration text
}

class description{
class description text
}

List of fungtions is made up of member fungtions and non-member fungtions
they both can have sub lists for diffrent fungtions
each element has a name and a desctiption they must be seperated by a ':' character
to create a new line type <br>

member fungtions{
name:desctiption

sublist{
name:desctiption
}
}

non-member fungtions{
name:desctiption

sublist{
name:desctiption
}
}



The fungtion files are structured like this:

Declerations{
1:Decleration of the fungtion
}

Descriptions{
1:Description of the fungtion
}

Complexity{
1:the time complexity of the fungtion
}

This explanation may be somewhat confusing, but if you take a look at the .txt files, it should clarify things.