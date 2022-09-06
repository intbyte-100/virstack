# Instructions
## Base instruction specification

The VRM has two instruction type. These are compressed and uncompressed instructions.
Compressed instructions are handling by the instruction decoder as uncompressed instruction.
Thus compressed instructions are a representation of uncompressed instructions.
When a compressed instruction is decoding first operand is doubling, so second operand began third. 

For example `add_rr R0, R1` is a representation for `add_rrr R0, R0, R1`


The exception to this rule is mov and some other instructions.

## Memory management
### 1. mov

The mov instructions copy value from source to destination.

#### compressed size instruction 
* `mov_rr Register, Register`. 
mov_rr instruction is copying value from one register to another. 
The binary representation is "0b10000000". It has no uncompressed analog.
* `mov_rp Register, Register (Pointer)`. mov_rp instruction is copying value from address that contains in second register to first register.
The binary representation is "0b10000001". 
The uncompressed analog is mov_rps instruction.

#### uncompressed size instructions

* `mov_rpf Register, Register (Pointer), 8-bit integer (Offset)`. mov_rpf instruction is copying value from address that contains in second register with an offset specified as third argument to first register.
The binary representation is "0b00000001".
The compressed analog is mov_rp instruction.