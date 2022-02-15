#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <mysql.h>
#include <time.h>
#define MAX1 7
#define MAX 4
#define MAXCOM 1000 // number of letters to be supported
#define MAXLIST 100 // number of commands to be supported
  
// Clear the shell using escape sequences  more like ESCH or ESC J
#define clear() printf("\033[H\033[J")
  
// Greeting shell during startup
void init_shell()
{
     clear();
   printf("\n\n---------------------------------------------------");
    char* username = getenv("USER");
    printf("\n\n\t Welcome %s to KinderCare CLI", username );
    printf("\n\n--------------------------------------------------");
    printf("\n");
    sleep(3);
    clear();
}
  
// Function to take input
int takeInput(char* str)
{
    char* buf;
  
    buf = readline("\n group12@group12:/Home$ ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}
  
// Function to print Current Directory.
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}
  
// Function where the system command is executed
void execArgs(char** parsed)
{
    // Forking a child
    pid_t pid = fork(); 
  
    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command..");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}
  
// Function where the piped system commands is executed
void execArgsPiped(char** parsed, char** parsedpipe)
{
    // 0 is read end, 1 is write end
    int pipefd[2]; 
    pid_t p1, p2;
  
    if (pipe(pipefd) < 0) {
        printf("\nPipe could not be initialized");
        return;
    }
    p1 = fork();
    if (p1 < 0) {
        printf("\nCould not fork");
        return;
    }
  
    if (p1 == 0) {
        // Child 1 executing..
        // It only needs to write at the write end
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
  
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command 1..");
            exit(0);
        }
    } else {
        // Parent executing
        p2 = fork();
  
        if (p2 < 0) {
            printf("\nCould not fork");
            return;
        }
  
        // Child 2 executing..
        // It only needs to read at the read end
        if (p2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            if (execvp(parsedpipe[0], parsedpipe) < 0) {
                printf("\nCould not execute command 2..");
                exit(0);
            }
        } else {
            // parent executing, waiting for two children
            wait(NULL);
            wait(NULL);
        }
    }
}
  
// Help command builtin
void openHelp()
{
    puts(
       "\nList of Commands supported:"
        "\n>Viewall --- Displays assignment number and date , showing if attempted or not"
        "\n>Checkstatus --- Displays the status report of the pupil summarizing all assignments (how many attempted, average score, percentage missed, percentage attempted etc.\n"
        "\n>Viewassignment assignmentid --- to see details of a specified assignment\n"
        "\n>Checkdates datefrom dateto --- shows if there is an assignment within a specified date range\n"
        "\n>RequestActivation --- used for pupil to request teacher to activate him or her"
        "\n>And all other linux commands\n");
    return;
}
void Viewall()
{
MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "Wisepro25*",
          "kindercare", 0, NULL, 0) == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
  }

  if (mysql_query(con, "SELECT * FROM assignments"))
  {
      fprintf(stderr, "%s\n", mysql_error(con));
  	mysql_close(con);
  	exit(1);
  }

  MYSQL_RES *result = mysql_store_result(con);

  if (result == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
  	mysql_close(con);
  	exit(1);
  }
  printf("Displaying number of assignments, Date and status");
  int num_fields = mysql_num_fields(result);
	printf("Number of assignments: %d\n", num_fields);	
  time_t tm;
    time(&tm);
    printf("Date: %s\n", ctime(&tm));
  MYSQL_ROW row;

  while ((row = mysql_fetch_row(result)))
  {
	printf("status: %s\n", row[5]);
   
  }

  mysql_free_result(result);
  mysql_close(con);
}
//checkstatus
void Checkstatus()
{
     MYSQL *con = mysql_init(NULL);
  if (mysql_real_connect(con, "localhost", "root", "Wisepro25*","kindercare", 0, NULL, 0) == NULL)
  {
    printf("Failed to connect\n");
  }
     if (mysql_query(con, "SELECT * FROM studentdetail"))
  {
      printf("Failed to collect anything");
  }
  MYSQL_RES *result = mysql_store_result(con);
  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result)))
  {
	  printf("Displaying pupil status report........\n");
      printf("noattempted: %s\n", row[1]);
   printf("averagescore: %s\n", row[2]);
   printf("percentagemissed:%s\n", row[3]);
   printf("percentageattempted	:%s\n", row[4]);
   printf("duration1:%s\n", row[5]);
   printf("duration2:%s\n", row[6]);

      printf("\n");
  }
  mysql_free_result(result);
  mysql_close(con);
    return;
}
//assignments
void Viewassignment(){
   int code;
    char sql[10000];
    printf("You must login first to attempt the assignment\n");
    printf("Enter your usercode\n");
    scanf("%d",&code);
    MYSQL *con = mysql_init(NULL);
    if (mysql_real_connect(con, "localhost", "root", "Wisepro25*","kindercare", 0, NULL, 0) == NULL)
  {
	printf("Connection failed\n");
  }
  sprintf(sql, "SELECT * FROM register WHERE usercode = '%d' AND status = 'active' ",code);
     
    if (mysql_query(con,sql) != 0)
  {
    printf("No pupil with that id\n");
  } else {
    MYSQL_RES *result = mysql_store_result(con);
  MYSQL_ROW row;
  int num_fields = mysql_num_fields(result);
  while ((row = mysql_fetch_row(result)))
  {
      if(row[4]){
           MYSQL *con = mysql_init(NULL);
  if (mysql_real_connect(con, "localhost", "root", "Wisepro25*",
          "kindercare", 0, NULL, 0) == NULL)
  {
     printf("Failed to connect");
  }
  if (mysql_query(con, "SELECT * FROM assignments"))
  {
      printf("Failed to collect anything");
  }
  MYSQL_RES *result = mysql_store_result(con);
  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result)))
  {
	  printf("Displaying assignment details........\n");
      printf("LETTER: %s\n", row[1]);
   printf("START TIME: %s\n", row[2]);
   printf("END TIME:%s\n", row[3]);
   printf("ASSIGNMENTDATE:%s\n", row[4]);
   printf("STATUS:%s\n", row[5]);
   printf("\n");

      printf("\n");
        time_t t = time(NULL);   // not a primitive datatype
        struct tm tim = *localtime(&t);          
    
      if(printf("%s \n", row[2]) >= printf("%02d:%02d:%02d\n", tim.tm_hour, tim.tm_min, tim.tm_sec)){
          printf("You are in time continuing attempting the assignment...\n");
         int num;
         	time_t first,second,third,fourth;
	    double duration1,duration2;
	    int register j,y,r;
	    char letters[]= "AB";
	int k,add2[MAX1][MAX];
	float marks,score;
    
	int A[7][4]={{32,42,42,32},{42,32,32,42},{42,32,32,42},{42,42,42,42},{42,32,32,42},{42,32,32,42},{42,32,32,42}};
	int B[7][4]={{42,42,42,32},{42,32,32,42},{42,32,32,42},{42,42,42,32},{42,32,32,42},{42,32,32,42},{42,42,42,32}}; 
	  marks =0;
	num=strlen(letters);
for(r=0;r<num;r++){
  // marking letter A
  if(letters[r]=='A'){
  	first= time(0);
  			for(j=0;j<MAX1;j++){
		        for(y=0;y<MAX;y++){
		        	begin:
		          printf("Enter 1 0r 0 for position[%d][%d]:",j,y);
			       scanf("%d",&k);
			       fflush(stdin);
			       switch(k){
				       case 0:{
					       add2[j][y]= 32;
					       break;
			    	    }
				        case 1:{
					       add2[j][y]= 42;
				           break;
				        }
				        default:{
				        	fprintf(stderr,"The value you entered is invalid\n");
				        	printf("Enter the allowable values which are 1 or 0\n");
				        	goto begin;
							break;
						}
			        }
		        }
		    printf("\n");
	        }
	        second= time(0);
	    printf("Appearance of your letter:\n");
	           for(j=0;j<MAX1;j++){
		           for(y=0;y<MAX;y++){
			          printf("%c ",add2[j][y]);
		            }
		          printf("\n");
	            }
   for(j=0;j<7;j++){
	    for(y=0;y<4;y++){
	        if(add2[j][y]==A[j][y]){
		       marks++;
	        } 	
	    }
    }
// score for 1st attempt
    score = (marks/28)*100;
     char sql[10000];
      MYSQL* conn = mysql_init(NULL);

    if (conn == NULL) {
        printf("MySQL initialization failed");
    }
    if (mysql_real_connect(conn, "localhost", "root", "Wisepro25*",
          "kindercare", 0, NULL, 0) == NULL) {
        printf("Unable to connect with MySQL server\n");
    }
      sprintf(sql, "Insert into studentdetails (averagescore) values ('%.2f')", score);
    if (mysql_query(conn,sql) != 0) {
        printf("Unable to insert data into student table\n");
    }else{
    printf("Data inserted successfully\n");
    }

  }
  // marking letter B
  if(letters[r]=='B'){
  	third = time(0);
  		for(j=0;j<MAX1;j++){
		    for(y=0;y<MAX;y++){
		        	begin2:
		        printf("Enter 1 0r 0 for position[%d][%d]:",j,y);
			       scanf("%d",&k);
			       fflush(stdin);
			       switch(k){
				       case 0:{
					       add2[j][y]= 32;
					       break;
			    	    }
				        case 1:{
					       add2[j][y]= 42;
				           break;
				        }
				        default:{
				        	fprintf(stderr,"The value you entered is invalid\n");
				        	printf("Enter the allowable values which are 1 or 0\n");
				        	goto begin2;
							break;
						}
			        }
		        }
		    printf("\n");
	        }
	        fourth = time(0);
	    printf("Appearance of your letter:\n");
	           for(j=0;j<MAX1;j++){
		           for(y=0;y<MAX;y++){
			          printf("%c ",add2[j][y]);
		            }
		          printf("\n");
	            }
    for(j=0;j<7;j++){
	    for(y=0;y<4;y++){
	        if(add2[j][y]==B[j][y]){
		      marks++;
	        } 	
		}
    }
//score
    score = (marks/28)*100;
    printf("You scored %.2f percent\n",score);
    duration2= difftime(fourth,third);
    
      }else{
          printf("You are late you can't attempt the assignment");
      }

    printf("The time taken for attempting the letter is: %f",duration2);
    }
  }

      
  }

    
      }else{
      printf("Please provide a valid student code or request to be reactivated");
      }
    printf("\n");
  }
}


    

}
//CheckDates
void Checkdates()
{
  int m1;
  int d1;
  int y1;
    int d2;
    int m2;
    int y2;
    char sql[10000];
    printf("Enter first date in (yyyy-mm-dd) format: ");
    scanf("%d-%d-%d", &y1, &m1, &d1);
      printf("Enter second date in (yyyy-mm-dd) format: ");
    scanf("%d-%d-%d", &y2, &m2, &d2);
     MYSQL *con = mysql_init(NULL);
  if (mysql_real_connect(con, "localhost", "root", "Wisepro25*","kindercare", 0, NULL, 0) == NULL)
  {
    printf("Failed to connect\n");
  }
    sprintf(sql, "SELECT * FROM assignments WHERE assigDate BETWEEN ('%04d-%02d-%02d') AND ('%04d-%02d-%02d') ",y1, m1, d1,y2, m2, d2);
     
    if (mysql_query(con,sql) != 0)
  {
    printf("Couldn't connect");
  } else {
    MYSQL_RES *result = mysql_store_result(con);
  MYSQL_ROW row;
  int num_fields = mysql_num_fields(result);
  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          printf("%s ", row[i] ? row[i] : "NULL");
      }
    printf("\n");
  }
}
}
//requestactivation
void RequestActivation()
{
	char input[25];
char sql[1000];
printf("Explain in detail why you need to be reactivated\n");
scanf("%s", input);
	MYSQL *con = mysql_init(NULL);
    if (mysql_real_connect(con, "localhost", "root", "Wisepro25*",
          "kindercare", 0, NULL, 0) == NULL)
  {
	printf("Connection failed\n");
  }

     sprintf(sql, "INSERT INTO requests (detail) VALUES ('%s')",input);
     mysql_query(con,sql);
     printf("Thanks for submitting in your request, I will let you know of my final decision!!!\n");
}

int ownCmdHandler(char** parsed)
{
    int NoOfOwnCmds = 9, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;
    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";
    ListOfOwnCmds[4] = "Viewall";
    ListOfOwnCmds[5] = "Checkstatus";
    ListOfOwnCmds[6] = "Viewassignment";
    ListOfOwnCmds[7] = "Checkdates";
    ListOfOwnCmds[8] = "RequestActivation";
    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }
  
    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        openHelp();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\n You are free to use all commands supported .", username);
        return 1; 
    case 5:
        Viewall();
        return 1;
     case 6:
        Checkstatus();
        return 1;
    case 7:
        Viewassignment();
        return 1;
    case 8:
        Checkdates();
        return 1;
    case 9:
        RequestActivation();
        return 1;
    default:
        break;
    }
  
    return 0;
}
  
// function for finding pipe
int parsePipe(char* str, char** strpiped)
{
    int i;
    for (i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }
  
    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
}
  
// function for parsing command words
void parseSpace(char* str, char** parsed)
{
    int i;
  
    for (i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");
  
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}
  
int processString(char* str, char** parsed, char** parsedpipe)
{
  
    char* strpiped[2];
    int piped = 0;
  
    piped = parsePipe(str, strpiped);
  
    if (piped) {
        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);
  
    } else {
  
        parseSpace(str, parsed);
    }
  
    if (ownCmdHandler(parsed))
        return 0;
    else
        return 1 + piped;
}
  
int main()
{
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char* parsedArgsPiped[MAXLIST];
    int execFlag = 0;
    init_shell();
  
    while (1) {
        // print shell line
        printDir();
        // take input
        if (takeInput(inputString))
            continue;
        // process
        execFlag = processString(inputString,
        parsedArgs, parsedArgsPiped);
        // execflag returns zero if there is no command
        // or it is a builtin command,
        // 1 if it is a simple command
        // 2 if it is including a pipe.
  
        // execute
        if (execFlag == 1)
            execArgs(parsedArgs);
  
        if (execFlag == 2)
            execArgsPiped(parsedArgs, parsedArgsPiped);
        //
    }
    return 0;
}
