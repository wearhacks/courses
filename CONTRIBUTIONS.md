# Contributions guidelines

Contributions to this repository are more than welcome. You are free to make modifications or additions and to send us 
a pull request which we will verify and then merge. 

The following document provides general informations and tips as to how to organize 
and format new projects' contributions. 

## Repository organization

A **project** folder is typically composed of an **instruction file** and 3 folders:
one containing the **source files** (Eagle files of the schematic of the project per example), 
one holding the **illustrations** of the project and finally one for the code. 

A **guide** explores a specific concept/technology. It is used to centralize the information about 
something that can be considered usefull for several projects. 

## Instructions formating 

### Markdown

Github uses a special syntax to format the **.md** files. The text files you will create will need
to use this format. You can start here if you are not familiar with it:

[Markdown basics](https://help.github.com/articles/markdown-basics/)
[Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

### Document Skeleton

The following lines are to be seen only are a source of inspiration. You are obviously free to 
organize things differently if you judge that it would improve the overall clarity of your content. 

A project start by an **introduction** paragraph summing up the project: the main features are evoqued 
and the educational aspects involved are underlined. 

A **list of the components** needed for the project is then provided. The electronic components should ideally include a link
to their datasheet. 

Then comes the **walkthrough** itself. It is organized modularly: every module of the project is first tested independently in order to test the components.
Software and Hardware are kept seperated if possible but modules are built by functional similarity before all. 

The document ends with a list of the sources that were used during the making of the project or the redaction of the tutorial. 


### Medias
**Pictures** of the project at its different stages, **schematic** or **fritzting diagrams** of the circuit, **3D models**, **Youtube videos**...
The addition of any form of illustration to the guides and projects is greatly encouraged. 

[Fritzing](http://fritzing.org/home/) can be used to draw breadboard circuits illustrations, draw schematics and conceive PCBs. 
[Eagle](http://www.cadsoftusa.com/download-eagle/?CMP=KNC-GUS-FUS-GEN-SUP-CAD-Eeagle) can also be used if need be. 

