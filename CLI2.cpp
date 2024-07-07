// Rylan Casanova
// 02/26/23
// CST-315
// Project 1: Improved Unix/Linux Command Line Interpreter

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

#define MAX_ARGS 10
#define MAX_LEN 100

void parseCommand(char *command, char **args)
{
    int i = 0;
    args[i] = strtok(command, " "); // split arguments string into tokens using space (" ") as the delimiter
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }
}

void executeCommand(char **args)
{
    pid_t pid = fork();
    if (pid == -1) // if parent id = -1 (does not exist)
    {
        cout << "Error: Unable to create child process" << endl;
        return;
    }
    else if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            cout << "Error: Command not found" << endl;
        }
        exit(0);
    }
    else
    {
        wait(NULL);
    }
}

int main()
{
    char *command;
    char *args[MAX_ARGS];

    while (1)
    {
        command = readline("$lopeShell: ");
        if (command == NULL) // if user pressed CTRL-D
        {
            break;
        }

        int n = strlen(command);
        if (n == 0)
        {
            continue; // if empty string (no more commands to enter)
        }

        add_history(command); // add command to history

        int i = 0;
        char *p = strtok(command, ";"); // split up multiple commands using a semicolon
        while (p != NULL)
        {
            parseCommand(p, args);


            executeCommand(args);
            p = strtok(NULL, ";");
        }
        free(command);
    }
    return 0;
}
