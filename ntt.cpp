#include<bits/stdc++.h>
#include "PrimeField.hpp"
#define ll long long
using namespace std;
const int p = 998244353;//998244353
PrimeField<p> root=root.get_generator();
void fft (vector<PrimeField<p> > &a, bool invert) {
	int n = (int) a.size();
	if (n == 1)  return;

	vector<PrimeField<p> > a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	fft (a0, invert);
	fft (a1, invert);

	PrimeField<p> w = 1;
	PrimeField<p> wlen = root;
	wlen = wlen^((p-1)/(int)a.size());
	if(invert)
		wlen = ~wlen;
	for (int i=0; i<n/2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i+n/2] = a0[i] - w * a1[i];
		if(invert){
            a[i] /= 2;
            a[i+n/2] /= 2;
		}
        w = w * wlen;
	}
}
vector<PrimeField<p> >& multiply(vector<PrimeField<p> > &a, vector<PrimeField<p> > &b){
	vector<PrimeField<p> > fa(a.begin(), a.end()), fb(b.begin(), b.end());
	size_t n = 1;
	while(max(a.size(), b.size()) > n)
		n <<= 1;
	n <<= 1;
	fa.resize(n);
	fb.resize(n);
	fft(fa, 0);
	fft(fb, 0);
	for(size_t i=0;i<n;i++)
		fa[i] = fa[i] * fb[i];
	fft(fa, 1);
	return  *(new vector<PrimeField<p> > (fa.begin(), fa.end()));
}	
int main(){
    vector<PrimeField<p> > a = {1,1,1};
    vector<PrimeField<p> > b = {1,1,1};
	for(auto i:multiply(a,b)){
		cout<<i<<" ";
	}
}

