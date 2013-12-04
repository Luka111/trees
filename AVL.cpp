#include <stdlib.h>
#include <iomanip>
#include <iostream>
using namespace std;
#include "AVL.h"

	AVL::AVL() : stb(0) {}
	AVL::AVL(int b) {stb = new Cvor(b);}
	AVL::AVL(const AVL& AVL){stb = kopiraj(AVL.stb);}
	AVL::~AVL() {brisi(stb);}
	bool AVL::prazno() const { return stb == 0;}
	void AVL::inorder() const {inorder(stb);}
	int AVL::min() const{
		if (!stb) exit(1);
		return min(stb)->broj;
	}
	int AVL::max() const{
		if (!stb) exit(1);
		return max(stb)->broj;
	}
	AVL::Cvor* AVL::nadji(int b) const{ return nadji(stb,b);}
	void AVL::dodaj(int b) {dodaj(stb, b);}
	//Citamo i ubacujemo elemente u stablo
	void AVL::citaj(int n){
		brisi(stb);
		for(int i=0;i<n;i++){
			int b;
			cout<<"Unesite "<<i+1<<". cvor stabla"<<endl;
			cin >> b;
			dodaj(b);
		}
	}
	void AVL::brisi() {brisi(stb);}
	void AVL::brisiCvor(int b) {brisiCvor(stb,b);}
	void AVL::crtaj() const{crtaj(stb,0);}

//Staticke metode

	//Kopiranje datog stabla
	AVL::Cvor* AVL::kopiraj(Cvor *stb){
		Cvor *tek = stb,*prvi=0,*novi=0,*pret=0;
		int pomeraj=0,brojPodSt=0,strana;
		if(stb==0) return 0;
		if(stb->levo!=0) ++brojPodSt;
		if(stb->desno!=0) ++brojPodSt;
		if(!brojPodSt){
			return new Cvor(tek->broj);
		};
		while(!(tek->otac==0 && pomeraj==brojPodSt)){
			if(!pomeraj){
				novi = new Cvor(tek->broj,tek->visinaLevo,tek->visinaDesno,pret);
				pret=novi;
				if(novi->otac){
					(strana==1?novi->otac->levo=novi:novi->otac->desno=novi);
				}else{
					prvi=novi;
				}
			}
			if(tek->levo && pomeraj==0){
				tek=tek->levo;
				pomeraj=0;
				strana=1;
			}else{
				if(tek->desno && pomeraj<=1){
					tek=tek->desno;
					pomeraj=0;
					strana=-1;
				}else{
					pomeraj=(tek->otac->levo==tek?1:2);
					tek=tek->otac;
					pret=pret->otac;
				}
			}
		}
		return prvi;
	}
	//Brisanje stabla
	void AVL::brisi(Cvor *stb){
		if(stb){
			brisi(stb->levo);brisi(stb->desno);delete stb;stb=0;
		}
	}
	//Ispisivanje stabla po inorderu
	void AVL::inorder(Cvor *stb){
		if(stb){
			inorder(stb->levo); cout << stb->broj << " "; inorder(stb->desno);
		}
	}
	//Dodavanje celog broja u skup
	void AVL::dodaj(Cvor *&stb, int b){
		Cvor *tek=stb,*pret=0,*novi = new Cvor(b);
		novi->visinaLevo=novi->visinaDesno=0;
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
		novi->otac=pret;
		if(!pret){
			stb=novi;
			return;
		}
		if(b>pret->broj){
			pret->desno = novi;
		}else{
			pret->levo = novi;
		}
		balans(stb,novi);
	}
	//Najmanji broj u skupu
	AVL::Cvor* AVL::min(Cvor *stb){
		Cvor *tek = stb;
		while(tek->levo){
			tek=tek->levo;
		}
		return tek;
	}
	//Najveci broj u skupu
	AVL::Cvor* AVL::max(Cvor *stb){
		Cvor *tek = stb;
		while(tek->desno){
			tek=tek->desno;
		}
		return tek;
	}
	//Pronalazenje datog broja u skupu (vraca pokazivac na cvor)
	AVL::Cvor* AVL::nadji(Cvor *stb, int b){
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

	//Brise cvor iz AVL stabla
	void AVL::brisiCvor(Cvor *&stb, int b){
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
			if(pret){
				(strana?pret->levo:pret->desno) = 0;
				(strana?--pret->visinaLevo:--pret->visinaDesno);
				tek->levo=tek->desno=tek->otac=0;
				delete tek;
				balansB(stb,pret);
			}else{
				stb=0;
				tek->levo=tek->desno=tek->otac=0;
				delete tek;
			};
		}else{
			if(!tek->levo || !tek->desno){
				Cvor *bal = (tek->levo?tek->levo:tek->desno);
				if(pret){
					(strana?pret->levo:pret->desno) =bal;
					bal->otac=pret;
					(strana?--pret->visinaLevo:--pret->visinaDesno);
					tek->levo=tek->desno=tek->otac=0;
					delete tek;
					balansB(stb,bal);
				}else{
					stb=bal;
					tek->levo=tek->desno=tek->otac=0;
					delete tek;
				};
			}else{
				Cvor *succ = tek->desno,*succpar=0,*bal;
				while(succ->levo){
					succpar=succ;
					succ=succ->levo;
				}
				if (!succpar){
					bal=succ;
				}else{
					bal=succpar;
					(bal->levo->otac==bal?--bal->visinaLevo:--bal->visinaDesno);
				};
				succ->otac=pret;
				if(pret){
					(strana?pret->levo:pret->desno) = succ;
				}else{
					stb = succ;
				}
				if(succpar){
					succpar->levo = succ->desno;
					if(succ->desno)succ->desno->otac = succpar;
				}
				if(succ!=tek->levo){
					succ->levo = tek->levo;
					tek->levo->otac = succ;
				}
				if(succ!=tek->desno){
					succ->desno = tek->desno;
					tek->desno->otac = succ;
				}
				succ->visinaLevo=tek->visinaLevo;
				if(succpar!=0)succ->visinaDesno=tek->visinaDesno;
				tek->levo=tek->desno=tek->otac=0;
				delete tek;
				balansB(stb,bal);
			}
		}
	}
	//Crtanje stabla
	void AVL::crtaj(Cvor *stb, int nivo){
		if(stb){
			crtaj(stb->desno, nivo+1);
			cout << setw(4*nivo) <<"" << stb->broj << endl;
			crtaj(stb->levo, nivo+1);
		}
	}
	//Balansiranje stabla pri dodavanju
	void AVL::balans(Cvor *&stb, Cvor *list){
		int br=0;
		while(list->otac){
			int pretBalans = list->visinaLevo-list->visinaDesno;
			int strana = (list->otac->levo==list?1:-1);
			int flag=0;
			list=list->otac;
			br+=1;
			if(!list->otac){
				flag=1;
			};
			if(br>(strana==1?list->visinaLevo:list->visinaDesno)){
				++(strana==1?list->visinaLevo:list->visinaDesno);
			};
			int balans=list->visinaLevo-list->visinaDesno;
			if(balans==-2){
				if(pretBalans<=0){
					list=levaRotacija(stb,list);
					flag=1;
				};
				if(pretBalans==1){
					desnaRotacija(stb,list->desno);
					list=levaRotacija(stb,list);
					flag=1;
				};
			};
			if(balans==2){
				if(pretBalans>=0){
					list=desnaRotacija(stb,list);
					flag=1;
				};
				if(pretBalans==-1){
					levaRotacija(stb,list->levo);
					list=desnaRotacija(stb,list);
					flag=1;
				};
			};
			if(flag) break;
		}
	}
	//Balansiranje stabla pri brisanju
	void AVL::balansB(Cvor *&stb, Cvor *list){
		int pretBalans = 0,br=1,flag=0;
		do{
			if(!list->otac){
				flag=1;
			};
			int strana;
			if(!flag){
				if(list){
					strana = (list->otac->levo==list?1:-1);
				}
			};
			int balans=list->visinaLevo-list->visinaDesno;
			if(balans==-2){
				if((br==1) && (list->desno!=0) && (!list->levo)){
					pretBalans=list->desno->visinaLevo-list->desno->visinaDesno;
				};
				if(pretBalans<=0){
					list = levaRotacija(stb,list);
				};
				if(pretBalans==1){
					desnaRotacija(stb,list->desno);
					list = levaRotacija(stb,list);
				};
			};
			if(balans==2){
				if((br==1) && (list->levo!=0) && (!list->desno)){
					pretBalans=list->levo->visinaLevo-list->levo->visinaDesno;
				};
				if(pretBalans>=0){
					list = desnaRotacija(stb,list);
				};
				if(pretBalans==-1){
					levaRotacija(stb,list->levo);
					list = desnaRotacija(stb,list);
				};
			};
			if(flag) break;
			if(!flag){
				(strana==1?list->otac->visinaLevo=maxInt(list->visinaLevo,list->visinaDesno)+1:list->otac->visinaDesno=maxInt(list->visinaLevo,list->visinaDesno)+1);
			}
			list=list->otac;
			br+=1;
			pretBalans = balans;
		}while(list);
	}
	//Leva Rotacija
	AVL::Cvor* AVL::levaRotacija(Cvor *&stb, Cvor *cvor){
		Cvor *vrati = cvor->desno;
		cvor->visinaDesno=cvor->desno->visinaLevo;
		cvor->desno->visinaLevo=1+maxInt(cvor->visinaLevo,cvor->desno->visinaLevo);
		cvor->desno->otac=cvor->otac;
		if(cvor->otac==0){
			stb=cvor->desno;
		}else{
			(cvor->otac->desno==cvor?cvor->otac->desno:cvor->otac->levo)=cvor->desno;
		};
		cvor->otac=cvor->desno;
		Cvor *temp = cvor->desno->levo;
		cvor->desno->levo = cvor;
		cvor->desno=temp;
		if(temp){
			temp->otac=cvor;
		};
		return vrati;
	}
	//Desna Rotacija
	AVL::Cvor* AVL::desnaRotacija(Cvor *&stb, Cvor *cvor){
		Cvor *vrati = cvor->levo;
		cvor->visinaLevo=cvor->levo->visinaDesno;
		cvor->levo->visinaDesno=1+maxInt(cvor->visinaDesno,cvor->levo->visinaDesno);
		cvor->levo->otac=cvor->otac;
		if(cvor->otac==0){
			stb=cvor->levo;
		}else{
			(cvor->otac->levo==cvor?cvor->otac->levo:cvor->otac->desno)=cvor->levo;
		};
		cvor->otac=cvor->levo;
		Cvor *temp = cvor->levo->desno;
		cvor->levo->desno = cvor;
		cvor->levo=temp;
		if(temp){
			temp->otac=cvor;
		};
		return vrati;
	}
	//Dodavanje elemenata jednog stabla drugom po inorderu
	void AVL::inorderDodaj(Cvor *stb){
		if(stb){
			if(nadji(this->stb,stb->broj)==0){
				dodaj(this->stb,stb->broj);
			}
			inorderDodaj(stb->levo);
			inorderDodaj(stb->desno);
		}
	}
	//Brisanje elementa jednog stabla iz drugog po inorderu
	void AVL::inorderRazlika(Cvor *stb1, Cvor *stb2){
		if(stb2){
			if(nadji(stb1,stb2->broj)==0){
				dodaj(this->stb,stb2->broj);
			}
			inorderRazlika(stb1,stb2->levo);
			inorderRazlika(stb1,stb2->desno);
		}
	}
	//Elementi koji se nalaze i u jednom i u drugom skupu (ubacivanje po preorder-u)
	void AVL::inorderPresek(Cvor *stb1, Cvor *stb2){
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
	AVL unija(const AVL& stablo1, const AVL& stablo2){
		AVL uStablo;
		uStablo.inorderDodaj(stablo1.stb);
		uStablo.inorderDodaj(stablo2.stb);
		return uStablo;
	}

	//Razlika 2 skupa
	AVL razlika(const AVL& stablo1, const AVL& stablo2){
		AVL rStablo;
		rStablo.inorderRazlika(stablo2.stb,stablo1.stb);
		return rStablo;
	}

	//Presek 2 skupa
	AVL presek(const AVL& stablo1, const AVL& stablo2){
		AVL pStablo;
		pStablo.inorderPresek(stablo1.stb,stablo2.stb);
		return pStablo;
	}

	//Maksimum 2 int-a
	int maxInt(int a,int b){
		return (a>=b?a:b);
	}