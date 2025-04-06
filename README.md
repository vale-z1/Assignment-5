This is the template for the fifth assignment - note that we don't have a template anymore, to prepare you for the final project. 

# Notes

The template is prepared to have everything in a single file, since splitting in interface and implementation gives challenge marks and the students should be using elements from the pre-lecture to make that compile (tip: remember also include guards like #IFNDEF to avoid including the headers too many times). 

# Tips on compilation 

If you want to use the same line that the demonstrators will use, print this in your terminal. 

`g++-11 -g myFirstClass.cpp mySecondClass.cpp myThirdClass.cpp myMain.cpp -o assignment-5.o -std=gnu++17`

The std=gnu++17 makes sure that the compiler you're using locally (which you should have installed following the instructions on the Quickstart guide on Blackboard/Git) picks up the same version of the C++ standards as the computers in the lab. Note:do not use g++ on Mac, or you'll get clang. 

You have to substitute the myFirstClass etc with the names of your cpp files. Also include the line that you use for compiling in a text file (e.g. called README) in your submission. 