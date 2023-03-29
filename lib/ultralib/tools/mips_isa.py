# TODO enum these constants
from enum import IntEnum, auto

# Register IDs
class MipsGPReg(IntEnum):
    R0 = 0      # 0
    AT = auto() # 1
    V0 = auto() # 2
    V1 = auto() # 3
    A0 = auto() # 4
    A1 = auto() # 5
    A2 = auto() # 6
    A3 = auto() # 7
    T0 = auto() # 8
    T1 = auto() # 9
    T2 = auto() # 10
    T3 = auto() # 11
    T4 = auto() # 12
    T5 = auto() # 13
    T6 = auto() # 14
    T7 = auto() # 15
    S0 = auto() # 16
    S1 = auto() # 17
    S2 = auto() # 18
    S3 = auto() # 19
    S4 = auto() # 20
    S5 = auto() # 21
    S6 = auto() # 22
    S7 = auto() # 23
    T8 = auto() # 24
    T9 = auto() # 25
    K0 = auto() # 26
    K1 = auto() # 27
    GP = auto() # 28
    SP = auto() # 29
    FP = auto() # 30
    RA = auto() # 31

class MipsFPReg(IntEnum):
    F0  = 0      # 0
    F1  = auto() # 1
    F2  = auto() # 2
    F3  = auto() # 3
    F4  = auto() # 4
    F5  = auto() # 5
    F6  = auto() # 6
    F7  = auto() # 7
    F8  = auto() # 8
    F9  = auto() # 9
    F10 = auto() # 10
    F11 = auto() # 11
    F12 = auto() # 12
    F13 = auto() # 13
    F14 = auto() # 14
    F15 = auto() # 15
    F16 = auto() # 16
    F17 = auto() # 17
    F18 = auto() # 18
    F19 = auto() # 19
    F20 = auto() # 20
    F21 = auto() # 21
    F22 = auto() # 22
    F23 = auto() # 23
    F24 = auto() # 24
    F25 = auto() # 25
    F26 = auto() # 26
    F27 = auto() # 27
    F28 = auto() # 28
    F29 = auto() # 29
    F30 = auto() # 30
    F31 = auto() # 31

# Instruction Unique IDs
MIPS_INS_SLL       = 0
MIPS_INS_SRL       = 1
MIPS_INS_SRA       = 2
MIPS_INS_SLLV      = 3
MIPS_INS_SRLV      = 4
MIPS_INS_SRAV      = 5
MIPS_INS_JR        = 6
MIPS_INS_JALR      = 7
MIPS_INS_SYSCALL   = 8
MIPS_INS_BREAK     = 9
MIPS_INS_SYNC      = 10
MIPS_INS_MFHI      = 11
MIPS_INS_MTHI      = 12
MIPS_INS_MFLO      = 13
MIPS_INS_MTLO      = 14
MIPS_INS_DSLLV     = 15
MIPS_INS_DSRLV     = 16
MIPS_INS_DSRAV     = 17
MIPS_INS_MULT      = 18
MIPS_INS_MULTU     = 19
MIPS_INS_DIV       = 20
MIPS_INS_DIVU      = 21
MIPS_INS_DMULT     = 22
MIPS_INS_DMULTU    = 23
MIPS_INS_DDIV      = 24
MIPS_INS_DDIVU     = 25
MIPS_INS_ADD       = 26
MIPS_INS_ADDU      = 27
MIPS_INS_SUB       = 28
MIPS_INS_SUBU      = 29
MIPS_INS_AND       = 30
MIPS_INS_OR        = 31
MIPS_INS_XOR       = 32
MIPS_INS_NOR       = 33
MIPS_INS_SLT       = 34
MIPS_INS_SLTU      = 35
MIPS_INS_DADD      = 36
MIPS_INS_DADDU     = 37
MIPS_INS_DSUB      = 38
MIPS_INS_DSUBU     = 39
MIPS_INS_TGE       = 40
MIPS_INS_TGEU      = 41
MIPS_INS_TLT       = 42
MIPS_INS_TLTU      = 43
MIPS_INS_TEQ       = 44
MIPS_INS_TNE       = 45
MIPS_INS_DSLL      = 46
MIPS_INS_DSRL      = 47
MIPS_INS_DSRA      = 48
MIPS_INS_DSLL32    = 49
MIPS_INS_DSRL32    = 50
MIPS_INS_DSRA32    = 51
MIPS_INS_BLTZ      = 52
MIPS_INS_BGEZ      = 53
MIPS_INS_BLTZL     = 54
MIPS_INS_BGEZL     = 55
MIPS_INS_TGEI      = 56
MIPS_INS_TGEIU     = 57
MIPS_INS_TLTI      = 58
MIPS_INS_TLTIU     = 59
MIPS_INS_TEQI      = 60
MIPS_INS_TNEI      = 61
MIPS_INS_BLTZAL    = 62
MIPS_INS_BGEZAL    = 63
MIPS_INS_BLTZALL   = 64
MIPS_INS_BGEZALL   = 65
MIPS_INS_J         = 66
MIPS_INS_JAL       = 67
MIPS_INS_BEQ       = 68
MIPS_INS_BNE       = 69
MIPS_INS_BLEZ      = 70
MIPS_INS_BGTZ      = 71
MIPS_INS_ADDI      = 72
MIPS_INS_ADDIU     = 73
MIPS_INS_SLTI      = 74
MIPS_INS_SLTIU     = 75
MIPS_INS_ANDI      = 76
MIPS_INS_ORI       = 77
MIPS_INS_XORI      = 78
MIPS_INS_LUI       = 79
MIPS_INS_MFC0      = 80
MIPS_INS_MTC0      = 81
MIPS_INS_TLBR      = 82
MIPS_INS_TLBWI     = 83
MIPS_INS_TLBWR     = 84
MIPS_INS_TLBP      = 85
MIPS_INS_ERET      = 86
MIPS_INS_MFC1      = 87
MIPS_INS_DMFC1     = 88
MIPS_INS_CFC1      = 89
MIPS_INS_MTC1      = 90
MIPS_INS_DMTC1     = 91
MIPS_INS_CTC1      = 92
MIPS_INS_BC1F      = 93
MIPS_INS_BC1T      = 94
MIPS_INS_BC1FL     = 95
MIPS_INS_BC1TL     = 96
MIPS_INS_ADD_S     = 97
MIPS_INS_SUB_S     = 98
MIPS_INS_MUL_S     = 99
MIPS_INS_DIV_S     = 100
MIPS_INS_SQRT_S    = 101
MIPS_INS_ABS_S     = 102
MIPS_INS_MOV_S     = 103
MIPS_INS_NEG_S     = 104
MIPS_INS_ROUND_L_S = 105
MIPS_INS_TRUNC_L_S = 106
MIPS_INS_CEIL_L_S  = 107
MIPS_INS_FLOOR_L_S = 108
MIPS_INS_ROUND_W_S = 109
MIPS_INS_TRUNC_W_S = 110
MIPS_INS_CEIL_W_S  = 111
MIPS_INS_FLOOR_W_S = 112
MIPS_INS_CVT_D_S   = 113
MIPS_INS_CVT_W_S   = 114
MIPS_INS_CVT_L_S   = 115
MIPS_INS_C_F_S     = 116
MIPS_INS_C_UN_S    = 117
MIPS_INS_C_EQ_S    = 118
MIPS_INS_C_UEQ_S   = 119
MIPS_INS_C_OLT_S   = 120
MIPS_INS_C_ULT_S   = 121
MIPS_INS_C_OLE_S   = 122
MIPS_INS_C_ULE_S   = 123
MIPS_INS_C_SF_S    = 124
MIPS_INS_C_NGLE_S  = 125
MIPS_INS_C_SEQ_S   = 126
MIPS_INS_C_NGL_S   = 127
MIPS_INS_C_LT_S    = 128
MIPS_INS_C_NGE_S   = 129
MIPS_INS_C_LE_S    = 130
MIPS_INS_C_NGT_S   = 131
MIPS_INS_ADD_D     = 132
MIPS_INS_SUB_D     = 133
MIPS_INS_MUL_D     = 134
MIPS_INS_DIV_D     = 135
MIPS_INS_SQRT_D    = 136
MIPS_INS_ABS_D     = 137
MIPS_INS_MOV_D     = 138
MIPS_INS_NEG_D     = 139
MIPS_INS_ROUND_L_D = 140
MIPS_INS_TRUNC_L_D = 141
MIPS_INS_CEIL_L_D  = 142
MIPS_INS_FLOOR_L_D = 143
MIPS_INS_ROUND_W_D = 144
MIPS_INS_TRUNC_W_D = 145
MIPS_INS_CEIL_W_D  = 146
MIPS_INS_FLOOR_W_D = 147
MIPS_INS_CVT_S_D   = 148
MIPS_INS_CVT_W_D   = 149
MIPS_INS_CVT_L_D   = 150
MIPS_INS_C_F_D     = 151
MIPS_INS_C_UN_D    = 152
MIPS_INS_C_EQ_D    = 153
MIPS_INS_C_UEQ_D   = 154
MIPS_INS_C_OLT_D   = 155
MIPS_INS_C_ULT_D   = 156
MIPS_INS_C_OLE_D   = 157
MIPS_INS_C_ULE_D   = 158
MIPS_INS_C_SF_D    = 159
MIPS_INS_C_NGLE_D  = 160
MIPS_INS_C_SEQ_D   = 161
MIPS_INS_C_NGL_D   = 162
MIPS_INS_C_LT_D    = 163
MIPS_INS_C_NGE_D   = 164
MIPS_INS_C_LE_D    = 165
MIPS_INS_C_NGT_D   = 166
MIPS_INS_CVT_S_W   = 167
MIPS_INS_CVT_D_W   = 168
MIPS_INS_CVT_S_L   = 169
MIPS_INS_CVT_D_L   = 170
MIPS_INS_BEQL      = 171
MIPS_INS_BNEL      = 172
MIPS_INS_BLEZL     = 173
MIPS_INS_BGTZL     = 174
MIPS_INS_DADDI     = 175
MIPS_INS_DADDIU    = 176
MIPS_INS_LDL       = 177
MIPS_INS_LDR       = 178
MIPS_INS_LB        = 179
MIPS_INS_LH        = 180
MIPS_INS_LWL       = 181
MIPS_INS_LW        = 182
MIPS_INS_LBU       = 183
MIPS_INS_LHU       = 184
MIPS_INS_LWR       = 185
MIPS_INS_LWU       = 186
MIPS_INS_SB        = 187
MIPS_INS_SH        = 188
MIPS_INS_SWL       = 189
MIPS_INS_SW        = 190
MIPS_INS_SDL       = 191
MIPS_INS_SDR       = 192
MIPS_INS_SWR       = 193
MIPS_INS_CACHE     = 194
MIPS_INS_LL        = 195
MIPS_INS_LWC1      = 196
MIPS_INS_LWC2      = 197
MIPS_INS_LLD       = 198
MIPS_INS_LDC1      = 199
MIPS_INS_LDC2      = 200
MIPS_INS_LD        = 201
MIPS_INS_SC        = 202
MIPS_INS_SWC1      = 203
MIPS_INS_SWC2      = 204
MIPS_INS_SCD       = 205
MIPS_INS_SDC1      = 206
MIPS_INS_SDC2      = 207
MIPS_INS_SD        = 208

# RSP COP2
MIPS_INS_VMULF     = 209
MIPS_INS_VMULU     = 210
MIPS_INS_VRNDP     = 211
MIPS_INS_VMULQ     = 212
MIPS_INS_VMUDL     = 213
MIPS_INS_VMUDM     = 214
MIPS_INS_VMUDN     = 215
MIPS_INS_VMUDH     = 216
MIPS_INS_VMACF     = 217
MIPS_INS_VMACU     = 218
MIPS_INS_VRNDN     = 219
MIPS_INS_VMACQ     = 220
MIPS_INS_VMADL     = 221
MIPS_INS_VMADM     = 222
MIPS_INS_VMADN     = 223
MIPS_INS_VMADH     = 224
MIPS_INS_VADD      = 225
MIPS_INS_VSUB      = 226
MIPS_INS_VABS      = 227
MIPS_INS_VADDC     = 228
MIPS_INS_VSUBC     = 229
MIPS_INS_VSAR      = 230
MIPS_INS_VLT       = 231
MIPS_INS_VEQ       = 232
MIPS_INS_VNE       = 233
MIPS_INS_VGE       = 234
MIPS_INS_VCL       = 235
MIPS_INS_VCH       = 236
MIPS_INS_VCR       = 237
MIPS_INS_VMRG      = 238
MIPS_INS_VAND      = 239
MIPS_INS_VNAND     = 240
MIPS_INS_VOR       = 241
MIPS_INS_VNOR      = 242
MIPS_INS_VXOR      = 243
MIPS_INS_VNXOR     = 244
MIPS_INS_VRCP      = 245
MIPS_INS_VRCPL     = 246
MIPS_INS_VRCPH     = 247
MIPS_INS_VMOV      = 248
MIPS_INS_VRSQ      = 249
MIPS_INS_VRSQL     = 250
MIPS_INS_VRSQH     = 251
MIPS_INS_VNOP      = 252
MIPS_INS_LBV       = 253
MIPS_INS_LSV       = 254
MIPS_INS_LLV       = 255
MIPS_INS_LDV       = 256
MIPS_INS_LQV       = 257
MIPS_INS_LRV       = 258
MIPS_INS_LPV       = 259
MIPS_INS_LUV       = 260
MIPS_INS_LHV       = 261
MIPS_INS_LFV       = 262
MIPS_INS_LTV       = 263
MIPS_INS_SBV       = 264
MIPS_INS_SSV       = 265
MIPS_INS_SLV       = 266
MIPS_INS_SDV       = 267
MIPS_INS_SQV       = 268
MIPS_INS_SRV       = 269
MIPS_INS_SPV       = 270
MIPS_INS_SUV       = 271
MIPS_INS_SHV       = 272
MIPS_INS_SFV       = 273
MIPS_INS_SWV       = 274
MIPS_INS_STV       = 275
MIPS_INS_MFC2      = 276
MIPS_INS_MTC2      = 277
MIPS_INS_CFC2      = 278
MIPS_INS_CTC2      = 279

# Pseudo-Instruction Unique IDs
MIPS_INS_BEQZ = 280
MIPS_INS_BNEZ = 281
MIPS_INS_B    = 282
MIPS_INS_NOP  = 283
MIPS_INS_MOVE = 284
MIPS_INS_NEGU = 285
MIPS_INS_NOT  = 286

# Invalid Instruction Unique ID
MIPS_INS_INVALID = -1

# Op IDs
# MIPS_OP_RS  = 0
# MIPS_OP_RT  = 0
# MIPS_OP_RD  = 0
# MIPS_OP_IMM = 0

# Instruction Groups

MIPS_BRANCH_LIKELY_INSNS = [
    MIPS_INS_BEQL, MIPS_INS_BGEZALL,
    MIPS_INS_BGEZL, MIPS_INS_BGTZL,
    MIPS_INS_BLEZL, MIPS_INS_BLTZALL,
    MIPS_INS_BLTZL, MIPS_INS_BNEL,
    MIPS_INS_BC1TL, MIPS_INS_BC1FL,
]

MIPS_BRANCH_INSNS = [
    *MIPS_BRANCH_LIKELY_INSNS,

    MIPS_INS_BEQ,
    MIPS_INS_BGEZ, MIPS_INS_BGEZAL,
    MIPS_INS_BGTZ,
    MIPS_INS_BNE,
    MIPS_INS_BLTZ, MIPS_INS_BLTZAL,
    MIPS_INS_BLEZ,
    MIPS_INS_BC1T, MIPS_INS_BC1F,

    MIPS_INS_BEQZ,
    MIPS_INS_BNEZ,
    MIPS_INS_B,
]

MIPS_JUMP_INSNS = [
    MIPS_INS_JAL, MIPS_INS_JALR, MIPS_INS_J, MIPS_INS_JR
]

MIPS_DELAY_SLOT_INSNS = [
    *MIPS_BRANCH_INSNS, *MIPS_JUMP_INSNS
]

MIPS_FP_LOAD_INSNS = [
    MIPS_INS_LWC1, MIPS_INS_LDC1
]

MIPS_LOAD_INSNS = [
    MIPS_INS_LB, MIPS_INS_LBU, 
    MIPS_INS_LH, MIPS_INS_LHU, 
    MIPS_INS_LW, MIPS_INS_LWL, MIPS_INS_LWR, MIPS_INS_LWU, 
    MIPS_INS_LD, MIPS_INS_LDL, MIPS_INS_LDR, 
    MIPS_INS_LL, MIPS_INS_LLD,
    *MIPS_FP_LOAD_INSNS 
]

MIPS_FP_STORE_INSNS = [
    MIPS_INS_SWC1, MIPS_INS_SDC1
]

MIPS_STORE_INSNS = [
    MIPS_INS_SB, 
    MIPS_INS_SH, 
    MIPS_INS_SW, MIPS_INS_SWL, MIPS_INS_SWR,     
    MIPS_INS_SD, MIPS_INS_SDL, MIPS_INS_SDR, 
    MIPS_INS_SC, MIPS_INS_SCD,
    *MIPS_FP_STORE_INSNS
]

MIPS_LOAD_STORE_INSNS = [
    *MIPS_LOAD_INSNS,
    *MIPS_STORE_INSNS,
]

MIPS_FP_LOAD_STORE_INSNS = [
    *MIPS_FP_LOAD_INSNS, *MIPS_FP_STORE_INSNS
]

RSP_VECTOR_LOAD_STORES = [
    MIPS_INS_LBV, MIPS_INS_LSV, MIPS_INS_LLV, MIPS_INS_LDV,
    MIPS_INS_LQV, MIPS_INS_LRV, MIPS_INS_LPV, MIPS_INS_LUV,
    MIPS_INS_LHV, MIPS_INS_LFV, MIPS_INS_LTV,

    MIPS_INS_SBV, MIPS_INS_SSV, MIPS_INS_SLV, MIPS_INS_SDV,
    MIPS_INS_SQV, MIPS_INS_SRV, MIPS_INS_SPV, MIPS_INS_SUV,
    MIPS_INS_SHV, MIPS_INS_SFV, MIPS_INS_SWV, MIPS_INS_STV,
]

# Labels

# These labels can be referenced from pointers/loads/stores/etc.
LABEL_TYPE_FUNC = 0
LABEL_TYPE_JTBL = 1
LABEL_TYPE_DATA = 2
LABEL_TYPE_BRANCH = 3

# Unknown
LABEL_TYPE_UNK = 20

class MipsLabel:
    """
    Label
    """

    def __init__(self, vaddr, name=None, lbl_type=LABEL_TYPE_UNK, is_global=None) -> None:
        self.name = name
        self.vaddr = vaddr
        self.lbl_type = lbl_type
        self.is_global = is_global or (False if (lbl_type == LABEL_TYPE_BRANCH) else True)

    def __str__(self):
        if self.name is not None:
            return self.name

        if self.lbl_type == LABEL_TYPE_FUNC:
            return f"func_{self.vaddr:08X}"
        elif self.lbl_type == LABEL_TYPE_JTBL:
            return f"jtbl_{self.vaddr:08X}"
        elif self.lbl_type == LABEL_TYPE_BRANCH:
            return f".L{self.vaddr:08X}"
        elif (self.lbl_type == LABEL_TYPE_DATA or self.lbl_type == LABEL_TYPE_UNK):
            return f"D_{self.vaddr:08X}"
        assert False , f"Unimplemented default name for label type {self.lbl_type}"

# Register Names

mips_gpr_names = (
    "$zero",
    "$at",
    "$v0", "$v1",
    "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9",
    "$k0", "$k1",
    "$gp",
    "$sp",
    "$fp",
    "$ra",
)

rsp_gpr_names = (
    "$zero",
     "$1",  "$2",  "$3",  "$4",  "$5",  "$6",
     "$7",  "$8",  "$9", "$10", "$11", "$12",
    "$13", "$14", "$15", "$16", "$17", "$18",
    "$19", "$20", "$21", "$22", "$23", "$24",
    "$25", "$26", "$27", "$28", "$29", "$30",
    "$ra",
)

mips_cop0_names = (
    "Index"     , "Random"    , "EntryLo0"  , "EntryLo1"  ,
    "Context"   , "PageMask"  , "Wired"     , "Reserved07",
    "BadVaddr"  , "Count"     , "EntryHi"   , "Compare"   ,
    "Status"    , "Cause"     , "EPC"       , "PRevID"    ,
    "Config"    , "LLAddr"    , "WatchLo"   , "WatchHi"   ,
    "XContext"  , "Reserved21", "Reserved22", "Reserved23",
    "Reserved24", "Reserved25", "PErr"      , "CacheErr"  ,
    "TagLo"     , "TagHi"     , "ErrorEPC"  , "Reserved31",
)

rsp_cop0_names = (
    "SP_MEM_ADDR", "SP_DRAM_ADDR", "SP_RD_LEN"   , "SP_WR_LEN"   , 
    "SP_STATUS"  , "SP_DMA_FULL" , "SP_DMA_BUSY" , "SP_SEMAPHORE", 
    "DPC_START"  , "DPC_END"     , "DPC_CURRENT" , "DPC_STATUS"  , 
    "DPC_CLOCK"  , "DPC_BUFBUSY" , "DPC_PIPEBUSY", "DPC_TMEM"    ,
)

mips_cop1_names = (
    "$f0", "$f1", "$f2", "$f3",
    "$f4", "$f5", "$f6", "$f7", "$f8", "$f9", "$f10", "$f11",
    "$f12", "$f13", "$f14", "$f15",
    "$f16", "$f17", "$f18", "$f19",
    "$f20", "$f21", "$f22", "$f23", "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30",
    # Status register
    "FpCsr",
)

rsp_cop2_names = (
     "$v0",  "$v1",  "$v2",  "$v3",  "$v4",  "$v5",  "$v6",  "$v7",
     "$v8",  "$v9", "$v10", "$v11", "$v12", "$v13", "$v14", "$v15",
    "$v16", "$v17", "$v18", "$v19", "$v20", "$v21", "$v22", "$v23",
    "$v24", "$v25", "$v26", "$v27", "$v28", "$v29", "$v30", "$v31",
)

rsp_cop2_ctrl_names = (
    '$vco', '$vcc', '$vce'
)

# Instruction sets

class MipsAbi:
    def __init__(self, name, gpr_names, cop0_names, cop1_names, cop2_names):
        self.name = name
        self.gpr_names, self.cop0_names, self.cop1_names, self.cop2_names = \
            gpr_names, cop0_names, cop1_names, cop2_names

ABI_VR4300 = MipsAbi("VR4300", mips_gpr_names, mips_cop0_names, mips_cop1_names, None          )
ABI_RSP    = MipsAbi("RSP",    rsp_gpr_names,  rsp_cop0_names,  None,            rsp_cop2_names)

# Instruction field fetching

def sign_extend_6(value):
    if value & (1 << (6 - 1)):
        return value - (1 << 6)
    return value

def sign_extend_16(value):
    return (value & 0x7FFF) - (value & 0x8000)

def mask_shift(v, s, w):
    return (v >> s) & ((1 << w) - 1)

mips_get_field     = lambda raw,vaddr : mask_shift(raw, 26,  6)
mips_get_special   = lambda raw,vaddr : mask_shift(raw,  0,  6)
mips_get_cop0      = lambda raw,vaddr : mask_shift(raw, 21,  5)
mips_get_cop1      = lambda raw,vaddr : mask_shift(raw, 21,  5)
mips_get_cop2      = lambda raw,vaddr : mask_shift(raw, 21,  4)
mips_get_regimm    = lambda raw,vaddr : mask_shift(raw, 16,  5)
mips_get_tlb       = lambda raw,vaddr : mask_shift(raw,  0,  5)
mips_get_function  = lambda raw,vaddr : mask_shift(raw,  0,  6)

mips_get_cond      = lambda raw,vaddr : mask_shift(raw,  0,  4)
mips_get_fd        = lambda raw,vaddr : MipsFPReg(mask_shift(raw,  6,  5))
mips_get_fs        = lambda raw,vaddr : MipsFPReg(mask_shift(raw, 11,  5))
mips_get_ft        = lambda raw,vaddr : MipsFPReg(mask_shift(raw, 16,  5))
mips_get_fmt       = lambda raw,vaddr : mask_shift(raw, 21,  5)
mips_get_ndtf      = lambda raw,vaddr : mask_shift(raw, 16,  2)

mips_get_target    = lambda raw,vaddr : ((vaddr & 0xFC000000) | (mask_shift(raw, 0, 26) << 2))
mips_get_offset    = lambda raw,vaddr : vaddr + 4 + sign_extend_16(mask_shift(raw, 0, 16)) * 4
mips_get_imm       = lambda raw,vaddr : mask_shift(raw,  0, 16)

mips_get_base      = lambda raw,vaddr : MipsGPReg(mask_shift(raw, 21,  5))

mips_get_cd        = lambda raw,vaddr : mask_shift(raw, 11,  5)

mips_get_code      = lambda raw,vaddr : (mask_shift(raw,  6, 20) << 6) >> 16
mips_get_op        = lambda raw,vaddr : mask_shift(raw, 16,  5)

mips_get_sa        = lambda raw,vaddr : mask_shift(raw,  6,  5)

mips_get_rd        = lambda raw,vaddr : MipsGPReg(mask_shift(raw, 11,  5))
mips_get_rs        = lambda raw,vaddr : MipsGPReg(mask_shift(raw, 21,  5))
mips_get_rt        = lambda raw,vaddr : MipsGPReg(mask_shift(raw, 16,  5))

rsp_load_store_multiplier = {
    0b00000 : 0x01, # lbv, sbv
    0b00001 : 0x02, # lsv, ssv
    0b00010 : 0x04, # llv, slv
    0b00011 : 0x08, # ldv, sdv
    0b00100 : 0x10, # lqv, sqv
    0b00101 : 0x10, # lrv, srv
    0b00110 : 0x08, # lpv, spv
    0b00111 : 0x08, # luv, suv

    0b01000 : 0x02, # lhv, shv
    0b01001 : 0x04, # lfv, sfv
    0b01010 : 0x10, # swv
    0b01011 : 0x10, # ltv, stv
}

mips_get_vc        = lambda raw,vaddr : mask_shift(raw, 11,  5)
mips_get_vd        = lambda raw,vaddr : mask_shift(raw, 6,   5)
mips_get_vs        = lambda raw,vaddr : mask_shift(raw, 11,  5)
mips_get_vt        = lambda raw,vaddr : mask_shift(raw, 16,  5)
mips_get_elem      = lambda raw,vaddr : mask_shift(raw, 21,  4)
mips_get_elemd     = lambda raw,vaddr : mask_shift(raw, 7,   4)
mips_get_cop2_func = lambda raw,vaddr : mask_shift(raw, 25,  1)
mips_get_lwc2      = lambda raw,vaddr : mask_shift(raw, 11,  5)
mips_get_swc2      = lambda raw,vaddr : mask_shift(raw, 11,  5)
mips_get_voffset   = lambda raw,vaddr : sign_extend_6(mask_shift(raw, 0, 6)) * rsp_load_store_multiplier[mips_get_lwc2(raw,vaddr)]

# Formatting

def resolve_pseudo_insn(insn):
    # move varies between assemblers
    # IDO
    move_insn = MIPS_INS_OR
    # GCC
    # move_insn = MIPS_INS_ADDU

    if insn.id == MIPS_INS_SLL and insn.rd == MipsGPReg.R0 and insn.rt == MipsGPReg.R0 and insn.sa == 0:
        return MIPS_INS_NOP, "nop", (), ()
    elif insn.id == MIPS_INS_BEQ and insn.rs == MipsGPReg.R0 and insn.rt == MipsGPReg.R0:
        return MIPS_INS_B, "b", ("offset",), (False,)
    elif insn.id == move_insn and insn.rt == MipsGPReg.R0:
        return MIPS_INS_MOVE, "move", ("rd","rs"), (True,False)
    elif insn.id == MIPS_INS_BEQ and insn.rt == MipsGPReg.R0:
        return MIPS_INS_BEQZ, "beqz", ("rs","offset"), (False,False)
    elif insn.id == MIPS_INS_BNE and insn.rt == MipsGPReg.R0:
        return MIPS_INS_BNEZ, "bnez", ("rs","offset"), (False,False)
    elif insn.id == MIPS_INS_SUBU and insn.rs == MipsGPReg.R0:
        return MIPS_INS_NEGU, "negu", ("rd","rt"), (True,False)
    elif insn.id == MIPS_INS_NOR and insn.rt == MipsGPReg.R0:
        return MIPS_INS_NOT, "not", ("rd","rs"), (True,False)
    else:
        return insn.id, insn.mnemonic, insn.fields, insn.writes

def format_hex(v, signed, zeros, no_zero):
    if abs(v) < 10:
        if v == 0 and no_zero:
            return ""
        return f"{v}"
    elif not signed:
        return f"0x{v:{f'0{zeros}' if zeros > 0 else ''}x}"
    else:
        return f"{v:#x}"

def format_vector_elem(insn, elem):
    if insn.id in RSP_VECTOR_LOAD_STORES:
        return f"[{elem}]"
    elif (elem & 8) == 8:
        return f"[{elem & 7}]"
    elif (elem & 0xC) == 4:
        return f"[{elem & 3}h]"
    elif (elem & 0xE) == 2:
        return f"[{elem & 1}q]"
    else:
        return ""

mips_field_formatters = {
    'code'          : (lambda insn : f'{insn.code}' if insn.code != 0 else ''),
    'cd'            : (lambda insn : insn.abi.cop0_names[insn.cd]),
    'rd'            : (lambda insn : insn.abi.gpr_names[insn.rd]),
    'rs'            : (lambda insn : insn.abi.gpr_names[insn.rs]),
    'rt'            : (lambda insn : insn.abi.gpr_names[insn.rt]),
    'fd'            : (lambda insn : insn.abi.cop1_names[insn.fd]),
    'fs'            : (lambda insn : insn.abi.cop1_names[insn.fs]),
    'ft'            : (lambda insn : insn.abi.cop1_names[insn.ft]),
    'sa'            : (lambda insn : format_hex(insn.sa, True, 0, False)),
    'op'            : (lambda insn : format_hex(insn.op, False, 0, False)),
    'imm'           : (lambda insn : format_hex(insn.imm, True, 0, False)),
    'offset(base)'  : (lambda insn : f'{format_hex(insn.imm, True, 0, True)}({insn.abi.gpr_names[insn.base]})'),
    'offset'        : (lambda insn : f'{format_hex(insn.offset, True, 0, False)}'),
    'target'        : (lambda insn : f'{format_hex(insn.target, False, 0, False)}'),
    'vd'            : (lambda insn : insn.abi.cop2_names[insn.vd]),
    'vs'            : (lambda insn : insn.abi.cop2_names[insn.vs]),
    'vt'            : (lambda insn : insn.abi.cop2_names[insn.vt]),
    'vt[e]'         : (lambda insn : f"{insn.abi.cop2_names[insn.vt]}{format_vector_elem(insn, insn.elem)}"),
    'vt[ed]'        : (lambda insn : f"{insn.abi.cop2_names[insn.vt]}{format_vector_elem(insn, insn.elemd)}"),
    'vd[e]'         : (lambda insn : f"{insn.abi.cop2_names[insn.vd]}{format_vector_elem(insn, insn.elem)}"),
    'vd[ed]'        : (lambda insn : f"{insn.abi.cop2_names[insn.vd]}{format_vector_elem(insn, insn.elemd)}"),
    'voffset'       : (lambda insn : f'{format_hex(insn.voffset, True, 0, False)}'),
    'voffset(base)' : (lambda insn : f'{format_hex(insn.voffset, True, 0, True)}({insn.abi.gpr_names[insn.base]})'),
    'vc'            : (lambda insn : rsp_cop2_ctrl_names[insn.vc])
}

class MipsInsn:

    def __init__(self, abi, raw, vaddr, values):
        self.abi = abi
        self.raw = raw
        self.vaddr = vaddr

        if values is None:
            values = MIPS_INS_INVALID, f"/* Invalid Instruction */ .4byte 0x{raw:08X}", (), ()

        self.id, self.mnemonic, self.fields, self.writes = values

        # self.code = self.sa = self.op = self.cd = self.rd = self.rs = self.rt = self.fd = self.fs = self.ft = self.imm = self.offset = self.base = self.target = None

        for field in self.fields:
            self.set_value(field)

        self.id, self.mnemonic, self.fields, self.writes = resolve_pseudo_insn(self)

        self.op_str = self.format_insn()

    def read_fields(self):
        return [field for i,field in enumerate(self.fields) if self.writes[i] == False]

    def write_fields(self):
        return [field for i,field in enumerate(self.fields) if self.writes[i] == True]

    def has_field(self, field):
        return field in self.fields

    def format_field(self, field):
        return mips_field_formatters[field](self)

    def format_insn(self):
        return ", ".join([self.format_field(field) for field in self.fields])

    def __str__(self):
        return f"{self.mnemonic:12}{self.op_str}"

    # Field setters

    def set_code(self):
        self.code = mips_get_code(self.raw, self.vaddr)

    def set_sa(self):
        self.sa = mips_get_sa(self.raw, self.vaddr)

    def set_op(self):
        self.op = mips_get_op(self.raw, self.vaddr)

    def set_cd(self):
        self.cd = mips_get_cd(self.raw, self.vaddr)

    def set_rd(self):
        self.rd = mips_get_rd(self.raw, self.vaddr)

    def set_rs(self):
        self.rs = mips_get_rs(self.raw, self.vaddr)

    def set_rt(self):
        self.rt = mips_get_rt(self.raw, self.vaddr)

    def set_fd(self):
        self.fd = mips_get_fd(self.raw, self.vaddr)

    def set_fs(self):
        self.fs = mips_get_fs(self.raw, self.vaddr)

    def set_ft(self):
        self.ft = mips_get_ft(self.raw, self.vaddr)

    do_sign_extend = [
        MIPS_INS_ADDIU, MIPS_INS_SLTI, MIPS_INS_ADDI, MIPS_INS_DADDIU, 
        MIPS_INS_LB, MIPS_INS_LBU, 
        MIPS_INS_LH, MIPS_INS_LHU, 
        MIPS_INS_LW, MIPS_INS_LWL, MIPS_INS_LWR, MIPS_INS_LWU, 
        MIPS_INS_LWC1, 
        MIPS_INS_LD, MIPS_INS_LDL, MIPS_INS_LDR, 
        MIPS_INS_LDC1, 
        MIPS_INS_LL, MIPS_INS_LLD, 
        MIPS_INS_SB, 
        MIPS_INS_SH, 
        MIPS_INS_SW, MIPS_INS_SWL, MIPS_INS_SWR, 
        MIPS_INS_SWC1, 
        MIPS_INS_SD, MIPS_INS_SDL, MIPS_INS_SDR, 
        MIPS_INS_SDC1, 
        MIPS_INS_SC, MIPS_INS_SCD,
    ]

    def set_imm(self):
        self.imm = mips_get_imm(self.raw, self.vaddr)
        if self.id in MipsInsn.do_sign_extend: # sign extended immediates
            self.imm = sign_extend_16(self.imm)

    def set_offset(self):
        self.offset = mips_get_offset(self.raw, self.vaddr)

    def set_base(self):
        self.base = mips_get_base(self.raw, self.vaddr)

    def set_offset_base(self):
        self.set_imm()
        self.set_base()

    def set_target(self):
        self.target = mips_get_target(self.raw, self.vaddr)

    def set_vd(self):
        self.vd = mips_get_vd(self.raw, self.vaddr)

    def set_vs(self):
        self.vs = mips_get_vs(self.raw, self.vaddr)

    def set_vt(self):
        self.vt = mips_get_vt(self.raw, self.vaddr)

    def set_e(self):
        self.elem = mips_get_elem(self.raw, self.vaddr)
    
    def set_ed(self):
        self.elemd = mips_get_elemd(self.raw, self.vaddr)

    def set_vd_e(self):
        self.set_vd()
        self.set_e()

    def set_vt_ed(self):
        self.set_vt()
        self.set_ed()

    def set_vt_e(self):
        self.set_vt()
        self.set_e()

    def set_vd_ed(self):
        self.set_vd()
        self.set_ed()

    def set_voffset(self):
        self.voffset = mips_get_voffset(self.raw, self.vaddr)

    def set_voffset_base(self):
        self.set_voffset()
        self.set_base()

    def set_vc(self):
        self.vc = mips_get_vc(self.raw, self.vaddr)

    field_setters = {
        'code'          : set_code,
        'sa'            : set_sa,
        'op'            : set_op,
        'cd'            : set_cd,
        'rd'            : set_rd,
        'rs'            : set_rs,
        'rt'            : set_rt,
        'fd'            : set_fd,
        'fs'            : set_fs,
        'ft'            : set_ft,
        'imm'           : set_imm,
        'offset'        : set_offset,
        'base'          : set_base,
        'offset(base)'  : set_offset_base,
        'target'        : set_target,
        'vd'            : set_vd,
        'vs'            : set_vs,
        'vt'            : set_vt,
        'vt[e]'         : set_vt_e,
        'vt[ed]'        : set_vt_ed,
        'vd[e]'         : set_vd_e,
        'vd[ed]'        : set_vd_ed,
        'voffset'       : set_voffset,
        'voffset(base)' : set_voffset_base,
        'vc'            : set_vc
    }

    def set_value(self, name):
        MipsInsn.field_setters[name](self)

    # Field getters

    field_getters = {
        'code'          : (lambda insn: insn.code),
        'sa'            : (lambda insn: insn.sa),
        'op'            : (lambda insn: insn.op),
        'cd'            : (lambda insn: insn.cd),
        'rd'            : (lambda insn: insn.rd),
        'rs'            : (lambda insn: insn.rs),
        'rt'            : (lambda insn: insn.rt),
        'fd'            : (lambda insn: insn.fd),
        'fs'            : (lambda insn: insn.fs),
        'ft'            : (lambda insn: insn.ft),
        'imm'           : (lambda insn: insn.imm),
        'offset'        : (lambda insn: insn.offset),
        'base'          : (lambda insn: insn.base),
        'offset(base)'  : (lambda insn: (insn.offset, insn.base)),
        'target'        : (lambda insn: insn.target),
        'vd'            : (lambda insn: insn.vd),
        'vs'            : (lambda insn: insn.vs),
        'vt'            : (lambda insn: insn.vt),
        'vt[e]'         : (lambda insn: (insn.vt, insn.elem)),
        'vt[ed]'        : (lambda insn: (insn.vt, insn.elemd)),
        'vd[e]'         : (lambda insn: (insn.vd, insn.elem)),
        'vd[ed]'        : (lambda insn: (insn.vd, insn.elemd)),
        'voffset'       : (lambda insn: insn.voffset),
        'voffset(base)' : (lambda insn: (insn.voffset, insn.base)),
        'vc'            : (lambda insn: insn.vc),
    }

    def value_forname(self, name):
        return MipsInsn.field_getters[name](self)

def fetch_insn(raw, vaddr, insn_set, func):
    insn = insn_set.get(func(raw, vaddr), None) # default none for invalid instruction encoding

    if insn is not None and type(insn[1]) == dict: # extra decoding required
        insn = fetch_insn(raw, vaddr, insn[1], insn[0])
    return insn

def decode_insn(raw, vaddr):
    return MipsInsn(ABI_VR4300, raw, vaddr, fetch_insn(raw, vaddr, mips_insns, mips_get_field))

def decode_rsp_insn(raw, vaddr):
    return MipsInsn(ABI_RSP, raw, vaddr, fetch_insn(raw, vaddr, rsp_insns, mips_get_field))

mips_insns = {
    0b000000: (mips_get_special, {
        # opcode   id                 mnemonic   fields            field is written to
        0b000000: (MIPS_INS_SLL,     "sll",     ("rd","rt","sa"), (True , False, False)),
        0b000010: (MIPS_INS_SRL,     "srl",     ("rd","rt","sa"), (True , False, False)),
        0b000011: (MIPS_INS_SRA,     "sra",     ("rd","rt","sa"), (True , False, False)),
        0b000100: (MIPS_INS_SLLV,    "sllv",    ("rd","rt","rs"), (True , False, False)),
        0b000110: (MIPS_INS_SRLV,    "srlv",    ("rd","rt","rs"), (True , False, False)),
        0b000111: (MIPS_INS_SRAV,    "srav",    ("rd","rt","rs"), (True , False, False)),
        0b001000: (MIPS_INS_JR,      "jr",      ("rs",         ), (False,             )),
        0b001001: (MIPS_INS_JALR,    "jalr",    ("rs",         ), (False,             )), # technically also rd but it's always $ra
        0b001100: (MIPS_INS_SYSCALL, "syscall", (              ), (                   )),
        0b001101: (MIPS_INS_BREAK,   "break",   ("code",       ), (False,             )),
        0b001111: (MIPS_INS_SYNC,    "sync",    (              ), (                   )),
        0b010000: (MIPS_INS_MFHI,    "mfhi",    ("rd",         ), (True ,             )),
        0b010001: (MIPS_INS_MTHI,    "mthi",    ("rs",         ), (False,             )),
        0b010010: (MIPS_INS_MFLO,    "mflo",    ("rd",         ), (True ,             )),
        0b010011: (MIPS_INS_MTLO,    "mtlo",    ("rs",         ), (False,             )),
        0b010100: (MIPS_INS_DSLLV,   "dsllv",   ("rd","rt","rs"), (True , False, False)),
        0b010110: (MIPS_INS_DSRLV,   "dsrlv",   ("rd","rt","rs"), (True , False, False)),
        0b010111: (MIPS_INS_DSRAV,   "dsrav",   ("rd","rt","rs"), (True , False, False)),
        0b011000: (MIPS_INS_MULT,    "mult",    ("rs","rt"     ), (False, False       )),
        0b011001: (MIPS_INS_MULTU,   "multu",   ("rs","rt"     ), (False, False       )),
        0b011010: (MIPS_INS_DIV,     "div",     ("rd","rs","rt"), (False, False, False)), # for some reason gas hates div instructions 
        0b011011: (MIPS_INS_DIVU,    "divu",    ("rd","rs","rt"), (False, False, False)), #    with the correct number of operands
        0b011100: (MIPS_INS_DMULT,   "dmult",   ("rs","rt"     ), (False, False       )),
        0b011101: (MIPS_INS_DMULTU,  "dmultu",  ("rs","rt"     ), (False, False       )),
        0b011110: (MIPS_INS_DDIV,    "ddiv",    ("rd","rs","rt"), (False, False, False)),
        0b011111: (MIPS_INS_DDIVU,   "ddivu",   ("rd","rs","rt"), (False, False, False)),
        0b100000: (MIPS_INS_ADD,     "add",     ("rd","rs","rt"), (True , False, False)),
        0b100001: (MIPS_INS_ADDU,    "addu",    ("rd","rs","rt"), (True , False, False)),
        0b100010: (MIPS_INS_SUB,     "sub",     ("rd","rs","rt"), (True , False, False)),
        0b100011: (MIPS_INS_SUBU,    "subu",    ("rd","rs","rt"), (True , False, False)),
        0b100100: (MIPS_INS_AND,     "and",     ("rd","rs","rt"), (True , False, False)),
        0b100101: (MIPS_INS_OR,      "or",      ("rd","rs","rt"), (True , False, False)),
        0b100110: (MIPS_INS_XOR,     "xor",     ("rd","rs","rt"), (True , False, False)),
        0b100111: (MIPS_INS_NOR,     "nor",     ("rd","rs","rt"), (True , False, False)),
        0b101010: (MIPS_INS_SLT,     "slt",     ("rd","rs","rt"), (True , False, False)),
        0b101011: (MIPS_INS_SLTU,    "sltu",    ("rd","rs","rt"), (True , False, False)),
        0b101100: (MIPS_INS_DADD,    "dadd",    ("rd","rs","rt"), (True , False, False)),
        0b101101: (MIPS_INS_DADDU,   "daddu",   ("rd","rs","rt"), (True , False, False)),
        0b101110: (MIPS_INS_DSUB,    "dsub",    ("rd","rs","rt"), (True , False, False)),
        0b101111: (MIPS_INS_DSUBU,   "dsubu",   ("rd","rs","rt"), (True , False, False)),
        0b110000: (MIPS_INS_TGE,     "tge",     ("rs","rt"     ), (False, False       )),
        0b110001: (MIPS_INS_TGEU,    "tgeu",    ("rs","rt"     ), (False, False       )),
        0b110010: (MIPS_INS_TLT,     "tlt",     ("rs","rt"     ), (False, False       )),
        0b110011: (MIPS_INS_TLTU,    "tltu",    ("rs","rt"     ), (False, False       )),
        0b110100: (MIPS_INS_TEQ,     "teq",     ("rs","rt"     ), (False, False       )),
        0b110110: (MIPS_INS_TNE,     "tne",     ("rs","rt"     ), (False, False       )),
        0b111000: (MIPS_INS_DSLL,    "dsll",    ("rd","rt","sa"), (True , False, False)),
        0b111010: (MIPS_INS_DSRL,    "dsrl",    ("rd","rt","sa"), (True , False, False)),
        0b111011: (MIPS_INS_DSRA,    "dsra",    ("rd","rt","sa"), (True , False, False)),
        0b111100: (MIPS_INS_DSLL32,  "dsll32",  ("rd","rt","sa"), (True , False, False)),
        0b111110: (MIPS_INS_DSRL32,  "dsrl32",  ("rd","rt","sa"), (True , False, False)),
        0b111111: (MIPS_INS_DSRA32,  "dsra32",  ("rd","rt","sa"), (True , False, False)),
    }),
    0b000001: (mips_get_regimm, {
        0b00000: (MIPS_INS_BLTZ,    "bltz",    ("rs","offset"), (False, False)),
        0b00001: (MIPS_INS_BGEZ,    "bgez",    ("rs","offset"), (False, False)),
        0b00010: (MIPS_INS_BLTZL,   "bltzl",   ("rs","offset"), (False, False)),
        0b00011: (MIPS_INS_BGEZL,   "bgezl",   ("rs","offset"), (False, False)),
        0b01000: (MIPS_INS_TGEI,    "tgei",    ("rs","imm"   ), (False, False)),
        0b01001: (MIPS_INS_TGEIU,   "tgeiu",   ("rs","imm"   ), (False, False)),
        0b01010: (MIPS_INS_TLTI,    "tlti",    ("rs","imm"   ), (False, False)),
        0b01011: (MIPS_INS_TLTIU,   "tltiu",   ("rs","imm"   ), (False, False)),
        0b01100: (MIPS_INS_TEQI,    "teqi",    ("rs","imm"   ), (False, False)),
        0b01110: (MIPS_INS_TNEI,    "tnei",    ("rs","imm"   ), (False, False)),
        0b10000: (MIPS_INS_BLTZAL,  "bltzal",  ("rs","offset"), (False, False)),
        0b10001: (MIPS_INS_BGEZAL,  "bgezal",  ("rs","offset"), (False, False)),
        0b10010: (MIPS_INS_BLTZALL, "bltzall", ("rs","offset"), (False, False)),
        0b10011: (MIPS_INS_BGEZALL, "bgezall", ("rs","offset"), (False, False)),
    }),
    0b000010: (MIPS_INS_J,     "j",     ("target",         ), (False,             )),
    0b000011: (MIPS_INS_JAL,   "jal",   ("target",         ), (False,             )),
    0b000100: (MIPS_INS_BEQ,   "beq",   ("rs","rt","offset"), (False, False, False)),
    0b000101: (MIPS_INS_BNE,   "bne",   ("rs","rt","offset"), (False, False, False)),
    0b000110: (MIPS_INS_BLEZ,  "blez",  ("rs","offset"     ), (False, False,      )),
    0b000111: (MIPS_INS_BGTZ,  "bgtz",  ("rs","offset"     ), (False, False,      )),
    0b001000: (MIPS_INS_ADDI,  "addi",  ("rt","rs","imm"   ), (True , False, False)),
    0b001001: (MIPS_INS_ADDIU, "addiu", ("rt","rs","imm"   ), (True , False, False)),
    0b001010: (MIPS_INS_SLTI,  "slti",  ("rt","rs","imm"   ), (True , False, False)),
    0b001011: (MIPS_INS_SLTIU, "sltiu", ("rt","rs","imm"   ), (True , False, False)),
    0b001100: (MIPS_INS_ANDI,  "andi",  ("rt","rs","imm"   ), (True , False, False)),
    0b001101: (MIPS_INS_ORI,   "ori",   ("rt","rs","imm"   ), (True , False, False)),
    0b001110: (MIPS_INS_XORI,  "xori",  ("rt","rs","imm"   ), (True , False, False)),
    0b001111: (MIPS_INS_LUI,   "lui",   ("rt","imm"        ), (True , False       )),
    0b010000: (mips_get_cop0, {
        0b00000: (MIPS_INS_MFC0, "mfc0", ("rt","cd"), (True , False)),
        0b00100: (MIPS_INS_MTC0, "mtc0", ("rt","cd"), (False, True )),
        0b10000: (mips_get_tlb, {
            0b000001: (MIPS_INS_TLBR,  "tlbr",  (), ()),
            0b000010: (MIPS_INS_TLBWI, "tlbwi", (), ()),
            0b000110: (MIPS_INS_TLBWR, "tlbwr", (), ()),
            0b001000: (MIPS_INS_TLBP,  "tlbp",  (), ()),
            0b011000: (MIPS_INS_ERET,  "eret",  (), ()),
        }),
    }),
    0b010001: (mips_get_cop1, {
        0b00000: (MIPS_INS_MFC1,  "mfc1",  ("rt","fs"), (True , False)),
        0b00001: (MIPS_INS_DMFC1, "dmfc1", ("rt","fs"), (True , False)),
        0b00010: (MIPS_INS_CFC1,  "cfc1",  ("rt","fs"), (True , False)),
        0b00100: (MIPS_INS_MTC1,  "mtc1",  ("rt","fs"), (False, True )),
        0b00101: (MIPS_INS_DMTC1, "dmtc1", ("rt","fs"), (False, True )),
        0b00110: (MIPS_INS_CTC1,  "ctc1",  ("rt","fs"), (False, True )),
        0b01000: (mips_get_ndtf, {
            0b00: (MIPS_INS_BC1F,  "bc1f",  ("offset",), (False,)),
            0b01: (MIPS_INS_BC1T,  "bc1t",  ("offset",), (False,)),
            0b10: (MIPS_INS_BC1FL, "bc1fl", ("offset",), (False,)),
            0b11: (MIPS_INS_BC1TL, "bc1tl", ("offset",), (False,)),
        }),
        0b010000: (mips_get_function, {
            0b000000: (MIPS_INS_ADD_S,     "add.s",     ("fd","fs","ft"), (True , False, False)),
            0b000001: (MIPS_INS_SUB_S,     "sub.s",     ("fd","fs","ft"), (True , False, False)),
            0b000010: (MIPS_INS_MUL_S,     "mul.s",     ("fd","fs","ft"), (True , False, False)),
            0b000011: (MIPS_INS_DIV_S,     "div.s",     ("fd","fs","ft"), (True , False, False)),
            0b000100: (MIPS_INS_SQRT_S,    "sqrt.s",    ("fd","fs"     ), (True , False       )),
            0b000101: (MIPS_INS_ABS_S,     "abs.s",     ("fd","fs"     ), (True , False       )),
            0b000110: (MIPS_INS_MOV_S,     "mov.s",     ("fd","fs"     ), (True , False       )),
            0b000111: (MIPS_INS_NEG_S,     "neg.s",     ("fd","fs"     ), (True , False       )),
            0b001000: (MIPS_INS_ROUND_L_S, "round.l.s", ("fd","fs"     ), (True , False       )),
            0b001001: (MIPS_INS_TRUNC_L_S, "trunc.l.s", ("fd","fs"     ), (True , False       )),
            0b001010: (MIPS_INS_CEIL_L_S,  "ceil.l.s",  ("fd","fs"     ), (True , False       )),
            0b001011: (MIPS_INS_FLOOR_L_S, "floor.l.s", ("fd","fs"     ), (True , False       )),
            0b001100: (MIPS_INS_ROUND_W_S, "round.w.s", ("fd","fs"     ), (True , False       )),
            0b001101: (MIPS_INS_TRUNC_W_S, "trunc.w.s", ("fd","fs"     ), (True , False       )),
            0b001110: (MIPS_INS_CEIL_W_S,  "ceil.w.s",  ("fd","fs"     ), (True , False       )),
            0b001111: (MIPS_INS_FLOOR_W_S, "floor.w.s", ("fd","fs"     ), (True , False       )),
            0b100001: (MIPS_INS_CVT_D_S,   "cvt.d.s",   ("fd","fs"     ), (True , False       )),
            0b100100: (MIPS_INS_CVT_W_S,   "cvt.w.s",   ("fd","fs"     ), (True , False       )),
            0b100101: (MIPS_INS_CVT_L_S,   "cvt.l.s",   ("fd","fs"     ), (True , False       )),
            0b110000: (MIPS_INS_C_F_S,     "c.f.s",     ("fs","ft"     ), (False, False       )),
            0b110001: (MIPS_INS_C_UN_S,    "c.un.s",    ("fs","ft"     ), (False, False       )),
            0b110010: (MIPS_INS_C_EQ_S,    "c.eq.s",    ("fs","ft"     ), (False, False       )),
            0b110011: (MIPS_INS_C_UEQ_S,   "c.ueq.s",   ("fs","ft"     ), (False, False       )),
            0b110100: (MIPS_INS_C_OLT_S,   "c.olt.s",   ("fs","ft"     ), (False, False       )),
            0b110101: (MIPS_INS_C_ULT_S,   "c.ult.s",   ("fs","ft"     ), (False, False       )),
            0b110110: (MIPS_INS_C_OLE_S,   "c.ole.s",   ("fs","ft"     ), (False, False       )),
            0b110111: (MIPS_INS_C_ULE_S,   "c.ule.s",   ("fs","ft"     ), (False, False       )),
            0b111000: (MIPS_INS_C_SF_S,    "c.sf.s",    ("fs","ft"     ), (False, False       )),
            0b111001: (MIPS_INS_C_NGLE_S,  "c.ngle.s",  ("fs","ft"     ), (False, False       )),
            0b111010: (MIPS_INS_C_SEQ_S,   "c.seq.s",   ("fs","ft"     ), (False, False       )),
            0b111011: (MIPS_INS_C_NGL_S,   "c.ngl.s",   ("fs","ft"     ), (False, False       )),
            0b111100: (MIPS_INS_C_LT_S,    "c.lt.s",    ("fs","ft"     ), (False, False       )),
            0b111101: (MIPS_INS_C_NGE_S,   "c.nge.s",   ("fs","ft"     ), (False, False       )),
            0b111110: (MIPS_INS_C_LE_S,    "c.le.s",    ("fs","ft"     ), (False, False       )),
            0b111111: (MIPS_INS_C_NGT_S,   "c.ngt.s",   ("fs","ft"     ), (False, False       )),
        }),
        0b010001: (mips_get_function, {
            0b000000: (MIPS_INS_ADD_D,     "add.d",     ("fd","fs","ft"), (True , False, False)),
            0b000001: (MIPS_INS_SUB_D,     "sub.d",     ("fd","fs","ft"), (True , False, False)),
            0b000010: (MIPS_INS_MUL_D,     "mul.d",     ("fd","fs","ft"), (True , False, False)),
            0b000011: (MIPS_INS_DIV_D,     "div.d",     ("fd","fs","ft"), (True , False, False)),
            0b000100: (MIPS_INS_SQRT_D,    "sqrt.d",    ("fd","fs"     ), (True , False       )),
            0b000101: (MIPS_INS_ABS_D,     "abs.d",     ("fd","fs"     ), (True , False       )),
            0b000110: (MIPS_INS_MOV_D,     "mov.d",     ("fd","fs"     ), (True , False       )),
            0b000111: (MIPS_INS_NEG_D,     "neg.d",     ("fd","fs"     ), (True , False       )),
            0b001000: (MIPS_INS_ROUND_L_D, "round.l.d", ("fd","fs"     ), (True , False       )),
            0b001001: (MIPS_INS_TRUNC_L_D, "trunc.l.d", ("fd","fs"     ), (True , False       )),
            0b001010: (MIPS_INS_CEIL_L_D,  "ceil.l.d",  ("fd","fs"     ), (True , False       )),
            0b001011: (MIPS_INS_FLOOR_L_D, "floor.l.d", ("fd","fs"     ), (True , False       )),
            0b001100: (MIPS_INS_ROUND_W_D, "round.w.d", ("fd","fs"     ), (True , False       )),
            0b001101: (MIPS_INS_TRUNC_W_D, "trunc.w.d", ("fd","fs"     ), (True , False       )),
            0b001110: (MIPS_INS_CEIL_W_D,  "ceil.w.d",  ("fd","fs"     ), (True , False       )),
            0b001111: (MIPS_INS_FLOOR_W_D, "floor.w.d", ("fd","fs"     ), (True , False       )),
            0b100000: (MIPS_INS_CVT_S_D,   "cvt.s.d",   ("fd","fs"     ), (True , False       )),
            0b100100: (MIPS_INS_CVT_W_D,   "cvt.w.d",   ("fd","fs"     ), (True , False       )),
            0b100101: (MIPS_INS_CVT_L_D,   "cvt.l.d",   ("fd","fs"     ), (True , False       )),
            0b110000: (MIPS_INS_C_F_D,     "c.f.d",     ("fs","ft"     ), (False, False       )),
            0b110001: (MIPS_INS_C_UN_D,    "c.un.d",    ("fs","ft"     ), (False, False       )),
            0b110010: (MIPS_INS_C_EQ_D,    "c.eq.d",    ("fs","ft"     ), (False, False       )),
            0b110011: (MIPS_INS_C_UEQ_D,   "c.ueq.d",   ("fs","ft"     ), (False, False       )),
            0b110100: (MIPS_INS_C_OLT_D,   "c.olt.d",   ("fs","ft"     ), (False, False       )),
            0b110101: (MIPS_INS_C_ULT_D,   "c.ult.d",   ("fs","ft"     ), (False, False       )),
            0b110110: (MIPS_INS_C_OLE_D,   "c.ole.d",   ("fs","ft"     ), (False, False       )),
            0b110111: (MIPS_INS_C_ULE_D,   "c.ule.d",   ("fs","ft"     ), (False, False       )),
            0b111000: (MIPS_INS_C_SF_D,    "c.sf.d",    ("fs","ft"     ), (False, False       )),
            0b111001: (MIPS_INS_C_NGLE_D,  "c.ngle.d",  ("fs","ft"     ), (False, False       )),
            0b111010: (MIPS_INS_C_SEQ_D,   "c.seq.d",   ("fs","ft"     ), (False, False       )),
            0b111011: (MIPS_INS_C_NGL_D,   "c.ngl.d",   ("fs","ft"     ), (False, False       )),
            0b111100: (MIPS_INS_C_LT_D,    "c.lt.d",    ("fs","ft"     ), (False, False       )),
            0b111101: (MIPS_INS_C_NGE_D,   "c.nge.d",   ("fs","ft"     ), (False, False       )),
            0b111110: (MIPS_INS_C_LE_D,    "c.le.d",    ("fs","ft"     ), (False, False       )),
            0b111111: (MIPS_INS_C_NGT_D,   "c.ngt.d",   ("fs","ft"     ), (False, False       )),
        }),
        0b010100: (mips_get_function, {
            0b100000: (MIPS_INS_CVT_S_W, "cvt.s.w", ("fd","fs"), (True , False)),
            0b100001: (MIPS_INS_CVT_D_W, "cvt.d.w", ("fd","fs"), (True , False)),
        }),
        0b010101: (mips_get_function, {
            0b100000: (MIPS_INS_CVT_S_L, "cvt.s.l", ("fd","fs"), (True , False)),
            0b100001: (MIPS_INS_CVT_D_L, "cvt.d.l", ("fd","fs"), (True , False)),
        }),
    }),
    0b010100: (MIPS_INS_BEQL,   "beql",   ("rs","rt","offset" ), (False, False, False)),
    0b010101: (MIPS_INS_BNEL,   "bnel",   ("rs","rt","offset" ), (False, False, False)),
    0b010110: (MIPS_INS_BLEZL,  "blezl",  ("rs","offset"      ), (False, False       )),
    0b010111: (MIPS_INS_BGTZL,  "bgtzl",  ("rs","offset"      ), (False, False       )),
    0b011000: (MIPS_INS_DADDI,  "daddi",  ("rt","rs","imm"    ), (True , False, False)),
    0b011001: (MIPS_INS_DADDIU, "daddiu", ("rt","rs","imm"    ), (True , False, False)),
    0b011010: (MIPS_INS_LDL,    "ldl",    ("rt","offset(base)"), (True , False       )),
    0b011011: (MIPS_INS_LDR,    "ldr",    ("rt","offset(base)"), (True , False       )),
    0b100000: (MIPS_INS_LB,     "lb",     ("rt","offset(base)"), (True , False       )),
    0b100001: (MIPS_INS_LH,     "lh",     ("rt","offset(base)"), (True , False       )),
    0b100010: (MIPS_INS_LWL,    "lwl",    ("rt","offset(base)"), (True , False       )),
    0b100011: (MIPS_INS_LW,     "lw",     ("rt","offset(base)"), (True , False       )),
    0b100100: (MIPS_INS_LBU,    "lbu",    ("rt","offset(base)"), (True , False       )),
    0b100101: (MIPS_INS_LHU,    "lhu",    ("rt","offset(base)"), (True , False       )),
    0b100110: (MIPS_INS_LWR,    "lwr",    ("rt","offset(base)"), (True , False       )),
    0b100111: (MIPS_INS_LWU,    "lwu",    ("rt","offset(base)"), (True , False       )),
    0b101000: (MIPS_INS_SB,     "sb",     ("rt","offset(base)"), (False, False       )),
    0b101001: (MIPS_INS_SH,     "sh",     ("rt","offset(base)"), (False, False       )),
    0b101010: (MIPS_INS_SWL,    "swl",    ("rt","offset(base)"), (False, False       )),
    0b101011: (MIPS_INS_SW,     "sw",     ("rt","offset(base)"), (False, False       )),
    0b101100: (MIPS_INS_SDL,    "sdl",    ("rt","offset(base)"), (False, False       )),
    0b101101: (MIPS_INS_SDR,    "sdr",    ("rt","offset(base)"), (False, False       )),
    0b101110: (MIPS_INS_SWR,    "swr",    ("rt","offset(base)"), (False, False       )),
    0b101111: (MIPS_INS_CACHE,  "cache",  ("op","offset(base)"), (False, False, False)),
    0b110000: (MIPS_INS_LL,     "ll",     ("rt","offset(base)"), (True , False       )),
    0b110001: (MIPS_INS_LWC1,   "lwc1",   ("ft","offset(base)"), (True , False       )),
    # lwc2
    0b110100: (MIPS_INS_LLD,    "lld",    ("rt","offset(base)"), (True , False       )),
    0b110101: (MIPS_INS_LDC1,   "ldc1",   ("ft","offset(base)"), (True , False       )),
    # ldc2
    0b110111: (MIPS_INS_LD,     "ld",     ("rt","offset(base)"), (True , False       )),
    0b111000: (MIPS_INS_SC,     "sc",     ("rt","offset(base)"), (False, False       )),
    0b111001: (MIPS_INS_SWC1,   "swc1",   ("ft","offset(base)"), (False, False       )),
    # lwc2
    0b111100: (MIPS_INS_SCD,    "scd",    ("rt","offset(base)"), (False, False       )),
    0b111101: (MIPS_INS_SDC1,   "sdc1",   ("ft","offset(base)"), (False, False       )),
    # sdc2
    0b111111: (MIPS_INS_SD,     "sd",     ("rt","offset(base)"), (False, False       )),
}

rsp_insns = {
    0b000000: (mips_get_special, {
        # opcode   id                 mnemonic   fields            field is written to
        0b000000: (MIPS_INS_SLL,     "sll",     ("rd","rt","sa"), (True , False, False)),
        0b000010: (MIPS_INS_SRL,     "srl",     ("rd","rt","sa"), (True , False, False)),
        0b000011: (MIPS_INS_SRA,     "sra",     ("rd","rt","sa"), (True , False, False)),
        0b000100: (MIPS_INS_SLLV,    "sllv",    ("rd","rt","rs"), (True , False, False)),
        0b000110: (MIPS_INS_SRLV,    "srlv",    ("rd","rt","rs"), (True , False, False)),
        0b000111: (MIPS_INS_SRAV,    "srav",    ("rd","rt","rs"), (True , False, False)),
        0b001000: (MIPS_INS_JR,      "jr",      ("rs",         ), (False,             )),
        0b001001: (MIPS_INS_JALR,    "jalr",    ("rs",         ), (False,             )), # technically also rd but it's always $ra
        0b001101: (MIPS_INS_BREAK,   "break",   ("code",       ), (False,             )),
        0b100000: (MIPS_INS_ADD,     "add",     ("rd","rs","rt"), (True , False, False)),
        0b100001: (MIPS_INS_ADDU,    "addu",    ("rd","rs","rt"), (True , False, False)),
        0b100010: (MIPS_INS_SUB,     "sub",     ("rd","rs","rt"), (True , False, False)),
        0b100011: (MIPS_INS_SUBU,    "subu",    ("rd","rs","rt"), (True , False, False)),
        0b100100: (MIPS_INS_AND,     "and",     ("rd","rs","rt"), (True , False, False)),
        0b100101: (MIPS_INS_OR,      "or",      ("rd","rs","rt"), (True , False, False)),
        0b100110: (MIPS_INS_XOR,     "xor",     ("rd","rs","rt"), (True , False, False)),
        0b100111: (MIPS_INS_NOR,     "nor",     ("rd","rs","rt"), (True , False, False)),
        0b101010: (MIPS_INS_SLT,     "slt",     ("rd","rs","rt"), (True , False, False)),
        0b101011: (MIPS_INS_SLTU,    "sltu",    ("rd","rs","rt"), (True , False, False)),
    }),
    0b000001: (mips_get_regimm, {
        0b00000: (MIPS_INS_BLTZ,    "bltz",    ("rs","offset"), (False, False)),
        0b00001: (MIPS_INS_BGEZ,    "bgez",    ("rs","offset"), (False, False)),
        0b10000: (MIPS_INS_BLTZAL,  "bltzal",  ("rs","offset"), (False, False)),
        0b10001: (MIPS_INS_BGEZAL,  "bgezal",  ("rs","offset"), (False, False)),
    }),
    0b000010: (MIPS_INS_J,     "j",     ("target",         ), (False,             )),
    0b000011: (MIPS_INS_JAL,   "jal",   ("target",         ), (False,             )),
    0b000100: (MIPS_INS_BEQ,   "beq",   ("rs","rt","offset"), (False, False, False)),
    0b000101: (MIPS_INS_BNE,   "bne",   ("rs","rt","offset"), (False, False, False)),
    0b000110: (MIPS_INS_BLEZ,  "blez",  ("rs","offset"     ), (False, False       )),
    0b000111: (MIPS_INS_BGTZ,  "bgtz",  ("rs","offset"     ), (False, False       )),
    0b001000: (MIPS_INS_ADDI,  "addi",  ("rt","rs","imm"   ), (True , False, False)),
    0b001001: (MIPS_INS_ADDIU, "addiu", ("rt","rs","imm"   ), (True , False, False)),
    0b001010: (MIPS_INS_SLTI,  "slti",  ("rt","rs","imm"   ), (True , False, False)),
    0b001011: (MIPS_INS_SLTIU, "sltiu", ("rt","rs","imm"   ), (True , False, False)),
    0b001100: (MIPS_INS_ANDI,  "andi",  ("rt","rs","imm"   ), (True , False, False)),
    0b001101: (MIPS_INS_ORI,   "ori",   ("rt","rs","imm"   ), (True , False, False)),
    0b001110: (MIPS_INS_XORI,  "xori",  ("rt","rs","imm"   ), (True , False, False)),
    0b001111: (MIPS_INS_LUI,   "lui",   ("rt","imm"        ), (True , False       )),
    0b010000: (mips_get_cop0, {
        0b00000: (MIPS_INS_MFC0, "mfc0", ("rt","cd"), (True , False)),
        0b00100: (MIPS_INS_MTC0, "mtc0", ("rt","cd"), (False, True )),
    }),
    0b010010: (mips_get_cop2_func, { # TODO this encoding got ugly, move to a mask matcher like gnu objdump
        0b0: (mips_get_cop2, {
            0b0000: (MIPS_INS_MFC2, "mfc2", ("rt", "vd[e]"), (True , False)),
            0b0100: (MIPS_INS_MTC2, "mtc2", ("rt", "vd[e]"), (False, True )),
            0b0010: (MIPS_INS_CFC2, "cfc2", ("rt", "vc"   ), (True , False)),
            0b0110: (MIPS_INS_CTC2, "ctc2", ("rt", "vc"   ), (False, True )),
        }),
        0b1: (mips_get_function, {
            0b000000: (MIPS_INS_VMULF, "vmulf", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b000001: (MIPS_INS_VMULU, "vmulu", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b000010: (MIPS_INS_VRNDP, "vrndp", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b000011: (MIPS_INS_VMULQ, "vmulq", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b000100: (MIPS_INS_VMUDL, "vmudl", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b000101: (MIPS_INS_VMUDM, "vmudm", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b000110: (MIPS_INS_VMUDN, "vmudn", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b000111: (MIPS_INS_VMUDH, "vmudh", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b001000: (MIPS_INS_VMACF, "vmacf", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b001001: (MIPS_INS_VMACU, "vmacu", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b001010: (MIPS_INS_VRNDN, "vrndn", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b001011: (MIPS_INS_VMACQ, "vmacq", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b001100: (MIPS_INS_VMADL, "vmadl", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b001101: (MIPS_INS_VMADM, "vmadm", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b001110: (MIPS_INS_VMADN, "vmadn", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b001111: (MIPS_INS_VMADH, "vmadh", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b010000: (MIPS_INS_VADD,  "vadd",  ("vd", "vs", "vt[e]"), (True , False, False)),
            0b010001: (MIPS_INS_VSUB,  "vsub",  ("vd", "vs", "vt[e]"), (True , False, False)),
            0b010011: (MIPS_INS_VABS,  "vabs",  ("vd", "vs", "vt[e]"), (True , False, False)),
            0b010100: (MIPS_INS_VADDC, "vaddc", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b010101: (MIPS_INS_VSUBC, "vsubc", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b011101: (MIPS_INS_VSAR,  "vsar",  ("vd", "vs", "vt[e]"), (True , False, False)),
            0b100000: (MIPS_INS_VLT,   "vlt",   ("vd", "vs", "vt[e]"), (True , False, False)),
            0b100001: (MIPS_INS_VEQ,   "veq",   ("vd", "vs", "vt[e]"), (True , False, False)),
            0b100010: (MIPS_INS_VNE,   "vne",   ("vd", "vs", "vt[e]"), (True , False, False)),
            0b100011: (MIPS_INS_VGE,   "vge",   ("vd", "vs", "vt[e]"), (True , False, False)),
            0b100100: (MIPS_INS_VCL,   "vcl",   ("vd", "vs", "vt[e]"), (True , False, False)),
            0b100101: (MIPS_INS_VCH,   "vch",   ("vd", "vs", "vt[e]"), (True , False, False)),
            0b100110: (MIPS_INS_VCR,   "vcr",   ("vd", "vs", "vt[e]"), (True , False, False)),
            0b100111: (MIPS_INS_VMRG,  "vmrg",  ("vd", "vs", "vt[e]"), (True , False, False)),
            0b101000: (MIPS_INS_VAND,  "vand",  ("vd", "vs", "vt[e]"), (True , False, False)),
            0b101001: (MIPS_INS_VNAND, "vnand", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b101010: (MIPS_INS_VOR,   "vor",   ("vd", "vs", "vt[e]"), (True , False, False)),
            0b101011: (MIPS_INS_VNOR,  "vnor",  ("vd", "vs", "vt[e]"), (True , False, False)),
            0b101100: (MIPS_INS_VXOR,  "vxor",  ("vd", "vs", "vt[e]"), (True , False, False)),
            0b101101: (MIPS_INS_VNXOR, "vnxor", ("vd", "vs", "vt[e]"), (True , False, False)),
            0b110000: (MIPS_INS_VRCP,  "vrcp",  ("vd[ed]", "vt[e]"  ), (True , False)),
            0b110001: (MIPS_INS_VRCPL, "vrcpl", ("vd[ed]", "vt[e]"  ), (True , False)),
            0b110010: (MIPS_INS_VRCPH, "vrcph", ("vd[ed]", "vt[e]"  ), (True , False)),
            0b110011: (MIPS_INS_VMOV,  "vmov",  ("vd[ed]", "vt[e]"  ), (True , False)),
            0b110100: (MIPS_INS_VRSQ,  "vrsq",  ("vd[ed]", "vt[e]"  ), (True , False)),
            0b110101: (MIPS_INS_VRSQL, "vrsql", ("vd[ed]", "vt[e]"  ), (True , False)),
            0b110110: (MIPS_INS_VRSQH, "vrsqh", ("vd[ed]", "vt[e]"  ), (True , False)),
            0b110111: (MIPS_INS_VNOP,  "vnop",  (                   ), ()),
        }),
    }),
    0b100000: (MIPS_INS_LB,     "lb",     ("rt","offset(base)"), (True , False)),
    0b100001: (MIPS_INS_LH,     "lh",     ("rt","offset(base)"), (True , False)),
    0b100011: (MIPS_INS_LW,     "lw",     ("rt","offset(base)"), (True , False)),
    0b100100: (MIPS_INS_LBU,    "lbu",    ("rt","offset(base)"), (True , False)),
    0b100101: (MIPS_INS_LHU,    "lhu",    ("rt","offset(base)"), (True , False)),
    0b101000: (MIPS_INS_SB,     "sb",     ("rt","offset(base)"), (False, False)),
    0b101001: (MIPS_INS_SH,     "sh",     ("rt","offset(base)"), (False, False)),
    0b101011: (MIPS_INS_SW,     "sw",     ("rt","offset(base)"), (False, False)),   
    0b110010: (mips_get_lwc2, {
        0b00000: (MIPS_INS_LBV, "lbv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b00001: (MIPS_INS_LSV, "lsv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b00010: (MIPS_INS_LLV, "llv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b00011: (MIPS_INS_LDV, "ldv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b00100: (MIPS_INS_LQV, "lqv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b00101: (MIPS_INS_LRV, "lrv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b00110: (MIPS_INS_LPV, "lpv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b00111: (MIPS_INS_LUV, "luv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b01000: (MIPS_INS_LHV, "lhv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b01001: (MIPS_INS_LFV, "lfv", ("vt[ed]", "voffset(base)"), (True , False)),
        0b01011: (MIPS_INS_LTV, "ltv", ("vt[ed]", "voffset(base)"), (True , False)),
    }),
    0b111010: (mips_get_swc2, {
        0b00000: (MIPS_INS_SBV, "sbv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b00001: (MIPS_INS_SSV, "ssv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b00010: (MIPS_INS_SLV, "slv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b00011: (MIPS_INS_SDV, "sdv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b00100: (MIPS_INS_SQV, "sqv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b00101: (MIPS_INS_SRV, "srv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b00110: (MIPS_INS_SPV, "spv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b00111: (MIPS_INS_SUV, "suv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b01000: (MIPS_INS_SHV, "shv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b01001: (MIPS_INS_SFV, "sfv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b01010: (MIPS_INS_SWV, "swv", ("vt[ed]", "voffset(base)"), (False, False)),
        0b01011: (MIPS_INS_STV, "stv", ("vt[ed]", "voffset(base)"), (False, False)),
    }),
}
