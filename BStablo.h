#pragma once
class BStablo{
	struct Cvor{
		Cvor **mPokazivaci;
		int **mKljucevi;
		Cvor *mOtac;
		Cvor(int red,Cvor *cvor,int m,int n);
		Cvor(int red,int broj,Cvor *prvi=0, Cvor *drugi=0);
	};
	Cvor *stb;
	int mRed;
	int mVisina;
	int mBrKljuceva;
public:
	BStablo(int r);
	~BStablo();
	void brisi();
	int getVisina() const;
	int getBrKljuceva() const;
	bool nadji(int a) const;
	void dodaj(int b);
	void crtaj() const;
	void brisiBroj(int b);
private:
	static void brisi(int red,Cvor *stb);
	static void unistiCvor(int red,Cvor *cvor);
	static bool nadji(int a,int red, Cvor *stb);
	static void dodaj(int red,int &brKljuceva, int &visina,Cvor *&stb, int b);
	static bool dodajUCvor(int red, Cvor *&stb, Cvor *cvor, int b, Cvor *prvi, Cvor *drugi);
	static void crtaj(int red, int brKlj, Cvor *stb);
	static void brisiBroj(int red, int &brKljuceva, int &visina, Cvor *&stb, int b);
	static bool brisiIzCvora(int red, Cvor*&stb, Cvor *cvor);
};

