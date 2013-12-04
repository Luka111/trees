#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;
#include "BST.h"
#include "AVL.h"
#include "BStablo.h"
#include "PerformanceCalculator.h"

int main(){
	while(1){
		char ind;
		cout<<"Unesite za koje stablo zelite da vrsite testiranje:"<<endl;
		cout<<"Binarno/AVL stablo(1) | B Stablo (2) | Kraj Programa(0)"<<endl;
		cin>>ind;
		if(ind=='0'){
			exit(0);
		}
		switch (ind){
		case '1':{
			while(1){
				char op;
				cout<<"-----BINARNO/AVL STABLO-----"<<endl;
				cout<<"Performanse(1) | Rucno testiranje(2) | Kraj(0)"<<endl;
				cin>>op;
				if(op=='0'){
					break;
				}
				switch (op){
				case '1':{
					int granica [7] = {200,500,1000,2000,10000,100000,1000000};
					int i,j,k,a;
					for(j=0;j<7;j++){
						double *avlPerf = new double [7];
						double *binPerf = new double [7];
						PerformanceCalculator pc1,pc2;
						double pVreme1=0,pVreme2=0;
						AVL StabloA,StabloA2;
						BST StabloB,StabloB2;
						//FORMIRANJE
						for(i=0;i<granica[j];i++){
							//Generisanje slucajnog broja
							a = rand()/((double)RAND_MAX)*granica[j];
							//AVL stablo
							pc1.start();
							StabloA.dodaj(a);
							pc1.stop();
							pVreme1+=pc1.elapsedMillis();
							StabloA2.dodaj(a+1);
							//Binarno Stablo
							pc2.start();
							StabloB.dodaj(a);
							pc2.stop();
							pVreme2+=pc2.elapsedMillis();
							StabloB2.dodaj(a+1);
						}
						avlPerf[0] = pVreme1;
						binPerf[0] = pVreme2;
						//UMETANJE
						a = rand()/((double)RAND_MAX)*granica[j];
						pc1.start();
						StabloA.dodaj(a);
						pc1.stop();
						avlPerf[1]=pc1.elapsedMillis();
						pc2.start();
						StabloB.dodaj(a);
						pc2.stop();
						binPerf[1]=pc2.elapsedMillis();
						//BRISANJE
						a = rand()/((double)RAND_MAX)*granica[j];
						pc1.start();
						StabloA.brisiCvor(a+1);
						pc1.stop();
						avlPerf[2]=pc1.elapsedMillis();
						pc2.start();
						StabloB.brisiCvor(a);
						pc2.stop();
						binPerf[2]=pc2.elapsedMillis();
						//PRETRAGA
						a = rand()/((double)RAND_MAX)*granica[j];
						pc1.start();
						StabloA.nadji(a);
						pc1.stop();
						avlPerf[3]=pc1.elapsedMillis();
						pc2.start();
						StabloB.nadji(a);
						pc2.stop();
						binPerf[3]=pc2.elapsedMillis();
						//SKUPOVNE OPERACIJE
						//UNIJA
						pc1.start();
						unija(StabloA,StabloA2);
						pc1.stop();
						avlPerf[4]=pc1.elapsedMillis();
						pc2.start();
						unija(StabloB,StabloB2);
						pc2.stop();
						binPerf[4]=pc2.elapsedMillis();
						//PRESEK
						pc1.start();
						presek(StabloA,StabloA2);
						pc1.stop();
						avlPerf[5]=pc1.elapsedMillis();
						pc2.start();
						presek(StabloB,StabloB2);
						pc2.stop();
						binPerf[5]=pc2.elapsedMillis();
						//RAZLIKA
						pc1.start();
						razlika(StabloA,StabloA2);
						pc1.stop();
						avlPerf[6]=pc1.elapsedMillis();
						pc2.start();
						razlika(StabloB,StabloB2);
						pc2.stop();
						binPerf[6]=pc2.elapsedMillis();
						//
						cout<<"PERFORMANSE ZA SKUP VELICINE: "<<granica[j]<<endl;
						cout<<"      FORMIRANJE  UMETANJE  BRISANJE  PRETRAGA  UNIJA  PRESEK  RAZLIKA"<<endl;
						cout<<"AVL ";
						for(i=0;i<7;i++){
							cout<<avlPerf[i]<<"  ";
						}
						cout<<endl;
						cout<<"BINARNO ";
						for(i=0;i<7;i++){
							cout<<binPerf[i]<<"  ";
						}
						//
						cout<<endl;
						if(j<3){
							cout<<"Sledeci krug testiranja - "<<granica[j+1]<<" clanova."<<endl;
							cout<<"Unesite bilo koji karakter da nastavite testiranje perforamnsi.."<<endl;
						}
						getchar();
						getchar();
						delete [] avlPerf;
						delete [] binPerf;
					}
					break;
					}
				case '2':{
					while(1){
						char vr;
						cout<<"Da li zelite da testirate Binarno(1) ili AVL(2)? Kraj(0)"<<endl;
						cin>>vr;
						if(vr=='0') break;
						switch (vr){
							case '1':{
							BST Stablo;
							while(1){
								int b;
								cout<<"-----BINARNO STABLO-----"<<endl;
								cout<<"Dodavanje brojeva u stablo (1)"<<endl;
								cout<<"Pretraga na celi broj (2)"<<endl;
								cout<<"Brisanje celog broja (3)"<<endl;
								cout<<"Skupovne operacije (4)"<<endl;
								cout<<"CRTAJ Binarno stablo (5)"<<endl;
								cout<<"Izbrisi celo stablo (6)"<<endl;
								cout<<"Kraj rada sa binarnim stablom(0)"<<endl;
								cin>>b;
								if(b==0){
									break;
								}
								switch (b){
								case 1:{
									while(1){
										int c;
										cout<<"Unesite celi broj koji zelite da dodate u stablo | Vrati(0)"<<endl;
										cin>>c;
										if(c==0)break;
										Stablo.dodaj(c);
									}
									break;
									}
								case 2:{
									int c;
									while(1){
										cout<<"Unesite celi broj na koji pretrazujete | Vrati(0)"<<endl;
										cin>>c;
										if(c==0)break;
										Stablo.nadji(c);
									}
									break;
									}
								case 3:{
									int c;
									while(1){
										cout<<"Unesite celi broj koji zelite da obrisete iz stabla | Vrati(0)"<<endl;
										cin>>c;
										if(c==0)break;
										Stablo.brisiCvor(c);
									}
									break;
									}
								case 4:{
									BST Stablo2;
									cout<<"--TESTIRANJE SKUPOVNIH OPERACIJA--"<<endl;
									cout<<"Da bi ste otpoceli testiranje morate formirati novi skup"<<endl;
									while(1){
										int c;
										cout<<"Unesite celi broj koji zelite da dodate u NOVO stablo | Kraj unosa(0)"<<endl;
										cin>>c;
										if(c==0)break;
										Stablo2.dodaj(c);
									}
									cout<<"----- Izgled starog stabla: -----"<<endl;
									Stablo.crtaj();
									cout<<"-----------------"<<endl;
									cout<<"----- Izgled novog stabla sa kojim cemo raditi skupovne operacije: -----"<<endl;
									Stablo2.crtaj();
									cout<<"-----------------"<<endl;
									while(1){
										int c;
										cout<<"Unija(1) | Presek(2) | Razlika(3) | Kraj(0)"<<endl;
										cin>>c;
										if(c==0) break;
										switch(c){
										case 1:{
											BST Skup = unija(Stablo,Stablo2);
											cout<<"-----UNIJA-----"<<endl;
											Skup.crtaj();
											break;
											}
										case 2:{
											BST Skup = presek(Stablo,Stablo2);
											cout<<"-----PRESEK-----"<<endl;
											Skup.crtaj();
											break;
											}
										case 3:{
											BST Skup = razlika(Stablo,Stablo2);
											cout<<"-----RAZLIKA-----"<<endl;
											Skup.crtaj();
											break;
											}
										}
									}
									break;
									}
								case 5:{
									cout<<"-----IZGLED BINARNOG STABLA-----"<<endl;
									Stablo.crtaj();
									break;
									}
								case 6:{
									Stablo.brisi();
									cout<<"Stablo je izbrisano!"<<endl;
									break;
									}
								default:continue;
								}
							}
							break;
							}
							case '2':{
							AVL Stablo;
							while(1){
								int b;
								cout<<"-----AVL STABLO-----"<<endl;
								cout<<"Dodavanje brojeva u stablo (1)"<<endl;
								cout<<"Pretraga na celi broj (2)"<<endl;
								cout<<"Brisanje celog broja (3)"<<endl;
								cout<<"Skupovne operacije (4)"<<endl;
								cout<<"CRTAJ AVL stablo (5)"<<endl;
								cout<<"Brisanje citavog stabla (6)"<<endl;
								cout<<"Kraj rada sa AVL stablom(0)"<<endl;
								cin>>b;
								if(b==0){
									break;
								}
								switch (b){
								case 1:{
									while(1){
										int c;
										cout<<"Unesite celi broj koji zelite da dodate u stablo | Vrati(0)"<<endl;
										cin>>c;
										if(c==0)break;
										Stablo.dodaj(c);
									}
									break;
									}
								case 2:{
									int c;
									while(1){
										cout<<"Unesite celi broj na koji pretrazujete | Vrati(0)"<<endl;
										cin>>c;
										if(c==0)break;
										Stablo.nadji(c);
									}
									break;
									}
								case 3:{
									int c;
									while(1){
										cout<<"Unesite celi broj koji zelite da obrisete iz stabla | Vrati(0)"<<endl;
										cin>>c;
										if(c==0)break;
										Stablo.brisiCvor(c);
									}
									break;
									}
								case 4:{
									AVL Stablo2;
									cout<<"--TESTIRANJE SKUPOVNIH OPERACIJA--"<<endl;
									cout<<"Da bi ste otpoceli testiranje morate formirati novi skup"<<endl;
									while(1){
										int c;
										cout<<"Unesite celi broj koji zelite da dodate u NOVO stablo | Kraj unosa(0)"<<endl;
										cin>>c;
										if(c==0)break;
										Stablo2.dodaj(c);
									}
									cout<<"----- Izgled starog stabla: -----"<<endl;
									Stablo.crtaj();
									cout<<"-----------------"<<endl;
									cout<<"----- Izgled novog stabla sa kojim cemo raditi skupovne operacije: -----"<<endl;
									Stablo2.crtaj();
									cout<<"-----------------"<<endl;
									while(1){
										int c;
										cout<<"Unija(1) | Presek(2) | Razlika(3) | Kraj(0)"<<endl;
										cin>>c;
										if(c==0) break;
										switch(c){
										case 1:{
											AVL Skup = unija(Stablo,Stablo2);;
											cout<<"-----UNIJA-----"<<endl;
											Skup.crtaj();
											break;
											}
										case 2:{
											AVL Skup = presek(Stablo,Stablo2);
											cout<<"-----PRESEK-----"<<endl;
											Skup.crtaj();
											break;
											}
										case 3:{
											AVL Skup = razlika(Stablo,Stablo2);
											cout<<"-----RAZLIKA-----"<<endl;
											Skup.crtaj();
											break;
											}
										}
									}
									break;
									}
								case 5:{
									cout<<"-----IZGLED AVL STABLA-----"<<endl;
									Stablo.crtaj();
									break;
									}
								case 6:{
									Stablo.brisi();
									cout<<"Stablo je obrisano!"<<endl;
									break;
									}
								default:continue;
								}
							}
							break;
							}
						}
					}
					break;
					}
				default: continue;
				}
			}
			break;
			}
		case '2':{
			while(1){
				int a;
				cout<<"Unesite red B stabla | Kraj rada (0)"<<endl;
				cin>>a;
				if(a<=1||a>100){
					break;
				}
				BStablo B(a);
				while(1){
					int b;
					cout<<"-----B STABLO-----"<<endl;
					cout<<"Dodavanje novog celog broja (1)"<<endl;
					cout<<"Pretraga na celi broj (2)"<<endl;
					cout<<"Broj elemenata stabla? (3)"<<endl;
					cout<<"Visina stabla? (4)"<<endl;
					cout<<"Crtaj B Stablo (5)"<<endl;
					cout<<"Brisi element B Stabla (6)"<<endl;
					cout<<"Brisanje celog stabla (7)"<<endl;
					cout<<"Kraj rada (0)"<<endl;
					cin>>b;
					if(b==0){
						break;
					}
					switch (b){
					case 1:{
						while(1){
							int c;
							cout<<"Unesite celi broj koji zelite da dodate u stablo | Vrati(0)"<<endl;
							cin>>c;
							if(c==0)break;
							B.dodaj(c);
						}
						break;
						}
					case 2:{
						while(1){
							int c;
							cout<<"Unesite celi broj na koji pretrazujete | Vrati(0)"<<endl;
							cin>>c;
							if(c==0)break;
							B.nadji(c);
						}
						break;
						}
					case 3:{
						cout<<"Broj elemenata stabla - "<<B.getBrKljuceva()<<endl;
						break;
						}
					case 4:{
						cout<<"Visina stabla - "<<B.getVisina()<<endl;
						break;
						}
					case 5:{
						B.crtaj();
						break;
						}
					case 6:{
						int c;
							cout<<"Unesite celi broj koji zelite da obrisete | Vrati(0)"<<endl;
							cin>>c;
							if(c==0)break;
							B.brisiBroj(c);
						}
					case 7:{
						B.brisi();
						break;
						}
					default:continue;
					}
				}
			}
			break;
			}
		}
	}
};