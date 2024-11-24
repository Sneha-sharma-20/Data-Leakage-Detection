#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define DATA_THRESHOLD 100  // Threshold in MB for suspicious data size
#define FREQUENCY_THRESHOLD 5  // Threshold for frequency of data transfer

typedef struct {
    char ipAddress[16];
    int dataSize;
} NetworkTraffic;

void enterData(NetworkTraffic traffic[], int *numEntries) {
    printf("Enter the number of network traffic entries (max %d): ", MAX_ENTRIES);
    scanf("%d", numEntries);

    if (*numEntries > MAX_ENTRIES) {
        printf("Number of entries exceeds limit. Exiting program.\n");
        exit(1);
    }

    for (int i = 0; i < *numEntries; i++) {
        printf("\nEnter IP address for entry %d: ", i + 1);
        scanf("%s", traffic[i].ipAddress);
        printf("Enter data size (in MB) for IP %s: ", traffic[i].ipAddress);
        scanf("%d", &traffic[i].dataSize);
    }
}

void analyzeData(NetworkTraffic traffic[], int numEntries) {
    int suspiciousCount = 0;

    printf("\nAnalyzing data for suspicious patterns...\n");

    // Calculate average data size
    int totalData = 0;
    for (int i = 0; i < numEntries; i++) {
        totalData += traffic[i].dataSize;
    }
    int avgDataSize = totalData / numEntries;

    for (int i = 0; i < numEntries; i++) {
        int count = 0;
        // Check for large data transfers
        if (traffic[i].dataSize > DATA_THRESHOLD) {
            printf("Suspicious: Large data transfer from IP %s, Data Size: %dMB\n",
                   traffic[i].ipAddress, traffic[i].dataSize);
            suspiciousCount++;
        }

        // Check frequency of transfers from the same IP
        for (int j = 0; j < numEntries; j++) {
            if (strcmp(traffic[i].ipAddress, traffic[j].ipAddress) == 0) {
                count++;
            }
        }

        if (count > FREQUENCY_THRESHOLD) {
            printf("Suspicious: High frequency of transfers from IP %s\n", traffic[i].ipAddress);
            suspiciousCount++;
        }

        // Check for data size anomalies based on average size
        if (traffic[i].dataSize > avgDataSize * 1.5) {  // If data is 50% above the average
            printf("Suspicious: Data size anomaly from IP %s, Data Size: %dMB\n",
                   traffic[i].ipAddress, traffic[i].dataSize);
            suspiciousCount++;
        }
    }

    if (suspiciousCount == 0) {
        printf("No suspicious activity detected.\n");
    }
}

int main() {
    NetworkTraffic traffic[MAX_ENTRIES];
    int numEntries;

    enterData(traffic, &numEntries);
    analyzeData(traffic, numEntries);

    return 0;
}

