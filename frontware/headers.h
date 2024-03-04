#pragma once

#ifdef _WIN32
#define USERNAME_LENGHT 0x101
#define COMPUTER_NAME_LENGHT 0x10
#define CPU_INFO_LENGHT 0x40
#endif

#ifdef __linux__

#define USERNAME_LENGHT 0x40

#endif