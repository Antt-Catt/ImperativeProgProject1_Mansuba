# ReadMe File for Project Mansuba


You can compile and execute the tests by entering the command **make test** in the terminal.


To compile the project, you msut first enter **make project** in your terminal, then execute the resulting file "**./src/project**" followed by optional parameters you want to add:

+ -s to initialize the random generator (by default: time(NULL)).
+ -t to set the type of victory (s for a simple victory, and c for a complex one) (by default: s).
+ -m parameter to set the maximum number of rounds (by default: 2 x WIDTH x HEIGHT).
+ -p to activate or disactivate achiev3's rules (1 to activate, 0 to disactivate) (activated by default).
+ -a to activate or disactivate achiev4's rules (1 to activate, 0 to disactivate) (activated by default).

Not mentioning a parameter in your command line means it will be set to its default value.