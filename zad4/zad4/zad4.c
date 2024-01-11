#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH 1024

struct polinom;
typedef struct polinom* position;
typedef struct polinom
{
	int coefficient;
	int exponent;
	position next;
} _polinom;

void ReadFile(position head, char* buffer);
void Insert(position head, int coefficient, int exponent);
void AddPolynomes(position resultHead, position h1, position h2);
void Multiplypolyonmes(position resultHead, position h1, position h2);
void Print(position head);

int main() {


	return 0;
}

void ucitajIzDatoteke(poli head, char* buffer)
{
	int k, e, brojBitova;
	char* trenutni = buffer;
	poli p = head, q = NULL, prev = head;
	while (strlen(trenutni) > 1)
	{
		prev = head;
		p = prev->next;
		sscanf(trenutni, "%d %d%n", &k, &e, &brojBitova);
		while (p != NULL)
		{
			if (e > p->eksp)
			{
				q = (poli)malloc(sizeof(struct polinom));
				q->koef = k;
				q->eksp = e;
				q->next = prev->next;
				prev->next = q;
				trenutni += brojBitova;
				p = head;
				break;
			}
			else if (e == p->eksp)
			{
				p->koef += k;
				if (p->koef == 0)
				{
					prev->next = p->next;
					free(p);
				}
				trenutni += brojBitova;
				p = head;
				break;
			}
			prev = prev->next;
			p = p->next;
		}
		if (p == NULL)
		{
			q = (poli)malloc(sizeof(struct polinom));
			q->koef = k;
			q->eksp = e;
			q->next = prev->next;
			prev->next = q;
			trenutni += brojBitova;
		}

	}
}
