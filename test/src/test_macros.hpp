#pragma once

#include <string>

#define _CPUFW_SLEEPYTEST_INIT_VARS()	registers regs; \
										memory mem; \
										vcpu_firmware vfw(&mem, &regs); \
										auto& inst_map = vfw.inst_map; \
										memset(mem.data(), 0, (0xFFFF * sizeof(byte_t)));\
										regs.zero_registers(true);\
										const registers::flag FLAG_SUB = registers::flag::SUB;\
										const registers::flag FLAG_ZERO = registers::flag::ZERO;\
										const registers::flag FLAG_HCARRY = registers::flag::HALF_CARRY;\
										const registers::flag FLAG_CARRY = registers::flag::CARRY

#define _CPUFW_SLEEPYTEST_INIT_NOWARN() UNREFERENCED_PARAMETER(inst_map);\
										UNREFERENCED_PARAMETER(regs);\
										UNREFERENCED_PARAMETER(mem);\

/* Initialize common cpu firmware unit test variables [sys,regs,mem,inst_map] */
#define CPUFW_SLEEPY_TESTINIT() _CPUFW_SLEEPYTEST_INIT_VARS();_CPUFW_SLEEPYTEST_INIT_NOWARN()