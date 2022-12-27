# Contributing to the documentation:
Editing of the content happens in the ".txt" files found in the TXT folder.

the TXT folder contains folder for all the libraryes and projects.<br>
In the library folders there is a classes folder containing the ".txt" files for the classes.<br>
And a folder for each of the classes containing the fungtions that involve the class.<br>

**Before pushing to the repo run the [CompileAll.cpp](Cpp/CompileAll.cpp) file in the Cpp folder.<br>
Check that the ".html" file it looks like it should in the browser.**

### Color scheme:
Classes are colored green ![#49bc8c](https://placehold.co/15x15/49bc8c/49bc8c.png)<br>
Fungtions are colored yellow ![#dad799](https://placehold.co/15x15/dad799/dad799.png)<br>
Keywords are colored blue ![#5395c2](https://placehold.co/15x15/5395c2/5395c2.png)<br>
Strings are colored brown ![#d1895e](https://placehold.co/15x15/d1895e/d1895e.png)<br>
This should be done automaticly when runing [CompileAll.cpp](Cpp/CompileAll.cpp).<br>

### Manualy define colores, other atibutes or links to text:
Costum color, other classes og link: <color or other classes, link>text<>.<br>
Costum color, other classes: <color or other classes>text<>.<br>
Costum link <,link>text<>.<br>
**Make sure that the color or other class that you use are defined in [HTML/documentationStyles/all.css](HTML/documentationStyles/all.css).<br>
The color and other classes are separated by a space.**<br>

## The class files are structured like this:
```
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
```


## The fungtion files are structured like this:
```
Declerations{
1:Decleration of the fungtion
}

Descriptions{
1:Description of the fungtion
}

Complexity{
1:the time complexity of the fungtion
}
```
This explanation may be somewhat confusing, but if you take a look at the ".txt" files, it should clarify things.
