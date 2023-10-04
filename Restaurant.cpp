#include "main.h"

class imp_res : public Restaurant
{
	public:	
		customer* head;
		customer* curr;
		int size;

		customer *qhead;
		customer *qcurr;
		int qsize;

		imp_res() {
			head = nullptr;
			size = 0;
			qsize = 0;
		};

		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer* cus;
			//check name
			bool check = true;
			//size = 0 skip
			if (size == 1){
				if (curr->name == name){
					check = false;
				}
			}
			if (size > 1){
				customer* temp = curr;
				if (temp->name == name){
					check = false;
				}
				temp = temp->next;
				while (temp != curr){
					if (temp->name == name){
						check = false;
						break;
					}
					temp = temp->next;
				}
			}

			if (energy != 0 && check && size < MAXSIZE){
				if (size == 0) {
					cus = new customer (name, energy, nullptr, nullptr);
					head = cus;
					curr = cus;
					}
				else if (!(size >= MAXSIZE/2)) {
					if (size == 1){
						cus = new customer (name, energy, curr, curr);
						curr->next = cus;
						curr->prev = cus;
					} else {
						if (energy >= curr->energy){
							cus = new customer (name, energy, curr, curr->next);
							curr->next->prev = cus;
							curr->next = cus;
						} else {
							cus = new customer (name, energy, curr->prev, curr);
							curr->prev->next = cus;
							curr->prev = cus;
						}
					}
				} else {
					int max = abs(energy - curr->energy);
					customer* maxcus = curr;
					customer* temp = curr->next;
					while (temp!=curr){
						if (abs(energy - temp->energy) > max){
							max = abs(energy - temp->energy);
							maxcus = temp;
						}
						temp = temp->next;
					}
					if (energy - maxcus->energy < 0){
						cus = new customer (name, energy, curr->prev, curr);
						curr->prev->next = cus;
						curr->prev = cus;
					} else {
						cus = new customer (name, energy, curr, curr->next);
						curr->next->prev = cus;
						curr->next = cus;
					}
				}
				curr = cus;
				size++;
			} else if (check && size >= MAXSIZE){
				if (qsize<MAXSIZE)

				qsize++;	
			} 

		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;

		}
		void PURPLE()
		{
			cout << "purple"<< endl;

		}
		void REVERSAL()
		{
			cout << "reversal" << endl;

		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;

		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;

		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;

		}
};