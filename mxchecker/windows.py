import ctypes
from ctypes import wintypes

class HW_PROFILE_INFO(ctypes.Structure):
    _fields_ = [
        ("dwDockInfo", wintypes.DWORD),
        ("szHwProfileGuid", wintypes.WCHAR * 39), 
        ("szHwProfileName", wintypes.WCHAR * 80),
    ]

advapi32 = ctypes.WinDLL('Advapi32.dll')
GetCurrentHwProfileW = advapi32.GetCurrentHwProfileW
GetCurrentHwProfileW.argtypes = [ctypes.POINTER(HW_PROFILE_INFO)]
GetCurrentHwProfileW.restype = wintypes.BOOL

def getHwid():
    info = HW_PROFILE_INFO()
    if GetCurrentHwProfileW(ctypes.byref(info)):
        return info.szHwProfileGuid  
    else:
        return None