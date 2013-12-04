#include <stdlib.h>
#include <iomanip>
#include <iostream>
using namespace std;
#include "BST.h"


	BST::BST() : stb(0) {}
	BST::BST(int b) {stb = new Cvor(b);}
	BST::BST(const BST& bst){stb = kopiraj(bst.stb);}
	BST::~BST() {brisi(stb);}
	bool BST::prazno() const { return stb == 0;}
	void BST::inorder() const {inorder(stb);}
	int BST::min() const{
		if (!stb) exit(1);
		return min(stb)->broj;
	}
	int BST::max() const{
		if (!stb) exit(1);
		return max(stb)->broj;
	}
	BST::Cvor* BST::nadji(int b) const{ 
		return nadji(stb,b);
	}
	void BST::dodaj(int b) {dodaj(stb, b);}
	//Citamo i ubacujemo elemente u stablo
	void BST::citaj(int n){
		brisi(stb);
		for(int i=0;i<n;i++){
			int b;
			cout<<"Unesite "<<i+1<<". cvor stabla"<<endl;
			cin >> b;
			dodaj(b);
		}
	}
	void BST::brisi() {brisi(stb);stb=0;}
	void BST::brisiCvor(int b) {brisiCvor(stb,b);}
	void BST::crtaj() const{crtaj(stb,0);}

//Staticke metode

	//Kopiranje datog stabla
	BST::Cvor* BST::kopiraj(Cvor *stb){
		return stb?
			new Cvor(stb->broj, kopiraj(stb->levo), kopiraj(stb->desno)):0;
	}
	//Brisanje stabla
	void BST::brisi(Cvor *stb){
		if(stb){
			brisi(stb->levo);brisi(stb->desno);delete stb;stb=0;
		}
	}
	//Ispisivanje stabla po inorderu
	void BST::inorder(Cvor *stb){
		if(stb){
			inorder(stb->levo); cout << stb->broj << " "; inorder(stb->desno);
		}
	}
	//Dodavanje celog broja u skup
	void BST::dodaj(Cvor *&stb, int b){
		Cvor *tek=stb,*pret=0,*novi = new Cvor(b);
		int flag = 0;
		while(tek){
			pret=tek;
			if(b==tek->broj){
				flag = 1;
				//cout<<"Broj "<<b<<" vec postoji u skupu!"<<endl;
				break;
				//exit(1);
			}
			if(b>tek->broj){
				tek=tek->desno;
			}else{
				tek=tek->levo;
			}
		}
		if(flag){
			return;
		}
		if(!pret){
			stb=novi;
			return;
		}
		if(b>pret->broj){
			pret->desno = novi;
		}else{
			pret->levo = novi;
		}
	}
	//Najmanji broj u skupu
	BST::Cvor* BST::min(Cvor *stb){
		Cvor *tek = stb;
		while(tek->levo){
			tek=tek->levo;
		}
		return tek;
	}
	//Najveci broj u skupu
	BST::Cvor* BST::max(Cvor *stb){
		Cvor *tek = stb;
		while(tek->desno){
			tek=tek->desno;
		}
		return tek;
	}
	//Pronalazenje datog broja u skupu (vraca pokazivac na cvor)
	BST::Cvor* BST::nadji(Cvor *stb, int b){
		Cvor *tek=stb;
		while (tek){
			if (tek->broj==b) return tek;
			if (tek->broj>b) {
				tek=tek->levo;
			}else{
				tek=tek->desno;
			}
		}
		return 0;
	}

	//Brise cvor iz Binarnog stabla
	void BST::brisiCvor(Cvor *&stb, int b){
		Cvor *tek = stb,*pret = 0;
		int strana = 0;
		while(tek){
			if(tek->broj==b){break;}
			pret = tek;
			if(tek->broj>b){
				tek=tek->levo;
				strana = 1;
			}else{
				tek=tek->desno;
				strana = 0;
			}
		}
		if(!tek){
			//cout<<"Cvor koji zelite da obrisete ne postoji!"<<endl;
			return;
		}
		if (!tek->levo && !tek->desno){
			(strana?pret->levo:pret->desno) = 0;
			tek->levo=tek->desno=0;
			delete tek;
		}else{
			if(!tek->levo || !tek->desno){
				if(pret) (strana?pret->levo:pret->desno) =(tek->levo?tek->levo:tek->desno);
				tek->levo=tek->desno=0;
				delete tek;
			}else{
				Cvor *succ = tek->desno,*succpar=0;
					while(succ->levo){
					succpar=succ;
					succ=succ->levo;
				}
				if(pret){
					(strana?pret->levo:pret->desno) = succ;
				}else{
					stb = succ;
				}
				if(succpar){
					succpar->levo = succ->desno;
				}
				if(succ!=tek->levo){
					succ->levo = tek->levo;
				}
				if(succ!=tek->desno){
					succ->desno = tek->desno;
				}
				tek->levo=tek->desno=0;
				delete tek;
			}
		}
		//cout<<"Broj "<<b<<" je USPESNO obrisan!"<<endl;
	}
	//Crtanje stabla
	void BST::crtaj(Cvor *stb, int nivo){
		if(stb){
			crtaj(stb->desno, nivo+1);
			cout << setw(4*nivo) <<"" << stb->broj << endl;
			crtaj(stb->levo, nivo+1);
		}
	}
	//Dodavanje elemenata jednog stabla drugom po inorderu
	void BST::inorderDodaj(Cvor *stb){
		if(stb){
			//if(nadji(this->stb,stb->broj)==0){
				dodaj(this->stb,stb->broj);
			//}
			inorderDodaj(stb->levo);
			inorderDodaj(stb->desno);
		}
	}
	//Brisanje elementa jednog stabla iz drugog po inorderu
	void BST::inorderRazlika(Cvor *stb1, Cvor *stb2){
		if(stb2){
			if(nadji(stb1,stb2->broj)==0){
				dodaj(this->stb,stb2->broj);
			}
			inorderRazlika(stb1,stb2->levo);
			inorderRazlika(stb1,stb2->desno);
		}
	}
	//Elementi koji se nalaze i u jednom i u drugom skupu (ubacivanje po preorder-u)
	void BST::inorderPresek(Cvor *stb1, Cvor *stb2){
		if(stb2){
			if(nadji(stb1,stb2->broj)!=0){
				dodaj(this->stb,stb2->broj);
			}
			inorderPresek(stb1,stb2->levo);
			inorderPresek(stb1,stb2->desno);
		}
	}

	//Prijateljske funkcije

	//Unija 2 skupa
	BST unija(const BST& stablo1, const BST& stablo2){
		BST uStablo;
		uStablo.inorderDodaj(stablo1.stb);
		uStablo.inorderDodaj(stablo2.stb);
		return uStablo;
	}

	//Razlika 2 skupa
	BST razlika(const BST& stablo1, const BST& stablo2){
		BST rStablo;
		rStablo.inorderRazlika(stablo2.stb,stablo1.stb);
		return rStablo;
	}

	//Presek 2 skupa
	BST presek(const BST& stablo1, const BST& stablo2){
		BST pStablo;
		pStablo.inorderPresek(stablo1.stb,stablo2.stb);
		return pStablo;
	}