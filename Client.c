#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <stdio.h>

#define PORT 8080 
#define SA struct sockaddr 

int checkwin(char square[]);
void board(char square[]);
void func(int sockfd);

int main() 
{ 

    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
    // function for chat 
    func(sockfd); 
  
    // close the socket 
    close(sockfd); 
} 
void board(char square[])
{
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("     |     |     \n\n");
}

int checkwin(char square[])
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
        
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
        
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
        
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
        
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
        
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
        
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
        
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
        
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] 
        != '7' && square[8] != '8' && square[9] != '9')

        return 0;
    else
        return  - 1;
}
void func(int sockfd) 
{ 
    int c;
    char square[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int n;
    int choice;
    
    
    for (;;) { 

        system("clear");
        board(square);
        printf("You are X \n Your move \n");
         for(;;){
        choice = getchar();
        if(choice == '1'){
            if(square[1] == '1'){
                square[1] = 'X';
                break;
            }
        }else if( choice == '2')
        {
             if(square[2] == '2'){
                square[2] = 'X';
                break;
            }
        }else if(choice == '3')
        {
             if(square[3] == '3'){
                square[3] = 'X';
                break;
            }
        }else if(choice == '4'){
             if(square[4] == '4'){
                square[4] = 'X';
                break;
            }
        }else if(choice == '5'){
             if(square[5] == '5'){
                square[5] = 'X';
                break;
            }
        }else if(choice == '6'){
            if(square[6] == '6'){
                square[6] = 'X';
                break;
            }
        }else if(choice == '7'){
            if(square[7] == '7'){
                square[7] = 'X';
                break;
            }
        }else if(choice == '8'){
            if(square[8] == '8'){
                square[8] = 'X';
                break;
            }
        }else if(choice == '9'){
            if(square[9] == '9'){
                square[9] = 'X';
                break;
            }
        }else{
        
        }

        } 
        
        board(square);
        printf("Opponents turn\n");
        write(sockfd, square, sizeof(square));
        c = checkwin(square);
        if (c == 1 ){
            printf("Game over. \n YOU WIN");
            close(sockfd);
            return;
        }
        else if ( c == 0){
            printf("Game over. \n DRAW");
            close(sockfd);
            return;
        }       
        read(sockfd,square,sizeof(square));
        c = checkwin(square);
        if (c == 1 ){
            printf("Game over. \n YOU LOOSE");
            close(sockfd);
            return;
        }
        if (c == 0 ){
            printf("Game over. \n DRAW");
            close(sockfd);
            return;
        }
    } 
}