#pragma once
class BST{
	//Cvor stabla BST-a
	struct Cvor {
		int broj;
		Cvor *levo;
		Cvor *desno;
		Cvor(int b, Cvor* l=0, Cvor* d=0){
			broj=b;
			levo=l;
			desno=d;
		}
	};
	//Pokazivac na koren
	Cvor* stb;
public:
	BST();
	BST(int b);
	BST(const BST& bst);
	~BST();
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
	friend BST unija(const BST& stablo1, const BST& stablo2);
	friend BST razlika(const BST& stablo1, const BST& stablo2);
	friend BST presek(const BST& stablo1, const BST& stablo2);
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
	void inorderDodaj(Cvor *stb);
	void inorderRazlika(Cvor *stb1, Cvor *stb2);
	void inorderPresek(Cvor *stb1, Cvor *stb2);
};

