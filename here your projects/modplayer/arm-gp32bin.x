/******************************************************************************
 * Linker script for arm-elf-ld v0.1 (w) Groepaz/Hitmen
 * Target CPU: Arm/T9  Machine: GamePark GP32
 *****************************************************************************/

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)                                                  /* code entry point */

MEMORY {

    /******* gp32 internal *******/

    bootrom   : ORIGIN = 0x00000000, LENGTH = 0x00040000       /* 512k (?) bootrom => fixme */
    sysram    : ORIGIN = 0x0C000000, LENGTH = 0x0077fffc       /* 8mb (?) system memory => fixme */
                                                               /* ~0.5mb reserved for system */
    stacktop  : ORIGIN = 0x0C77fffc, LENGTH = 0x00000004       /* top of user stack => fixme */

    /******* gamepak ********/

		/* any mem-mapped stuff here ? */

}

SECTIONS {

	/* ? */

  .interp        : { *(.interp)         }
  .hash          : { *(.hash)           }

  .dynsym        : { *(.dynsym)         }
  .dynstr        : { *(.dynstr)         }

	/* gnu version information */

  .gnu.version   : { *(.gnu.version)    }
  .gnu.version_d : { *(.gnu.version_d)  }
  .gnu.version_r : { *(.gnu.version_r)  }

  /* relocation information */

  .rel.text      : { *(.rel.text)
  		               *(.rel.text.*)
							*(.rel.gnu.linkonce.t*) }

  .rela.text     : { *(.rela.text)
  		               *(.rela.text.*)
							*(.rela.gnu.linkonce.t*) }

  .rel.data      : { *(.rel.data)
  		               *(.rel.data.*)
							*(.rel.gnu.linkonce.d*) }

  .rela.data     : { *(.rela.data)
  		               *(.rela.data.*)
							*(.rela.gnu.linkonce.d*) }

  .rel.rodata    : { *(.rel.rodata)
  		               *(.rel.rodata.*)
							*(.rel.gnu.linkonce.r*) }

  .rela.rodata   : { *(.rela.rodata)
  		               *(.rela.rodata.*)
							*(.rela.gnu.linkonce.r*) }

  .rel.got		  : { *(.rel.got) }
  .rela.got		  : { *(.rela.got) }

  .rel.ctors     : { *(.rel.ctors) }
  .rela.ctors    : { *(.rela.ctors) }

  .rel.ctors     : { *(.rel.ctors) }
  .rela.ctors    : { *(.rela.ctors) }

  .rel.init      : { *(.rel.init) }
  .rela.init     : { *(.rela.init) }

  .rel.fini      : { *(.rel.fini) }
  .rela.fini     : { *(.rela.fini) }

  .rel.bss       : { *(.rel.bss) }
  .rela.bss      : { *(.rela.bss) }

  .rel.plt       : { *(.rel.plt) }
  .rela.plt      : { *(.rela.plt) }

  /* ? */

  .init          : { *(.init) }
  .plt           : { *(.plt) }

  /* program layout information */

  .text : {  /* CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE */

                *(.text)                           /* code */
		*(.text.*)
		*(.stub)                           /* debug-stub code */
		*(.gnu.warning)
		*(.gnu.linkonce.t*)
		*(.glue_7t);                       /* ? */
		*(.glue_7);                        /* ? */

		_etext = ABSOLUTE(.) ;             /* => provide adr. of end of text */

  		PROVIDE (etext = .);

    } > sysram

  .fini : { *(.fini) }

  .got : { *(.got.plt)                   /* ? */
           *(.got)     }

  .dynamic : { *(.dynamic) }             /* ? */

  .tors : {  /* CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA */

		/* .ctors */
		. = ALIGN(4);
    	__ctors = ABSOLUTE(.) ;
   	*(.ctors)                          /* c++ constructors */
   	__ctors_end = ABSOLUTE(.) ;

		/* .dtors */
   	. = ALIGN(4);
    	__dtors = ABSOLUTE(.) ;
   	*(.dtors)                          /* c++ destructors */
   	__dtors_end = ABSOLUTE(.) ;

  } > sysram

  .rodata : {  /* CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA */

        . = ALIGN(4);

                *(.rodata)                         /* initialized data */
		*(.rodata.*)
		*(.gnu.linkonce.r*)
		/* .rodata1 */
		*(.rodata1)

        . = ALIGN(4);

		_erodata = ABSOLUTE(.) ;
		_romdata = ABSOLUTE(.) ;

		PROVIDE(romdata = .);

   } > sysram

/*  _idata = 0xc100000 ;*/
/*  _idata = . ; */

/*  .data _idata : AT (_romdata) { */  /* CONTENTS, ALLOC, LOAD, DATA */
  .data : {  /* CONTENTS, ALLOC, LOAD, DATA */

        . = ALIGN(4);

		_bdata = ABSOLUTE(.) ;
                _bdata = . ;
  		PROVIDE (bdata = .);

                *(.data)          /* CONTENTS, ALLOC, LOAD, DATA */
		*(.data.*)
		*(.gnu.linkonce.d*)

                 *(.data1)

        . = ALIGN(4);

                /* short initialized/writeable data field */
		*(.sdata)
		*(.sdata.*)

        . = ALIGN(4);

		*(COMMON)
		*(.COMMON)
		*(common)
		*(.common)

        . = ALIGN(4);

		_edata = ABSOLUTE(.) ;
  		PROVIDE (edata = .);

  } > sysram

        . = ALIGN(4);

/*  _bstart = ( _edata - _bdata ) + _edata ; */

        _bstart = ABSOLUTE(.) ;

  .bss _bstart (NOLOAD)  : {                            /* non-initialized data */
/*  .bss (NOLOAD)  : { */                           /* non-initialized data */

		*(dynbss)
		*(.bss)
		*(.bss.*)

        . = ALIGN(4);
                /* short bss data field */
		*(.sbss)
		*(.scommon)

  }

        . = ALIGN(4);

    _end = ABSOLUTE(.) ;
    end = ABSOLUTE(.) ;  			/* needed for screwed up _sbrk ?! */

    _bend = ABSOLUTE(.) ;

  PROVIDE(bend = .);

	PROVIDE (end = .);

                                             /* the heap will be here */

  .stack (NOLOAD) : {
    	*(.stack)                              /* cpu-stack */
    	_stack = ABSOLUTE(.) ;
    } > stacktop

  /**************************** debug information ****************************/


  /* Stabs debugging sections.  */
  .stab 		   0 : { *(.stab)          }             /* ? */
  .stabstr 		   0 : { *(.stabstr)       }             /* ? */
  .stab.excl 	   0 : { *(.stab.excl) 	 }               /* ? */
  .stab.exclstr    0 : { *(.stab.exclstr)  }             /* ? */
  .stab.index 	   0 : { *(.stab.index)    }             /* ? */
  .stab.indexstr   0 : { *(.stab.indexstr) }             /* ? */
  .comment 		   0 : { *(.comment)       }             /* ? */
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug 		   0 : { *(.debug)         }             /* ? */
  .line 		   0 : { *(.line)          }             /* ? */
  /* GNU DWARF 1 extensions */
  .debug_srcinfo   0 : {  *(.debug_srcinfo)   }
  .debug_sfnames   0 : {  *(.debug_sfnames)   }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges   0 : {  *(.debug_aranges)   }
  .debug_pubnames  0 : {  *(.debug_pubnames)  }
  /* DWARF 2 */
  .debug_info      0 : {  *(.debug_info)      }
  .debug_abbrev    0 : {  *(.debug_abbrev)    }
  .debug_line      0 : {  *(.debug_line)      }
  .debug_frame     0 : {  *(.debug_frame)     }
  .debug_str       0 : {  *(.debug_str)       }
  .debug_loc       0 : {  *(.debug_loc)       }
  .debug_macinfo   0 : {  *(.debug_macinfo)   }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : {  *(.debug_weaknames) }
  .debug_funcnames 0 : {  *(.debug_funcnames) }
  .debug_typenames 0 : {  *(.debug_typenames) }
  .debug_varnames  0 : {  *(.debug_varnames)  }

}
