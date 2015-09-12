/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

regex_t regexp; // Regular Expression variable
regmatch_t matches[NUM_TRACKS];    // Array of matches
int status;                 // Check if regular expression compiles correctly

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char* search_for)
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{   
    status = regcomp(&regexp, pattern, REG_EXTENDED); // compile the pattern with the regular expression and see if it's valid
    printf("status: %d\n", status);

    for (int i = 0; i < NUM_TRACKS; i++) {
        // match every single track with the regex
        status = regexec(&regexp, tracks[i], NUM_TRACKS, matches, 0);
        if (status == 0) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
    
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
    *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];
    char option[2];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    printf("\n");
    rstrip(search_for);

    printf("type 'a' for string search and 'b' for regex search: ");

    
    fgets(option, 2, stdin);
    printf("\n");

    if (*option == 'a') {
        find_track(search_for);
    }
    else if (*option == 'b') {
        find_track_regex(search_for);
    }



    
    regfree(&regexp); // free up memory held within the regex memory
    return 0;
}
