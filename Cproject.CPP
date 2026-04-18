#include <stdio.h>
#include <conio.h>
#include <string.h>

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
    fflush(stdin);  // to clear input buffer
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
    char line[200];
    clrscr();
    if (fp == NULL) {
	printf("Error opening file!");
	return;
    }

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    printf("\nAll Books:\n");
    while (fscanf(fp, "%s %s %s %s %d %d %d %d",
		  lib.name.book_name,
		  lib.name.author_firstname, lib.name.author_lastname,
		  lib.category,
		  &lib.date.day, &lib.date.month, &lib.date.year,
		  &lib.price) != EOF) {
	printf("\nBook Name   : %s", lib.name.book_name);
	printf("\nAuthor Name : %s %s", lib.name.author_firstname, lib.name.author_lastname);
	printf("\nCategory    : %s", lib.category);
	printf("\nIssued Date : %02d-%02d-%04d", lib.date.day, lib.date.month, lib.date.year);
	printf("\nPrice       : %d", lib.price);
	printf("\n----------------------------\n");
    }
    fclose(fp);
}

void books_after_date() {
    struct book lib;
    FILE *fp = fopen("books.txt", "r");
    char line[200];
    clrscr();
    if (fp == NULL) {
	printf("Error opening file!");
	return;
    }

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    printf("\nBooks issued after 01-01-2026:\n");
    while (fscanf(fp, "%s %s %s %s %d %d %d %d",
		  lib.name.book_name,
		  lib.name.author_firstname, lib.name.author_lastname,
		  lib.category,
		  &lib.date.day, &lib.date.month, &lib.date.year,
		  &lib.price) != EOF) {
	if (lib.date.year > 2026 ||
	   (lib.date.year == 2026 && lib.date.month > 1) ||
	   (lib.date.year == 2026 && lib.date.month == 1 && lib.date.day > 1)) {
	    printf("\nBook Name : %s", lib.name.book_name);
	    printf("  Author Name : %s %s", lib.name.author_firstname, lib.name.author_lastname);
	    printf("\n Category : %s", lib.category);
	    printf("  Issued Date : %02d-%02d-%04d", lib.date.day, lib.date.month, lib.date.year);
	    printf("  Price : %d", lib.price);

	}
    }
    fclose(fp);
}

void count_books_per_category() {
    struct book lib;
    FILE *fp = fopen("books.txt", "r");
    char line[200];
    int cs=0,it=0,management=0,network=0,database=0;
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
	if(strcmp(lib.category,"cs")==0) cs++;
	else if(strcmp(lib.category,"it")==0) it++;
	else if(strcmp(lib.category,"management")==0) management++;
	else if(strcmp(lib.category,"network")==0) network++;
	else if(strcmp(lib.category,"database")==0) database++;
    }

    printf("\nBooks per category:");
    printf("\nCS         : %d", cs);
    printf("\nIT         : %d", it);
    printf("\nManagement : %d", management);
    printf("\nNetwork    : %d", network);
    printf("\nDatabase   : %d\n", database);

    fclose(fp);
}

void most_and_least_expensive() {
    struct book lib, max_book, min_book;
    FILE *fp = fopen("books.txt", "r");
    char line[200];
    int max_price=-1, min_price=999999;
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

    printf("\nMost Expensive Book:");
    printf("\nBook Name   : %s", max_book.name.book_name);
    printf("\nAuthor Name : %s %s", max_book.name.author_firstname, max_book.name.author_lastname);
    printf("\nCategory    : %s", max_book.category);
    printf("\nIssued Date : %02d-%02d-%04d", max_book.date.day, max_book.date.month, max_book.date.year);
    printf("\nPrice       : %d\n", max_book.price);

    printf("\nLeast Expensive Book:");
    printf("\nBook Name   : %s", min_book.name.book_name);
    printf("\nAuthor Name : %s %s", min_book.name.author_firstname, min_book.name.author_lastname);
    printf("\nCategory    : %s", min_book.category);
    printf("\nIssued Date : %02d-%02d-%04d", min_book.date.day, min_book.date.month, min_book.date.year);
    printf("\nPrice       : %d\n", min_book.price);

    fclose(fp);
}

void books_by_author() {
    struct book lib;
    FILE *fp = fopen("books.txt", "r");
    char line[200];
    char search_first[20], search_last[20];

    if (fp == NULL) {
	printf("Error opening file!");
	return;
    }
     clrscr();
    printf("Enter author first name: ");
    scanf("%s", search_first);
    printf("Enter author last name: ");
    scanf("%s", search_last);

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    printf("\nBooks by %s %s:\n", search_first, search_last);
    while (fscanf(fp, "%s %s %s %s %d %d %d %d",
		  lib.name.book_name,
		  lib.name.author_firstname, lib.name.author_lastname,
		  lib.category,
		  &lib.date.day, &lib.date.month, &lib.date.year,
		  &lib.price) != EOF) {
	if(strcmp(lib.name.author_firstname, search_first)==0 &&
	   strcmp(lib.name.author_lastname, search_last)==0)
		   {
	      printf("\nBook Name   : %s", lib.name.book_name);
	      printf("\nAuthor Name : %s %s", lib.name.author_firstname, lib.name.author_lastname);
	      printf("\nCategory    : %s", lib.category);
	      printf("\nIssued Date : %02d-%02d-%04d", lib.date.day, lib.date.month, lib.date.year);
	      printf("\nPrice       : %d", lib.price);
	   }
    }

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

