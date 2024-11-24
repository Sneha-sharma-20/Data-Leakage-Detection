#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 100

typedef struct {
    char *data;
    char *alteration;
} DataEntry;

typedef struct {
    char *agentId;
    char *agentName;
    DataEntry allocatedData[MAX_DATA];
    int dataCount;
} Agent;

typedef struct AgentNode {
    Agent *agent;
    struct AgentNode *next;
} AgentNode;

typedef struct {
    AgentNode *storage;
} DataStorage;

typedef struct {
    DataStorage *dataStorage;
} LeakageDetector;

// Function to create a new agent
Agent* createAgent(const char *agentId, const char *agentName) {
    Agent *agent = (Agent *)malloc(sizeof(Agent));
    agent->agentId = strdup(agentId);
    agent->agentName = strdup(agentName);
    agent->dataCount = 0;
    return agent;
}

// Function to allocate data and its alteration to the agent
void allocateData(Agent *agent, const char *data, const char *alteration) {
    if (agent->dataCount < MAX_DATA) {
        agent->allocatedData[agent->dataCount].data = strdup(data);
        agent->allocatedData[agent->dataCount].alteration = strdup(alteration);
        agent->dataCount++;
    }
}

// Function to create a data storage
DataStorage* createDataStorage() {
    DataStorage *ds = (DataStorage *)malloc(sizeof(DataStorage));
    ds->storage = NULL;
    return ds;
}

// Function to store agent data in the data storage
void storeData(DataStorage *ds, Agent *agent) {
    AgentNode *newNode = (AgentNode *)malloc(sizeof(AgentNode));
    newNode->agent = agent;
    newNode->next = ds->storage;
    ds->storage = newNode;
}

// Function to create a leakage detector
LeakageDetector* createLeakageDetector(DataStorage* dataStorage) {
    LeakageDetector* detector = (LeakageDetector*)malloc(sizeof(LeakageDetector));
    detector->dataStorage = dataStorage;
    return detector;
}

// Function to detect leakage by comparing leaked data
void detectLeakage(LeakageDetector* detector, const char* leakedData, const char* alteration) {
    int leakDetected = 0;
    AgentNode *current;

    // Iterate through all stored agents and their data entries
    for (current = detector->dataStorage->storage; current != NULL; current = current->next) {
        Agent *agent = current->agent;
        int i;
        for (i = 0; i < agent->dataCount; i++) {
            if (strcmp(leakedData, agent->allocatedData[i].data) == 0 && 
                strcmp(alteration, agent->allocatedData[i].alteration) == 0) {
                printf("Leakage detected from Agent: %s (Agent Name: %s)\n", 
                       agent->agentId, agent->agentName);
                leakDetected = 1;
                break;
            }
        }
        if (leakDetected) break;
    }

    if (!leakDetected) {
        printf("No leakage detected for data: %s with alteration: %s\n", 
               leakedData, alteration);
    }
}

// Function to free the memory allocated for an agent
void freeAgent(Agent *agent) {
    int i;
    free(agent->agentId);
    free(agent->agentName);
    for (i = 0; i < agent->dataCount; i++) {
        free(agent->allocatedData[i].data);
        free(agent->allocatedData[i].alteration);
    }
    free(agent);
}

// Function to free the memory allocated for the data storage
void freeDataStorage(DataStorage *ds) {
    AgentNode *current = ds->storage;
    while (current != NULL) {
        AgentNode *temp = current;
        current = current->next;
        freeAgent(temp->agent);
        free(temp);
    }
    free(ds);
}

int main() {
    DataStorage *dataStorage = createDataStorage();
    LeakageDetector *leakageDetector = createLeakageDetector(dataStorage);
    int numAgents;
    int i, j;
    
    printf("Enter number of agents: ");
    scanf("%d", &numAgents);
    getchar(); // To consume the newline character left by scanf

    // Input agent details and allocate data
    for (i = 0; i < numAgents; i++) {
        char agentId[50], agentName[50];
        int numDataEntries;
        
        printf("\nEnter details for Agent %d:\n", i + 1);
        printf("Agent ID: ");
        fgets(agentId, sizeof(agentId), stdin);
        agentId[strcspn(agentId, "\n")] = 0;

        printf("Agent Name: ");
        fgets(agentName, sizeof(agentName), stdin);
        agentName[strcspn(agentName, "\n")] = 0;

        Agent *agent = createAgent(agentId, agentName);

        printf("Enter number of data entries for this agent: ");
        scanf("%d", &numDataEntries);
        getchar(); // To consume the newline character left by scanf

        for (j = 0; j < numDataEntries; j++) {
            char data[100], alteration[100];
            printf("Enter data entry %d:\n", j + 1);
            printf("Data: ");
            fgets(data, sizeof(data), stdin);
            data[strcspn(data, "\n")] = 0;

            printf("Alteration: ");
            fgets(alteration, sizeof(alteration), stdin);
            alteration[strcspn(alteration, "\n")] = 0;

            allocateData(agent, data, alteration);
        }

        // Store agent in data storage
        storeData(dataStorage, agent);
    }

    // Simulate leakage detection
    char leakedData[100], leakedAlteration[100];
    printf("\nEnter data to check for leakage:\n");
    printf("Leaked Data: ");
    fgets(leakedData, sizeof(leakedData), stdin);
    leakedData[strcspn(leakedData, "\n")] = 0;

    printf("Leaked Alteration: ");
    fgets(leakedAlteration, sizeof(leakedAlteration), stdin);
    leakedAlteration[strcspn(leakedAlteration, "\n")] = 0;

    // Detect leakage
    detectLeakage(leakageDetector, leakedData, leakedAlteration);

    // Free allocated memory
    freeDataStorage(dataStorage);
    free(leakageDetector);

    return 0;
} 
