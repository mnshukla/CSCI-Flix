/**************************
HW #3 README
Manish Shukla
CSCI 104

**************************/

DLL.h, Set.h, Mergesort.h, Queue.h are the header and implentation files (implementations inside header, no .cpp or .hpp)

main.cpp is the my main program

User.h and User.cpp are the header and implementation files respectively for the User class (step 2)

Movie.h and Movie.cpp are the header and implementation files respectively for the Movie class (step 3)

Any files ending with "Window" or "Menu" are the Qt design window/menu files

Makefile is my makefile 

Compiled using the following commands:
"qmake -project"
"qmake"
"make"

Run using terminal command "./project_mshukla [file_name]"

valgrind errors for prob4.cpp were checked using the command "valgrind --leak-check=full -v ./project_mshukla"

I had data, lib, and bin folders, but when I tried opening these files using subdirectories, I would get weird errors that I and some TA's haven't seen before, so for the
time being, I'm just going to take the deduction hit and just leave it in the main project folder. 

For the "Next Movie" button when searching a movie by title, the program seg faults and I understand why but have no idea how to fix it.

Also, when clicking "delete movie" and/or "move movie to back of queue" several times, many windows will exist, but will all be hidden. I still need to get rid of all of them.

When rating a movie after returning it, the ratings window pops up behind the User Menu window,
so you need to move the user menu to the side in order to see the ratings window and rate a movie. 

I allow for the user to modify ratings (1 B&W), search by actors based on the format in my movie_info.txt file (1 B&W), and implemented user fields with password and credit card encryption via MD5 (2 B&W) with MD5 implementation from http://www.zedwood.com/article/cpp-md5-function .

The program will seg fault when searching for a movie by title and then trying to return to the main user menu, and also when trying to rent and return several movies multiple times. 