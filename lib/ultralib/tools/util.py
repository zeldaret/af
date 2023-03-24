
import struct

def enumerate_stepped(l, start=0, step=1):
    p = start
    for e in l:
        yield p, e
        p += step

def back_align(x, al):
    return x - (x % al)

def forward_align(x, al):
    return (x + (al - 1)) & ~(al - 1)

def as_double(b):
    return struct.unpack(">d", b)[0]

def as_dword(b):
    return struct.unpack(">Q", b)[0]

def as_float(b):
    return struct.unpack(">f", b)[0]

def as_word(b):
    return struct.unpack(">I", b)[0]

def as_hword(b):
    return struct.unpack(">H", b)[0]

def as_double_list(b):
    return [i[0] for i in struct.iter_unpack(">d", b)]

def as_dword_list(b):
    return [i[0] for i in struct.iter_unpack(">Q", b)]

def as_float_list(b):
    return [i[0] for i in struct.iter_unpack(">f", b)]

def as_word_list(b):
    return [i[0] for i in struct.iter_unpack(">I", b)]

def as_hword_list(b):
    return [h[0] for h in struct.iter_unpack(">H", b)]
