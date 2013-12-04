#include "BStablo.h"
#include <iomanip>
#include <iostream>
using namespace std;
//Konstruktori cvora
BStablo::Cvor::Cvor(int red, Cvor* cvor,int m,int n):
		mPokazivaci(new Cvor* [red]),
		mKljucevi(new int* [red-1])
		{
			int i,j=0;
			mOtac=cvor->mOtac;
			for(i=0;i<red-1;i++){
					mPokazivaci[i]=0;
					mKljucevi[i]=0;
				if(i>=m && i<=n){
					mPokazivaci[j]=cvor->mPokazivaci[i];
					mKljucevi[j++]=cvor->mKljucevi[i];
				}
			}
			mPokazivaci[i]=0;
			if(n==red-1){
				mPokazivaci[i]=cvor->mPokazivaci[i];
			}
		}

BStablo::Cvor::Cvor(int red, int broj,Cvor *prvi, Cvor *drugi):
		mPokazivaci(new Cvor* [red]),
		mKljucevi(new int* [red-1])
		{
			int i;
			mOtac=0;
			for(i=0;i<red-1;i++){
				if(i==0){
					mKljucevi[i]=new int (broj);
					mPokazivaci[i]=prvi;
				}else{
					if(i==1){
						mKljucevi[i]=0;
						mPokazivaci[i]=drugi;
					}else{
						mKljucevi[i]=0;
						mPokazivaci[i]=0;
					}
				}
			}
			mPokazivaci[i]=0;
			if(mPokazivaci[0]!=0){
				mPokazivaci[0]->mOtac=this;
			}
			if(mPokazivaci[0]!=0){
				mPokazivaci[1]->mOtac=this;
			}
		}

//Javne metode
BStablo::BStablo(int r):
	mRed(r),
	mVisina(0),
	mBrKljuceva(0),
	stb(0)
	{
	}

BStablo::~BStablo(){
	brisi();
}

void BStablo::brisi(){
	brisi(mRed,stb);
	stb=0;
}

int BStablo::getVisina() const{
	return mVisina;
}

int BStablo::getBrKljuceva() const{
	return mBrKljuceva;
}

bool BStablo::nadji(int a) const{
	return nadji(a,mRed,stb);
}

void BStablo::dodaj(int b){
	dodaj(mRed,mBrKljuceva,mVisina,stb,b);
}

void BStablo::crtaj() const{
	crtaj(mRed,mBrKljuceva,stb);
}

void BStablo::brisiBroj(int b){
	brisiBroj(mRed,mBrKljuceva,mVisina,stb,b);
}
//
//Privatne staticne metode
void BStablo::brisi(int red,Cvor *stb){
	int i=0;
	if(stb){
		while(i<red-1){
			brisi(red, stb->mPokazivaci[i++]);
		}
		unistiCvor(red,stb);
	}
}

void BStablo::unistiCvor(int red,Cvor *cvor){
	//delete cvor->mPokazivaci;
	//delete cvor->mKljucevi;
	delete cvor;
}

bool BStablo::nadji(int a,int red,Cvor *stb){
	if(stb==0) return false;
	Cvor *tek = stb;
	while (1){
		int i=0;
		while(tek->mKljucevi[i]!=0){
			int trKljuc = *tek->mKljucevi[i];
			if(a==trKljuc){
				cout<<"Kljuc "<<a<<" je pronadjen!"<<endl;
				return true;
			};
			if(a<trKljuc){
				if(tek->mPokazivaci[i]){
					tek=tek->mPokazivaci[i];
					i=0;
				}else{
					cout<<"Kljuc "<<a<<" NE POSTOJI u stablu. Pretraga neuspesna."<<endl;
					return false;
				}
			}else{
				i++;
			}
			if((tek->mKljucevi[i]==0)||(i==red-1)){
				if(tek->mPokazivaci[i]){
					tek=tek->mPokazivaci[i];
					i=0;
				}else{
					cout<<"Kljuc "<<a<<" NE POSTOJI u stablu. Pretraga neuspesna."<<endl;
					return false;
				}
			}
		}
	}
}

void BStablo::dodaj(int red,int &brKljuceva, int &visina,Cvor *&stb, int b){
	if(!stb){
		stb = new Cvor(red,b);
		visina++;
		brKljuceva++;
		cout<<"Uspesno dodavanje kljuca "<<b<<" u stablo!"<<endl;
		return;
	}
	//Trazimo cvor gde treba da ubacimo novi broj
	Cvor *tek = stb;
	int flag=1;
	while(flag){
		int i=0;
		while(tek->mKljucevi[i]!=0){
			int trKljuc = *tek->mKljucevi[i];
			if(b==trKljuc){
				cout<<"Kljuc "<<b<<" vec postoji!. Dodavanje neuspesno"<<endl;
				return;
			}
			if(b<trKljuc){
				if(tek->mPokazivaci[i]){
					tek=tek->mPokazivaci[i];
					break;
				}else{
					flag=0;
					break;
				}
			}else{
				i++;
			}
			if((tek->mKljucevi[i]==0)||(i==red-1)){
				if(tek->mPokazivaci[i]){
					tek=tek->mPokazivaci[i];
					break;
				}else{
					flag=0;
					break;
				}
			}
		}
	}
	//Na list u koji treba da ubacimo novi element pokazuje tek
	if(dodajUCvor(red,stb,tek,b,0,0)){
		visina++;
	};
	brKljuceva++;
	cout<<"Uspesno dodavanje kljuca "<<b<<" u stablo!"<<endl;
	return;
}

bool BStablo::dodajUCvor(int red, Cvor *&stb, Cvor *cvor, int b, Cvor *prvi, Cvor *drugi){
	if(cvor->mKljucevi[red-2]==0){
		int i=red-2;
		while(cvor->mKljucevi[--i]==0){
		}
		while(*cvor->mKljucevi[i]>b){
			cvor->mKljucevi[i+1]=cvor->mKljucevi[i];
			cvor->mPokazivaci[i+2]=cvor->mPokazivaci[i+1];
			i--;
			if(i==-1)break;
		}
		cvor->mKljucevi[i+1] = new int (b);
		cvor->mPokazivaci[i+1] = prvi;
		cvor->mPokazivaci[i+2] = drugi;
		return false;
	}else{
		int *niz = new int [red];
		int i;
		for(i=0;i<red-1;i++){
			niz[i]=*cvor->mKljucevi[i];
		}
		i=red-1;
		while(b<niz[i-1]){
			niz[i]=niz[i-1];
			i--;
		}
		niz[i]=b;
		int low = red/2-1, mid = red/2;
		int j=0;
		for(i=0;i<red;i++){
			if(i!=mid){
				*cvor->mKljucevi[j++]=niz[i];
			}
		}
		int srednji = niz[mid];
		Cvor* p = new Cvor(red,cvor,0,low);
		Cvor* d = new Cvor(red,cvor,mid,red-1);
		Cvor *otac = cvor->mOtac;
		if(otac!=0){
			int i=0;
			while(i<red){
				if(otac->mPokazivaci[i]==cvor){
					cvor->mOtac->mPokazivaci[i]=0;
				}
				i++;
			}
		}
		if(prvi!=0){
			int i=0;
			int j=0;
			while(i<red){
				bool nula = (cvor->mPokazivaci[i]==0?true:false);
				if(i==red/2){
					if(nula){
						p->mPokazivaci[j]=prvi;
						p->mPokazivaci[j]->mOtac=p;
						j=0;
						d->mPokazivaci[j]=drugi;
						d->mPokazivaci[j]->mOtac=d;
						j++;
					}else{
						p->mPokazivaci[j]=cvor->mPokazivaci[i];
						p->mPokazivaci[j]->mOtac=p;
						j=0;
					}
				}
				if(i<red/2){
					if(nula){
						p->mPokazivaci[j]=prvi;
						p->mPokazivaci[j]->mOtac=p;
						j++;
						p->mPokazivaci[j]=drugi;
						p->mPokazivaci[j]->mOtac=p;
						j++;
					}else{
						p->mPokazivaci[j]=cvor->mPokazivaci[i];
						p->mPokazivaci[j]->mOtac=p;
						j++;
					}
				}
				if(i>red/2){
					if(nula){
						d->mPokazivaci[j]=prvi;
						d->mPokazivaci[j]->mOtac=d;
						j++;
						d->mPokazivaci[j]=drugi;
						d->mPokazivaci[j]->mOtac=d;
						j++;
					}else{
						d->mPokazivaci[j]=cvor->mPokazivaci[i];
						d->mPokazivaci[j]->mOtac=d;
						j++;
					}
				}
				i++;
			}
		}
		//ukloniCvor(red,cvor);
		delete [] niz;
		if(otac!=0){
			dodajUCvor(red,stb,otac,srednji,p,d);
		}else{
			stb = new Cvor(red,srednji,p,d);
			return true;
		}
	}
}

void BStablo::crtaj(int red, int brKlj, Cvor *stb){
	if(stb==0) return;
	Cvor** stek = new Cvor* [brKlj*red];
	int i,br=0,cnt=0,brNivo=0,brNivoP=0;
	if(stb==0) return;
	//Ispisujemo koren, i njegove sinove stavljamo na stek
	for(i=0;i<red-1;i++){
		if(stb->mKljucevi[i]!=0) {
			cout<<*stb->mKljucevi[i]<<" ";
		}
		if(stb->mPokazivaci[i]!=0){
			stek[br++]=stb->mPokazivaci[i];
			brNivo++;
		}
	}
	//Poslednji sin
	if(stb->mPokazivaci[i]!=0){
		stek[br++]=stb->mPokazivaci[i];
		brNivo++;
	}
	cout<<endl;
	while(cnt<br){
		Cvor *tek = stek[cnt++];
		for(i=0;i<red-1;i++){
			if(tek->mKljucevi[i]!=0) cout<<*tek->mKljucevi[i]<<" ";
			if(tek->mPokazivaci[i]!=0){
				stek[br++]=tek->mPokazivaci[i];
				brNivoP++;
			}
		}
		if(tek->mPokazivaci[i]!=0){
			stek[br++]=tek->mPokazivaci[i];
			brNivoP++;
		}
		brNivo--;
		if(brNivo>0){
			cout<<"   ";
		}else{
			brNivo=brNivoP;
			brNivoP=0;
			cout<<endl;
		}
	}
	delete [] stek;
}

void BStablo::brisiBroj(int red, int &brKljuceva, int &visina, Cvor *&stb, int b){
	if(stb==0) return;
	Cvor *tek = stb;
	//Trazimo cvor gde se nalazi zadati broj
	int flag=1,i;
	while (flag){
		i=0;
		while(tek->mKljucevi[i]!=0){
			int trKljuc = *tek->mKljucevi[i];
			if(b==trKljuc){
				cout<<"Kljuc "<<b<<" je pronadjen!"<<endl;
				flag=0;
				break;
			};
			if(b<trKljuc){
				if(tek->mPokazivaci[i]){
					tek=tek->mPokazivaci[i];
					i=0;
				}else{
					cout<<"Kljuc "<<b<<" NE POSTOJI u stablu. Pretraga neuspesna."<<endl;
					return;
				}
			}else{
				i++;
			}
			if((tek->mKljucevi[i]==0)||(i==red-1)){
				if(tek->mPokazivaci[i]){
					tek=tek->mPokazivaci[i];
					i=0;
				}else{
					cout<<"Kljuc "<<b<<" NE POSTOJI u stablu. Pretraga neuspesna."<<endl;
					return;
				}
			}
		}
	}
	//Zamenjujemo ga sa sledbenikom u slucaju da nadjeni broj nije u listu
	//'i' mesto u cvoru gde se broj nalazi
	if(tek->mPokazivaci[0]!=0){
		Cvor *pom = tek;
		tek=tek->mPokazivaci[i+1];
		while(tek->mPokazivaci[0]!=0){
			tek=tek->mPokazivaci[0];
		}
		int t = *pom->mKljucevi[i];
		*pom->mKljucevi[i] = *tek->mKljucevi[0];
		*tek->mKljucevi[0] = t;
	}
	//Brisemo dati broj tako sto sve elemente desno od njega pomeramo za jedno mesto u levo
	while(i<red-2){
		tek->mKljucevi[i]=tek->mKljucevi[i+1];
		i++;
	}
	tek->mKljucevi[i]=0;
	//'brisiIzCvora' vodi racuna o tome da li je u cvoru iz koga se brise ostalo dovoljno cvorova
	//Ili moramo vrsiti pozajmicu/spajanje
	if(brisiIzCvora(red,stb,tek)){
		visina--;
	};
	brKljuceva--;
	cout<<"Uspesno brisanje kljuca "<<b<<" iz stabla!"<<endl;
	return;
}

bool BStablo::brisiIzCvora(int red, Cvor *&stb, Cvor *cvor){
	if(cvor->mOtac!=0){
		int broj=0,i;
		for(i=0;i<red-1;i++){
			if(cvor->mKljucevi[i]!=0) {
				broj++;
			}
		}
		if(broj>=red/2){
			return false;
		}else{
			int pom=broj;
			i=0;
			int brojR=0;
			//Cvor iz koga brisemo je u i-tom pokazivacu roditeljskog cvora
			//'brojR' pokazuje koliko elemenata ima roditeljski cvor
			while(i<red-1){
				if(cvor->mOtac->mKljucevi[i]!=0) brojR++;
				if(cvor->mOtac->mPokazivaci[i]==cvor) break;
				i++;
			}
			int poz=i;
			int brcv = 0;
			int flag = 0;
			if(poz<red-1){ 
				flag=(cvor->mOtac->mPokazivaci[poz+1]!=0?1:0);
			}
			//Proveravamo da li u njegovom desnom bratu ima dovoljno cvorova za pozajmicu
			if(flag){
				for(i=0;i<red-1;i++){
					if(cvor->mOtac->mPokazivaci[poz+1]->mKljucevi[i]!=0) brcv++;
				}
			}
			if(brcv>red/2+1){
				int i;
				cvor->mKljucevi[pom]=cvor->mOtac->mKljucevi[poz];
				cvor->mPokazivaci[pom+1]=cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[0];
				cvor->mOtac->mKljucevi[poz]=cvor->mOtac->mPokazivaci[poz+1]->mKljucevi[0];
				for(i=0;i<red-2;i++){
					cvor->mOtac->mPokazivaci[poz+1]->mKljucevi[i]=cvor->mOtac->mPokazivaci[poz+1]->mKljucevi[i+1];
					cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[i]=cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[i+1];
				}
				cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[i]=cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[i+1];
				cvor->mOtac->mPokazivaci[poz+1]->mKljucevi[i+1]=0;
				cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[i+2]=0;
				return false;
			}else{
				//Sada proveravamo za levog brata
				brcv=0;
				flag=0;
				if(poz>0){
					flag=(cvor->mOtac->mPokazivaci[poz-1]!=0?1:0);
				}
				if(flag){
					for(i=0;i<red-1;i++){
						if(cvor->mOtac->mPokazivaci[poz-1]->mKljucevi[i]!=0)brcv++;
					}
				}
				if(brcv>=red/2+1){
					int i;
					cvor->mPokazivaci[pom+1]=cvor->mPokazivaci[pom];
					for(int i=pom;i>0;i--){
						cvor->mKljucevi[i]=cvor->mKljucevi[i-1];
						cvor->mPokazivaci[i]=cvor->mPokazivaci[i-1];
					}
					//trazimo koliko elemenata ima levi brat
					i=0;
					while(i<red-1){
						if(cvor->mOtac->mPokazivaci[poz-1]->mKljucevi[i]==0) break;
						i++;
					}
					int brojCvLB=i;
					cvor->mKljucevi[0]=cvor->mOtac->mKljucevi[poz-1];
					cvor->mPokazivaci[0]=cvor->mOtac->mPokazivaci[poz-1]->mPokazivaci[brojCvLB];
					cvor->mOtac->mKljucevi[poz-1]=cvor->mOtac->mPokazivaci[poz-1]->mKljucevi[brojCvLB-1];
					cvor->mOtac->mPokazivaci[poz-1]->mKljucevi[brojCvLB-1]=0;
					cvor->mOtac->mPokazivaci[poz-1]->mPokazivaci[brojCvLB]=0;
					return false;
				}else{
					//Ako nema dovoljno elemenata za pozajmicu ni u levom ni u desnom bratu moramo vrsiti spajanje
					//Punimo cvor iz koga je obrisan element, elementom roditeljskog cvora koji razdvaja njega i desnog brata
					//Kao i svim elementima desnog brata
					int i;
					//Ako ima desnog brata
					flag=0;
					if(poz<red-1){
						flag=(cvor->mOtac->mPokazivaci[poz+1]!=0?1:0);
					}
					if(flag){
						cvor->mKljucevi[pom]=cvor->mOtac->mKljucevi[poz];
						i=0;
						while(i<red-1){
							if(cvor->mOtac->mPokazivaci[poz+1]->mKljucevi[i]==0)break;
							cvor->mKljucevi[pom+1+i]=cvor->mOtac->mPokazivaci[poz+1]->mKljucevi[i];
							cvor->mPokazivaci[pom+1+i]=cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[i];
							i++;
						}
						cvor->mPokazivaci[pom+1+i]=cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[i];
						//Regulisemo brata (+Brisanje)
						for(i=0;i<red-1;i++){
							cvor->mOtac->mPokazivaci[poz+1]->mKljucevi[i]=0;
							cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[i]=0;
						}
						//Regulisemo oca
						for(i=poz;i<red-2;i++){
							cvor->mOtac->mKljucevi[i]=cvor->mOtac->mKljucevi[i+1];
							cvor->mOtac->mPokazivaci[i+1]=cvor->mOtac->mPokazivaci[i+2];
						}
						cvor->mOtac->mKljucevi[i]=0;
						cvor->mOtac->mPokazivaci[i+1]=0;
						cvor->mOtac->mPokazivaci[poz+1]->mPokazivaci[i]=0;
						//unistiCvor(red,cvor->mOtac->mPokazivaci[poz+1]);
						brisiIzCvora(red,stb,cvor->mOtac);
					}else{
						//Ako nema onda moramo raditi isti postupak samo sa levim bratom
						//Trazimo koliko elemenata ima levi brat
						i=0;
						while(i<red-1){
							if(cvor->mOtac->mPokazivaci[poz-1]->mKljucevi[i]==0) break;
							i++;
						}
						int brojCvLB=i;						
						cvor->mPokazivaci[pom+brojCvLB]=cvor->mPokazivaci[pom];
						for(int i=pom;i>0;i--){
							cvor->mKljucevi[i+brojCvLB-1]=cvor->mKljucevi[i-1];
							cvor->mPokazivaci[i+brojCvLB-1]=cvor->mPokazivaci[i-1];
						}
						cvor->mKljucevi[brojCvLB]=cvor->mOtac->mKljucevi[poz-1];
						i=brojCvLB-1;
						while(i>=0){
							cvor->mKljucevi[i]=cvor->mOtac->mPokazivaci[poz-1]->mKljucevi[i];
							cvor->mPokazivaci[i]=cvor->mOtac->mPokazivaci[poz-1]->mPokazivaci[i];
							i--;
						}
						//Regulisemo brata (+Brisanje)
						for(i=0;i<red-1;i++){
							cvor->mOtac->mPokazivaci[poz-1]->mKljucevi[i]=0;
							cvor->mOtac->mPokazivaci[poz-1]->mPokazivaci[i]=0;
						}
						//Regulisemo oca
						for(i=poz-1;i<red-2;i++){
							cvor->mOtac->mKljucevi[i]=cvor->mOtac->mKljucevi[i+1];
							cvor->mOtac->mPokazivaci[i]=cvor->mOtac->mPokazivaci[i+1];
						}

						cvor->mOtac->mPokazivaci[i]=cvor->mOtac->mPokazivaci[i+1];
						cvor->mOtac->mKljucevi[i]=0;
						cvor->mOtac->mPokazivaci[poz-1]->mPokazivaci[i]=0;
						//unistiCvor(red,cvor->mOtac->mPokazivaci[poz-1]);
						brisiIzCvora(red,stb,cvor->mOtac);
					}
				}
			}
		}
	}else{
		if(cvor->mKljucevi[0]==0) {
			stb=(cvor->mPokazivaci[0]?cvor->mPokazivaci[0]:0);
			cvor->mPokazivaci[0]=0;
			unistiCvor(red,cvor);
			return true;
		}
		return false;
	}
}