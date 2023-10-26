#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;
//main.h
int MAXSIZE;
class Restaurant {

	public:
		Restaurant() {};
		~Restaurant() {};
		virtual void RED(string name, int energy) = 0;
		virtual void BLUE(int num) = 0;
		virtual void PURPLE() = 0;
		virtual void REVERSAL() = 0;
		virtual void UNLIMITED_VOID() = 0;
		virtual void DOMAIN_EXPANSION() = 0;	
		virtual void LIGHT(int num) = 0;
		public:
			class customer {
			public:	
				string name;
				int energy;
				customer* prev;
				customer* next;
			public:
				customer(){}
				customer(string na, int e, customer* p, customer *ne): name(na), energy(e), prev(p), next(ne){}
				~customer(){};
				void print() {
					cout << name << "-" << energy << endl;
				}
			};
};
//Restaurant.cpp
class imp_res : public Restaurant
{	
	public:
		class DCLList {
		private:
			customer* head;
			customer* curr;
			int size;
		public:
		DCLList() {
			head = nullptr;
			curr = nullptr;
			size = 0;
		}
		~DCLList(){
			// 
			for (int i=0; i<size; i++){
				customer* temp = curr;
				curr = curr->next;
				delete temp;
			}
		}
		void setcurr(customer* c){
			curr = c;
		}
		void add(string name, int energy){
			if (size == 0) {
				head = new customer(name, energy, nullptr, nullptr);
				head->next = head->prev = head;
				curr = head;
				}
			else if (size == 1){
				curr->next = new customer(name, energy, curr, curr);
				curr->prev = curr->next;
				curr = curr->next;
			} else {
				customer* temp = new customer(name, energy, curr, curr->next);
				curr->next->prev = temp;
				curr->next = temp;
				curr = temp;
			}
			size++;
		}
		void addbefore(string name, int energy){
			if (size == 0) {
				head = new customer(name, energy, nullptr, nullptr);
				curr = head;
				}
			else if (size == 1){
				head->next = new customer(name, energy, head, head);
				head->prev = head->next;
				curr = head->next;
			} else {
				customer* temp = new customer(name, energy, curr->prev, curr);
				curr->prev->next = temp;
				curr->prev = temp;
				curr = temp;
			}
			size++;
		}
		void remove(){ // xoa ngay vi tri con tro curr
			if (size == 0){
				return;
			}
			else if (size == 1){
				customer* temp = curr;
				delete temp;
				curr = nullptr;
				head = nullptr;
				size--;
				return;
			}
			else if (size == 2){
				customer* temp = curr;
				curr = curr->next;
				curr->next = curr;
				curr->prev = curr;
				size--;
				delete temp;
				return;
			}
			else {
				customer* temp = curr;
				int energy = curr->energy;
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				if (energy > 0) {
					curr = curr->next;
				} else {
					curr = curr->prev;
				}
				size--;
				delete temp;
				return;
			}
		}
		void remove(string name){
			customer* temp = curr;
			int energy = curr->energy;
			for (int i=0; i < size; i++){
				if (temp->name == name){
					if (size == 0){
						return;
					}
					else if (size == 1){
						curr = nullptr;
						head = nullptr;
						size--;
						delete temp;
						return;
					}
					else if (size == 2){
						customer* tempdelete = temp;
						temp->next->prev = temp->prev;
						temp->prev->next = temp->next;
						curr = temp->next;
						size--;
						delete tempdelete;
						return;
					} else {
						temp->next->prev = temp->prev;
						temp->prev->next = temp->next;
						if (energy > 0) {
							curr = temp->next;
						} else {
							curr = temp->prev;
						}
						size--;
						delete temp;
						return;
					}
				}
				temp = temp->next;
			}
			return;
		}
		customer* get(){
			return curr;
		}
		int getSize(){
			return size;
		}
		bool isEmpty(){
			return size == 0;
		}
		void next(){
			curr = curr->next;
		}
		void prev(){
			curr = curr->prev;
		}
		bool check(string name){
			customer* temp = curr;
			for (int i = 0; i < size; i++){
				if (temp->name == name) return true;
				temp = temp->next;
        }
        return false;
    	}
	};
		class LQueue {
		private:
			customer* head;
			customer* rear; 
			customer* curr;
			int size;
		public:
		LQueue() {
			head = nullptr;
			rear = nullptr;
			size = 0;
		}
		LQueue(LQueue* q){
			// deep copy
			head = nullptr;
			rear = nullptr;
			size = 0;
			customer* temp = q->head;
			for (int i=0; i<q->size; i++){
				add(temp->name, temp->energy);
				temp = temp->next;
			}
		}
		~LQueue(){
			while (head != nullptr) {
            customer* temp = head;
            head = head->next;
            delete temp;
        	}
		}
		void add(string name, int energy){
			if (size==0){
				head = rear = new customer(name, energy, nullptr, nullptr);
			} else {
				rear->next = new customer(name, energy, nullptr, nullptr);
				rear = rear->next;
			}
			size++;
		}
		void remove(){
			if (size == 0) return;
			else if (size == 1){
				customer* temp = head;
				head = rear = nullptr;
				size--;
				delete temp;
			} else {
				customer* temp = head;
				head = head->next;
				size--;
				delete temp;
			}
		}
		// customer* removeAt(int i){
		// 	if (i == 0) return remove();
		// 	else if (i == size - 1){
		// 		customer* temp = rear;
		// 		curr = head;
		// 		for (int i=0; i<size-2; i++){
		// 			curr = curr->next;
		// 		}
		// 		rear = curr; // detach rear luon
		// 		size--;
		// 		return temp;
		// 	} else {
		// 		curr = head;
		// 		for (int j=0; j<i-1; j++){ //ngựa hí hí 🐴
		// 			curr = curr->next;
		// 		}
		// 		customer* temp = curr->next;
		// 		curr->next = curr->next->next;
		// 		size--;
		// 		return temp;
		// 	}
		// }
		void remove(string name){
			if (size == 0) return;
			customer* temp = head;
			for (int i=0; i< size; i++){
				if (temp->name == name) return removeAt(i);
				temp = temp->next;
			}
			return;
		}
		customer* get(){
			return head;
		}
		// void clear(){
			// chưa cần
		// }
		int getSize(){
			return size;
		}
		bool check(string name){
			customer* temp = head;
			for (int i = 0; i < size; i++){
				if (temp->name == name) return true;
				temp = temp->next;
			}
			return false;
		}
		bool isEmpty(){
			return size == 0;
		}
		void moveTo(int n){
			if (n >= size) n = size - 1;
			curr = head;
			for (int i = 0; i < n; i++){
				curr = curr->next;
			}
		}
		customer* getcurr(){
			return curr;
		}
		customer* getat(int n){
			moveTo(n);
			return curr;
		}
		int getPos(){
			customer* temp = head;
			int i = 0;
			while (temp != curr){
				temp = temp->next;
				i++;
			}
			return i;
		}
		void next(){
			curr = curr->next;
		}
		void prev(){
			// if < 0 return
			moveTo(getPos()-1);
		}
		void swap(int a, int b){
			moveTo(a);
			customer* temp = curr;
			moveTo(b);
			customer* temp2 = curr;
			std::swap(temp->energy, temp2->energy);
			std::swap(temp->name, temp2->name);
		}
		void removeAt(int n){
			moveTo(n);
			customer* temp;
			if (n == 0){
				temp = head;
				head = head->next;
				size--;
				delete temp;
			} else if (n == size - 1){
				temp = rear;
				moveTo(n-1);
				rear = curr;
				size--;
				delete temp;
			} else {
				temp = curr;
				moveTo(n-1);
				curr->next = curr->next->next;
				size--;
				delete temp;
			}
		}
	};

	public:
		DCLList *table;
		LQueue *queue;
		LQueue *history;

		imp_res() {
			table = new DCLList();
			queue = new LQueue();
			history = new LQueue();
		};
		~imp_res(){
			delete table;
			delete queue;
			delete history;
		}
		void RED(string name, int energy)
		{	
			// cout << name << " " << energy << endl;
			bool check = table->check(name) || queue->check(name); // true là bị trùng
			if (energy != 0 && table->getSize() < MAXSIZE && !check){
				if (table->getSize()<=1){
					table->add(name, energy);
				} else if (!(table->getSize() >= MAXSIZE/2)) {
					if (table->get()->energy <= energy){ //energy khach >= energy ban
						table->add(name, energy);
					} else {
						table->addbefore(name, energy);
					}
				} else if (table->getSize() >= MAXSIZE/2){
					int max = abs(energy - table->get()->energy);
					customer* maxcus = table->get();
					customer* x = table->get();
					x = x->next;
					while (table->get() != x){
						if (max < abs(energy - x->energy)){
							max = abs(energy - x->energy);
							maxcus = x;
						}
						x = x->next;
					}
					int noabsmax = energy - maxcus->energy;

					table->setcurr(maxcus);
					if (noabsmax < 0){
						table->addbefore(name, energy);
					} else {
						table->add(name, energy);
					}
				}
				history->add(name, energy);
			} else if (energy != 0 && queue->getSize()<MAXSIZE && !check) {
				queue->add(name, energy);
			}
		}
		void BLUE(int num)
		{ //history
			// cout << "blue "<< num << endl;
			if (num >= table->getSize()){
				num = table->getSize();
			}
			//kick khach cu nhat //ko can kiem tra vi = getsize
			for (int i = 0; i < num; i++){
				int removedenergy = history->get()->energy;
				string removedname = history->get()->name;
				history->remove();

				customer* temp = table->get();
				for (int j=0; j<table->getSize();j++){
					if (temp->name == removedname){
						string tempname = temp->name;
						temp = temp->next;
						table->remove(tempname);
						break;
					}
						temp = temp->next;
				}
			}
			//pop queue
			//chay red
			while (!(queue->isEmpty())&&table->getSize()<MAXSIZE){
				string removedname = queue->get()->name;
				int removedenergy = queue->get()->energy;
				queue->remove();
				RED(removedname, removedenergy);
			}
		}
		void inssort2(LQueue *head, int n, int incr, int& swapcount){
			for (int i=incr; i<n; i+=incr){
				for (int j=i; (j>=incr) && (abs(head->getat(j)->energy) > abs(head->getat(j-incr)->energy)); j-=incr){
					head->swap(j, j-incr);
					swapcount++;
				}
			}
		}
		void shellsort(LQueue *head, int n, int& swapcount){
			for (int i=n/2; i>2; i/=2){
				for (int j=0; j<i; j++){
					inssort2(head, n-j, i, swapcount);
				}
			}
			inssort2(head, n, 1, swapcount);
		}
		void PURPLE()
		{
			// cout << "purple"<< endl;
			//xep queue; //nếu có queue

			// abs() từ lớn đến bé
			if (!queue->isEmpty()){
			int maxenergy = abs(queue->get()->energy);
			int maxindex = 0;
			int N = 0;
			for (int i=1;i<queue->getSize();i++){
				if (abs(queue->getat(i)->energy) >= maxenergy){
					maxenergy = queue->getat(i)->energy;
					maxindex = i;
				}
			}
			// sort from 0 to i
			LQueue *begin = new LQueue(queue);
			shellsort(queue, maxindex+1,N);
			// fix the stable of the queue after sorting
			for (int i=0; i<queue->getSize()-1; i++){
				//move queue den cho do
				queue->moveTo(i);
				// neu 2 thang bang nhau -> check xem co dung thu tu ko
				if (queue->getcurr()->energy == queue->getcurr()->next->energy){
					// lay thu tu cua curr va curr next
					string namecurr = queue->getcurr()->name;
					string namecurrnext = queue->getcurr()->next->name; 
					// lay thu tu cua curr va curr nexg trong begin
					int currindex = 0;
					int currnextindex = 0;
					for (int j=0; j<begin->getSize(); j++){
						begin->moveTo(j);
						if (begin->getcurr()->name == namecurr){
							currindex = j;
						}
						if (begin->getcurr()->name == namecurrnext){
							currnextindex = j;
						}
					}
					if (currindex > currnextindex){
						// neu sai thu tu -> swap
						queue->swap(i, i+1);
					}
				}
			}
			BLUE(N%MAXSIZE);
			}
		}
		void REVERSAL()
		{
			// cout << "reversal" << endl;
			//replace duong
			string temp = table->get()->name;
			LQueue* tempq = new LQueue();
			customer* tempcus = table->get();
			int len = table->getSize();
			// int qlen = 0;
			for (int i=0; i<len; i++){
				if (tempcus->energy > 0){
					tempq->add(tempcus->name, tempcus->energy);
					// qlen++;
				}
				if (i!=len-1) tempcus = tempcus->prev;
			}
			for (int i=0; i<len; i++){
				if (tempcus->energy > 0){
					tempcus->energy = tempq->get()->energy;
					tempcus->name = tempq->get()->name;
					tempq->remove();
				}
				tempcus = tempcus->next;
			}
			//replace âm
			delete tempq;
			tempq = new LQueue();
			tempcus = table->get();
			// qlen = 0;
			for (int i=0; i<len; i++){
				if (tempcus->energy < 0){
					tempq->add(tempcus->name, tempcus->energy);
					// qlen++;
				}
				if (i!=len-1) tempcus = tempcus->prev;
			}
			for (int i=0; i<len; i++){
				if (tempcus->energy < 0){
					tempcus->energy = tempq->get()->energy;
					tempcus->name = tempq->get()->name;
					tempq->remove();
				}
				tempcus = tempcus->next;
			}
			
			delete tempq;
			// set lai x
			tempcus = table->get();
			for (int i=0; i<len; i++){
				if (tempcus->name == temp){
					table->setcurr(tempcus);
				}
				tempcus = tempcus->prev;
			}
		}
		void UNLIMITED_VOID()
		{
			// cout << "unlimited_void" << endl;
			//bo truong hop < 4
			int len = table->getSize();
			if (len < 4) return;
			customer *left = table->get();
			customer *right = table->get()->next->next->next;
			//init
			int minoutersum;
			for (int i=0; i<len; i++){
				customer* templeft = table->get(); 
				int sum = 0;
				//dich chuyen
				for (int k=0; k<i;k++){
					templeft = templeft->next;
				}
				customer *temp = templeft;
				customer *tempright = templeft->next->next->next;
				//get tong 4 cai dau
				for (int j=0; j<4;j++){
					sum += temp->energy;
					temp = temp->next;
				}
				//nho nhat
				int minsum = sum;
				temp = tempright;
				//so sanh nhung cai sau
				for (int l=4; l<len;l++){
					temp = temp->next;
					sum += temp->energy;
					if (sum <= minsum){
						minsum = sum;
						//move to
						tempright = temp;
					}
				}

				if (i==0){
					minoutersum = minsum;
				} else if (minsum <= minoutersum){
					minoutersum = minsum;
					//move to
					left = templeft;
					right = tempright;
				}
			}
			// co l r
			// co dc day nho nhat
			// tim phan tu nho nhat
			customer* smallest = left;
			customer* temp = left;
			int count = 1; //hjhj
			while (temp!=right){
				count++;
				temp = temp->next;
			}
			temp = left;
			// temp = temp->next;
			for (int i=0; i<count; i++){
				if (smallest->energy > temp->energy){
					smallest = temp;
				}
				temp = temp->next;
			}
			// in ra tu nho nhat den cuoi theo chieu dong ho
			temp = smallest;
			count = 1;
			while (temp!=right){
				count++;
				temp = temp->next;
			}
			temp = smallest;

			customer* temp2 = left;
			int count2 = 0;
			while (temp2!=temp){
				count2++;
				temp2 = temp2->next;
			}
			temp2 = left;
			for (int i=0; i<count; i++){
				cout << temp->name << "-" << temp->energy << endl;
				temp = temp->next;
			}
			for (int i=0; i<count2; i++){
				cout << temp2->name << "-" << temp2->energy << endl;
				temp2 = temp2->next;
			}
		}
		void DOMAIN_EXPANSION()
		{
			// cout << "domain_expansion" << endl;
			int chewTwerkShoe = 0;
			int oanTLinh = 0;
			//get cho chu thuat su
			customer* tablecurr = table->get();
			queue->moveTo(0);
			customer* queuecurr = queue->get();
			for (int i=0; i<table->getSize();i++){
				if (tablecurr->energy > 0) chewTwerkShoe += tablecurr->energy;
				tablecurr = tablecurr->next;
			}
			for (int i=0; i<queue->getSize();i++){
				if (queuecurr->energy > 0) chewTwerkShoe += queuecurr->energy;
				queuecurr = queuecurr->next;
			}
			//get cho oan linh
			tablecurr = table->get();
			queue->moveTo(0);
			queuecurr = queue->get();
			for (int i=0; i<table->getSize();i++){
				if (tablecurr->energy < 0) oanTLinh += tablecurr->energy;
				tablecurr = tablecurr->next;
			}
			for (int i=0; i<queue->getSize();i++){
				if (queuecurr->energy < 0) oanTLinh += queuecurr->energy;
				queuecurr = queuecurr->next;
			}
			if (chewTwerkShoe==0||oanTLinh==0){
				return;
			}
			if (chewTwerkShoe>=abs(oanTLinh)){
				//kick oantlinh
				//kick queue // gần đây nhất (từ đuôi đến đầu)
				int queueSize = queue->getSize();
				for (int i=queueSize-1; i>=0;i--){
					queue->moveTo(i);
					if (queue->getcurr()->energy < 0){

						//customer* temp = queue->removeAt(i);
						int energy = queue->getat(i)->energy;
						string name = queue->getat(i)->name;
						queue->removeAt(i);
						cout << name << "-" << energy << endl;
					}
				}
				//kick history (table) 
				int historySize = history->getSize();

				for (int i=historySize-1; i>=0;i--){
					history->moveTo(i);
					if (history->getcurr()->energy < 0){
						// customer* temp = history->removeAt(i);
						int energy = history->getat(i)->energy;
						string name = history->getat(i)->name;
						history->removeAt(i);
						table->remove(name);
						cout << name << "-" << energy << endl;
					}
				}
			}else{
				//kick chewtwerkshoe
				//kick queue
				int queueSize = queue->getSize();
				for (int i=queueSize-1; i>=0;i--){
					queue->moveTo(i);
					if (queue->getcurr()->energy > 0){
						// customer* temp = queue->removeAt(i);
						int energy = queue->getat(i)->energy;
						string name = queue->getat(i)->name;
						queue->removeAt(i);
						cout << name << "-" << energy << endl;
					}
				}
				//kick history (table)
				int historySize = history->getSize();
				for (int i=historySize-1; i>=0;i--){
					history->moveTo(i);
					if (history->getcurr()->energy > 0){
						// customer* temp = history->removeAt(i);
						int energy = history->getat(i)->energy;
						string name = history->getat(i)->name;
						history->removeAt(i);
						table->remove(name);
						cout << name << "-" << energy << endl;
					}
				}
			}
			//chay red
			while (!(queue->isEmpty())&&table->getSize()<MAXSIZE){
				//customer* temp = queue->remove();
				customer* temp = queue->get();
				int energy = temp->energy;
				string name = temp->name;
				queue->remove();

				RED(name, energy);
			}
			/*“Luận về Yêu” hay là “Con chó và Thằng Osin”
				Chắc hẳn nhiều bạn trai, đặc biệt là các bạn hay đọc diễn đàn f17 VoZ khoảng năm 2010 đến 2013 không lạ lẫm gì với học thuyết Con chó và thằng Osin. Học thuyết này có nội dung ngắn gọn như sau: Bất kì cô gái xinh đẹp và khôn ngoan nào (chuẩn hotgirl hiện nay) đều có hai người bạn trai chính. Một là Con Chó — giàu có, đẹp trai, đi xế xịn — được các cô dùng để khoe và chứng tỏ giá trị của bản thân với thiên hạ. Hai là Thằng Osin — chăm chỉ, hiền lành, đa phần là học giỏi — luôn thờ phụng và sẵn sàng làm mọi việc các cô yêu cầu từ làm bài tập hộ đến đón thằng em trai. Tuy nhiên Thằng Osin sẽ không bao giờ được bước ra ánh sáng cuộc đời cùng với các cô, đơn giản vì Osin không bóng bẩy bằng Con Chó.

				Lẽ dĩ nhiên học thuyết này mang nặng mùi cay đắng đổ vỡ tình đầu của các cậu trai mới lớn, vì vậy không hề mang tính khách quan phổ quát. Nhưng mình muốn nói tới một khía cạnh khác, được chấp nhận rộng rãi hơn của học thuyết này.

				Đa phần chúng ta cho rằng cả Con Chó và Thằng Osin đều rất ngu dốt khi đầu tư mù quáng vào một mối quan hệ vô bổ như vậy. Thậm chí đôi lúc chúng ta còn thương cảm cho họ, đặc biệt là Thằng Osin. Chắc hẳn ngoài đời thực bạn đã gặp vài Thằng Osin như vậy. Đưa đi đón về như xe ôm riêng, chăm sóc hơn cả chăm bà đẻ, ngoan ngoãn vâng dạ như cháu nghe lời bà nội… để cuối cùng trở thành bạn thân (friendzone), anh trai (brotherzone), bố (familyzone)… Thật là hết sức thảm thương và tệ bạc!

				Thanks, Obama…
				Sự thương cảm và bất bình của chúng ta chủ yếu đến từ kết luận cho rằng Thằng Osin đã đầu tư quá nhiều vào mối quan hệ mà không nhận được gì. Theo kinh tế học, đây là một khoản đầu tư hoàn toàn thất bại. Theo phạm trù đạo đức thông thường, sau bao nhiêu hy sinh và cống hiến như vậy, Thằng Osin xứng đáng được cô nàng đền đáp một tình yêu chân thành.

				Vì những đánh giá và bất bình như trên, nếu Thằng Osin kia có mối quan hệ gần gũi với chúng ta (bạn bè, họ hàng…) chúng ta sẽ tìm cách “chửi cho nó sáng mắt ra” vì “không thể để nó tự làm khổ mình như thế mãi được” với những mệnh đề quen thuộc như:

				Nó cho mày cái gì đâu mà mày vì nó thế?
				Tao thấy mày nhục vđ mà có được cái gì đâu?
				Xu hướng khổ dâm à?
				Sao mày ngu và cố chấp thế? — Lú tình à? — Ăn phải bả của nó à?
				Tao nói đ nghe sau này bị nó phũ thì đừng khóc lóc.
				Nhưng sự thật liệu có phải như vậy? Liệu có đúng là Thằng Osin “ngu ngơ”, “bị lú tình”, “cho đi không hề nhận lại” đúng như những gì chúng ta kết luận?

				Alain de Botton và mình cho là không phải như vậy.

				Chương 19. Bên ngoài Thiện và Ác, Alain viết:

				Liệu tôi có tốt đẹp hơn Chloe chỉ vì tôi yêu cô ấy? Tất nhiên là không, bởi vì mặc dù tình yêu của tôi dành cho cô bao hàm sự hy sinh, tôi trao tình yêu cho cô vì tôi hạnh phúc khi làm thế, tôi không hy sinh bản thân mình, tôi đã hành động chỉ vì nó tương hợp quá hoàn hảo với những thiên hướng của tôi, vì nó không phải bổn phận.
				Dù không trực tiếp đề cập tới, nhưng khẳng định trên của Alain rất phù hợp với thuyết Tư lợi Vị tha (Enlightened self-interest), trong đó:

				“một người hành động vì lợi ích của người khác (hoặc lợi ích của một nhóm hoặc những nhóm họ thuộc về), cuối cùng là phục vụ lợi ích của chính họ.”
				Thằng Osin không chỉ đơn giản là hy sinh một cách mù quáng, mà họ đang đánh đổi những giá trị hữu hình (thời gian, tiền bạc…) để nhận lại những giá trị vô hình (sự thoả mãn trong tâm hồn, tình cảm…). Và vì tình yêu luôn luôn là một trải nghiệm cá nhân, làm sao bạn có thể hiểu và cảm thấy những giá trị vô hình mà Thằng Osin nhận được?

				Đến đây, chúng ta có thể tạm kết luận rằng Thằng Osin không hề “cao thượng và vị tha” như chúng ta tưởng, nên chúng ta có thể tạm ngừng bài ca chửi rủa và bớt đi ý định “khai sáng” cho nó. Tuy nhiên, câu chuyện của Thằng Osin chưa dừng lại tại đây.

				Bạn đã phần nào hiểu và ngừng phán xét Thằng Osin, để hắn mặc sức chìm đắm trong sự đam mê và khoái lạc của giá trị vô hình hắn đem đánh đổi được. Tuy nhiên, bạn vẫn khó chịu với cách hành xử của hắn, và cũng như nếu bạn để ý, nhiều lúc hắn vẫn hoài nghi về những gì mình nhận được. Có một điều gì đó vẫn sai và thiếu ở mối tình này. Tại sao cả bạn (người “có vẻ” khách quan đứng ngoài) và hắn (người chủ quan đứng trong) đều có cảm giác như vậy?

				Câu trả lời nằm ở Lý thuyết Tam giác Tình Yêu (Triangular theory of love) của nhà tâm lý học Robert Sternberg:

				Mô hình Tam giác Tình yêu
				Như lý thuyết này cho thấy, một tình yêu “hoàn hảo” chỉ xuất hiện khi đủ 3 yếu tố: Tính thân mật — Đam mê — Cam kết. Rõ ràng những giá trị vô hình Thằng Osin nhận được chỉ đáp ứng được hai đỉnh Tính thân mật và Đam mê. Sự thiếu hụt Cam kết tạo ra cảm giác bất an và mất an toàn về mối quan hệ này, kéo theo là những đêm dài mất ngủ suy nghĩ và cảm giác kết thúc rõ ràng luôn thấy trước của Thằng Osin. Đây là lí do dù say đắm tới nhường nào, chúng ta vẫn cần những lời tỏ tình, những bức ảnh, tuyên bố công khai… để tự an ủi mình về sự chắc chắn của mối quan hệ.

				Thật tội nghiệp Thằng Osin, vì hắn sẽ chẳng bao giờ có được điều đó…

				Có thể đến đây bạn sẽ hỏi, vậy liệu Thằng Osin có nên tiếp tục mối quan hệ vừa sung sướng vừa khổ đau này? Thật khó để trả lời. Sẽ chẳng bao giờ có một công thức chung trong tình yêu, vì dù não bộ chúng ta có logic và siêu việt đến nhường nào, hormone và trái tim loạn nhịp khi yêu làm sẽ làm nó lú lẫn hết cả đi. Tuy nhiên, chúng ta có thể đưa cho hắn một số công cụ để hắn tự soi rọi vào tình yêu của hẳn.

				Vì sao con người lại Yêu? Chúng ta đâm đầu vào yêu, yêu lấy yêu để, yêu hùng hục, yêu dù biết đắng cay khổ đau nhục nhã cũng không thiếu gì bên cạnh những sung sướng đam mê tê dại? Phải có một động lực ghê gớm lắm khiến cả loài người phát điên lên vì yêu như vậy (tạm thời chúng ta sẽ bỏ qua nhu cầu duy trì nói giống). Trong Tuyên ngôn Độc lập Hoa Kỳ có nói tới ba quyền cơ bản nhất của con người gồm Quyền được sống, quyền tự do và quyền mưu cầu hạnh phúc. Con người yêu, vì con người mưu cầu hạnh phúc. Công thức của hạnh phúc như sau:

				it’s not simple as it looks, dude…
				Công thức này được hai nhà kinh tế học Manel Baucells và Rakesh Sarin đưa ra vào năm 2011. Một phương trình đơn giản giữa Thực tế và Kì vọng. Khi Thực tế lớn hơn Kì vọng, bạn hạnh phúc. Khi Kì vọng lớn hơn Thực tế, đó là mầm mống khổ đau và tuyệt vọng.

				Bên cạnh những giá trị vô hình, kì vọng chính là động lực thúc đẩy Thằng Osin theo đuổi mối quan hệ mang tính chất khá một chiều này. Kì vọng về một tương lai cô ấy sẽ cảm động, cô ấy sẽ yêu mình, cô ấy sẽ… Kì vọng luôn luôn có một sức mạnh lừa phỉnh rất to lớn, vì chúng cho chúng ta sự yên tâm, nhưng là yên tâm trong thì tương lai. Nói cách khác, chính những kì vọng này đã tạo ra một đỉnh Cam kết “ảo của thì tương lai” trong Tam giác Tình yêu, khiến Thằng Osin nghĩ rằng đây chính là “tình yêu hoàn hảo” của đời hắn. Thằng Osin đã rơi vào cái bẫy tự huyễn hoặc bản thân lúc nào không biết.

				Đã đến lúc ngồi lại, bình tĩnh nhìn vào sự thật rồi, anh bạn…

				Mình viết không nhằm mục đích chỉ ra thế nào là yêu đúng, yêu sai. Mình cho rằng tình yêu là lãnh địa huyền bí của cảm xúc, những phân tích tâm lí hay triết học sâu sắc đến nhường nào cũng không thể bao trùm hết ý nghĩa của tình yêu. Mình chỉ mong các bạn nào kiên nhẫn đọc hết bài viết này (chắc là bạn cũng đang yêu?), hãy mở lòng và vị tha hơn với sự mù quáng của những kẻ đang yêu. Vì bản thân tình yêu đâu có tội, đúng không?

				Tái bút: Dù viết có vẻ logic và deep như vậy nhưng tác giả yêu vào cũng lú bỏ mẹ, nên các bạn cứ yêu nhiệt đi, nghĩ làm gì cho mệt ihihi

				- nguồn https://www.linkedin.com/pulse/lu%E1%BA%ADn-v%E1%BB%81-y%C3%AAu-hay-l%C3%A0-con-ch%C3%B3-v%C3%A0-th%E1%BA%B1ng-osin-nguy%E1%BB%85n-duy-qu%C3%AD
			*/
		}
		void LIGHT(int num)
		{
			// cout << "light " << num << endl;
			if (num>0) {
				customer *temp = table->get();
				int len = table->getSize();
				for (int i=0;i<len;i++){
					cout << temp->name << "-" << temp->energy << endl;
					temp = temp->next;
				}
			} else if (num<0) {
				customer *temp = table->get();
				int len = table->getSize();
				for (int i=0;i<len;i++){
					cout << temp->name << "-" << temp->energy << endl;
					temp = temp->next;
				}
			} else {
				int len = queue->getSize();
				for (int i=0;i<len;i++){
					cout << queue->getat(i)->name << "-" << queue->getat(i)->energy << endl;
				}
			}
		}
};
//main.cpp
void simulate(string filename, imp_res* r)
{
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
    	}
        else if(str == "RED") // RED <NAME> <ENERGY>
        {
            ss >> name;
            ss >> energy;
            r->RED(name, stoi(energy));
    	}
    	else if(str == "BLUE") // BLUE <NUM>
    	{
                ss >> num;
    			r->BLUE(stoi(num));
		}
    	else if(str == "PURPLE") // PURPLE
    	{
    			r->PURPLE();
		}
		else if(str == "REVERSAL") // REVERSAL
		{
    			r->REVERSAL();	
		}
    	else if(str == "UNLIMITED_VOID") // UNLIMITED_VOID
     	{   	
    			r->UNLIMITED_VOID();
    	}
    	else if(str == "DOMAIN_EXPANSION") // DOMAIN_EXPANSION
    	{
    			r->DOMAIN_EXPANSION();
    	}
    	else // LIGHT <NUM>
    	{
                ss >> num;
    			r->LIGHT(stoi(num));
    	}
    }
}

int main(int argc, char* argv[]) {
	//if (argc < 2)
    //	return 1;
	//  string fileName = argv[1];
	imp_res* r = new imp_res();
	string fileName = "test.txt";
    simulate(fileName, r);
  	delete r;
	return 0;
}

