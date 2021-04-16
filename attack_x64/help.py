#!/usr/bin/env python3
# coding=utf-8

from capstone import *
import sys

if (len(sys.argv) < 2):
    sys.exit(0)

for t in range(1, len(sys.argv)):
    print("=" * 30 + f"{t:03}" + "=" * 30)
    CODE = bytes.fromhex(sys.argv[t])
    md = Cs(CS_ARCH_X86, CS_MODE_64)
    md.syntax = CS_OPT_SYNTAX_ATT

    print(f"CODE: {CODE}")
    for i in md.disasm(CODE, 0x1000):
        print(f"0x{i.address:x}:\t{i.mnemonic}\t{i.op_str}")

    print()
