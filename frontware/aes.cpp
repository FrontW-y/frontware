#include "aes.h"
#include "headers.h"

#include <iostream>

CryptoPP::byte* AESKey::getKey() {
	realloc(_key, sizeof(_key));
	return _key;
}

AESKey::AESKey()
{
		_prng.GenerateBlock(_key, sizeof(_key));
#if DEBUG
		std::cout << "0x" << &_key << " Allocated Buffer :  _key " << std::hex <<  _key  <<std::endl;
	#endif

		_prng.GenerateBlock(_iv, sizeof(_iv));
#if DEBUG
		std::clog << "0x" << &_iv << " Allocated Buffer :  _iv " << _iv << std::endl;
#endif

}

AESKey::~AESKey()
{
		return ;
}
