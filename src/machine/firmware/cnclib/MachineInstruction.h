#if !defined(MI)
#define MI

typedef struct Vector_ Vector;

void mi_parse_coordinate(char* instruction, Vector* current, Vector* coordinate);
void mi_parse_wait_instruction(char* instruction, int* milliseconds);

#endif // MI
