#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_REVIEW_LEN 256
#define LEXICON_SIZE 10

// Define a structure for word sentiment scores
typedef struct {
    char word[30];
    int score;
} SentimentWord;

// Simple pre-loaded lexicon
SentimentWord lexicon[LEXICON_SIZE] = {
    {"great", 2}, {"amazing", 3}, {"good", 1}, {"love", 2}, {"excellent", 3},
    {"bad", -2}, {"terrible", -3}, {"poor", -1}, {"hate", -2}, {"awful", -3}
};

// Function to convert a string to lowercase
void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Function to analyze sentiment of a review
int analyzeSentiment(char *review) {
    int totalScore = 0;
    char buffer[MAX_REVIEW_LEN];
    strcpy(buffer, review);
    toLowerStr(buffer);

    // Tokenize review by spaces
    char *token = strtok(buffer, " ,.-!?\n");
    while (token != NULL) {
        // Check against lexicon
        for (int i = 0; i < LEXICON_SIZE; i++) {
            if (strcmp(token, lexicon[i].word) == 0) {
                totalScore += lexicon[i].score;
                break;
            }
        }
        token = strtok(NULL, " ,.-!?\n");
    }

    return totalScore;
}

// Function to save review to a file
void saveReview(char *review, int score) {
    FILE *file = fopen("reviews.txt", "a");
    if (file == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }
    
    char *sentimentLabel = (score > 0) ? "Positive" : (score < 0) ? "Negative" : "Neutral";
    fprintf(file, "Review: %s | Score: %d | Sentiment: %s\n", review, score, sentimentLabel);
    fclose(file);
    printf("Review saved successfully!\n");
}

int main() {
    char review[MAX_REVIEW_LEN];

    printf("=== Customer Feedback & Sentiment App ===\n");
    printf("Enter your review: ");
    
    if (fgets(review, sizeof(review), stdin) != NULL) {
        // Remove trailing newline if present
        review[strcspn(review, "\n")] = 0;

        int score = analyzeSentiment(review);
        
        printf("\n--- Analysis Result ---\n");
        printf("Total Sentiment Score: %d\n", score);
        if (score > 0) {
            printf("Overall Sentiment: Positive \n");
        } else if (score < 0) {
            printf("Overall Sentiment: Negative \n");
        } else {
            printf("Overall Sentiment: Neutral \n");
        }

        // Save to file database
        saveReview(review, score);
    }

    return 0;
}