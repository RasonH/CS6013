 #include <iostream>
 #include <vector>
 #include "shelpers.hpp"



 int main(int argc, const char * argv[]) {
     std::string input;
     std::vector<std::string> tokens;

     while(std::cout << "shell$ " && getline(std::cin, input)) {

         // check if the user entered "exit"
         if(input == "exit"){
             std::cout << "Exit shell." << std::endl;
             exit(0);
         }

         // parse user input to commands
         tokens = tokenize(input);
         std::vector<Command> commands = getCommands(tokens);

         // initialize for multiple process
         std::vector<pid_t> pids;

         // loop over each command
         for (int i = 0; i < commands.size(); i++) {

             // fork a new process
             int pid = fork();

             if (pid < 0) { // error occurred during fork
                 perror("fork failed!");
                 exit(1);
             }
             else if (pid == 0) { // in child process
            
                 // redirect fdStdin to the appropriate input file descriptor
                 int d1 = dup2(commands[i].fdStdin, 0);
                 if (d1 == -1) { // error occurred during redirection
                     perror("fdStdin failed!");
                     exit(1);
                 }

                 int d2 = dup2(commands[i].fdStdout, 1);
                 // redirect fdStdout to the appropriate output file descriptor
                 if (d2 == -1) { // error occurred during redirection
                     perror("fdStdout failed!");
                     exit(1);
                 }
                 // execute the command using the execvp function
                 int ret = execvp(commands[i].exec.c_str(), const_cast<char *const *>(commands[i].argv.data()));
                 if (ret == -1) { // error occurred during execution
                     perror("execvp failed!");
                     exit(1);
                 }
             }
             else { // in parent process
                 // close input/output file descriptors
                 if (commands[i].fdStdin != 0)
                     close(commands[i].fdStdin);
                 if (commands[i].fdStdout != 1)
                     close(commands[i].fdStdout);

                 // keep track of the child process ids
                 pids.push_back(pid);
                 int Status;

                 // wait for the child processes to finish
                 if (!commands[i].background) {
                     for (pid_t p: pids) {
                         waitpid(p, &Status, 0);
                     }
                 }
                     // print the child process ids when running in the background
                 else {
                     for (pid_t p: pids) {
                         std::cout << p << std::endl;
                     }
                 }

                 // Part 4: shell builtins CD:
                 if (commands[i].exec == "cd") {
                     // if there is no argument after "cd"
                     if (commands[i].argv.size() == 2) {
                         chdir(getenv("HOME"));
                     }
                     // if there is an argument after "cd", change directory to that argument
                     else if (commands[i].argv.size() > 2){
                         chdir(commands[i].argv[1]);
                     }
                 }
             }
         }
         // clear user input string for next iteration
         input.clear();
     }
     return 0;
 }
