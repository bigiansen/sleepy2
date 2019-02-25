#include <catch2/catch.hpp>

#include <sleepy/vcpu_firmware.hpp>
#include "test_macros.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_DEC_R8")
	{
		SECTION("DEC_R8_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& dec_a = inst_map[opcode(0x3D)];
			vcpu_instruction& dec_b = inst_map[opcode(0x05)];
			vcpu_instruction& dec_c = inst_map[opcode(0x0D)];
			vcpu_instruction& dec_d = inst_map[opcode(0x15)];
			vcpu_instruction& dec_e = inst_map[opcode(0x1D)];
			vcpu_instruction& dec_h = inst_map[opcode(0x25)];
			vcpu_instruction& dec_l = inst_map[opcode(0x2D)];
			vcpu_instruction& dec_phl = inst_map[opcode(0x35)];

			regs.a = 0x01;
			dec_a.call(nullptr);
			REQUIRE(0x00 == regs.a);

			regs.a = 0x00;
			dec_a.call(nullptr);
			REQUIRE(0xFF == regs.a);
		}

		SECTION("DEC_R8_CorrectFlags")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& dec_a = inst_map[opcode(0x3D)];
			vcpu_instruction& dec_b = inst_map[opcode(0x05)];
			vcpu_instruction& dec_c = inst_map[opcode(0x0D)];
			vcpu_instruction& dec_d = inst_map[opcode(0x15)];
			vcpu_instruction& dec_e = inst_map[opcode(0x1D)];
			vcpu_instruction& dec_h = inst_map[opcode(0x25)];
			vcpu_instruction& dec_l = inst_map[opcode(0x2D)];
			vcpu_instruction& dec_phl = inst_map[opcode(0x35)];

			regs.a = 0x00;
			dec_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));

			regs.a = 0x01;
			dec_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(regs.read_flag(FLAG_ZERO));

			regs.a = 0x0F;
			dec_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));

			regs.a = 0xFF;
			dec_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
		}
	};
}