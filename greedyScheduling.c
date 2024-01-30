#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Selection sort based approach to sorting jobs

int main(int argc, char* argv[]) {

    // First peek at how many jobs and time-slots there are
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    char buf[256];

    // Read the number of jobs to be scheduled
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of jobs failed");
        exit(EXIT_FAILURE);
    }
    int jobcount = atoi(buf);

    // Next read the maximum number of timeslots
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of timeslots failed");
        exit(EXIT_FAILURE);
    }
    int timeslots = atoi(buf);

    // We've read the number of timeslots so close the file and start over
    fclose(fp);
    int previousend = 0;

    for (unsigned int slot=0; slot < timeslots; slot++) {

        FILE* fp = fopen(argv[1], "r");
        if (!fp) {
            perror("fopen failed");
            exit(EXIT_FAILURE);
        }

        char buf[256];

        // First read the number of jobs to be scheduled
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of jobs failed");
            exit(EXIT_FAILURE);
        }

        // Next read the maximum number of timeslots
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of timeslots failed");
            exit(EXIT_FAILURE);
        }

        // Now read the rest of the file
        for (int line=0; line < jobcount; line++) {

            if (!fgets(buf, 256, fp)) {
                perror("reading a line for a job failed");
                exit(EXIT_FAILURE);
            }

            char job;
            unsigned int end;
            unsigned int begin;
            if (!sscanf(buf, "%c %d %d", &job, &begin, &end)) {
                perror("parsing a line for a job failed");
                exit(EXIT_FAILURE);
            }

            if (end == slot) {
              if (begin > previousend && end > previousend){
                printf("%c\n", job);
                previousend = end;
                }
            }

        }
        fclose(fp);

    }

    exit(EXIT_SUCCESS);
}
