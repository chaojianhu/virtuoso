/*
 *  i386 micro operations (templates for various register related
 *  operations)
 *
 *  Copyright (c) 2003 Fabrice Bellard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */


#ifndef IFLW_WRAPPER
#error "Why is IFLW_WRAPPER not defined?"
#endif

// info-flow log write with reg as an implied param
#define IFLW_REG(op) \
IFLW_WRAPPER ( \
  IFLW_PUT_OP(glue(INFO_FLOW_OP_REG_,op)); \
  IFLW_PUT_ARG(REGNUM); \
)


void OPPROTO glue(op_movl_A0,REGNAME)(void)
{
  // we'll code the REG into the info flow log element
  IFLW_REG(MOVL_A0_R); 
    A0 = (uint32_t)REG;
}

void OPPROTO glue(op_addl_A0,REGNAME)(void)
{
  IFLW_REG(ADDL_A0_R); 
    A0 = (uint32_t)(A0 + REG);
}

void OPPROTO glue(glue(op_addl_A0,REGNAME),_s1)(void)
{
  IFLW_REG(ADDL_A0_R_S1);
    A0 = (uint32_t)(A0 + (REG << 1));
}

void OPPROTO glue(glue(op_addl_A0,REGNAME),_s2)(void)
{
  IFLW_REG(ADDL_A0_R_S2);
    A0 = (uint32_t)(A0 + (REG << 2));
}

void OPPROTO glue(glue(op_addl_A0,REGNAME),_s3)(void)
{
  IFLW_REG(ADDL_A0_R_S3);
    A0 = (uint32_t)(A0 + (REG << 3));
}

#ifdef TARGET_X86_64
void OPPROTO glue(op_movq_A0,REGNAME)(void)
{
    A0 = REG;
}

void OPPROTO glue(op_addq_A0,REGNAME)(void)
{
    A0 = (A0 + REG);
}

void OPPROTO glue(glue(op_addq_A0,REGNAME),_s1)(void)
{
    A0 = (A0 + (REG << 1));
}

void OPPROTO glue(glue(op_addq_A0,REGNAME),_s2)(void)
{
    A0 = (A0 + (REG << 2));
}

void OPPROTO glue(glue(op_addq_A0,REGNAME),_s3)(void)
{
    A0 = (A0 + (REG << 3));
}
#endif

void OPPROTO glue(op_movl_T0,REGNAME)(void)
{
  IFLW_REG(MOVL_T0_R);
    T0 = REG;
}

void OPPROTO glue(op_movl_T1,REGNAME)(void)
{
  IFLW_REG(MOVL_T1_R);
    T1 = REG;
}

void OPPROTO glue(op_movh_T0,REGNAME)(void)
{
  IFLW_REG(MOVH_T0_R);
    T0 = REG >> 8;
}

void OPPROTO glue(op_movh_T1,REGNAME)(void)
{
  IFLW_REG(MOVH_T1_R);
    T1 = REG >> 8;
}

void OPPROTO glue(glue(op_movl,REGNAME),_T0)(void)
{
  IFLW_REG(MOVL_R_T0);
    REG = (uint32_t)T0;
}

void OPPROTO glue(glue(op_movl,REGNAME),_T1)(void)
{
  IFLW_REG(MOVL_R_T1);
    REG = (uint32_t)T1;
}

void OPPROTO glue(glue(op_movl,REGNAME),_A0)(void)
{
  IFLW_REG(MOVL_R_A0);
    REG = (uint32_t)A0;
}

#ifdef TARGET_X86_64
void OPPROTO glue(glue(op_movq,REGNAME),_T0)(void)
{
    REG = T0;
}

void OPPROTO glue(glue(op_movq,REGNAME),_T1)(void)
{
    REG = T1;
}

void OPPROTO glue(glue(op_movq,REGNAME),_A0)(void)
{
    REG = A0;
}
#endif

/* mov T1 to REG if T0 is true */
void OPPROTO glue(glue(op_cmovw,REGNAME),_T1_T0)(void)
{
  if (T0) {
    IFLW_REG(CMOVW_R_T1_T0);
        REG = (REG & ~0xffff) | (T1 & 0xffff);
  }
    FORCE_RET();
}

void OPPROTO glue(glue(op_cmovl,REGNAME),_T1_T0)(void)
{
  if (T0) {
    IFLW_REG(CMOVL_R_T1_T0);
        REG = (uint32_t)T1;
  }
    FORCE_RET();
}

#ifdef TARGET_X86_64
void OPPROTO glue(glue(op_cmovq,REGNAME),_T1_T0)(void)
{
  if (T0) {
        REG = T1;
  }
    FORCE_RET();
}
#endif

/* NOTE: T0 high order bits are ignored */
void OPPROTO glue(glue(op_movw,REGNAME),_T0)(void)
{
  IFLW_REG(MOVW_R_T0);
    REG = (REG & ~0xffff) | (T0 & 0xffff);
}

/* NOTE: T0 high order bits are ignored */
void OPPROTO glue(glue(op_movw,REGNAME),_T1)(void)
{
  IFLW_REG(MOVW_R_T1);
    REG = (REG & ~0xffff) | (T1 & 0xffff);
}

/* NOTE: A0 high order bits are ignored */
void OPPROTO glue(glue(op_movw,REGNAME),_A0)(void)
{
  IFLW_REG(MOVW_R_A0);
    REG = (REG & ~0xffff) | (A0 & 0xffff);
}

/* NOTE: T0 high order bits are ignored */
void OPPROTO glue(glue(op_movb,REGNAME),_T0)(void)
{
  IFLW_REG(MOVB_R_T0);
    REG = (REG & ~0xff) | (T0 & 0xff);
}

/* NOTE: T0 high order bits are ignored */
void OPPROTO glue(glue(op_movh,REGNAME),_T0)(void)
{
  IFLW_REG(MOVH_R_T0);
    REG = (REG & ~0xff00) | ((T0 & 0xff) << 8);
}

/* NOTE: T1 high order bits are ignored */
void OPPROTO glue(glue(op_movb,REGNAME),_T1)(void)
{
  IFLW_REG(MOVB_R_T1);
    REG = (REG & ~0xff) | (T1 & 0xff);
}

/* NOTE: T1 high order bits are ignored */
void OPPROTO glue(glue(op_movh,REGNAME),_T1)(void)
{
  IFLW_REG(MOVH_R_T1);
    REG = (REG & ~0xff00) | ((T1 & 0xff) << 8);
}

#undef REGNAME
#undef REGNUM
