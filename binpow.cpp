int binpow (int a, int x) {
	int ans = 1;
	while(x) {
		if (x & 1)
			ans = (ans*1ll*a)%mod;
		a = (a * 1ll* a)%mod;
		x >>= 1;
	}
	return ans%mod;
}