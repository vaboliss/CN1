#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>   

#define PORT 8080 
#define SA struct sockaddr 
  


int checkwin(char square[]);
void board(char square[]);

// Function designed for chat between client and server.

void func(int sockfd) 
{  
    int c;
    int n;
    char square[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    char choice;
    for (;;) { 

        read(sockfd, square, sizeof(square));
        board(square);
        c = checkwin(square);
        if (c == 1 ){
            printf("Game over. \n YOU LOOSE");
            close(sockfd);
            return;
        }
        else if ( c == 0){
            printf("Game over. \n DRAW");
            close(sockfd);
            return;
        }
        system("cls");
        board(square);
        printf("You are O\n");
        printf("Your move 1-9\n");
        for(;;)
     {
        choice = getchar();
        if(choice == '1'){
            if(square[1] == '1'){
                square[1] = 'O';
                break;
            }
        }else if( choice == '2')
        {
             if(square[2] == '2'){
                square[2] = 'O';
                break;
            }
        }else if(choice == '3')
        {
             if(square[3] == '3'){
                square[3] = 'O';
                break;
            }
        }else if(choice == '4'){
             if(square[4] == '4'){
                square[4] = 'O';
                break;
            }
        }else if(choice == '5'){
             if(square[5] == '5'){
                square[5] = 'O';
                break;
            }
        }else if(choice == '6'){
            if(square[6] == '6'){
                square[6] = 'O';
                break;
            }
        }else if(choice == '7'){
            if(square[7] == '7'){
                square[7] = 'O';
                break;
            }
        }else if(choice == '8'){
            if(square[8] == '8'){
                square[8] = 'O';
                break;
            }
        }else if(choice == '9'){
            if(square[9] == '9'){
                square[9] = 'O';
                break;
            }
        }else{
        
        }
    }

        system("cls");

        board(square);
        write(sockfd, square, sizeof(square));
        c = checkwin(square); 
        if (c == 1 ){
            printf("Game over. \n YOU WIN");
            close(sockfd);
            return;
        }
         if (c == 0 ){
            printf("Game over. \n DRAW");
            close(sockfd);
            return;
        }
        printf("Opponents turn\n");       
    } 
} 
  
// Driver function 
int main() 
{ 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
            sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
            if (sockfd == -1) { 
                printf("socket creation failed...\n"); 
                exit(0); 
            } 
            else
                printf("Socket successfully created..\n"); 
                
            bzero(&servaddr, sizeof(servaddr)); 
        
            
            servaddr.sin_family = AF_INET; 
            servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
            servaddr.sin_port = htons(PORT); 
        
          

            if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
                printf("Socket bind failed...\n"); 
                exit(0); 
            } 
            else
                printf("Socket successfully binded..\n"); 
        
           
            if ((listen(sockfd, 1)) != 0) { 
                printf("Listen failed...\n"); 
                exit(0); 
            } 
            else
                printf("Server listening..\n"); 
            len = sizeof(cli); 
        
            
            connfd = accept(sockfd, (SA*)&cli, &len); 
            if (connfd < 0) { 
                printf("server acccept failed...\n"); 
                exit(0); 
            } 
            else
                printf("Player joined game...\n"); 

            func(connfd); 
        
            close(sockfd); 
            exit(EXIT_SUCCESS);
 
               exit(EXIT_FAILURE);         
   
} 
void board( char square[])
{
    system("cls");
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