// wap to find the most and least expensive books
#include <stdio.h>
#include <string.h>

struct Name {
    char book_name[50];
    char author_name[50];
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

int main() {
    FILE *fp = fopen("library.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open library.txt. Make sure the file exists!\n");
        return 1;
    }

    struct book current_book, min_book, max_book;
    char header_buffer[256];
    int count = 0;

    // Skip the first two header lines in your text file
    fgets(header_buffer, sizeof(header_buffer), fp);
    fgets(header_buffer, sizeof(header_buffer), fp);

    /* We use fscanf to pull data based on the format used in your write function.
       The loop continues as long as we successfully read 7 items (book, author, d, m, y, cat, price)
    */
    while (fscanf(fp, "%s %s %d-%d-%d %s %d", 
                  current_book.name.book_name, 
                  current_book.name.author_name, 
                  &current_book.date.day, &current_book.date.month, &current_book.date.year, 
                  current_book.category, 
                  &current_book.price) == 7) {
        
        // On the very first book, initialize min and max with its values
        if (count == 0) {
            min_book = current_book;
            max_book = current_book;
        } else {
            // Check for new expensive book
            if (current_book.price > max_book.price) {
                max_book = current_book;
            }
            // Check for new cheapest book
            if (current_book.price < min_book.price) {
                min_book = current_book;
            }
        }
        count++;
    }

    fclose(fp);

    if (count > 0) {
        printf("\n Library Price Report \n");
        
        printf("\nMost Expensive Book:\n");
        printf("Name: %s  Price: $%d  Author: %s\n", 
                max_book.name.book_name, max_book.price, max_book.name.author_name);

        printf("\nLeast Expensive Book:\n");
        printf("Name: %s  Price: $%d  Author: %s\n", 
                min_book.name.book_name, min_book.price, min_book.name.author_name);
    } else {
        printf("No valid book records found in the file.\n");
    }

    return 0;
}
