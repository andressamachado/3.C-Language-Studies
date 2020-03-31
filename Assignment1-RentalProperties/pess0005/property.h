
// Defines the Street Struct
typedef struct Street {
    char *street;
    int distance;
} StreetStruct;

// Defines the Property Struct to be used in the list node
typedef struct Property {
    StreetStruct *street;
    int streetNumber;
    int numberOfBedrooms;
    int pricePerBedroom;
} PropertyNode;

PropertyNode *createProperty();
void printFormatted(PropertyNode *property);
void printTableFormat(PropertyNode *property);
int totalDistance(PropertyNode *property);
