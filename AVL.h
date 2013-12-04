#pragma once
class AVL{
	//Cvor stabla AVL-a
	struct Cvor {
		int broj;
		Cvor *levo;
		Cvor *desno;
		Cvor *otac;
		int visinaLevo;
		int visinaDesno;
		Cvor(int b,int vl=0,int vd=0,Cvor* o=0, Cvor* l=0, Cvor* d=0){
			broj=b;
			levo=l;
			desno=d;
			otac = o;
			visinaLevo=vl;
			visinaDesno=vd;
		}
	};
	//Pokazivac na koren
	Cvor* stb;
public:
	AVL();
	AVL(int b);
	AVL(const AVL& AVL);
	~AVL();
	bool prazno() const;
	void inorder() const;
	int min() const;
	int max() const;
	Cvor* nadji(int b) const;
	void dodaj(int b);
	void citaj(int n);
	void brisi();
	void brisiCvor(int b);
	void crtaj() const;
	friend AVL unija(const AVL& stablo1, const AVL& stablo2);
	friend AVL razlika(const AVL& stablo1, const AVL& stablo2);
	friend AVL presek(const AVL& stablo1, const AVL& stablo2);
private:
	static Cvor* kopiraj(Cvor *stb);
	static void brisi(Cvor *stb);
	static void inorder(Cvor *stb);
	static void dodaj(Cvor *&stb, int b);
	static Cvor* min(Cvor *stb);
	static Cvor* max(Cvor *stb);
	static Cvor* nadji(Cvor *stb, int b);
	static void brisiCvor(Cvor *&stb, int b);
	static void crtaj(Cvor *stb, int nivo);
	static void balans(Cvor *&stb, Cvor *list);
	static void balansB(Cvor *&stb, Cvor *list);
	static Cvor* levaRotacija(Cvor *&stb, Cvor *cvor);
	static Cvor* desnaRotacija(Cvor *&stb, Cvor *cvor);
	void inorderDodaj(Cvor *stb);
	void inorderRazlika(Cvor *stb1, Cvor *stb2);
	void inorderPresek(Cvor *stb1, Cvor *stb2);
};
	int maxInt(int a,int b);

