#pragma once
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>


#define AES_KEY_LENGHT 32

class AESKey
{
	private:
		 CryptoPP::AutoSeededRandomPool _prng;
		 CryptoPP::byte _key[CryptoPP::AES::DEFAULT_KEYLENGTH];
		 CryptoPP::byte _iv[CryptoPP::AES::BLOCKSIZE];

	public:
	AESKey();
	~AESKey();
	CryptoPP::byte* getKey();

	


};