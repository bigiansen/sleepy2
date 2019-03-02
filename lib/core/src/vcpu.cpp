#include <sleepy/vcpu.hpp>

#include <iostream>

namespace sleepy
{
    vcpu::vcpu()
        : _vfw(vcpu_firmware(&_mem, &_regs))
    { }

    void vcpu::exec_op(opcode op, byte_t* args)
    {
        auto& inst = _vfw.inst_map[op];

        _pre_exec_debug_fun(*this, &inst);
        inst.call(args);
        _post_exec_debug_fun(*this, &inst);
        
        _last_executed_inst = &inst;
        _regs.pc += inst.pc_offset;
    }

    const memory& vcpu::memory() const noexcept
    {
        return _mem;
    }

    const registers& vcpu::registers() const noexcept
    {
        return _regs;
    }

    const vcpu_instruction& vcpu::get_inst_data(opcode op)
    {
        return _vfw.inst_map[op];
    }

    void vcpu::start()
    {
        if(!_memory_set)
        { 
            throw std::logic_error("Unable to start vcpu without setting memory data!");
        }
        _regs.zero_registers(true);
        while(true)
        {
            byte_t op = _mem.read_byte(_regs.pc);
            if(op == 0xCBu)
            {
                ++(_regs.pc);
                byte_t opv = _mem.read_byte(_regs.pc);
                opcode opc(op, opv);
                byte_t* args = &_mem.data()[_regs.pc + 1];
                exec_op(opc, args);
            }
            else
            {
                opcode opc(op);
                byte_t* args = &_mem.data()[_regs.pc + 1];
                exec_op(opc, args);
            }
        }
    }

    void vcpu::setup_memory(std::istream& data)
    {
        std::istream_iterator<sleepy::byte_t> beg(data);
        std::istream_iterator<sleepy::byte_t> end;

        std::vector<byte_t> cdata(beg, end);

        std::copy(cdata.begin(), cdata.begin() + 0xFFFF, _mem.data());
        _memory_set = true;
    }

    void vcpu::setup_debug(debug_func_t pre_exec, debug_func_t post_exec)
    {
        _pre_exec_debug_fun = pre_exec;
        _post_exec_debug_fun = post_exec;
        _debug_enabled = true;
    }

    void vcpu::enable_debug(bool enabled)
    {
        _debug_enabled = false;
    }

    const vcpu_instruction* vcpu::last_executed_instruction() const noexcept
    {
        return _last_executed_inst;
    }
}