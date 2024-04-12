// Hugo Thorstensen Apr. 12

#include <stdio.h>
#include <stdlib.h> 

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
	struct RecordType* next;
	
};

// Fill out this structure
struct HashType
{
	struct RecordType* head;
};


// Compute the hash function
int hash(int x, int hashSz)
{
	return x % hashSz;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen("input.txt", "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

void insertRecord(struct HashType* hashArray, struct RecordType* record, int hashSz){
	int index = hash(record->id, hashSz);
	struct RecordType* current = hashArray[index].head;
	
	if (current == NULL){
		hashArray[index].head = record;
	} else {
		record->next = hashArray[index].head;
		hashArray[index].head = record;
	}
}

void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	struct RecordType* temp;
	for (i=0;i<hashSz;++i)
	{
		temp = pHashArray[i].head;
		if (temp != NULL){
			printf("index %d -> ", i);
			while (temp != NULL) {
				printf("id: %d, name: %c, order: %d -> ", temp->id, temp->name, temp->order);
				temp = temp->next;
			}
			printf("NULL\n");
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
	struct HashType* hashArray = (struct HashType*) malloc(sizeof(struct HashType) * recordSz);
	for (int i = 0; i < recordSz; i++){
		insertRecord(hashArray, &pRecords[i], recordSz);
	}
	displayRecordsInHash(hashArray, recordSz);

	free(pRecords);
	free(hashArray);
	return 0;
}