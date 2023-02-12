#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[]) {
    // print to indicate parent process
    std::cout << "Parent process [" << getpid() << "] running, enter parent code block:" << std::endl;

    // check for correct command line argument input
    if(argc != 2){
        std::cerr << "No message passed. Correct usage: ./<programName> <message>." << std::endl;
    }

    // initialize pipe, pipe_fd[0] for reading, fd[1] for writing
    int pipe_fd[2]; // can be also done with "int *pipe_fd = new int[2];", then remember to "delete[]" afterwards

    // check for error in creating pipe
    if(pipe(pipe_fd) == -1){
        perror("Error occurred when creating pipe.");
        exit(1);
    }
    std::cout << "New pipe [" << pipe_fd << "] has created." << std::endl;

    // fork a child process
    int pid = fork();
    // without the if statement to specify which process, now currently on both process, do this:
    std::cout << "\n--- line after fork() running on different process [" << getpid() << "] --- (code only occurred once but print for all processes.)" << std::endl;
    // check error for fork
    if(pid == -1){
        perror("Error occurred when forking child precess.");
        exit(1);
    }


    // child process - do required tasks
    if(pid == 0){
        // print to indicate child process
        std::cout << "Child process [" << getpid() << "] running, enter child code block:" << std::endl;

        // close the writing end of the pipe, only needs to read from its parent
        close(pipe_fd[1]);

        // read message from its parent - length of message & message string
        int msgLength;
        //  read length of message, check error
        if(read(pipe_fd[0], &msgLength, sizeof(msgLength) == -1)){
            perror("Error occurred when reading the length of message.");
            exit(1);
        }
        // allocate buffer memory for the message
        char* msg = new char[msgLength + 1];
        // read message string, check error
        if(read(pipe_fd[0], msg, msgLength) == -1){
            perror("Error occurred when reading the message string.");
            exit(1);
        }
        // add a null terminator to the end of the message
        msg[msgLength] = '\0';

        // print the message received from its parent
        std::cout << "Child process [" << getpid() << "] has received message \"" << msg << "\" from its parent process [" << getppid() << "] through pipe [" << pipe_fd << "]." << std::endl;

        // release memory
        delete[] msg;

        // close the reading end of the pipe
        close(pipe_fd[0]);

        std::cout << "Prompt from child process [" << getpid() << "]: child process ready to exit." << std::endl;
        // exit child process
        return 0;


    }else{ // continue the code block for the parent process, can also switch places with child code block
        // close the reading end of the pipe, only needs to write to its child
        close(pipe_fd[0]);

        // get message from the command line
        char* msg = argv[1];
        int msgLength = std::strlen(msg);

        // write the length of the message, check error
        if(write(pipe_fd[1], &msgLength, sizeof(msgLength) == -1)){
            perror("Error occurred when writing the length of message.");
            exit(1);
        }

        // write the message string, check error
        if(write(pipe_fd[1], msg, msgLength) == -1){
            perror("Error occurred when writing the message string.");
            exit(1);
        }

        std::cout << "Parent process [" << getpid() << "] has sent message\"" << msg << "\" to its child process [" << pid << "] through pipe [" << pipe_fd << "]." << std::endl;

        // close the writing end of the pipe
        close(pipe_fd[1]);

        // wait until child process exit, then exit parent
        std::cout << "Parent process [" << getpid() << "] waiting for child process [" << pid << "] to exit." << std::endl;
        int status;
        waitpid(pid, &status, 0);

        std::cout << "\n--- line continue running on parent process [" << getpid() << "] ---" << std::endl;
        std::cout << "Prompt from parent process [" << getpid() << "]: child process has exited, parent process ready to exit." << std::endl;

        //exit parent process
        return 0;
    }
}
