#include <stdio.h>
#include <conio.h>
#include <string.h>
#include<graphics.h>

struct Name {
    char book_name[50];
    char author_firstname[20];
    char author_lastname[20];
};

struct issued_date {
    int day, month, year;
};

struct book {
    char category[50];
    int price;
    struct Name name;
    struct issued_date date;
};



// ---------------- FUNCTIONS ----------------

void addbooks() {
    struct book lib;
    FILE *fp = fopen("books.txt", "a");
    clrscr();

    printf("Enter book name: ");
    fflush(stdin);  // to clear the input buffer.
    gets(lib.name.book_name);

    printf("Enter author first name: ");
    fflush(stdin);
    gets(lib.name.author_firstname);

    printf("Enter author last name: ");
    fflush(stdin);
    gets(lib.name.author_lastname);

    printf("Enter category: ");
    fflush(stdin);
    gets(lib.category);

    printf("Enter issued date (DD MM YYYY): ");
    scanf("%d %d %d", &lib.date.day, &lib.date.month, &lib.date.year);

    printf("Enter price: ");
    scanf("%d", &lib.price);

    fprintf(fp, "%s %s %s %s %d %d %d %d\n",
	    lib.name.book_name,
	    lib.name.author_firstname, lib.name.author_lastname,
	    lib.category,
	    lib.date.day, lib.date.month, lib.date.year,
	    lib.price);

    fclose(fp);
    printf("Written Successfully!\n");
}

void display_books() {
    struct book lib;
    FILE *fp = fopen("books.txt", "r");
    char line[300];
    int gd=DETECT, gm;
    int y = 40;  // starting vertical position

    if (fp == NULL) {
        printf("Error opening file!");
        return;
    }

    // Skip header lines if present
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    // Initialize graphics
    initgraph(&gd, &gm, "c:\\turboc3\\bgi");

    // Draw rectangle background
    setcolor(WHITE);
    rectangle(10, 10, 630, 470);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(15, 15, WHITE);

    // Title
    outtextxy(20, 20, "All Books:");

    // Loop through all records
    while (fscanf(fp, "%s %s %s %s %d %d %d %d",
		  lib.name.book_name,
		  lib.name.author_firstname, lib.name.author_lastname,
		  lib.category,
		  &lib.date.day, &lib.date.month, &lib.date.year,
		  &lib.price) != EOF)
    {
	// Prepare one-line record
	sprintf(line, "%s | %s %s | %s | %02d-%02d-%04d | Rs.%d",
		lib.name.book_name,
		lib.name.author_firstname, lib.name.author_lastname,
		lib.category,
		lib.date.day, lib.date.month, lib.date.year,
		lib.price);

	// Print inside rectangle
	outtextxy(20, y, line);
	y += 20;

	// If rectangle fills up, pause and clear for next batch
	if (y > 450) {
	    outtextxy(20, y, "--Press any key for more--");
	    getch();
	    cleardevice();  // to clear the graphics screen and reset the current position coordinates to (0,0).
	    rectangle(10, 10, 630, 470);
	    setfillstyle(SOLID_FILL,BLUE);
	    floodfill(15, 15, WHITE);
	    y = 40;
	}
    }

    fclose(fp);
    getch();
    closegraph();
}


void books_after_date() {
    struct book lib;
    FILE *fp = fopen("books.txt", "r");
    char line[300];
    int x = 10, y = 50;   // starting position for text x = x_coordinate ,y=y_coordinate
    int gd = DETECT, gm;

    if (fp == NULL) {
	printf("Error opening file!");
	return;
    }

    // Skip header lines
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    // Initialize graphics once
    initgraph(&gd, &gm, "c:\\turboc3\\bgi");

    // Draw one big rectangle
    rectangle(5, 10, 630, 250);
    setfillstyle(SOLID_FILL,MAGENTA);
    floodfill(15,50,WHITE);


    // Title inside rectangle
    sprintf(line,"Books issued after 01-01-2026:");
    outtextxy(10, 20,line);
    outtextxy(10,26,"______________________________");


    // Loop through all records
    while (fscanf(fp, "%s %s %s %s %d %d %d %d",
		  lib.name.book_name,
		  lib.name.author_firstname, lib.name.author_lastname,
		  lib.category,
		  &lib.date.day, &lib.date.month, &lib.date.year,
		  &lib.price) != EOF) {

	if (lib.date.year > 2026 ||
	   (lib.date.year == 2026 && lib.date.month > 1) ||
	   (lib.date.year == 2026 && lib.date.month == 1 && lib.date.day > 1)) {

	    // Prepare one-line record
	    sprintf(line, "%-24s| %-7s %-8s| %-10s| %02d-%02d-%04d| Rs.%d",
		    lib.name.book_name,
		    lib.name.author_firstname, lib.name.author_lastname,
		    lib.category,
		    lib.date.day, lib.date.month, lib.date.year,
		    lib.price);

	    // Print inside rectangle
	    outtextxy(x, y, line);
	    y += 20; // move down for next record
	}
    }

    fclose(fp);
    getch();
    closegraph();
}


void count_books_per_category() {
    struct book lib;
    FILE *fp = fopen("books.txt", "r");
    char line[200];
    int cs=0,it=0,management=0,network=0,database=0;
    int gd=DETECT,gm;

    if (fp == NULL) {
	printf("Error opening file!");
	return;
    }

    // Skip header lines if present
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    // Initialize graphics once
    initgraph(&gd, &gm, "c:\\turboc3\\bgi");

    // Draw one big rectangle
    setcolor(WHITE);
    rectangle(10, 10, 350, 180);
    setfillstyle(SOLID_FILL, MAGENTA);
    floodfill(15, 15, WHITE);

    // Count categories
    while (fscanf(fp, "%s %s %s %s %d %d %d %d",
		  lib.name.book_name,
		  lib.name.author_firstname, lib.name.author_lastname,
		  lib.category,
		  &lib.date.day, &lib.date.month, &lib.date.year,
		  &lib.price) != EOF)
    {
	if(strcmp(lib.category,"cs")==0) cs++;
	else if(strcmp(lib.category,"it")==0) it++;
	else if(strcmp(lib.category,"management")==0) management++;
	else if(strcmp(lib.category,"network")==0) network++;
	else if(strcmp(lib.category,"database")==0) database++;
    }

    // Display results neatly

    outtextxy(20, 30,"Books per category:");
    outtextxy(20,36,"__________________");

    sprintf(line,"CS         : %d", cs);
    outtextxy(20,50,line);

    sprintf(line,"IT         : %d", it);
    outtextxy(20,70,line);

    sprintf(line,"Management : %d", management);
    outtextxy(20,90,line);

    sprintf(line,"Network    : %d", network);
    outtextxy(20,110,line);

    sprintf(line,"Database   : %d", database);
    outtextxy(20,130,line);

    getch();
    closegraph();
    fclose(fp);
}


void most_and_least_expensive() {
    struct book lib, max_book, min_book;
    FILE *fp = fopen("books.txt", "r");
    char line[200];
    int max_price=-1, min_price=999999;
    int gd=DETECT,gm;
    clrscr();
    if (fp == NULL) {
	printf("Error opening file!");
	return;
    }

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    while (fscanf(fp, "%s %s %s %s %d %d %d %d",
		  lib.name.book_name,
		  lib.name.author_firstname, lib.name.author_lastname,
		  lib.category,
		  &lib.date.day, &lib.date.month, &lib.date.year,
		  &lib.price) != EOF) {
	if(lib.price > max_price) { max_price = lib.price; max_book = lib; }
	if(lib.price < min_price) { min_price = lib.price; min_book = lib; }
    }


    initgraph(&gd, &gm, "c:\\turboc3\\bgi");
    setcolor(WHITE);
    rectangle(10, 10, 400, 130);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(15, 15, WHITE);


    outtextxy(20, 20, "Most Expensive Book:");
    outtextxy(20,26,"____________________");
    sprintf(line,"Book name: %s",max_book.name.book_name);
    outtextxy(20,40,line);

    sprintf(line,"Author name: %s %s",
		max_book.name.author_firstname,max_book.name.author_lastname);
    outtextxy(20,60,line);

    sprintf(line,"Category: %s",max_book.category);
    outtextxy(20,80,line);

    sprintf(line,"Issued date: %02d-%02d-%04d",
		 max_book.date.day,max_book.date.month,max_book.date.year);
    outtextxy(20,100,line);

    sprintf(line,"Price: Rs.%d",max_book.price);
    outtextxy(20,120,line);


    setcolor(WHITE);
    rectangle(10,150,400,280);
    setfillstyle(SOLID_FILL,LIGHTRED);
    floodfill(15,155,WHITE);

    outtextxy(20, 160, "Least Expensive Book:");
    outtextxy(20,166,"_____________________");

    sprintf(line,"Book name: %s", min_book.name.book_name);
    outtextxy(20,180,line);

    sprintf(line,"Author name: %s %s",
	       min_book.name.author_firstname, min_book.name.author_lastname);
    outtextxy(20,200,line);

    sprintf(line,"Category: %s",min_book.category);
    outtextxy(20,220,line);

    sprintf(line,"Issued date: %02d-%02d-%04d",
	    min_book.date.day, min_book.date.month, min_book.date.year);
    outtextxy(20,240,line);

    sprintf(line,"price: Rs.%d",min_book.price);
    outtextxy(20,260,line);

    getch();
    closegraph();
    fclose(fp);
}

void books_by_author() {
    struct book lib;
    FILE *fp = fopen("books.txt", "r");
    char line[200];
    char search_first[20], search_last[20];
    int gd=DETECT, gm;
    int y = 45;
    int found=0;

    if (fp == NULL) {
	printf("Error opening file!");
	return;
    }

    printf("Enter author first name: ");
    scanf("%s", search_first);
    printf("Enter author last name: ");
    scanf("%s", search_last);

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    initgraph(&gd, &gm, "c:\\turboc3\\bgi");
    setcolor(WHITE);
    rectangle(10, 10, 630, 350);
    setfillstyle(SOLID_FILL, CYAN);
    floodfill(15, 15, WHITE);

    sprintf(line,"Books by %s %s:", search_first, search_last);
    outtextxy(20, 20, line);
    outtextxy(20,26,"____________________");


    while (fscanf(fp, "%s %s %s %s %d %d %d %d",
		  lib.name.book_name,
		  lib.name.author_firstname, lib.name.author_lastname,
		  lib.category,
		  &lib.date.day, &lib.date.month, &lib.date.year,
		  &lib.price) != EOF) {
	if(strcmp(lib.name.author_firstname, search_first)==0 &&
	   strcmp(lib.name.author_lastname, search_last)==0) {

	    sprintf(line,"Book name: %s",lib.name.book_name);
	    outtextxy(20,y,line);
	    y+=20;

	    sprintf(line,"Category: %s",lib.category);
	    outtextxy(20,y,line);
	    y+=20;

	    sprintf(line,"Issued date: %02d-%02d-%04d",
			 lib.date.day, lib.date.month, lib.date.year);
	    outtextxy(20,y,line);
	    y+=20;

	    sprintf(line,"Price: Rs.%d",lib.price);
	    outtextxy(20, y, line);
	    y += 20;
	    found = 1;
	}
    }

    if(!found) {
	outtextxy(20, y, "No books found!");
    }

    getch();
    closegraph();
    fclose(fp);
}




int main() {
    int choice;
    FILE *fp;


//    // Create header in file if not exists
//    fp = fopen("books.txt", "w");
//    fprintf(fp, "Book name    Author name  Category  Issued date(DD MM YYYY)  Price\n");
//    fprintf(fp, "------------------------------------------------------------------\n");
//    fclose(fp);

    do {
	clrscr();
	printf("\n===== Library Record Keeping System =====");
	printf("\n1. Add Book");
	printf("\n2. Display All Books");
	printf("\n3. Show Books Issued After 01-01-2026");
	printf("\n4. Count Books Per Category");
	printf("\n5. Find Most & Least Expensive Book");
	printf("\n6. Display Books by Specific Author");
	printf("\n7. Exit");
	printf("\nEnter your choice: ");
	scanf("%d", &choice);

	switch(choice) {
	    case 1: addbooks(); break;
	    case 2: display_books(); break;
	    case 3: books_after_date(); break;
	    case 4: count_books_per_category(); break;
	    case 5: most_and_least_expensive(); break;
	    case 6: books_by_author(); break;
	    case 7: printf("\nExiting program..."); break;
	    default: printf("\nInvalid choice! Try again.");
	}
	getch();
    } while(choice != 7);

    return 0;
}

