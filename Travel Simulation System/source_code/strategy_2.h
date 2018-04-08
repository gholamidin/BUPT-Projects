#ifndef QCCC
#define QCCC
#include "strategy_1.h"
void second_initial(graph G, int start, int &expected_hour, int fl[], struct temp D[][12], int P[], int &flag);
void initial(graph G, clientlist &p, int final[], struct temp D[][12], int P[]);
void shortest_time(graph G, int start, int arrive, int &expected_hour, int final[], struct temp D[][12], int P[], routelist &m);
void Shortest_Time(graph G,clientlist &p);
#endif
