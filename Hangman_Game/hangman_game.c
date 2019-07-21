/*		Github --> https://github.com/singhiqbal1007/
		C Program for hangman game.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#define N 40

char movie_name[N];
char allowed_char[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9','\0'};
char used_char[N] = {'A','E','I','O','U', '\0'};
int used_char_size = 5;

/* Get a Random movie name from the file */
void getMovieName(){
    FILE* file = fopen("movies.txt", "r");
    char line[256], chr,i;
    int count = 0, random_line;
    while (fgets(line, sizeof(line), file)) {
        count++;
    }
    srand(time(0));
    random_line = rand() % count + 1;

    count = 0;
    file = fopen("movies.txt", "r");
    while (fgets(line, sizeof(line), file)) {
        count++;
        if(count==random_line){
            i=0;
            while(line[i]!='\n'){
                movie_name[i]=toupper(line[i]);
                i++;
            }
            movie_name[i+1] = '\0';
        }
    }
    fclose(file);
}

/* Check if User Wins */
char isWinner(char user_movie[]){
    if(strcmp(user_movie,movie_name) == 0){
        return 't';
    }
    else return 'f';
}

/*check if character is already used or not */
char check_used_char(char guess){
    int i=0;
    while(used_char[i]!= '\0'){
        if(guess == used_char[i]){
            return 't';
        }
        i++;
    }
    used_char[used_char_size] = guess;
    used_char[used_char_size+1] = '\0';
    used_char_size++;
    return 'f';
}

/* check if character is allowed */
char check_allowed_char(char guess){
    int i=0;
    while(allowed_char[i]!= '\0'){
        if(guess == allowed_char[i]){
            return 't';
        }
        i++;
    }
    return 'f';
}


/* check if character is present in movie name */
char check_movie_name(char guess){
    int i=0;
    while(movie_name[i] != '\0'){
        if(guess == movie_name[i]){
            return 't';
        }
        i++;
    }
    return 'f';

}


/* update user_movie array */
void update_user_movie(char user_movie[], int n){
    int i,j, flag;
    for(i=0;i<n;i++){
        j=0;
        flag = 0;
        while(used_char[j] != '\0'){
            if(used_char[j] == movie_name[i]){
                flag = 1;
                user_movie[i]= used_char[j];
                break;
            }
            j++;
        }

        if(movie_name[i]==' '){
            user_movie[i] = ' ';
        }
        else if(flag==0){
            user_movie[i]='_';
        }
    }
    user_movie[i]='\0';
}

/* main function */
void main(){
    int n,tries = 5;
    char user_movie[N], user_guess;
    getMovieName();
    n = strlen(movie_name);
    update_user_movie(user_movie, n);
    printf("***********WELCOME TO HANGMAN*************\n\n");
    while(tries != 0){
        printf("Guess Movie Name\n");
        printf("%s",user_movie);
        printf("          tries left = %d\n",tries);
        printf("Enter a character: ");
        scanf(" %c", &user_guess);
        user_guess = toupper(user_guess);

        if(check_allowed_char(user_guess) == 'f'){
            printf("%c is not allowed.\n\n",user_guess);
            continue;
        }


        if(check_used_char(user_guess) == 't'){
            printf("You have already guessed %c. Try Another.\n\n",user_guess);
            continue;
        }

        if(check_movie_name(user_guess) == 't'){
            printf("CORRECT GUESS!!!\n\n");

            update_user_movie(user_movie, n);

            if(isWinner(user_movie) == 't'){
                 printf("%s",movie_name);
                 printf("\nYou Win\n");
                 break;
            }
            else{
                continue;
            }
        }
        else{
            printf("INCORRECT GUESS!!!! Try Again.\n\n");
            tries--;
            if(tries > 0 ){
                continue;
            }
            else{
                 printf("Movie was %s",movie_name);
                 printf("\nYou Lose\n");
                 break;
            }
        }
    }
}
