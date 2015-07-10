#!/bin/bash 

sed -i '1d' ./Section_Headers.txt 
sed -i -r '1,$ s/\[ /\[/g' ./Section_Headers.txt 
sed -i -r '1,$ s/ \(/\(/g' ./Section_Headers.txt 
sed -i -r '1,$ s/\, /\,/g' ./Section_Headers.txt 
sed -i -r '1,$ s/\,/ /g' ./Section_Headers.txt 
sed -i -r 's/ELF Header/文件头/' ./Section_Headers.txt 
sed -i -r 's/Magic:   /魔数    :/' ./Section_Headers.txt 
sed -i -r 's/Class:   /机器字长:/' ./Section_Headers.txt 
sed -i -r 's/Data:    /编码方式:/' ./Section_Headers.txt 
sed -i -r 's/  Version: /  版本    :/' ./Section_Headers.txt 
sed -i -r 's/ABI Version:/ABI版本 :   /' ./Section_Headers.txt 
sed -i -r 's/Type:    /类型    :/' ./Section_Headers.txt 
sed -i -r 's/Machine: /硬件平台:/' ./Section_Headers.txt 
sed -i -r 's/Entry point address:      /入口地址:		    /' ./Section_Headers.txt  
sed -i -r 's/Start of program headers: /段表位置:		    /' ./Section_Headers.txt 
sed -i -r 's/Start of section headers: /节表位置:		    /' ./Section_Headers.txt 
sed -i -r 's/Flags:   /标志位  :/' ./Section_Headers.txt 
sed -i -r 's/Size of this header:      /头部长度:		    /' ./Section_Headers.txt 
sed -i -r 's/Size of program headers:  /段表长度:		    /' ./Section_Headers.txt 
sed -i -r 's/Number of program headers:/段表数量:		    /' ./Section_Headers.txt 
sed -i -r 's/Size of section headers:  /节表长度:		    /' ./Section_Headers.txt 
sed -i -r 's/Number of section headers:/节表数量:		    /'  ./Section_Headers.txt 
sed -i -r 's/Section header string table index:/节表字符串表索引:                 /' ./Section_Headers.txt 
sed -i -r 's/Section Headers/节头表/' ./Section_Headers.txt 
sed  -i -r 's/Addr/地址/'  ./Section_Headers.txt 
sed  -i -r 's/   Off/偏移/'  ./Section_Headers.txt 
sed  -i -r 's/Size/大小/'  ./Section_Headers.txt 
sed  -i -r 's/Name/名称/'  ./Section_Headers.txt 
sed  -i -r 's/ Type/类型/'  ./Section_Headers.txt 
sed  -i -r 's/Key to/   /'  ./Section_Headers.txt 
sed  -i -r 's/write/可写/'  ./Section_Headers.txt 
sed  -i -r 's/alloc/可分配/'  ./Section_Headers.txt 
sed  -i -r 's/execute/可执行/'  ./Section_Headers.txt 
sed  -i -r 's/merge/可合并/'  ./Section_Headers.txt 
sed  -i -r 's/strings/字符串相关/'  ./Section_Headers.txt 
sed  -i -r 's/I (info)/I (SHT索引)/'  ./Section_Headers.txt 
sed  -i -r 's/link order/链接序号/'  ./Section_Headers.txt 
sed  -i -r 's/group/组成员/'  ./Section_Headers.txt 
sed  -i -r 's/TLS/本地数据/'  ./Section_Headers.txt 
sed  -i -r 's/exclude/不包含/'  ./Section_Headers.txt 
sed  -i -r 's/unknown/未知/'  ./Section_Headers.txt 
sed  -i -r 's/extra OS processing required/额外的操作系统处理需求/'  ./Section_Headers.txt 
sed  -i -r 's/OS specific/特殊操作系统/'  ./Section_Headers.txt 
sed  -i -r 's/processor specific/特殊处理器/'  ./Section_Headers.txt 

sed  -i -r 's/  ES Flg Lk Inf Al/项长 标志 链接 辅助 对齐/'  ./Section_Headers.txt 
sed  -i -r 's/Relocation section/重定位段的/'  ./Section_Headers.txt 
sed  -i -r 's/ at/在/'  ./Section_Headers.txt 
sed  -i -r 's/Offset/偏移量/'  ./Section_Headers.txt 
sed  -i -r 's/contains/包含/'  ./Section_Headers.txt 
sed  -i -r 's/entries/条目/'  ./Section_Headers.txt 
sed  -i -r 's/offset/偏移/'  ./Section_Headers.txt 
sed  -i -r 's/Info/符号表索引/'  ./Section_Headers.txt 
sed  -i -r 's/  Sym./符号/'  ./Section_Headers.txt 
sed  -i -r 's/Symbol table/符号表/'  ./Section_Headers.txt 
sed  -i -r 's/Num/序号/'  ./Section_Headers.txt 
sed  -i -r 's/Value/值/' ./Section_Headers.txt 
sed  -i -r 's/Bind/ 属性/'  ./Section_Headers.txt 
sed  -i -r 's/Vis/ 可见性/'  ./Section_Headers.txt 
sed  -i -r 's/    Ndx/索引/'  ./Section_Headers.txt 
sed  -i -r 's/Sym. /符号/'   ./Section_Headers.txt 
sed  -i -r 's/NOTYPE/无类型/'  ./Section_Headers.txt 
sed  -i -r 's/OBJECT/数据  /'  ./Section_Headers.txt 
sed  -i -r 's/FUNC/函数/'  ./Section_Headers.txt 
sed  -i -r 's/SECTION/段相关/'  ./Section_Headers.txt 
sed  -i -r 's/FILE/文件/'  ./Section_Headers.txt 
sed  -i -r 's/LOPROC/专用/'  ./Section_Headers.txt 
sed  -i -r 's/HIPROC/专用/'  ./Section_Headers.txt 
sed  -i -r 's/LOCAL/局部/'  ./Section_Headers.txt 
sed  -i -r 's/GLOBAL/全局/'  ./Section_Headers.txt 
sed  -i -r 's/WEAK  /弱符/'  ./Section_Headers.txt 

sed  -i -r 's/Contents of the/内容来自/'  ./Section_Headers.txt 
sed  -i -r 's/Compilation Unit/编译单元/'  ./Section_Headers.txt 
sed  -i -r 's/section/段/'  ./Section_Headers.txt 
sed  -i -r 's/Abbrev/缩略/'  ./Section_Headers.txt 
sed  -i -r 's/Pointer/指针/'  ./Section_Headers.txt 
sed  -i -r 's/Length/长度/'  ./Section_Headers.txt 
sed  -i -r 's/ Number/序号/'  ./Section_Headers.txt 

sed  -i -r 's/DW_TAG_compile_unit/编译单元/'  ./Section_Headers.txt 
sed  -i -r 's/ber//'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_producer/编译器/'  ./Section_Headers.txt 
sed  -i -r 's/DW_TAG_base_type/基本类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_subprogram/函数名称/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_variable/变量类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_array_type/数组名称/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_subrange_type/数组大小/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_formal_parameter/函数参数/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_pointer_type/指针类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_const_type/常量类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_inlined_subroutine/内联实例/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_entry_point/入口点/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_class_type/类名类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_structure_type/结构类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_union_type/结构类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_enumeration_type/枚举类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_typedef/typedef类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_inheritance/继承类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_TAG_member/类的成员/'  ./Section_Headers.txt  

sed  -i -r 's/DW_AT_virtuality  /虚拟类型/'  ./Section_Headers.txt  
sed  -i -r 's/DW_AT_name        /名称字符/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_language    /语言类型/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_comp_dir    /目录    /'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_type        /类型    /'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_sibling     /兄弟位置/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_upper_bound /上界    /'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_low_pc      /起始地址/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_high_pc     /结束地址/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_frame_base  /框架    /'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_decl_line   /所在行号/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_decl_file   /所在文件/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_external    /来自外部/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_location    /位置信息/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_stmt_list   /语句列表/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_encoding    /编码方式/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_byte_size   /类型大小/'  ./Section_Headers.txt 
sed  -i -r 's/DW_AT_prototyped  /原型    /'  ./Section_Headers.txt 

sed  -i -r 's/indirect string/间接字符串/'  ./Section_Headers.txt 
sed  -i -r 's/(location list)/位置信息表中/'  ./Section_Headers.txt 
sed  -i -r 's/byte block/字节块/'  ./Section_Headers.txt 
sed  -i -r 's/, offset/偏移量/'  ./Section_Headers.txt 

sed -i /^[[:space:]]*$/d  ./Section_Headers.txt
sed -i /^$/d ./Section_Headers.txt
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 





